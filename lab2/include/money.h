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

        Money add(const Money& other);
        Money substract(const Money& other);

        bool equal(const Money& other);
        bool greater(const Money& other);
        bool less(const Money& other);


        std::ostream& print(std::ostream& os);

        virtual ~Money() noexcept;

    private:
        int _size;
        unsigned char *_array;
        bool _positive;

        bool _greater(const Money& res, const Money& other);
        void _add(Money& res, const Money& other);
        void _substract(Money& res, const Money& other);

        int ctoi(char c);
        char itoc(int n);

};