#ifndef SCREEN_MANAGER_H
#define SCREEN_MANAGER_H

#include "screen.h"

class ScreenManager
{
    public:
        ScreenManager();

        void update();
        Screen* get_current_screen();
        void switch_screen(Screen*, Screen*);
    
    private:
        Screen* current_screen;
};

#endif
