#pragma once

class Point {

    friend bool operator==(const Point& left_operand, const Point& right_operand);
    friend bool operator<(const Point& left_operand, const Point& right_operand);
    friend Point operator-(const Point& left_operand, const Point& right_operand);
    friend Point operator/(const Point& left_operand, const int& num);
    friend double operator*(const Point& left_operand, const Point& right_operand);
    friend Point operator+(const Point& left_operand, const Point& right_operand);
    friend double vector_length(const Point& vector);

    public:

        Point() = default;
        Point(double x, double y) : x(x), y(y) {};
        ~Point() = default;

        double x, y;
    
};