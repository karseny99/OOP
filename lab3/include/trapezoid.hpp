#include "figure.hpp"
#include "point.hpp"

class Trapezoid : public Figure {
    
    public:
        Trapezoid() = default;
        Trapezoid(Point a, Point b, Point c, Point d);
        Trapezoid(const Trapezoid& other);

        ~Trapezoid() = default;

        virtual Point center() const final;
        virtual double square() const final;
        bool equal(const Trapezoid& other) const;

    private:
        Point * _array;

        bool trapezoid_check();
};
