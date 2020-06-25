/*
 * dwm_spi.h
 *
 *  Created on: Jun 12, 2020
 *      Author: aswin
 */

#ifndef INC_DWM_SPI_H_
#define INC_DWM_SPI_H_

#include "main.h"


//IO
#define DWM_CS_PIN DWM_CS_Pin
#define DWM_CS_Port DWM_CS_GPIO_Port

#define DWM_Reset_PIN DWM_Reset_Pin
#define DWM_Reset_Port DWM_Reset_GPIO_Port

//Commands & Headers
#define DWM_WRITE_OP 0x80
#define DWM_SUBADDR1_PRESENT 0x40
#define DWM_SINGLE_BYTE_HEADER 0xBF

#define DWM_READ_OP 0x7F
#define DWM_NO_EXTENDED_ADDR 0x7F
#define DWM_EXTENDED_ADDR_PRESENT 0x80


void attach_SPI_Handle(SPI_HandleTypeDef* hspi);
void dwm_writereg_single_byte_header(uint8_t regFileID, uint8_t* data, uint32_t dataLen);
void dwm_readreg_single_byte_header(uint8_t regFileID, uint8_t* data, uint32_t dataLen);
void dwm_writereg_double_byte_header(uint8_t regFileID, uint8_t subAddr, uint8_t* data, uint32_t dataLen);
void dwm_readreg_double_byte_header(uint8_t regFileID, uint8_t subAddr, uint8_t* data, uint32_t dataLen);
void dwm_writereg_triple_byte_header(uint8_t regFileID, uint16_t subAddr, uint8_t* data, uint32_t dataLen);
void dwm_readreg_triple_byte_header(uint8_t regFileID, uint16_t subAddr, uint8_t* data, uint32_t dataLen);

#endif /* INC_DWM_SPI_H_ */
