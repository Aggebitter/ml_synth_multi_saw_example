/*
 * Copyright (c) 2023 Marcel Licence
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * Dieses Programm ist Freie Software: Sie können es unter den Bedingungen
 * der GNU General Public License, wie von der Free Software Foundation,
 * Version 3 der Lizenz oder (nach Ihrer Wahl) jeder neueren
 * veröffentlichten Version, weiter verteilen und/oder modifizieren.
 *
 * Dieses Programm wird in der Hoffnung bereitgestellt, dass es nützlich sein wird, jedoch
 * OHNE JEDE GEWÄHR,; sogar ohne die implizite
 * Gewähr der MARKTFÄHIGKEIT oder EIGNUNG FÜR EINEN BESTIMMTEN ZWECK.
 * Siehe die GNU General Public License für weitere Einzelheiten.
 *
 * Sie sollten eine Kopie der GNU General Public License zusammen mit diesem
 * Programm erhalten haben. Wenn nicht, siehe <https://www.gnu.org/licenses/>.
 */

/**
 * @file config.h
 * @author Marcel Licence
 * @date 21.11.2021
 *
 * @brief This file contains the project configuration
 *
 * All definitions are visible in the entire project
 *
 * Put all your project settings here (defines, numbers, etc.)
 * configurations which are requiring knowledge of types etc.
 * shall be placed in z_config.ino (will be included at the end)
 */


#ifndef CONFIG_H_
#define CONFIG_H_


#ifdef __CDT_PARSER__
#include <cdt.h>
#endif


#define NOTE_ON_AFTER_SETUP /* used to get a test tone without MIDI input. Can be deactivated */



//#define I2S_NODAC
//#define NODAC

#define MIDI_RECV_FROM_SERIAL
#define SERIAL_BAUDRATE 115200
#define MIDI_SERIAL_BAUDRATE SERIAL_BAUDRATE


//#define CS4272_ENABLED

//#define AUDIO_PASS_THROUGH


/* use the following to test the output / codec */
//#define OUTPUT_SAW_TEST


/*
 * Configuration for
 * Board: "Rapsberry Pi Pico"
 *
 * BCK: 26
 * DIN: 28
 * LCK: 27  (always BCK + 1)
 *
 * MIDI_RX: 12 (GP9)
 *
 * Pinout @see https://www.raspberrypi-spy.co.uk/2021/01/pi-pico-pinout-and-power-pins/#prettyPhoto
 */
#if (defined ARDUINO_RASPBERRY_PI_PICO) || (defined ARDUINO_GENERIC_RP2040)

#ifdef ARDUINO_RASPBERRY_PI_PICO
#define BLINK_LED_PIN LED_BUILTIN
#else
#define BLINK_LED_PIN 19
#endif
#define SAMPLE_BUFFER_SIZE  48
#define SAMPLE_RATE  48000

//#define ADC_ENABLED
//#define ADC_CONTROL_NOTE
//#define ARP_MODULE_ENABLED

#define MIDI_RX2_PIN    5
#define MIDI_PORT2_ACTIVE

#define MIDI_USB_ENABLED /* connect RP2040 as a USB device */

#define MAX_DELAY 24000

#define RP2040_AUDIO_PWM

#endif /* ARDUINO_RASPBERRY_PI_PICO, ARDUINO_GENERIC_RP2040 */



#ifdef TEENSYDUINO
#include <Audio.h> /* required to access teensy audio defines */
#endif


/*
 * Configuration for
 * Board: "LOLIN(WEMOS) D1 R2 & mini 2 or similar
 */
#ifdef ESP8266

#define SWAP_SERIAL
#define I2S_NODAC /* RX pin will be used for audio output */
#define LED_PIN     LED_BUILTIN

#define MIDI_PORT_ACTIVE

#ifndef SWAP_SERIAL
#define RXD2 13 /* U2RRXD, D7 */
#define TXD2 15 /* U2RRXD, D0 */
#include <SoftwareSerial.h>
SoftwareSerial Serial2(RXD2, TXD2);
#define MIDI_PORT2_ACTIVE
#endif

#define SAMPLE_RATE 44100
#define SAMPLE_BUFFER_SIZE 48

#endif /* ESP8266 */

/*
 * Configuration for
 * Board: "ESP32 Dev Module" or similar
 */
#if (defined ESP32) && (! defined ARDUINO_LOLIN_S2_MINI)

#define BOARD_ML_V1 /* activate this when using the ML PCB V1 */
//#define BOARD_ESP32_AUDIO_KIT_AC101 /* activate this when using the ESP32 Audio Kit v2.2 with the AC101 codec */
//#define BOARD_ESP32_AUDIO_KIT_ES8388 /* activate this when using the ESP32 Audio Kit v2.2 with the ES8388 codec */
//#define BOARD_ESP32_DOIT /* activate this when using the DOIT ESP32 DEVKIT V1 board */
//#define BOARD_WEMOS_D1_MINI_ESP32
//#define BOARD_TTGO_T9_RGB_LED_WM8978 /* activate this when using the TTGO T9 Audio Kit with the WM8978 codec */

