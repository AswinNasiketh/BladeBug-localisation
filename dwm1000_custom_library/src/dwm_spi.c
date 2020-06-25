/*
 * dwm_spi.c
 *
 *  Created on: Jun 12, 2020
 *      Author: aswin
 */


#include "dwm_spi.h"
#include "main.h"

static SPI_HandleTypeDef* spi_handle;

void attach_SPI_Handle(SPI_HandleTypeDef* hspi){
	spi_handle = hspi;
}

void dwm_writereg_single_byte_header(uint8_t regFileID, uint8_t* data, uint32_t dataLen){
	regFileID |= DWM_WRITE_OP; // set MSb to indicate write
	regFileID &= DWM_SINGLE_BYTE_HEADER;// reset bit 6 to indicate single byte header

	HAL_GPIO_WritePin(DWM_CS_GPIO_Port, DWM_CS_PIN, GPIO_PIN_RESET);

	HAL_SPI_Transmit(spi_handle, &regFileID, 1, HAL_MAX_DELAY);
	HAL_Delay(5); //wait 5 us
	HAL_SPI_Transmit(spi_handle, data, dataLen, HAL_MAX_DELAY);

	HAL_GPIO_WritePin(DWM_CS_GPIO_Port, DWM_CS_Pin, GPIO_PIN_SET);
}


void dwm_readreg_single_byte_header(uint8_t regFileID, uint8_t* data, uint32_t dataLen){
	regFileID &= DWM_READ_OP & DWM_SINGLE_BYTE_HEADER;// reset bit 7 and 6 to indicate read operation and single byte header

	HAL_GPIO_WritePin(DWM_CS_GPIO_Port, DWM_CS_PIN, GPIO_PIN_RESET);

	HAL_SPI_Transmit(spi_handle, &regFileID, 1, HAL_MAX_DELAY);
	HAL_Delay(5); //wait 5 us
	HAL_SPI_Receive(spi_handle, data, dataLen, HAL_MAX_DELAY);

	HAL_GPIO_WritePin(DWM_CS_GPIO_Port, DWM_CS_Pin, GPIO_PIN_SET);
}

void dwm_writereg_double_byte_header(uint8_t regFileID, uint8_t subAddr, uint8_t* data, uint32_t dataLen){
	uint8_t header[2];
	header[0] = regFileID | DWM_WRITE_OP | DWM_SUBADDR1_PRESENT; // set MSb to indicate write and 6th bit to indicate sub address is present
	header[1] = subAddr & DWM_NO_EXTENDED_ADDR; //reset MSb to indicate there is no extended address


	HAL_GPIO_WritePin(DWM_CS_GPIO_Port, DWM_CS_PIN, GPIO_PIN_RESET);

	HAL_SPI_Transmit(spi_handle, &header[0], 2, HAL_MAX_DELAY);
	HAL_Delay(5); //wait 5 us
	HAL_SPI_Transmit(spi_handle, data, dataLen, HAL_MAX_DELAY);

	HAL_GPIO_WritePin(DWM_CS_GPIO_Port, DWM_CS_Pin, GPIO_PIN_SET);
}


void dwm_readreg_double_byte_header(uint8_t regFileID, uint8_t subAddr, uint8_t* data, uint32_t dataLen){
	uint8_t header[2];
	header[0] = (regFileID & DWM_READ_OP) | DWM_SUBADDR1_PRESENT; // reset MSb to indicate read and set 6th bit to indicate sub address is present
	header[1] = subAddr & DWM_NO_EXTENDED_ADDR; //reset MSb to indicate there is no extended address


	HAL_GPIO_WritePin(DWM_CS_GPIO_Port, DWM_CS_PIN, GPIO_PIN_RESET);

	HAL_SPI_Transmit(spi_handle, &header[0], 2, HAL_MAX_DELAY);
	HAL_Delay(5); //wait 5 us
	HAL_SPI_Receive(spi_handle, data, dataLen, HAL_MAX_DELAY);

	HAL_GPIO_WritePin(DWM_CS_GPIO_Port, DWM_CS_Pin, GPIO_PIN_SET);
}

void dwm_writereg_triple_byte_header(uint8_t regFileID, uint16_t subAddr, uint8_t* data, uint32_t dataLen){
	uint8_t header[3];
	header[0] = regFileID | DWM_WRITE_OP | DWM_SUBADDR1_PRESENT; // set MSb to indicate write and 6th bit to indicate sub address is present
	header[1] = (subAddr & 0x7F) | DWM_EXTENDED_ADDR_PRESENT; //Take lowest 7 bits Set MSb to indicate there is extended address
	header[2] = (subAddr >> 7) & 0xFF; //take higher 8 bits

	HAL_GPIO_WritePin(DWM_CS_GPIO_Port, DWM_CS_PIN, GPIO_PIN_RESET);

	HAL_SPI_Transmit(spi_handle, &header[0], 3, HAL_MAX_DELAY);
	HAL_Delay(5); //wait 5 us
	HAL_SPI_Transmit(spi_handle, data, dataLen, HAL_MAX_DELAY);

	HAL_GPIO_WritePin(DWM_CS_GPIO_Port, DWM_CS_Pin, GPIO_PIN_SET);
}

void dwm_readreg_triple_byte_header(uint8_t regFileID, uint16_t subAddr, uint8_t* data, uint32_t dataLen){
	uint8_t header[3];
	header[0] = (regFileID & DWM_READ_OP) | DWM_SUBADDR1_PRESENT; // reset MSb to indicate read and set 6th bit to indicate sub address is present
	header[1] = (subAddr & 0x7F) | DWM_EXTENDED_ADDR_PRESENT; //Take lowest 7 bits, Set MSb to indicate there is extended address
	header[2] = (subAddr >> 7) & 0xFF; //take higher 8 bits of 15 bit address

	HAL_GPIO_WritePin(DWM_CS_GPIO_Port, DWM_CS_PIN, GPIO_PIN_RESET);

	HAL_SPI_Transmit(spi_handle, &header[0], 3, HAL_MAX_DELAY);
	HAL_Delay(5); //wait 5 us
	HAL_SPI_Receive(spi_handle, data, dataLen, HAL_MAX_DELAY);

	HAL_GPIO_WritePin(DWM_CS_GPIO_Port, DWM_CS_Pin, GPIO_PIN_SET);
}

