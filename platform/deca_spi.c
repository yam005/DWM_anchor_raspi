/*! ----------------------------------------------------------------------------
 * @file	deca_spi.c
 * @brief	SPI access functions
 *
 * @attention
 *
 * Copyright 2013 (c) DecaWave Ltd, Dublin, Ireland.
 *
 * All rights reserved.
 *
 * @author DecaWave
 */
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "deca_spi.h"
#include "deca_device_api.h"
#include <wiringPiSPI.h>


/*! ------------------------------------------------------------------------------------------------------------------
 * Function: writetospi()
 *
 * Low level abstract function to write to the SPI
 * Takes two separate byte buffers for write header and write data
 * returns 0 for success, or -1 for error
 */
//#pragma GCC optimize ("O3")
int writetospi(uint16 headerLength, const uint8 *headerBuffer, uint32 bodylength, const uint8 *bodyBuffer)
{
	uint32 len = headerLength + bodylength;
	uint8 *wr_buff = (uint8 *)malloc(len);
	strcpy((char *)wr_buff, (char *)headerBuffer);
	strcpy((char *)wr_buff, (char *)bodyBuffer);
	wiringPiSPIDataRW (SPI_CH0, wr_buff, len);
	free(wr_buff);
	
    return 0;
} // end writetospi()


/*! ------------------------------------------------------------------------------------------------------------------
 * Function: readfromspi()
 *
 * Low level abstract function to read from the SPI
 * Takes two separate byte buffers for write header and read data
 * returns the offset into read buffer where first byte of read data may be found,
 * or returns -1 if there was an error
 */
//#pragma GCC optimize ("O3")
int readfromspi(uint16 headerLength, const uint8 *headerBuffer, uint32 readlength, uint8 *readBuffer)
{
	uint32 len = headerLength + readlength;
	uint8 *wr_buff = (uint8 *)malloc(len);
	uint8 i;
	strcpy((char *)wr_buff, (char *)headerBuffer);
	wiringPiSPIDataRW (SPI_CH0, wr_buff, len);
	for (i = 0; i<readlength; i++) {
		readBuffer[i] = wr_buff[i + 1];
	}
	free(wr_buff);

    return 0;
} // end readfromspi()
