
#include "../include/money.h"
#define MIN_SIZE 2


const int BASE = 10;


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

    int sign_shift = 0;
    if('0' <= *t.begin() and *t.begin() <= itoc(BASE - 1)) {
        _size = t.size() + 1;
        _positive = true;
    } else {
        _size = t.size();
        _positive = (*t.begin() == '-') ? false : true;
        sign_shift = 1;
    }


    _array = new unsigned char[_size];
    _array[0] = itoc(0);

    bool _is_zero = true;

    size_t i{1};
    for(std::initializer_list<unsigned char>::iterator iter = t.begin() + sign_shift; iter != t.end(); ++iter) {
        _array[i++] = *iter;
        if(*iter != '0') {
            _is_zero = false;
        }
    }

    if(_is_zero) _positive = true;
}


Money::Money(const std::string &t) {
    std::cout << "Copy string constructor" << std::endl;
    if('0' <= t[0] and t[0] <= itoc(BASE - 1)) {
        // std::cout << 213321321321321 << ' ';
        _size = t.size() + 1;
        _positive = true;
    } else {
        _size = t.size();
        _positive = (t[0] == '-') ? false : true;
    }

    _array = new unsigned char[_size];
    _array[0] = itoc(0);

    bool _is_zero = true;
    
    for(size_t i{0}; i < _size; ++i) {
        _array[i + 1] = t[i + !_positive];
    }

    for(size_t i{0}; i < _size; ++i) {
        if(_array[i] != '0') {
            _is_zero = false;
            break;
        }
    }

    if(_is_zero) _positive = true;
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

    other._positive = !other._positive;
    Money subs_res = substract(other);
    other._positive = !other._positive;

    return subs_res;
}


void Money::_add(Money& res, const Money& other) {

    res._size = std::max(_size, other._size) + 1;
    res._array = new unsigned char[res._size];
    res._array[0] = itoc(0);
    res._positive = _positive;


    int shift_sum = 0;
    int cur_sum = 0;
    int limit = std::min(_size, other._size);
    for(int i{0}; i < limit; ++i) {
        
        cur_sum = (ctoi(_array[_size - i - 1]) + ctoi(other._array[other._size - i - 1]) + shift_sum) % BASE;
        shift_sum = (ctoi(_array[_size - i - 1]) + ctoi(other._array[other._size - i - 1]) + shift_sum) / BASE;

        res._array[res._size - i - 1] = itoc(cur_sum);        
    }
    
    const Money& main_arr = (_size < other._size) ? other : *this;

    for(int i{limit}; i < main_arr._size; ++i) {
        cur_sum = (ctoi(main_arr._array[main_arr._size - i - 1]) + shift_sum) % BASE;
        shift_sum = (ctoi(main_arr._array[main_arr._size - i - 1]) + shift_sum) / BASE;
        res._array[res._size - i - 1] = itoc(cur_sum);
    }

}


Money Money::substract(const Money& other) {
    /*
        0) *this == other

        1) 5 - 3 ==> +(5 - 3)
        2) 2 - 9 ==> -(9 - 2)
        3) 5 - (-3) ==> 5 + 3
        4) -3 - 5 ==> -(3 + 5)
        
        5.1) -5 - (-3) ==> -(5 - 3)
        5.2) -5 - (-9) ==> 9 - 5
    */
    Money res;

    if(equal(other)) {
        res._array = new unsigned char[MIN_SIZE];
        res._size = MIN_SIZE;
        res._positive = true;
        for(size_t i{0}; i < MIN_SIZE; ++i) {
            res._array[i] = itoc(0);
        }
        return res;
    }

    if(_positive and _greater(other) and other._positive) { 

        _substract(res, *this, other);
        res._positive = true;
    } else if(_positive and !_greater(other) and other._positive) {

        _substract(res, other, *this);
        res._positive = false;
    } else if(_positive and !other._positive) {
        _add(res, other);
        res._positive = true;
    } else if(!_positive and other._positive) {
        _add(res, other);
        res._positive = false;
    } else {
        if(_greater(other)) {
            _substract(res, *this, other);
            res._positive = false;
        } else {
            _substract(res, other, *this);
            res._positive = true;
        }
    }

    return res;
}


void Money::_substract(Money& res, const Money& first, const Money& second) {
    
    res._size = std::max(first._size, second._size);
    res._array = new unsigned char[res._size];

    int cur_shift = 0;
    for(int i{0}; i < std::min(first._size, second._size); ++i) {
        int cur_element = ctoi(first._array[first._size - i - 1]) - ctoi(second._array[second._size - i - 1]) - cur_shift;
        if(cur_element < 0) {
            cur_element += BASE;
            cur_shift = 1;
        } else {
            cur_shift = 0;
        }

        res._array[res._size - i - 1] = itoc(cur_element);
    }

    const Money& main_arr = (first._size < second._size) ? second : first;

    for(int i{std::min(first._size, second._size)}; i < main_arr._size; ++i) {
        int cur_element = ctoi(main_arr._array[main_arr._size - i - 1]) - cur_shift;

        if(cur_element < 0) {
            cur_element += BASE;
            cur_shift = 1;
        } else {
            cur_shift = 0;
        }
        res._array[res._size - i - 1] = itoc(cur_element);
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

    if(_positive and !other._positive) {
        return true;
    } else if(!_positive and other._positive) {
        return false;
    } else if(_positive and other._positive) {
        return _greater(other);
    } else {
        return !_greater(other);
    }

}


bool Money::_greater(const Money& other) {
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
    } else if(_size < other._size) {
        return false;
    } else {
        return true;
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
    if(equal(other)) {
        return false;
    }
    return !greater(other);
}


std::ostream &Money::print(std::ostream& os) {
    if(!_positive) {
        os << '-';
    }
    size_t z_skip = 0;
    while(_array[z_skip++] == '0');
    for(size_t i{z_skip - 1}; i < _size; ++i) os << _array[i];
    if(z_skip == _size + 1) os << '0';
    return os;
}


Money::~Money() noexcept {
    if (_size > 0) {
        _size = 0;
        delete[] _array;
        _array = nullptr;
    }
}