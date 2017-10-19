#include "CircularHitbox.h"

CircularHitbox::CircularHitbox(double x, double y, double radius) : Hitbox(x, y)
{
    this->edges = 0;
    this->radius = radius;
}

CircularHitbox::~CircularHitbox()
{

}

bool CircularHitbox::minmax(Point* vec, double* x, double* y) {
    double val = vec->x * this->center.x + vec->y * this->center.y;
    *x = val;
    *y = val;
    return true;
}

void CircularHitbox::translate(double x, double y) {
    this->center.x += x;
    this->center.y += y;
}

/* What are you looking at?? It's a damn circle! */
void CircularHitbox::rotate_rad(double rad) {
    this->rads += rad;
}

bool collides(Hitbox* box) {

    if (box->get_edges()) {

    } else {

    }
}

void CircularHitbox::draw(sf::RenderWindow* window, sf::Color color) {

}
