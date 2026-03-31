#ifndef TOP_IT_VECTOR
#define TOP_IT_VECTOR
#include <cstddef>
#include <iomanip>
namespace topit
{
  template < class T >
  struct Vector
  {
    ~Vector();
    Vector();
    Vector(const Vector&);
    Vector(Vector&&);
    explicit Vector(std::initializer_list< T > il);
    explicit Vector(size_t size, const T& init);
    Vector< T >& operator=(const Vector< T >&);
    Vector< T >& operator=(Vector< T >&&) noexcept;

    bool isEmpty() const noexcept;
    size_t getSize() const noexcept;
    size_t getCapacity() const noexcept;
    void reserve(size_t);
    void shrinkToFit();

    T& operator[](size_t id) noexcept;
    const T& operator[](size_t id) const noexcept;
    T& at(size_t id);
    const T& at(size_t id) const;
    void swap(Vector< T >& rhs) noexcept;

    void pushBack(const T& v);
    void pushBackCount(size_t k, const T& v) template < class IT >
    template <class IT>
    void pushBackRange(IT a, size_t count);
    void unsafePushBack(size_t k, const T& v)


        void popBack();
    void insert(size_t i, const T& v);
    void erase(size_t i);

  private:
    explicit Vector(size_t size);
    T* data_;
    size_t size_, capacity_;
  };
  template < class T >
  bool operator==(const Vector< T >& lhs, const Vector< T >& rhs);
}
template < class T >
template < class IT >
void topit::Vector< T >::pushBackRange(IT a, size_t count)
{}

template < class T >
void topit::Vector< T >::pushBackCount(size_t k, const T& v)
{}

template < class T >
void topit::Vector< T >::unsafePushBack(size_t k, const T& v)
{
  assert(size_ < capacity_);
}
template < class T >
topit::Vector< T >::Vector(std::initializer_list< T > il):
  Vector(il.size())
{
  size_t i = 0;
  for (auto it = il.begin(); it != il.end(); ++it) {
    data_[i++] = *it;
  }
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
