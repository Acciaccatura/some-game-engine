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

Point* Hitbox::get_center() {
    return &(this->center);
}

Point* Hitbox::get_vertices() {
    return this->vertices;
}

int Hitbox::get_edges() {
    return this->edges;
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
 * get the minimum and maximum points of a hitbox
 * keep in mind hitboxes must be convex so once we
 * find a minimum and maximum value we can stop!
 *
 * Until I figure out how to implement that without
 * sacrificing performance you just get a loop. lmao
 */
bool Hitbox::minmax(Point vec, double* min, double* max) {
     int index;
     double min_temp = INFINITY;
     double max_temp = -INFINITY;
     for (index = 0; index < this->edges; index++) {
         double calc = ((this->vertices[index].x) * vec.x) + ((this->vertices[index].y) * vec.y);
         if (calc > max_temp) max_temp = calc;
         if (calc < min_temp) min_temp = calc;
     }
     *min = min_temp;
     *max = max_temp;
     return min_temp <= max_temp;
}

/**
 * get overlap between two hitboxes
 * returns vec * vec because i feel like it
 */

double Hitbox::overlap(Point vec, Hitbox other) {
    //TODO: this
    double start_x, end_x, start_y, end_y;
    this->minmax(vec, &start_x, &end_x);
    other.minmax(vec, &start_y, &end_y);
    bool is_overlapping = (start_x <= start_y && end_x >= start_y) || (start_x >= start_y && end_x <= end_y) || (start_x <= start_y && end_x >= end_y) || (start_x <= end_y && end_x >= end_y);
    return is_overlapping;
}

/**
 * Check for a collision between box and this
 * using SAT
 */
bool Hitbox::collision(Hitbox box) {
    //get number of things to test for this
    int my_edges, their_edges, index;
    my_edges = this->edges;
    if (!(this->edges & 1)) {
        //since we're dealing with regular polygons,
        //if we have an even amount of edges,
        //we only need to check half of them.
        my_edges >>= 1;
    }
    for (index = 1; index < my_edges; index++) {
        Point base = {this->vertices[index].x - this->vertices[index - 1].x, this->vertices[index].y - this->vertices[index - 1].y};
        if (!box.overlap(base, *this)) {
            return false;
        }
    }
    Point base = {this->vertices[this->edges - 1].x - this->vertices[0].x, this->vertices[this->edges - 1].y - this->vertices[0].y};
    if (!box.overlap(base, *this)) {
        return false;
    }
    their_edges = box.edges;
    if (!(this->edges & 1)) {
        their_edges >>= 1;
    }
    for (index = 1; index < their_edges; index++) {
        Point base = {box.vertices[index].x - box.vertices[index - 1].x, box.vertices[index].y - box.vertices[index - 1].y};
        if (!this->overlap(base, box)) {
            return false;
        }
    }
    base = {box.vertices[box.edges - 1].x - box.vertices[0].x, box.vertices[box.edges - 1].y - box.vertices[0].y};
    if (!this->overlap(base, box)) {
        return false;
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
