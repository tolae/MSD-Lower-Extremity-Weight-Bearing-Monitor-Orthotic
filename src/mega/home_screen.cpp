#include <Arduino.h>
#include "inc/mega.h"
#include "inc/home_screen.h"
#include "inc/settings_screen.h"
#include "inc/timer.h"

#define YELLOW_UPDATE_FREQ 2 // 2 Hz (500ms)
#define RED_UPDATE_FREQ 4 // 4 Hz (250ms)

extern HomeScreen* home_screen;

uint8_t btn_callback_function_home(void* a, GuiElement* element, uint8_t event);
void flash_green();
void flash_yellow();

HomeScreen::HomeScreen(int16_t _x, int16_t _y, int16_t _width, int16_t _height)
{
	pinMode(LED_BUILTIN, OUTPUT);

	x = _x;
	y = _y;
	width = _width;
	height = _height;

	str_val_TS = new GuiLabel(240, 10, 60, 60, "TS 100%");
	str_val_TS->textAlignH = TEXT_H_ALIGN_CENTRE;
	str_val_TS->fontSize(3);
	str_val_FS = new GuiLabel(380, 10, 60, 60, "FS 100%");
	str_val_FS->textAlignH = TEXT_H_ALIGN_CENTRE;
	str_val_FS->fontSize(3);
	str_val_Percentage = new GuiLabel(240, 140, 60, 60, "\0");
	str_val_Percentage->textAlignH = TEXT_H_ALIGN_LEFT;
	str_val_Percentage->fontSize(12);
	str_val_Weight = new GuiLabel(120, 260, 60, 60, "Weight");
	str_val_Weight->textAlignH = TEXT_H_ALIGN_CENTRE;
	str_val_Weight->fontSize(4);
	str_val_Tolerance = new GuiLabel(300, 260, 60, 60, "Toler");
	str_val_Tolerance->textAlignH = TEXT_H_ALIGN_CENTRE;
	str_val_Tolerance->fontSize(4);
	buttonSettings = new GuiButton(20, 20, 120, 60, "Settings");
	buttonSettings->value(SETTINGS_BTN_VAL);

	buttonSettings->connectCallback(btn_callback_function_home, this);
	
	GuiElement::addChild((GuiElement *)str_val_TS);
	GuiElement::addChild((GuiElement *)str_val_FS);
	GuiElement::addChild((GuiElement *)str_val_Percentage);
	GuiElement::addChild((GuiElement *)str_val_Weight);
	GuiElement::addChild((GuiElement *)str_val_Tolerance);
	GuiElement::addChild((GuiElement *)buttonSettings);
}

void HomeScreen::load(const BaseLoadData* params)
{
	if (params != (void *)NULL)
	{
		HomeLoadData* data = (HomeLoadData*)params;
		str_val_Weight->text(data->weight);
		str_val_Tolerance->text(data->tolerance);
	}
	else
	{
	  str_val_Weight->text("Weight");
	}
}

const BaseLoadData* HomeScreen::unload()
{
	disable_timer(TimerModule::TIM_3);
	return new SettingsLoadData(str_val_Weight->text());
}

int state = 0;
void HomeScreen::update()
{
	if (Serial.available())
	{
		uint8_t in = Serial.read();
		Serial.println(in);
		char temp[6];
		str_val_Percentage->text(itoa(in, temp, 10));
		if (in > '7')
		{
			configure_timer(TimerModule::TIM_3, flash_yellow, 10, TimerPrescaler::TEN_TWO_FOUR);
		}
		else if (in > '5')
		{
			configure_timer(TimerModule::TIM_3, flash_green, 2, TimerPrescaler::TEN_TWO_FOUR);
		}
		else
		{
			disable_timer(TimerModule::TIM_3);
			tft.drawCircle(60, 160, 40, COLOR_LIGHTGREY);
			tft.fillCircle(60, 160, 40, COLOR_LIGHTGREY);
		}
	}
	return; // Nothing to do
}

// This will be called when the button is pressed or released
uint8_t btn_callback_function_home(void* a, GuiElement* element, uint8_t event) {
	if (event == GUI_EVENT_PRESS)
	{
	}
	else if (event == GUI_EVENT_RELEASE)
	{
		if (element->value() == SETTINGS_BTN_VAL)
		{
			screen_manager->switch_screen(SCREENS[ScreenIndex::SETTINGS]);
		}
	}
	return 0;
}

void flash_green()
{
	static int flash_green_flag = 0;
	if (flash_green_flag == 1)
	{
		flash_green_flag = 0;
		tft.drawCircle(60, 160, 40, COLOR_LIGHTGREY);
		tft.fillCircle(60, 160, 40, COLOR_LIGHTGREY);
	}
	else
	{
		flash_green_flag = 1;
		tft.drawCircle(60, 160, 40, COLOR_GREEN);
		tft.fillCircle(60, 160, 40, COLOR_GREEN);
	}
}

void flash_yellow()
{
	static int flash_yellow_flag = 0;
	if (flash_yellow_flag == 1)
	{
		flash_yellow_flag = 0;
		tft.drawCircle(60, 160, 40, COLOR_LIGHTGREY);
		tft.fillCircle(60, 160, 40, COLOR_LIGHTGREY);
	}
	else
	{
		flash_yellow_flag = 1;
		tft.drawCircle(60, 160, 40, COLOR_YELLOW);
		tft.fillCircle(60, 160, 40, COLOR_YELLOW);
	}
}
