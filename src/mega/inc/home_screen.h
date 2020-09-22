#ifndef HOME_SCREEN_H
#define HOME_SCREEN_H

#include <GuiLibrary.h>
#include "screen.h"

class HomeLoadData
{
public:
    uint32_t weight;
    uint32_t tolerance;

    HomeLoadData(uint32_t w, uint32_t t) :
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
    HomeScreen(int16_t x, int16_t y, int16_t width, int16_t height);

        /**
         * @brief WIP.
         * 
         * TODO: Make a HomeLoadData that contains:
         * - The inserted weight
         * - The inserted threshold
         * 
         * @param params 
         */
        void load(const void *params);

        /**
         * @brief WIP.
         * 
         * TODO: Make a HomeUnloadData that contains:
         * - The current weight
         * - The current threshold
         * 
         * @return const void* A HomeUnloadData object.
         */
        const void *unload();

        /**
         * @brief Handles the logic and communcation to the foot orthotic.
         * 
         */
        void update();

        /** The label for the touchscreen's battery life. */
        GuiLabel* str_val_TS;

        /** The label for the foot orthotic's battery life. */
        GuiLabel* str_val_FS;

class HomeScreen : public Screen
{
public:
    HomeScreen(int16_t x, int16_t y, int16_t width, int16_t height);

    void load(const void*);
    void* unload();
    void update();

    GuiLabel* str_val_TS;
    GuiLabel* str_val_FS;
    GuiLabel* str_val_Percentage;
    GuiLabel* str_val_Weight;
    GuiLabel* str_val_Tolerance;
    GuiButton* buttonSettings;

};

#endif