#include <stdlib.h>
#include <math.h>
#include <iostream>
#include "Hitbox.h"

Hitbox::Hitbox(double x, double y)
{
    this->rads = 0;
    this->center = {x, y};
}

Hitbox::~Hitbox()
{
    free(this->vertices);
}

void Hitbox::translate(double x, double y) {
    this->center.x += x;
    this->center.y += y;
    int index;
    for (index = 0; index < this->edges; index++) {
        Point* p = &(this->vertices[index]);
        p->x += x;
        p->y += y;
    }
}

void Hitbox::rotate_rad(double rad) {
    int index;
    for (index = 0; index < this->edges; index++) {
        Point* p = &(this->vertices[index]);
        p->x -= this->center.x;
        p->y -= this->center.y;
        double old_x = p->x;
        //rotation matrix
        p->x = cos(rad)*(p->x) - sin(rad)*(p->y);
        p->y = sin(rad)*(old_x) + cos(rad)*(p->y);

        p->x += this->center.x;
        p->y += this->center.y;
        this->rads += rad;
    }
}

/**
 * get the minimum and maximum dot products relative to a vector
 * returns vec * vec because i feel like it
 */

double Hitbox::get_minmax(Point vec, double* start_dot, double* end_dot) {
    int index;
    double dot = vec.x * vec.x + vec.y * vec.y;
    for (index = 0; index < this->edges; index++) {
        double calc = (this->vertices[index].x * vec.x) + (this->vertices[index].y * vec.y);
        if (calc > *end_dot) *end_dot = calc;
        if (calc < *start_dot) *start_dot = calc;
    }
    return dot;
}

/**
 * Check for a collision between box and this
 * using SAT
 */
bool Hitbox::collision(Hitbox box) {
    //get number of things to test for this
    int my_edges, index;
    my_edges = this->edges;
    if (!(this->edges & 1)) {
        //since we're dealing with regular polygons,
        //if we have an even amount of edges,
        //we only need to check half of them.
        my_edges >>= 1;
    }
    for (index = 1; index < my_edges; index++) {
        Point base = {this->vertices[index].x - this->vertices[index-1].x, this->vertices[index].y - this->vertices[index - 1].y};
        double start_dot, end_dot;
        double base_dot = box.get_minmax(base, &start_dot, &end_dot);
        //if even one of these perspectives do not have an overlap, there is no collision
        if ((start_dot > base_dot && end_dot > base_dot) || (start_dot < 0 && end_dot < 0)) {
            return false;
        }
    }
    return true;
}

/**
 * Initialize a rectanglular hitbox.
 * Returns a pointer to said hitbox.
 * Maybe make it so that it just returns the hitbox and
 * you don't have to pass it a pointer to some memory.
 *
 */
Hitbox* Hitbox::rectangle(Hitbox* box, double x_length, double y_length) {
    x_length /= 2;
    y_length /= 2;
    box->edges = 4;
    box->vertices = (Point*) malloc(sizeof(Point)*4);
    box->vertices[0] = {box->center.x - x_length, box->center.y - y_length};
    box->vertices[1] = {box->center.x + x_length, box->center.y - y_length};
    box->vertices[2] = {box->center.x + x_length, box->center.y + y_length};
    box->vertices[3] = {box->center.x - x_length, box->center.y + y_length};
    return box;
}
