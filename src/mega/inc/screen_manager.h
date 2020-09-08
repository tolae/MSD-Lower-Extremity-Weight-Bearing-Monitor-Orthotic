#ifndef SCREEN_MANAGER_H
#define SCREEN_MANAGER_H

class ScreenManager
{
    public:
        ScreenManager();

        void update();
        Screen get_current_screen();
        void switch_screen(Screen);
        void switch_screen_params(Screen, void*);
    
    private:
        Screen current_screen;
};

extern ScreenManager scrn_mngr;

#endif
