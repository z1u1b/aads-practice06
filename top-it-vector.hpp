#ifndef TOP_IT_VECTOR
#define TOP_IT_VECTOR
#include <cstddef>
template <class T>
struct Vector {
  T* data;
  size_t size,capacity;
};

#endif
