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
 * TODO This needs pruning
 */

#include "Firefly.h"
#include "Timer.h"

static volatile uint16_t timer1ReloadVal;

void timer1Init(void)
{
    T1CONbits.TMR1ON = 0U;             // TMRON disabled

    T1GCON = (0 << _T1GCON_T1GGO_POSN)   // T1GGO done
        | (0 << _T1GCON_T1GSPM_POSN)   // T1GSPM disabled
        | (0 << _T1GCON_T1GTM_POSN)   // T1GTM disabled
        | (0 << _T1GCON_T1GPOL_POSN)   // T1GPOL low
        | (0 << _T1GCON_T1GE_POSN);  // T1GE disabled

    T1GATE = (0 << _T1GATE_GSS_POSN);  // GSS T1GPPS

    T1CLK = (3 << _T1CLK_CS_POSN);  // CS HFINTOSC

    TMR1H = 0x5;              // Period 1.00003ms; Timer clock 64000000 Hz;
    TMR1L = 0xFE;

    timer1ReloadVal=((uint16_t)TMR1H << 8) | TMR1L;

	PIR3bits.TMR1IF = 0U;
	PIE3bits.TMR1IE = 1U;
	PIR3bits.TMR1GIF = 0U;
	
    T1CON = (1 << _T1CON_TMR1ON_POSN)   // TMR1ON enabled
        | (0 << _T1CON_T1RD16_POSN)   // T1RD16 disabled
        | (1 << _T1CON_nT1SYNC_POSN)   // nT1SYNC do_not_synchronize
        | (0 << _T1CON_CKPS_POSN);  // CKPS 1:1
}

void timer1Start(void)
{   
    T1CONbits.TMR1ON = 1U;
}

void timer1Stop(void)
{ 
    T1CONbits.TMR1ON = 0U;
}