#define SAMPLE_BUFFER_SIZE  (48) /* 48 1kHz testtone */
#define SAMPLE_RATE  48000


#if 0 /* setup */

//#define MIDI_STREAM_PLAYER_ENABLED

//#define I2C_SCL 22
//#define I2C_SDA 21

#define BLINK_LED_PIN     2



//#define I2S_DIN_PIN    32


/* MCLK: Master clock line. It’s an optional signal depends on slave side, mainly used for offering a reference clock to the I2S slave device. */

#define SPI_SCK     18
#define SPI_MISO    19
#define SPI_MOSI    23
#define SPI_SS      5

#define BLINK_LED_PIN     2
//#define SAMPLE_SIZE_32BIT
//#define SAMPLE_RATE 44100
#define SAMPLE_BUFFER_SIZE  (48) /* 48 1kHz testtone */

#define CODEC_RST_PIN   16

#define I2S_USE_APLL
#endif /* testsetup */




//#define INPUT_TO_MIX /* use this to mix the input to the organ signal */

#define LED_PIN     BLINK_LED_PIN

#define REVERB_ENABLED /* add simple reverb */

#define MAX_DELAY   (SAMPLE_RATE/4)

//#define MIDI_STREAM_PLAYER_ENABLED /* activate this to use the midi stream playback module */

/* use this to display a scope on the oled display */
//#define OLED_OSC_DISP_ENABLED

//#define MIDI_BLE_ENABLED
// #define BLE_MIDI_CLIENT



/*
 * use MIDI_BLE_ENABLED to activate the MIDI BLE functionality
 * you might turn off the delay and reverb due to the high heap consumption
 * MIDI BLE will be set as SERVER if MIDI_BLE_CLIENT is deactivated
 * Turn on MIDI_BLE_DEBUG_ENABLED to get some debug messages.
 * @see https://youtu.be/awurJEY8X10
 */
//#define MIDI_BLE_ENABLED
//#define MIDI_BLE_CLIENT /* configured as client it will start to search for the server to connect to */
//#define MIDI_BLE_DEBUG_ENABLED

/*
 * include the board configuration
 * there you will find the most hardware depending pin settings
 */
#include <ml_boards.h> /* requires the ML_Synth library:  https://github.com/marcel-licence/ML_SynthTools */

#ifdef BOARD_ML_V1
#elif (defined BOARD_ESP32_AUDIO_KIT_AC101)
#elif (defined BOARD_ESP32_AUDIO_KIT_ES8388)
#elif (defined BOARD_ESP32_DOIT)
#elif (define BOARD_TTGO_T9_RGB_LED_WM8978)


#define MIDI_PORT2_ACTIVE
#define MIDI_RX2_PIN RXD2


/* you can activate the following lines to get an additional MIDI input */
// MIDI_PORT1_ACTIVE
// #define MIDI_RX1_PIN 13
#endif

#define SAMPLE_SIZE_16BIT



/* MIDI_VIA_USB_ENABLED activates MIDI via USB (please look into usbMidiHost.ino for more information) */
//#define MIDI_VIA_USB_ENABLED

#endif /* ESP32 */


#ifdef ARDUINO_LOLIN_S2_MINI

#define SAMPLE_SIZE_32BIT
#define SAMPLE_BUFFER_SIZE  48
#define I2S_NODAC
#define BLINK_LED_PIN 15

#endif

/*
 * Configuration for
 * Board: "Teensy 4.1"
 *
 * BCK: 21
 * DIN: 7
 * LCK: 20
 */
#ifdef TEENSYDUINO // CORE_TEENSY



//#define USB_HOST_ENABLED

//#define OLED_OSC_DISP_ENABLED

#define LED_PIN 13 /* led pin on teensy 4.1 */
#define BLINK_LED_PIN LED_PIN
#define MIDI_PORT1_ACTIVE
#define MIDI_SERIAL1_BAUDRATE   31250
#define SAMPLE_BUFFER_SIZE AUDIO_BLOCK_SAMPLES
#define SAMPLE_RATE AUDIO_SAMPLE_RATE


#if (defined USB_MIDI_AUDIO_SERIAL) || (defined USB_MIDI) || (defined USB_MIDI_SERIAL)
#define USB_MIDI_ENABLED
#endif

#if (defined USB_MIDI_AUDIO_SERIAL) || (defined USB_AUDIO)
#define USB_AUDIO_ENABLED
#endif

#define AUDIO_CS42448

#endif /* TEENSYDUINO */

/*
 * Configuration for
 * Board: "Generic STM32H7 Series"
 * Board part number: "Daisy Seed"
 */
#ifdef ARDUINO_DAISY_SEED

