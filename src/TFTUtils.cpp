#include "TFTUtils.h"

void TFTUtils::drawBorderRect(TFT_eSPI *tft, Window win, uint32_t borderColor, uint32_t fillColor, uint8_t borderWidth /*= 1*/) {
  for (int i = 0; i < borderWidth; i++) {
    tft->drawRect(win.x+i, win.y+i, win.width-(2*i), win.height-(2*i), borderColor);
  }
  tft->fillRect(win.x+borderWidth, win.y+borderWidth, win.width-2*borderWidth, win.height-2*borderWidth, fillColor);
}

void TFTUtils::touchCalibrate(TFT_eSPI *tft, const char *calFileName, bool forceCalibrate) {
  uint16_t calData[5];
  uint8_t calDataOK = 0;

  tft->fillScreen(TFT_BLACK);
  tft->setTextColor(TFT_WHITE, TFT_BLACK);
  tft->setTextSize(1);
  tft->setCursor(20, 0, 2);

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
