#ifndef ITERATOR_HPP
#define ITERATOR_HPP

namespace topit
{
  template < class T >
  struct Vector;
  template < class T >
  class VectIter
  {
    friend class topit::Vector< T >;
    VectIter() noexcept:
      ptr_(nullptr)
    {}
    VectIter(T* ptr) noexcept:
      ptr_(ptr)
    {}

  public:
    T& operator*();
    VectIter< T >& operator++();
    VectIter< T > operator++(int);
    VectIter< T > operator+(int);

    VectIter< T >& operator--();
    VectIter< T > operator--(int);
    VectIter< T > operator-(const VectIter< T >&);
    bool operator!=(const VectIter< T >&) const;
    bool operator==(const VectIter< T >&) const;

  private:
    T* ptr_;
  };

  template < class T >
  T& topit::VectIter< T >::operator*()
  {
    return *ptr_;
  }

  template < class T >
  VectIter< T >& topit::VectIter< T >::operator++()
  {
    ++ptr_;
    return *this;
  }

  template < class T >
  VectIter< T > topit::VectIter< T >::operator++(int)
  {
    VectIter< T > tmp = *this;
    ++ptr_;
    return tmp;
  }
  template < class T >
  VectIter< T > topit::VectIter< T >::operator+(int n)
  {
    return VectIter(ptr_ + n);
  }
  template < class T >
  VectIter< T >& topit::VectIter< T >::operator--()
  {
    --ptr_;
    return *this;
  }

  template < class T >
  VectIter< T > topit::VectIter< T >::operator--(int)
  {
    VectIter< T > tmp = *this;
    --ptr_;
    return tmp;
  }
  template < class T >
  VectIter< T > topit::VectIter< T >::operator-(const VectIter< T >& other)
  {
    return VectIter(ptr_ - other.ptr_);
  }
  template < class T >
  bool topit::VectIter< T >::operator!=(const VectIter< T >& other) const
  {
    return ptr_ != other.ptr_;
  }
  template < class T >
  bool topit::VectIter< T >::operator==(const VectIter< T >& other) const
  {
    return ptr_ == other.ptr_;
  }
}

#endif