#define LED_PIN LED_BUILTIN
#define SAMPLE_BUFFER_SIZE  48
#define SAMPLE_RATE 48000

#define MIDI_PORT2_ACTIVE
#define MIDI_BAUDRATE   31250

#define REVERB_ENABLED /* add simple reverb */

#define MAX_DELAY   (SAMPLE_RATE * 2)

#endif /* ARDUINO_DAISY_SEED */

/*
 * Configuration for
 * Board: "Seeeduino XIAO"
 */
#ifdef ARDUINO_SEEED_XIAO_M0

#define LED_PIN LED_BUILTIN
#define SAMPLE_BUFFER_SIZE  48
#define SAMPLE_RATE  22050

#define MIDI_PORT1_ACTIVE

#endif /* ARDUINO_SEEED_XIAO_M0 */

/*
 * Configuration for
 * Board: "Generic STM32F4 Series"
 * Board part number: "Generic F407VGTx"
 *
 * does not work at the moment
 */
#ifdef ARDUINO_GENERIC_F407VGTX

#include <ml_boards.h> /* requires the ML_Synth library:  https://github.com/marcel-licence/ML_SynthTools */

#define BLINK_LED_PIN LED_USER_RED
#define LED_PIN LED_USER_GREEN

#define SAMPLE_BUFFER_SIZE  48
#define SAMPLE_RATE  44100

#define MIDI_PORT2_ACTIVE

#endif /* ARDUINO_GENERIC_F407VGTX */


#ifdef ARDUINO_DISCO_F407VG

/*
 * pro organ seems not to work. Maybe too slow?
 */

#include <ml_boards.h> /* requires the ML_Synth library:  https://github.com/marcel-licence/ML_SynthTools */

#define BLINK_LED_PIN LED_USER_RED
#define LED_PIN LED_USER_GREEN

#define SAMPLE_BUFFER_SIZE  48
#define SAMPLE_RATE  44100

//#define MIDI_PORT1_ACTIVE /* MIDI in : PIN A10  not tested*/
#define MIDI_PORT2_ACTIVE /* MIDI in : PIN A3 */

#endif /* ARDUINO_DISCO_F407VG */


#ifdef ARDUINO_BLACK_F407VE
/*
 * from variant.h
 * LED_BUILTIN: PA6
 * LED1_BUILTIN: PA7
 *
 * USER_BUTTON0: PA0
 * USER_BUTTON1: PE3
 * USER_BUTTON2: PE4
 *
 * SDA: PB7
 * SCL: PB6
 *
 * @see http://wiki.stm32duino.com/images/5/5c/STM32_F4VE_SCHEMATIC.PDF
 */
#define BLINK_LED_PIN LED_BUILTIN /* PA6 */
#define LED_PIN LED_BUILTIN

#define SAMPLE_BUFFER_SIZE  48
#define SAMPLE_RATE  44100

/*
 * define your I2S interface here!
 * values are just example values and will not work
 */
#define I2S_I2SN    SPI1 // Using SPI1 for I2S
#define I2S_MCLK    PC7 // I2S1_MCK
#define I2S_SCLK    PC10 // I2S1_CK
#define I2S_SDIN    PC12 // I2S1_SD mcu out -> dac in
#define I2S_LRCK    PA4 // I2S1_WS

#endif /* DARDUINO_BLACK_F407VE */


#ifdef ARDUINO_BLUEPILL_F103C8

#define BLINK_LED_PIN LED_BUILTIN
#define LED_PIN LED_BUILTIN

#define SAMPLE_BUFFER_SIZE  48
#define SAMPLE_RATE  44100

/*
 * define your I2S interface here!
 * values are just example values and will not work
 */
#define I2S_I2SN    SPI1 // Using SPI1 for I2S
#define I2S_MCLK    PB7 // I2S1_MCK
#define I2S_SCLK    PC15 // I2S1_CK
#define I2S_SDIN    PC9 // I2S1_SD mcu out -> dac in
#define I2S_LRCK    PA4 // I2S1_WS

#endif /* ARDUINO_BLUEPILL_F103C8 */


#ifdef ARDUINO_BLUE_F103VE

#define BLINK_LED_PIN LED_BUILTIN
#define LED_PIN LED_BUILTIN

#define SAMPLE_BUFFER_SIZE  48
#define SAMPLE_RATE  44100

/*
 * define your I2S interface here!
 * values are just example values and will not work
 */
#define I2S_I2SN    SPI1 // Using SPI1 for I2S
#define I2S_MCLK    PC7 // I2S1_MCK
#define I2S_SCLK    PC10 // I2S1_CK
#define I2S_SDIN    PC12 // I2S1_SD mcu out -> dac in
#define I2S_LRCK    PA4 // I2S1_WS

#endif /* ARDUINO_BLUE_F103VE */

#define MIDI_FMT_INT
#ifndef MIDI_BAUDRATE
#define MIDI_BAUDRATE   31250
#endif

#endif /* CONFIG_H_ */

