#ifndef _TFT_UTILS_H
#define _TFT_UTILS_H

#include <Arduino.h>
#include "FS.h"
#include "TFT_eSPI.h"

#ifdef TFT_ENABLED

struct Point {
  uint32_t x;
  uint32_t y;
};

struct Window {
  uint32_t x;
  uint32_t y;
  int16_t width;
  int16_t height;
};

struct LineProperties {
  uint32_t color;
  uint8_t width;
};

const LineProperties DefaultBorder = { TFT_WHITE, 1 };

typedef std::function<void(TFT_eSPI *tft)> TFTHandler;

typedef std::function<void(uint16_t x, uint16_t y)> TouchHandler;

namespace TFTUtils {
  void ignoreTouch(uint16_t x, uint16_t y);
  bool contains(Window &w, uint16_t x, uint16_t y);
  void fillWindow(TFT_eSPI *tft, Window win, uint32_t fillColor);
  void drawBorderRect(TFT_eSPI *tft, Window win, uint32_t fillColor, LineProperties borderProps = DefaultBorder);
  // Read calibration data from file given, or calibrate and then save it there
  void touchCalibrate(TFT_eSPI *tft, const char *calFileName, bool forceCalibrate = false);
};

class TouchControl {
  protected:
    Window *m_win;
    TouchHandler m_touchHandler = TFTUtils::ignoreTouch;
  public:
    Window *getWindow();
    void handleTouch(uint16_t x, uint16_t y); // must be relative to control position
};

#endif // #ifdef TFT_ENABLED

#endif // #ifndef _TFT_UTILS_H