#ifndef TOP_IT_VECTOR
#define TOP_IT_VECTOR
#include <cstddef>
namespace topit
{
  template < class T >
  struct Vector
  {
    ~Vector();
    Vector();

    bool isEmpty() const noexcept;

  private:
    T* data_;
    size_t size_, capacity_;
  };
}
template < class T >
bool topit::Vector< T >::isEmpty() const noexcept
{
  return !size_;
}

template < class T >
topit::Vector< T >::~Vector()
{
  delete [] data_;
}
template < class T >
topit::Vector< T >::Vector():
  data_(nullptr),
  size_(0),
  capacity_(0)
{}
#endif
