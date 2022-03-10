/**
 * @file malloc_alloc_template.h
 * @author yuanyongan (3092699411@qq.com)
 * @brief SGI STL的第一级配置器，主要用来处理大小大于128byte的空间分配
 * @date 2022-02-23
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include <new> //空间
#include <iostream>
#define __THROW_BAD_ALLOC   throw bad_alloc
#define __THROW_BAD_ALLOC   cerr << "out of memory" << endl; exit(1);

namespace SIMPLE_STL{
    
    // 配置器一般无template型参数
    class malloc_alloc_template
    {
    private:
        /* data */
        // oom: out of memory
        // 以下都是函数指针， 所代表的函数将用来处理内存不足的情况
        // 任何类型都可以传给void*，且不需要类型转换
        static void* oom_malloc(size_t);
        static void* oom_realloc(void *, size_t);
        static void (* malloc_alloc_oom_handler)(); 

    public:
        static void* allocate(size_t n){
            // void * result
        }
        malloc_alloc_template(/* args */);
        ~malloc_alloc_template();
        
    };
    
    malloc_alloc_template::malloc_alloc_template(/* args */)
    {
    }
    
    malloc_alloc_template::~malloc_alloc_template()
    {
    }
    
} // end of namespace SIMPLE_STL