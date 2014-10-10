/************************************************************************/
/*                                                                      */
/*    BoardConfig.h   This configures board specific features           */
/*                  for the stk500v2 avrdude/MPIDE PIC32                */
/*                    compliment bootloader                             */
/*                                                                      */
/************************************************************************/
/*    Author:     Keith Vogel                                           */
/*  Copyright 2013, Digilent Inc.                                       */
/************************************************************************/
/*
*
* Copyright (c) 2013-2014, Digilent <www.digilentinc.com>
* Contact Digilent for the latest version.
*
* This program is free software; distributed under the terms of
* BSD 3-clause license ("Revised BSD License", "New BSD License", or "Modified BSD License")
*
* Redistribution and use in source and binary forms, with or without modification,
* are permitted provided that the following conditions are met:
*
* 1.    Redistributions of source code must retain the above copyright notice, this
*        list of conditions and the following disclaimer.
* 2.    Redistributions in binary form must reproduce the above copyright notice,
*        this list of conditions and the following disclaimer in the documentation
*        and/or other materials provided with the distribution.
* 3.    Neither the name(s) of the above-listed copyright holder(s) nor the names
*        of its contributors may be used to endorse or promote products derived
*        from this software without specific prior written permission.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
* ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
* WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
* IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
* INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
* BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
* DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
* LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
* OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
* OF THE POSSIBILITY OF SUCH DAMAGE.
*/
/************************************************************************/
/*  Revision History:                                                   */
/*                                                                      */
/*    2/23/2011(KeithV): Created                                        */
/*    6/17/2012(KeithV): Added Just In Time Flash Erase                 */
/*    6/17/2012(KeithV): Added header information                       */
/*    6/25/2012(KeithV): Added Vendor ID and Product IDs                */
/*    1/15/2013(BrianS): Added PPS unlock for MX1/MX2 devices           */
/*    3/18/2013(BrianS): Added 48Mhz FB Mini device, fixed USBID and    */
/*                       VBUSON                                         */
/*    22/5/2013(gmtii):  Added Olimex PIC32 Pinguino board		        */
/*    6/2302/13(BrianS): Added DP32                                     */
/*    1/15/2014 (KeithV): Added MZ support                              */
/*                                                                      */
/************************************************************************/

// *****************************************************************************
// *****************************************************************************
//                     Helper Macros
// *****************************************************************************
// *****************************************************************************
#define CAT1_2(a,b)         a##b
#define CAT_2(a,b)          CAT1_2(a,b)
#define CAT_3(a,b,c)        CAT_2(CAT_2(a,b),c)
#define CAT_4(a,b,c,d)      CAT_2(CAT_2(a,b),CAT_2(c,d))
#define CAT_5(a,b,c,d,e)    CAT_2(CAT_3(a,b,c),CAT_2(d,e))
#define Low     0
#define High    1

// *****************************************************************************
// *****************************************************************************
//                     Vendor IDs
// *****************************************************************************
// *****************************************************************************
#define     vendUnknown         0xFFFF
#define     vendUnassigned      0x0000
#define     vendDigilent        0x0001
#define     vendMicrochip       0x0002
#define     vendFubarino        0x0003
#define     vendSchmalzHausLLC  0x0004
#define     vendOlimex          0x0005
#define		vendElement14		0x0006
#define     vendPontech         0x0007
#define     vendExperimental    0x8000

// *****************************************************************************
// *****************************************************************************
//                    Digilent Product IDs
// *****************************************************************************
// *****************************************************************************
#define     prodUnknown         0xFFFF
#define     prodUnassigned      0x0000

// Hardware / software Arduino compatible chipKITs
#define     prodChipKITUno32    0x0101
#define     prodChipKITMax32    0x0102
#define     prodChipKITuC32     0x0103
#define     prodChipKITWF32     0x0104
#define     prodChipKITFG32     0x0105

// Cerebot like boards, only software Arduino compatible chipKITs
#define     prodCerebot32MX4    0x0201
#define     prodCerebot32MX7    0x0202
#define     prodCerebotMX3cK128 0x0203
#define     prodCerebotMX4cK    0x0204
#define     prodCerebotMX7cK    0x0205
#define     prodCerebotMX3cK512 0x0206

// DIP form factor, only software Arduino compatible chipKITs
#define     prodCmodCK1         0x0301

// Experimenter boards form factor, only software Arduino compatible chipKITs
#define     prodChipKITDP32     0x0401

// UDB board
#define     prodChipKITUDB32PIM 0x0501

// MZ processors
#define     prodChipKITWiFire   0x0601
#define     prodChipKITzUno     0x0602


// *****************************************************************************
// *****************************************************************************
//                    Fubarino Product IDs
// *****************************************************************************
// *****************************************************************************
#define     prodFubarinoSD      0x0001
#define     prodFubarinoMini    0x0002
#define     prodFubarinoSD_512K 0x0003
#define     prodFubarinoMini48MHz 0x0004
#define     prodFubarinoMini50MHz 0x0005

// *****************************************************************************
// *****************************************************************************
//                    Schmalz Haus Product IDs
// *****************************************************************************
// *****************************************************************************
#define     prodEBBv3      		0x0001
#define     prodUBW32MX460 		0x0002
#define     prodUBW32MX795 		0x0003

// *****************************************************************************
// *****************************************************************************
//                    Olimex Product IDs
// *****************************************************************************
// *****************************************************************************
#define     prodOlimex_PIC32_Pinguino   0x0001
#define     prodOlimex_Duinomite        0x0002

// *****************************************************************************
// *****************************************************************************
//                    Element14 Product IDs
// *****************************************************************************
// *****************************************************************************
#define     prodChipkitPi		0x0001

// *****************************************************************************
// *****************************************************************************
//                    Pontech Product IDs
// *****************************************************************************
// *****************************************************************************
#define     prodQuick240                0x0001

// Bootloader Capability bits
// The first 4 bits define what type of STK500 interface is used
// The next 4 bits define what LEDs are used
// The next 8 bits define how the bootloader is to be put in programming/listen mode
// The next 8 bits are how flash is erased instructed by the linker
// The next 4 bits are this and that capabilities instructed by the linker
// The last 4 bits are this and that capabilities
#define blCapUARTInterface                              0x00000001ul        // Avrdude talks over a UART
#define blCapUSBInterface                               0x00000002ul        // Avrdude talks over the USB for serial
#define blCapBootLED                                    0x00000010ul        // A boot LED is driven
#define blCapDownloadLED                                0x00000020ul        // A download LED is driven
#define blCapAutoResetListening                         0x00000100ul        // There is a short listening delay after reset for avrdude to upload a sketch before automatically loading the in flash sketch              
#define blCapProgramButton                              0x00000200ul        // A program button is suppored  
#define blCapVirtualProgramButton                       0x00000400ul        // A virtual program button is suppored
#define blCapLkInstrFullFlashEraseLess4KEEProm          0x00010000ul        // The original bootloader method of erasing all of program flash except the last 4K reserved for eeprom
#define blCapLkInstrJustInTimeFlashErase                0x00020000ul        // Only flash pages written too needed by the sketch is erased
#define blCapLkInstrFlashErase                          0x00040000ul        // The linker defines the flash range to erase
#define blCapLkInstrFullFlashErase                      0x00080000ul        // All of flash is erased
#define blCapLkInstrExecutionJumpAddress                0x01000000ul        // the bootloader will jump to the execution jump address immediately after programming
#define blCapLkInstrExecutionJumpToFirstInFlash         0x02000000ul        // the bootloader will jump to the first sketch loaded in flash ignoring the execution jump address immediately after programming
#define blCapSupportsRamHeaderAndPersistentData         0x10000000ul        // This checks and clears the Ram Header and adds RAM header data like the RCON value
#define blCapSplitFlashBootloader                       0x20000000ul        // This is a split flash bootloader with some of the bootloader in program flash
#define blCapSmartStart                                 0x40000000ul        // To indicate that the bootloader has implemented a smart start sequence to prevent execution of the sketch until all start sequences have stabalized.
#define blCapNotProvided                                0x80000000ul        // If this is set, then all capability bits have no meaning. This will be set if flash is in its erased state and the bootloader did not set any bits.

#define CAPCOMMON (blCapLkInstrFullFlashEraseLess4KEEProm | blCapLkInstrJustInTimeFlashErase | blCapLkInstrFlashErase | blCapLkInstrFullFlashErase | blCapLkInstrExecutionJumpAddress | blCapLkInstrExecutionJumpToFirstInFlash | blCapSupportsRamHeaderAndPersistentData)

#if !defined(__PIC32MX__) && !defined(__PIC32MZ__)
    #error "This project was designed for PIC32MX family devices. Please select the appropriate project for your target device family."
#endif

// For historical reasons, these must be defined as these specific constants and nothing else
#define FLASH_START             0x9D000000
#define USER_APP_ADDR           0x9D001000
#define DEFAULT_EEPROM_SIZE     4096

//************************************************************************
#if defined(_BOARD_EXAMPLE_MX1_)               

#if defined(PUT_CONFIG_BITS_HERE)

    //*    Oscillator Settings
    #pragma config FNOSC    = PRIPLL                        // Oscillator Selection
    #pragma config POSCMOD  = XT                            // Primary Oscillator
    #pragma config FPLLIDIV = DIV_2                         // PLL input divider
    #pragma config FPLLMUL  = MUL_20                        // PLL multiplier
    #pragma config FPLLODIV = DIV_2                         // PLL output divider
    #pragma config FPBDIV   = DIV_1                         // Peripheral bus clock divider
    #pragma config FSOSCEN  = OFF                           // Secondary Oscillator Enable

    //*    Clock control settings
    #pragma config IESO     = ON                            // Internal/External Switch-over
    #pragma config FCKSM    = CSDCMD                        // Clock Switching & Fail Safe Clock Monitor
    #pragma config OSCIOFNC = OFF                           // CLKO Enable

    //*    Other Peripheral Device settings
    #pragma config FWDTEN   = OFF                           // Watchdog Timer
    #pragma config WDTPS    = PS1024                        // Watchdog Timer Postscale
    #pragma config WINDIS   = OFF
    #pragma config JTAGEN   = OFF                           // JTAG port disabled

    //*    Code Protection settings
    #pragma config CP       = OFF                           // Code Protect
    #pragma config BWP      = OFF                           // Boot Flash Write Protect
    #pragma config PWP      = OFF                           // Program Flash Write Protect

    //*    Debug settings
    #pragma config ICESEL   = ICS_PGx1                      // ICE/ICD Comm Channel Select
    //#pragma config DEBUG    = ON                          // DO NOT SET THIS CONFIG BIT, it will break debugging

    #pragma config PMDL1WAY = OFF                           // Allow multiple reconfigurations
    #pragma config IOL1WAY  = OFF                           // Allow multiple reconfigurations
#endif

    #define CAPABILITIES    (blCapBootLED | blCapDownloadLED | blCapUARTInterface | blCapProgramButton | blCapVirtualProgramButton | CAPCOMMON)

    // BTN / LED sense
    #define LedOn       High
    #define BntOn       High

    // Boot LED
    #define BLedLat     A
    #define BLedBit     7

    // Download LED
    #define DLedLat     A
    #define DLedBit     8

    // Virtual program button
    #define VPBntLat    A
    #define VPBntBit    4

    // Program button
    #define PBntPort    A
    #define PBntBit     4

    #define _CPU_NAME_              "32MX120F032D"
    #define VEND                    vendUnassigned
    #define PROD                    prodUnassigned
    #define F_CPU                   40000000UL              // CPU frequence
    #define F_PBUS                  F_CPU                   // Peripheral bus rate F_CPU / FPBDIV; just set it, saves code.

    #define FLASH_BYTES             0x8000                  // 32K
    #define FLASH_PAGE_SIZE         1024

    #define BOOTLOADER_UART         1                       // avrdude program UART
    #define BAUDRATE                115200                  // avrdude baudrate
    #define UARTMapRX()             (U1RXR = 0x1)           // RPB6 -> U1RX
    #define UARTMapTX()             (RPB7R = 0x1)           // RB7 -> U1TX
 
//************************************************************************
#elif defined(_BOARD_UDB32_MX2_DIP_)

#if defined(PUT_CONFIG_BITS_HERE)

    //* Oscillator Settings
    #pragma config FNOSC    = PRIPLL                                // Oscillator selection
    #pragma config POSCMOD  = XT                                    // Primary oscillator mode
    #pragma config FPLLIDIV = DIV_2                                 // PLL input divider
    #pragma config FPLLMUL  = MUL_20                                // PLL multiplier
    #pragma config FPLLODIV = DIV_2                                 // PLL output divider
    #pragma config FPBDIV   = DIV_1                                 // Peripheral bus clock divider
    #pragma config FSOSCEN  = OFF                                    // Secondary oscillator enable

    //* Clock control settings
    #pragma config IESO     = OFF                                   // Internal/external clock switchover
    #pragma config FCKSM    = CSECME                                // Clock switching (CSx)/Clock monitor (CMx)
    #pragma config OSCIOFNC = OFF                                   // Clock output on OSCO pin enable

    //* USB Settings
    #pragma config UPLLEN   = ON                                    // USB PLL enable
    #pragma config UPLLIDIV = DIV_2                                 // USB PLL input divider
    #pragma config FVBUSONIO = OFF                                  // Make VBUSON a GPIO pin
    #pragma config FUSBIDIO = OFF                                   // Controlled by port function

    //* Other Peripheral Device settings
    #pragma config FWDTEN   = OFF                                   // Watchdog timer enable
    #pragma config WDTPS    = PS1024                                // Watchdog timer postscaler
    #pragma config WINDIS   = OFF
    #pragma config JTAGEN   = OFF                                   // JTAG port disabled

    //* Code Protection settings
    #pragma config CP       = OFF                                   // Code protection
    #pragma config BWP      = OFF                                   // Boot flash write protect
    #pragma config PWP      = OFF                                   // Program flash write protect

    //*    Debug settings
    #pragma config ICESEL   = ICS_PGx1                      		// ICE/ICD Comm Channel Select
    //#pragma config DEBUG    = ON                          		// DO NOT SET THIS CONFIG BIT, it will break debugging

    #pragma config PMDL1WAY = OFF                           		// Allow multiple reconfigurations
    #pragma config IOL1WAY  = OFF                           		// Allow multiple reconfigurations
#endif

    #define CAPABILITIES    (blCapBootLED | blCapDownloadLED | blCapUARTInterface | blCapProgramButton | blCapVirtualProgramButton | CAPCOMMON)

    // BTN / LED sense
    #define LedOn       Low
    #define BntOn       High

    // Boot LED
    #define BLedLat     B
    #define BLedBit     0

    // Download LED
    #define DLedLat     B
    #define DLedBit     1

    // Virtual program button
    #define VPBntLat    B
    #define VPBntBit    4

    // Program button
    #define PBntPort    B
    #define PBntBit     4

    #define _CPU_NAME_                  "32MX250F128B"
    #define VEND                        vendDigilent
    #define PROD                        prodChipKITDP32
    #define F_CPU                       40000000UL
    #define F_PBUS                      F_CPU

    #define FLASH_BYTES                 (0x20000)           // Leave room 4 pages (for bootloader!)
    #define FLASH_PAGE_SIZE             1024                // In bytes

    #define BOOTLOADER_UART             1                   // avrdude program UART
    #define BAUDRATE                    115200              // avrdude baudrate
    #define UARTMapRX()                 (U1RXR = 0x3)       // RPB13 -> U1RX
    #define UARTMapTX()                 (RPB3R = 0x1)       // RB3 -> U1TX

//************************************************************************
#elif defined(_BOARD_CMOD_CK1_)

#if defined(PUT_CONFIG_BITS_HERE)

    //*    Oscillator Settings
    #pragma config FNOSC    = PRIPLL                        // Oscillator Selection
    #pragma config POSCMOD  = XT                            // Primary Oscillator
    #pragma config FPLLIDIV = DIV_2                         // PLL input divider
    #pragma config FPLLMUL  = MUL_20                        // PLL multiplier
    #pragma config FPLLODIV = DIV_2                         // PLL output divider
    #pragma config FPBDIV   = DIV_1                         // Peripheral bus clock divider
    #pragma config FSOSCEN  = OFF                           // Secondary Oscillator Enable

    //*    Clock control settings
    #pragma config IESO     = ON                            // Internal/External Switch-over
    #pragma config FCKSM    = CSDCMD                        // Clock Switching & Fail Safe Clock Monitor
    #pragma config OSCIOFNC = OFF                           // CLKO Enable

    //*    Other Peripheral Device settings
    #pragma config FWDTEN   = OFF                           // Watchdog Timer
    #pragma config WDTPS    = PS1024                        // Watchdog Timer Postscale
    #pragma config WINDIS   = OFF
    #pragma config JTAGEN   = OFF                           // JTAG port disabled

    //*    Code Protection settings
    #pragma config CP       = OFF                           // Code Protect
    #pragma config BWP      = OFF                           // Boot Flash Write Protect
    #pragma config PWP      = OFF                           // Program Flash Write Protect

    //*    Debug settings
    #pragma config ICESEL   = ICS_PGx2                      // ICE/ICD Comm Channel Select
    //#pragma config DEBUG    = ON                          // DO NOT SET THIS CONFIG BIT, it will break debugging

    #pragma config PMDL1WAY = OFF                           // Allow multiple reconfigurations
    #pragma config IOL1WAY  = OFF                           // Allow multiple reconfigurations
#endif

    #define CAPABILITIES    (blCapBootLED | blCapDownloadLED | blCapUARTInterface | blCapAutoResetListening | blCapVirtualProgramButton | CAPCOMMON)

    // BTN / LED sense
    #define LedOn       High
    #define BntOn       High

    // Boot LED
    #define BLedLat     A
    #define BLedBit     10

    // Download LED
    #define DLedLat     B
    #define DLedBit     12

    // Virtual program button
    #define VPBntLat    A
    #define VPBntBit    2

    #define _CPU_NAME_              "PIC32MX150F128D"
    #define VEND                    vendDigilent
    #define PROD                    prodCmodCK1
    #define F_CPU                   40000000UL              // CPU frequence
    #define F_PBUS                  F_CPU                   // Peripheral bus rate F_CPU / FPBDIV; just set it, saves code.

    #define FLASH_BYTES             0x20000                  // 128K
    #define FLASH_PAGE_SIZE         1024

    #define LISTEN_BEFORE_LOAD      2000                    // no less than 2 seconds
    #define BOOTLOADER_UART         1                       // avrdude program UART
    #define BAUDRATE                115200                  // avrdude baudrate
    #define UARTMapRX()             (U1RXR = 0x5)           // RPC6 -> U1RX
    #define UARTMapTX()             (RPB3R = 0x1)           // RPB3 -> U1TX

//************************************************************************
#elif defined(_BOARD_CHIPKIT_DP32_)

