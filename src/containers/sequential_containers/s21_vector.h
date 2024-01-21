#ifndef S21_VECTOR_H
#define S21_VECTOR_H

#include <cstddef>
#include <initializer_list>
#include <iostream>
#include <limits>
#include <stdexcept>
#include <utility>

namespace s21 {
template <typename T>
class Vector {
 public:
  class VectorIterator {
   public:
    VectorIterator() : cur_(nullptr) {}
    explicit VectorIterator(T* cur_) : cur_(cur_) {}

    T& operator*() { return (*cur_); }

    VectorIterator& operator++() {
      ++cur_;
      return *this;
    }

    VectorIterator& operator--() {
      --cur_;
      return *this;
    }

    VectorIterator operator++(int) {
      VectorIterator tmp(*this);
      ++cur_;
      return tmp;
    }

    VectorIterator operator--(int) {
      VectorIterator tmp(*this);
      --cur_;
      return tmp;
    }

    VectorIterator& operator+(size_t val) {
      cur_ += val;
      return *this;
    }

    VectorIterator& operator-(size_t val) {
      cur_ -= val;
      return *this;
    }

    bool operator==(const VectorIterator& other) const {
      return (cur_ == other.cur_);
    }

    bool operator!=(const VectorIterator& other) const {
      return (cur_ != other.cur_);
    }

   private:
    T* cur_;
  };

  class VectorIteratorConst {
   public:
    VectorIteratorConst() : cur_(nullptr) {}
    explicit VectorIteratorConst(T* cur_) : cur_(cur_) {}

    T& operator*() const { return *cur_; }

    VectorIteratorConst& operator++() {
      ++cur_;
      return *this;
    }

    VectorIteratorConst& operator--() {
      --cur_;
      return *this;
    }

    VectorIteratorConst operator++(int) {
      VectorIteratorConst tmp(*this);
      ++cur_;
      return tmp;
    }

    VectorIteratorConst operator--(int) {
      VectorIteratorConst tmp(*this);
      --cur_;
      return tmp;
    }

    bool operator==(const VectorIteratorConst& other) const {
      return (cur_ == other.cur_);
    }

    bool operator!=(const VectorIteratorConst& other) const {
      return (cur_ != other.cur_);
    }

   private:
    T* cur_;
  };

  using value_type = T;
  using reference = T&;
  using const_reference = const T&;
  using size_type = size_t;
  using iterator = VectorIterator;
  using const_iterator = VectorIteratorConst;

  Vector()
      : v_size_(0U),
        v_capacity_(0U),
        arr_(value_type()) {}  // default constructor, creates empty vector

  explicit Vector(size_type n)
      : v_size_(n), v_capacity_(n), arr_(n ? new value_type[n] : value_type()) {
    std::fill_n(arr_, n, value_type());
  }  // parameterized constructor, creates the vector of size n

  explicit Vector(std::initializer_list<value_type> const& items)
      : v_size_(items.size()),
        v_capacity_(items.size()),
        arr_(new value_type[items.size()]) {
    std::copy(items.begin(), items.end(), arr_);
  }  // initializer list constructor, creates vector initizialized using
     // std::initializer_list

  Vector(const Vector& v) : Vector() {
    arr_ = new value_type[v.v_capacity_];
    v_size_ = v.v_size_;
    v_capacity_ = v.v_capacity_;
    for (size_type i = 0; i < v.Size(); ++i) arr_[i] = v.arr_[i];
  }  // copy constructor

  Vector(Vector&& v)
      : v_size_(v.v_size_), v_capacity_(v.v_capacity_), arr_(v.arr_) {
    v.arr_ = nullptr;
    v.v_size_ = 0;
    v.v_capacity_ = 0;
  }  // move constructor

  ~Vector() {
    v_size_ = 0;
    v_capacity_ = 0;
    delete[] arr_;
    arr_ = nullptr;
  }  // destructor

  Vector& operator=(Vector&& v) {
    v_size_ = v.v_size_;
    v.v_size_ = 0;
    v_capacity_ = v.v_capacity_;
    v.v_capacity_ = 0;
    delete[] arr_;
    arr_ = v.arr_;
    v.arr_ = nullptr;
    return *this;
  }  // assignment operator overload for moving object

  // Vector Element access
  reference At(size_type pos) {
    if (pos >= v_size_) {
      throw std::out_of_range("Incorrect index");
    }
    return arr_[pos];
  }  // access specified element with bounds checking

  reference operator[](size_type pos) {
    if (pos >= v_size_) {
      throw std::out_of_range("Incorrect index");
    }
    return arr_[pos];
  }  // access specified element

  const_reference operator[](size_type pos) const {
    if (pos >= v_size_) {
      throw std::out_of_range("Incorrect index");
    }
    return arr_[pos];
  }  // access specified element

  const_reference Front() const {
    if (arr_ == nullptr) {
      throw std::out_of_range("Incorrect index");
    }
    return arr_[0];
  }  // access the first element

