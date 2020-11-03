#ifndef MEGA_H
#define MEGA_H

#include <GuiLibrary.h>
#include <Adafruit_HX8357.h>
#include "screen.h"
#include "screen_manager.h"
#include "Volume.h"

/** The global gui from the GuiLibrary. */
extern Gui gui;
extern Adafruit_HX8357 tft;

/** The global screen manager that will handle all the screens. */
extern ScreenManager* screen_manager;

/** The global screen array that will contain all the screens. */
extern const Screen* SCREENS[];

extern Volume speaker_vol;

enum ScreenIndex
{
    KEYPAD = 0,
    HOME = 1,
    SETTINGS = 2,
};

#endif