#if defined(PUT_CONFIG_BITS_HERE)

    //* Oscillator Settings
    #pragma config FNOSC    = PRIPLL                                // Oscillator selection
    #pragma config POSCMOD  = XT                                    // Primary oscillator mode
    #pragma config FPLLIDIV = DIV_2                                 // PLL input divider
    #pragma config FPLLMUL  = MUL_20                                // PLL multiplier
    #pragma config FPLLODIV = DIV_2                                 // PLL output divider
    #pragma config FPBDIV   = DIV_1                                 // Peripheral bus clock divider
    #pragma config FSOSCEN  = OFF                                    // Secondary oscillator enable

    //* Clock control settings
    #pragma config IESO     = OFF                                   // Internal/external clock switchover
    #pragma config FCKSM    = CSECME                                // Clock switching (CSx)/Clock monitor (CMx)
    #pragma config OSCIOFNC = OFF                                   // Clock output on OSCO pin enable

    //* USB Settings
    #pragma config UPLLEN   = ON                                    // USB PLL enable
    #pragma config UPLLIDIV = DIV_2                                 // USB PLL input divider
    #pragma config FVBUSONIO = OFF                                  // Make VBUSON a GPIO pin
    #pragma config FUSBIDIO = OFF                                   // Controlled by port function

    //* Other Peripheral Device settings
    #pragma config FWDTEN   = OFF                                   // Watchdog timer enable
    #pragma config WDTPS    = PS1024                                // Watchdog timer postscaler
    #pragma config WINDIS   = OFF
    #pragma config JTAGEN   = OFF                                   // JTAG port disabled

    //* Code Protection settings
    #pragma config CP       = OFF                                   // Code protection
    #pragma config BWP      = OFF                                   // Boot flash write protect
    #pragma config PWP      = OFF                                   // Program flash write protect

    //*    Debug settings
    #pragma config ICESEL   = ICS_PGx1                      		// ICE/ICD Comm Channel Select
    //#pragma config DEBUG    = ON                          		// DO NOT SET THIS CONFIG BIT, it will break debugging

    #pragma config PMDL1WAY = OFF                           		// Allow multiple reconfigurations
    #pragma config IOL1WAY  = OFF                           		// Allow multiple reconfigurations
#endif

    #define CAPABILITIES    (blCapBootLED | blCapDownloadLED | blCapSplitFlashBootloader | blCapUSBInterface | blCapProgramButton | blCapVirtualProgramButton | CAPCOMMON)

    // BTN / LED sense
    #define LedOn       High
    #define BntOn       High

    // Boot LED
    #define BLedLat     B
    #define BLedBit     3

    // Download LED
    #define DLedLat     B
    #define DLedBit     2

    // Virtual program button
    #define VPBntLat    B
    #define VPBntBit    4

    // Program button
    #define PBntPort    B
    #define PBntBit     4

    #define _CPU_NAME_                  "32MX250F128B"
    #define VEND                        vendDigilent
    #define PROD                        prodChipKITDP32
    #define F_CPU                       40000000UL
    #define F_PBUS                      F_CPU

    #define FLASH_BYTES                 (0x20000-0x1000)		    // Leave room 4 pages (for bootloader!)
    #define FLASH_PAGE_SIZE             1024                                // In bytes

//************************************************************************
#elif defined(_BOARD_CHIPKIT_DP32_CHIPSTOMP_)

#if defined(PUT_CONFIG_BITS_HERE)

    //* Oscillator Settings
    #pragma config FNOSC    = PRIPLL                                // Oscillator selection
    #pragma config POSCMOD  = XT                                    // Primary oscillator mode
    #pragma config FPLLIDIV = DIV_2                                 // PLL input divider
    #pragma config FPLLMUL  = MUL_20                                // PLL multiplier
    #pragma config FPLLODIV = DIV_2                                 // PLL output divider
    #pragma config FPBDIV   = DIV_1                                 // Peripheral bus clock divider
    #pragma config FSOSCEN  = OFF                                    // Secondary oscillator enable

    //* Clock control settings
    #pragma config IESO     = OFF                                   // Internal/external clock switchover
    #pragma config FCKSM    = CSECME                                // Clock switching (CSx)/Clock monitor (CMx)
    #pragma config OSCIOFNC = OFF                                   // Clock output on OSCO pin enable

    //* USB Settings
    #pragma config UPLLEN   = ON                                    // USB PLL enable
    #pragma config UPLLIDIV = DIV_2                                 // USB PLL input divider
    #pragma config FVBUSONIO = OFF                                  // Make VBUSON a GPIO pin
    #pragma config FUSBIDIO = OFF                                   // Controlled by port function

    //* Other Peripheral Device settings
    #pragma config FWDTEN   = OFF                                   // Watchdog timer enable
    #pragma config WDTPS    = PS1024                                // Watchdog timer postscaler
    #pragma config WINDIS   = OFF
    #pragma config JTAGEN   = OFF                                   // JTAG port disabled

    //* Code Protection settings
    #pragma config CP       = OFF                                   // Code protection
    #pragma config BWP      = OFF                                   // Boot flash write protect
    #pragma config PWP      = OFF                                   // Program flash write protect

    //*    Debug settings
    #pragma config ICESEL   = ICS_PGx1                              // ICE/ICD Comm Channel Select
    //#pragma config DEBUG    = ON                                  // DO NOT SET THIS CONFIG BIT, it will break debugging

    #pragma config PMDL1WAY = OFF                                   // Allow multiple reconfigurations
    #pragma config IOL1WAY  = OFF                                   // Allow multiple reconfigurations
#endif

    #define CAPABILITIES    (blCapBootLED | blCapDownloadLED | blCapSplitFlashBootloader | blCapUSBInterface | blCapProgramButton | blCapVirtualProgramButton | CAPCOMMON)

    // BTN / LED sense
    #define LedOn       High
    #define BntOn       Low

    // Boot LED
    #define BLedLat     B
    #define BLedBit     3

    // Download LED
    #define DLedLat     B
    #define DLedBit     2

    // Virtual program button
    #define VPBntLat    B
    #define VPBntBit    4

    // Program button
    #define PBntPort    B
    #define PBntBit     4

    #define _CPU_NAME_                  "32MX250F128B"
    #define VEND                        vendDigilent
    #define PROD                        prodChipKITDP32
    #define F_CPU                       40000000UL
    #define F_PBUS                      F_CPU

    #define FLASH_BYTES                 (0x20000-0x1000)            // Leave room 4 pages (for bootloader!)
    #define FLASH_PAGE_SIZE             1024                                // In bytes

//************************************************************************
#elif defined(_BOARD_CHIPKIT_UNO32_)

#if defined(PUT_CONFIG_BITS_HERE)

    //*    Oscillator Settings
    #pragma config FNOSC    = PRIPLL                        // Oscillator selection
    #pragma config POSCMOD  = XT                            // Primary oscillator mode
    #pragma config FPLLIDIV = DIV_2                         // PLL input divider
    #pragma config FPLLMUL  = MUL_20                        // PLL multiplier
    #pragma config FPLLODIV = DIV_1                         // PLL output divider
    #pragma config FPBDIV   = DIV_1                         // Peripheral bus clock divider
    #pragma config FSOSCEN  = ON                            // Secondary oscillator enable

    //*    Clock control settings
    #pragma config IESO     = OFF                           // Internal/external clock switchover
    #pragma config FCKSM    = CSDCMD                        // Clock switching (CSx)/Clock monitor (CMx)
    #pragma config OSCIOFNC = OFF                           // Clock output on OSCO pin enable

    //*    Other Peripheral Device settings
    #pragma config FWDTEN   = OFF                           // Watchdog timer enable
    #pragma config WDTPS    =  PS1024                       // Watchdog timer postscaler

    //*    Code Protection settings
    #pragma config CP       = OFF                           // Code protection
    #pragma config BWP      = OFF                           // Boot flash write protect
    #pragma config PWP      = OFF                           // Program flash write protect

    //*    Debug settings
    #pragma config ICESEL   = ICS_PGx2                      // ICE pin selection
#endif

    #define CAPABILITIES    (blCapBootLED | blCapDownloadLED | blCapUARTInterface | blCapAutoResetListening | blCapVirtualProgramButton | CAPCOMMON)

    // BTN / LED sense
    #define LedOn       High
    #define BntOn       High

    // Boot LED
    #define BLedLat     G
    #define BLedBit     6

    // Download LED
    #define DLedLat     F
    #define DLedBit     0

    // Virtual program button
    #define VPBntLat    C
    #define VPBntBit    12

    // Other capabilities
    #define LISTEN_BEFORE_LOAD          2000                // no less than 2 seconds
    #define BOOTLOADER_UART             1                   // avrdude program UART
    #define BAUDRATE                    115200              // avrdude baudrate
 
    #define _CPU_NAME_                  "32MX320F128H"
    #define VEND                        vendDigilent
    #define PROD                        prodChipKITUno32
    #define F_CPU                       80000000UL
    #define F_PBUS                      F_CPU

    #define FLASH_BYTES                 0x20000             // 128K
    #define FLASH_PAGE_SIZE             4096
    #define LoadFlashWaitStates()       (CHECON = 2)

//************************************************************************
#elif defined(_BOARD_CEREBOT_MX3CK_128_)

#if defined(PUT_CONFIG_BITS_HERE)

    //*    Oscillator Settings
    #pragma config FNOSC    = PRIPLL                            // Oscillator selection
    #pragma config POSCMOD  = XT                                // Primary oscillator mode
    #pragma config FPLLIDIV = DIV_2                             // PLL input divider
    #pragma config FPLLMUL  = MUL_20                            // PLL multiplier
    #pragma config FPLLODIV = DIV_1                             // PLL output divider
    #pragma config FPBDIV   = DIV_1                             // Peripheral bus clock divider
    #pragma config FSOSCEN  = ON                                // Secondary oscillator enable

    //*    Clock control settings
    #pragma config IESO     = OFF                               // Internal/external clock switchover
    #pragma config FCKSM    = CSDCMD                            // Clock switching (CSx)/Clock monitor (CMx)
    #pragma config OSCIOFNC = OFF                               // Clock output on OSCO pin enable

    //*    Other Peripheral Device settings
    #pragma config FWDTEN   = OFF                               // Watchdog timer enable
    #pragma config WDTPS    = PS1024                            // Watchdog timer postscaler

    //*    Code Protection settings
    #pragma config CP       = OFF                               // Code protection
    #pragma config BWP      = OFF                               // Boot flash write protect
    #pragma config PWP      = OFF                               // Program flash write protect

    //*    Debug settings
    #pragma config ICESEL   = ICS_PGx2                          // ICE pin selection
#endif

    #define CAPABILITIES    (blCapBootLED | blCapDownloadLED | blCapUARTInterface | blCapAutoResetListening | blCapVirtualProgramButton | CAPCOMMON)

    // BTN / LED sense
    #define LedOn       High
    #define BntOn       High

    // Boot LED
    #define BLedLat     F
    #define BLedBit     0

    // Download LED
    #define DLedLat     F
    #define DLedBit     1

    // Virtual program button
    #define VPBntLat    C
    #define VPBntBit    12

    // Other capabilities
    #define LISTEN_BEFORE_LOAD          2000                // no less than 2 seconds
    #define BOOTLOADER_UART             1                   // avrdude program UART
    #define BAUDRATE                    115200              // avrdude baudrate
 
    #define _CPU_NAME_                  "32MX320F128H"
    #define VEND                        vendDigilent
    #define PROD                        prodCerebotMX3cK128
    #define F_CPU                       80000000UL
    #define F_PBUS                      F_CPU

    #define FLASH_BYTES                 0x20000             // 128K
    #define FLASH_PAGE_SIZE             4096
    #define LoadFlashWaitStates()       (CHECON = 2)        // 0 for 0-30Mhz, 1 for 31-60Mhz, 2 for 61-80Mhz

//************************************************************************
#elif defined(_BOARD_UDB32_PIM_)

#if defined(PUT_CONFIG_BITS_HERE)

    //*    Oscillator Settings
    #pragma config FNOSC    = PRIPLL                        // Oscillator selection
    #pragma config POSCMOD  = XT                            // Primary oscillator mode
    #pragma config FPLLIDIV = DIV_2                         // PLL input divider
    #pragma config FPLLMUL  = MUL_20                        // PLL multiplier
    #pragma config FPLLODIV = DIV_1                         // PLL output divider
    #pragma config FPBDIV   = DIV_1                         // Peripheral bus clock divider
    #pragma config FSOSCEN  = ON                            // Secondary oscillator enable

    //*    Clock control settings
    #pragma config IESO     = OFF                           // Internal/external clock switchover
    #pragma config FCKSM    = CSDCMD                        // Clock switching (CSx)/Clock monitor (CMx)
    #pragma config OSCIOFNC = OFF                           // Clock output on OSCO pin enable

    //*    Other Peripheral Device settings
    #pragma config FWDTEN   = OFF                           // Watchdog timer enable
    #pragma config WDTPS    = PS1024                        // Watchdog timer postscaler

    //*    Code Protection settings
    #pragma config CP       = OFF                           // Code protection
    #pragma config BWP      = OFF                           // Boot flash write protect
    #pragma config PWP      = OFF                           // Program flash write protect

    //*    Debug settings
    #pragma config ICESEL   = ICS_PGx1                      // ICE pin selection
#endif

    #define CAPABILITIES    (blCapBootLED | blCapDownloadLED | blCapUARTInterface | blCapProgramButton | blCapVirtualProgramButton | CAPCOMMON)

    // BTN / LED sense
    #define LedOn       Low
    #define BntOn       High

    // Boot LED
    #define BLedLat     A
    #define BLedBit     6

    // Download LED
    #define DLedLat     A
    #define DLedBit     7

    // Virtual program button
    #define VPBntLat    G
    #define VPBntBit    15

    // Program button
    #define PBntPort    G
    #define PBntBit     15

    // Other capabilities
    #define BOOTLOADER_UART             1                   // avrdude program UART
    #define BAUDRATE                    115200              // avrdude baudrate

    #define _CPU_NAME_                  "32MX360F512L"
    #define VEND                        vendDigilent
    #define PROD                        prodChipKITUDB32PIM
    #define F_CPU                       80000000UL
    #define F_PBUS                      F_CPU

    #define FLASH_BYTES                 0x80000         // 512K
    #define FLASH_PAGE_SIZE             4096
    #define LoadFlashWaitStates()       (CHECON = 2)

//************************************************************************
#elif defined(_BOARD_CHIPKIT_UC32_)

#if defined(PUT_CONFIG_BITS_HERE)

    //*    Oscillator Settings
    #pragma config FNOSC    = PRIPLL                        // Oscillator selection
    #pragma config POSCMOD  = XT                            // Primary oscillator mode
    #pragma config FPLLIDIV = DIV_2                         // PLL input divider
    #pragma config FPLLMUL  = MUL_20                        // PLL multiplier
    #pragma config FPLLODIV = DIV_1                         // PLL output divider
    #pragma config FPBDIV   = DIV_1                         // Peripheral bus clock divider
    #pragma config FSOSCEN  = ON                            // Secondary oscillator enable

    //*    Clock control settings
    #pragma config IESO     = OFF                           // Internal/external clock switchover
    #pragma config FCKSM    = CSDCMD                        // Clock switching (CSx)/Clock monitor (CMx)
    #pragma config OSCIOFNC = OFF                           // Clock output on OSCO pin enable

    //*    Other Peripheral Device settings
    #pragma config FWDTEN   = OFF                           // Watchdog timer enable
    #pragma config WDTPS    = PS1024                        // Watchdog timer postscaler

    //*    Code Protection settings
    #pragma config CP       = OFF                           // Code protection
    #pragma config BWP      = OFF                           // Boot flash write protect
    #pragma config PWP      = OFF                           // Program flash write protect

    //*    Debug settings
    #pragma config ICESEL   = ICS_PGx2                      // ICE pin selection
#endif

    #define CAPABILITIES    (blCapBootLED | blCapDownloadLED | blCapUARTInterface | blCapAutoResetListening | blCapVirtualProgramButton | CAPCOMMON)

    // BTN / LED sense
    #define LedOn       High
    #define BntOn       High

    // Boot LED
    #define BLedLat     G
    #define BLedBit     6

    // Download LED
    #define DLedLat     F
    #define DLedBit     0

    // Virtual program button
    #define VPBntLat    C
    #define VPBntBit    12

    // Other capabilities
    #define LISTEN_BEFORE_LOAD          2000                // no less than 2 seconds
    #define BOOTLOADER_UART             1                   // avrdude program UART
    #define BAUDRATE                    115200              // avrdude baudrate

    #define _CPU_NAME_                  "32MX340F512H"
    #define VEND                        vendDigilent
    #define PROD                        prodChipKITuC32
    #define F_CPU                       80000000UL
    #define F_PBUS                      F_CPU

    #define FLASH_BYTES                 0x80000         // 512K   
    #define FLASH_PAGE_SIZE             4096
    #define LoadFlashWaitStates()       (CHECON = 2)

//************************************************************************
#elif defined(_BOARD_CEREBOT_MX3CK_512_)

#if defined(PUT_CONFIG_BITS_HERE)

    //*    Oscillator Settings
    #pragma config FNOSC    = PRIPLL                            // Oscillator selection
    #pragma config POSCMOD  = XT                                // Primary oscillator mode
    #pragma config FPLLIDIV = DIV_2                             // PLL input divider
    #pragma config FPLLMUL  = MUL_20                            // PLL multiplier
    #pragma config FPLLODIV = DIV_1                             // PLL output divider
    #pragma config FPBDIV   = DIV_1                             // Peripheral bus clock divider
    #pragma config FSOSCEN  = ON                                // Secondary oscillator enable

    //*    Clock control settings
    #pragma config IESO     = OFF                               // Internal/external clock switchover
    #pragma config FCKSM    = CSDCMD                            // Clock switching (CSx)/Clock monitor (CMx)
    #pragma config OSCIOFNC = OFF                               // Clock output on OSCO pin enable

    //*    Other Peripheral Device settings
    #pragma config FWDTEN   = OFF                               // Watchdog timer enable
    #pragma config WDTPS    = PS1024                            // Watchdog timer postscaler

    //*    Code Protection settings
    #pragma config CP       = OFF                               // Code protection
    #pragma config BWP      = OFF                               // Boot flash write protect
    #pragma config PWP      = OFF                               // Program flash write protect

    //*    Debug settings
    #pragma config ICESEL   = ICS_PGx2                          // ICE pin selection
#endif

    #define CAPABILITIES    (blCapBootLED | blCapDownloadLED | blCapUARTInterface | blCapAutoResetListening | blCapVirtualProgramButton | CAPCOMMON)

    // BTN / LED sense
    #define LedOn       High
    #define BntOn       High

    // Boot LED
    #define BLedLat     F
    #define BLedBit     0

    // Download LED
    #define DLedLat     F
    #define DLedBit     1

    // Virtual program button
    #define VPBntLat    C
    #define VPBntBit    12

    // Other capabilities
    #define LISTEN_BEFORE_LOAD          2000                // no less than 2 seconds
    #define BOOTLOADER_UART             1                   // avrdude program UART
    #define BAUDRATE                    115200              // avrdude baudrate
 
    #define _CPU_NAME_                  "32MX340F512H"
    #define VEND                        vendDigilent
    #define PROD                        prodCerebotMX3cK512
    #define F_CPU                       80000000UL
    #define F_PBUS                      F_CPU

    #define FLASH_BYTES                 0x80000         // 512K   
    #define FLASH_PAGE_SIZE             4096
    #define LoadFlashWaitStates()       (CHECON = 2)        // 0 for 0-30Mhz, 1 for 31-60Mhz, 2 for 61-80Mhz

