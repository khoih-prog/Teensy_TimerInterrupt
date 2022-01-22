# Teensy_TimerInterrupt Library

[![arduino-library-badge](https://www.ardu-badge.com/badge/Teensy_TimerInterrupt.svg?)](https://www.ardu-badge.com/Teensy_TimerInterrupt)
[![GitHub release](https://img.shields.io/github/release/khoih-prog/Teensy_TimerInterrupt.svg)](https://github.com/khoih-prog/Teensy_TimerInterrupt/releases)
[![GitHub](https://img.shields.io/github/license/mashape/apistatus.svg)](https://github.com/khoih-prog/Teensy_TimerInterrupt/blob/master/LICENSE)
[![contributions welcome](https://img.shields.io/badge/contributions-welcome-brightgreen.svg?style=flat)](#Contributing)
[![GitHub issues](https://img.shields.io/github/issues/khoih-prog/Teensy_TimerInterrupt.svg)](http://github.com/khoih-prog/Teensy_TimerInterrupt/issues)

---
---

## Table of Contents

* [Changelog](#changelog)
  * [Releases v1.3.0](#releases-v130)
  * [Releases v1.2.0](#releases-v120)
  * [Releases v1.1.1](#releases-v111)
  * [Releases v1.0.1](#releases-v101)
  * [Releases v1.0.0](#releases-v100)

---
---

## Changelog

### Releases v1.3.0

1. Fix `multiple-definitions` linker error. Drop `src_cpp` and `src_h` directories
2. Add example [multiFileProject](examples/multiFileProject) to demo for multiple-file project.
3. Optimize library code by using `reference-passing` instead of `value-passing`
4. Update all examples

### Releases v1.2.0

1. Add better debug feature.
2. Optimize code and examples to reduce RAM usage
3. Add Table of Contents

### Releases v1.1.1

1. Add example [**Change_Interval**](examples/Change_Interval) and [**ISR_16_Timers_Array_Complex**](examples/ISR_16_Timers_Array_Complex)
2. Bump up version to sync with other TimerInterrupt Libraries. Modify Version String.

### Releases v1.0.1

1. Add complicated example [ISR_16_Timers_Array](examples/ISR_16_Timers_Array) utilizing and demonstrating the full usage of 16 independent ISR Timers.

### Releases v1.0.0

1. Permit up to 16 super-long-time, super-accurate ISR-based timers to avoid being blocked
2. Using cpp code besides Impl.h code to use if Multiple-Definition linker error.

