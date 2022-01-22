# Teensy_TimerInterrupt Library

[![arduino-library-badge](https://www.ardu-badge.com/badge/Teensy_TimerInterrupt.svg?)](https://www.ardu-badge.com/Teensy_TimerInterrupt)
[![GitHub release](https://img.shields.io/github/release/khoih-prog/Teensy_TimerInterrupt.svg)](https://github.com/khoih-prog/Teensy_TimerInterrupt/releases)
[![GitHub](https://img.shields.io/github/license/mashape/apistatus.svg)](https://github.com/khoih-prog/Teensy_TimerInterrupt/blob/master/LICENSE)
[![contributions welcome](https://img.shields.io/badge/contributions-welcome-brightgreen.svg?style=flat)](#Contributing)
[![GitHub issues](https://img.shields.io/github/issues/khoih-prog/Teensy_TimerInterrupt.svg)](http://github.com/khoih-prog/Teensy_TimerInterrupt/issues)

---
---

## Table of Contents

* [Important Change from v1.3.0](#Important-Change-from-v130)
* [Why do we need this Teensy_TimerInterrupt library](#why-do-we-need-this-teensy_timerinterrupt-library)
  * [Features](#features)
  * [Why using ISR-based Hardware Timer Interrupt is better](#why-using-isr-based-hardware-timer-interrupt-is-better)
  * [Currently supported Boards](#currently-supported-boards)
  * [Important Notes about ISR](#important-notes-about-isr)
* [Changelog](changelog.md) 
* [Prerequisites](#prerequisites)
* [Installation](#installation)
  * [Use Arduino Library Manager](#use-arduino-library-manager)
  * [Manual Install](#manual-install)
  * [VS Code & PlatformIO](#vs-code--platformio)
* [Packages' Patches](#packages-patches)
  * [1. For Teensy boards](#1-for-teensy-boards)
* [Libraries' Patches](#libraries-patches)
  * [1. For application requiring 2K+ HTML page](#1-for-application-requiring-2k-html-page)
  * [2. For Ethernet library](#2-for-ethernet-library)
  * [3. For EthernetLarge library](#3-for-ethernetlarge-library)
  * [4. For Etherne2 library](#4-for-ethernet2-library)
  * [5. For Ethernet3 library](#5-for-ethernet3-library)
  * [6. For UIPEthernet library](#6-for-uipethernet-library)
* [HOWTO Fix `Multiple Definitions` Linker Error](#howto-fix-multiple-definitions-linker-error)
* [New from v1.0.0](#new-from-v100)
* [Usage](#usage)
  * [1. Using only Hardware Timer directly](#1-using-only-hardware-timer-directly)
    * [1.1 Init Hardware Timer](#11-init-hardware-timer)
    * [1.2 Set Hardware Timer Interval and attach Timer Interrupt Handler function](#12-set-hardware-timer-interval-and-attach-timer-interrupt-handler-function)
    * [1.3 Set Hardware Timer Frequency and attach Timer Interrupt Handler function](#13-set-hardware-timer-frequency-and-attach-timer-interrupt-handler-function)
  * [2. Using 16 ISR_based Timers from 1 Hardware Timer](#2-using-16-isr_based-timers-from-1-hardware-timer)
    * [2.1 Important Note](#21-important-note)
    * [2.2 Init Hardware Timer and ISR-based Timer](#22-init-hardware-timer-and-isr-based-timer)
    * [2.3 Set Hardware Timer Interval and attach Timer Interrupt Handler functions](#23-set-hardware-timer-interval-and-attach-timer-interrupt-handler-functions)
* [Examples](#examples)
  * [  1. Argument_None](examples/Argument_None)
  * [  2. ISR_16_Timers_Array](examples/ISR_16_Timers_Array)
  * [  3. ISR_RPM_Measure](examples/ISR_RPM_Measure)
  * [  4. ISR_Timer_Complex](examples/ISR_Timer_Complex)
  * [  5. RPM_Measure](examples/RPM_Measure)
  * [  6. SwitchDebounce](examples/SwitchDebounce)
  * [  7. TimerInterruptTest](examples/TimerInterruptTest)
  * [  8. TimerInterruptLEDDemo](examples/TimerInterruptLEDDemo)
  * [  9. **Change_Interval**](examples/Change_Interval)
  * [ 10. **ISR_16_Timers_Array_Complex**](examples/ISR_16_Timers_Array_Complex)
  * [ 11. **multiFileProject**](examples/multiFileProject) **New**
* [Example ISR_16_Timers_Array_Complex](#example-isr_16_timers_array_complex)
* [Debug Terminal Output Samples](#debug-terminal-output-samples)
  * [1. ISR_16_Timers_Array on Teensy 4.1](#1-isr_16_timers_array-on-teensy-41)
  * [2. TimerInterruptTest on Teensy 4.1](#2-timerinterrupttest-on-teensy-41)
  * [3. Argument_None on Teensy 4.1](#3-argument_none-on-teensy-41)
  * [4. Change_Interval on Teensy 4.1](#4-change_interval-on-teensy-41)
  * [5. ISR_16_Timers_Array_Complex on Teensy 4.1](#5-isr_16_timers_array_complex-on-teensy-41)
* [Debug](#debug)
* [Troubleshooting](#troubleshooting)
* [Issues](#issues)
* [TO DO](#to-do)
* [DONE](#done)
* [Contributions and Thanks](#contributions-and-thanks)
* [Contributing](#contributing)
* [License](#license)
* [Copyright](#copyright)

---
---

### Important Change from v1.3.0

Please have a look at [HOWTO Fix `Multiple Definitions` Linker Error](#howto-fix-multiple-definitions-linker-error)

### Why do we need this [Teensy_TimerInterrupt library](https://github.com/khoih-prog/Teensy_TimerInterrupt)

### Features

This library enables you to use Interrupt from Hardware Timers on an Teensy-based board, such as Teensy 4.x, 3.x, LC, Teensy++ 2.0 or Teensy 2.0. 

As **Hardware Timers are rare, and very precious assets** of any board, this library now enable you to use up to **16 ISR-based Timers, while consuming only 1 Hardware Timer**. Timers' interval is very long (**ulong millisecs**). 

You'd certainly experienced that if using other Hardware Timer Libraries, such as [**TimerOne**](https://github.com/PaulStoffregen/TimerOne) or [**TimerThree**](https://github.com/PaulStoffregen/TimerThree), the interval is short, in milliseconds range.

For example, Teensy 4.x, with **super-high clock frequency of 600MHz and Timer1 and Timer3 clock of 150MHz, the maximum interval / frequency is only 55922.3467 us / 17.881939 Hz**. This [**Teensy_TimerInterrupt library**](https://github.com/khoih-prog/Teensy_TimerInterrupt) will provide you up to 16 super-long (**ulong millisecs**) ISR Timers for each used Timer1 or Timer3.

For Teensy 4.x, this library will be expanded to use other available hardware timers, such as **FTM, GPT, QUAD, PIT**, in addition to current **Timer1 and Timer3**.

Now with these new **16 ISR-based timers**, the maximum interval is **practically unlimited** (limited only by unsigned long miliseconds) while **the accuracy is nearly perfect** compared to software timers. 

The most important feature is they're ISR-based timers. Therefore, their executions are **not blocked by bad-behaving functions / tasks**. This important feature is absolutely necessary for mission-critical tasks. 

The [**ISR_Timer_Complex**](examples/ISR_Timer_Complex) example will demonstrate the nearly perfect accuracy compared to software timers by printing the actual elapsed millisecs of each type of timers.

Being ISR-based timers, their executions are not blocked by bad-behaving functions / tasks, such as connecting to WiFi, Internet and Blynk services. You can also have many `(up to 16)` timers to use.

This non-being-blocked important feature is absolutely necessary for mission-critical tasks.

You'll see blynkTimer Software is blocked while system is connecting to WiFi / Internet / Blynk, as well as by blocking task 
in loop(), using delay() function as an example. The elapsed time then is very unaccurate

### Why using ISR-based Hardware Timer Interrupt is better

Imagine you have a system with a **mission-critical** function, measuring water level and control the sump pump or doing something much more important. You normally use a software timer to poll, or even place the function in loop(). But what if another function is **blocking** the loop() or setup().

So your function **might not be executed, and the result would be disastrous.**

You'd prefer to have your function called, no matter what happening with other functions (busy loop, bug, etc.).

The correct choice is to use a Hardware Timer with **Interrupt** to call your function.

These hardware timers, using interrupt, still work even if other functions are blocking. Moreover, they are much more **precise** (certainly depending on clock frequency accuracy) than other software timers using millis() or micros(). That's necessary if you need to measure some data requiring better accuracy.

Functions using normal software timers, relying on loop() and calling millis(), won't work if the loop() or setup() is blocked by certain operation. For example, certain function is blocking while it's connecting to WiFi or some services.

The catch is **your function is now part of an ISR (Interrupt Service Routine), and must be lean / mean, and follow certain rules.** More to read on:

[**HOWTO Attach Interrupt**](https://www.arduino.cc/reference/en/language/functions/external-interrupts/attachinterrupt/)

---

### Currently supported Boards

1. **Teensy boards** such as :

  - **Teensy 4.1, 4.0, Teensy MicroMod**
  - **Teensy 3.6, 3.5, 3.2/3.1, 3.0**
  - **Teensy LC**
  - **Teensy++ 2.0 and Teensy 2.0**

---

### Important Notes about ISR

1. Inside the attached function, **delay() won’t work and the value returned by millis() will not increment.** Serial data received while in the function may be lost. You should declare as **volatile any variables that you modify within the attached function.**

2. Typically global variables are used to pass data between an ISR and the main program. To make sure variables shared between an ISR and the main program are updated correctly, declare them as volatile.

---
---


## Prerequisites

 1. [`Arduino IDE 1.8.19+` for Arduino](https://github.com/arduino/Arduino). [![GitHub release](https://img.shields.io/github/release/arduino/Arduino.svg)](https://github.com/arduino/Arduino/releases/latest)
 2. [`Teensy Core 1.56+`](https://www.pjrc.com/teensy/td_download.html) for Teensy.
 3. To use with certain example, 
   - [`SimpleTimer library`](https://github.com/jfturcot/SimpleTimer) for [ISR_16_Timers_Array example](examples/ISR_16_Timers_Array).

---
---

## Installation

### Use Arduino Library Manager

The best and easiest way is to use `Arduino Library Manager`. Search for [**Teensy_TimerInterrupt**](https://github.com/khoih-prog/Teensy_TimerInterrupt), then select / install the latest version.
You can also use this link [![arduino-library-badge](https://www.ardu-badge.com/badge/Teensy_TimerInterrupt.svg?)](https://www.ardu-badge.com/Teensy_TimerInterrupt) for more detailed instructions.

### Manual Install

Another way to install is to:

1. Navigate to [**Teensy_TimerInterrupt**](https://github.com/khoih-prog/Teensy_TimerInterrupt) page.
2. Download the latest release `Teensy_TimerInterrupt-master.zip`.
3. Extract the zip file to `Teensy_TimerInterrupt-master` directory 
4. Copy whole `Teensy_TimerInterrupt-master` folder to Arduino libraries' directory such as `~/Arduino/libraries/`.

### VS Code & PlatformIO

1. Install [VS Code](https://code.visualstudio.com/)
2. Install [PlatformIO](https://platformio.org/platformio-ide)
3. Install [**Teensy_TimerInterrupt** library](https://platformio.org/lib/show/11426/Teensy_TimerInterrupt) or [**Teensy_TimerInterrupt** library](https://platformio.org/lib/show/11404/Teensy_TimerInterrupt) by using [Library Manager](https://platformio.org/lib/show/11426/Teensy_TimerInterrupt/installation). Search for **Teensy_TimerInterrupt** in [Platform.io Author's Libraries](https://platformio.org/lib/search?query=author:%22Khoi%20Hoang%22)
4. Use included [platformio.ini](platformio/platformio.ini) file from examples to ensure that all dependent libraries will installed automatically. Please visit documentation for the other options and examples at [Project Configuration File](https://docs.platformio.org/page/projectconf.html)

---
---

### Packages' Patches

#### 1. For Teensy boards
 
 **To be able to compile and run on Teensy boards**, you have to copy the file [Teensy boards.txt](Packages_Patches/hardware/teensy/avr/boards.txt) into Teensy hardware directory (./arduino-1.8.19/hardware/teensy/avr/boards.txt). 

Supposing the Arduino version is 1.8.19. These files must be copied into the directory:

- `./arduino-1.8.19/hardware/teensy/avr/boards.txt`
- `./arduino-1.8.19/hardware/teensy/avr/cores/teensy/Stream.h`
- `./arduino-1.8.19/hardware/teensy/avr/cores/teensy3/Stream.h`
- `./arduino-1.8.19/hardware/teensy/avr/cores/teensy4/Stream.h`

Whenever a new version is installed, remember to copy this file into the new version directory. For example, new version is x.yy.zz
This file must be copied into the directory:

- `./arduino-x.yy.zz/hardware/teensy/avr/boards.txt`
- `./arduino-x.yy.zz/hardware/teensy/avr/cores/teensy/Stream.h`
- `./arduino-x.yy.zz/hardware/teensy/avr/cores/teensy3/Stream.h`
- `./arduino-x.yy.zz/hardware/teensy/avr/cores/teensy4/Stream.h`

---
---

### Libraries' Patches

#### Notes: These patches are totally optional and necessary only when you use the related Ethernet library and get certain error or issues.

#### 1. For application requiring 2K+ HTML page

If your application requires 2K+ HTML page, the current [`Ethernet library`](https://www.arduino.cc/en/Reference/Ethernet) must be modified if you are using W5200/W5500 Ethernet shields. W5100 is not supported for 2K+ buffer. If you use boards requiring different CS/SS pin for W5x00 Ethernet shield, for example ESP32, ESP8266, nRF52, etc., you also have to modify the following libraries to be able to specify the CS/SS pin correctly.

#### 2. For Ethernet library

To fix [`Ethernet library`](https://www.arduino.cc/en/Reference/Ethernet), just copy these following files into the [`Ethernet library`](https://www.arduino.cc/en/Reference/Ethernet) directory to overwrite the old files:
- [Ethernet.h](LibraryPatches/Ethernet/src/Ethernet.h)
- [Ethernet.cpp](LibraryPatches/Ethernet/src/Ethernet.cpp)
- [EthernetServer.cpp](LibraryPatches/Ethernet/src/EthernetServer.cpp)
- [w5100.h](LibraryPatches/Ethernet/src/utility/w5100.h)
- [w5100.cpp](LibraryPatches/Ethernet/src/utility/w5100.cpp)

#### 3. For EthernetLarge library

To fix [`EthernetLarge library`](https://github.com/OPEnSLab-OSU/EthernetLarge), just copy these following files into the [`EthernetLarge library`](https://github.com/OPEnSLab-OSU/EthernetLarge) directory to overwrite the old files:
- [EthernetLarge.h](LibraryPatches/EthernetLarge/src/EthernetLarge.h)
- [EthernetLarge.cpp](LibraryPatches/EthernetLarge/src/EthernetLarge.cpp)
- [EthernetServer.cpp](LibraryPatches/EthernetLarge/src/EthernetServer.cpp)
- [w5100.h](LibraryPatches/EthernetLarge/src/utility/w5100.h)
- [w5100.cpp](LibraryPatches/EthernetLarge/src/utility/w5100.cpp)


#### 4. For Ethernet2 library

To fix [`Ethernet2 library`](https://github.com/khoih-prog/Ethernet2), just copy these following files into the [`Ethernet2 library`](https://github.com/khoih-prog/Ethernet2) directory to overwrite the old files:

- [Ethernet2.h](LibraryPatches/Ethernet2/src/Ethernet2.h)
- [Ethernet2.cpp](LibraryPatches/Ethernet2/src/Ethernet2.cpp)

To add UDP Multicast support, necessary for the [**UPnP_Generic library**](https://github.com/khoih-prog/UPnP_Generic):

- [EthernetUdp2.h](LibraryPatches/Ethernet2/src/EthernetUdp2.h)
- [EthernetUdp2.cpp](LibraryPatches/Ethernet2/src/EthernetUdp2.cpp)

#### 5. For Ethernet3 library

5. To fix [`Ethernet3 library`](https://github.com/sstaub/Ethernet3), just copy these following files into the [`Ethernet3 library`](https://github.com/sstaub/Ethernet3) directory to overwrite the old files:
- [Ethernet3.h](LibraryPatches/Ethernet3/src/Ethernet3.h)
- [Ethernet3.cpp](LibraryPatches/Ethernet3/src/Ethernet3.cpp)

#### 6. For UIPEthernet library

***To be able to compile and run on nRF52 boards with ENC28J60 using UIPEthernet library***, you have to copy these following files into the UIPEthernet `utility` directory to overwrite the old files:

- For [UIPEthernet v2.0.8](https://github.com/UIPEthernet/UIPEthernet)

  - [UIPEthernet.h](LibraryPatches/UIPEthernet/UIPEthernet.h)
  - [UIPEthernet.cpp](LibraryPatches/UIPEthernet/UIPEthernet.cpp)
  - [Enc28J60Network.h](LibraryPatches/UIPEthernet/utility/Enc28J60Network.h)
  - [Enc28J60Network.cpp](LibraryPatches/UIPEthernet/utility/Enc28J60Network.cpp)

- For [UIPEthernet v2.0.9](https://github.com/UIPEthernet/UIPEthernet)

  - [UIPEthernet.h](LibraryPatches/UIPEthernet-2.0.9/UIPEthernet.h)
  - [UIPEthernet.cpp](LibraryPatches/UIPEthernet-2.0.9/UIPEthernet.cpp)
  - [Enc28J60Network.h](LibraryPatches/UIPEthernet-2.0.9/utility/Enc28J60Network.h)
  - [Enc28J60Network.cpp](LibraryPatches/UIPEthernet-2.0.9/utility/Enc28J60Network.cpp)


---
---


### HOWTO Fix `Multiple Definitions` Linker Error

The current library implementation, using `xyz-Impl.h` instead of standard `xyz.cpp`, possibly creates certain `Multiple Definitions` Linker error in certain use cases.

You can include `.hpp`

```
// Can be included as many times as necessary, without `Multiple Definitions` Linker Error
#include "TeensyTimerInterrupt.hpp"     //https://github.com/khoih-prog/Teensy_TimerInterrupt

// Can be included as many times as necessary, without `Multiple Definitions` Linker Error
#include "Teensy_ISR_Timer.hpp"         //https://github.com/khoih-prog/Teensy_TimerInterrupt
```

in many files. But be sure to use the following `.h` files **in just 1 `.h`, `.cpp` or `.ino` file**, which must **not be included in any other file**, to avoid `Multiple Definitions` Linker Error

```
// To be included only in main(), .ino with setup() to avoid `Multiple Definitions` Linker Error
#include "TeensyTimerInterrupt.h"       //https://github.com/khoih-prog/Teensy_TimerInterrupt

// To be included only in main(), .ino with setup() to avoid `Multiple Definitions` Linker Error
#include "Teensy_ISR_Timer.h"           //https://github.com/khoih-prog/Teensy_TimerInterrupt
```

Check the new [**multiFileProject** example](examples/multiFileProject) for a `HOWTO` demo.


---
---


## New from v1.0.0

You'd certainly experienced that if using other Hardware Timer Libraries, such as [**TimerOne**](https://github.com/PaulStoffregen/TimerOne) or [**TimerThree**](https://github.com/PaulStoffregen/TimerThree), the interval is short, in milliseconds range.

For example, Teensy 4.x, with **super-high clock frequency of 600MHz and Timer1 and Timer3 clock of 150MHz, the maximum interval / frequency is only 55922.3467 us / 17.881939 Hz**. This [**Teensy_TimerInterrupt library**](https://github.com/khoih-prog/Teensy_TimerInterrupt) will provide you up to 16 super-long (**ulong millisecs**) ISR Timers for each used Timer1 or Timer3.

Now with these new `16 ISR-based timers` (while consuming only **1 hardware timer**), the maximum interval is practically unlimited (limited only by unsigned long miliseconds). The accuracy is nearly perfect compared to software timers. The most important feature is they're ISR-based timers Therefore, their executions are not blocked by bad-behaving functions / tasks.
This important feature is absolutely necessary for mission-critical tasks. 

The `ISR_Timer_Complex` example will demonstrate the nearly perfect accuracy compared to software timers by printing the actual elapsed millisecs of each type of timers.

Being ISR-based timers, their executions are not blocked by bad-behaving functions / tasks, such as connecting to WiFi, Internet and Blynk services. You can also have many `(up to 16)` timers to use.
This non-being-blocked important feature is absolutely necessary for mission-critical tasks. 
You'll see blynkTimer Software is blocked while system is connecting to WiFi / Internet / Blynk, as well as by blocking task 
in loop(), using delay() function as an example. The elapsed time then is very unaccurate

---
---

## Usage

Before using any Timer, you have to make sure the Timer has not been used by any other purpose.

### 1. Using only Hardware Timer directly

### 1.1 Init Hardware Timer

```
// You can select Teensy Hardware Timer  from TEENSY_TIMER_1 or TEENSY_TIMER_3

// Init Teensy timer TEENSY_TIMER_1
TeensyTimer ITimer0(TEENSY_TIMER_1);
```

### 1.2 Set Hardware Timer Interval and attach Timer Interrupt Handler function

Use one of these functions with **interval in unsigned long milliseconds**

```
// Interval (in microseconds)
// For Teensy 4.0/4.1, F_BUS_ACTUAL = 150 MHz => max interval/period is only 55922 us (~17.9 Hz)
bool setInterval(unsigned long interval, timerCallback callback);

// interval (in microseconds) and duration (in milliseconds). Duration = 0 or not specified => run indefinitely
// No params and duration now. To be added in the future by adding similar functions here or to NRF52-hal-timer.c
bool attachInterruptInterval(unsigned long interval, timerCallback callback);
```

as follows

```
void TimerHandler0(void)
{
  // Doing something here inside ISR
}

// For Teensy 4.0/4.1, F_BUS_ACTUAL = 150 MHz => max period is only 55922 us (~17.9 Hz)
#define TIMER0_INTERVAL_MS        50L

void setup()
{
  ....
  
  // Interval in microsecs
  if (ITimer0.attachInterruptInterval(TIMER0_INTERVAL_MS * 1000, TimerHandler0))
  {
    Serial.print(F("Starting ITimer0 OK, millis() = ")); Serial.println(millis());
  }
  else
    Serial.println(F("Can't set ITimer0. Select another freq. or timer));
}  
```

### 1.3 Set Hardware Timer Frequency and attach Timer Interrupt Handler function

Use one of these functions with **frequency in float Hz**

```
// frequency (in hertz) and duration (in milliseconds). Duration = 0 or not specified => run indefinitely
// No params and duration now. To be added in the future by adding similar functions here or to NRF52-hal-timer.c
bool setFrequency(float frequency, timerCallback callback);

// frequency (in hertz).
bool attachInterrupt(float frequency, timerCallback callback);
```

as follows

```
void TimerHandler0(void)
{
  // Doing something here inside ISR
}

// For Teensy 4.0/4.1, F_BUS_ACTUAL = 150 MHz => max period is only 55922 us (~17.9 Hz)
#define TIMER0_FREQ_HZ        5555.555

void setup()
{
  ....
  
  // Interval in microsecs
  if (ITimer0.attachInterrupt(TIMER0_FREQ_HZ, TimerHandler0))
  {
    Serial.print(F("Starting ITimer0 OK, millis() = ")); Serial.println(millis());
  }
  else
    Serial.println(F("Can't set ITimer0. Select another freq. or timer));
}  
```

### 2. Using 16 ISR_based Timers from 1 Hardware Timer

### 2.1 Important Note

The 16 ISR_based Timers, designed for long timer intervals, only support using **unsigned long millisec intervals**. If you have to use much higher frequency or sub-millisecond interval, you have to use the Hardware Timers directly as in [1.3 Set Hardware Timer Frequency and attach Timer Interrupt Handler function](#13-set-hardware-timer-frequency-and-attach-timer-interrupt-handler-function)

### 2.2 Init Hardware Timer and ISR-based Timer

```
// You can select Teensy Hardware Timer  from TEENSY_TIMER_1 or TEENSY_TIMER_3

// Init Teensy timer TEENSY_TIMER_1
TeensyTimer ITimer(TEENSY_TIMER_1);

// Init Teensy_ISR_Timer
// Each Teensy_ISR_Timer can service 16 different ISR-based timers
Teensy_ISR_Timer ISR_Timer;
```

### 2.3 Set Hardware Timer Interval and attach Timer Interrupt Handler functions

```
void TimerHandler(void)
{
  ISR_Timer.run();
}

#define HW_TIMER_INTERVAL_MS          50L

#define TIMER_INTERVAL_2S             2000L
#define TIMER_INTERVAL_5S             5000L
#define TIMER_INTERVAL_11S            11000L
#define TIMER_INTERVAL_101S           101000L

// In Teensy, avoid doing something fancy in ISR, for example complex Serial.print with String() argument
// The pure simple Serial.prints here are just for demonstration and testing. Must be eliminate in working environment
// Or you can get this run-time error / crash
void doingSomething2s()
{
  // Doing something here inside ISR every 2 seconds
}
  
void doingSomething5s()
{
  // Doing something here inside ISR every 5 seconds
}

void doingSomething11s()
{
  // Doing something here inside ISR  every 11 seconds
}

void doingSomething101s()
{
  // Doing something here inside ISR every 101 seconds
}

void setup()
{
  ....
  
  // Interval in microsecs
  if (ITimer0.attachInterruptInterval(TIMER0_INTERVAL_MS * 1000, TimerHandler0))
  {
    Serial.print(F("Starting ITimer0 OK, millis() = ")); Serial.println(millis());
  }
  else
    Serial.println(F("Can't set ITimer0. Select another freq. or timer));

  // Just to demonstrate, don't use too many ISR Timers if not absolutely necessary
  // You can use up to 16 timer for each ISR_Timer
  ISR_Timer.setInterval(TIMER_INTERVAL_2S, doingSomething2s);
  ISR_Timer.setInterval(TIMER_INTERVAL_5S, doingSomething5s);
  ISR_Timer.setInterval(TIMER_INTERVAL_11S, doingSomething11s);
  ISR_Timer.setInterval(TIMER_INTERVAL_101S, doingSomething101s);
}  
```


---
---

### Examples: 

 1. [Argument_None](examples/Argument_None)
 2. [ISR_16_Timers_Array](examples/ISR_16_Timers_Array)
 3. [ISR_RPM_Measure](examples/ISR_RPM_Measure)
 4. [ISR_Timer_Complex](examples/ISR_Timer_Complex)
 5. [RPM_Measure](examples/RPM_Measure)
 6. [SwitchDebounce](examples/SwitchDebounce)
 7. [TimerInterruptTest](examples/TimerInterruptTest)
 8. [TimerInterruptLEDDemo](examples/TimerInterruptLEDDemo)
 9. [**Change_Interval**](examples/Change_Interval). New
10. [**ISR_16_Timers_Array_Complex**](examples/ISR_16_Timers_Array_Complex).
11. [**multiFileProject**](examples/multiFileProject). **New**

---
---

### Example [ISR_16_Timers_Array_Complex](examples/ISR_16_Timers_Array_Complex)

```
#if !( defined(CORE_TEENSY) || defined(TEENSYDUINO) )
  #error This code is designed to run on Teensy platform! Please check your Tools->Board setting.
#endif

// These define's must be placed at the beginning before #include "TeensyTimerInterrupt.h"
// _TIMERINTERRUPT_LOGLEVEL_ from 0 to 4
// Don't define _TIMERINTERRUPT_LOGLEVEL_ > 0. Only for special ISR debugging only. Can hang the system.
// Don't define TIMER_INTERRUPT_DEBUG > 2. Only for special ISR debugging only. Can hang the system.
#define TIMER_INTERRUPT_DEBUG         0
#define _TIMERINTERRUPT_LOGLEVEL_     3

// To be included only in main(), .ino with setup() to avoid `Multiple Definitions` Linker Error
#include "TeensyTimerInterrupt.h"

// To be included only in main(), .ino with setup() to avoid `Multiple Definitions` Linker Error
#include "Teensy_ISR_Timer.h"

#include <SimpleTimer.h>              // https://github.com/jfturcot/SimpleTimer

#ifndef LED_BUILTIN
  #define LED_BUILTIN       13
#endif

#ifndef LED_BLUE
  #define LED_BLUE          2
#endif

#ifndef LED_RED
  #define LED_RED           3
#endif

#define HW_TIMER_INTERVAL_US      10000L

volatile uint32_t startMillis = 0;

// You can select Teensy Hardware Timer  from TEENSY_TIMER_1 or TEENSY_TIMER_3

// Init Teensy timer TEENSY_TIMER_1
TeensyTimer ITimer(TEENSY_TIMER_1);

// Init Teensy_ISR_Timer
// Each Teensy_ISR_Timer can service 16 different ISR-based timers
Teensy_ISR_Timer ISR_Timer;

#define LED_TOGGLE_INTERVAL_MS        2000L

void TimerHandler()
{
  static bool toggle  = false;
  static int timeRun  = 0;

  ISR_Timer.run();

  // Toggle LED every LED_TOGGLE_INTERVAL_MS = 2000ms = 2s
  if (++timeRun == ((LED_TOGGLE_INTERVAL_MS * 1000) / HW_TIMER_INTERVAL_US) )
  {
    timeRun = 0;

    //timer interrupt toggles pin LED_BUILTIN
    digitalWrite(LED_BUILTIN, toggle);
    toggle = !toggle;
  }
}

/////////////////////////////////////////////////

#define NUMBER_ISR_TIMERS         16

typedef void (*irqCallback)  ();

/////////////////////////////////////////////////

#define USE_COMPLEX_STRUCT      true

#if USE_COMPLEX_STRUCT

  typedef struct 
  {
    irqCallback   irqCallbackFunc;
    uint32_t      TimerInterval;
    unsigned long deltaMillis;
    unsigned long previousMillis;
  } ISRTimerData;
  
  // In NRF52, avoid doing something fancy in ISR, for example Serial.print()
  // The pure simple Serial.prints here are just for demonstration and testing. Must be eliminate in working environment
  // Or you can get this run-time error / crash
  
  void doingSomething(int index);

#else

  volatile unsigned long deltaMillis    [NUMBER_ISR_TIMERS] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
  volatile unsigned long previousMillis [NUMBER_ISR_TIMERS] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
  
  // You can assign any interval for any timer here, in milliseconds
  uint32_t TimerInterval[NUMBER_ISR_TIMERS] =
  {
    5000L,  10000L,  15000L,  20000L,  25000L,  30000L,  35000L,  40000L,
    45000L, 50000L,  55000L,  60000L,  65000L,  70000L,  75000L,  80000L
  };
  
  void doingSomething(int index)
  {
    unsigned long currentMillis  = millis();
    
    deltaMillis[index]    = currentMillis - previousMillis[index];
    previousMillis[index] = currentMillis;
  }

#endif

////////////////////////////////////
// Shared
////////////////////////////////////

void doingSomething0()
{
  doingSomething(0);
}

void doingSomething1()
{
  doingSomething(1);
}

void doingSomething2()
{
  doingSomething(2);
}

void doingSomething3()
{
  doingSomething(3);
}

void doingSomething4()
{
  doingSomething(4);
}

void doingSomething5()
{
  doingSomething(5);
}

void doingSomething6()
{
  doingSomething(6);
}

void doingSomething7()
{
  doingSomething(7);
}

void doingSomething8()
{
  doingSomething(8);
}

void doingSomething9()
{
  doingSomething(9);
}

void doingSomething10()
{
  doingSomething(10);
}

void doingSomething11()
{
  doingSomething(11);
}

void doingSomething12()
{
  doingSomething(12);
}

void doingSomething13()
{
  doingSomething(13);
}

void doingSomething14()
{
  doingSomething(14);
}

void doingSomething15()
{
  doingSomething(15);
}

#if USE_COMPLEX_STRUCT

  ISRTimerData curISRTimerData[NUMBER_ISR_TIMERS] =
  {
    //irqCallbackFunc, TimerInterval, deltaMillis, previousMillis
    { doingSomething0,    5000L, 0, 0 },
    { doingSomething1,   10000L, 0, 0 },
    { doingSomething2,   15000L, 0, 0 },
    { doingSomething3,   20000L, 0, 0 },
    { doingSomething4,   25000L, 0, 0 },
    { doingSomething5,   30000L, 0, 0 },
    { doingSomething6,   35000L, 0, 0 },
    { doingSomething7,   40000L, 0, 0 },
    { doingSomething8,   45000L, 0, 0 },
    { doingSomething9,   50000L, 0, 0 },
    { doingSomething10,  55000L, 0, 0 },
    { doingSomething11,  60000L, 0, 0 },
    { doingSomething12,  65000L, 0, 0 },
    { doingSomething13,  70000L, 0, 0 },
    { doingSomething14,  75000L, 0, 0 },
    { doingSomething15,  80000L, 0, 0 }
  };
  
  void doingSomething(int index)
  {
    unsigned long currentMillis  = millis();
    
    curISRTimerData[index].deltaMillis    = currentMillis - curISRTimerData[index].previousMillis;
    curISRTimerData[index].previousMillis = currentMillis;
  }

#else

  irqCallback irqCallbackFunc[NUMBER_ISR_TIMERS] =
  {
    doingSomething0,  doingSomething1,  doingSomething2,  doingSomething3,
    doingSomething4,  doingSomething5,  doingSomething6,  doingSomething7,
    doingSomething8,  doingSomething9,  doingSomething10, doingSomething11,
    doingSomething12, doingSomething13, doingSomething14, doingSomething15
  };

#endif
///////////////////////////////////////////

#define SIMPLE_TIMER_MS        2000L

// Init SimpleTimer
SimpleTimer simpleTimer;

// Here is software Timer, you can do somewhat fancy stuffs without many issues.
// But always avoid
// 1. Long delay() it just doing nothing and pain-without-gain wasting CPU power.Plan and design your code / strategy ahead
// 2. Very long "do", "while", "for" loops without predetermined exit time.
void simpleTimerDoingSomething2s()
{
  static unsigned long previousMillis = startMillis;

  unsigned long currMillis = millis();

  Serial.print(F("SimpleTimer : "));Serial.print(SIMPLE_TIMER_MS / 1000);
  Serial.print(F(", ms : ")); Serial.print(currMillis);
  Serial.print(F(", Dms : ")); Serial.println(currMillis - previousMillis);

  for (uint16_t i = 0; i < NUMBER_ISR_TIMERS; i++)
  {
#if USE_COMPLEX_STRUCT    
    Serial.print(F("Timer : ")); Serial.print(i);
    Serial.print(F(", programmed : ")); Serial.print(curISRTimerData[i].TimerInterval);
    Serial.print(F(", actual : ")); Serial.println(curISRTimerData[i].deltaMillis);
#else
    Serial.print(F("Timer : ")); Serial.print(i);
    Serial.print(F(", programmed : ")); Serial.print(TimerInterval[i]);
    Serial.print(F(", actual : ")); Serial.println(deltaMillis[i]);
#endif    
  }

  previousMillis = currMillis;
}

void setup()
{
  pinMode(LED_BUILTIN, OUTPUT);

  Serial.begin(115200);
  while (!Serial);

  delay(100);
  
  Serial.print(F("\nStarting ISR_16_Timers_Array_Complex on ")); Serial.println(BOARD_NAME);
  Serial.println(TEENSY_TIMER_INTERRUPT_VERSION);
  Serial.print(F("CPU Frequency = ")); Serial.print(F_CPU / 1000000); Serial.println(F(" MHz"));

  // Interval in microsecs
  if (ITimer.attachInterruptInterval(HW_TIMER_INTERVAL_US, TimerHandler))
  {
    startMillis = millis();
    Serial.print(F("Starting ITimer0 OK, millis() = ")); Serial.println(startMillis);
  }
  else
    Serial.println(F("Can't set ITimer0. Select another freq. or timer"));

  // Just to demonstrate, don't use too many ISR Timers if not absolutely necessary
  // You can use up to 16 timer for each Teensy_ISR_Timer
  for (uint16_t i = 0; i < NUMBER_ISR_TIMERS; i++)
  {
#if USE_COMPLEX_STRUCT
    curISRTimerData[i].previousMillis = startMillis;
    ISR_Timer.setInterval(curISRTimerData[i].TimerInterval, curISRTimerData[i].irqCallbackFunc);
#else
    previousMillis[i] = startMillis;
    ISR_Timer.setInterval(TimerInterval[i], irqCallbackFunc[i]);
#endif    
  }

  // You need this timer for non-critical tasks. Avoid abusing ISR if not absolutely necessary.
  simpleTimer.setInterval(SIMPLE_TIMER_MS, simpleTimerDoingSomething2s);
}

#define BLOCKING_TIME_MS      10000L

void loop()
{
  // This unadvised blocking task is used to demonstrate the blocking effects onto the execution and accuracy to Software timer
  // You see the time elapse of ISR_Timer still accurate, whereas very unaccurate for Software Timer
  // The time elapse for 2000ms software timer now becomes 3000ms (BLOCKING_TIME_MS)
  // While that of ISR_Timer is still prefect.
  delay(BLOCKING_TIME_MS);

  // You need this Software timer for non-critical tasks. Avoid abusing ISR if not absolutely necessary
  // You don't need to and never call ISR_Timer.run() here in the loop(). It's already handled by ISR timer.
  simpleTimer.run();
}
```
---
---

### Debug Terminal Output Samples

### 1. ISR_16_Timers_Array on Teensy 4.1

The following is the sample terminal output when running example [ISR_16_Timers_Array](examples/ISR_16_Timers_Array) on **Teensy 4.1** to demonstrate the accuracy of ISR Hardware Timer, **especially when system is very busy or blocked**. The 16 independent ISR timers are **programmed to be activated repetitively after certain intervals, is activated exactly after that programmed interval !!!**

While software timer, **programmed for 2s, is activated after 10.000s in loop()!!!**.

In this example, 16 independent ISR Timers are used and utilized just one Hardware Timer. The Timer Intervals and Function Pointers are stored in arrays to facilitate the code modification.

```
Starting TimerInterruptTest on Teensy 4.1
TeensyTimerInterrupt v1.3.0
CPU Frequency = 600 MHz
[TISR] TEENSY_TIMER_1: F_BUS_ACTUAL (MHz) = 150
[TISR] Request interval = 1000, actual interval (us) = 999
[TISR] Prescale = 2, _timerCount = 18750
Starting  ITimer OK, millis() = 1241
1s: Delta ms = 1000, ms = 2241
1s: Delta ms = 1000, ms = 3241
2s: Delta ms = 2000, ms = 3241
1s: Delta ms = 1000, ms = 4241
3s: Delta ms = 3000, ms = 4241
1s: Delta ms = 1000, ms = 5241
2s: Delta ms = 2000, ms = 5241
4s: Delta ms = 4000, ms = 5241
1s: Delta ms = 1000, ms = 6241
5s: Delta ms = 5000, ms = 6241
1s: Delta ms = 1000, ms = 7241
2s: Delta ms = 2000, ms = 7241
3s: Delta ms = 3000, ms = 7241
6s: Delta ms = 6000, ms = 7241
1s: Delta ms = 1000, ms = 8241
7s: Delta ms = 7000, ms = 8241
1s: Delta ms = 1000, ms = 9241
2s: Delta ms = 2000, ms = 9241
4s: Delta ms = 4000, ms = 9241
8s: Delta ms = 8000, ms = 9241
1s: Delta ms = 1000, ms = 10241
3s: Delta ms = 3000, ms = 10241
9s: Delta ms = 9000, ms = 10241
simpleTimerDoingSomething2s: Delta programmed ms = 2000, actual = 10000
1s: Delta ms = 1000, ms = 11241
2s: Delta ms = 2000, ms = 11241
5s: Delta ms = 5000, ms = 11241
10s: Delta ms = 10000, ms = 11241
1s: Delta ms = 1000, ms = 12241
11s: Delta ms = 11000, ms = 12241
1s: Delta ms = 1000, ms = 13241
2s: Delta ms = 2000, ms = 13241
3s: Delta ms = 3000, ms = 13241
4s: Delta ms = 4000, ms = 13241
6s: Delta ms = 6000, ms = 13241
12s: Delta ms = 12000, ms = 13241
1s: Delta ms = 1000, ms = 14241
13s: Delta ms = 13000, ms = 14241
1s: Delta ms = 1000, ms = 15241
2s: Delta ms = 2000, ms = 15241
7s: Delta ms = 7000, ms = 15241
14s: Delta ms = 14000, ms = 15241
1s: Delta ms = 1000, ms = 16241
3s: Delta ms = 3000, ms = 16241
5s: Delta ms = 5000, ms = 16241
15s: Delta ms = 15000, ms = 16241
1s: Delta ms = 1000, ms = 17241
2s: Delta ms = 2000, ms = 17241
4s: Delta ms = 4000, ms = 17241
8s: Delta ms = 8000, ms = 17241
16s: Delta ms = 16000, ms = 17241
1s: Delta ms = 1000, ms = 18241
1s: Delta ms = 1000, ms = 19241
2s: Delta ms = 2000, ms = 19241
3s: Delta ms = 3000, ms = 19241
6s: Delta ms = 6000, ms = 19241
9s: Delta ms = 9000, ms = 19241
1s: Delta ms = 1000, ms = 20241
simpleTimerDoingSomething2s: Delta programmed ms = 2000, actual = 10000
```

---

### 2. TimerInterruptTest on Teensy 4.1

The following is the sample terminal output when running example [**TimerInterruptTest**](examples/TimerInterruptTest) on **Teensy 4.1** to demonstrate how to start/stop and the accuracy of Hardware Timers.

```
Starting TimerInterruptTest on Teensy 4.1
TeensyTimerInterrupt v1.3.0
CPU Frequency = 600 MHz
[TISR] TEENSY_TIMER_1: F_BUS_ACTUAL (MHz) = 150
[TISR] Request interval = 50000, actual interval (us) = 49998
[TISR] Prescale = 7, _timerCount = 29296
Starting  ITimer0 OK, millis() = 1128
Stop ITimer0, millis() = 5001
TeensyTimerInterrupt:stopTimer TEENSY_TIMER_1
Start ITimer0, millis() = 10002
TeensyTimerInterrupt:stopTimer TEENSY_TIMER_1
TeensyTimerInterrupt:resumeTimer TEENSY_TIMER_1
Stop ITimer0, millis() = 15003
TeensyTimerInterrupt:stopTimer TEENSY_TIMER_1
Start ITimer0, millis() = 20004
TeensyTimerInterrupt:stopTimer TEENSY_TIMER_1
TeensyTimerInterrupt:resumeTimer TEENSY_TIMER_1
Stop ITimer0, millis() = 25005
TeensyTimerInterrupt:stopTimer TEENSY_TIMER_1
Start ITimer0, millis() = 30006
TeensyTimerInterrupt:stopTimer TEENSY_TIMER_1
TeensyTimerInterrupt:resumeTimer TEENSY_TIMER_1
Stop ITimer0, millis() = 35007
TeensyTimerInterrupt:stopTimer TEENSY_TIMER_1
Start ITimer0, millis() = 40008
TeensyTimerInterrupt:stopTimer TEENSY_TIMER_1
TeensyTimerInterrupt:resumeTimer TEENSY_TIMER_1
Stop ITimer0, millis() = 45009
TeensyTimerInterrupt:stopTimer TEENSY_TIMER_1
Start ITimer0, millis() = 50010
TeensyTimerInterrupt:stopTimer TEENSY_TIMER_1
TeensyTimerInterrupt:resumeTimer TEENSY_TIMER_1
Stop ITimer0, millis() = 55011
TeensyTimerInterrupt:stopTimer TEENSY_TIMER_1

```

---

### 3. Argument_None on Teensy 4.1

The following is the sample terminal output when running example [**Argument_None**](examples/Argument_None) on **Teensy4.1** to demonstrate the accuracy of Hardware Timers.

```
Starting Argument_None on Teensy 4.1
TeensyTimerInterrupt v1.3.0
CPU Frequency = 600 MHz
[TISR] TEENSY_TIMER_1: F_BUS_ACTUAL (MHz) = 150
[TISR] Request interval = 50000, actual interval (us) = 49998
[TISR] Prescale = 7, _timerCount = 29296
Starting  ITimer0 OK, millis() = 629
ITimer0: millis() = 629, delta = 629
ITimer0: millis() = 679, delta = 50
ITimer0: millis() = 729, delta = 50
ITimer0: millis() = 779, delta = 50
ITimer0: millis() = 829, delta = 50
ITimer0: millis() = 879, delta = 50
ITimer0: millis() = 929, delta = 50
ITimer0: millis() = 979, delta = 50
ITimer0: millis() = 1029, delta = 50
ITimer0: millis() = 1079, delta = 50
ITimer0: millis() = 1129, delta = 50
ITimer0: millis() = 1179, delta = 50
ITimer0: millis() = 1229, delta = 50
ITimer0: millis() = 1279, delta = 50
ITimer0: millis() = 1329, delta = 50
ITimer0: millis() = 1379, delta = 50
ITimer0: millis() = 1429, delta = 50
ITimer0: millis() = 1479, delta = 50
ITimer0: millis() = 1529, delta = 50
ITimer0: millis() = 1579, delta = 50
ITimer0: millis() = 1629, delta = 50
ITimer0: millis() = 1679, delta = 50
ITimer0: millis() = 1729, delta = 50
ITimer0: millis() = 1779, delta = 50
ITimer0: millis() = 1829, delta = 50
ITimer0: millis() = 1879, delta = 50
ITimer0: millis() = 1929, delta = 50
ITimer0: millis() = 1979, delta = 50
ITimer0: millis() = 2029, delta = 50
ITimer0: millis() = 2079, delta = 50
ITimer0: millis() = 2129, delta = 50
ITimer0: millis() = 2179, delta = 50

```

---

### 4. Change_Interval on Teensy 4.1

The following is the sample terminal output when running example [Change_Interval](examples/Change_Interval) on **Teensy4.1** to demonstrate how to change Timer Interval on-the-fly

```
Starting Change_Interval on Teensy 4.1
TeensyTimerInterrupt v1.3.0
CPU Frequency = 600 MHz
[TISR] TEENSY_TIMER_1: F_BUS_ACTUAL (MHz) = 150
[TISR] Request interval = 10000, actual interval (us) = 9999
[TISR] Prescale = 5, _timerCount = 23437
Starting  ITimer OK, millis() = 1432
Time = 10001, TimerCount = 857
Time = 20002, TimerCount = 1857
Changing Interval, Timer = 20
Time = 30003, TimerCount = 2358
Time = 40004, TimerCount = 2858
Changing Interval, Timer = 10
Time = 50005, TimerCount = 3857
Time = 60006, TimerCount = 4857
Changing Interval, Timer = 20
Time = 70007, TimerCount = 5357
Time = 80008, TimerCount = 5857
Changing Interval, Timer = 10
Time = 90009, TimerCount = 6857
Time = 100010, TimerCount = 7857
Changing Interval, Timer = 20
```

---

### 5. ISR_16_Timers_Array_Complex on Teensy 4.1

The following is the sample terminal output when running new example [ISR_16_Timers_Array_Complex](examples/ISR_16_Timers_Array_Complex) on **Teensy 4.1** to demonstrate the accuracy of ISR Hardware Timer, **especially when system is very busy or blocked**. The 16 independent ISR timers are **programmed to be activated repetitively after certain intervals, is activated exactly after that programmed interval !!!**

While software timer, **programmed for 2s, is activated after 10.000s in loop()!!!**.

In this example, 16 independent ISR Timers are used, yet utilized just one Hardware Timer. The Timer Intervals and Function Pointers are stored in arrays to facilitate the code modification.

```
Starting ISR_16_Timers_Array_Complex on Teensy 4.1
TeensyTimerInterrupt v1.3.0
CPU Frequency = 600 MHz
[TISR] TEENSY_TIMER_1: F_BUS_ACTUAL (MHz) = 150
[TISR] Request interval = 10000, actual interval (us) = 9999
[TISR] Prescale = 5, _timerCount = 23437
Starting  ITimer OK, millis() = 1247
SimpleTimer : 2s, ms = 11247, Dms : 10000
Timer : 0, programmed : 5000, actual : 5000
Timer : 1, programmed : 10000, actual : 10000
Timer : 2, programmed : 15000, actual : 0
Timer : 3, programmed : 20000, actual : 0
Timer : 4, programmed : 25000, actual : 0
Timer : 5, programmed : 30000, actual : 0
Timer : 6, programmed : 35000, actual : 0
Timer : 7, programmed : 40000, actual : 0
Timer : 8, programmed : 45000, actual : 0
Timer : 9, programmed : 50000, actual : 0
Timer : 10, programmed : 55000, actual : 0
Timer : 11, programmed : 60000, actual : 0
Timer : 12, programmed : 65000, actual : 0
Timer : 13, programmed : 70000, actual : 0
Timer : 14, programmed : 75000, actual : 0
Timer : 15, programmed : 80000, actual : 0
SimpleTimer : 2s, ms = 21247, Dms : 10000
Timer : 0, programmed : 5000, actual : 5000
Timer : 1, programmed : 10000, actual : 10000
Timer : 2, programmed : 15000, actual : 15000
Timer : 3, programmed : 20000, actual : 20000
Timer : 4, programmed : 25000, actual : 0
Timer : 5, programmed : 30000, actual : 0
Timer : 6, programmed : 35000, actual : 0
Timer : 7, programmed : 40000, actual : 0
Timer : 8, programmed : 45000, actual : 0
Timer : 9, programmed : 50000, actual : 0
Timer : 10, programmed : 55000, actual : 0
Timer : 11, programmed : 60000, actual : 0
Timer : 12, programmed : 65000, actual : 0
Timer : 13, programmed : 70000, actual : 0
Timer : 14, programmed : 75000, actual : 0
Timer : 15, programmed : 80000, actual : 0
SimpleTimer : 2s, ms = 31247, Dms : 10000
Timer : 0, programmed : 5000, actual : 5000
Timer : 1, programmed : 10000, actual : 10000
Timer : 2, programmed : 15000, actual : 15000
Timer : 3, programmed : 20000, actual : 20000
Timer : 4, programmed : 25000, actual : 25000
Timer : 5, programmed : 30000, actual : 30000
Timer : 6, programmed : 35000, actual : 0
Timer : 7, programmed : 40000, actual : 0
Timer : 8, programmed : 45000, actual : 0
Timer : 9, programmed : 50000, actual : 0
Timer : 10, programmed : 55000, actual : 0
Timer : 11, programmed : 60000, actual : 0
Timer : 12, programmed : 65000, actual : 0
Timer : 13, programmed : 70000, actual : 0
Timer : 14, programmed : 75000, actual : 0
Timer : 15, programmed : 80000, actual : 0
SimpleTimer : 2s, ms = 41247, Dms : 10000
Timer : 0, programmed : 5000, actual : 5000
Timer : 1, programmed : 10000, actual : 10000
Timer : 2, programmed : 15000, actual : 15000
Timer : 3, programmed : 20000, actual : 20000
Timer : 4, programmed : 25000, actual : 25000
Timer : 5, programmed : 30000, actual : 30000
Timer : 6, programmed : 35000, actual : 35000
Timer : 7, programmed : 40000, actual : 40000
Timer : 8, programmed : 45000, actual : 0
Timer : 9, programmed : 50000, actual : 0
Timer : 10, programmed : 55000, actual : 0
Timer : 11, programmed : 60000, actual : 0
Timer : 12, programmed : 65000, actual : 0
Timer : 13, programmed : 70000, actual : 0
Timer : 14, programmed : 75000, actual : 0
Timer : 15, programmed : 80000, actual : 0
SimpleTimer : 2s, ms = 51247, Dms : 10000
Timer : 0, programmed : 5000, actual : 5000
Timer : 1, programmed : 10000, actual : 10000
Timer : 2, programmed : 15000, actual : 15000
Timer : 3, programmed : 20000, actual : 20000
Timer : 4, programmed : 25000, actual : 25000
Timer : 5, programmed : 30000, actual : 30000
Timer : 6, programmed : 35000, actual : 35000
Timer : 7, programmed : 40000, actual : 40000
Timer : 8, programmed : 45000, actual : 45000
Timer : 9, programmed : 50000, actual : 50000
Timer : 10, programmed : 55000, actual : 0
Timer : 11, programmed : 60000, actual : 0
Timer : 12, programmed : 65000, actual : 0
Timer : 13, programmed : 70000, actual : 0
Timer : 14, programmed : 75000, actual : 0
Timer : 15, programmed : 80000, actual : 0
SimpleTimer : 2s, ms = 61247, Dms : 10000
Timer : 0, programmed : 5000, actual : 5000
Timer : 1, programmed : 10000, actual : 10000
Timer : 2, programmed : 15000, actual : 15000
Timer : 3, programmed : 20000, actual : 20000
Timer : 4, programmed : 25000, actual : 25000
Timer : 5, programmed : 30000, actual : 30000
Timer : 6, programmed : 35000, actual : 35000
Timer : 7, programmed : 40000, actual : 40000
Timer : 8, programmed : 45000, actual : 45000
Timer : 9, programmed : 50000, actual : 50000
Timer : 10, programmed : 55000, actual : 55000
Timer : 11, programmed : 60000, actual : 60000
Timer : 12, programmed : 65000, actual : 0
Timer : 13, programmed : 70000, actual : 0
Timer : 14, programmed : 75000, actual : 0
Timer : 15, programmed : 80000, actual : 0
SimpleTimer : 2s, ms = 71247, Dms : 10000
Timer : 0, programmed : 5000, actual : 5000
Timer : 1, programmed : 10000, actual : 10000
Timer : 2, programmed : 15000, actual : 15000
Timer : 3, programmed : 20000, actual : 20000
Timer : 4, programmed : 25000, actual : 25000
Timer : 5, programmed : 30000, actual : 30000
Timer : 6, programmed : 35000, actual : 35000
Timer : 7, programmed : 40000, actual : 40000
Timer : 8, programmed : 45000, actual : 45000
Timer : 9, programmed : 50000, actual : 50000
Timer : 10, programmed : 55000, actual : 55000
Timer : 11, programmed : 60000, actual : 60000
Timer : 12, programmed : 65000, actual : 65000
Timer : 13, programmed : 70000, actual : 70000
Timer : 14, programmed : 75000, actual : 0
Timer : 15, programmed : 80000, actual : 0
SimpleTimer : 2s, ms = 81247, Dms : 10000
Timer : 0, programmed : 5000, actual : 5000
Timer : 1, programmed : 10000, actual : 10000
Timer : 2, programmed : 15000, actual : 15000
Timer : 3, programmed : 20000, actual : 20000
Timer : 4, programmed : 25000, actual : 25000
Timer : 5, programmed : 30000, actual : 30000
Timer : 6, programmed : 35000, actual : 35000
Timer : 7, programmed : 40000, actual : 40000
Timer : 8, programmed : 45000, actual : 45000
Timer : 9, programmed : 50000, actual : 50000
Timer : 10, programmed : 55000, actual : 55000
Timer : 11, programmed : 60000, actual : 60000
Timer : 12, programmed : 65000, actual : 65000
Timer : 13, programmed : 70000, actual : 70000
Timer : 14, programmed : 75000, actual : 75000
Timer : 15, programmed : 80000, actual : 80000
```
---
---

### Debug

Debug is enabled by default on Serial.

You can also change the debugging level (_TIMERINTERRUPT_LOGLEVEL_) from 0 to 4

```cpp
// These define's must be placed at the beginning before #include "TeensyTimerInterrupt.h"
// _TIMERINTERRUPT_LOGLEVEL_ from 0 to 4
// Don't define _TIMERINTERRUPT_LOGLEVEL_ > 0. Only for special ISR debugging only. Can hang the system.
#define TIMER_INTERRUPT_DEBUG         0
#define _TIMERINTERRUPT_LOGLEVEL_     0
```

---

### Troubleshooting

If you get compilation errors, more often than not, you may need to install a newer version of the core for Arduino boards.

Sometimes, the library will only work if you update the board core to the latest version because I am using newly added functions.

---
---


### Issues

Submit issues to: [Teensy_TimerInterrupt issues](https://github.com/khoih-prog/Teensy_TimerInter/issues)

---

## TO DO

1. Search for bug and improvement.
2. Similar features for more sophisticated Teensy 4.x Timers (**FTM, GPT, QUAD, PIT**)

---

## DONE

1. Basic hardware timers for Teensy, using Timer1 and Timer3.
2. More hardware-initiated software-enabled timers
3. Longer time interval
4. Similar features for remaining Arduino boards such as AVR, ESP32, ESP8266, STM32, SAM-DUE, SAMD21/SAMD51, mbed-nRF52, nRF52, etc.
5. Add Table of Contents
6. Fix `multiple-definitions` linker error
7. Optimize library code by using `reference-passing` instead of `value-passing`

---
---

### Contributions and Thanks

Many thanks for everyone for bug reporting, new feature suggesting, testing and contributing to the development of this library.


---

## Contributing

If you want to contribute to this project:
- Report bugs and errors
- Ask for enhancements
- Create issues and pull requests
- Tell other people about this library

---

### License

- The library is licensed under [MIT](https://github.com/khoih-prog/Teensy_TimerInterrupt/blob/master/LICENSE)

---

## Copyright

Copyright 2020- Khoi Hoang


