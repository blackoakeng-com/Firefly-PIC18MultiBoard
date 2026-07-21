/*
 * @file    Clock.c
 * @brief Clock inits
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
#include "Clock.h"

void clockInit(void)
{
    // Set the CLOCK CONTROL module to the options selected in the user interface.
    OSCCON1 = (0 << _OSCCON1_NDIV_POSN)   // NDIV 1
        | (6 << _OSCCON1_NOSC_POSN);  // NOSC HFINTOSC
    OSCCON3 = (0 << _OSCCON3_SOSCPWR_POSN)   // SOSCPWR Low power
        | (0 << _OSCCON3_CSWHOLD_POSN);  // CSWHOLD may proceed
    OSCEN = (0 << _OSCEN_EXTOEN_POSN)   // EXTOEN disabled
        | (0 << _OSCEN_HFOEN_POSN)   // HFOEN disabled
        | (0 << _OSCEN_MFOEN_POSN)   // MFOEN disabled
        | (0 << _OSCEN_LFOEN_POSN)   // LFOEN disabled
        | (0 << _OSCEN_SOSCEN_POSN)   // SOSCEN disabled
        | (0 << _OSCEN_ADOEN_POSN)   // ADOEN disabled
        | (0 << _OSCEN_PLLEN_POSN);  // PLLEN disabled
    OSCFRQ = (8 << _OSCFRQ_HFFRQ_POSN);  // HFFRQ 64_MHz
    OSCTUNE = (0 << _OSCTUNE_TUN_POSN);  // TUN 0x0
    ACTCON = (0 << _ACTCON_ACTEN_POSN)   // ACTEN disabled
        | (0 << _ACTCON_ACTUD_POSN);  // ACTUD enabled

}