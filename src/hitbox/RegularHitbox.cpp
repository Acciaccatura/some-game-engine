#include <stdlib.h>
#include <math.h>
#include <iostream>
#include "RegularHitbox.h"

#ifndef PI
#define PI 3.14159265
#endif

RegularHitbox::RegularHitbox(double x, double y) :Hitbox(x, y)
{

}

RegularHitbox::~RegularHitbox()
{
    free(this->vertices);
}

void RegularHitbox::translate(double x, double y) {
    this->center.x += x;
    this->center.y += y;
}

void RegularHitbox::rotate_rad(double rad) {
    int index;
    for (index = 0; index < this->edges; index++) {
        Point* p = &(this->vertices[index]);
        double old_x = p->x;
        //rotation matrix
        p->x = cos(rad)*(p->x) - sin(rad)*(p->y);
        p->y = sin(rad)*(old_x) + cos(rad)*(p->y);
    }
    this->rads += rad;
}

void RegularHitbox::draw(sf::RenderWindow* window, sf::Color color) {
    sf::ConvexShape polygon;
    polygon.setPointCount(this->edges);
    int index;
    Point* vertices = this->vertices;
    polygon.setFillColor(color);
    polygon.setOutlineColor(color);
    for (index = 0; index < this->edges; index++) {
        polygon.setPoint(index, sf::Vector2f(vertices[index].x + this->center.x, vertices[index].y + this->center.y));
    }
    window->draw(polygon);
}

/**
 * get the minimum and maximum points of a hitbox
 * keep in mind hitboxes must be convex so once we
 * find a minimum and maximum value we can stop!
 *
 * Until I figure out how to implement that without
 * sacrificing performance you just get a loop. lmao
 */
bool RegularHitbox::minmax(Point* vec, double* min, double* max) {
     int index;
     double min_temp = INFINITY;
     double max_temp = -INFINITY;
     for (index = 0; index < this->edges; index++) {
         double calc = ((this->vertices[index].x + this->center.x) * vec->x) + ((this->vertices[index].y + this->center.y) * vec->y);
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
double RegularHitbox::overlap(Point vec, Hitbox* other) {
    double start_x, end_x, start_y, end_y;
    this->minmax(&vec, &start_x, &end_x);
    other->minmax(&vec, &start_y, &end_y);
    bool is_overlapping = (start_x <= start_y && end_x >= start_y) || (start_x >= start_y && end_x <= end_y) || (start_x <= start_y && end_x >= end_y) || (start_x <= end_y && end_x >= end_y);
    return is_overlapping;
}

/**
 * Check for a collision between box and this
 * using SAT
 */
bool RegularHitbox::collides(Hitbox* box) {
    //get number of things to test for this
    if (box->active) {
        int their_edges, index;
        their_edges = box->get_edges();
        Point* their_vertices = box->get_vertices();
        if (!(their_edges & 1)) {
            //since we're dealing with regular polygons,
            //if we have an even amount of edges,
            //we only need to check half of them.
            their_edges >>= 1;
        }
        for (index = 1; index < their_edges; index++) {
            Point base = {their_vertices[index].y - their_vertices[index - 1].y, -their_vertices[index].x + their_vertices[index - 1].x};
            if (!this->overlap(base, box)) {
                return false;
            }
        }
        Point base = {their_vertices[box->get_edges() - 1].y - their_vertices[0].y, -their_vertices[box->get_edges() - 1].x + their_vertices[0].x};
        if (!this->overlap(base, box)) {
            return false;
        }
        return true;
    } else return false;
}

/**
 * Initialize a rectanglular hitbox.
 * Returns a pointer to said hitbox.
 * Maybe make it so that it just returns the hitbox and
 * you don't have to pass it a pointer to some memory.
 *
 */
RegularHitbox* RegularHitbox::rectangle(double x, double y, double x_length, double y_length) {
    RegularHitbox* box = new RegularHitbox(x, y);
    x_length /= 2;
    y_length /= 2;
    box->edges = 4;
    box->vertices = (Point*) malloc(sizeof(Point)*4);
    box->vertices[0] = {-x_length, -y_length};
    box->vertices[1] = {x_length, -y_length};
    box->vertices[2] = {x_length, y_length};
    box->vertices[3] = {-x_length, y_length};
    return box;
}

RegularHitbox* RegularHitbox::regular_polygon(double x, double y, int edges, double radius) {
    RegularHitbox* box = new RegularHitbox(x, y);
    box->edges = edges;
    box->vertices = (Point*) malloc(sizeof(Point)*edges);
    double radians = 2*PI/edges;
    int index;
    for (index = 0; index < edges; index++) {
        box->vertices[index] = {cos(radians*index)*radius, sin(radians*index)*radius};
    }
    return box;
}