//************************************************************************
#elif defined(_BOARD_CEREBOT_32MX4_)
 
#if defined(PUT_CONFIG_BITS_HERE)

    //* Oscillator Settings
    #pragma config FNOSC    = PRIPLL                                // Oscillator selection
    #pragma config POSCMOD  = XT                                    // Primary oscillator mode
    #pragma config FPLLIDIV = DIV_2                                 // PLL input divider
    #pragma config FPLLMUL  = MUL_20                                // PLL multiplier
    #pragma config FPLLODIV = DIV_1                                 // PLL output divider
    #pragma config FPBDIV   = DIV_1                                 // Peripheral bus clock divider
    #pragma config FSOSCEN  = ON                                    // Secondary oscillator enable
    
    //* Clock control settings
    #pragma config IESO     = OFF                                   // Internal/external clock switchover
    #pragma config FCKSM    = CSECME                                // Clock switching (CSx)/Clock monitor (CMx)
    #pragma config OSCIOFNC = OFF                                   // Clock output on OSCO pin enable
    
    //* USB Settings
    #pragma config UPLLEN   = ON                                    // USB PLL enable
    #pragma config UPLLIDIV = DIV_2                                 // USB PLL input divider
    
    //* Other Peripheral Device settings
    #pragma config FWDTEN   = OFF                                   // Watchdog timer enable
    #pragma config WDTPS    = PS1024                                // Watchdog timer postscaler
    
    //* Code Protection settings
    #pragma config CP       = OFF                                   // Code protection
    #pragma config BWP      = OFF                                   // Boot flash write protect
    #pragma config PWP      = OFF                                   // Program flash write protect
    
    //* Debug settings
    #pragma config ICESEL   = ICS_PGx2                              // ICE pin selection
#endif
    
    #define CAPABILITIES    (blCapBootLED | blCapDownloadLED | blCapUARTInterface | blCapProgramButton | blCapVirtualProgramButton | CAPCOMMON)

    // BTN / LED sense
    #define LedOn       High
    #define BntOn       High

    // Boot LED
    #define BLedLat     B
    #define BLedBit     10

    // Download LED
    #define DLedLat     B
    #define DLedBit     11

    // Virtual program button
    #define VPBntLat    C
    #define VPBntBit    12

    // Program button
    #define PBntPort    A
    #define PBntBit     6

     // Other capabilities
    #define BOOTLOADER_UART             1                   // avrdude program UART
    #define BAUDRATE                                115200              

    #define _CPU_NAME_                  "32MX460F512L"
    #define VEND                        vendDigilent
    #define PROD                        prodCerebot32MX4
    #define F_CPU                       80000000UL
    #define F_PBUS                      F_CPU

    #define FLASH_BYTES                 0x80000                 // 512K
    #define FLASH_PAGE_SIZE             4096
    #define LoadFlashWaitStates()       (CHECON = 2)            // 0 for 0-30Mhz, 1 for 31-60Mhz, 2 for 61-80Mhz

//************************************************************************
#elif defined(_BOARD_CEREBOT_32MX4_USB_)
 
#if defined(PUT_CONFIG_BITS_HERE)

    //* Oscillator Settings
    #pragma config FNOSC    = PRIPLL                                // Oscillator selection
    #pragma config POSCMOD  = XT                                    // Primary oscillator mode
    #pragma config FPLLIDIV = DIV_2                                 // PLL input divider
    #pragma config FPLLMUL  = MUL_20                                // PLL multiplier
    #pragma config FPLLODIV = DIV_1                                 // PLL output divider
    #pragma config FPBDIV   = DIV_1                                 // Peripheral bus clock divider
    #pragma config FSOSCEN  = ON                                    // Secondary oscillator enable
    
    //* Clock control settings
    #pragma config IESO     = OFF                                   // Internal/external clock switchover
    #pragma config FCKSM    = CSECME                                // Clock switching (CSx)/Clock monitor (CMx)
    #pragma config OSCIOFNC = OFF                                   // Clock output on OSCO pin enable
    
    //* USB Settings
    #pragma config UPLLEN   = ON                                    // USB PLL enable
    #pragma config UPLLIDIV = DIV_2                                 // USB PLL input divider
    
    //* Other Peripheral Device settings
    #pragma config FWDTEN   = OFF                                   // Watchdog timer enable
    #pragma config WDTPS    = PS1024                                // Watchdog timer postscaler
    
    //* Code Protection settings
    #pragma config CP       = OFF                                   // Code protection
    #pragma config BWP      = OFF                                   // Boot flash write protect
    #pragma config PWP      = OFF                                   // Program flash write protect
    
    //* Debug settings
    #pragma config ICESEL   = ICS_PGx2                              // ICE pin selection
#endif
    
    #define CAPABILITIES    (blCapBootLED | blCapDownloadLED | blCapUSBInterface | blCapProgramButton | blCapVirtualProgramButton | CAPCOMMON)

    // BTN / LED sense
    #define LedOn       High
    #define BntOn       High

    // Boot LED
    #define BLedLat     B
    #define BLedBit     10

    // Download LED
    #define DLedLat     B
    #define DLedBit     11

    // Virtual program button
    #define VPBntLat    C
    #define VPBntBit    12

    // Program button
    #define PBntPort    A
    #define PBntBit     6

    #define _CPU_NAME_                  "32MX460F512L"
    #define VEND                        vendDigilent
    #define PROD                        prodCerebot32MX4
    #define F_CPU                       80000000UL
    #define F_PBUS                      F_CPU

    #define FLASH_BYTES                 0x80000                     // 512K
    #define FLASH_PAGE_SIZE             4096
    #define LoadFlashWaitStates()       (CHECON = 2)                // 0 for 0-30Mhz, 1 for 31-60Mhz, 2 for 61-80Mhz

//************************************************************************
#elif defined(_BOARD_CEREBOT_MX4CK_)
 
#if defined(PUT_CONFIG_BITS_HERE)

    //* Oscillator Settings
    #pragma config FNOSC    = PRIPLL                                // Oscillator selection
    #pragma config POSCMOD  = XT                                    // Primary oscillator mode
    #pragma config FPLLIDIV = DIV_2                                 // PLL input divider
    #pragma config FPLLMUL  = MUL_20                                // PLL multiplier
    #pragma config FPLLODIV = DIV_1                                 // PLL output divider
    #pragma config FPBDIV   = DIV_1                                 // Peripheral bus clock divider
    #pragma config FSOSCEN  = ON                                    // Secondary oscillator enable
    
    //* Clock control settings
    #pragma config IESO     = OFF                                   // Internal/external clock switchover
    #pragma config FCKSM    = CSECME                                // Clock switching (CSx)/Clock monitor (CMx)
    #pragma config OSCIOFNC = OFF                                   // Clock output on OSCO pin enable
    
    //* USB Settings
    #pragma config UPLLEN   = ON                                    // USB PLL enable
    #pragma config UPLLIDIV = DIV_2                                 // USB PLL input divider
    
    //* Other Peripheral Device settings
    #pragma config FWDTEN   = OFF                                   // Watchdog timer enable
    #pragma config WDTPS    = PS1024                                // Watchdog timer postscaler
    
    //* Code Protection settings
    #pragma config CP       = OFF                                   // Code protection
    #pragma config BWP      = OFF                                   // Boot flash write protect
    #pragma config PWP      = OFF                                   // Program flash write protect
    
    //* Debug settings
    #pragma config ICESEL   = ICS_PGx2                              // ICE pin selection
#endif
    
    #define CAPABILITIES    (blCapBootLED | blCapDownloadLED | blCapUARTInterface | blCapAutoResetListening | blCapVirtualProgramButton | CAPCOMMON)

    // BTN / LED sense
    #define LedOn       High
    #define BntOn       High

    // Boot LED
    #define BLedLat     B
    #define BLedBit     10

    // Download LED
    #define DLedLat     B
    #define DLedBit     11

    // Virtual program button
    #define VPBntLat    C
    #define VPBntBit    12

    // Other capabilities
    #define LISTEN_BEFORE_LOAD          2000                // no less than 2 seconds
    #define BOOTLOADER_UART             1                   // avrdude program UART
    #define BAUDRATE                    115200              // avrdude baudrate

    #define _CPU_NAME_                  "32MX460F512L"
    #define VEND                        vendDigilent
    #define PROD                        prodCerebotMX4cK
    #define F_CPU                       80000000UL
    #define F_PBUS                      F_CPU

    #define FLASH_BYTES                 0x80000                 // 512K
    #define FLASH_PAGE_SIZE             4096
    #define LoadFlashWaitStates()       (CHECON = 2)            // 0 for 0-30Mhz, 1 for 31-60Mhz, 2 for 61-80Mhz

//************************************************************************
#elif defined(_BOARD_UBW32_MX460_USB_)

#if defined(PUT_CONFIG_BITS_HERE)

    //*    Oscillator Settings
    #pragma config FNOSC        = PRIPLL                            // Oscillator selection
    #pragma config POSCMOD      = XT                                // Primary oscillator mode
    #pragma config FPLLIDIV     = DIV_2                             // PLL input divider
    #pragma config FPLLMUL      = MUL_20                            // PLL multiplier
    #pragma config FPLLODIV     = DIV_1                             // PLL output divider
    #pragma config FPBDIV       = DIV_1                             // Peripheral bus clock divider
    #pragma config FSOSCEN      = OFF                               // Secondary oscillator enable

    //*    Clock control settings
    #pragma config IESO         = ON                                // Internal/external clock switchover
    #pragma config FCKSM        = CSDCMD                            // Clock switching (CSx)/Clock monitor (CMx)
    #pragma config OSCIOFNC     = OFF                               // Clock output on OSCO pin enable

    //*    Other Peripheral Device settings
    #pragma config FWDTEN       = OFF                               // Watchdog timer enable
    #pragma config WDTPS        = PS1024                            // Watchdog timer postscaler

    //*    Code Protection settings
    #pragma config CP           = OFF                               // Code protection
    #pragma config BWP          = OFF                               // Boot flash write protect
    #pragma config PWP          = OFF                               // Program flash write protect

    //*    Debug settings
    #pragma config ICESEL       = ICS_PGx2                          // ICE pin selection

    //*    USB Settings
    #pragma config UPLLEN       = ON                                // USB PLL enable
    #pragma config UPLLIDIV     = DIV_2                             // USB PLL input divider
#endif

    #define CAPABILITIES    (blCapBootLED | blCapDownloadLED | blCapUSBInterface | blCapProgramButton | blCapVirtualProgramButton | CAPCOMMON)

    // BTN / LED sense
    #define LedOn       High
    #define BntOn       Low

    // Boot LED
    #define BLedLat     E
    #define BLedBit     3

    // Download LED
    #define DLedLat     E
    #define DLedBit     2

    // Virtual program button
    #define VPBntLat    E
    #define VPBntBit    7

    // Program button
    #define PBntPort    E
    #define PBntBit     7

    #define _CPU_NAME_                  "32MX460F512L"
    #define VEND                        vendSchmalzHausLLC
    #define PROD                        prodUBW32MX460
    #define F_CPU                       80000000UL
    #define F_PBUS                      F_CPU

    #define FLASH_BYTES                 0x80000                     // 512K
    #define FLASH_PAGE_SIZE             4096
    #define LoadFlashWaitStates()       (CHECON = 2)                // 0 for 0-30Mhz, 1 for 31-60Mhz, 2 for 61-80Mhz

//************************************************************************
#elif defined(_BOARD_CHIPKIT_WF32_)

#if defined(PUT_CONFIG_BITS_HERE)

    //*    Oscillator Settings
    #pragma config FNOSC        = PRIPLL                            // Oscillator selection
    #pragma config POSCMOD      = XT                                // Primary oscillator mode
    #pragma config FPLLIDIV     = DIV_2                             // PLL input divider
    #pragma config FPLLMUL      = MUL_20                            // PLL multiplier
    #pragma config FPLLODIV     = DIV_1                             // PLL output divider
    #pragma config FPBDIV       = DIV_1                             // Peripheral bus clock divider
    #pragma config FSOSCEN      = OFF                               // Secondary oscillator enable

    //*    Clock control settings
    #pragma config IESO         = OFF                               // Internal/external clock switchover
    #pragma config FCKSM        = CSDCMD                            // Clock switching (CSx)/Clock monitor (CMx)
    #pragma config OSCIOFNC     = OFF                               // Clock output on OSCO pin enable

    //*    Other Peripheral Device settings
    #pragma config FWDTEN       = OFF                               // Watchdog timer enable
    #pragma config WDTPS        = PS1024                            // Watchdog timer postscaler

    //*    Code Protection settings
    #pragma config CP           = OFF                               // Code protection
    #pragma config BWP          = OFF                               // Boot flash write protect
    #pragma config PWP          = OFF                               // Program flash write protect

    //*    Debug settings
    #pragma config ICESEL       = ICS_PGx2                          // ICE pin selection

    //*    Other Peripheral Device settings
    #pragma config FSRSSEL      = PRIORITY_7                        // SRS interrupt priority
//    #pragma config FCANIO       = OFF                               // Standard/alternate CAN pin select (OFF=Alt)
    #pragma config FETHIO       = ON                                // Standard/alternate ETH pin select (OFF=Alt)
    #pragma config FMIIEN       = OFF                               // MII/RMII select (OFF=RMII)

    //*    USB Settings
    #pragma config UPLLEN       = ON                                // USB PLL enable
    #pragma config UPLLIDIV     = DIV_2                             // USB PLL input divider
    #pragma config FVBUSONIO    = OFF                               // VBUS pin control
    #pragma config FUSBIDIO     = OFF                               // USBID pin control
#endif

    #define CAPABILITIES    (blCapBootLED | blCapDownloadLED | blCapUARTInterface | blCapAutoResetListening | blCapVirtualProgramButton | CAPCOMMON)

    // BTN / LED sense
    #define LedOn       High
    #define BntOn       High

    // Boot LED
    #define BLedLat     G
    #define BLedBit     6

    // Download LED
    #define DLedLat     F
    #define DLedBit     0

    // Virtual program button
    #define VPBntLat    C
    #define VPBntBit    12

    // Other capabilities
    #define LISTEN_BEFORE_LOAD          2000                // no less than 2 seconds
    #define BOOTLOADER_UART             1                   // avrdude program UART
    #define BAUDRATE                    115200              // avrdude baudrate

    #define _CPU_NAME_                  "32MX695F512L"
    #define VEND                        vendDigilent
    #define PROD                        prodChipKITWF32
    #define F_CPU                       80000000UL
    #define F_PBUS                      F_CPU

    #define FLASH_BYTES                 0x80000                     // 512K
    #define FLASH_PAGE_SIZE             4096
    #define LoadFlashWaitStates()       (CHECON = 2)                // 0 for 0-30Mhz, 1 for 31-60Mhz, 2 for 61-80Mhz

//************************************************************************
#elif defined(_BOARD_CHIPKIT_ZUNO_)

#if defined(PUT_CONFIG_BITS_HERE)

     //*    Oscillator Settings
    // works with proper timing
    #pragma config POSCMOD      = EC                                // External Clock
//    #pragma config POSCMOD      = HS                                // Crystal

    #pragma config FPLLIDIV     = DIV_3                             // 8 MHz
    #pragma config FPLLICLK     = PLL_POSC                          // 8MHz Posc

    #pragma config FNOSC        = SPLL                              // Oscillator selection
    #pragma config FPLLMULT     = MUL_50                            // 400 MHz
    #pragma config FPLLODIV     = DIV_2                             // 200 MHz or 80 MHz, depending

    #pragma config FPLLRNG      = RANGE_5_10_MHZ                    // 5-10Mhz
    #pragma config FSOSCEN      = OFF                               // Secondary oscillator enable
    #pragma config UPLLFSEL     = FREQ_24MHZ                        // USB PLL Input Frequency Selection (USB PLL input is 24 MHz)

    //*    Clock control settings
    #pragma config IESO         = ON                                // Internal/external clock switchover
    #pragma config FCKSM        = CSDCMD                            // Clock switching (CSx)/Clock monitor (CMx)
    #pragma config OSCIOFNC     = OFF                               // Clock output on OSCO pin enable

    //*    Other Peripheral Device settings
    #pragma config FWDTEN       = OFF                               // Watchdog timer enable
    #pragma config WDTPS        = PS1048576                         // Watchdog timer postscaler
    #pragma config WDTSPGM      = STOP                              // Watchdog Timer Stop During Flash Programming (WDT stops during Flash programming)
    #pragma config WINDIS       = NORMAL          // Watchdog Timer Window Mode (Watchdog Timer is in non-Window mode)
    #pragma config FWDTWINSZ    = WINSZ_25     // Watchdog Timer Window Size (Window size is 25%)
    #pragma config FDMTEN       = OFF             // Deadman Timer Enable (Deadman Timer is disabled)

    //*    Code Protection settings
    #pragma config CP           = OFF                               // Code protection

    //*    Debug settings
//    #pragma config DEBUG       = ON                             // turn debugging on
    #pragma config ICESEL       = ICS_PGx2                          // ICE pin selection

    #pragma config FETHIO       = ON                                // Standard/alternate ETH pin select (OFF=Alt)
    #pragma config FMIIEN       = OFF                               // MII/RMII select (OFF=RMII)

    #pragma config BOOTISA  = MIPS32

    //*    USB Settings
    #pragma config UPLLEN       = ON                                // USB PLL enable
//    #pragma config UPLLIDIV     = DIV_2                             // USB PLL input divider
//    #pragma config FVBUSONIO    = OFF                               // VBUS pin control
    #pragma config FUSBIDIO     = OFF                               // USBID pin control

    #pragma config DMTCNT       = 0

//#pragma config PGL1WAY  = OFF             // Permission Group Lock One Way Configuration (Allow only one reconfiguration)
//#pragma config PMDL1WAY = OFF           // Peripheral Module Disable Configuration (Allow only one reconfiguration)
//#pragma config IOL1WAY  = OFF             // Peripheral Pin Select Configuration (Allow only one reconfiguration)
//#pragma config DMTINTV  = WIN_127_128    // DMT Count Window Interval (Window/Interval value is 127/128 counter value)
//#pragma config EJTAGBEN = NORMAL
//#pragma config DBGPER   = PG_ALL
//#pragma config FSLEEP   = OFF
//#pragma config FECCCON  = OFF_UNLOCKED
//#pragma config TRCEN    = OFF

#endif

    #define CAPABILITIES    (blCapBootLED | blCapDownloadLED | blCapUARTInterface | blCapAutoResetListening | blCapVirtualProgramButton | CAPCOMMON)

    // BTN / LED sense
    #define LedOn       High
    #define BntOn       High

    // Boot LED
    #define BLedLat     B
    #define BLedBit     14

    // Download LED
    #define DLedLat     B
    #define DLedBit     15

    // Virtual program button
    #define VPBntLat    C
    #define VPBntBit    12

    // Other capabilities
    #define LISTEN_BEFORE_LOAD          2000                // no less than 2 seconds
    #define BOOTLOADER_UART             1                   // avrdude program UART
    #define BAUDRATE                    115200              // avrdude baudrate
    #define UARTMapRX()                 (U1RXR = 0b0100)    // RPF1 -> U1RX
    #define UARTMapTX()                 (RPF0R = 0b0001)    // RF0 -> U1TX

    #define _CPU_NAME_                  "PIC32MZ2048ECG"
    #define VEND                        vendDigilent
    #define PROD                        prodChipKITzUno
    #define F_CPU                       200000000UL
    #define F_PBUS                      (F_CPU / (PB2DIVbits.PBDIV + 1))

    #define FLASH_BYTES                 0x200000                    // 2MB
    #define FLASH_PAGE_SIZE             0x4000                      // 16K

