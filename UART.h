/*
 * @file    UART.h
 * @brief UART serial comms
 * Project:  Firefly PIC18 Multiboard
 *   Supports Acorn API v1.1
 * Author:  Michael L Anderson
 * Company: Black Oak Engineering
 * Copyright 2026 - All Rights Reserved
 * Created: 19 Jun 26
 * Hardware: v1 PCBA, PIC18F26Q43T-I/SS, internal oscillator, SYSCLK = 16 MHz 
 * License: BOE Proprietary
 */

#ifndef UART_H
#define UART_H

#include "Firefly.h"

void uart1Init(void);
void uart1Enable(void);
void uart1Disable(void);
void uart1TransmitEnable(void);
void uart1TransmitDisable(void);
void uart1ReceiveEnable(void);
void uart1ReceiveDisable(void);
void uart1SendBreakControlEnable(void);
void uart1SendBreakControlDisable(void);
void uart1AutoBaudSet(bool enable);
bool uart1AutoBaudQuery(void);
void uart1AutoBaudDetectCompleteReset(void);
bool uart1IsAutoBaudDetectOverflow(void);
void uart1AutoBaudDetectOverflowReset(void);
bool uart1IsRxReady(void);
bool uart1IsTxReady(void);
bool uart1IsTxDone(void);
uint8_t uart1Read(void);
void uart1Write(uint8_t txData);
int getch(void);   
void putch(char txData);


#ifdef __cplusplus  // Provide C++ Compatibility


    }

#endif

#endif  // UART1_H
