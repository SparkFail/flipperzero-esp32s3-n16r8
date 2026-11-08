#ifndef SCREEN_PROFILES_H
#define SCREEN_PROFILES_H

/* ==========================================================================
 *  屏幕配置档案
 *
 *  TFT_eSPI 的驱动型号和分辨率是编译期定死的，不能在运行时自动识别，
 *  所以这里做成"一个屏一个档案"，编译时用 -D 参数选一个：
 *
 *      pio run -e s3-n16r8-multitool          -> 默认，1.44" ST7789 128x128
 *      pio run -e s3-n16r8-screen-240         -> 1.3"  ST7789 240x240
 *      pio run -e s3-n16r8-screen-240x320     -> 2.0"  ST7789 240x320
 *      pio run -e s3-n16r8-screen-7735-160    -> 1.8"  ST7735 128x160
 *      pio run -e s3-n16r8-screen-7735-80     -> 0.96" ST7735 80x160
 *      pio run -e s3-n16r8-screen-ili9341     -> 2.8"  ILI9341 240x320
 *
 *  接线（BL/RST/DC/CS/MOSI/SCLK）在 pins_arduino.h 里，所有档案共用，
 *  换屏不用改线，只要换档案重新编译。
 *
 *  常见微调（改本文件里对应档案的那几行）：
 *    - 红蓝反了        : TFT_RGB_ORDER  0 <-> 1
 *    - 画面像底片      : 打开 TFT_INVERSION_ON
 *    - 花屏 / 条纹     : SPI_FREQUENCY 调低（40000000 -> 27000000 -> 20000000）
 *    - 方向不对        : ROTATION 改 0/1/2/3
 * ========================================================================== */

/* 没有指定任何档案时，默认 1.44" ST7789 */
#if !defined(SCREEN_ST7789_128) && !defined(SCREEN_ST7789_240) &&       \
    !defined(SCREEN_ST7789_240X320) && !defined(SCREEN_ST7735_128X160) && \
    !defined(SCREEN_ST7735_80X160) && !defined(SCREEN_ILI9341_240X320)
#define SCREEN_ST7789_128
#endif

#define HAS_SCREEN 1
#define MINBRIGHT (uint8_t)1
#define USER_SETUP_LOADED 1
#define SMOOTH_FONT 1

/* -------------------------------------------------------------------------
 * 1.44"  ST7789  128x128   (默认)
 * ---------------------------------------------------------------------- */
#if defined(SCREEN_ST7789_128)
#define ST7789_DRIVER 1
#define TFT_WIDTH 128
#define TFT_HEIGHT 128
#define TFT_RGB_ORDER 0
#define ROTATION 1
#define SPI_FREQUENCY 27000000
#define SPI_READ_FREQUENCY 16000000
#define SCREEN_NAME "1.44in ST7789 128x128"

/* -------------------------------------------------------------------------
 * 1.3"   ST7789  240x240
 * ---------------------------------------------------------------------- */
#elif defined(SCREEN_ST7789_240)
#define ST7789_DRIVER 1
#define TFT_WIDTH 240
#define TFT_HEIGHT 240
#define TFT_RGB_ORDER 0
#define TFT_INVERSION_ON
#define ROTATION 0
#define SPI_FREQUENCY 40000000
#define SPI_READ_FREQUENCY 16000000
#define SCREEN_NAME "1.3in ST7789 240x240"

/* -------------------------------------------------------------------------
 * 2.0"   ST7789  240x320
 * ---------------------------------------------------------------------- */
#elif defined(SCREEN_ST7789_240X320)
#define ST7789_DRIVER 1
#define TFT_WIDTH 240
#define TFT_HEIGHT 320
#define TFT_RGB_ORDER 0
#define ROTATION 0
#define SPI_FREQUENCY 40000000
#define SPI_READ_FREQUENCY 16000000
#define SCREEN_NAME "2.0in ST7789 240x320"

/* -------------------------------------------------------------------------
 * 1.8"   ST7735  128x160
 * ---------------------------------------------------------------------- */
#elif defined(SCREEN_ST7735_128X160)
#define ST7735_DRIVER 1
#define TFT_WIDTH 128
#define TFT_HEIGHT 160
#define TFT_RGB_ORDER 0
#define TFT_INVERSION_OFF
#define ROTATION 1
#define SPI_FREQUENCY 27000000
#define SPI_READ_FREQUENCY 16000000
#define SCREEN_NAME "1.8in ST7735 128x160"

/* -------------------------------------------------------------------------
 * 0.96"  ST7735  80x160
 * ---------------------------------------------------------------------- */
#elif defined(SCREEN_ST7735_80X160)
#define ST7735_DRIVER 1
#define TFT_WIDTH 80
#define TFT_HEIGHT 160
#define TFT_RGB_ORDER 1
#define TFT_INVERSION_ON
#define ROTATION 1
#define SPI_FREQUENCY 27000000
#define SPI_READ_FREQUENCY 16000000
#define SCREEN_NAME "0.96in ST7735 80x160"

/* -------------------------------------------------------------------------
 * 2.8"   ILI9341  240x320
 * ---------------------------------------------------------------------- */
#elif defined(SCREEN_ILI9341_240X320)
#define ILI9341_DRIVER 1
#define TFT_WIDTH 240
#define TFT_HEIGHT 320
#define TFT_RGB_ORDER 0
#define ROTATION 0
#define SPI_FREQUENCY 40000000
#define SPI_READ_FREQUENCY 16000000
#define SCREEN_NAME "2.8in ILI9341 240x320"
#endif

#endif /* SCREEN_PROFILES_H */
