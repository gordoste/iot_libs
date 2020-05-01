#ifndef _TFT_UTILS_H
#define _TFT_UTILS_H

#include "FS.h"
#include "TFT_eSPI.h"
#include <Arduino.h>

#ifdef TFT_ENABLED

#define TFT_TOUCH_TIME 100 // ms to ignore touches after processing one

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

const LineProperties DefaultBorder = {TFT_WHITE, 1};

typedef std::function<void(TFT_eSPI *tft)> TFTHandler;

class TFTUtils {
public:
    static void ignoreTouch(uint16_t x, uint16_t y, bool absolute);
    static bool contains(Window &w, uint16_t x, uint16_t y);
    static void fillWindow(TFT_eSPI *tft, Window win, uint32_t fillColor);
    static void drawBorderRect(TFT_eSPI *tft, Window win, uint32_t fillColor, LineProperties borderProps = DefaultBorder);
    // Read calibration data from file given, or calibrate and then save it there
    static void touchCalibrate(TFT_eSPI *tft, const char *calFileName, bool forceCalibrate = false);
}; // namespace TFTUtils

#endif // #ifdef TFT_ENABLED

#endif // #ifndef _TFT_UTILS_H