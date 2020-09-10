#include <Arduino.h>
#include "inc/screen_manager.h"

ScreenManager::ScreenManager()
{
    current_screen = NULL;
}

void ScreenManager::update()
{
    if (current_screen != NULL)
    {
        current_screen->update();
    }
}

Screen* ScreenManager::get_current_screen()
{
    return current_screen;
}

void ScreenManager::init_screen(Screen* first_screen)
{
    init_screen(first_screen, NULL);
}

void ScreenManager::init_screen(Screen* first_screen, void* data)
{
    first_screen->load(data);
    first_screen->visible(true);
    current_screen = first_screen;
}

void ScreenManager::switch_screen(Screen* dst_screen)
{
    const void *unloaded_data = NULL;

    if (current_screen != NULL)
    {
        unloaded_data = current_screen->unload();
        current_screen->visible(false);
    }
    if (dst_screen != NULL)
    {
        dst_screen->load(unloaded_data);
        dst_screen->visible(true);
    }
    current_screen = dst_screen;
}
