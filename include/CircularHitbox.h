/*

#ifndef CIRCULARHITBOX_H
#define CIRCULARHITBOX_H

#include <Hitbox.h>


class CircularHitbox : public Hitbox
{
    public:
        CircularHitbox(double, double, double);
        virtual ~CircularHitbox();

        virtual bool minmax(Point*, double*, double*);

        virtual void rotate_rad(double) = 0;
        virtual void translate(double, double) = 0;
        virtual void draw(sf::RenderWindow*, sf::Color) = 0;

    protected:

        virtual bool collides(Hitbox*);

    private:
};

#endif // CIRCULARHITBOX_H

*/
