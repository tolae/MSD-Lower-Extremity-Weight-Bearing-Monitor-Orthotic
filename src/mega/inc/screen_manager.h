#ifndef SCREEN_MANAGER_H
#define SCREEN_MANAGER_H

#include "screen.h"

class ScreenManager
{
	public:
		ScreenManager();

		void update();
		Screen* get_current_screen();
		void init_screen(Screen*);
		void init_screen(Screen*, void*);
		void switch_screen(Screen*);
	
	private:
		Screen* current_screen;
};

#endif
