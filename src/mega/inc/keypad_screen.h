#ifndef KEYPAD_SCREEN_H
#define KEYPAD_SCREEN_H

#include "screen.h"

class KeypadScreen : Screen
{
    public:
        Screen();

        void load(void *);
        void *unload();
        void update();
    
    private:
        GuiLabel *string_val;
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

        const char *input;
        char output[4] = {0};
        int counter = 0;
};

#endif
