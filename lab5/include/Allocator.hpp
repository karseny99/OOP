
#include <iostream>
#include <memory>
#include <list>
#include <map>
#include <utility>
#include <list>

template <class T, size_t BLOCK_COUNT>
class Allocator
{
    private:
        T* _used_blocks;
        std::list<T*> _free_blocks;
        // uint64_t _free_count;

    public:
        // static constexpr size_t max_count = BLOCK_COUNT;
        using value_type = T;
        using pointer = T *;
        using const_pointer = const T *;
        using size_type = std::size_t;

        Allocator()
        {
            // static_assert(BLOCK_COUNT > 0);
            // _used_blocks = (char *)malloc(sizeof(T) * max_count);
            // _free_blocks = (void **)malloc(sizeof(void *) * max_count);

            // _free_blocks.resize(max_count);

            
            // auto it_fb = std::begin(_free_blocks);

            _used_blocks = new T[BLOCK_COUNT];

            for (size_t i{0}; i < BLOCK_COUNT; ++i) { 
                _free_blocks.push_back(&_used_blocks[i]);
            }
            // _free_count = max_count;
        }

        ~Allocator()
        {
            // delete _free_blocks;
            // delete _used_blocks;

            // _used_blocks.clear();
            // _free_blocks.clear();

            delete[] _used_blocks;
#ifdef DEBUG
            std::cout << "Memory freed" << std::endl;
#endif
        }

        // мы не используем параметр n - поэтому с std::vector данный аллокатор работать не будет
        T *allocate(const size_t& n)
        {

            if(_used_blocks == nullptr) {
                static_assert(BLOCK_COUNT > 0);
                
                _used_blocks = new T[BLOCK_COUNT];

                for (size_t i{0}; i < BLOCK_COUNT; ++i) { 
                    _free_blocks.push_back(&_used_blocks[i]);
                }
            }

            if (_free_blocks.size() > 0)
            {
                T* result = _free_blocks.front();

#ifdef DEBUG
                std::cout << "N is: " << n << " _free_blocks.size is: " << _free_blocks.size() << std::endl;
#endif

                for(size_t i{0}; i < n; ++i) {
                    _free_blocks.pop_front();
                }
                
                return result;
            }
            else
            {
                throw std::bad_alloc();
            }
        }                

        void deallocate(T *pointer, size_t)
        {
            // auto it = std::next(std::begin(_free_blocks), _free_count);
            // *it = pointer;
            // ++_free_count;
            // _free_blocks[_free_count++] = pointer;
        }


        template <typename U, typename... Args>
        void construct(U* result, Args&& ... args)
        {
            new (result) U(std::forward<Args>(args)...);
        }
        template <class U>
        struct rebind
        {
            using other = Allocator<U, BLOCK_COUNT>;
        };

        void destroy(pointer p)
        {
            // p->~T();
        }
};