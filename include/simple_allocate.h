/**
 * @file malloc_alloc_template.h
 * @author yuanyongan (3092699411@qq.com)
 * @brief 这个simple_allocate简单的实现了allocator所需要的方法
 * 其实就是对::operator new和::operate delete进行了简单的封装
 * 一个是分配空间，一个是回收空间，
 * 但这种简单的allocator速度非常慢相对于std::allocator而言
 * @date 2022-02-23
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef _SIMPLE_ALLOC_
#define _SIMPLE_ALLOC_

#include <new>      // for placement new 
#include <cstddef>  // for ptrdiff_t, size_t
#include <cstdlib>  // for exit()
#include <climits>  // for UINT_MAX
#include <iostream> // for err
using namespace std;

namespace SIMPLE_STL{
    template <typename T>
    class simple_allocate
    {
    public:
        typedef T           value_type;
        typedef T*          pointer;
        typedef const T*    const_pointer;
        typedef T&          reference;
        typedef const T&    const_reference;
        typedef size_t      size_type;
        typedef ptrdiff_t   difference_type;
        

        // rebind allocator of type U
        template<typename U>
        struct rebind
        {
            typedef simple_allocate<U> other;
        };
        
        //hint used for locality.ref.
        pointer allocate(size_type n, const void* hint = 0){
            set_new_handler(0);
            
            T* tmp = (T*)(::operator new((size_t)((difference_type)n * sizeof(T))));
            if (tmp == 0){
                cerr << "out of memory" <<endl;
                exit(1);
            }
            return tmp;
        }

        void deallocate(pointer p, size_type n){
            ::operator delete(p);
        }

        void construct(pointer p, const pointer& value){
            new(p) pointer(value);  // placement new ,在p地址上使用T1的构造函数进行初始化
        }

        void destroy(pointer p){ 
           p->~T();
        }

        pointer address(reference x){ return (pointer)&x;}

        const_pointer const_address(const_reference x){
            return (const_pointer)&x;
        }

        size_type max_size() const {
            return size_type(UINT_MAX/sizeof(T));
        }        

    };
    
    
} // end of namespace SIMPLE_STL

#endif