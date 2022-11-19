/****************************************************************************************************************************
  TeensyTimerInterrupt.h
  For Teensy boards
  Written by Khoi Hoang

  Built by Khoi Hoang https://github.com/khoih-prog/Teensy_TimerInterrupt
  Licensed under MIT license

  Now even you use all these new 16 ISR-based timers,with their maximum interval practically unlimited (limited only by
  unsigned long miliseconds), you just consume only one Teensy timer and avoid conflicting with other cores' tasks.
  The accuracy is nearly perfect compared to software timers. The most important feature is they're ISR-based timers
  Therefore, their executions are not blocked by bad-behaving functions / tasks.
  This important feature is absolutely necessary for mission-critical tasks.

  Based on SimpleTimer - A timer library for Arduino.
  Author: mromani@ottotecnica.com
  Copyright (c) 2010 OTTOTECNICA Italy

  Based on BlynkTimer.h
  Author: Volodymyr Shymanskyy

  Version: 1.3.0

  Version Modified By   Date      Comments
  ------- -----------  ---------- -----------
  1.0.0   K Hoang      04/11/2020 Initial coding
  1.0.1   K Hoang      06/11/2020 Add complicated example ISR_16_Timers_Array using all 16 independent ISR Timers.
  1.1.1   K.Hoang      06/12/2020 Add complex examples. Bump up version to sync with other TimerInterrupt Libraries
  1.2.0   K.Hoang      11/01/2021 Add better debug feature. Optimize code and examples to reduce RAM usage
  1.3.0   K.Hoang      21/01/2022 Fix `multiple-definitions` linker error. Fix bug
*****************************************************************************************************************************/

#pragma once

#ifndef TEENSYTIMERINTERRUPT_H
#define TEENSYTIMERINTERRUPT_H

#if ( defined(__arm__) && defined(TEENSYDUINO) && defined(__IMXRT1062__) )

// Nothing here yet

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
// For Teensy 3.x and LC
#elif defined(__arm__) && defined(TEENSYDUINO) && (defined(KINETISK) || defined(KINETISL))

void ftm1_isr()
{
  uint32_t sc = FTM1_SC;

#ifdef KINETISL

  if (sc & 0x80)
    FTM1_SC = sc;

#else

  if (sc & 0x80)
    FTM1_SC = sc & 0x7F;

#endif

  (*(TeensyTimers[TEENSY_TIMER_1]->getCallback()))();
}

void ftm2_isr()
{
  uint32_t sc = FTM2_SC;

#ifdef KINETISL

  if (sc & 0x80)
    FTM2_SC = sc;

#else

  if (sc & 0x80)
    FTM2_SC = sc & 0x7F;

#endif

  (*(TeensyTimers[TEENSY_TIMER_3]->getCallback()))();
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
// For Teensy 2.0 and Teensy++ 2.0

#elif ( defined(ARDUINO_ARCH_AVR) || defined(__AVR__) )

ISR(TIMER1_OVF_vect)
{
  (*(TeensyTimers[TEENSY_TIMER_1]->getCallback()))();
}

ISR(TIMER3_OVF_vect)
{
  (*(TeensyTimers[TEENSY_TIMER_3]->getCallback()))();
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

#else

#error Not support board

#endif


////////////////////////////////////////////////////////////////////////////////

#endif    // TEENSYTIMERINTERRUPT_H
