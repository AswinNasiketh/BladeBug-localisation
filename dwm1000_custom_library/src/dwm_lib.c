/*
 * dwm_lib.c
 *
 *  Created on: Jun 12, 2020
 *      Author: aswin
 */

#include "dwm_spi.h"
#include "dwm_lib.h"
#include "stdlib.h"


uint32_t dwm_read_deviceID(void){
	uint8_t data[4];

	dwm_readreg_single_byte_header(DWM_REG_DEVID, data, 4);

	return (data[3] << 24) | (data[2] << 16) | (data[1] << 8) | data[0];
}

void shift_data_to_uint8_array(uint32_t data, uint8_t* array, uint8_t numBytes){
	for(int j = 0; j < numBytes ; j++){
		array[j] = (data >> (8 * numBytes - 1 - j)) & 0xFF;
	}
}


//function to modify the default configurations as given in section 2.5.5 of user manual
void modify_default_conf(void){
	uint8_t data[4];

	//ACG_Tune_1
	shift_data_to_uint8_array(DWM_AGC_TUNE1_PRF_16_MHZ, data, 2);
	dwm_writereg_double_byte_header(DWM_REG_FILE_AGC_CONTROL, DWM_REG_ADDR_AGC_TUNE1, data , 2);

	//ACG_Tune_ 2
	shift_data_to_uint8_array(DWM_AGC_TUNE2_OPT, data, 4);
	dwm_writereg_double_byte_header(DWM_REG_FILE_AGC_CONTROL, DWM_REG_ADDR_AGC_TUNE2, data , 4);

	//DRX_Tune_2
	shift_data_to_uint8_array(DWM_DRX_TUNE2_OPT, data, 4);
	dwm_writereg_double_byte_header(DWM_REG_FILE_DRX_CONF, DWM_REG_ADDR_DRX_TUNE2, data , 4);

	//Skip NTM

	//LDE_CONF2
	shift_data_to_uint8_array(DWM_LDE_CFG2_PRF_16_MHZ, data, 2);
	dwm_writereg_triple_byte_header(DWM_REG_FILE_LDE_INT, DWM_REG_ADDR_LDE_CFG2, data, 2);

	//TX_POWER
	shift_data_to_uint8_array(DWM_TX_POWER_OPT, data, 4);
	dwm_writereg_single_byte_header(DWM_REG_FILE_TX_POWER_CTRL, data, 4);

	//RF_TXCTRL
	shift_data_to_uint8_array(DWM_RF_TXCTRL_CH5_OPT, data, 3);
	dwm_writereg_double_byte_header(DWM_REG_FILE_ANALOG_RF_CONF, DWM_REG_ADDR_RF_TXCTRL, data, 3);

	//TC_PGDELAY
	shift_data_to_uint8_array(DWM_TC_PGDELAY_CH5_OPT, data, 1);
	dwm_writereg_double_byte_header(DWM_REG_FILE_TX_CAL, DWM_REG_ADDR_TC_PGDELAY, data, 1);

	//FS_PLLTUNE
	shift_data_to_uint8_array(DWM_FS_PLLTUNE_CH5_OPT, data, 1);
	dwm_writereg_double_byte_header(DWM_REG_FILE_FS_CTRL, DWM_REG_ADDR_FS_PLLTUNE, data, 1);

	//skip LDELOAD - come back later when ranging required

	//disable LDERUNE
	dwm_readreg_double_byte_header(DWM_REG_FILE_PMSC, DWM_REG_ADDR_PMSC_CTRL1, data, 4);
	data[2] &= 0xFD; //clear second bit in 3rd octet
	dwm_writereg_double_byte_header(DWM_REG_FILE_PMSC, DWM_REG_ADDR_PMSC_CTRL1, data, 4);

	uint8_t dataBuf[5];
	read_OTP_mem(DWM_OTP_ADDR_LDO_CAL, dataBuf, 4);
	read_OTP_mem(DWM_OTP_ADDR_LDO_CAL + 1, &dataBuf[4], 1);
	if(dataBuf[0]){ //check LSB of LDOTUNE_CAL
		//if nonzero, write contents of LDO_CAL in OTP to LDOTUNE register
		dwm_writereg_double_byte_header(DWM_REG_FILE_ANALOG_RF_CONF, DWM_REG_ADDR_LDOTUNE, dataBuf, 5);
	}

}

