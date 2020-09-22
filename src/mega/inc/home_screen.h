#ifndef HOME_SCREEN_H
#define HOME_SCREEN_H

#include <GuiLibrary.h>
#include "screen.h"

class HomeLoadData
{
public:
    uint32_t weight;
    uint32_t tolerance;

    HomeLoadData(uint32_t w, uint32_t t) :
        weight(w),
        tolerance(t)
    {}
};

class HomeScreen : public Screen
{
public:
    HomeScreen(int16_t x, int16_t y, int16_t width, int16_t height);

    void load(const void*);
    void* unload();
    void update();

    GuiLabel* str_val_TS;
    GuiLabel* str_val_FS;
    GuiLabel* str_val_Percentage;
    GuiLabel* str_val_Weight;
    GuiLabel* str_val_Tolerance;
    GuiButton* buttonSettings;

};

#endif