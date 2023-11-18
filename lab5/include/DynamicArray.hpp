#include <iostream>
#include <memory>
#include <concepts>   
#include <assert.h>
#include <utility>

/*
    vec.push_back();
    vec.pop_back();
    vec.size();
*/

#define Min_Cap 10
template<typename T> 
concept Number = std::is_same<T, int>::value || std::is_same<T, double>::value || std::is_same<T, float>::value;

template<Number T>
class DynamicArray 
{
    private:
        size_t _size;
        size_t _capacity;
        size_t _head_idx;
        std::shared_ptr<T[]> _array;

        void _increase() {
            auto tmp = std::shared_ptr<T[]>(new T[_capacity * 2]);

            for(size_t i{0}; i < _size; ++i) {
                tmp[i] = _array.get()[(i + _head_idx) % _capacity];
            }
            
            _head_idx = 0;
            _capacity *= 2;
            // delete[] _array;
            _array = tmp;
        }

        void _decrease() {
            auto tmp = std::shared_ptr<T[]>(new T[_capacity / 2]);


            for(size_t i{0}; i < _size; ++i) {
                tmp[i] = _array.get()[(i + _head_idx) % _capacity];
            }

            _head_idx = 0;
            _capacity /= _capacity;
            // delete[] _array;
            _array = tmp;
        }

    public: 
        DynamicArray() : _size(0), _capacity(Min_Cap), _head_idx(0) {
            _array.reset(new T[_capacity]);
        }
        DynamicArray(size_t sz) : _size(sz) {
            _capacity = _size * 2;
            _head_idx = 0;
            _array.reset(new T[_capacity]);

        }

        ~DynamicArray() {
            _size = 0;
            _capacity = 0;
            _head_idx = 0;

#ifdef DEBUG
            std::cout << "Memory freed" << std::endl;
#endif
        }

        T& operator[](const size_t index) {
            assert(index < _size);
            return _array.get()[(index + _head_idx) % _capacity];
        }

        size_t size() const{
            return _size;
        }

        void push_back(T element) {
            if(_size == _capacity - 1) {
                _increase();
            }

            _array[(_size + _head_idx) % _capacity] = element;
            ++_size;
        }

        void set_element(size_t index, const T& value) {
            assert(index < _size);
            _array[(_head_idx + index) % _capacity] = value;
        }

        void erase(size_t index) {
            assert(index < _size);

            if(_size * 4 <= _capacity) {
                _decrease();
            }

            if(index == _head_idx) {
                _head_idx = (_head_idx + 1) % _capacity;
                --_size;
            } else if(index == (_head_idx + _size - 1) % _capacity) {
                --_size;
            } else {

                auto tmp = std::shared_ptr<T[]>(new T[_capacity]);

                size_t k{0};
                for(size_t i{0}; i < _size; ++i, ++k) {
                    if(i == index) {
                        --k;
                        continue;
                    } 

                    tmp[k] = _array.get()[(i + _head_idx) % _capacity];
                }

                --_size;
                _head_idx = 0;
                _array = tmp;
            }

        }

        void pop_back() {
            if(_size * 4 <= _capacity) {
                _decrease();
            }
            --_size;
        }
};