
#include "../include/money.h"


int Money::ctoi(char c) {
    return c - '0';
}

char Money::itoc(int n) {
    return n + '0';
}


Money::Money() : _size(0), _array{nullptr} {
    std::cout << "Default constructor" << std::endl;
}


Money::Money(const std::initializer_list<unsigned char> &t) {
    std::cout << "Initializer list constructor" << std::endl;
    if('0' <= *t.begin() and *t.begin() <= '9') {
        _size = t.size() + 1;
        _positive = true;
    } else {
        _size = t.size();
        _positive = (*t.begin() == '-') ? false : true;
    }

    _array = new unsigned char[_size];
    _array[0] = itoc(0);


    size_t i{1};
    for(auto c : t) {
        if(c == '-' or c == '+') 
            continue;
        _array[i++] = c;
    }
}


Money::Money(const std::string &t) {
    std::cout << "Copy string constructor" << std::endl;
    if('0' <= t[0] and t[0] <= '9') {
        _size = t.size() + 1;
        _positive = true;
    } else {
        _size = t.size();
        _positive = (t[0] == '-') ? false : true;
    }

    _array = new unsigned char[_size];
    _array[0] = itoc(0);
    
    for(size_t i{0}; i < _size; ++i) {
        _array[i + 1] = t[i + !_positive];
    }
}


Money::Money(const Money& other) {
    std::cout << "Copy constructor" << std::endl;
    _size = other._size;
    _array = new unsigned char[_size];
    _positive = other._positive;

    for(size_t i{0}; i < _size; ++i) _array[i] = other._array[i];
}


Money::Money(Money&& other) noexcept {
    std::cout << "Move constructor" << std::endl;
    _size = other._size;
    _array = other._array;
    _positive = other._positive;

    other._size = 0;
    other._array = nullptr;
}

Money Money::add(Money& other) {
    Money res;

    if(_positive == other._positive) {
        _add(res, other);
        return res;
    }

    return res;

}


void Money::_add(Money& res, Money& other) {

    res._size = std::max(_size, other._size) + 1;
    res._array = new unsigned char[res._size];
    res._array[0] = itoc(0);
    res._positive = _positive;


    int shift_sum = 0;
    int cur_sum = 0;
    int limit = std::min(_size, other._size);
    for(int i{0}; i < limit; ++i) {
        
        cur_sum = (ctoi(_array[_size - i - 1]) + ctoi(other._array[other._size - i - 1]) + shift_sum) % 10;
        shift_sum = (ctoi(_array[_size - i - 1]) + ctoi(other._array[other._size - i - 1]) + shift_sum) / 10;

        res._array[res._size - i - 1] = itoc(cur_sum);        
    }
    
    Money& main_arr = (_size < other._size) ? other : *this;

    for(int i{limit}; i < main_arr._size; ++i) {
        cur_sum = (ctoi(main_arr._array[main_arr._size - i - 1]) + shift_sum) % 10;
        shift_sum = (ctoi(main_arr._array[main_arr._size - i - 1]) + shift_sum) / 10;
        res._array[res._size - i - 1] = itoc(cur_sum);
    }

}

bool Money::equal(const Money& other) {
    if(_size != other._size) {
        
        const Money& highest_size = (_size < other._size) ? other : *this;
        const Money& lowest_size = (_size > other._size) ? other : *this;
        if(highest_size._size - lowest_size._size == 1 and highest_size._array[0] == itoc(0)) {
            for(int i{0}; i < lowest_size._size; ++i) {
                if(_array[_size - i - 1] != other._array[other._size - i - 1]) return false;
            }
            return true;
        }

        return false;
    } 

        
    for(size_t i{0}; i < _size; ++i) {
        if(_array[i] != other._array[i]) return false;
    }

    return true;
}


bool Money::greater(const Money& other) {

    if(_positive and other._positive) {
        return _greater(*this, other);
    } else if(!_positive and !other._positive) {
        return !_greater(*this, other);
    } else if(_positive and !other._positive) {
        return true;
    } else {
        return false;
    }

}


bool Money::_greater(const Money& res, const Money& other) {
    size_t _add_idx_other;
    size_t _add_idx;

    if(_size == other._size) {
        _add_idx = 0;
        _add_idx_other = 0;
    } else if((other._size - _size == 1 and other._array[0] == itoc(0))) {
        _add_idx_other = 1;
        _add_idx = 0;
    } else if ((_size - other._size == 1 and _array[0] == itoc(0))) {
        _add_idx_other = 0;
        _add_idx = 1;
    } else {
        return false;
    }
    size_t i = 0;
    while(i < _size) {
        if(_array[i + _add_idx] < other._array[i + _add_idx_other]) {
            return false;
        } else if(_array[i + _add_idx] > other._array[i + _add_idx_other]) {
            return true;
        } 
        ++i;
    }
    return false;
}

bool Money::less(const Money& other) {
    
}


std::ostream &Money::print(std::ostream& os) {
    if(!_positive) {
        os << '-';
    }
    for(size_t i{0}; i < _size; ++i) os << _array[i];
    return os;
}


Money::~Money() noexcept {
    if (_size > 0) {
        _size = 0;
        delete[] _array;
        _array = nullptr;
    }
}