//************************************************************************
#elif defined(_BOARD_CHIPKIT_WIFIRE_)

#if defined(PUT_CONFIG_BITS_HERE)

     //*    Oscillator Settings
    // works with proper timing
    #pragma config POSCMOD      = EC                                // External Clock
//    #pragma config POSCMOD      = HS                                // Crystal

    #pragma config FPLLIDIV     = DIV_3                             // 8 MHz
    #pragma config FPLLICLK     = PLL_POSC                          // 8MHz Posc

    #pragma config FNOSC        = SPLL                              // Oscillator selection
    #pragma config FPLLMULT     = MUL_50                            // 400 MHz
    #pragma config FPLLODIV     = DIV_2                             // 200 MHz or 80 MHz, depending

    #pragma config FPLLRNG      = RANGE_5_10_MHZ                    // 5-10Mhz
    #pragma config FSOSCEN      = OFF                               // Secondary oscillator enable
    #pragma config UPLLFSEL     = FREQ_24MHZ                        // USB PLL Input Frequency Selection (USB PLL input is 24 MHz)

    //*    Clock control settings
    #pragma config IESO         = ON                                // Internal/external clock switchover
    #pragma config FCKSM        = CSDCMD                            // Clock switching (CSx)/Clock monitor (CMx)
    #pragma config OSCIOFNC     = OFF                               // Clock output on OSCO pin enable

    //*    Other Peripheral Device settings
    #pragma config FWDTEN       = OFF                               // Watchdog timer enable
    #pragma config WDTPS        = PS1048576                         // Watchdog timer postscaler
    #pragma config WDTSPGM      = STOP                              // Watchdog Timer Stop During Flash Programming (WDT stops during Flash programming)
    #pragma config WINDIS       = NORMAL                            // Watchdog Timer Window Mode (Watchdog Timer is in non-Window mode)
    #pragma config FWDTWINSZ    = WINSZ_25                          // Watchdog Timer Window Size (Window size is 25%)
    #pragma config FDMTEN       = OFF                               // Deadman Timer Enable (Deadman Timer is disabled)

    //*    Code Protection settings
    #pragma config CP           = OFF                               // Code protection

    //*    Debug settings
//    #pragma config DEBUG       = ON                               // turn debugging on
    #pragma config ICESEL       = ICS_PGx2                          // ICE pin selection

    #pragma config FETHIO       = ON                                // Standard/alternate ETH pin select (OFF=Alt)
    #pragma config FMIIEN       = OFF                               // MII/RMII select (OFF=RMII)

    #pragma config BOOTISA  = MIPS32

    //*    USB Settings
    #pragma config UPLLEN       = ON                                // USB PLL enable
    #pragma config FUSBIDIO     = OFF                               // USBID pin control

    #pragma config DMTCNT       = 0

//#pragma config PGL1WAY  = OFF             // Permission Group Lock One Way Configuration (Allow only one reconfiguration)
//#pragma config PMDL1WAY = OFF             // Peripheral Module Disable Configuration (Allow only one reconfiguration)
//#pragma config IOL1WAY  = OFF             // Peripheral Pin Select Configuration (Allow only one reconfiguration)
//#pragma config DMTINTV  = WIN_127_128     // DMT Count Window Interval (Window/Interval value is 127/128 counter value)
//#pragma config EJTAGBEN = NORMAL
//#pragma config DBGPER   = PG_ALL
//#pragma config FSLEEP   = OFF
//#pragma config FECCCON  = OFF_UNLOCKED
//#pragma config TRCEN    = OFF

#endif

    #define CAPABILITIES    (blCapBootLED | blCapDownloadLED | blCapUARTInterface | blCapAutoResetListening | blCapVirtualProgramButton | CAPCOMMON)

    // BTN / LED sense
    #define LedOn       High
    #define BntOn       High

    // Boot LED
    #define BLedLat     G
    #define BLedBit     6

    // Download LED
    #define DLedLat     D
    #define DLedBit     4

    // Virtual program button
    #define VPBntLat    C
    #define VPBntBit    12

    // Other capabilities
    #define LISTEN_BEFORE_LOAD          2000                // no less than 2 seconds
    #define BOOTLOADER_UART             4                   // avrdude program UART
    #define BAUDRATE                    115200              // avrdude baudrate
    #define UARTMapRX()                 (U4RXR = 0b1011)    // RPF2 -> U4RX
    #define UARTMapTX()                 (RPF8R = 0b0010)    // RF8 -> U4TX

    #define _CPU_NAME_                  "PIC32MZ2048ECG"
    #define VEND                        vendDigilent
    #define PROD                        prodChipKITWiFire
    #define F_CPU                       200000000UL
    #define F_PBUS                      (F_CPU / (PB2DIVbits.PBDIV + 1))

    #define FLASH_BYTES                 0x200000                    // 2MB
    #define FLASH_PAGE_SIZE             0x4000                      // 16K

//************************************************************************
#elif defined(_BOARD_CHIPKIT_MAX32_)

#if defined(PUT_CONFIG_BITS_HERE)

    //*    Oscillator Settings
    #pragma config FNOSC        = PRIPLL                            // Oscillator selection
    #pragma config POSCMOD      = XT                                // Primary oscillator mode
    #pragma config FPLLIDIV     = DIV_2                             // PLL input divider
    #pragma config FPLLMUL      = MUL_20                            // PLL multiplier
    #pragma config FPLLODIV     = DIV_1                             // PLL output divider
    #pragma config FPBDIV       = DIV_1                             // Peripheral bus clock divider
    #pragma config FSOSCEN      = OFF                               // Secondary oscillator enable

    //*    Clock control settings
    #pragma config IESO         = OFF                               // Internal/external clock switchover
    #pragma config FCKSM        = CSDCMD                            // Clock switching (CSx)/Clock monitor (CMx)
    #pragma config OSCIOFNC     = OFF                               // Clock output on OSCO pin enable

    //*    Other Peripheral Device settings
    #pragma config FWDTEN       = OFF                               // Watchdog timer enable
    #pragma config WDTPS        = PS1024                            // Watchdog timer postscaler

    //*    Code Protection settings
    #pragma config CP           = OFF                               // Code protection
    #pragma config BWP          = OFF                               // Boot flash write protect
    #pragma config PWP          = OFF                               // Program flash write protect

    //*    Debug settings
    #pragma config ICESEL       = ICS_PGx2                          // ICE pin selection

    //*    Other Peripheral Device settings
    #pragma config FSRSSEL      = PRIORITY_7                        // SRS interrupt priority
    #pragma config FCANIO       = OFF                               // Standard/alternate CAN pin select (OFF=Alt)
    #pragma config FETHIO       = ON                                // Standard/alternate ETH pin select (OFF=Alt)
    #pragma config FMIIEN       = OFF                               // MII/RMII select (OFF=RMII)

    //*    USB Settings
    #pragma config UPLLEN       = ON                                // USB PLL enable
    #pragma config UPLLIDIV     = DIV_2                             // USB PLL input divider
    #pragma config FVBUSONIO    = OFF                               // VBUS pin control
    #pragma config FUSBIDIO     = OFF                               // USBID pin control
#endif

    #define CAPABILITIES    (blCapBootLED | blCapDownloadLED | blCapUARTInterface | blCapAutoResetListening | blCapVirtualProgramButton | CAPCOMMON)

    // BTN / LED sense
    #define LedOn       High
    #define BntOn       High

    // Boot LED
    #define BLedLat     A
    #define BLedBit     3

    // Download LED
    #define DLedLat     C
    #define DLedBit     1

    // Virtual program button
    #define VPBntLat    C
    #define VPBntBit    12

    // Other capabilities
    #define LISTEN_BEFORE_LOAD          2000                // no less than 2 seconds
    #define BOOTLOADER_UART             1                   // avrdude program UART
    #define BAUDRATE                    115200              // avrdude baudrate

    #define _CPU_NAME_                  "32MX795F512L"
    #define VEND                        vendDigilent
    #define PROD                        prodChipKITMax32
    #define F_CPU                       80000000UL
    #define F_PBUS                      F_CPU

    #define FLASH_BYTES                 0x80000                     // 512K
    #define FLASH_PAGE_SIZE             4096
    #define LoadFlashWaitStates()       (CHECON = 2)                // 0 for 0-30Mhz, 1 for 31-60Mhz, 2 for 61-80Mhz

//************************************************************************
#elif defined(_BOARD_CEREBOT_32MX7_)

#if defined(PUT_CONFIG_BITS_HERE)

    //*    Oscillator Settings
    #pragma config FNOSC        = PRIPLL                            // Oscillator selection
    #pragma config POSCMOD      = XT                                // Primary oscillator mode
    #pragma config FPLLIDIV     = DIV_2                             // PLL input divider
    #pragma config FPLLMUL      = MUL_20                            // PLL multiplier
    #pragma config FPLLODIV     = DIV_1                             // PLL output divider
    #pragma config FPBDIV       = DIV_1                             // Peripheral bus clock divider
    #pragma config FSOSCEN      = OFF                               // Secondary oscillator enable

    //*    Clock control settings
    #pragma config IESO         = OFF                               // Internal/external clock switchover
    #pragma config FCKSM        = CSDCMD                            // Clock switching (CSx)/Clock monitor (CMx)
    #pragma config OSCIOFNC     = OFF                               // Clock output on OSCO pin enable

    //*    Other Peripheral Device settings
    #pragma config FWDTEN       = OFF                               // Watchdog timer enable
    #pragma config WDTPS        = PS1024                            // Watchdog timer postscaler

    //*    Code Protection settings
    #pragma config CP           = OFF                               // Code protection
    #pragma config BWP          = OFF                               // Boot flash write protect
    #pragma config PWP          = OFF                               // Program flash write protect

    //*    Debug settings
    #pragma config ICESEL       = ICS_PGx1                          // ICE pin selection

    //*    Other Peripheral Device settings
    #pragma config FSRSSEL      = PRIORITY_7                        // SRS interrupt priority
    #pragma config FCANIO       = OFF                               // Standard/alternate CAN pin select (OFF=Alt)
    #pragma config FETHIO       = ON                                // Standard/alternate ETH pin select (OFF=Alt)
    #pragma config FMIIEN       = OFF                               // MII/RMII select (OFF=RMII)

    //*    USB Settings
    #pragma config UPLLEN       = ON                                // USB PLL enable
    #pragma config UPLLIDIV     = DIV_2                             // USB PLL input divider
    #pragma config FVBUSONIO    = OFF                               // VBUS pin control
    #pragma config FUSBIDIO     = OFF                               // USBID pin control
#endif

    #define CAPABILITIES    (blCapBootLED | blCapDownloadLED | blCapUARTInterface | blCapProgramButton | blCapVirtualProgramButton | CAPCOMMON)

    // BTN / LED sense
    #define LedOn       High
    #define BntOn       High

    // Boot LED
    #define BLedLat     G
    #define BLedBit     12

    // Download LED
    #define DLedLat     G
    #define DLedBit     13

    // Virtual program button
    #define VPBntLat    C
    #define VPBntBit    12

    // Program button
    #define PBntPort    G
    #define PBntBit     6

    // Other capabilities
    #define BOOTLOADER_UART             1                   // avrdude program UART
    #define BAUDRATE                    115200              // avrdude baudrate

    #define _CPU_NAME_                  "32MX795F512L"
    #define VEND                        vendDigilent
    #define PROD                        prodCerebot32MX7
    #define F_CPU                       80000000UL
    #define F_PBUS                      F_CPU

    #define FLASH_BYTES                 0x80000                 // 512K
    #define FLASH_PAGE_SIZE             4096
    #define LoadFlashWaitStates()       (CHECON = 2)            // 0 for 0-30Mhz, 1 for 31-60Mhz, 2 for 61-80Mhz

//************************************************************************
#elif defined(_BOARD_CEREBOT_32MX7_USB_)

#if defined(PUT_CONFIG_BITS_HERE)

    //*    Oscillator Settings
    #pragma config FNOSC        = PRIPLL                            // Oscillator selection
    #pragma config POSCMOD      = XT                                // Primary oscillator mode
    #pragma config FPLLIDIV     = DIV_2                             // PLL input divider
    #pragma config FPLLMUL      = MUL_20                            // PLL multiplier
    #pragma config FPLLODIV     = DIV_1                             // PLL output divider
    #pragma config FPBDIV       = DIV_1                             // Peripheral bus clock divider
    #pragma config FSOSCEN      = OFF                               // Secondary oscillator enable

    //*    Clock control settings
    #pragma config IESO         = OFF                               // Internal/external clock switchover
    #pragma config FCKSM        = CSDCMD                            // Clock switching (CSx)/Clock monitor (CMx)
    #pragma config OSCIOFNC     = OFF                               // Clock output on OSCO pin enable

    //*    Other Peripheral Device settings
    #pragma config FWDTEN       = OFF                               // Watchdog timer enable
    #pragma config WDTPS        = PS1024                            // Watchdog timer postscaler

    //*    Code Protection settings
    #pragma config CP           = OFF                               // Code protection
    #pragma config BWP          = OFF                               // Boot flash write protect
    #pragma config PWP          = OFF                               // Program flash write protect

    //*    Debug settings
    #pragma config ICESEL       = ICS_PGx1                          // ICE pin selection

    //*    Other Peripheral Device settings
    #pragma config FSRSSEL      = PRIORITY_7                        // SRS interrupt priority
    #pragma config FCANIO       = OFF                               // Standard/alternate CAN pin select (OFF=Alt)
    #pragma config FETHIO       = ON                                // Standard/alternate ETH pin select (OFF=Alt)
    #pragma config FMIIEN       = OFF                               // MII/RMII select (OFF=RMII)

    //*    USB Settings
    #pragma config UPLLEN       = ON                                // USB PLL enable
    #pragma config UPLLIDIV     = DIV_2                             // USB PLL input divider
    #pragma config FVBUSONIO    = OFF                               // VBUS pin control
    #pragma config FUSBIDIO     = OFF                               // USBID pin control
#endif

    #define CAPABILITIES    (blCapBootLED | blCapDownloadLED | blCapUSBInterface | blCapProgramButton | blCapVirtualProgramButton | CAPCOMMON)

    // BTN / LED sense
    #define LedOn       High
    #define BntOn       High

    // Boot LED
    #define BLedLat     G
    #define BLedBit     12

    // Download LED
    #define DLedLat     G
    #define DLedBit     13

    // Virtual program button
    #define VPBntLat    C
    #define VPBntBit    12

    // Program button
    #define PBntPort    G
    #define PBntBit     6

    // Other capabilities
    #define BOOTLOADER_UART             1                   // avrdude program UART
    #define BAUDRATE                    115200              // avrdude baudrate

    #define _CPU_NAME_                  "32MX795F512L"
    #define VEND                        vendDigilent
    #define PROD                        prodCerebot32MX7
    #define F_CPU                       80000000UL
    #define F_PBUS                      F_CPU

    #define FLASH_BYTES                 0x80000                     // 512K
    #define FLASH_PAGE_SIZE             4096
    #define LoadFlashWaitStates()       (CHECON = 2)                // 0 for 0-30Mhz, 1 for 31-60Mhz, 2 for 61-80Mhz
 
//************************************************************************
#elif defined(_BOARD_CEREBOT_32MX7_USB_SPLIT_)

#if defined(PUT_CONFIG_BITS_HERE)

    //*    Oscillator Settings
    #pragma config FNOSC        = PRIPLL                            // Oscillator selection
    #pragma config POSCMOD      = XT                                // Primary oscillator mode
    #pragma config FPLLIDIV     = DIV_2                             // PLL input divider
    #pragma config FPLLMUL      = MUL_20                            // PLL multiplier
    #pragma config FPLLODIV     = DIV_1                             // PLL output divider
    #pragma config FPBDIV       = DIV_1                             // Peripheral bus clock divider
    #pragma config FSOSCEN      = OFF                               // Secondary oscillator enable

    //*    Clock control settings
    #pragma config IESO         = OFF                               // Internal/external clock switchover
    #pragma config FCKSM        = CSDCMD                            // Clock switching (CSx)/Clock monitor (CMx)
    #pragma config OSCIOFNC     = OFF                               // Clock output on OSCO pin enable

    //*    Other Peripheral Device settings
    #pragma config FWDTEN       = OFF                               // Watchdog timer enable
    #pragma config WDTPS        = PS1024                            // Watchdog timer postscaler

    //*    Code Protection settings
    #pragma config CP           = OFF                               // Code protection
    #pragma config BWP          = OFF                               // Boot flash write protect
    #pragma config PWP          = OFF                               // Program flash write protect

    //*    Debug settings
    #pragma config ICESEL       = ICS_PGx1                          // ICE pin selection

    //*    Other Peripheral Device settings
    #pragma config FSRSSEL      = PRIORITY_7                        // SRS interrupt priority
    #pragma config FCANIO       = OFF                               // Standard/alternate CAN pin select (OFF=Alt)
    #pragma config FETHIO       = ON                                // Standard/alternate ETH pin select (OFF=Alt)
    #pragma config FMIIEN       = OFF                               // MII/RMII select (OFF=RMII)

    //*    USB Settings
    #pragma config UPLLEN       = ON                                // USB PLL enable
    #pragma config UPLLIDIV     = DIV_2                             // USB PLL input divider
    #pragma config FVBUSONIO    = OFF                               // VBUS pin control
    #pragma config FUSBIDIO     = OFF                               // USBID pin control
#endif

    #define CAPABILITIES    (blCapBootLED | blCapDownloadLED | blCapUSBInterface | blCapProgramButton | blCapVirtualProgramButton | CAPCOMMON)

    // BTN / LED sense
    #define LedOn       High
    #define BntOn       High

    // Boot LED
    #define BLedLat     G
    #define BLedBit     12

    // Download LED
    #define DLedLat     G
    #define DLedBit     13

    // Virtual program button
    #define VPBntLat    C
    #define VPBntBit    12

    // Program button
    #define PBntPort    G
    #define PBntBit     6

    #define _CPU_NAME_                  "32MX795F512L"
    #define VEND                        vendDigilent
    #define PROD                        prodCerebot32MX7
    #define F_CPU                       80000000UL
    #define F_PBUS                      F_CPU

    #define FLASH_BYTES                 (0x80000-4096)              // 512K less 4K for the splitflash bootloader in program flash
    #define FLASH_PAGE_SIZE             4096
    #define LoadFlashWaitStates()       (CHECON = 2)                // 0 for 0-30Mhz, 1 for 31-60Mhz, 2 for 61-80Mhz
 
//************************************************************************
#elif defined(_BOARD_CEREBOT_MX7CK_)

