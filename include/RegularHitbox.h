#ifndef REGULARHITBOX_H
#define REGULARHITBOX_H

#include <Hitbox.h>

class RegularHitbox: public Hitbox
{
    public:
        RegularHitbox(double, double, double, int);
        virtual ~RegularHitbox();

        Point* get_vertices();

        virtual bool minmax(Point*, double*, double*) override;
        virtual double overlap(Point, Hitbox*);

        virtual void rotate_rad(double) override;
        virtual void translate(double, double) override;
        virtual void draw(sf::RenderWindow*, sf::Color) override;

        static RegularHitbox* rectangle(double, double, double, double);
    protected:
        virtual bool collides(Hitbox*);

    private:
        //virtual bool collides(Hitbox*);
};

#endif // REGULARHITBOX_H
