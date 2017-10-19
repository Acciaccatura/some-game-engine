#include <SFML/Graphics.hpp>

#ifndef HITBOX_H
#define HITBOX_H

typedef struct {
    double x, y;
} Point;

class Hitbox
{
    public:
        virtual ~Hitbox();

        bool active;
        //getters
        Point* get_center();
        Point* get_vertices();
        int get_edges();

        bool collision(Hitbox*);

        virtual void rotate_rad(double) = 0;
        virtual void translate(double, double) = 0;
        virtual void draw(sf::RenderWindow*, sf::Color) = 0;

        virtual bool minmax(Point*, double*, double*) = 0;
    protected:
        Point center;
        Point* vertices;
        int edges;
        double rads;

        Hitbox(double x, double y);

        virtual bool collides(Hitbox*) = 0;
    private:
};

#endif // HITBOX_H
