#ifndef _TFT_UTILS_H
#define _TFT_UTILS_H

#include <Arduino.h>
#include "FS.h"
#include "TFT_eSPI.h"

#ifdef TFT_ENABLED

struct Window {
  uint32_t x;
  uint32_t y;
  int16_t width;
  int16_t height;
};

namespace TFTUtils {
  void drawBorderRect(TFT_eSPI *tft, Window win, uint32_t borderColor, uint32_t fillColor, uint8_t borderWidth = 1);
  // Read calibration data from file given, or calibrate and then save it there
  void touchCalibrate(TFT_eSPI *tft, const char *calFileName, bool forceCalibrate = false);
};

#endif // #ifdef TFT_ENABLED

#endif // #ifndef _TFT_UTILS_H