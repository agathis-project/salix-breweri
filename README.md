```
AP:      4
Title:   Root Module Microcontroller FW
Repo:    agathis-project
State:   Idea
Type:    SW
License: GPL
Author:  md-agathisproject
```

# Root Module Microcontroller FW

## 1. Abstract

This AP describes the functions of the microcontroller (uC) and their 
implementation - the firmware. The hardware interfaces and main uC 
functionality are described in *AP-1 Root Module HW*.

## 2. Rationale

Without the uC, the root module is dead in the water. At a the bare minimum,
to support the microprocessor (uP) bring-up, the uC needs to turn on the power
converters and take the uP out of reset.

The documenation of the uC firmware is a must; this AP will support just that.

## 3. Content

### 3.1. Requirements
EASY TO CHANGE

#### 3.1.1. uP Communication: I2C

uC is slave to uP on I2C-TRUNK interface

#### 3.1.2. uP Control: Power: V1P8, VCORE, V3P3

uC controls the power delivery to uP (V1P8, VCORE and V3P3)

#### 3.1.3. uP Control: Reset and Boot

uC controls the initialization of the uP by controlling the reset and system 
boot configuration.

#### 3.1.4. USB-OTG Interface: Power Control

#### 3.1.5. USB-OTG Interface: Authentication (switch)

#### 3.1.6. USB Host: Hub Configuration (SMB)

#### 3.1.7. USB Host: VBUS Generator (voltage doubler)

#### 3.1.8. USB Host: Control (Reset and Suspend Indicator)

#### 3.1.9. Power Switches (uSD, eMMC, Ethernet PHY, USB hub)

#### 3.1.10. Ethernet PHY (interrupt)

#### 3.1.11. Analog Monitors

#### 3.1.12. Branch Control


# 1. INTRODUCTION
## 1.1 Purpose and Scope
Help understanding the uC code intention.

## 1.2 References 
AP-1 Root Module HW

### 1.3 Definitions and acronyms

```
uC = Microcontroller
uP = Microprocessor

```

### 1.4 Document structure and reading guide
4+1 view
	
### 1.5 Document role in an iterative development process

# 2. SYSTEM OVERVIEW

##2.1 System context

## 2.2 System introduction

# 3. SYSTEM INTERFACES

## 3.1 Interface to human actors

### 3.1.1. Gateway access over USB-OTG port:

- an operator may use USB-OTG port for field servicing of the gateway.

- the gateway may connect, upon need, as USB host or as USB device.

### 3.1.1.1 Root as a USB Host:

- the uP/OS is always in control of the connection; the uC controls the USB 
  switch to connect the USB-OTG to uP.

### 3.1.1.2 Root as USB Device:

- at the time of the hardware design it was assumed that connecting the 
  gateway as USB device pose a security risk more dificult to solve at the 
  OS/SW level; as such, an optional solution was provided, to connect USB-OTG 
  firstly to uC to uC to pass an authentication test and only then the USB-OTG
  is switched over to uP/OS.

### 3.1.2. Gateway access over Test Extension Connector
  
## 3.2 Interface to external system actors

- branch control during system stand-by state.
- slave for uP on I2C-TRUNK
- master for TPM on I2C-MCU
- master for Crypto-IC in I2C-MCU
- master for ID EEPROM on I2C-TRUNK during stand-by state

- power switch control for SD-Card, eMMC, Eth-PHY, USB Hub

- voltage regulators control for V1P8, VCORE, V3P3, VUSB 

- USB-OTG cable connect event
- USB-OTG cable disconnect event 

- monitored root voltages:
  - V3P3
  - VCORE
  - V1P8
  - VUSB
  - VSYS
  
- monitored root currents:
  - current delivered to Power Module
  - current delivered to USB-OTG attached device

- power events
  - VSB3P3 rises above brown-out level
  - VSB3P3 falls below broun-out level

## 3.4 Interface to external software actors:

### 3.4.1. Test tools over Test Extension Connector: 
- PDI-DATA and PDI-CLK programming signals.
- UART
- GPIO1
- TPM-PP
- I2C-MCU  
  
### 3.4.2. USB driver on equipment connected to USB-OTG port
- the uC enters a dialog with the USB software driver of the equipment 
connected to USB-OTG; this dialog should follow the USB specifications.

# 4. USE CASE VIEW 

**Overview of architecture significant Use cases:**

- turn-on uP voltages and take uP out of reset.

- monitor uC state and system parameters over UART-XP on extension connector.

- write root module ID EEPROM: serial number and root module hardware 
descriptors.

## 4.1 Use case 1. Turn-on uP voltages and take uP out of reset.

**Scenarios A:**

- turn-on uP voltage rails - as required in AP-1 doc - only if VSYS voltage is 
above a minimal value VSYS = VSYS_START = 3.0V; VSYS_START should be 
parametrizable and listed as a hardware descriptor in ID EEPROM.

- configure the SYSBOOT signals to load from SD-Card (to begin with); their
default boot configuration should be stored as hardware descriptor in ID EEPROM.

- after the uP loads the OS, it should send an I2C message to uC with the 
result; the uC shall store this message in the flight-recorder 
(ID EEPROM or internal EEPROM).

- if the uP did not send the message within the time-out limit (tbd), then uC 
go into recovery mode - cycle through all possible booting sources.

## 4.2 Use case 2. Monitor uC over UART of extension connector.

**Scenario A:**

- after coming out of power-on reset, the uC should be responsive to UART-XU
queries from the equipment attached to the test extension connector; this 
should be done using a register map that stores root module operating 
parameters such as voltages, currents or hardware descriptors read from
ID EEPROM.

### 4.3. Use case 3. Write ID EEPROM.

**Scenarios:**

- the ID EEPROM should be partitioned as follows:
  - Serial Number
  - Hardware Descriptors
  - Flight Recorder

- The uC writes the ID EEPROM over I2C under commands from external equipment
connected to UART-XU; the uC should not change the ID EEPROM 


write ID EEPROM




# 5. LOGICAL VIEW 

5.1 Overview

5.2 Architecturally significant design packages
5.2.1 Package 1

5.2.2 Package 2

5.3 Use case realizations

5.3.1 Use case 1. realization

5.3.2 Use case 2. realization



6. PROCESS/TASK VIEW 

6.1 Process/task overview

6.2 Process/task implementation

6.3 Process/task communication and synchronization

6.4 Process group 1.

6.4.1 Process communication in group 1

6.4.2 Process 1. description

6.4.3 Process 2. description

6.5 Process group 2.

7. DEPLOYMENT VIEW 

7.1 System configurations overview

7.2 System configurations

7.2.1 Configuration 1.

7.2.2 Configuration 2.

7.3 Node descriptions

7.3.1 Node 1. description

7.3.2 Node 2. description

8. IMPLEMENTATION VIEW 

8.1 Overview

8.2 Component descriptions

8.2.1 Component 1

8.2.2 Component 2

9. DATA VIEW

9.1 Data model

9.2 Implementation of persistence

10. GENEREL DESIGN DECISIONS

10.1 Architectural goals and constraints 

10.2 Architectural patterns

10.3 General user interface design rules

10.4 Exception and error handling

10.5 Implementation languages and tools

10.6 Implementation libraries

11. SIZE AND PERFORMANCE 

12. QUALITY 

13. COMPILATION AND LINKING

13.1 Compilation-hardware

13.2 Compilation-software

13.3 Compilation and linking process

14. INSTALLATION AND EXECUTING

14.1 Installation

14.2 Executing-hardware

14.3 Executing-software

14.4 Execution-control (start, stop and restart)

14.5 Error messages

15. APPENDICES







## 4. References
## 5. License
This work is licensed under GPL.

## 6. Attachments