  const_reference Back() const {
    if (arr_ == nullptr) {
      throw std::out_of_range("Incorrect index");
    }
    return arr_[v_size_ - 1];
  }  // access the last element

  // Vector Iterators
  iterator Begin() {
    return iterator(arr_);
  }  // returns an iterator to the beginning

  const_iterator Cbegin() const { return const_iterator(arr_); }

  iterator End() { return iterator(arr_ + v_size_); }

  const_iterator Cend() const {
    return const_iterator(arr_ + v_size_);
  }  // returns an iterator to the end

  // Vector Capacity
  bool empty() const {
    return (v_size_ == 0);
  }  // checks whether the container is empty

  size_type Size() const { return v_size_; }  // returns the number of elements

  size_type Max_Size() const {
    return std::numeric_limits<size_type>::max() / sizeof(value_type) / 2;
  }  // returns the maximum possible number of elements

  void Reserve(size_type new_cap) {
    if (new_cap > v_capacity_) {
      value_type* new_arr = new value_type[new_cap];
      for (size_t idx = 0; idx < v_size_; ++idx) {
        new_arr[idx] = arr_[idx];
      }
      delete[] arr_;
      arr_ = new_arr;
      v_capacity_ = new_cap;
    }
  }  // allocate storage of size elements and copies current array elements to a
     // newely allocated array

  size_type Capacity() const {
    return v_capacity_;
  }  // returns the number of elements that can be held in currently allocated
     // storage

  void Shrink_To_Fit() {
    if (v_size_ != v_capacity_) {
      auto new_array = new value_type[v_size_];
      for (size_type i = 0U; i < v_size_; ++i) {
        new_array[i] = std::move(arr_[i]);
      }
      delete[] arr_;
      arr_ = std::move(new_array);
      v_capacity_ = v_size_;
    }
  }  // reduces memory usage by freeing unused memory

  // Vector Modifiers
  void Clear() {
    delete[] arr_;
    v_size_ = 0;
    v_capacity_ = 0;
    arr_ = nullptr;
  }  // clears the contents

  iterator Insert(iterator pos, const_reference value) {
    iterator it = Begin();
    size_t new_pos = 0U;
    while (it != pos) {
      ++new_pos;
      ++it;
    }
    if (v_size_ + 1 >= v_capacity_) {
      Reserve(v_capacity_ * 2);
    }
    for (size_t idx = v_size_; idx > new_pos; --idx) {
      arr_[idx] = arr_[idx - 1];
    }
    arr_[new_pos] = value;
    ++v_size_;
    return iterator(arr_ + new_pos);
  }  // inserts elements into concrete pos and returns the iterator that points
     // to the new element

  void Erase(iterator pos) {
    iterator it = Begin();
    size_t new_pos = 0U;
    while (it != pos) {
      ++new_pos;
      ++it;
    }
    if (new_pos >= v_size_) {
      throw std::out_of_range("Incorrect index");
    }
    for (size_t idx = new_pos; idx < v_size_ - 1; ++idx) {
      arr_[idx] = arr_[idx + 1];
    }
    --v_size_;
  }  // erases element at pos

  void Push_Back(const_reference value) {
    if (v_size_ >= v_capacity_) {
      Reserve(v_capacity_ ? v_capacity_ * 2 : 1);
    }
    value_type* new_arr = new value_type[v_size_ + 1U];
    for (size_t idx = 0; idx < v_size_; ++idx) {
      new_arr[idx] = arr_[idx];
    }
    new_arr[v_size_] = value;
    ++v_size_;
    delete[] arr_;
    arr_ = new_arr;
  }  // adds an element to the end

  void Pop_Back() {
    if (v_size_ > 0) {
      value_type* new_arr = new value_type[v_size_ - 1U];
      --v_size_;
      for (size_t idx = 0U; idx < v_size_; ++idx) {
        new_arr[idx] = arr_[idx];
      }
      delete[] arr_;
      arr_ = std::move(new_arr);
    }
  }  // removes the last element

  void Swap(Vector& other) {
    std::swap(other.arr_, arr_);
    std::swap(other.v_size_, v_size_);
    std::swap(other.v_capacity_, v_capacity_);
  }  // swaps the contents

  value_type* Data() { return arr_; }

  // Bonus
  template <typename... Args>
  iterator Insert_Many(const_iterator pos, Args&&... args) {
    auto args_v =
        std::initializer_list<value_type>{std::forward<Args>(args)...};
    const_iterator it = Cbegin();
    size_t new_pos = 0U;
    while (it != pos) {
      ++new_pos;
      ++it;
    }
    for (auto const& i : args_v) {
      Insert((Begin() + new_pos), i);
      ++new_pos;
    }
    return (Begin() + new_pos);
  }

  template <typename... Args>
  void Insert_Many_Back(Args&&... args) {
    auto args_v =
        std::initializer_list<value_type>{std::forward<Args>(args)...};
    for (auto const& i : args_v) {
      Push_Back(i);
    }
  }

 private:
  size_type v_size_;
  size_type v_capacity_;
  value_type* arr_;
};
}  // namespace s21

#endif
