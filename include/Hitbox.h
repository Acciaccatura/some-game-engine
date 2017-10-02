#ifndef HITBOX_H
#define HITBOX_H

typedef struct {
    double x, y;
} Point;

class Hitbox
{
    public:
        Hitbox(double x, double y);
        virtual ~Hitbox();
        Point center;
        Point* vertices;
        int edges;
        double rads;

        bool collision(Hitbox);
        void rotate_rad(double);
        void translate(double, double);
        double get_minmax(Point, double*, double*);

        static Hitbox* rectangle(Hitbox*, double, double);
    protected:
    private:
};

#endif // HITBOX_H
