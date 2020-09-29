#include <Arduino.h>
#include "inc/mega.h"
#include "inc/keypad_screen.h"

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
	button8 = new GuiButton(180, 80, 120, 60, "8");
	button9 = new GuiButton(300, 80, 120, 60, "9");
	button4 = new GuiButton(60, 140, 120, 60, "4");
	button5 = new GuiButton(180, 140, 120, 60, "5");
	button6 = new GuiButton(300, 140, 120, 60, "6");
	button1 = new GuiButton(60, 200, 120, 60, "1");
	button2 = new GuiButton(180, 200, 120, 60, "2");
	button3 = new GuiButton(300, 200, 120, 60, "3");
	button_save = new GuiButton(60, 260, 120, 60, "Save");
	button0 = new GuiButton(180, 260, 120, 60, "0");
	button_bksp = new GuiButton(300, 260, 120, 60, "<-");

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
		str_val_lbl->text(str_val_lbl_text);

		calling_screen = data->calling_screen;
	}
	else
	{
		strcpy(str_val_lbl_text, "0");
		str_val_lbl->text(str_val_lbl_text);
		calling_screen = NULL;
	}
}

const BaseLoadData* KeypadScreen::unload()
{
	return (const BaseLoadData*)str_val_lbl->text();
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
			input = ((GuiButton*)element)->text();
			if (input == "<-") {
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
			else if (input == "Save")
			{
				screen_manager->switch_screen(SCREENS[2]);
			}
			else if ((str_val_lbl_text_ctr <=0) & (input == "0"))
			{
				return 0;
			}
			else
			{
				if (str_val_lbl_text_ctr < 3)
				{
					str_val_lbl_text[str_val_lbl_text_ctr++] = input[0];
				}
			}
			Serial.println(str_val_lbl_text);
			keypad_screen->str_val_lbl->draw();
		}
	}
	return 0;
}
