#pragma once

#include <iostream>
#include <string>

class Money {

    public:
        Money();
        // Money(const size_t & n, unsigned char t = 0);
        Money(const std::initializer_list< unsigned char> &t);
        Money(const std::string &t);
        Money(const Money& other);
        Money(Money&& other) noexcept;   

        Money add(Money& other);
        // Money substraction(const Money& other);

        bool equal(const Money& other);
        // bool greater(Money& other);
        // bool less(Money& other);


        std::ostream& print(std::ostream& os);

        virtual ~Money() noexcept;

    private:
        size_t _size;
        unsigned char *_array;
        bool _positive;

        void _add(Money& res, Money& other);
        // void _substraction(Money& res, Money& other);

        int ctoi(char c);
        char itoc(int n);

};