/*
 * @file    SPI.h
 * @brief SPI
 * Project:  Firefly PIC18 Multiboard
 *   Supports Acorn API v1.1
 * Author:  Michael L Anderson
 * Company: Black Oak Engineering
 * Copyright 2026 - All Rights Reserved
 * Created: 19 Jun 26
 * Hardware: v1 PCBA, PIC18F26Q43T-I/SS, internal oscillator, SYSCLK = 16 MHz 
 * License: BOE Proprietary
 */

#ifndef SPI_H
#define SPI_H

void spi1Init(void);
void spi1Transfer(const void * txBuffer, void * rxBuffer, size_t bufferSize);
void spi1BufferExchange(void * bufferData, size_t bufferSize);
void spi1BufferWrite(void * bufferData, size_t bufferSize);
void spi1BufferRead(void * bufferData, size_t bufferSize);
uint8_t spi1ByteExchange(uint8_t byteData);
void spi1ByteWrite(uint8_t byteData);
uint8_t spi1ByteRead(void);
bool spi1IsRxReady(void);
bool spi1IsTxReady(void);

#endif // SPI_H