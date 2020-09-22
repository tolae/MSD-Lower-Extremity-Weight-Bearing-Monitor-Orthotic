#include <Arduino.h>
#include "inc/mega.h"
#include "inc/home_screen.h"

extern HomeScreen* home_screen;
const char* input1;
char str_val_lbl_text1[4] = "\0\0\0";
int str_val_lbl_text1_ctr = 0;

uint8_t btn_callback_function_home(void* a, GuiElement* element, uint8_t event);

HomeScreen::HomeScreen(int16_t _x, int16_t _y, int16_t _width, int16_t _height)
{
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
    str_val_Percentage = new GuiLabel(240, 140, 60, 60, "50%");
    str_val_Percentage->textAlignH = TEXT_H_ALIGN_CENTRE;
    str_val_Percentage->fontSize(12);
    str_val_Weight = new GuiLabel(120, 260, 60, 60, "Weight");
    str_val_Weight->textAlignH = TEXT_H_ALIGN_CENTRE;
    str_val_Weight->fontSize(4);
    str_val_Tolerance = new GuiLabel(300, 260, 60, 60, "Toler");
    str_val_Tolerance->textAlignH = TEXT_H_ALIGN_CENTRE;
    str_val_Tolerance->fontSize(4);
    buttonSettings = new GuiButton(20, 20, 120, 60, "Settings"); //(x,y,width,height,text)

	buttonSettings->connectCallback(btn_callback_function_home, this);
	
    GuiElement::addChild((GuiElement *)str_val_TS);
    GuiElement::addChild((GuiElement *)str_val_FS);
    GuiElement::addChild((GuiElement *)str_val_Percentage);
    GuiElement::addChild((GuiElement *)str_val_Weight);
    GuiElement::addChild((GuiElement *)str_val_Tolerance);
    GuiElement::addChild((GuiElement *)buttonSettings);

}

void HomeScreen::load(const void* params)
{
    
	if (params != NULL)
    {
        HomeLoadData* data = (HomeLoadData*)params;
        strcpy(str_val_lbl_text1, (const char*)(data->weight));
        str_val_Weight->text(str_val_lbl_text1);
    }
    else
    {
      strcpy(str_val_lbl_text1, "0");
      str_val_Weight->text(str_val_lbl_text1);
    }
}

void* HomeScreen::unload()
{
    return (void*)str_val_Weight->text();
}

void HomeScreen::update()
{
    return; // Nothing to do
}

// This will be called when the button is pressed or released
uint8_t btn_callback_function_home(void* a, GuiElement* element, uint8_t event) {
    if (event == GUI_EVENT_PRESS)
    {

    }
    else if (event == GUI_EVENT_RELEASE)
    {
		if (input1 == "Settings")
	    {
	    	Serial.print("Yo");
	      screen_manager->switch_screen(SCREENS[0]);
	    }

    }
    return 0;
}
