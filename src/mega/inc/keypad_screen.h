#ifndef KEYPAD_SCREEN_H
#define KEYPAD_SCREEN_H

#include <GuiLibrary.h>
#include "screen.h"

#define SAVE_BTN 10
#define BKSP_BTN 11

/**
 * @brief The data to load the keypad with.
 * 
 * This is the parameter structure the keypad expects.
 */
class KeypadLoadData : public BaseLoadData
{
	public:
		/** The screen to return to when the data has been entered. */
		Screen* calling_screen;
		/** The initial string value to load into the keypad label. */
		char* init_str_val_lbl_txt;

		/**
		 * @brief Construct a new Keypad Load Data object.
		 * 
		 * @param screen The screen to return to.
		 * @param txt The initial string value to load.
		 */
		KeypadLoadData(Screen* screen, char* txt) :
			calling_screen(screen),
			init_str_val_lbl_txt(txt)
		{}
};

/**
 * @brief Handles user input from a visible keypad.
 * 
 * TODO: Make this a "widget" that draws over the current screen rather than
 * making it its own screen.
 * 
 */
class KeypadScreen : public Screen
{
	public:
		/**
		 * @brief Construct a new Keypad Screen object.
		 * 
		 * The additional parameters are required from the base GuiElement
		 * class.
		 * 
		 * TODO: Let the base screen class handle this implementation.
		 * 
		 * @param x The x coordinate.
		 * @param y The y coordinate.
		 * @param width The width of the screen.
		 * @param height The height of the screen.
		 */
		KeypadScreen(int16_t _x, int16_t _y, int16_t _width, int16_t _height);

		/**
		 * @brief A pointer to the KeypadLoadData object to load.
		 * 
		 * @param params A pointer to the KeypadLoadData object.
		 */
		void load(const BaseLoadData* params);

		/**
		 * @brief Returns the string value that is contained within the keypad
		 * label when the save button is clicked.
		 * 
		 * @return const BaseLoadData* A pointer to the string that is contained in the
		 * keypad label.
		 */
		const BaseLoadData* unload();

		/**
		 * @brief Does nothing.
		 * 
		 */
		void update();

		/** The GuiLibrary label that holds the user input data. */
		GuiLabel *str_val_lbl;

		/** 0 Button */
		GuiButton *button0;
		/** 1 Button */
		GuiButton *button1;
		/** 2 Button */
		GuiButton *button2;
		/** 3 Button */
		GuiButton *button3;
		/** 4 Button */
		GuiButton *button4;
		/** 5 Button */
		GuiButton *button5;
		/** 6 Button */
		GuiButton *button6;
		/** 7 Button */
		GuiButton *button7;
		/** 8 Button */
		GuiButton *button8;
		/** 9 Button */
		GuiButton *button9;
		/** Backspace Button: Deletes an entry. */
		GuiButton *button_bksp;
		/** Save Button: Saves and switches back to the calling_screen */
		GuiButton *button_save;
		/** The previous screen that swapped to this one. */
		Screen* calling_screen;
};

#endif
