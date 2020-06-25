/*
 * dwm_lib.h
 *
 *  Created on: Jun 12, 2020
 *      Author: aswin
 */

#ifndef INC_DWM_LIB_H_
#define INC_DWM_LIB_H_

//Register Addresses
#define DWM_REG_DEVID 0x00

#define DWM_REG_FILE_AGC_CONTROL 0x23
#define DWM_REG_ADDR_AGC_TUNE1 0x04
#define DWM_REG_ADDR_AGC_TUNE2 0x0C

#define DWM_REG_FILE_DRX_CONF 0x27
#define DWM_REG_ADDR_DRX_TUNE2 0x08

#define DWM_REG_FILE_LDE_INT 0x2E
#define DWM_REG_ADDR_LDE_CFG2 0x1806

#define DWM_REG_FILE_TX_POWER_CTRL 0x1E

#define DWM_REG_FILE_ANALOG_RF_CONF 0x28
#define DWM_REG_ADDR_RF_TXCTRL 0x0C
#define DWM_REG_ADDR_LDOTUNE 0x30

#define DWM_REG_FILE_TX_CAL 0x2A
#define DWM_REG_ADDR_TC_PGDELAY 0x0B

#define DWM_REG_FILE_FS_CTRL 0x2B
#define DWM_REG_ADDR_FS_PLLTUNE 0x0B

#define DWM_REG_FILE_OTP_IF 0x2D
#define DWM_REG_ADDR_OTP_ADDR 0x04
#define DWM_REG_ADDR_OTP_CTRL 0x06
#define DWM_REG_ADDR_OTP_RDAT 0x0A

#define DWM_OTP_ADDR_LDO_CAL 0x4

#define DWM_REG_FILE_TX_FCRTL 0x08
#define DWM_REG_FILE_TX_BUFFER 0x09

#define DWM_REG_FILE_SYS_CTRL 0x0D
#define DWM_REG_FILE_SYS_STATUS 0x0F

#define DWM_REG_FILE_RX_FINFO 0x10
#define DWM_REG_FILE_RX_BUFFER 0x11

#define DWM_REG_FILE_PMSC 0x36
#define DWM_REG_ADDR_PMSC_CTRL1 0x04



//Register values
#define DWM_AGC_TUNE1_PRF_16_MHZ 0x8870
#define DWM_AGC_TUNE2_OPT 0x2502A907

#define DWM_DRX_TUNE2_OPT 0x311A002D

#define DWM_LDE_CFG2_PRF_16_MHZ 0X1607

#define DWM_TX_POWER_OPT 0x0E082848

#define DWM_RF_TXCTRL_CH5_OPT 0x1E3FE3

#define DWM_TC_PGDELAY_CH5_OPT 0xC0

#define DWM_FS_PLLTUNE_CH5_OPT 0xBE

#define DWM_OTP_READ 0x03


//Bit Flags
#define DWM_SYS_STATUS_RXPHE 0x10 //sys status 2nd byte
#define DWM_SYS_STATUS_RXFCE 0x80 //sys status 2nd byte
#define DWM_SYS_STATUS_RXDFR 0x20 //sys status 2nd byte
#define DWM_SYS_STATUS_RXRFSL 0x1 //sys status 3rd byte

uint32_t dwm_read_deviceID(void);
void modify_default_conf(void);
void read_OTP_mem(uint32_t otpAddr, uint8_t* dataBuf, uint32_t dataLen);
void dwm_transmit(uint8_t* pData, uint8_t dataLen);
void dwm_receive(uint8_t* pData, uint8_t* dataLen);

#endif /* INC_DWM_LIB_H_ */
