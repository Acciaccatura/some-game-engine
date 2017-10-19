#include <stdlib.h>
#include <math.h>
#include <iostream>
#include "Hitbox.h"

#ifndef PI
#define PI 3.14159265
#endif



Hitbox::Hitbox(double x, double y)
{
    this->rads = 0;
    this->center = {x, y};
    this->active = true;
}

Hitbox::~Hitbox()
{
    free(this->vertices);
}

Point* Hitbox::get_center() {
    return &(this->center);
}

Point* Hitbox::get_vertices() {
    return this->vertices;
}

int Hitbox::get_edges() {
    return this->edges;
}

bool Hitbox::collision(Hitbox* h) {
    if (!this->collides(h)) {
        return false;
    } else return h->collides(this);
}