#if defined(PUT_CONFIG_BITS_HERE)

    //*    Oscillator Settings
    #pragma config FNOSC        = PRIPLL                            // Oscillator selection
    #pragma config POSCMOD      = XT                                // Primary oscillator mode
    #pragma config FPLLIDIV     = DIV_2                             // PLL input divider
    #pragma config FPLLMUL      = MUL_20                            // PLL multiplier
    #pragma config FPLLODIV     = DIV_1                             // PLL output divider
    #pragma config FPBDIV       = DIV_1                             // Peripheral bus clock divider
    #pragma config FSOSCEN      = OFF                               // Secondary oscillator enable

    //*    Clock control settings
    #pragma config IESO         = OFF                               // Internal/external clock switchover
    #pragma config FCKSM        = CSDCMD                            // Clock switching (CSx)/Clock monitor (CMx)
    #pragma config OSCIOFNC     = OFF                               // Clock output on OSCO pin enable

    //*    Other Peripheral Device settings
    #pragma config FWDTEN       = OFF                               // Watchdog timer enable
    #pragma config WDTPS        = PS1024                            // Watchdog timer postscaler

    //*    Code Protection settings
    #pragma config CP           = OFF                               // Code protection
    #pragma config BWP          = OFF                               // Boot flash write protect
    #pragma config PWP          = OFF                               // Program flash write protect

    //*    Debug settings
    #pragma config ICESEL       = ICS_PGx1                          // ICE pin selection

    //*    Other Peripheral Device settings
    #pragma config FSRSSEL      = PRIORITY_7                        // SRS interrupt priority
    #pragma config FCANIO       = OFF                               // Standard/alternate CAN pin select (OFF=Alt)
    #pragma config FETHIO       = ON                                // Standard/alternate ETH pin select (OFF=Alt)
    #pragma config FMIIEN       = OFF                               // MII/RMII select (OFF=RMII)

    //*    USB Settings
    #pragma config UPLLEN       = ON                                // USB PLL enable
    #pragma config UPLLIDIV     = DIV_2                             // USB PLL input divider
    #pragma config FVBUSONIO    = OFF                               // VBUS pin control
    #pragma config FUSBIDIO     = OFF                               // USBID pin control
#endif

    #define CAPABILITIES    (blCapBootLED | blCapDownloadLED | blCapUARTInterface | blCapAutoResetListening | blCapVirtualProgramButton | CAPCOMMON)

    // BTN / LED sense
    #define LedOn       High
    #define BntOn       High

    // Boot LED
    #define BLedLat     G
    #define BLedBit     12

    // Download LED
    #define DLedLat     G
    #define DLedBit     13

    // Virtual program button
    #define VPBntLat    C
    #define VPBntBit    12

    // Other capabilities
    #define LISTEN_BEFORE_LOAD          2000                // no less than 2 seconds
    #define BOOTLOADER_UART             1                   // avrdude program UART
    #define BAUDRATE                    115200              // avrdude baudrate

    #define _CPU_NAME_                  "32MX795F512L"
    #define VEND                        vendDigilent
    #define PROD                        prodCerebotMX7cK
    #define F_CPU                       80000000UL
    #define F_PBUS                      F_CPU

    #define FLASH_BYTES                 0x80000                 // 512K
    #define FLASH_PAGE_SIZE             4096
    #define LoadFlashWaitStates()       (CHECON = 2)            // 0 for 0-30Mhz, 1 for 31-60Mhz, 2 for 61-80Mhz

//************************************************************************
#elif defined(_BOARD_UBW32_MX795_USB_)

#if defined(PUT_CONFIG_BITS_HERE)

    //*    Oscillator Settings
    #pragma config FNOSC        = PRIPLL                            // Oscillator selection
    #pragma config POSCMOD      = XT                                // Primary oscillator mode
    #pragma config FPLLIDIV     = DIV_2                             // PLL input divider
    #pragma config FPLLMUL      = MUL_20                            // PLL multiplier
    #pragma config FPLLODIV     = DIV_1                             // PLL output divider
    #pragma config FPBDIV       = DIV_1                             // Peripheral bus clock divider
    #pragma config FSOSCEN      = OFF                               // Secondary oscillator enable

    //*    Clock control settings
    #pragma config IESO         = ON                                // Internal/external clock switchover
    #pragma config FCKSM        = CSDCMD                            // Clock switching (CSx)/Clock monitor (CMx)
    #pragma config OSCIOFNC     = OFF                               // Clock output on OSCO pin enable

    //*    Other Peripheral Device settings
    #pragma config FWDTEN       = OFF                               // Watchdog timer enable
    #pragma config WDTPS        = PS1024                            // Watchdog timer postscaler

    //*    Code Protection settings
    #pragma config CP           = OFF                               // Code protection
    #pragma config BWP          = OFF                               // Boot flash write protect
    #pragma config PWP          = OFF                               // Program flash write protect

    //*    Debug settings
    #pragma config ICESEL       = ICS_PGx2                          // ICE pin selection

    //*    Other Peripheral Device settings
    #pragma config FSRSSEL      = PRIORITY_7                        // SRS interrupt priority
    #pragma config FCANIO       = OFF                               // Standard/alternate CAN pin select (OFF=Alt)
    #pragma config FETHIO       = ON                                // Standard/alternate ETH pin select (OFF=Alt)
    #pragma config FMIIEN       = OFF                               // MII/RMII select (OFF=RMII)

    //*    USB Settings
    #pragma config UPLLEN       = ON                                // USB PLL enable
    #pragma config UPLLIDIV     = DIV_2                             // USB PLL input divider
    #pragma config FVBUSONIO    = OFF                               // VBUS pin control
    #pragma config FUSBIDIO     = OFF                               // USBID pin control
#endif

    #define CAPABILITIES    (blCapBootLED | blCapDownloadLED | blCapUSBInterface | blCapProgramButton | blCapVirtualProgramButton | CAPCOMMON)

    // BTN / LED sense
    #define LedOn       High
    #define BntOn       Low

    // Boot LED
    #define BLedLat     E
    #define BLedBit     3

    // Download LED
    #define DLedLat     E
    #define DLedBit     2

    // Virtual program button
    #define VPBntLat    E
    #define VPBntBit    7

    // Program button
    #define PBntPort    E
    #define PBntBit     7

    #define _CPU_NAME_                  "32MX795F512L"
    #define VEND                        vendSchmalzHausLLC
    #define PROD                        prodUBW32MX795
    #define F_CPU                       80000000UL
    #define F_PBUS                      F_CPU

    #define FLASH_BYTES                 0x80000                     // 512K
    #define FLASH_PAGE_SIZE             4096
    #define LoadFlashWaitStates()       (CHECON = 2)                // 0 for 0-30Mhz, 1 for 31-60Mhz, 2 for 61-80Mhz

//************************************************************************
#elif defined(_BOARD_CHIPKIT_FG32_)

#if defined(PUT_CONFIG_BITS_HERE)

    //*    Oscillator Settings
    #pragma config FNOSC        = PRIPLL                            // Oscillator selection
    #pragma config POSCMOD      = XT                                // Primary oscillator mode
    #pragma config FPLLIDIV     = DIV_2                             // PLL input divider
    #pragma config FPLLMUL      = MUL_20                            // PLL multiplier
    #pragma config FPLLODIV     = DIV_1                             // PLL output divider
    #pragma config FPBDIV       = DIV_1                             // Peripheral bus clock divider
    #pragma config FSOSCEN      = OFF                               // Secondary oscillator enable

    //*    Clock control settings
    #pragma config IESO         = OFF                               // Internal/external clock switchover
    #pragma config FCKSM        = CSDCMD                            // Clock switching (CSx)/Clock monitor (CMx)
    #pragma config OSCIOFNC     = OFF                               // Clock output on OSCO pin enable

    //*    Other Peripheral Device settings
    #pragma config FWDTEN       = OFF                               // Watchdog timer enable
    #pragma config WDTPS        = PS1024                            // Watchdog timer postscaler

    //*    Code Protection settings
    #pragma config CP           = OFF                               // Code protection
    #pragma config BWP          = OFF                               // Boot flash write protect
    #pragma config PWP          = OFF                               // Program flash write protect

    //*    Debug settings
    #pragma config ICESEL       = ICS_PGx2                          // ICE pin selection

    //*    Other Peripheral Device settings
    #pragma config FSRSSEL      = PRIORITY_7                        // SRS interrupt priority
    #pragma config FCANIO       = OFF                               // Standard/alternate CAN pin select (OFF=Alt)
    #pragma config FETHIO       = ON                                // Standard/alternate ETH pin select (OFF=Alt)
    #pragma config FMIIEN       = OFF                               // MII/RMII select (OFF=RMII)

    //*    USB Settings
    #pragma config UPLLEN       = ON                                // USB PLL enable
    #pragma config UPLLIDIV     = DIV_2                             // USB PLL input divider
    #pragma config FVBUSONIO    = OFF                               // VBUS pin control
    #pragma config FUSBIDIO     = OFF                               // USBID pin control
#endif

    #define CAPABILITIES    (blCapUARTInterface | blCapAutoResetListening | blCapVirtualProgramButton | CAPCOMMON)

    // BTN / LED sense
    #define LedOn       High
    #define BntOn       High

    // Boot LED
//    #define BLedLat     A
//    #define BLedBit     3

    // Download LED
//    #define DLedLat     C
//    #define DLedBit     1

    // Virtual program button
    #define VPBntLat    C
    #define VPBntBit    12

    // Other capabilities
    #define LISTEN_BEFORE_LOAD          2000                // no less than 2 seconds
    #define BOOTLOADER_UART             1                   // avrdude program UART
    #define BAUDRATE                    115200              // avrdude baudrate

    #define _CPU_NAME_                  "32MX695F512L"
    #define VEND                        vendDigilent
    #define PROD                        prodChipKITFG32
    #define F_CPU                       80000000UL
    #define F_PBUS                      F_CPU

    #define FLASH_BYTES                 0x80000                     // 512K
    #define FLASH_PAGE_SIZE             4096
    #define LoadFlashWaitStates()       (CHECON = 2)                // 0 for 0-30Mhz, 1 for 31-60Mhz, 2 for 61-80Mhz

//************************************************************************
#elif defined(_BOARD_FUBARINO_SD_USB_)  // 32MX440F256H, SeedStudio version (after first 100) - v1.4
 
#if defined(PUT_CONFIG_BITS_HERE)

    //* Oscillator Settings
    #pragma config FNOSC    = PRIPLL                                // Oscillator selection
    #pragma config POSCMOD  = HS                                    // Primary oscillator mode
    #pragma config FPLLIDIV = DIV_2                                 // PLL input divider
    #pragma config FPLLMUL  = MUL_20                                // PLL multiplier
    #pragma config FPLLODIV = DIV_1                                 // PLL output divider
    #pragma config FPBDIV   = DIV_1                                 // Peripheral bus clock divider
    #pragma config FSOSCEN  = OFF                                   // Secondary oscillator enable
    
    //* Clock control settings
    #pragma config IESO     = OFF                                   // Internal/external clock switchover
    #pragma config FCKSM    = CSECME                                // Clock switching (CSx)/Clock monitor (CMx)
    #pragma config OSCIOFNC = OFF                                   // Clock output on OSCO pin enable
    
    //* USB Settings
    #pragma config UPLLEN   = ON                                    // USB PLL enable
    #pragma config UPLLIDIV = DIV_2                                 // USB PLL input divider
    
    //* Other Peripheral Device settings
    #pragma config FWDTEN   = OFF                                   // Watchdog timer enable
    #pragma config WDTPS    = PS1024                                // Watchdog timer postscaler
    
    //* Code Protection settings
    #pragma config CP       = OFF                                   // Code protection
    #pragma config BWP      = OFF                                   // Boot flash write protect
    #pragma config PWP      = OFF                                   // Program flash write protect
    
    //* Debug settings
    #pragma config ICESEL   = ICS_PGx2                              // ICE pin selection
#endif
    
    #define CAPABILITIES    (blCapBootLED | blCapUSBInterface | blCapProgramButton | blCapVirtualProgramButton | CAPCOMMON)

    // BTN / LED sense
    #define LedOn       High
    #define BntOn       Low

    // Boot LED
    #define BLedLat     E
    #define BLedBit     5

    // Virtual program button
    #define VPBntLat    E
    #define VPBntBit    7

    // Program button
    #define PBntPort    E
    #define PBntBit     7
 
    #define _CPU_NAME_                  "32MX440F256H"
    #define VEND                        vendFubarino
    #define PROD                        prodFubarinoSD
    #define F_CPU                       80000000UL
    #define F_PBUS                      F_CPU

    #define FLASH_BYTES                 0x40000                     // 256K
    #define FLASH_PAGE_SIZE             4096
    #define LoadFlashWaitStates()       (CHECON = 2)            // 0 for 0-30Mhz, 1 for 31-60Mhz, 2 for 61-80Mhz

//************************************************************************
#elif defined(_BOARD_FUBARINO_SD_512K_USB_) // 32MX795F512H, Microchip version (v1.5)

#if defined(PUT_CONFIG_BITS_HERE)

    //* Oscillator Settings
    #pragma config FNOSC    = PRIPLL                                // Oscillator selection
    #pragma config POSCMOD  = HS                                    // Primary oscillator mode
    #pragma config FPLLIDIV = DIV_2                                 // PLL input divider
    #pragma config FPLLMUL  = MUL_20                                // PLL multiplier
    #pragma config FPLLODIV = DIV_1                                 // PLL output divider
    #pragma config FPBDIV   = DIV_1                                 // Peripheral bus clock divider
    #pragma config FSOSCEN  = OFF                                   // Secondary oscillator enable

    //* Clock control settings
    #pragma config IESO     = OFF                                   // Internal/external clock switchover
    #pragma config FCKSM    = CSECME                                // Clock switching (CSx)/Clock monitor (CMx)
    #pragma config OSCIOFNC = OFF                                   // Clock output on OSCO pin enable

    //* USB Settings
    #pragma config UPLLEN   = ON                                    // USB PLL enable
    #pragma config UPLLIDIV = DIV_2                                 // USB PLL input divider
    #pragma config FUSBIDIO = OFF									// USB USID pin controlled by port function
    #pragma config FVBUSONIO = OFF									// USB VBUSON pin controlled by port function

    //* Other Peripheral Device settings
    #pragma config FWDTEN   = OFF                                   // Watchdog timer enable
    #pragma config WDTPS    = PS1024                                // Watchdog timer postscaler

    //* Code Protection settings
    #pragma config CP       = OFF                                   // Code protection
    #pragma config BWP      = OFF                                   // Boot flash write protect
    #pragma config PWP      = OFF                                   // Program flash write protect

    //* Debug settings
    #pragma config ICESEL   = ICS_PGx2                              // ICE pin selection
#endif

    #define CAPABILITIES    (blCapBootLED | blCapUSBInterface | blCapProgramButton | blCapVirtualProgramButton | CAPCOMMON)

    // BTN / LED sense
    #define LedOn       High
    #define BntOn       Low

    // Boot LED
    #define BLedLat     E
    #define BLedBit     5

    // Virtual program button
    #define VPBntLat    E
    #define VPBntBit    7

    // Program button
    #define PBntPort    E
    #define PBntBit     7
 
    #define _CPU_NAME_                  "32MX795F512H"
    #define VEND                        vendFubarino
    #define PROD                        prodFubarinoSD_512K
    #define F_CPU                       80000000UL
    #define F_PBUS                      F_CPU

    #define FLASH_BYTES                 0x80000                     // 512K
    #define FLASH_PAGE_SIZE             4096
    #define LoadFlashWaitStates()       (CHECON = 2)            // 0 for 0-30Mhz, 1 for 31-60Mhz, 2 for 61-80Mhz

//************************************************************************
#elif defined(_BOARD_FUBARINO_MINI_USB_)
 
#if defined(PUT_CONFIG_BITS_HERE)

    //* Oscillator Settings
    #pragma config FNOSC    = PRIPLL                                // Oscillator selection
    #pragma config POSCMOD  = XT                                    // Primary oscillator mode
    #pragma config FPLLIDIV = DIV_2                                 // PLL input divider
    #pragma config FPLLMUL  = MUL_20                                // PLL multiplier
    #pragma config FPLLODIV = DIV_2                                 // PLL output divider
    #pragma config FPBDIV   = DIV_1                                 // Peripheral bus clock divider
    #pragma config FSOSCEN  = OFF                                   // Secondary oscillator enable
    
    //* Clock control settings
    #pragma config IESO     = OFF                                   // Internal/external clock switchover
    #pragma config FCKSM    = CSECME                                // Clock switching (CSx)/Clock monitor (CMx)
    #pragma config OSCIOFNC = OFF                                   // Clock output on OSCO pin enable
    
    //* USB Settings
    #pragma config UPLLEN   = ON                                    // USB PLL enable
    #pragma config UPLLIDIV = DIV_2                                 // USB PLL input divider
    #pragma config FUSBIDIO = OFF									// USB USID pin controlled by port function
    #pragma config FVBUSONIO = OFF									// USB VBUSON pin controlled by port function
    
    //* Other Peripheral Device settings
    #pragma config FWDTEN   = OFF                                   // Watchdog timer enable
    #pragma config WDTPS    = PS1024                                // Watchdog timer postscaler
    #pragma config WINDIS   = OFF
    #pragma config JTAGEN   = OFF                          			// JTAG port disabled
    
    //* Code Protection settings
    #pragma config CP       = OFF                                   // Code protection
    #pragma config BWP      = OFF                                   // Boot flash write protect
    #pragma config PWP      = OFF                                   // Program flash write protect
    
    //*    Debug settings
    #pragma config ICESEL   = ICS_PGx1                      		// ICE/ICD Comm Channel Select
    //#pragma config DEBUG    = ON                          		// DO NOT SET THIS CONFIG BIT, it will break debugging

    #pragma config PMDL1WAY = OFF                           		// Allow multiple reconfigurations
    #pragma config IOL1WAY  = OFF                           		// Allow multiple reconfigurations
#endif
    
    #define CAPABILITIES    (blCapBootLED | blCapSplitFlashBootloader | blCapUSBInterface | blCapProgramButton | blCapVirtualProgramButton | CAPCOMMON)

    // BTN / LED sense
    #define LedOn       High
    #define BntOn       Low

    // Boot LED
    #define BLedLat     A
    #define BLedBit     10

    // Virtual program button
    #define VPBntLat    A
    #define VPBntBit    8

    // Program button
    #define PBntPort    A
    #define PBntBit     8
  
    #define _CPU_NAME_                  "32MX250F128D"
    #define VEND                        vendFubarino
    #define PROD                        prodFubarinoMini
    #define F_CPU                       40000000UL
    #define F_PBUS                      F_CPU

    #define FLASH_BYTES                 (0x20000-0x1000)		    // Leave room one flash block (for bootloader!)
    #define FLASH_PAGE_SIZE             1024						// In bytes

//************************************************************************
#elif defined(_BOARD_FUBARINO_MINI_USB_48MHZ_)
 
