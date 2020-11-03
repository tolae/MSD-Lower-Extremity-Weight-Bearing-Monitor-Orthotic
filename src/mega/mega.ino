/***************************************************
	Example showing a list of elements, some enabled, some disabled some touch enabled

	NOTE: screeen rotation is set to 270 degrees. Don't worry, the touchscreen will map
	correctly.

	Uses Adafruit TFT library for the example:
	Written by Limor Fried/Ladyada for Adafruit Industries.
	MIT license, all text above must be included in any redistribution
 ****************************************************/

/** NOT FOR USE WITH THE TOUCH SHIELD, ONLY FOR THE BREAKOUT! **/


// These are the four touchscreen analog pins
#define YP A0  // must be an analog pin, use "An" notation!
#define XM A1  // must be an analog pin, use "An" notation!
#define YM 6   // can be a digital pin
#define XP 5   // can be a digital pin

// This is calibration data for the raw touch data to the screen coordinates
#define TS_MINX 150
#define TS_MINY 100
#define TS_MAXX 900
#define TS_MAXY 900


// The display uses hardware SPI, plus #9 & #10
#define TFT_CS 40
#define TFT_DC 41
#define TFT_RST 39 // RST can be set to -1 if you tie it to Arduino's reset

#define GUICONFIG_H_

#include <Adafruit_GFX.h>    // Core graphics library
#include <SPI.h>
#include <Adafruit_HX8357.h>
#include <TouchScreen.h>
#include "inc/mega.h"
#include "inc/screen_manager.h"
#include "inc/keypad_screen.h"
#include "inc/home_screen.h"
#include "inc/settings_screen.h"
#include "inc/timer.h"

// Use hardware SPI (on Uno, #13, #12, #11) and the above for CS/DC
Adafruit_HX8357 tft = Adafruit_HX8357(TFT_CS, TFT_DC, TFT_RST);

// For better pressure precision, we need to know the resistance
// between X+ and X- Use any multimeter to read it
// For the one we're using, its 300 ohms across the X plate
TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300);

// Setup the gui model
// needs reference to the tft and the touchscreen
Gui gui(&tft, &ts, 0, 0, tft.height(), tft.width());

const Screen* SCREENS[] = 
{
  new KeypadScreen(0, 0, TS_MAXX - TS_MINX, TS_MAXY - TS_MINY),
  new HomeScreen(0, 0, TS_MAXX - TS_MINX, TS_MAXY - TS_MINY),
  new SettingsScreen(0, 0, TS_MAXX - TS_MINX, TS_MAXY - TS_MINY)
};

Volume speaker_vol;

ScreenManager* screen_manager = new ScreenManager();

void setup(void) {
	speaker_vol.setMasterVolume(1);
	Serial.begin(115200);
	while(!Serial);
	Serial.println("Gui Widgets test!");
	
	tft.begin();
	// in multiples of 90 only
	gui.setRotation(270);

	for (int i = 0; i < sizeof(SCREENS) / sizeof(char*); i++)
	{
		Screen* screen = SCREENS[i];
		screen->visible(false);
		gui.addChild(screen);
	}
	screen_manager->init_screen(SCREENS[1]);
	
	gui.draw();

	return;
}

void loop()
{
	// this has to be called to keep the system up to date
	gui.update();
	screen_manager->update();

	return;
}
