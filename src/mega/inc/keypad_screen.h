#ifndef KEYPAD_SCREEN_H
#define KEYPAD_SCREEN_H

#include <GuiLibrary.h>
#include "screen.h"

class KeypadLoadData
{
    public:
        Screen* calling_screen;
        char* init_str_val_lbl_txt;

        KeypadLoadData(Screen* screen, char* txt) :
            calling_screen(screen),
            init_str_val_lbl_txt(txt)
            {}
};

class KeypadScreen : public Screen
{
    public:
        KeypadScreen(int16_t x, int16_t y, int16_t width, int16_t height);

        void load(const void *);
        const void *unload();
        void update();

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

        Screen* calling_screen;
};

#endif