#if defined(PUT_CONFIG_BITS_HERE)

    //* Oscillator Settings
    #pragma config FNOSC    = PRIPLL                                // Oscillator selection
    #pragma config POSCMOD  = XT                                    // Primary oscillator mode
    #pragma config FPLLIDIV = DIV_2                                 // PLL input divider
    #pragma config FPLLMUL  = MUL_24                                // PLL multiplier
    #pragma config FPLLODIV = DIV_2                                 // PLL output divider
    #pragma config FPBDIV   = DIV_1                                 // Peripheral bus clock divider
    #pragma config FSOSCEN  = OFF                                   // Secondary oscillator enable
    
    //* Clock control settings
    #pragma config IESO     = OFF                                   // Internal/external clock switchover
    #pragma config FCKSM    = CSECME                                // Clock switching (CSx)/Clock monitor (CMx)
    #pragma config OSCIOFNC = OFF                                   // Clock output on OSCO pin enable
    
    //* USB Settings
    #pragma config UPLLEN   = ON                                    // USB PLL enable
    #pragma config UPLLIDIV = DIV_2                                 // USB PLL input divider
    #pragma config FUSBIDIO = OFF									// USB USID pin controlled by port function
    #pragma config FVBUSONIO = OFF									// USB VBUSON pin controlled by port function
    
    //* Other Peripheral Device settings
    #pragma config FWDTEN   = OFF                                   // Watchdog timer enable
    #pragma config WDTPS    = PS1024                                // Watchdog timer postscaler
    #pragma config WINDIS   = OFF
    #pragma config JTAGEN   = OFF                          			// JTAG port disabled
    
    //* Code Protection settings
    #pragma config CP       = OFF                                   // Code protection
    #pragma config BWP      = OFF                                   // Boot flash write protect
    #pragma config PWP      = OFF                                   // Program flash write protect
    
    //*    Debug settings
    #pragma config ICESEL   = ICS_PGx1                      		// ICE/ICD Comm Channel Select
    //#pragma config DEBUG    = ON                          		// DO NOT SET THIS CONFIG BIT, it will break debugging

    #pragma config PMDL1WAY = OFF                           		// Allow multiple reconfigurations
    #pragma config IOL1WAY  = OFF                           		// Allow multiple reconfigurations
#endif
    
    #define CAPABILITIES    (blCapBootLED | blCapSplitFlashBootloader | blCapUSBInterface | blCapProgramButton | blCapVirtualProgramButton | CAPCOMMON)

    // BTN / LED sense
    #define LedOn       High
    #define BntOn       Low

    // Boot LED
    #define BLedLat     A
    #define BLedBit     10


    // Virtual program button
    #define VPBntLat    A
    #define VPBntBit    8

    // Program button
    #define PBntPort    A
    #define PBntBit     8
  
    #define _CPU_NAME_                  "32MX250F128D"
    #define VEND                        vendFubarino
    #define PROD                        prodFubarinoMini48MHz
    #define F_CPU                       48000000UL
    #define F_PBUS                      F_CPU

    #define FLASH_BYTES                 (0x20000-0x1000)		    // Leave room one flash block (for bootloader!)
    #define FLASH_PAGE_SIZE             1024						// In bytes

//************************************************************************
#elif defined(_BOARD_FUBARINO_MINI_USB_50MHZ_)
// This is a Fubarino Mini with a 20MHz crystal
 
#if defined(PUT_CONFIG_BITS_HERE)

    //* Oscillator Settings
    #pragma config FNOSC    = PRIPLL                                // Oscillator selection
    #pragma config POSCMOD  = XT                                    // Primary oscillator mode
    #pragma config FPLLIDIV = DIV_4                                 // PLL input divider
    #pragma config FPLLMUL  = MUL_20                                // PLL multiplier
    #pragma config FPLLODIV = DIV_2                                 // PLL output divider
    #pragma config FPBDIV   = DIV_1                                 // Peripheral bus clock divider
    #pragma config FSOSCEN  = OFF                                   // Secondary oscillator enable
    
    //* Clock control settings
    #pragma config IESO     = OFF                                   // Internal/external clock switchover
    #pragma config FCKSM    = CSECME                                // Clock switching (CSx)/Clock monitor (CMx)
    #pragma config OSCIOFNC = OFF                                   // Clock output on OSCO pin enable
    
    //* USB Settings
    #pragma config UPLLEN   = ON                                    // USB PLL enable
    #pragma config UPLLIDIV = DIV_5                                 // USB PLL input divider
    #pragma config FUSBIDIO = OFF									// USB USID pin controlled by port function
    #pragma config FVBUSONIO = OFF									// USB VBUSON pin controlled by port function
    
    //* Other Peripheral Device settings
    #pragma config FWDTEN   = OFF                                   // Watchdog timer enable
    #pragma config WDTPS    = PS1024                                // Watchdog timer postscaler
    #pragma config WINDIS   = OFF
    #pragma config JTAGEN   = OFF                          			// JTAG port disabled
    
    //* Code Protection settings
    #pragma config CP       = OFF                                   // Code protection
    #pragma config BWP      = OFF                                   // Boot flash write protect
    #pragma config PWP      = OFF                                   // Program flash write protect
    
    //*    Debug settings
    #pragma config ICESEL   = ICS_PGx1                      		// ICE/ICD Comm Channel Select
    //#pragma config DEBUG    = ON                          		// DO NOT SET THIS CONFIG BIT, it will break debugging

    #pragma config PMDL1WAY = OFF                           		// Allow multiple reconfigurations
    #pragma config IOL1WAY  = OFF                           		// Allow multiple reconfigurations
#endif
    
    #define CAPABILITIES    (blCapBootLED | blCapSplitFlashBootloader | blCapUSBInterface | blCapProgramButton | blCapVirtualProgramButton | CAPCOMMON)

    // BTN / LED sense
    #define LedOn       High
    #define BntOn       Low

    // Boot LED
    #define BLedLat     A
    #define BLedBit     10

    // Virtual program button
    #define VPBntLat    A
    #define VPBntBit    8

    // Program button
    #define PBntPort    A
    #define PBntBit     8
 
    #define _CPU_NAME_                  "32MX250F128D"
    #define VEND                        vendFubarino
    #define PROD                        prodFubarinoMini50MHz
    #define F_CPU                       50000000UL
    #define F_PBUS                      F_CPU

    #define FLASH_BYTES                 (0x20000-0x1000)		    // Leave room one flash block (for bootloader!)
    #define FLASH_PAGE_SIZE             1024						// In bytes

//************************************************************************
#elif defined(_BOARD_OLIMEX_PIC32_PINGUINO_)
 
#if defined(PUT_CONFIG_BITS_HERE)

    //* Oscillator Settings
    #pragma config FNOSC    = PRIPLL                                // Oscillator selection
    #pragma config POSCMOD  = HS                                    // Primary oscillator mode
    #pragma config FPLLIDIV = DIV_2                                 // PLL input divider
    #pragma config FPLLMUL  = MUL_20                                // PLL multiplier
    #pragma config FPLLODIV = DIV_1                                 // PLL output divider
    #pragma config FPBDIV   = DIV_1                                 // Peripheral bus clock divider
    #pragma config FSOSCEN  = OFF                                   // Secondary oscillator enable
    
    //* Clock control settings
    #pragma config IESO     = OFF                                   // Internal/external clock switchover
    #pragma config FCKSM    = CSECME                                // Clock switching (CSx)/Clock monitor (CMx)
    #pragma config OSCIOFNC = OFF                                   // Clock output on OSCO pin enable
    
    //* USB Settings
    #pragma config UPLLEN   = ON                                    // USB PLL enable
    #pragma config UPLLIDIV = DIV_2                                 // USB PLL input divider
    
    //* Other Peripheral Device settings
    #pragma config FWDTEN   = OFF                                   // Watchdog timer enable
    #pragma config WDTPS    = PS1024                                // Watchdog timer postscaler
    #pragma config WINDIS   = OFF
    #pragma config JTAGEN   = OFF                          			// JTAG port disabled
   
    //* Code Protection settings
    #pragma config CP       = OFF                                   // Code protection
    #pragma config BWP      = OFF                                   // Boot flash write protect
    #pragma config PWP      = OFF                                   // Program flash write protect
    
    //* Debug settings
    #pragma config ICESEL   = ICS_PGx2                              // ICE pin selection
    //#pragma config DEBUG    = ON                          		// DO NOT SET THIS CONFIG BIT, it will break debugging
#endif
    
    #define CAPABILITIES    (blCapBootLED | blCapSplitFlashBootloader | blCapUSBInterface | blCapProgramButton | blCapVirtualProgramButton | CAPCOMMON)

    // BTN / LED sense
    #define LedOn       High
    #define BntOn       Low

    // Boot LED
    #define BLedLat     G
    #define BLedBit     6

    // Virtual program button
    #define VPBntLat    D
    #define VPBntBit    0

    // Program button
    #define PBntPort    D
    #define PBntBit     0
 
    #define _CPU_NAME_                  "32MX440F256H"
    #define VEND                        vendOlimex
    #define PROD                        prodOlimex_PIC32_Pinguino
    #define F_CPU                       80000000UL
    #define F_PBUS                      F_CPU

    #define FLASH_BYTES                 0x40000                     // 256K
    #define FLASH_PAGE_SIZE             4096
    #define LoadFlashWaitStates()       (CHECON = 2)            // 0 for 0-30Mhz, 1 for 31-60Mhz, 2 for 61-80Mhz

//************************************************************************
#elif defined(_BOARD_EBBV3_USB_)
 
#if defined(PUT_CONFIG_BITS_HERE)

    //* Oscillator Settings
    #pragma config FNOSC    = PRIPLL                                // Oscillator selection
    #pragma config POSCMOD  = XT                                    // Primary oscillator mode
    #pragma config FPLLIDIV = DIV_2                                 // PLL input divider
    #pragma config FPLLMUL  = MUL_20                                // PLL multiplier
    #pragma config FPLLODIV = DIV_2                                 // PLL output divider
    #pragma config FPBDIV   = DIV_1                                 // Peripheral bus clock divider
    #pragma config FSOSCEN  = OFF                                   // Secondary oscillator enable
    
    //* Clock control settings
    #pragma config IESO     = OFF                                   // Internal/external clock switchover
    #pragma config FCKSM    = CSECME                                // Clock switching (CSx)/Clock monitor (CMx)
    #pragma config OSCIOFNC = OFF                                   // Clock output on OSCO pin enable
    
    //* USB Settings
    #pragma config UPLLEN   = ON                                    // USB PLL enable
    #pragma config UPLLIDIV = DIV_2                                 // USB PLL input divider
    #pragma config FUSBIDIO = OFF									// USB USID pin controlled by port function
    #pragma config FVBUSONIO = OFF									// USB VBUSON pin controlled by port function
    
    //* Other Peripheral Device settings
    #pragma config FWDTEN   = OFF                                   // Watchdog timer enable
    #pragma config WDTPS    = PS1024                                // Watchdog timer postscaler
    #pragma config WINDIS   = OFF
    #pragma config JTAGEN   = OFF                          			// JTAG port disabled
    
    //* Code Protection settings
    #pragma config CP       = OFF                                   // Code protection
    #pragma config BWP      = OFF                                   // Boot flash write protect
    #pragma config PWP      = OFF                                   // Program flash write protect
    
    //*    Debug settings
    #pragma config ICESEL   = ICS_PGx1                      		// ICE/ICD Comm Channel Select
    //#pragma config DEBUG    = ON                          		// DO NOT SET THIS CONFIG BIT, it will break debugging

    #pragma config PMDL1WAY = OFF                           		// Allow multiple reconfigurations
    #pragma config IOL1WAY  = OFF                           		// Allow multiple reconfigurations
#endif
    
    #define CAPABILITIES    (blCapBootLED | blCapSplitFlashBootloader | blCapUSBInterface | blCapProgramButton | blCapVirtualProgramButton | CAPCOMMON)

    // BTN / LED sense
    #define LedOn       High
    #define BntOn       Low

    // Boot LED
    #define BLedLat     B
    #define BLedBit     15

    // Virtual program button
    #define VPBntLat    A
    #define VPBntBit    0

    // Program button
    #define PBntPort    A
    #define PBntBit     0
   
    #define _CPU_NAME_                  "32MX250F128D"
    #define VEND                        vendSchmalzHausLLC
    #define PROD                        prodEBBv3
    #define F_CPU                       40000000UL
    #define F_PBUS                      F_CPU

    #define FLASH_BYTES                 (0x20000-0x1000)		    // Leave room one flash block (for bootloader!)
    #define FLASH_PAGE_SIZE             1024						// In bytes

//************************************************************************
#elif defined(_BOARD_CHIPKIT_PI_)   // UART (Default) version
// NOTE: As of 8/20/2013 the crystal on the board (v3.37 and above) is now 8MHz, so this bootloader has been updated

#if defined(PUT_CONFIG_BITS_HERE)

    //* Oscillator Settings
    #pragma config FNOSC    = PRIPLL                                // Oscillator selection
    #pragma config POSCMOD  = HS                                    // Primary oscillator mode
    #pragma config FPLLIDIV = DIV_2                                 // PLL input divider
    #pragma config FPLLMUL  = MUL_20                                // PLL multiplier
    #pragma config FPLLODIV = DIV_2                                 // PLL output divider
    #pragma config FPBDIV   = DIV_1                                 // Peripheral bus clock divider
    #pragma config FSOSCEN  = OFF                                   // Secondary oscillator enable

    //* Clock control settings
    #pragma config IESO     = OFF                                   // Internal/external clock switchover
    #pragma config FCKSM    = CSECME                                // Clock switching (CSx)/Clock monitor (CMx)
    #pragma config OSCIOFNC = OFF                                   // Clock output on OSCO pin enable

    //* USB Settings
    #pragma config UPLLEN   = ON                                    // USB PLL enable
    #pragma config UPLLIDIV = DIV_2                                 // USB PLL input divider
    #pragma config FUSBIDIO = OFF									// USB USID pin controlled by port function
    #pragma config FVBUSONIO = OFF									// USB VBUSON pin controlled by port function

    //* Other Peripheral Device settings
    #pragma config FWDTEN   = OFF                                   // Watchdog timer enable
    #pragma config WDTPS    = PS1024                                // Watchdog timer postscaler
    #pragma config WINDIS   = OFF
    #pragma config JTAGEN   = OFF                          			// JTAG port disabled

    //* Code Protection settings
    #pragma config CP       = OFF                                   // Code protection
    #pragma config BWP      = OFF                                   // Boot flash write protect
    #pragma config PWP      = OFF                                   // Program flash write protect

    //*    Debug settings
    #pragma config ICESEL   = ICS_PGx1                      		// ICE/ICD Comm Channel Select
    //#pragma config DEBUG    = ON                          		// DO NOT SET THIS CONFIG BIT, it will break debugging

    #pragma config PMDL1WAY = OFF                           		// Allow multiple reconfigurations
    #pragma config IOL1WAY  = OFF                           		// Allow multiple reconfigurations
#endif

	// LED1 on RA0
	// LED2 on RB15
	// Boot button on RB9
    #define CAPABILITIES    (blCapBootLED | blCapUARTInterface | blCapProgramButton | blCapVirtualProgramButton | CAPCOMMON)

    // BTN / LED sense
    #define LedOn       High
    #define BntOn       Low

    // Boot LED
    #define BLedLat     A
    #define BLedBit     0

    // Virtual program button
    #define VPBntLat    B
    #define VPBntBit    9

    // Program button
    #define PBntPort    B
    #define PBntBit     9

    // Other capabilities
    #define BOOTLOADER_UART             2                   // avrdude program UART
    #define BAUDRATE                    115200              // avrdude baudrate
    #define UARTMapRX()                 (U2RXR = 0x2)       // RB1 -> U2RX
    #define UARTMapTX()                 (RPB0R = 0x2)       // RB0 -> U2TX

    #define _CPU_NAME_                  "32MX250F128B"
    #define VEND                        vendElement14
    #define PROD                        prodChipkitPi
    #define F_CPU                       40000000UL
    #define F_PBUS                      F_CPU

    #define FLASH_BYTES                 (0x20000-0x1000)		    // Leave room one flash block (for bootloader!)
    #define FLASH_PAGE_SIZE             1024						// In bytes

//************************************************************************
#elif defined(_BOARD_QUICK240_)

#if defined(PUT_CONFIG_BITS_HERE)

    //* Oscillator Settings
    #pragma config FNOSC    = PRIPLL                                // Oscillator selection
    #pragma config POSCMOD  = HS                                    // Primary oscillator mode
    #pragma config FPLLIDIV = DIV_2                                 // PLL input divider
    #pragma config FPLLMUL  = MUL_20                                // PLL multiplier
    #pragma config FPLLODIV = DIV_1                                 // PLL output divider
    #pragma config FPBDIV   = DIV_1                                 // Peripheral bus clock divider
    #pragma config FSOSCEN  = OFF                                   // Secondary oscillator enable

    //* Clock control settings
    #pragma config IESO     = OFF                                   // Internal/external clock switchover
    #pragma config FCKSM    = CSECME                                // Clock switching (CSx)/Clock monitor (CMx)
    #pragma config OSCIOFNC = OFF                                   // Clock output on OSCO pin enable

    //* USB Settings
    #pragma config UPLLEN   = ON                                    // USB PLL enable
    #pragma config UPLLIDIV = DIV_2                                 // USB PLL input divider
    #pragma config FUSBIDIO = OFF                                   // USB USID pin controlled by port function
    #pragma config FVBUSONIO = OFF                                  // USB VBUSON pin controlled by port function

    //* Other Peripheral Device settings
    #pragma config FWDTEN   = OFF                                   // Watchdog timer enable
    #pragma config WDTPS    = PS1024                                // Watchdog timer postscaler

    //* Code Protection settings
    #pragma config CP       = OFF                                   // Code protection
    #pragma config BWP      = OFF                                   // Boot flash write protect
    #pragma config PWP      = OFF                                   // Program flash write protect

    //* Debug settings
    #pragma config ICESEL   = ICS_PGx2                              // ICE pin selection
#endif

    #define CAPABILITIES    (blCapBootLED | blCapUSBInterface | blCapProgramButton | blCapVirtualProgramButton | CAPCOMMON)

    // BTN / LED sense
    #define LedOn       High
    #define BntOn       Low

    // Boot LED
    #define BLedLat     E
    #define BLedBit     0

     // Virtual program button
    #define VPBntLat    G
    #define VPBntBit    15

    // Program button
    #define PBntPort    G
    #define PBntBit     15

    #define _CPU_NAME_                  "32MX795F512L"
    #define VEND                        vendPontech
    #define PROD                        prodQuick240
    #define F_CPU                       80000000UL
    #define F_PBUS                      F_CPU

    #define FLASH_BYTES                 0x80000                     // 512K
    #define FLASH_PAGE_SIZE             4096
    #define LoadFlashWaitStates()       (CHECON = 2)            // 0 for 0-30Mhz, 1 for 31-60Mhz, 2 for 61-80Mhz

//************************************************************************
#elif defined(_BOARD_CHIPKIT_PI_USB_)
 
