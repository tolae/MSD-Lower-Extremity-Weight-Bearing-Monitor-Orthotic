#ifndef SETTINGS_SCREEN_H
#define SETTINGS_SCREEN_H

#include <GuiLibrary.h>
#include "screen.h"

/**
 * @brief The data to load the keypad with.
 *
 * This is the parameter structure the keypad expects.
 *
 * TODO: All loading data should be shifted to a different header file.
 */
class SettingsLoadData
{
public:
	/** The screen to return to when the data has been entered. */
	Screen* calling_screen;
	/** The initial string value to load into the Settings label. */
	char* init_str_val_lbl_txt;

	/**
	 * @brief Construct a new Settings Load Data object.
	 *
	 * @param screen The screen to return to.
	 * @param txt The initial string value to load.
	 */
	SettingsLoadData(Screen* screen, char* txt) :
		calling_screen(screen),
		init_str_val_lbl_txt(txt)
	{}
};

/**
 * @brief Handles user input from a visible Settings.
 *
 * TODO: Make this a "widget" that draws over the current screen rather than
 * making it its own screen.
 *
 */
class SettingsScreen : public Screen
{
public:
	/**
	 * @brief Construct a new Settings Screen object.
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
	SettingsScreen(int16_t x, int16_t y, int16_t width, int16_t height);

	/**
	 * @brief A pointer to the SettingsLoadData object to load.
	 *
	 * @param params A pointer to the SettingsLoadData object.
	 */
	void load(const void* params);

	/**
	 * @brief Returns the string value that is contained within the Settings
	 * label when the save button is clicked.
	 *
	 * @return const void* A pointer to the string that is contained in the
	 * Settings label.
	 */
	const void* unload();

	/**
	 * @brief Does nothing.
	 *
	 */
	void update();

	/** The GuiLibrary label that holds the user input data. */
	GuiLabel* str_val_weight;
	GuiLabel* str_val_volume;
	GuiLabel* str_val_tolerance;
	GuiLabel* str_val_vibration;
	GuiLabel* str_val_feedback;

	/** Weight Button */
	GuiButton* buttonWeight;
	/** Volume Button */
	GuiButton* buttonVolume;
	/** Tolerance Button */
	GuiButton* buttonTolerance;
	/** Vibration Button */
	GuiButton* buttonVibration;
	/** Auditory Feedback Button */
	GuiButton* buttonAuditory;
	/** Haptic Feedback Button */
	GuiButton* buttonHaptic;
	/** Save & Exit Button */
	GuiButton* buttonSE;

	/** The previous screen that swapped to this one. */
	Screen* calling_screen;
};

#endif
