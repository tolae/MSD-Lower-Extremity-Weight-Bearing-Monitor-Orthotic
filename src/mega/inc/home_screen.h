#ifndef HOME_SCREEN_H
#define HOME_SCREEN_H

#include <GuiLibrary.h>
#include "screen.h"

#define SETTINGS_BTN_VAL 1

/**
 * @brief The data to load the home screen with.
 * 
 */
class HomeLoadData : public BaseLoadData
{
    public:
        /**
         * @brief The weight input of the user.
         * 
         */
        const char* weight;

        /**
         * @brief The percentage of the user's weight that the user cannot exceed.
         * 
         */
        const char* tolerance;

        /**
         * @brief Construct a new Home Load Data object
         * 
         * @param w The weight input
         * @param t The tolerance input
         */
        HomeLoadData(const char* w, const char* t) :
            weight(w),
            tolerance(t)
        {}
};

/**
 * @brief The primary screen the user will see.
 * 
 * This screen holds the most valuable information for the user. It will
 * display: the current weight percentage, the set weight, the set threshold,
 * and the battery life for this device and the connected foot orthotic.
 * 
 */
class HomeScreen : public Screen
{
public:
    /**
     * @brief Construct a new Home Screen object
     * 
     * @param x
     * @param y
     * @param width
     * @param height
     */
    HomeScreen(int16_t _x, int16_t _y, int16_t _width, int16_t _height);

        /**
         * @brief WIP.
         * 
         * TODO: Make a HomeLoadData that contains:
         * - The inserted weight
         * - The inserted threshold
         * 
         * @param params 
         */
        void load(const BaseLoadData* params);

        /**
         * @brief WIP.
         * 
         * TODO: Make a HomeUnloadData that contains:
         * - The current weight
         * - The current threshold
         * 
         * @return const BaseLoadData* A HomeUnloadData object.
         */
        const BaseLoadData* unload();

        /**
         * @brief Handles the logic and communcation to the foot orthotic.
         * 
         */
        void update();



        /** The label for the touchscreen's battery life. */
        GuiLabel* str_val_TS;

        /** The label for the foot orthotic's battery life. */
        GuiLabel* str_val_FS;

        /** The label for the currently applied weight percentage. */
        GuiLabel* str_val_Percentage;

        /** The label for the currently set weight. */
        GuiLabel* str_val_Weight;

        /** The label for the currently set tolerance. */
        GuiLabel* str_val_Tolerance;

        /** Transitions to the SettingsScreen. */
        GuiButton* buttonSettings;
};

void circle_on();
void circle_off();

#endif