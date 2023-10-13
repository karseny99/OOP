#include "figure.hpp"
#include "point.hpp"

class Rhombus : public Figure {
    
    public:
        Rhombus() = default;
        Rhombus(Point a, Point b, Point c, Point d);
        Rhombus(const Rhombus& other);
        ~Rhombus() = default;

        virtual Point center() const final;
        virtual double square() const final;
        bool equal(const Rhombus& other) const;

    private:
        Point * _array;

        bool rhombus_check();
};