#if defined(PUT_CONFIG_BITS_HERE)

    //* Oscillator Settings
    #pragma config FNOSC    = PRIPLL                                // Oscillator selection
    #pragma config POSCMOD  = XT                                    // Primary oscillator mode
    #pragma config FPLLIDIV = DIV_2                                 // PLL input divider
    #pragma config FPLLMUL  = MUL_20                                // PLL multiplier
    #pragma config FPLLODIV = DIV_2                                 // PLL output divider
    #pragma config FPBDIV   = DIV_1                                 // Peripheral bus clock divider
    #pragma config FSOSCEN  = OFF                                   // Secondary oscillator enable
    
    //* Clock control settings
    #pragma config IESO     = OFF                                   // Internal/external clock switchover
    #pragma config FCKSM    = CSECME                                // Clock switching (CSx)/Clock monitor (CMx)
    #pragma config OSCIOFNC = OFF                                   // Clock output on OSCO pin enable
    
    //* USB Settings
    #pragma config UPLLEN   = ON                                    // USB PLL enable
    #pragma config UPLLIDIV = DIV_2                                 // USB PLL input divider
    #pragma config FUSBIDIO = OFF									// USB USID pin controlled by port function
    #pragma config FVBUSONIO = OFF									// USB VBUSON pin controlled by port function
    
    //* Other Peripheral Device settings
    #pragma config FWDTEN   = OFF                                   // Watchdog timer enable
    #pragma config WDTPS    = PS1024                                // Watchdog timer postscaler
    #pragma config WINDIS   = OFF
    #pragma config JTAGEN   = OFF                          			// JTAG port disabled
    
    //* Code Protection settings
    #pragma config CP       = OFF                                   // Code protection
    #pragma config BWP      = OFF                                   // Boot flash write protect
    #pragma config PWP      = OFF                                   // Program flash write protect
    
    //*    Debug settings
    #pragma config ICESEL   = ICS_PGx1                      		// ICE/ICD Comm Channel Select
    //#pragma config DEBUG    = ON                          		// DO NOT SET THIS CONFIG BIT, it will break debugging

    #pragma config PMDL1WAY = OFF                           		// Allow multiple reconfigurations
    #pragma config IOL1WAY  = OFF                           		// Allow multiple reconfigurations
#endif
    
	// LED1 on RA0
	// LED2 on RB15
	// Boot button on RB9
    #define CAPABILITIES    (blCapSplitFlashBootloader | blCapUSBInterface | blCapBootLED | blCapProgramButton | blCapVirtualProgramButton | CAPCOMMON)

    // BTN / LED sense
    #define LedOn       High
    #define BntOn       Low

    // Boot LED
    #define BLedLat     A
    #define BLedBit     0

    // Virtual program button
    #define VPBntLat    B
    #define VPBntBit    9

    // Program button
    #define PBntPort    B
    #define PBntBit     9
  
#define _CPU_NAME_                  "32MX250F128B"
    #define VEND                        vendElement14
    #define PROD                        prodUnassigned
    #define F_CPU                       40000000UL
    #define F_PBUS                      F_CPU

    #define FLASH_BYTES                 (0x20000-0x1000)		    // Leave room one flash block (for bootloader!)
    #define FLASH_PAGE_SIZE             1024						// In bytes

//************************************************************************
#elif defined(_BOARD_OLIMEX_DUINOMITE_) // 32MX795F512H, Microchip version (v1.5)

#if defined(PUT_CONFIG_BITS_HERE)

    //* Oscillator Settings
    #pragma config FNOSC    = PRIPLL                                // Oscillator selection
    #pragma config POSCMOD  = HS                                    // Primary oscillator mode
    #pragma config FPLLIDIV = DIV_2                                 // PLL input divider
    #pragma config FPLLMUL  = MUL_20                                // PLL multiplier
    #pragma config FPLLODIV = DIV_1                                 // PLL output divider
    #pragma config FPBDIV   = DIV_1                                 // Peripheral bus clock divider
    #pragma config FSOSCEN  = OFF                                   // Secondary oscillator enable

    //* Clock control settings
    #pragma config IESO     = OFF                                   // Internal/external clock switchover
    #pragma config FCKSM    = CSECME                                // Clock switching (CSx)/Clock monitor (CMx)
    #pragma config OSCIOFNC = OFF                                   // Clock output on OSCO pin enable

    //* USB Settings
    #pragma config UPLLEN   = ON                                    // USB PLL enable
    #pragma config UPLLIDIV = DIV_2                                 // USB PLL input divider
    #pragma config FUSBIDIO = OFF                                   // USB USID pin controlled by port function
    #pragma config FVBUSONIO = OFF                                  // USB VBUSON pin controlled by port function

    //* Other Peripheral Device settings
    #pragma config FWDTEN   = OFF                                   // Watchdog timer enable
    #pragma config WDTPS    = PS1024                                // Watchdog timer postscaler

    //* Code Protection settings
    #pragma config CP       = OFF                                   // Code protection
    #pragma config BWP      = OFF                                   // Boot flash write protect
    #pragma config PWP      = OFF                                   // Program flash write protect

    //* Debug settings
    #pragma config ICESEL   = ICS_PGx2                              // ICE pin selection
#endif

    #define CAPABILITIES    (blCapBootLED | blCapUSBInterface | blCapProgramButton | blCapVirtualProgramButton | CAPCOMMON)

    // BTN / LED sense
    #define LedOn       High
    #define BntOn       Low

    // Boot LED
    #define BLedLat     B
    #define BLedBit     15

    // Virtual program button
    #define VPBntLat    D
    #define VPBntBit    8

    // Program button
    #define PBntPort    D
    #define PBntBit     8

    #define _CPU_NAME_                  "32MX795F512H"
    #define VEND                        vendOlimex
    #define PROD                        prodOlimex_Duinomite
    #define F_CPU                       80000000UL
    #define F_PBUS                      F_CPU

    #define FLASH_BYTES                 0x80000                     // 512K
    #define FLASH_PAGE_SIZE             4096
    #define LoadFlashWaitStates()       (CHECON = 2)            // 0 for 0-30Mhz, 1 for 31-60Mhz, 2 for 61-80Mhz

//************************************************************************

#else
    #error    Board/CPU combination not defined
#endif

// *****************************************************************************
// *****************************************************************************
//                     THINGS BELOW HERE SHOULD NOT NEED TO BE MODIFIED
// *****************************************************************************
// *****************************************************************************
#if !defined(CAPABILITIES)
    #error CAPABILITIES needs to be defined.
#endif

// Check processor specific stuff.
// In particular PPS for MX1 or MX2
#if (                           \
    (__32MX110F016B__)  ||      \
    (__32MX110F016C__)  ||      \
    (__32MX110F016D__)  ||      \
    (__32MX120F032B__)  ||      \
    (__32MX120F032C__)  ||      \
    (__32MX120F032D__)  ||      \
    (__32MX130F064B__)  ||      \
    (__32MX130F064C__)  ||      \
    (__32MX130F064D__)  ||      \
    (__32MX150F128B__)  ||      \
    (__32MX150F128C__)  ||      \
    (__32MX150F128D__)  ||      \
    (__32MX210F016B__)  ||      \
    (__32MX210F016C__)  ||      \
    (__32MX210F016D__)  ||      \
    (__32MX220F032B__)  ||      \
    (__32MX220F032C__)  ||      \
    (__32MX220F032D__)  ||      \
    (__32MX230F064B__)  ||      \
    (__32MX230F064C__)  ||      \
    (__32MX230F064D__)  ||      \
    (__32MX250F128B__)  ||      \
    (__32MX250F128C__)  ||      \
    (__32MX250F128D__)  ||      \
    (__32MZ0256ECE064__) ||     \
    (__32MZ0512ECE064__) ||     \
    (__32MZ1024ECE064__) ||     \
    (__32MZ1024ECG064__) ||     \
    (__32MZ2048ECG064__) ||     \
    (__32MZ0256ECJ064__) ||     \
    (__32MZ0512ECJ064__) ||     \
    (__32MZ1024ECJ064__) ||     \
    (__32MZ1024ECL064__) ||     \
    (__32MZ2048ECL064__) ||     \
    (__32MZ0256ECF064__) ||     \
    (__32MZ0512ECF064__) ||     \
    (__32MZ1024ECF064__) ||     \
    (__32MZ1024ECH064__) ||     \
    (__32MZ2048ECH064__) ||     \
    (__32MZ0256ECK064__) ||     \
    (__32MZ0512ECK064__) ||     \
    (__32MZ1024ECK064__) ||     \
    (__32MZ1024ECM064__) ||     \
    (__32MZ2048ECM064__) ||     \
    (__32MZ0256ECE100__) ||     \
    (__32MZ0512ECE100__) ||     \
    (__32MZ1024ECE100__) ||     \
    (__32MZ1024ECG100__) ||     \
    (__32MZ2048ECG100__) ||     \
    (__32MZ0256ECJ100__) ||     \
    (__32MZ0512ECJ100__) ||     \
    (__32MZ1024ECJ100__) ||     \
    (__32MZ1024ECL100__) ||     \
    (__32MZ2048ECL100__) ||     \
    (__32MZ0256ECF100__) ||     \
    (__32MZ0512ECF100__) ||     \
    (__32MZ1024ECF100__) ||     \
    (__32MZ1024ECH100__) ||     \
    (__32MZ2048ECH100__) ||     \
    (__32MZ0256ECK100__) ||     \
    (__32MZ0512ECK100__) ||     \
    (__32MZ1024ECK100__) ||     \
    (__32MZ1024ECM100__) ||     \
    (__32MZ2048ECM100__) ||     \
    (__32MZ0256ECE124__) ||     \
    (__32MZ0512ECE124__) ||     \
    (__32MZ1024ECE124__) ||     \
    (__32MZ1024ECG124__) ||     \
    (__32MZ2048ECG124__) ||     \
    (__32MZ0256ECJ124__) ||     \
    (__32MZ0512ECJ124__) ||     \
    (__32MZ1024ECJ124__) ||     \
    (__32MZ1024ECL124__) ||     \
    (__32MZ2048ECL124__) ||     \
    (__32MZ0256ECF124__) ||     \
    (__32MZ0512ECF124__) ||     \
    (__32MZ1024ECF124__) ||     \
    (__32MZ1024ECH124__) ||     \
    (__32MZ2048ECH124__) ||     \
    (__32MZ0256ECK124__) ||     \
    (__32MZ0512ECK124__) ||     \
    (__32MZ1024ECK124__) ||     \
    (__32MZ1024ECM124__) ||     \
    (__32MZ2048ECM124__) ||     \
    (__32MZ0256ECE144__) ||     \
    (__32MZ0512ECE144__) ||     \
    (__32MZ1024ECE144__) ||     \
    (__32MZ1024ECG144__) ||     \
    (__32MZ2048ECG144__) ||     \
    (__32MZ0256ECJ144__) ||     \
    (__32MZ0512ECJ144__) ||     \
    (__32MZ1024ECJ144__) ||     \
    (__32MZ1024ECL144__) ||     \
    (__32MZ2048ECL144__) ||     \
    (__32MZ0256ECF144__) ||     \
    (__32MZ0512ECF144__) ||     \
    (__32MZ1024ECF144__) ||     \
    (__32MZ1024ECH144__) ||     \
    (__32MZ2048ECH144__) ||     \
    (__32MZ0256ECK144__) ||     \
    (__32MZ0512ECK144__) ||     \
    (__32MZ1024ECK144__) ||     \
    (__32MZ1024ECM144__) ||     \
    (__32MZ2048ECM144__)        )

	#define PPS_IN_USE		1		// indicate that this is a PPS type processor

    #if ((CAPABILITIES & blCapUARTInterface) == blCapUARTInterface)

        // must define what pins the UART goes on
        #if !defined(UARTMapRX)
            #error UARTMapRX needs to be defined specifying how UART RX PPS pins are to be selected.
        #elif !defined(UARTMapTX)
            #error UARTMapTX needs to be defined specifying how UART TX PPS pins are to be selected.
        #endif


        // say to use PPS mapping
        #define USE_PPS_UART 1

    #endif  // UART

    #if defined(LoadFlashWaitStates)
        #error LoadFlashWaitStates is not supported and unneeded for the MX1/2 or MZ parts
    #endif

   // define nothing for the flash wait states
    #define LoadFlashWaitStates()                           // not supported on MX1/2

#endif  // MX1 or MX2

// Assign the bootloader UART
#if( ((CAPABILITIES & blCapUARTInterface) == blCapUARTInterface) )
    #if(BOOTLOADER_UART == 1)
        #define UMODE       U1MODE
        #define USTA        U1STA
        #define UBRG        U1BRG
        #define UMODEbits   U1MODEbits
        #define USTAbits    U1STAbits
        #define UTXREG      U1TXREG
        #define URXREG      U1RXREG
    #elif(BOOTLOADER_UART == 2)
        #define UMODE       U2MODE
        #define USTA        U2STA
        #define UBRG        U2BRG
        #define UMODEbits   U2MODEbits
        #define USTAbits    U2STAbits
        #define UTXREG      U2TXREG
        #define URXREG      U2RXREG
    #elif(BOOTLOADER_UART == 3)
        #define UMODE       U3MODE
        #define USTA        U3STA
        #define UBRG        U3BRG
        #define UMODEbits   U3MODEbits
        #define USTAbits    U3STAbits
        #define UTXREG      U3TXREG
        #define URXREG      U3RXREG
    #elif(BOOTLOADER_UART == 4)
        #define UMODE       U4MODE
        #define USTA        U4STA
        #define UBRG        U4BRG
        #define UMODEbits   U4MODEbits
        #define USTAbits    U4STAbits
        #define UTXREG      U4TXREG
        #define URXREG      U4RXREG
    #elif(BOOTLOADER_UART == 5)
        #define UMODE       U5MODE
        #define USTA        U5STA
        #define UBRG        U5BRG
        #define UMODEbits   U5MODEbits
        #define USTAbits    U5STAbits
        #define UTXREG      U5TXREG
        #define URXREG      U5RXREG
    #else
        #error a UART 1 thru 5 must be specified.
    #endif  // UART number
#elif ((CAPABILITIES & blCapUSBInterface) == blCapUSBInterface)
    // do nothing
#else  
    #error blCapUARTInterface or blCapUSBInterface must be assigned in CAPABILITIES
#endif

// if no BOOT/HEARTBEAT LED
#if ((CAPABILITIES & blCapBootLED) == 0)
    #define EnableBootLED()
    #define DisableBootLED()
    #define BootLED_Toggle()
    #define BootLED_On()
    #define BootLED_Off()
#else
    #define EnableBootLED()             (CAT_3(TRIS,BLedLat,CLR) = (1 << BLedBit))
    #define DisableBootLED()            (CAT_3(TRIS,BLedLat,SET) = (1 << BLedBit))
    #define BootLED_Toggle()            (CAT_3(LAT,BLedLat,INV) = (1 << BLedBit))

    #if(LedOn == High)
        #define BootLED_On()            (CAT_3(LAT,BLedLat,SET) = (1 << BLedBit))
        #define BootLED_Off()           (CAT_3(LAT,BLedLat,CLR) = (1 << BLedBit))
    #elif(LedOn == Low)
        #define BootLED_On()            (CAT_3(LAT,BLedLat,CLR) = (1 << BLedBit))
        #define BootLED_Off()           (CAT_3(LAT,BLedLat,SET) = (1 << BLedBit))
    #else
        #error Must specify if LedOn is High or Low
    #endif
#endif

// if no DOWNLOAD LED
#if ((CAPABILITIES & blCapDownloadLED) == 0)
    #define EnableDownLoadLED()
    #define DisableDownLoadLED()
    #define DownloadLED_Toggle()
    #define DownloadLED_On()
    #define DownloadLED_Off()
#else
    #define EnableDownLoadLED()         (CAT_3(TRIS,DLedLat,CLR) = (1 << DLedBit))
    #define DisableDownLoadLED()        (CAT_3(TRIS,DLedLat,SET) = (1 << DLedBit))
    #define DownloadLED_Toggle()        (CAT_3(LAT,DLedLat,INV) = (1 << DLedBit))

    #if(LedOn == High)
        #define DownloadLED_On()        (CAT_3(LAT,DLedLat,SET) = (1 << DLedBit))
        #define DownloadLED_Off()       (CAT_3(LAT,DLedLat,CLR) = (1 << DLedBit))
    #elif(LedOn == Low)
        #define DownloadLED_On()        (CAT_3(LAT,DLedLat,CLR) = (1 << DLedBit))
        #define DownloadLED_Off()       (CAT_3(LAT,DLedLat,SET) = (1 << DLedBit))
   #else
        #error Must specify if LedOn is High or Low
    #endif
#endif

// if no program button
#if ((CAPABILITIES & blCapProgramButton) == 0)
    #define fLoadFromAVRDudeViaProgramButton            (false)
#else
    #define fLoadFromAVRDudeViaProgramButton            (CAT_3(PORT,PBntPort,bits).CAT_3(R,PBntPort,PBntBit) == BntOn)
#endif

// if no virtual program button
#if ((CAPABILITIES & blCapVirtualProgramButton) == 0)
    #define fLoadFromAVRDudeViaVirtualProgramButton     (false) 
    #define ClearVirtualProgramButton()
#else
    #define fLoadFromAVRDudeViaVirtualProgramButton     (CAT_3(LAT,VPBntLat,bits).CAT_3(LAT,VPBntLat,VPBntBit) == 1)
    #define ClearVirtualProgramButton()                 (CAT_3(LAT,VPBntLat,CLR) = (1 << VPBntBit))
#endif

// if no auto reset listen time
#if ((CAPABILITIES & blCapAutoResetListening) == 0)
        #define LISTEN_BEFORE_LOAD                      0 
#endif

// error checking for #defines.
#if !defined(_CPU_NAME_)
    #error _CPU_NAME_ needs to be defined.
#elif !defined(F_CPU)
    #error F_CPU needs to be defined specifying the processor master clock frequency.
#elif !defined(VEND)
    #error VEND needs to be defined specifying the vendor ID.
#elif !defined(PROD)
    #error PROD needs to be defined specifying the product ID.
#elif !defined(F_PBUS)
    #error _F_PBUS needs to be defined specifying the peripheral buss frequency.
#elif !defined(FLASH_START)
    #error FLASH_START needs to be defined specifying the flash start address.
#elif !defined(FLASH_BYTES)
    #error FLASH_BYTES needs to be defined specifying the number of bytes in flash, less that reserved for EEPROM.
#elif !defined(FLASH_PAGE_SIZE)
    #error FLASH_PAGE_SIZE needs to be defined specifying the number of bytes in a flash page.
#elif !defined(USER_APP_ADDR)
    #error USER_APP_ADDR needs to be defined specifying where the user applicaiton is loaded in flash.
#elif !defined(EnableBootLED)
    #error EnableBootLED needs to be defined specifying how to enable the Boot LED.
#elif !defined(DisableBootLED)
    #error DisableBootLED needs to be defined specifying how to disable the Boot LED.
#elif !defined(BootLED_Toggle)
    #error BootLED_Toggle needs to be defined specifying how to toggle the Boot LED.
#elif !defined(BootLED_On)
    #error BootLED_On needs to be defined specifying how to turn on the Boot LED.
#elif !defined(BootLED_Off)
    #error BootLED_Off needs to be defined specifying how to turn off the Boot LED.
#elif !defined(EnableDownLoadLED)
    #error EnableDownLoadLED needs to be defined specifying how to enable the Download LED.
#elif !defined(DisableDownLoadLED)
    #error DisableDownLoadLED needs to be defined specifying how to disable the Download LED.
#elif !defined(DownloadLED_Toggle)
    #error DownloadLED_Toggle needs to be defined specifying how to toggle the Download LED.
#elif !defined(DownloadLED_On)
    #error DownloadLED_On needs to be defined specifying how to turn on the Download LED.
