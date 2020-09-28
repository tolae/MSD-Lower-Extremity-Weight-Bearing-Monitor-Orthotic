#include <Arduino.h>
#include "inc/mega.h"
#include "inc/settings_screen.h"

const char* input2;
int haptic = 0;
int auditory = 0;



uint8_t btn_callback_function_settings(void* a, GuiElement* element, uint8_t event);

SettingsScreen::SettingsScreen(int16_t _x, int16_t _y, int16_t _width, int16_t _height)
{
	x = _x;
	y = _y;
	width = _width;
	height = _height;

	str_val_weight = new GuiLabel(20, 20, 60, 60, "Weight");
	buttonWeight = new GuiButton(140, 20, 100, 60, "LBS");
	str_val_volume = new GuiLabel(250, 20, 60, 60, "Volume");
	buttonVolume = new GuiButton(360, 20, 100, 60, "%");

	str_val_tolerance = new GuiLabel(20, 90, 60, 60, "Tolerance");
	GuiButton* buttonTolerance = new GuiButton(140, 90, 100, 60, "%");
	str_val_vibration = new GuiLabel(250, 90, 60, 60, "Vibration");
	GuiButton* buttonVibration = new GuiButton(360, 90, 100, 60, "%");

	str_val_feedback = new GuiLabel(20, 160, 60, 60, "Feedback");
	GuiButton* buttonAuditory = new GuiButton(140, 160, 140, 60, "Auditory");
	GuiButton* buttonHaptic = new GuiButton(320, 160, 140, 60, "Haptic");

	GuiButton* buttonSE = new GuiButton(320, 230, 140, 60, "Save & Exit");

	

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

void SettingsScreen::load(const void* params)
{
	
}

const void* SettingsScreen::unload()
{

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
		input2 = ((GuiButton*)element)->text();

	}
	else if (event == GUI_EVENT_RELEASE)
	{
		if (input2 == "LBS")
		{
			screen_manager->switch_screen(SCREENS[0]);
		}
		else if (input2 == "%") {
			screen_manager->switch_screen(SCREENS[0]);
		}
		else if (input2 == "Auditory") {
			if(auditory == 0){
				((GuiButton*)element)->setBackground(COLOR_WHITE);
				auditory = 1;
			}
			else{
				((GuiButton*)element)->setBackground(COLOR_DARKGREY);
				auditory = 0;
			}
			
		}
		else if (input2 == "Haptic") {
			if(haptic == 0){
				((GuiButton*)element)->setBackground(COLOR_WHITE);
				haptic = 1;
			}
			else{
				((GuiButton*)element)->setBackground(COLOR_DARKGREY);
				haptic = 0;
			}
		}
		else {
			screen_manager->switch_screen(SCREENS[1]);
		}

	}
	return 0;
}