void read_OTP_mem(uint32_t otpAddr, uint8_t* dataBuf, uint32_t dataLen){
	uint8_t data[2];

	//Write Address to OTP_ADDR
	shift_data_to_uint8_array(otpAddr, data, 2);
	dwm_writereg_double_byte_header(DWM_REG_FILE_OTP_IF, DWM_REG_ADDR_OTP_ADDR, data, 2);

	//Write read control to OTP_CTRL
	shift_data_to_uint8_array(DWM_OTP_READ, data, 1);
	dwm_writereg_double_byte_header(DWM_REG_FILE_OTP_IF, DWM_REG_ADDR_OTP_CTRL, data, 1);

	//Clear OTP_CTRL
	shift_data_to_uint8_array(0, data, 1);
	dwm_writereg_double_byte_header(DWM_REG_FILE_OTP_IF, DWM_REG_ADDR_OTP_CTRL, data, 1);

	//Read OTP_RDAT for read value
	dwm_readreg_double_byte_header(DWM_REG_FILE_OTP_IF, DWM_REG_ADDR_OTP_RDAT, dataBuf, dataLen);

}


//only supports data lengths of up to 125 for now - blocking
void dwm_transmit(uint8_t* pData, uint8_t dataLen){
	//configure frame length
	uint8_t tx_fctrl_contents[5];
	dwm_readreg_single_byte_header(DWM_REG_FILE_TX_FCRTL, tx_fctrl_contents, 5);

	tx_fctrl_contents[0] &= 0xC0; //reset lowest 6 bits
	tx_fctrl_contents[0] |= ((dataLen + 2) & 0x3F); //add 2 to include two octet CRC, then reset most significant 2 bits before merging with tx_fctrl_contents

	dwm_writereg_single_byte_header(DWM_REG_FILE_TX_FCRTL, tx_fctrl_contents, 5);

	//write frame contents to tx buffer
	dwm_writereg_single_byte_header(DWM_REG_FILE_TX_BUFFER, pData, dataLen);

	//start tx
	uint8_t sys_ctrl_contents[4];
	dwm_readreg_single_byte_header(DWM_REG_FILE_SYS_CTRL, sys_ctrl_contents, 4);
	sys_ctrl_contents[0] |= 0x02; //set TXSTRT bit
	dwm_writereg_single_byte_header(DWM_REG_FILE_SYS_CTRL, sys_ctrl_contents, 4);

	//wait for frame sent event by checking TXFRS bit
	uint8_t sys_status_contents[5] = {0,0,0,0,0};
	while(!(sys_status_contents[0] & 0x80)){
		dwm_readreg_single_byte_header(DWM_REG_FILE_SYS_STATUS, sys_status_contents, 5);
	}

}

//both parameters are outputs of the function, function is blocking
void dwm_receive(uint8_t* pData, uint8_t* dataLen){
	//start receive process
	uint8_t sys_ctrl_contents[4];
	dwm_readreg_single_byte_header(DWM_REG_FILE_SYS_CTRL, sys_ctrl_contents, 4);
	sys_ctrl_contents[1] |= 0x01; //set RXENAB bit
	dwm_writereg_single_byte_header(DWM_REG_FILE_SYS_CTRL, sys_ctrl_contents, 4);


	//wait for frame received event by checking RXDFR bit
	//TODO: add error bit checking
	uint8_t sys_status_contents[5] = {0,0,0,0,0};
	while(!((sys_status_contents[1] & (DWM_SYS_STATUS_RXDFR | DWM_SYS_STATUS_RXFCE | DWM_SYS_STATUS_RXPHE)) |  (sys_status_contents[2] & DWM_SYS_STATUS_RXRFSL))){
		dwm_readreg_single_byte_header(DWM_REG_FILE_SYS_STATUS, sys_status_contents, 5);
		__NOP();
	}

	if(!(sys_status_contents[1] & DWM_SYS_STATUS_RXDFR)){
		*dataLen = 0;
		return;
	}

	//read received frame info to find length
	uint8_t rx_finfo_contents[4];
	dwm_readreg_single_byte_header(DWM_REG_FILE_RX_FINFO, rx_finfo_contents, 4);
	*dataLen = rx_finfo_contents[0] & 0x3F; //reset most significant 2 bits

	//read rx buffer
	pData = malloc((*dataLen) * sizeof(uint8_t));
	dwm_readreg_single_byte_header(DWM_REG_FILE_RX_BUFFER, pData, *dataLen);
}