#elif !defined(DownloadLED_Off)
    #error DownloadLED_Off needs to be defined specifying how to turn off the Download LED.
#elif !defined(fLoadFromAVRDudeViaProgramButton)
    #error fLoadFromAVRDudeViaProgramButton needs to be defined specifying if the program button is active.
#elif !defined(fLoadFromAVRDudeViaVirtualProgramButton)
    #error fLoadFromAVRDudeViaVirtualProgramButton needs to be defined specifying if the virtual program latch is active.
#elif !defined(ClearVirtualProgramButton)
    #error ClearVirtualProgramButton needs to be defined specifying how to clear the virtual program latch.
#elif !defined(LoadFlashWaitStates)
    #error LoadFlashWaitStates needs to be defined specifying the number of wait states to be inserted for flash operation.
#elif !defined(LISTEN_BEFORE_LOAD)
    #error LISTEN_BEFORE_LOAD needs to be defined specifying how long in milliseconds to listen for an upload from avrdude before jumping to the application in flash.
#elif ((CAPABILITIES & blCapSmartStart) == blCapSmartStart)
    #if !defined(USE_POR_SEQUENCE)
        #error USE_POR_SEQUENCE needs to be defined specifying if a power on reset sequence is needed to prevent unwanted false starts
    #endif  // POR Sequence
#elif ((CAPABILITIES & blCapUARTInterface) == blCapUARTInterface)
    #if !defined(BAUDRATE)
        #error BAUDRATE needs to be defined specifying the baud rate for the UART to run at.
    #endif // BAUD RATE
#endif

// core timer ticks per second is always 1/2 the CPU ticks, so devide by 2 to get ticks per second
// divide by another 1000 (or 2* 1000) to get ticks per millisecond
// we add the 1000 to round up or down on a faction of a millisecond
#define CORE_TIMER_TICKS_PER_MILLISECOND    ((F_CPU + 1000) / 2000)

/***    static inline void __attribute__((always_inline)) InitLEDsAndButtons(void)
**
**    Synopsis:   
**      This initializes board specific LEDs and Buttons.
*
**    Parameters:
**      None
**
**    Return Values:
**      None
**
**    Errors:
**      None
**
**  Notes:
**
**      This is inlined as only one copy will exist in the code
**
*/
static inline void __attribute__((always_inline)) InitLEDsAndButtons(void)
{
	// We assume the processor is unlocked, so let's just assert that here
    // While the processor comes up in the unlocked state after reset it is
    // possible that the rest code was jumped to after someone locked the system
    // and we need to re-assert the unlock.
    SYSKEY = 0;
    SYSKEY = 0xAA996655;
    SYSKEY = 0x556699AA;
 
    #ifdef PPS_IN_USE
		CFGCONbits.IOLOCK = 0;            // unlock PPS; same reasoning as explicitly unlocking the processor
    #endif

    // define all analog pins as digital
    #ifdef _ANSELA_w_POSITION
        ANSELA = 0;
    #endif
     
    #ifdef _ANSELB_w_POSITION
        ANSELB = 0;
    #endif
     
    #ifdef _ANSELC_w_POSITION
        ANSELC = 0;
    #endif
     
    #ifdef _AD1PCFG_w_POSITION
        AD1PCFG = 0xffff;
    #endif

    // wait states flash/cache based on the system clock speed.
    // This assumes the clock is running at a 20Mhz multiple and is greater than 20Mhz.
    LoadFlashWaitStates();

    EnableBootLED();
    EnableDownLoadLED();

    // no need to enable the program button as it is tri-stated after reset

    // Intialize the download LED off
    DownloadLED_Off();
}

/***    static inline void __attribute__((always_inline)) UninitLEDsAndButtons(void)
**
**    Synopsis:   
**      This Uninitializes board specific LEDs and Buttons
*
**    Parameters:
**      None
**
**    Return Values:
**      None
**
**    Errors:
**      None
**
**  Notes:
**
**      This is inlined as only one copy will exist in the code
**
*/
static inline void __attribute__((always_inline)) UninitLEDsAndButtons(void)
{
    // turn the LEDs OFF before tri-stating
    BootLED_Off();
    DownloadLED_Off();

    // tri-state the LEDs
    DisableBootLED();
    DisableDownLoadLED();

    // Buttons are already input, already tri-stated
}

// USB SPECIFIC CODE
#if ((CAPABILITIES & blCapUSBInterface) == blCapUSBInterface)

    #include "cdcacm.h"
    #include "usb.h"
    
    #define stk500v2_isr                usb_isr
    #define stk500v2_print              usb_print
    #define UninitStk500v2Interface     usb_uninitialize

    static inline void __attribute__((always_inline)) InitStk500v2Interface(void)
    {
       // initialize usb
        usb_initialize();
        cdcacm_register(null_reset_cbfn);
    }
    
    // this function sends bytes to the CDC/ACM port
    static inline void __attribute__((always_inline)) usb_print(const byte *buffer, int length)
    {
        if (cdcacm_attached && cdcacm_active) {
            cdcacm_print(buffer, length);
        }
    }

    // this function receives bytes from the CDC/ACM port
    // N.B. if this routine returns false, cdcacm will drop the ball and we'll
    // call cdcacm_command_ack() later to pick it up again.
    static inline bool __attribute__((always_inline)) avrbl_receive(const byte *buffer, int length)
    {
        int i;
    
        for (i = 0; i < length; i++) {
            avrbl_state_machine(buffer[i]);
        }
    
        return true;
    }

// UART SPECIFIC CODE
#else  // using a UART

    #include "serial.h"
    
    #define stk500v2_isr                serial_isr
    #define stk500v2_print              serial_print
    
    static inline void __attribute__((always_inline)) InitStk500v2Interface(void)
    {
        // if the UART is mapped via Peripheral Pin Selection
        #if defined(USE_PPS_UART)
    
            // The unlock code is documented as required yet does not seem to be needed.
            //        SYSKEY = 0;
            //        SYSKEY = 0xAA996655;
            //        SYSKEY = 0x556699AA;
            //        CFGCONbits.IOLOCK = 0;            // unlock PPS
            // End of seemingly unneeded unlock code
        
            // modify PPS
            UARTMapRX();
            UARTMapTX();
        
            // The lock code is documented as required yet does not seem to be needed.
            //        CFGCONbits.IOLOCK = 1;            // lock PPS
            //        SYSKEY = 0x33333333;
            // End of seemingly unneeded lock code
    
        #endif
    
    	//*	Init UART
    	//*	set baudrate and enable USART receiver and transmiter without interrupts
    	UMODE	=	(UART_ENABLE);
    	USTA	=	(UART_RX_ENABLE | UART_TX_ENABLE);
    	UBRG	=	((F_PBUS / (16 * BAUDRATE))-1);	// calculate actual BAUD generate value.
    
    	//*	ok, the serial port is initialized, clear any data that may be there
    	while (USTAbits.URXDA)
    	{
    	    byte value = 0;
    		value = URXREG;
    	}
    }

    static inline void __attribute__((always_inline)) UninitStk500v2Interface(void)
    {
        // make sure we transmitted our last byte before closeing
        while (!USTAbits.TRMT);

        // disable the UART
        UMODE = 0;
    }
#endif  // End of _USE_USB_FOR_BOOTLOADER_ and  UART specific code


// *****************************************************************************
// *****************************************************************************
//           These are power up sequences to prevent multiple restarts
// *****************************************************************************
// *****************************************************************************

/***    static inline void __attribute__((always_inline)) PowerOnResetDelay(void)
**
**    Synopsis:   
**      Some boards have a MPLAB debug circuit that takes several seconds to initialize
**      and it pulls reset several times in the process. This is a board specific sequence
**      to determine when the last reset was pulled and then can jump to normal processeing
**
**
**    Parameters:
**      None
**
**    Return Values:
**      None
**
**    Errors:
**      None
**
**  Notes:
**
**typedef union {
**  struct {
**    unsigned POR:1;
**    unsigned BOR:1;
**    unsigned IDLE:1;
**    unsigned SLEEP:1;
**    unsigned WDTO:1;
**    unsigned :1;
**    unsigned SWR:1;
**    unsigned EXTR:1;
**    unsigned VREGS:1;
**    unsigned CMR:1;
**  };
**      This is inlined as only one copy will exist in the code
**
**      state sequence; we use WDTO as a sometimes persistent state bit.
**      1. EXTR,BOR,POR      - 0x83; Action: Set WDTO and Clear BOR
**      2. EXTR,WDTO,POR     - 0x91; Action: Set BOR
**      3. EXTR,BOR,POR      - 0x83; Action: Set WDTO and Clear BOR, but... WDTO will not survive
**      4. EXTR,POR          - 0x81; Action: Exit
**
**      If just an EXTR reset (0x80) comes in, then Exit, this is not a power up situation.
**
**      If this ever gets fixed it should come up with BOR, POR only, so make that exit as well.
**
*/
#if ((CAPABILITIES & blCapSmartStart) == 0)
    #define WaitForFinalReset()
#elif (USE_POR_SEQUENCE == 1)         // PKOB reset skip for the MX4 & MX4 Cerebot boards
    static inline void __attribute__((always_inline)) WaitForFinalReset(void)
    {   
        uint16 rCon = RCON & 0xC3;
        bool fClrRCONAfter1Second = false;
        uint32 tStart = _CP0_GET_COUNT();
        uint32 tCur = tStart;
        uint32 tExit = tStart;
        uint32 tBlink = tStart;

        switch(rCon)
        {
            // external reset only, we don't wait, we are done; EXTR only
            case 0x80:      // simple reset
                tExit = 0;
                break;

            // unknown state; this shouldn't happen
            default:
            // fall through, lets just assume state 1
            // this will give us the longest reset path of a min. of 9s (7s + 2s at 0xC1)
         
            // state 2, EXTR & BOR & POR 
                // sometimes state 1 is missed when there is a glitch on the reset line that is so
                // fast that the code at state 1 does not run, or if reset comes up so slow that EXTR 
                // is set such as when JP11 enables the MPIDE RC auto-reset circuit.
             
            // state 4, EXTR & BOR & POR; with DBG connected to MPLAB prepare for the 2nd weird reset pair
                // when we go to state 5, EXTR & POR will be set; SWR will get cleared by the weird reset pair

            case 0x83:      // state 2 & 4
                RCON = 0x41;                                        // just set SWR, POR
                // fall thru as in either of these states if I don't get another reset
                // with in a second, then on the next state I want to exit

            // state 1, BOR and POR set, 
                // case 1, simple boot, we will wait 7s
                // case 2, only MPIDE is attached we will wait 6s and MPIDE will reset
                // case 3, DBG is attached, after 20ms a reset will come in
            case 0x3:       // state 1  

                // wait 1 second. We do this to make sure we are not at state 1 waiting
                // for state 2 in an MPLAB connected condition.
                // plus we need to keep either BOR or POR set in case we have those
                // resets every 650ms.
                fClrRCONAfter1Second = true;
                
                // If a reset has not occured after 1 second, then we know the next
                // state will be an exit, so clear RCON so the next state will
                // come up as either just EXTR, or EXTR and POR (state 5)
                tExit = (CORE_TIMER_TICKS_PER_MILLISECOND * 7000);  // 7 second delay
                break;

            // state 3; EXTR & SWR & POR
            // DBG USB + MPLAB connected, we are at about .5s, just after .4s after the long reset
            // Then next state 4 is our first weird double reset
            case 0xC1:      // state 3
                RCON = 0x3;                                         // set BOR & POR
                tExit = (CORE_TIMER_TICKS_PER_MILLISECOND * 2000);  // 2 second delay
                break;

            // state 5, with DBG connected to MPLAB; EXTR & POR;
            // we wait a second because if we have MPIDE, DBG, and JP11, we get 650ms spikes
            // and we want to wait for the next spike to reset us.
            case 0x81:      // state 5
                tExit = (CORE_TIMER_TICKS_PER_MILLISECOND * 1000);  // 1 second delay
                break;
        }
  
        // All LEDs are off, so toggle one out of phase with the other
        BootLED_On();

        // wait for a reset or completion           
        do
        {
            tCur = _CP0_GET_COUNT(); 

            // if we wait long enough, then we know we are in a state where the next
            // state we should exit, but setting RCON to 0, the next state will be just EXTR
            // and that will cause us to immediately exit. 
            // except for the condition where POR gets set and gives us EXTR & POR, state 5.
            if(fClrRCONAfter1Second && ((tCur - tStart) >= (CORE_TIMER_TICKS_PER_MILLISECOND * 1000)))
            {
                RCON = 0x0;
                fClrRCONAfter1Second = false;
            }

            // toggle our leds 8 times a second (on to on, so toggle is 16 times a second).
            if((tCur - tBlink) >= (CORE_TIMER_TICKS_PER_MILLISECOND * 62))
            {
                BootLED_Toggle();
                DownloadLED_Toggle();
                tBlink = tCur;
             }
        } while((tCur- tStart) <= tExit); 

        // when we are done, clear all bits.
        RCON = 0x0;
  }
#elif (USE_POR_SEQUENCE == 100)         // test debug for the MX7cK
    static inline void __attribute__((always_inline)) WaitForFinalReset(void)
    {   
        uint32 tStart = _CP0_GET_COUNT();
        uint32 tCur;

        // Connector JA pins 1,2,3
        TRISBCLR = (1 << 2);      
        TRISBCLR = (1 << 3);      
        TRISBCLR = (1 << 4);      

        LATBbits.LATB2 = RCONbits.POR;
        LATBbits.LATB3 = RCONbits.BOR;
        LATBbits.LATB4 = RCONbits.EXTR;

        // reset bits fro next pass
        RCON = 0;

        while(1);   // stop
 }
#elif (USE_POR_SEQUENCE == 101)         // MX7cK Logic Analyzer verification sequence
    static inline void __attribute__((always_inline)) WaitForFinalReset(void)
    {   
        uint16 rCon = RCON & 0xC3;
        bool fClrRCONAfter1Second = false;
        uint32 tStart = _CP0_GET_COUNT();
        uint32 tCur = tStart;
        uint32 tExit = tStart;

        // connector JB, pin 1,2
        // NOT ready
        TRISECLR = (1 << 0);
        TRISECLR = (2 << 0);
        LATEbits.LATE0 = 1;         // app running
        LATEbits.LATE1 = 0;         // ready

        // set up LEDs for output
        TRISGCLR = (1 << 12);      
        TRISGCLR = (1 << 13);      
        TRISGCLR = (1 << 14);      
        TRISGCLR = (1 << 15);   

        // show the bits on the LEDs
        LATGbits.LATG12 = RCONbits.POR;
        LATGbits.LATG13 = RCONbits.BOR;
        LATGbits.LATG15 = RCONbits.SWR;;
        LATGbits.LATG14 = RCONbits.EXTR;

        // Connector JA pins 1,2,3,4
        TRISBCLR = (1 << 2);      
        TRISBCLR = (1 << 3);      
        TRISBCLR = (1 << 4);      
        TRISBCLR = (1 << 6);      

        LATBbits.LATB2 = RCONbits.POR;
        LATBbits.LATB3 = RCONbits.BOR;
        LATBbits.LATB4 = RCONbits.SWR;
        LATBbits.LATB6 = RCONbits.EXTR;

        switch(rCon)
        {
            // external reset only, we don't wait, we are done; EXTR only
            case 0x80:      // simple reset
                tExit = 0;
                break;

            // unknown state; this shouldn't happen
            default:
            // fall through, lets just assume state 1
            // this will give us the longest reset path of a min. of 9s (7s + 2s at 0xC1)
         
            // state 2, EXTR & BOR & POR 
                // sometimes state 1 is missed when there is a glitch on the reset line that is so
                // fast that the code at state 1 does not run, or if reset comes up so slow that EXTR 
                // is set such as when JP11 enables the MPIDE RC auto-reset circuit.
             
            // state 4, EXTR & BOR & POR; with DBG connected to MPLAB prepare for the 2nd weird reset pair
                // when we go to state 5, EXTR & POR will be set; SWR will get cleared by the weird reset pair

            case 0x83:      // state 2 & 4
                RCON = 0x41;                                        // just set SWR, POR
                // fall thru as in either of these states if I don't get another reset
                // with in a second, then on the next state I want to exit

            // state 1, BOR and POR set, 
                // case 1, simple boot, we will wait 7s
                // case 2, only MPIDE is attached we will wait 6s and MPIDE will reset
                // case 3, DBG is attached, after 20ms a reset will come in
            case 0x3:       // state 1  

                // wait 1 second. We do this to make sure we are not at state 1 waiting
                // for state 2 in an MPLAB connected condition.
                // plus we need to keep either BOR or POR set in case we have those
                // resets every 650ms.
                fClrRCONAfter1Second = true;
                
                // If a reset has not occured after 1 second, then we know the next
                // state will be an exit, so clear RCON so the next state will
                // come up as either just EXTR, or EXTR and POR (state 5)
                tExit = (CORE_TIMER_TICKS_PER_MILLISECOND * 7000);  // 7 second delay
                break;

            // state 3; EXTR & SWR & POR
            // DBG USB + MPLAB connected, we are at about .5s, just after .4s after the long reset
            // Then next state 4 is our first weird double reset
            case 0xC1:      // state 3
                RCON = 0x3;                                         // set BOR & POR
                tExit = (CORE_TIMER_TICKS_PER_MILLISECOND * 2000);  // 2 second delay
                break;

            // state 5, with DBG connected to MPLAB; EXTR & POR;
            // we wait a second because if we have MPIDE, DBG, and JP11, we get 650ms spikes
            // and we want to wait for the next spike to reset us.
            case 0x81:      // state 5
                tExit = (CORE_TIMER_TICKS_PER_MILLISECOND * 1000);  // 1 second delay
                break;
        }
  
        // wait for a reset or completion           
        do
        {
            tCur = _CP0_GET_COUNT(); 

            // if we wait long enough, then we know we are in a state where the next
            // state we should exit, but setting RCON to 0, the next state will be just EXTR
            // and that will cause us to immediately exit. 
            // except for the condition where POR gets set and gives us EXTR & POR, state 5.
            if(fClrRCONAfter1Second && ((tCur - tStart) >= (CORE_TIMER_TICKS_PER_MILLISECOND * 1000)))
            {
                RCON = 0x0;
                fClrRCONAfter1Second = false;
            }
        } while((tCur- tStart) <= tExit);   // 5 second wait
                   
        // when we are done, clear all bits.
        RCON = 0x0;

        // display our registers on LEDs
        LATGbits.LATG12 = RCONbits.POR;
        LATGbits.LATG13 = RCONbits.BOR;
        LATGbits.LATG15 = RCONbits.SWR;;
        LATGbits.LATG14 = RCONbits.EXTR;

        // display registers to logic analyzer
        LATBbits.LATB2 = RCONbits.POR;
        LATBbits.LATB3 = RCONbits.BOR;
        LATBbits.LATB4 = RCONbits.SWR;
        LATBbits.LATB6 = RCONbits.EXTR;

        // say we are ready
        LATEbits.LATE1 = 1;

        while(1);   // stop
 }
#else
        #error USE_POR_SEQUENCE needs to be defined specifying which power on reset sequence to use to avoid the muliple resets on board power up.
#endif

