#ifndef HOME_SCREEN_H
#define HOME_SCREEN_H

#include <GuiLibrary.h>
#include "screen.h"

class HomeScreen : Screen
{
public:
    HomeScreen();

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