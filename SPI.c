/*
 * @file    SPI.c
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

#include "Firefly.h"
#include "SPI.h"

void spi1Init(void)
{
    SPI1CON0bits.EN = 0U;

	// Disable the interrupts
    PIE3bits.SPI1IE 	= 0U;
    PIE3bits.SPI1TXIE 	= 0U;
    PIE3bits.SPI1RXIE 	= 0U;
	
    SPI1CON1 = (0 << _SPI1CON1_SDOP_POSITION)	/* SDOP active high(0) */
			|(0 << _SPI1CON1_SDIP_POSITION)	/* SDIP active high(0) */
			|(0 << _SPI1CON1_SSP_POSITION)	/* SSP active high(0) */
			|(0 << _SPI1CON1_FST_POSITION)	/* FST disabled(0) */
			|(1 << _SPI1CON1_CKP_POSITION)	/* CKP Idle:Low, Active:High(0) Asahi */
			|(0 << _SPI1CON1_CKE_POSITION)	/* CKE Active to idle(1) */
			|(0 << _SPI1CON1_SMP_POSITION);	/* SMP Middle(0) */
    SPI1CON2 = (0 << _SPI1CON2_RXR_POSITION)	/* RXR data is not stored in the FIFO(0) */
			|(0 << _SPI1CON2_TXR_POSITION)	/* TXR not required for a transfer(0) */
			|(0 << _SPI1CON2_SSET_POSITION);	/* SSET disabled(0) */
    SPI1BAUD = 0x0F;    // (0 << _SPI1BAUD_BAUD_POSITION);	/* BAUD 0x0(0) */
    SPI1CLK = (0 << _SPI1CLK_CLKSEL_POSITION);	/* CLKSEL FOSC(0) */
	SPI1TCNTL = (0 << _SPI1TCNTL_TCNTL_POSITION);	/* TCNTL 0x0(0) */
	SPI1TCNTH = (0 << _SPI1TCNTH_TCNTH_POSITION);	/* TCNTH 0x0(0) */
	SPI1STATUS = (0 << _SPI1STATUS_CLRBF_POSITION)	/* CLRBF no action(0) */
			|(0 << _SPI1STATUS_RXRE_POSITION)	/* RXRE no error(0) */
			|(0 << _SPI1STATUS_TXWE_POSITION);	/* TXWE no error(0) */
	SPI1TWIDTH = (0 << _SPI1TWIDTH_TWIDTH_POSITION);	/* TWIDTH 0x0(0) */
	SPI1INTE = (0 << _SPI1INTE_TXUIE_POSITION)	/* TXUIE disabled(0) */
			|(0 << _SPI1INTE_RXOIE_POSITION)	/* RXOIE disabled(0) */
			|(0 << _SPI1INTE_EOSIE_POSITION)	/* EOSIE disabled(0) */
			|(0 << _SPI1INTE_SOSIE_POSITION)	/* SOSIE disabled(0) */
			|(0 << _SPI1INTE_TCZIE_POSITION)	/* TCZIE disabled(0) */
			|(0 << _SPI1INTE_SRMTIE_POSITION);	/* SRMTIE disabled(0) */
	SPI1INTF = (0 << _SPI1INTF_TXUIF_POSITION)	/* TXUIF disabled(0) */
			|(0 << _SPI1INTF_RXOIF_POSITION)	/* RXOIF disabled(0) */
			|(0 << _SPI1INTF_EOSIF_POSITION)	/* EOSIF disabled(0) */
			|(0 << _SPI1INTF_SOSIF_POSITION)	/* SOSIF disabled(0) */
			|(0 << _SPI1INTF_TCZIF_POSITION)	/* TCZIF disabled(0) */
			|(0 << _SPI1INTF_SRMTIF_POSITION);	/* SRMTIF disabled(0) */
    
	SPI1STATUSbits.CLRBF = 1U;
	
	SPI1CON0 = (0 << _SPI1CON0_BMODE_POSITION)	/* BMODE last byte(0) */
			|(1 << _SPI1CON0_MST_POSITION)	/* MST bus host(1) */
			|(0 << _SPI1CON0_LSBF_POSITION)	/* LSBF MSb first(0) */
			|(0 << _SPI1CON0_EN_POSITION);	/* EN disabled(0) */
    
    
    SPI1CON0bits.EN = 1U;
}

