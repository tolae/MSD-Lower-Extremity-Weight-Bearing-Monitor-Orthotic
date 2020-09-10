#include <Arduino.h>
#include "inc/screen_manager.h"

ScreenManager::ScreenManager()
{
    current_screen = NULL;
}

ScreenManager::update()
{
    if (current_screen != NULL)
    {
        current_screen.update();
    }
}

ScreenManager::get_current_screen()
{
    return current_screen;
}

ScreenManager::switch_screen(Screen* src_screen, Screen* dst_screen)
{
    const void *unloaded_data = NULL;

    if (src_screen != NULL)
    {
        unloaded_data = src_screen.unload();
        src_screen.visible(false);
    }
    if (dst_screen != NULL)
    {
        dst_screen.load(unloaded_data);
        dst_screen.visible(true);
    }
    current_screen = dst_screen;
}
