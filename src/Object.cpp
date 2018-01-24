#include <stdlib.h>
#include <stdarg.h>
#include "Object.h"

Object::Object()
{
    this->hitboxes = 0;
    this->hitbox_alloc = 1;
    this->boxes = (Hitbox*) malloc(sizeof(Hitbox*));
}

Object::~Object()
{
    free(this->boxes);
}
