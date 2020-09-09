#ifndef KEYPAD_SCREEN_H
#define KEYPAD_SCREEN_H

#include <GuiLibrary.h>
#include "screen.h"

class KeypadScreen : Screen
{
    public:
        KeypadScreen();

        void load(void *);
        void *unload();
        void update();
    
    private:
        GuiLabel *str_val_lbl;
        GuiButton *button0;
        GuiButton *button1;
        GuiButton *button2;
        GuiButton *button3;
        GuiButton *button4;
        GuiButton *button5;
        GuiButton *button6;
        GuiButton *button7;
        GuiButton *button8;
        GuiButton *button9;
        GuiButton *button_bksp;
        GuiButton *button_save;
};

#endif
