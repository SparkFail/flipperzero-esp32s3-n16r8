#include "core/bus_HAL.h"
#include "core/powerSave.h"
#include <Arduino.h>
#include <Wire.h>

/***************************************************************************************
** Function name: _setup_gpio()
** Description:   initial setup for the S3-N16R8 multi-tool board
***************************************************************************************/
void _setup_gpio() {
    // Buttons are wired to GND, active LOW, internal pull-ups enabled
    pinMode(SEL_BTN, INPUT_PULLUP);
    pinMode(UP_BTN, INPUT_PULLUP);
    pinMode(DW_BTN, INPUT_PULLUP);
    pinMode(L_BTN, INPUT_PULLUP);
    pinMode(R_BTN, INPUT_PULLUP);
    pinMode(ESC_BTN, INPUT_PULLUP);

    // Keep every SPI slave deselected while the buses come up
    pinMode(CC1101_SS_PIN, OUTPUT);
    digitalWrite(CC1101_SS_PIN, HIGH);
    pinMode(SDCARD_CS, OUTPUT);
    digitalWrite(SDCARD_CS, HIGH);
    pinMode(TFT_CS, OUTPUT);
    digitalWrite(TFT_CS, HIGH);

    bruceConfigPins.rfModule = CC1101_SPI_MODULE;
    bruceConfigPins.rfidModule = PN532_I2C_MODULE;
    bruceConfigPins.irRx = -1;
    bruceConfigPins.irTx = -1;

    // PN532 sits on the main I2C bus
    setSysI2CBus(&Wire);
    Wire.begin(SYS_I2C_SDA, SYS_I2C_SCL);
}

/***************************************************************************************
** Function name: getBattery()
** Description:   no fuel gauge on this build
***************************************************************************************/
int getBattery() { return 100; }

bool isCharging() { return false; }

/*********************************************************************
** Function: setBrightness
**********************************************************************/
void _setBrightness(uint8_t brightval) {
    if (TFT_BL < 0) return;
    if (brightval == 0) {
        analogWrite(TFT_BL, 0);
    } else {
        int bl = MINBRIGHT + round(((255 - MINBRIGHT) * brightval / 100.0));
        analogWrite(TFT_BL, bl);
    }
}

/*********************************************************************
** Function: InputHandler
** Handles PrevPress, NextPress, SelPress, AnyKeyPress and EscPress
**********************************************************************/
void InputHandler(void) {
    static unsigned long tm = 0;
    if (millis() - tm < 200 && !LongPress) return;

    bool _u = digitalRead(UP_BTN);
    bool _d = digitalRead(DW_BTN);
    bool _l = digitalRead(L_BTN);
    bool _r = digitalRead(R_BTN);
    bool _s = digitalRead(SEL_BTN);
    bool _e = digitalRead(ESC_BTN);

    if (!_s || !_u || !_d || !_r || !_l || !_e) {
        tm = millis();
        if (!wakeUpScreen()) AnyKeyPress = true;
        else return;
    }

    if (!_l) { PrevPress = true; }
    if (!_r) { NextPress = true; }
    if (!_u) {
        UpPress = true;
        PrevPagePress = true;
    }
    if (!_d) {
        DownPress = true;
        NextPagePress = true;
    }
    if (!_s) { SelPress = true; }
    if (!_e) { EscPress = true; }
}

/*********************************************************************
** Function: powerOff
**********************************************************************/
void powerOff() {
    if (TFT_BL >= 0) digitalWrite(TFT_BL, !TFT_BACKLIGHT_ON);
    esp_sleep_enable_ext0_wakeup((gpio_num_t)SEL_BTN, BTN_ACT);
    esp_deep_sleep_start();
}

/*********************************************************************
** Function: checkReboot
** Hold ESC + OK for 2 s to power the board off
**********************************************************************/
void checkReboot() {
    if (digitalRead(ESC_BTN) == BTN_ACT && digitalRead(SEL_BTN) == BTN_ACT) {
        uint32_t start = millis();
        while (digitalRead(ESC_BTN) == BTN_ACT && digitalRead(SEL_BTN) == BTN_ACT) {
            if (millis() - start > 2000) { delay(50); powerOff(); }
            delay(10);
        }
    }
}
