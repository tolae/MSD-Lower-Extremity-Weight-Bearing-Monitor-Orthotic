#include <Arduino.h>
#include "inc/keypad_screen.h"

uint8_t callback_function(void *a, GuiElement *element, uint8_t event);

KeypadScreen::KeypadScreen()
{
    string_val = new GuiLabel(60, 0, 360, 60, "000");
    string_val->textAlignH = TEXT_H_ALIGN_RIGHT;
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
    button7->connectCallback(callback_function);
    button8->connectCallback(callback_function);
    button9->connectCallback(callback_function);
    button4->connectCallback(callback_function);
    button5->connectCallback(callback_function);
    button6->connectCallback(callback_function);
    button1->connectCallback(callback_function);
    button2->connectCallback(callback_function);
    button3->connectCallback(callback_function);
    button_save->connectCallback(callback_function);
    button0->connectCallback(callback_function);
    button_bksp->connectCallback(callback_function);
}

void KeypadScreen::load(void * params)
{
    // finally add the widgt to the page
    gui.addChild(string_val);
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
    return (void *)output;
}

void KeypadScreen::update()
{
    return; // Nothing to do
}

// This will be called when the button is pressed or released
uint8_t callback_function(void *a, GuiElement *element, uint8_t event) {
  if (event == GUI_EVENT_PRESS)
  {
    
  }
  else if (event == GUI_EVENT_RELEASE)
  {
    if (counter <= 3)
    {
      input = ((GuiButton*)element)->text();
      if (input == "<-") {
        if (counter <= 0)
        {
          counter = 0;
        }
        else
        {
          output[--counter] = '\0';
        }
      }
      else
      {
        if (counter < 3)
        {
          output[counter++] = input[0];
        }
      }
      Serial.println(output);
      ((GuiLabel*)string_val)->text(output);
    }
  }
  return 0;
}
