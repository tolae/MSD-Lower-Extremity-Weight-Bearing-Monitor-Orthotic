#include "inc\brightness.h"

struct COLOR
{
	union
	{
		uint16_t rgb;
		struct
		{
			uint8_t blue : 5;
			uint8_t green : 6;
			uint8_t red : 5;
		};
	};
};

void _setBrightnessForElement(GuiElement* element, uint8_t level);
uint16_t _setBrightnessLevel(struct COLOR color, uint8_t level);

void setBrightness(Screen* screen, uint8_t level)
{
	_setBrightnessForElement((GuiElement*)screen, level);
	
	GuiNode* curr = screen->children.head();
	while (curr != NULL)
	{
		_setBrightnessForElement((GuiElement*) curr, level);

		curr = curr->next();
	}
}

void _setBrightnessForElement(GuiElement* element, uint8_t level)
{
	struct COLOR color = { 0 };
	color.rgb = element->backgroundColour;
	element->backgroundColour = _setBrightnessLevel(color, level);

	color.rgb = element->backgroundColour;
	element->foregroundColour = _setBrightnessLevel(color, level);
	
	color.rgb = element->backgroundColour;
	element->borderColour = _setBrightnessLevel(color, level);
}

uint16_t _setBrightnessLevel(struct COLOR color, uint8_t level)
{
	// First extend the RGB565 to RGB888
	uint8_t red = map(color.red, 0, 31, 0, 255);
	uint8_t blue = map(color.blue, 0, 31, 0, 255);
	uint8_t green = map(color.green, 0, 63, 0, 255);
	// Take the percentage of the given level for each value
	red *= (((float)level) / 100.0f);
	green *= (((float)level) / 100.0f);
	blue *= (((float)level) / 100.0f);
	// Map it back to RGB565
	color.red = map(red, 0, 255, 0, 31);
	color.blue = map(green, 0, 255, 0, 31);
	color.green = map(blue, 0, 255, 0, 63);

	return color.rgb;
}
