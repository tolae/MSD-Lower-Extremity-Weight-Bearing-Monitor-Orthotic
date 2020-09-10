#ifndef SCREEN_H
#define SCREEN_H

#include <GuiLibrary.h>

class Screen : public GuiElement {
    public:
        void removeChild(GuiElement);
        virtual void load(const void *) = 0;
        virtual void * unload() = 0;
        virtual void update() = 0;
};

#endif
