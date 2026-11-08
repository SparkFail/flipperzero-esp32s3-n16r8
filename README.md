# flipperzero-esp32s3-n16r8
A small gadget based on ESP32-S3 N16R8 with functions similar to Flipper Zero. It supports multiple screens:  - 1.44″ 128×128 ST7789 (default) - 1.3″ 240×240 ST7789 `-Screen 240` - 2.0″ 240×320 ST7789 `-Screen 240x320` - 1.8″ 128×160 ST7735 `-Screen 7735-160` - 0.96″ 80×160 ST7735 `-Screen 7735-80` - 2.8″ 240×320 ILI9341 `-Screen ili9341`
# flipperzero-esp32s3-n16r8
A small gadget based on ESP32-S3 N16R8 with functions similar to Flipper Zero.

## Supported Displays
- 1.44″ 128×128 ST7789 (default)
- 1.3″ 240×240 ST7789
- 2.0″ 240×320 ST7789
- 1.8″ 128×160 ST7735
- 0.96″ 80×160 ST7735
- 2.8″ 240×320 ILI9341

## Project Contents
- Wiring diagram
- User manual
- Prebuilt firmware `.bin` files
- Flash tools & flash config
- Log viewer
- Board configuration

## Prebuilt Firmware
Ready-to-flash `.bin` firmware files are located in the `固件` folder.
Default firmware is compiled for the 1.44" ST7789 screen.
Use the flash tool inside the `工具` folder to write firmware to ESP32-S3 directly.

## Rebuild Source Code
You can open the project in VSCode with PlatformIO extension.
All other screen options are commented out in source code.
Just uncomment the target screen definition and recompile.
