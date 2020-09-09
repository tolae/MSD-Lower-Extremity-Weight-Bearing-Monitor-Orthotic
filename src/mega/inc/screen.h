#ifndef SCREEN_H
#define SCREEN_H

class Screen
{
    public:
        Screen();

        virtual void load(void *) = 0;
        virtual void * unload() = 0;
        virtual void update() = 0;
};

#endif
