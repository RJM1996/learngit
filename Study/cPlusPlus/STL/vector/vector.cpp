
#include "vector.h"

void printContainer(const container& s)
{

}

// 四个构造函数
// 1. explicit vector (const allocator_type& alloc = allocator_type());
// 2. explicit vector (size_type n, const value_type& val = value_type(),
//                     const allocator_type& alloc = allocator_type());
// 3. template <class InputIterator>
//    vector (InputIterator first, InputIterator last,
//            const allocator_type& alloc = allocator_type());
// 4. vector (const vector& x);
void TestConstructor()
{
    vector<int> first;
    vector<int> second (4, 100);
    vector<int> third (second.begin(), second.end());
    vector<int> fourth (third);


}
