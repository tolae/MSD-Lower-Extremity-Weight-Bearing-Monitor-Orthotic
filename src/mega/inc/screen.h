#ifndef SCREEN_H
#define SCREEN_H

#include <GuiLibrary.h>

/**
 * @brief Base class for all load data.
 * 
 */
class BaseLoadData
{
    // Nothing here
};

/**
 * @brief Base screen class. Derives from GuiElement to contain child elemnts.
 * 
 */
class Screen : public GuiElement {
	public:
		/**
		 * @brief Removes the given child elemnt from the screen.
		 * 
		 * @param e The element to remove.
		 */
		void removeChild(GuiElement e);

		/**
		 * @brief Configures the screen with the given parameters.
		 * 
		 * This is specific to the screen being constructed. These parameters
		 * are passed in from the unload"()" step of the current/calling screen.
		 * 
		 * @param param The parameters to load.
		 */
		virtual void load(const BaseLoadData* param) = 0;

		/**
		 * @brief Preserves parameters that are passed from screen to screen.
		 * 
		 * For example, the keypad screen would return the text a user has
		 * entered as an integer.
		 * 
		 * @return const BaseLoadData* The parameters to preserve.
		 */
		virtual const BaseLoadData* unload() = 0;
		
		/**
		 * @brief Called during the update cycle of the main loop.
		 * 
		 * This should contain any logic that periodically checks for external
		 * information such as Serial communications.
		 * 
		 */
		virtual void update() = 0;
};

#endif
