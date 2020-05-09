#ifndef _MENU_H
#define _MENU_H

#include "StringUtils.h"

#define MAX_CHOICES 20

#include "TouchControl.h"

typedef std::function<const char *(uint8_t cell_nr)> TLabel_Getter;
typedef std::function<uint32_t(uint8_t cell_nr)> TColor_Getter;

class Menu : public TouchControl {
    static const char *DEFAULT_LABEL_GETTER(uint8_t _cellNum) { return "-"; }
    static uint32_t MENU_WHITE_GETTER(uint8_t _cellNum) { return TFT_WHITE; }
    static uint32_t MENU_BLACK_GETTER(uint8_t _cellNum) { return TFT_BLACK; }

public:
    void init() {};
    void show();
    void showText(const char *str);
    bool isShown() { return m_shown; }

    void onCellLabelPrint(TFTHandler fn) { m_onCellLabelPrint = fn; };

    int8_t getSelectedChoice();
    Menu *setSelectedChoice(int8_t c);

    Menu *setChoiceBorderProps(LineProperties &_props);
    Menu *setSelectedBorderProps(LineProperties &_props);

    Menu *setNumChoices(uint8_t _n, uint8_t _x, uint8_t _y);
    Menu *setNumChoices(uint8_t _n) { return setNumChoices(_n, 1, _n); };
    uint8_t getNumChoices() { return m_numChoices; }

    Menu *setLabelGetter(TLabel_Getter _lg) {
        m_labelGetter = _lg;
        return this;
    }
    Menu *setFillColorGetter(TColor_Getter _cg) {
        m_fillColorGetter = _cg;
        return this;
    }

protected:
    TFTHandler m_onCellLabelPrint = NULL;
    const char **m_cellLabels;
    const char *m_allChoices[MAX_CHOICES];
    uint32_t m_divX, m_divY;
    uint8_t m_currentDiv[2] = {0, 0}; // which cell are we drawing
    uint8_t m_xDivs, m_yDivs;
    uint8_t m_selectedChoice;
    uint8_t m_numChoices;
    Window m_currentCell;
    uint8_t m_currentCellNum;
    TLabel_Getter m_labelGetter = DEFAULT_LABEL_GETTER;
    TColor_Getter m_fillColorGetter = MENU_BLACK_GETTER;
    LineProperties m_choiceBorderProps = DefaultBorder;
    LineProperties m_selectedBorderProps = {TFT_RED, 3};

private:
    void getCell(uint8_t c);
    void drawCell(uint8_t _cellNum);
    void drawLabel(uint8_t _cellNum);
    void drawBorderAndFill(uint8_t _cellNum);
    void drawCell();
    void drawLabel();
    void drawBorderAndFill();
};

#endif //#ifndef _MENU_H