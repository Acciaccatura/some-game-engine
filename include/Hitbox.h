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

        //getters
        Point* get_center();
        Point* get_vertices();
        int get_edges();

        bool minmax(Point, double*, double*);
        double overlap(Point, Hitbox*);
        bool collision(Hitbox*);

        void rotate_rad(double);
        void translate(double, double);
        void draw(sf::RenderWindow*, sf::Color);

        static Hitbox* rectangle(double, double, double, double);
        static Hitbox* triangle(double, double, double);
    protected:
        Point center;
        Point* vertices;
        int edges;
        double rads;

        Hitbox(double x, double y);
    private:
};

#endif // HITBOX_H
