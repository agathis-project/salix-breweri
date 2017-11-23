```
AP:      4
Title:   Root Module Microcontroller FW
Repo:    salix-breweri
State:   Idea
Type:    SW
License: CC BY-SA / GPL
Author:  md-agathisproject, jonsnow1357
```

# Root Module Microcontroller FW

## 1. Abstract

This AP describes the functions of the microcontroller (uC) and its firmware.
The hardware interfaces and main uC functionality are described in *AP-1 Root Module HW*.

## 2. Rationale

Without the uC, the root module is dead in the water. At a the bare minimum,
to support the microprocessor (uP) bring-up, the uC needs to turn on the power
converters and take the uP out of reset.

## 3. Build environment

### 3.1 Prerequisites

The current environment is assuming [AVR-gcc](https://gcc.gnu.org/wiki/avr-gcc) is installed on your computer.

### 3.2 Building

For the time being we try to support the following build tools:

* [make](https://www.gnu.org/software/make/)
* [scons](http://scons.org/)

In your local repository it should be just as simple as:

```
cd code
make all
```
or
```
cd code
scons
```
and after all is done you should find the *salix-breweri.hex* file ready to program.

## 4. Requirements

### 4.1. IO default values

Please check [the code](https://github.com/agathis-project/salix-breweri/code) for
the list of actual default values. The values are defined *only* in the code
to avoid changes in multiple places.

### 4.2. uP Control - Power

The uC controls the uP power-up to uP as specified in
[AP-1](https://github.com/agathis-project/salix-arctica#3321-power-up)

If uP power-down is necessary, it will be symmetrical to the above power-up.

### 4.3. uP Control - Reset and Boot

The uC controls the initialization of the uP by controlling the reset and system
boot configuration.

### 4.4. Ethernet PHY (interrupt)

TBD

### 4.5. Branch Control

TBD

## 5. References

* [AP-1 Root Module HW](https://github.com/agathis-project/salix-arctica)

## 6. License

* This document is licensed under Creative Commons Attribution-ShareAlike 4.0
  International License ([CC BY-SA 4.0](https://creativecommons.org/licenses/by-sa/4.0/))
* All code is licensed under [GPL v3](https://www.gnu.org/licenses/gpl.html)
