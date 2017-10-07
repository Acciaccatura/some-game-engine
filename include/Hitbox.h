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

        //getters
        Point* get_center();
        Point* get_vertices();
        int get_edges();

        bool minmax(Point, double*, double*);
        bool collision(Hitbox);
        void rotate_rad(double);
        void translate(double, double);
        double overlap(Point, Hitbox);

        static Hitbox* rectangle(Hitbox*, double, double);
    protected:
        Point center;
        Point* vertices;
        int edges;
        double rads;
    private:
};

#endif // HITBOX_H
