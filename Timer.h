/*
 * @file    Timer.h
 * @brief tmr1 functions
 * Project:  Firefly PIC18 Multiboard
 *   Supports Acorn API v1.1
 * Author:  Michael L Anderson
 * Company: Black Oak Engineering
 * Copyright 2026 - All Rights Reserved
 * Created: 19 Jun 26
 * Hardware: v1 PCBA, PIC18F26Q43T-I/SS, internal oscillator, SYSCLK = 16 MHz 
 * License: BOE Proprietary
 */

#ifndef TIMER_H
#define TIMER_H

void timer1Init(void);
void timer1Start(void);
void timer1Stop(void);

#endif // TMR_H