void spi1Transfer(const void * txBuffer, void * rxBuffer, size_t bufferSize)
{
	uint8_t* bufferReceive = rxBuffer;
	const uint8_t* bufferTransmit = (const uint8_t *)txBuffer;

    SPI1STATUSbits.CLRBF = 1U;

	// Clear the TCZIF interrupt flag
	SPI1INTFbits.TCZIF = 0U;

	// Set as full duplex mode for buffer exchange operation
    SPI1CON2 = (SPI1CON2 | _SPI1CON2_SPI1RXR_MASK) | _SPI1CON2_SPI1TXR_MASK;
	
	// Load the transfer count registers
	SPI1TCNTH = (uint8_t)(bufferSize>>8);
	SPI1TCNTL = (uint8_t)(bufferSize);	
	
	while(0U == SPI1INTFbits.TCZIF)
	{
		// Write input data to SPI transmit buffer register
		SPI1TXB = *bufferTransmit;
		while(!PIR3bits.SPI1RXIF)
		{
			// Wait on receive interrupt flag to be set
        };
		
		// Store received data  from receive buffer register 
		*bufferReceive = SPI1RXB;		
		bufferReceive++;
		bufferTransmit++;
	}
}
void spi1BufferExchange(void *bufferData, size_t bufferSize)
{
	uint8_t* bufferInput = bufferData;

    SPI1STATUSbits.CLRBF = 1U;

	// Clear the TCZIF interrupt flag
	SPI1INTFbits.TCZIF = 0U;

	// Set as full duplex mode for buffer exchange operation
    SPI1CON2 = (SPI1CON2 | _SPI1CON2_SPI1RXR_MASK) | _SPI1CON2_SPI1TXR_MASK;
	
	// Load the transfer count registers
	SPI1TCNTH = (uint8_t)(bufferSize>>8);
	SPI1TCNTL = (uint8_t)(bufferSize);	
	
	while(0U == SPI1INTFbits.TCZIF)
	{
		// Write input data to SPI transmit buffer register
		SPI1TXB = *bufferInput;
		while(!PIR3bits.SPI1RXIF)
		{
			// Wait on receive interrupt flag to be set
        };
		
		// Store received data  from receive buffer register 
		*bufferInput = SPI1RXB;		
		bufferInput++;
	}
}

void spi1BufferWrite(void *bufferData, size_t bufferSize)
{
	uint8_t* bufferInput = bufferData;

	SPI1STATUSbits.CLRBF = 1U;

	// Clear the TCZIF interrupt flag
	SPI1INTFbits.TCZIF = 0U;

	// Set as transmit only mode for buffer write operation
    SPI1CON2 = (SPI1CON2 & ~_SPI1CON2_SPI1RXR_MASK) | _SPI1CON2_SPI1TXR_MASK;
   
	// Load the transfer count registers
	SPI1TCNTH = (uint8_t)(bufferSize>>8);
	SPI1TCNTL = (uint8_t)(bufferSize);

	
	while(0U == SPI1INTFbits.TCZIF)
	{
		// Write input data to SPI transmit buffer register
		SPI1TXB = *bufferInput;
		while(!PIR3bits.SPI1TXIF)
		{
			// Wait on transmit interrupt flag to be set
        };
		bufferInput++;
	}
}

void spi1BufferRead(void *bufferData, size_t bufferSize)
{
	uint8_t* bufferInput = bufferData;

	SPI1STATUSbits.CLRBF = 1U;

	// Clear the TCZIF interrupt flag
	SPI1INTFbits.TCZIF = 0U;

	// Set as receive only mode for buffer read operation
    SPI1CON2 = (SPI1CON2 & ~_SPI1CON2_SPI1TXR_MASK) | _SPI1CON2_SPI1RXR_MASK;
	
	// Load the transfer count registers
	SPI1TCNTH = (uint8_t)(bufferSize>>8);
	SPI1TCNTL = (uint8_t)(bufferSize);

	while(0U == SPI1INTFbits.TCZIF)
	{
		while(!PIR3bits.SPI1RXIF)
		{
            // Wait on receive interrupt flag to be set
        };

		// Store received data  from receive buffer register 
		*bufferInput = SPI1RXB;
		bufferInput++;
	}
}

uint8_t spi1ByteExchange(uint8_t byteData)
{
	uint8_t returnValue = 0U;
    
	SPI1STATUSbits.CLRBF = 1U;

	// Set as full duplex mode
	SPI1CON2 = SPI1CON2 | _SPI1CON2_SPI1RXR_MASK | _SPI1CON2_SPI1TXR_MASK;
	
	// Load the transfer count registers
	SPI1TCNTH = 0U;
	SPI1TCNTL = 1U;

	SPI1TXB = byteData;
    
   // delay(10);
   // while(!SPI1STATUSbits.RXBF);    // Wait for the transfer to complete

//	while(!PIR3bits.SPI1RXIF)
//	{
//		// Wait on receive interrupt flag to be set
//    };
	returnValue = SPI1RXB;
	return returnValue;
}

void spi1ByteWrite(uint8_t byteData)
{	
	// Set as full duplex mode
	SPI1CON2 = SPI1CON2 | _SPI1CON2_SPI1RXR_MASK | _SPI1CON2_SPI1TXR_MASK;
	
	// Load the transfer count registers
	SPI1TCNTH = 0;
	SPI1TCNTL = 1;
	
	SPI1TXB = byteData;
}

uint8_t spi1ByteRead(void)
{
	uint8_t returnValue = 0x00U;
	
	// Set as full duplex mode
    SPI1CON2 = SPI1CON2 | _SPI1CON2_SPI1RXR_MASK | _SPI1CON2_SPI1TXR_MASK;
	
	// Store received data from receive buffer register 
	returnValue = SPI1RXB;	
	return returnValue;
}

bool spi1IsTxReady(void)
{
	bool returnValue = false;
	if(true == SPI1CON0bits.EN)
	{
		returnValue = PIR3bits.SPI1TXIF;
	}
	else 
	{
		returnValue = false;
	}
	return returnValue;
}

bool spi1IsRxReady(void)
{
	bool returnValue = false;
	
	if(true == SPI1CON0bits.EN)
    {
		returnValue = PIR3bits.SPI1RXIF;
    }
    else 
    {
        returnValue = false;
    }
    return returnValue;
}