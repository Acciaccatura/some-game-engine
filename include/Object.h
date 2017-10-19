#include "Hitbox.h"

#ifndef OBJECT_H
#define OBJECT_H

class Object
{
    public:
        Object();
        virtual ~Object();

    protected:
        int hitbox_alloc;
        int hitboxes;
        Hitbox* boxes;

    private:

};

#endif // OBJECT_H
