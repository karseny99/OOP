#include <iostream>
#include <memory>
#include <concepts>   
#include <assert.h>
#include <utility>


template <class ItemType, class ArrayType>
class ArrayIterator
{
private:
    ArrayType *array;
    size_t index;
    size_t size;

public:
    ArrayIterator(ArrayType *value, size_t i, size_t s) : array(value), index(i), size(s){};

    ItemType operator*()
    {
        if (index >= size)
            throw OutOfBoundException();
        return (*array)[index];
    }

    ItemType operator->()
    {
        if (index >= size)
            throw OutOfBoundException();
        return (*array)[index];
    }

    bool operator!=(ArrayIterator<ItemType, ArrayType> const &other) const
    {
        return (other.index != index) || (other.array != array);
    }

    ArrayIterator<ItemType, ArrayType> &operator++()
    {
        ++index;
        return *this;
    }
};
