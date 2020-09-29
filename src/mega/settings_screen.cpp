#include <Arduino.h>
#include "inc/mega.h"
#include "inc/settings_screen.h"
#include "inc/keypad_screen.h"
#include "inc/home_screen.h"

uint8_t btn_callback_function_settings(void* a, GuiElement* element, uint8_t event);

SettingsScreen::SettingsScreen(int16_t _x, int16_t _y, int16_t _width, int16_t _height)
{
	x = _x;
	y = _y;
	width = _width;
	height = _height;

	update_label = Label::NONE;
	haptic = 0;
	auditory = 0;

	str_val_weight = new GuiLabel(20, 20, 60, 60, "Weight");
	strcpy(button_weight_str, "200");
	buttonWeight = new GuiButton(140, 20, 100, 60, button_weight_str);
	buttonWeight->value(Label::WEIGHT);
	str_val_volume = new GuiLabel(250, 20, 60, 60, "Volume");
	strcpy(button_volume_str, "0");
	buttonVolume = new GuiButton(360, 20, 100, 60, button_volume_str);
	buttonVolume->value(Label::VOLUME);

	str_val_tolerance = new GuiLabel(20, 90, 60, 60, "Tolerance");
	strcpy(button_tolerance_str, "50");
	buttonTolerance = new GuiButton(140, 90, 100, 60, button_tolerance_str);
	buttonTolerance->value(Label::TOLERANCE);
	str_val_vibration = new GuiLabel(250, 90, 60, 60, "Vibration");
	strcpy(button_vibration_str, "0");
	buttonVibration = new GuiButton(360, 90, 100, 60, button_vibration_str);
	buttonVibration->value(Label::VIBRATION);

	str_val_feedback = new GuiLabel(20, 160, 60, 60, "Feedback");
	buttonAuditory = new GuiButton(140, 160, 140, 60, "Auditory");
	buttonAuditory->value(Label::AUDITORY);
	buttonHaptic = new GuiButton(320, 160, 140, 60, "Haptic");
	buttonHaptic->value(Label::HAPTIC);

	buttonSE = new GuiButton(320, 230, 140, 60, "Save & Exit");
	buttonSE->value(Label::SAVE_AND_EXIT);

	// hook up the callback function defined above to the button so we can track clicks
	buttonWeight->connectCallback(btn_callback_function_settings, this);
	buttonVolume->connectCallback(btn_callback_function_settings, this);
	buttonTolerance->connectCallback(btn_callback_function_settings, this);
	buttonVibration->connectCallback(btn_callback_function_settings, this);
	buttonAuditory->connectCallback(btn_callback_function_settings, this);
	buttonHaptic->connectCallback(btn_callback_function_settings, this);
	buttonSE->connectCallback(btn_callback_function_settings, this);

	// finally add the widgt to the page
	GuiElement::addChild((GuiElement*)str_val_weight);
	GuiElement::addChild((GuiElement*)str_val_volume);
	GuiElement::addChild((GuiElement*)str_val_tolerance);
	GuiElement::addChild((GuiElement*)str_val_vibration);
	GuiElement::addChild((GuiElement*)str_val_feedback);
	GuiElement::addChild((GuiElement*)buttonWeight);
	GuiElement::addChild((GuiElement*)buttonVolume);
	GuiElement::addChild((GuiElement*)buttonTolerance);
	GuiElement::addChild((GuiElement*)buttonVibration);
	GuiElement::addChild((GuiElement*)buttonAuditory);
	GuiElement::addChild((GuiElement*)buttonHaptic);
	GuiElement::addChild((GuiElement*)buttonSE);
}

void SettingsScreen::load(const BaseLoadData* params)
{
	if (params != (void *)NULL)
	{
		SettingsLoadData* data = (SettingsLoadData*)params;
		if (update_label == Label::WEIGHT)
		{
			strcpy(button_weight_str, data->init_str_val_lbl_txt);
		}
		else if (update_label == Label::TOLERANCE)
		{
			strcpy(button_tolerance_str, data->init_str_val_lbl_txt);
		}
		else if (update_label == Label::VOLUME)
		{
			strcpy(button_volume_str, data->init_str_val_lbl_txt);
		}
		else if (update_label == Label::VIBRATION)
		{
			strcpy(button_vibration_str, data->init_str_val_lbl_txt);
		}
	}
}

const BaseLoadData* SettingsScreen::unload()
{
	KeypadLoadData* keypad_data = (void *)NULL;
	HomeLoadData* home_data = (void *)NULL;
	if (update_label == Label::WEIGHT)
	{
		keypad_data = new KeypadLoadData(this, buttonWeight->text());
	}
	else if (update_label == Label::TOLERANCE)
	{
		keypad_data = new KeypadLoadData(this, buttonTolerance->text());
	}
	else if (update_label == Label::VOLUME)
	{
		keypad_data = new KeypadLoadData(this, buttonVolume->text());
	}
	else if (update_label == Label::VIBRATION)
	{
		keypad_data = new KeypadLoadData(this, buttonVibration->text());
	}
	else if (update_label == Label::SAVE_AND_EXIT)
	{
		home_data = new HomeLoadData(
			buttonWeight->text(),
			buttonTolerance->text()
		);
	}

	if (keypad_data != (void *)NULL)
	{
		return keypad_data;
	}
	else
	{
		return home_data;
	}
	return (void *)NULL;
}

void SettingsScreen::update()
{
	return; // Nothing to do
}

// This will be called when the button is pressed or released
uint8_t btn_callback_function_settings(void* a, GuiElement* element, uint8_t event) {
	SettingsScreen* settings_screen = (SettingsScreen*)a;

	if (event == GUI_EVENT_PRESS)
	{
		settings_screen->update_label = ((GuiButton*)element)->value();
	}
	else if (event == GUI_EVENT_RELEASE)
	{
		if (settings_screen->update_label == SettingsScreen::Label::SAVE_AND_EXIT)
		{
			screen_manager->switch_screen(SCREENS[1]);
		}
		else if (settings_screen->update_label == SettingsScreen::Label::HAPTIC)
		{
			if(settings_screen->haptic == 0){
				((GuiButton*)element)->setBackground(COLOR_WHITE);
				settings_screen->haptic = 1;
			}
			else{
				((GuiButton*)element)->setBackground(COLOR_DARKGREY);
				settings_screen->haptic = 0;
			}
		}
		else if (settings_screen->update_label == SettingsScreen::Label::AUDITORY)
		{
			if(settings_screen->auditory == 0){
				((GuiButton*)element)->setBackground(COLOR_WHITE);
				settings_screen->auditory = 1;
			}
			else{
				((GuiButton*)element)->setBackground(COLOR_DARKGREY);
				settings_screen->auditory = 0;
			}
		}
		else // Update a label
		{
			screen_manager->switch_screen(SCREENS[0]);
		}
	}
	return 0;
}
