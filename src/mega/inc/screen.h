#ifndef SCREEN_H
#define SCREEN_H

class Screen
{
    public:

        virtual void load(const void *) = 0;
        virtual void * unload() = 0;
        virtual void update() = 0;
};

#endif
