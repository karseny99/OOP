#include <iostream>
#include <memory>
#include <chrono>
#include <list>
#include <map>
#include <utility>




template <class T, size_t BLOCK_COUNT>
class Allocator
{
    private:
        char *_used_blocks;
        void **_free_blocks;
        uint64_t _free_count;

    public:
        static constexpr size_t max_count = BLOCK_COUNT;
        using value_type = T;
        using pointer = T *;
        using const_pointer = const T *;
        using size_type = std::size_t;

        Allocator()
        {
            static_assert(BLOCK_COUNT > 0);
            _used_blocks = (char *)malloc(sizeof(T) * max_count);
            _free_blocks = (void **)malloc(sizeof(void *) * max_count);

            for (uint64_t i = 0; i < max_count; i++)
                _free_blocks[i] = _used_blocks + i * sizeof(T);
            _free_count = max_count;
        }

        ~Allocator()
        {
            delete _free_blocks;
            delete _used_blocks;

            _free_blocks = nullptr;
            _used_blocks = nullptr;
        }

        template <class U>
        struct rebind
        {
            using other = Allocator<U, BLOCK_COUNT>;
        };

        // мы не используем параметр n - поэтому с std::vector данный аллокатор работать не будет
        T *allocate(size_t n)
        {
            T *result = nullptr;
            if (_free_count > 0)
            {
                result = (T *)_free_blocks[--_free_count];
            }
            else
            {
                throw std::bad_alloc();
            }
            return result;
        }

        void deallocate(T *pointer, size_t)
        {
            _free_blocks[_free_count++] = pointer;
        }
        template <typename U, typename... Args>
        void construct(U *p, Args &&...args)
        {
            new (p) U(std::forward<Args>(args)...);
        }

        void destroy(pointer p)
        {
            p->~T();
        }
};

template <class T, class U, size_t BLOCK_COUNT>
constexpr bool operator==(const Allocator<T, BLOCK_COUNT> &lhs, const Allocator<U, BLOCK_COUNT> &rhs) 
{
    return true;
}

template <typename T, typename U, size_t BLOCK_COUNT>
constexpr bool operator!=(const Allocator<T, BLOCK_COUNT> &lhs, const Allocator<U, BLOCK_COUNT> &rhs)  
{
    return false;
}

template <int N>
int factorial()
{
    return N * factorial<N - 1>();
}
template <>
int factorial<0>()
{
    return 1;
}

template <int N>
void fill_map(std::map<int, int, std::less<int>, Allocator<std::pair<const int,int>, 10>> &map)
{
    map.insert(std::pair<int, int>(N, factorial<N>()));
    fill_map<N - 1>(map);
}

template <>
void fill_map<0>(std::map<int, int, std::less<int>, Allocator<std::pair<const int,int>, 10>> &map)
{
    map.insert(std::pair<int, int>(0, factorial<0>()));
}
  
int main(int argc, char **argv)
{
    std::map<int, int, std::less<int>, Allocator<std::pair<const int,int>, 10>> my_map;

    std::cout << my_map.size() << std::endl;

    fill_map<9>(my_map);

    for(auto& el : my_map) {
        std::cout << el.first << ' ' << el.second << std::endl;
    }
}