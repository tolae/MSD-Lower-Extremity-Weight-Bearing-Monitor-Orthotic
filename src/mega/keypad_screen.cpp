#include <Arduino.h>
#include "inc/mega.h"
#include "inc/keypad_screen.h"

const char *input;
char str_val_lbl_text[4] = "000";
int str_val_lbl_text_ctr = 0;

uint8_t btn_callback_function(void *a, GuiElement *element, uint8_t event);

KeypadScreen::KeypadScreen()
{
    str_val_lbl = new GuiLabel(60, 0, 360, 60, str_val_lbl_text);
    str_val_lbl->textAlignH = TEXT_H_ALIGN_RIGHT;
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
    button7->connectCallback(btn_callback_function);
    button8->connectCallback(btn_callback_function);
    button9->connectCallback(btn_callback_function);
    button4->connectCallback(btn_callback_function);
    button5->connectCallback(btn_callback_function);
    button6->connectCallback(btn_callback_function);
    button1->connectCallback(btn_callback_function);
    button2->connectCallback(btn_callback_function);
    button3->connectCallback(btn_callback_function);
    button_save->connectCallback(btn_callback_function);
    button0->connectCallback(btn_callback_function);
    button_bksp->connectCallback(btn_callback_function);
}

void KeypadScreen::load(void * params)
{
    strcpy(str_val_lbl_text, (const char *)params);
    str_val_lbl->text(str_val_lbl_text);
    // finally add the widgt to the page
    gui.addChild(str_val_lbl);
    gui.addChild(button7);
    gui.addChild(button8);
    gui.addChild(button9);
    gui.addChild(button4);
    gui.addChild(button5);
    gui.addChild(button6);
    gui.addChild(button1);
    gui.addChild(button2);
    gui.addChild(button3);
    gui.addChild(button_save);
    gui.addChild(button0);
    gui.addChild(button_bksp);

    gui.draw();
}

void * KeypadScreen::unload()
{
    return (void *)str_val_lbl->text();
}

void KeypadScreen::update()
{
    return; // Nothing to do
}

// This will be called when the button is pressed or released
uint8_t btn_callback_function(void *a, GuiElement *element, uint8_t event) {
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
        }
        else
        {
          str_val_lbl_text[--str_val_lbl_text_ctr] = '\0';
        }
      }
      else
      {
        if (str_val_lbl_text_ctr < 3)
        {
          str_val_lbl_text[str_val_lbl_text_ctr++] = input[0];
        }
      }
      Serial.println(str_val_lbl_text);
      // str_val_lbl->draw();
    }
  }
  return 0;
}
