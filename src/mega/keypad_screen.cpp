#include <Arduino.h>
#include "inc/mega.h"
#include "inc/keypad_screen.h"
#include "inc/settings_screen.h"

const char *input;
char str_val_lbl_text[4] = "\0\0\0";
int str_val_lbl_text_ctr = 0;

uint8_t btn_callback_function(void *a, GuiElement *element, uint8_t event);

KeypadScreen::KeypadScreen(int16_t _x, int16_t _y, int16_t _width, int16_t _height)
{
	x = _x;
	y = _y;
	width = _width;
	height = _height;

	str_val_lbl = new GuiLabel(60, 0, 360, 60, str_val_lbl_text);
	str_val_lbl->textAlignH = TEXT_H_ALIGN_RIGHT;
	str_val_lbl->fontSize(6);
	button7 = new GuiButton(60, 80, 120, 60, "7"); //(x,y,width,height,text)
	button7->value(7);
	button8 = new GuiButton(180, 80, 120, 60, "8");
	button8->value(8);
	button9 = new GuiButton(300, 80, 120, 60, "9");
	button9->value(9);
	button4 = new GuiButton(60, 140, 120, 60, "4");
	button4->value(4);
	button5 = new GuiButton(180, 140, 120, 60, "5");
	button5->value(5);
	button6 = new GuiButton(300, 140, 120, 60, "6");
	button6->value(6);
	button1 = new GuiButton(60, 200, 120, 60, "1");
	button1->value(1);
	button2 = new GuiButton(180, 200, 120, 60, "2");
	button2->value(2);
	button3 = new GuiButton(300, 200, 120, 60, "3");
	button3->value(3);
	button0 = new GuiButton(180, 260, 120, 60, "0");
	button0->value(0);
	button_save = new GuiButton(60, 260, 120, 60, "Save");
	button_save->value(SAVE_BTN);
	button_bksp = new GuiButton(300, 260, 120, 60, "<-");
	button_bksp->value(BKSP_BTN);

	// hook up the callback function defined above to the button so we can track clicks
	button7->connectCallback(btn_callback_function, this);
	button8->connectCallback(btn_callback_function, this);
	button9->connectCallback(btn_callback_function, this);
	button4->connectCallback(btn_callback_function, this);
	button5->connectCallback(btn_callback_function, this);
	button6->connectCallback(btn_callback_function, this);
	button1->connectCallback(btn_callback_function, this);
	button2->connectCallback(btn_callback_function, this);
	button3->connectCallback(btn_callback_function, this);
	button_save->connectCallback(btn_callback_function, this);
	button0->connectCallback(btn_callback_function, this);
	button_bksp->connectCallback(btn_callback_function, this);
	// finally add the widgt to the page
	GuiElement::addChild((GuiElement *)str_val_lbl);
	GuiElement::addChild((GuiElement *)button7);
	GuiElement::addChild((GuiElement *)button8);
	GuiElement::addChild((GuiElement *)button9);
	GuiElement::addChild((GuiElement *)button4);
	GuiElement::addChild((GuiElement *)button5);
	GuiElement::addChild((GuiElement *)button6);
	GuiElement::addChild((GuiElement *)button1);
	GuiElement::addChild((GuiElement *)button2);
	GuiElement::addChild((GuiElement *)button3);
	GuiElement::addChild((GuiElement *)button_save);
	GuiElement::addChild((GuiElement *)button0);
	GuiElement::addChild((GuiElement *)button_bksp);
}

void KeypadScreen::load(const BaseLoadData* params)
{
	if (params != NULL)
	{
		KeypadLoadData* data = (KeypadLoadData*)params;
		strcpy(str_val_lbl_text, (const char*)(data->init_str_val_lbl_txt));
		str_val_lbl_text[3] = '\0';
		str_val_lbl_text_ctr = strlen(str_val_lbl_text);
		str_val_lbl->text(str_val_lbl_text);

		calling_screen = data->calling_screen;
	}
	else
	{
		strcpy(str_val_lbl_text, "0");
		str_val_lbl->text(str_val_lbl_text);
		str_val_lbl_text_ctr = 0;
		calling_screen = NULL;
	}
}

const BaseLoadData* KeypadScreen::unload()
{
	return new SettingsLoadData(str_val_lbl->text());
}

void KeypadScreen::update()
{
	return; // Nothing to do
}

// This will be called when the button is pressed or released
uint8_t btn_callback_function(void *a, GuiElement *element, uint8_t event) {
	KeypadScreen* keypad_screen = (KeypadScreen *)a;

	if (event == GUI_EVENT_PRESS)
	{
	
	}
	else if (event == GUI_EVENT_RELEASE)
	{
		if (str_val_lbl_text_ctr <= 3)
		{
			uint16_t btn_val = element->value();
			if (btn_val == BKSP_BTN) {
				if (str_val_lbl_text_ctr <= 0)
				{
					str_val_lbl_text_ctr = 0;
					return 0;
				}
				else
				{
					str_val_lbl_text[--str_val_lbl_text_ctr] = '\0';
					if(str_val_lbl_text_ctr <= 0)
					{
						str_val_lbl_text[str_val_lbl_text_ctr] = '0';
					}
				}
			}
			else if (btn_val == SAVE_BTN)
			{
				screen_manager->switch_screen(SCREENS[ScreenIndex::SETTINGS]);
			}
			else if ((str_val_lbl_text_ctr <= 0) && (btn_val == 0))
			{
				return 0;
			}
			else if (str_val_lbl_text_ctr < 3)
			{
				if (str_val_lbl_text[0] == '0')
				{
					str_val_lbl_text[0] = ((GuiButton*)element)->text()[0];
					str_val_lbl_text_ctr = 1;
				}
				else
				{
					str_val_lbl_text[str_val_lbl_text_ctr++] = ((GuiButton*)element)->text()[0];
				}
			}
			keypad_screen->str_val_lbl->draw();
		}
	}
	return 0;
}
