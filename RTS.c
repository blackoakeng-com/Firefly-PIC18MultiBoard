/*
 * @file    RTS.h
 * @brief Real Time Scheduler
 * Project:  Firefly PIC18 Multiboard
 *   Supports Acorn API v1.1
 * Author:  Michael L Anderson
 * Company: Black Oak Engineering
 * Copyright 2026 - All Rights Reserved
 * Created: 19 Jun 26
 * Hardware: v1 PCBA, PIC18F26Q43T-I/SS, internal oscillator, SYSCLK = 16 MHz 
 * License: BOE Proprietary
 */

#include <stdio.h>
#include "Firefly.h"
#include "RTS.h"
//#include "Meas.h"   

struct rtsStruct rts;

// Called by exec loop.  Deprecated.  Use rtsClock() semaphor to schedule.
void rtsScheduler(void)
{
//    static int16_t msecLast;
//    int16_t msecLapsed;
//    
//    if (rts.ms >= msecLast) msecLapsed = rts.ms - msecLast;    
//    else msecLapsed = 1000 - msecLast + rts.ms;
//    msecLast = rts.ms;
//    if (msecLapsed == 0) return;  
//    if (rts.serialRepPeriod_ms != PeriodDisabled)          // Periodic serial post if enabled
//    {
//        if ((rts.serialRepCtdn_ms - msecLapsed) > 0) rts.serialRepCtdn_ms -= msecLapsed;                      
//        else 
//        {
//            // LATCbits.LATC0 = 1;  // DEB
//            ak09940AMeasMagn();     // 450 us in ver 0.7
//            // LATCbits.LATC0 = 0;  // DEB
//            printf("%02u.%03u,%3.02f,%3.02f,%3.02f\r\n", rts.sec, rts.ms, meas.x_uT, meas.y_uT, meas.z_uT);                      
//            rts.serialRepCtdn_ms = rts.serialRepPeriod_ms;       // Reseed            
//        }
//    }
}

void rtsInit(void)
{
    rts.serialRepPeriod_ms = 1000;   
}

void delay(uint16_t d)
{
    for (uint16_t e = 0; e < d; e++);   
}

void msDelay(uint16_t ms)   // Blocking
{
    uint16_t msStart, msEnd;       
    msStart = rts.ms;
    if (ms > 999) ms = 999;
    if ((msStart + ms) > 999) msEnd = msStart + ms - 1000; 
    else msEnd = msStart + ms;
    while (rts.ms != msEnd);
}

void rtsClock(void)
{     
    if (rts.serialRepCtdn_ms++ >= rts.serialRepPeriod_ms)
    {
        rts.measSemaphor = true;
        rts.serialRepCtdn_ms = 0;
    }
    else
    {
        if (rts.free_ms < 59999) rts.free_ms++;
        else rts.free_ms = 0;
    }
    if (rts.ms++ >= 999)
    {        
        rts.ms = 0;
        if (rts.sec++ >= 59)
        {
            rts.sec = 0;
            if (rts.min++ >= 59)
            {
                rts.min = 0;
                if (rts.hr++ >= 23)
                {
                    rts.hr = 0;
                }
            }
        }
    }       
}
