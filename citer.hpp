#ifndef CITERATOR_HPP
#define CITERATOR_HPP

namespace topit
{
  template < class T >
  struct Vector;
  template < class T >
  class CVectIter
  {
    friend class topit::Vector< T >;
    CVectIter() noexcept:
      ptr_(nullptr)
    {}
    CVectIter(const T* ptr) noexcept:
      ptr_(ptr)
    {}

  public:
    const T& operator*() const;
    CVectIter< T >& operator++();
    CVectIter< T > operator++(int);
    CVectIter< T > operator+(int);

    bool operator!=(const CVectIter< T >&) const;
    bool operator==(const CVectIter< T >&) const;

  private:
    const T* ptr_;
  };

  template < class T >
  const T& topit::CVectIter< T >::operator*() const
  {
    return *ptr_;
  }

  template < class T >
  CVectIter< T >& topit::CVectIter< T >::operator++()
  {
    ++ptr_;
    return *this;
  }

  template < class T >
  CVectIter< T > topit::CVectIter< T >::operator++(int)
  {
    CVectIter< T > tmp = *this;
    ++ptr_;
    return tmp;
  }
  template < class T >
  CVectIter< T > topit::CVectIter< T >::operator+(int n)
  {
    return CVectIter(ptr_ + n);
  }
  template < class T >
  bool topit::CVectIter< T >::operator!=(const CVectIter< T >& other) const
  {
    return ptr_ != other.ptr_;
  }
  template < class T >
  bool topit::CVectIter< T >::operator==(const CVectIter< T >& other) const
  {
    return ptr_ == other.ptr_;
  }
}

#endif
