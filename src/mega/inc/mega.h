#ifndef MEGA_H
#define MEGA_H

#include <GuiLibrary.h>
#include "screen.h"
#include "screen_manager.h"

/** The global gui from the GuiLibrary. */
extern Gui gui;

/** The global screen manager that will handle all the screens. */
extern ScreenManager* screen_manager;

/** The global screen array that will contain all the screens. */
extern const Screen* SCREENS[];

#endif
