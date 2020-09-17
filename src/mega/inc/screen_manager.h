#ifndef SCREEN_MANAGER_H
#define SCREEN_MANAGER_H

#include "screen.h"

/**
 * @brief Handles the logic for screen transitions and parameter passing.
 * 
 */
class ScreenManager
{
	public:
		/**
		 * @brief Construct a new Screen Manager object.
		 * 
		 */
		ScreenManager();

		/**
		 * @brief Called during the update cycle of the main loop.
		 * 
		 * This also calls the update function of the current screen.
		 * 
		 */
		void update();

		/**
		 * @brief Get the current screen object.
		 * 
		 * @return Screen* The current screen object.
		 */
		Screen* get_current_screen();

		/**
		 * @brief Initializes the screen manager object with the new screen.
		 * 
		 * This makes the screen visible and loads it with no parameters.
		 * 
		 * @param screen The screen to initialize with.
		 */
		void init_screen(Screen* screen);

		/**
		 * @brief Initializes the screen manager object with the new screen.
		 * 
		 * This makes the screen visible and loads it with the given parameters.
		 * 
		 * @param screen The screen to initialize with.
		 * @param params The parameter to load the screen with.
		 */
		void init_screen(Screen* screen, void* params);

		/**
		 * @brief Transitions from the current screen to the new screen.
		 * 
		 * This will pass any unload parameters from the current screen to the
		 * new screen.
		 * 
		 * @param screen The new screen to load.
		 */
		void switch_screen(Screen* new_screen);
	
	private:
		/**
		 * @brief The current screen that is visible.
		 * 
		 */
		Screen* current_screen;
};

#endif
