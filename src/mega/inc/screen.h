#ifndef SCREEN_H
#define SCREEN_H

class Screen
{
    public:
        virtual Screen() = 0;

        virtual void load(void *) = 0;
        virtual void * unload() = 0;
        virtual void update() = 0;
};

#endif
