#ifndef TOP_IT_VECTOR
#define TOP_IT_VECTOR
#include "citer.hpp"
#include "iter.hpp"
#include <cstddef>
#include <iomanip>
// Классная работа
// СТРОГАЯ ГАРАНТИЯ!!!
// Тестирование для копирования и перемещения
// insert (x2)
// erase (x2)
// + тесты
// pushBack/popBack
// Домашнее задание
// СТРОГАЯ ГАРАНТИЯ! ! !!
// Итераторы для вектора
// Придумать несколько insert/erase с итераторами
// По 3 штуки + тесты
namespace topit
{
  template < class T >
  struct Vector
  {
    ~Vector();
    Vector();
    Vector(const Vector&);
    Vector(Vector&&);
    Vector(size_t size, const T& init);
    Vector< T >& operator=(const Vector< T >&);
    Vector< T >& operator=(Vector< T >&&) noexcept;

    bool isEmpty() const noexcept;
    size_t getSize() const noexcept;
    size_t getCapacity() const noexcept;

    T& operator[](size_t id) noexcept;
    const T& operator[](size_t id) const noexcept;
    T& at(size_t id);
    const T& at(size_t id) const;
    void swap(Vector< T >& rhs) noexcept;
    VectIter< T > begin();
    VectIter< T > end();

    void pushBack(const T& v);
    void popBack();
    VectIter< T > insert(CVectIter< T > pos, const T& v);
    VectIter< T > insert(CVectIter< T > pos, VectIter< T > beg, VectIter< T > end);

    void erase(CVectIter< T > pos);
    void erase(VectIter< T > beg, VectIter< T > end);

  private:
    explicit Vector(size_t size);
    T* data_;
    size_t size_, capacity_;
  };
  template < class T >
  bool operator==(const Vector< T >& lhs, const Vector< T >& rhs);
}
template < class T >
topit::VectIter< T > topit::Vector< T >::insert(CVectIter< T > pos, const T& v)
{
  size_t index = pos - begin();
  if (size_ == capacity_) {

    size_t newCapacity = capacity_ ? capacity_ * 2 : 1;
    T* newData = new T[newCapacity];

    for (size_t i = 0; i < index; ++i) {
      newData[i] = data_[i];
    }
    newData[index] = v;
    for (size_t i = index; i < size_; ++i) {
      newData[i + 1] = data_[i];
    }

    delete[] data_;
    data_ = newData;
    capacity_ = newCapacity;
    size_++;
  } else {
    for (VectIter< T > it = end(); it > begin() + index; --it) {
      *it = *(it - 1);
    }
  }
  pos=begin() + index
  *(pos) = v;
  ++size_;
  return pos;
}

template < class T >
topit::VectIter< T > topit::Vector< T >::insert(CVectIter< T > pos, VectIter< T > first, VectIter< T > last)
{
  size_t index = pos - begin();
  size_t length = last - first;
  if (size_ + length > capacity_) {

    size_t newCapacity = capacity_ ? capacity_ * 2 : 1;

    while (newCapacity < size_ + length) {
      newCapacity *= 2;
    }
    T* newData = new T[newCapacity];
    for (size_t i = 0; i < index; ++i) {
      newData[i] = data_[i];
    }
    for (size_t i = 0; i < length; ++i) {
      newData[index + i] = *(first + i);
    }

    for (size_t i = index ; i < size_; ++i) {
      newData[i+ length] = data_[i];
    }

    delete[] data_;
    data_ = newData;
    capacity_ = newCapacity;
  } else {
    for (VectIter< T > it = end(); it > begin() + index + length; --it) {
      *it = *(it - 1);
    }
    for (size_t i = 0; i < length; ++i) {
      data_[i+index] = *(first + i);
    }
  }
  size_ += length;
  return begin() + index;
}

template < class T >
void topit::Vector< T >::erase(CVectIter< T > pos)
{

  for (auto it=pos;it<end()-1;++it) {
    *it=*(it+1);
  }
  size_--;
  return begin() + (pos-begin());
}

template < class T >
void topit::Vector< T >::erase(VectIter< T > first, VectIter< T > last)
{
  size_t index=first-begin();
  size_t count=last-first;

  for (size_t i=index;i<index+count;++i) {
    data[i]=data[i+count];
  }
}

