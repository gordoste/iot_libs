#include "TFTUtils.h"

void TFTUtils::fillWindow(TFT_eSPI *tft, Window win, uint32_t fillColor) {
    tft->fillRect(win.x, win.y, win.width, win.height, fillColor);
}

void TFTUtils::ignoreTouch(uint16_t x, uint16_t y, bool absolute) { return; }

void TFTUtils::drawBorderRect(TFT_eSPI *tft, Window win, uint32_t fillColor, LineProperties borderProps) {
    for (int i = 0; i < borderProps.width; i++) {
        tft->drawRect(win.x + i, win.y + i, win.width - (2 * i), win.height - (2 * i), borderProps.color);
    }
    tft->fillRect(win.x + borderProps.width, win.y + borderProps.width,
                  win.width - (2 * borderProps.width), win.height - (2 * borderProps.width), fillColor);
}

void TFTUtils::touchCalibrate(TFT_eSPI *tft, const char *calFileName, bool forceCalibrate) {
    uint16_t calData[5];
    uint8_t calDataOK = 0;

    // check if calibration file exists
    if (SPIFFS.exists(calFileName)) {
        File f = SPIFFS.open(calFileName, "r");
        if (f) {
            size_t rd = f.readBytes((char *)calData, 14);
            if (rd == 14) {
                calDataOK = 1;
            }
            f.close();
        }
    }
    if (calDataOK && !forceCalibrate) {
        // calibration data valid
        tft->setTouch(calData);
    } else {
        tft->fillScreen(TFT_BLACK);
        tft->setTextColor(TFT_WHITE, TFT_BLACK);
        tft->setTextSize(1);
        tft->setCursor(20, 0, 2);
        tft->println("calibration run");
        // data not valid. recalibrate
        tft->calibrateTouch(calData, TFT_MAGENTA, TFT_BLACK, 15);
        // store data
        File f = SPIFFS.open(calFileName, "w");
        if (f) {
            f.write((const unsigned char *)calData, 14);
            f.close();
        }
    }
}

bool TFTUtils::contains(Window &w, uint16_t x, uint16_t y) {
    if (x < w.x || x > w.x + w.width) return false;
    if (y < w.y || y > w.y + w.height) return false;
    return true;
}