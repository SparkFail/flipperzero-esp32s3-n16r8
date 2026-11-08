#ifndef Pins_Arduino_h
#define Pins_Arduino_h

#include "soc/soc_caps.h"
#include <stdint.h>

/* ==========================================================================
 *  ESP32-S3 N16R8  (16 MB QSPI flash + 8 MB OPI PSRAM)
 *  Custom "Flipper-like" build:
 *      ST7789 1.44" 128x128  +  microSD  +  CC1101  +  PN532 (I2C)
 *
 *  GPIOs that are NOT usable on this module:
 *      26..32  -> SPI flash
 *      33..37  -> octal PSRAM (R8)
 *      19, 20  -> native USB D-/D+
 *      43, 44  -> UART0 (kept for serial log)
 * ========================================================================== */

// UART0
#define SERIAL_TX 43
#define SERIAL_RX 44
static const uint8_t TX = SERIAL_TX;
static const uint8_t RX = SERIAL_RX;

// USB HID (BadUSB) on the native USB port
#define USB_as_HID 1

/* ---------------------------- I2C : PN532 ------------------------------- */
/* GPIO 48 drives the on-board RGB LED of the DevKitC-1, so it is avoided. */
#define GROVE_SDA 21
#define GROVE_SCL 18
#define SYS_I2C_SDA 21
#define SYS_I2C_SCL 18
static const uint8_t SDA = SYS_I2C_SDA;
static const uint8_t SCL = SYS_I2C_SCL;

/* ------------------- SPI bus A : ST7789 + microSD ----------------------- */
#define SPI_SCK_PIN 12
#define SPI_MOSI_PIN 11
#define SPI_MISO_PIN 13
#define SPI_SS_PIN 10
static const uint8_t SS = SPI_SS_PIN;
static const uint8_t MOSI = SPI_MOSI_PIN;
static const uint8_t MISO = SPI_MISO_PIN;
static const uint8_t SCK = SPI_SCK_PIN;

/* ------------------- SPI bus B : CC1101 (own bus) ----------------------- */
#define CC1101_SPI_SCK 5
#define CC1101_SPI_MOSI 4
#define CC1101_SPI_MISO 15

/* ------------------------------ BUTTONS --------------------------------- */
#define BTN_ALIAS "\"OK\""
#define HAS_5_BUTTONS
#define SEL_BTN 0   // BOOT button of the devkit, also wake-up pin
#define UP_BTN 41
#define DW_BTN 40
#define L_BTN 39
#define R_BTN 38
#define ESC_BTN 42
#define BTN_ACT LOW

// No IR LED / receiver installed
#define RXLED -1
#define TXLED -1
#define LED_ON HIGH
#define LED_OFF LOW

/* ------------------------------- CC1101 --------------------------------- */
#define USE_CC1101_VIA_SPI
#define CC1101_GDO0_PIN 17
#define CC1101_SS_PIN 16
#define CC1101_MOSI_PIN CC1101_SPI_MOSI
#define CC1101_SCK_PIN CC1101_SPI_SCK
#define CC1101_MISO_PIN CC1101_SPI_MISO

/* -------------------------------- FONTS --------------------------------- */
#define FP 1
#define FM 2
#define FG 3

/* --------------------------- 屏幕配置档案 -------------------------------- */
/* 驱动型号、分辨率、颜色顺序、SPI 频率、旋转角都在 screen_profiles.h，
 * 用编译参数 -DSCREEN_xxx 选档案；不指定就是 1.44" ST7789 128x128。
 * 下面这些是接线引脚，所有档案共用，换屏不用改线。                  */
#include "screen_profiles.h"

#define TFT_BACKLIGHT_ON 1
#define TFT_BL 7
#define TFT_RST 8
#define TFT_DC 9
#define TFT_MISO -1
#define TFT_MOSI SPI_MOSI_PIN
#define TFT_SCLK SPI_SCK_PIN
#define TFT_CS 10
#define TOUCH_CS -1

/* ------------------------------ microSD --------------------------------- */
#define SDCARD_CS 6
#define SDCARD_SCK SPI_SCK_PIN
#define SDCARD_MISO SPI_MISO_PIN
#define SDCARD_MOSI SPI_MOSI_PIN

#endif /* Pins_Arduino_h */