template < class T >
topit::VectIter< T > topit::Vector< T >::begin()
{
  return VectIter< T >(data_);
}

template < class T >
topit::VectIter< T > topit::Vector< T >::end()
{
  return VectIter< T >(data_ + size_);
}

template < class T >
void topit::Vector< T >::swap(Vector< T >& rhs) noexcept
{
  std::swap(data_, rhs.data_);
  std::swap(size_, rhs.size_);
  std::swap(capacity_, rhs.capacity_);
}
template < class T >
topit::Vector< T >& topit::Vector< T >::operator=(const Vector< T >& rhs)
{
  if (this == std::addressof(rhs)) {
    return *this;
  }

  Vector< T > cpy(rhs);
  swap(cpy);
  return *this;
}

template < class T >
topit::Vector< T >& topit::Vector< T >::operator=(Vector< T >&& rhs) noexcept
{
  if (this == std::addressof(rhs)) {
    return *this;
  }

  Vector< T > cpy(std::move(rhs));
  swap(cpy);
  return *this;
}

template < class T >
topit::Vector< T >::Vector(Vector< T >&& rhs):
  data_(rhs.data_),
  size_(rhs.size_),
  capacity_(rhs.capacity_)
{
  rhs.data_ = nullptr;
}
template < class T >
topit::Vector< T >::Vector(size_t size, const T& init):
  data_(size ? new T[size] : nullptr),
  size_(size),
  capacity_(size)
{
  for (size_t i = 0; i < size; ++i) {
    data_[i] = init;
  }
}

template < class T >
topit::Vector< T >::Vector(size_t size):
  data_(size ? new T[size] : nullptr),
  size_(size),
  capacity_(size)
{}
template < class T >
topit::Vector< T >::Vector(const Vector< T >& rhs):
  Vector(rhs.getSize())
{
  for (size_t i = 0; i < rhs.getSize(); ++i) {
    try {
      data_[i] = rhs[i];
    } catch (...) {
      delete[] data_;
      throw;
    }
  }
}
template < class T >
bool topit::operator==(const Vector< T >& lhs, const Vector< T >& rhs)
{

  bool isEqual = lhs.getSize() == rhs.getSize();
  for (size_t i = 0; (i < lhs.getSize()) && (isEqual = isEqual && lhs[i] == rhs[i]); ++i)
    ;
  return isEqual;
}
template < class T >
T& topit::Vector< T >::operator[](size_t id) noexcept
{
  const Vector< T >* cthis = this;

  return const_cast< T& >((*cthis)[id]);
}
template < class T >
const T& topit::Vector< T >::operator[](size_t id) const noexcept
{
  return data_[id];
}
template < class T >
T& topit::Vector< T >::at(size_t id)
{
  const Vector< T >* cthis = this;
  return const_cast< T& >(cthis->at(id));
}
template < class T >
const T& topit::Vector< T >::at(size_t id) const
{
  if (id < getSize()) {
    return (*this)[id];
  }
  throw std::out_of_range("bad id");
}
template < class T >
bool topit::Vector< T >::isEmpty() const noexcept
{
  return !size_;
}
template < class T >
size_t topit::Vector< T >::getSize() const noexcept
{
  return size_;
}
template < class T >
size_t topit::Vector< T >::getCapacity() const noexcept
{
  return capacity_;
}
template < class T >
void topit::Vector< T >::pushBack(const T& v)
{
  if (size_ == capacity_) {
    size_t newCapacity = capacity_ ? capacity_ * 2 : 1;
    T* newData = new T[newCapacity];

    for (size_t i = 0; i < size_; ++i) {
      newData[i] = data_[i];
    }

    delete[] data_;
    data_ = newData;
    capacity_ = newCapacity;
  }
  data_[size_++] = v;
}
template < class T >
void topit::Vector< T >::popBack()
{
  if (size_ > 0) {
    size_--;
  }
}
template < class T >
topit::Vector< T >::~Vector()
{
  delete[] data_;
}
template < class T >
topit::Vector< T >::Vector():
  data_(nullptr),
  size_(0),
  capacity_(0)
{}
#endif
