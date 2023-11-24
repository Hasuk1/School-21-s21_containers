#ifndef CPP2_S21_CONTAINERS_SRC_ARRAY_S21_ARRAY_H_
#define CPP2_S21_CONTAINERS_SRC_ARRAY_S21_ARRAY_H_
namespace s21 {
template <typename T>
class array {
 public:
  class ArrayIterators {
   public:
    ArrayIterators() : it_ptr_(nullptr){};
    ArrayIterators(T* ptr) : it_ptr_(ptr){};
    ArrayIterators(const ArrayIterators& other) : it_ptr_(other.it_ptr_){};
    ArrayIterators(ArrayIterators&& other) : it_ptr_(other.it_ptr_) {
      other.it_ptr_ = nullptr;
    };
    ArrayIterators& operator=(const ArrayIterators& other) {
      if (this != &other) {
        it_ptr_ = other.it_ptr_;
      }
      return *this;
    };
    ArrayIterators& operator=(ArrayIterators&& other) noexcept {
      if (this != &other) {
        it_ptr_ = other.it_ptr_;
        other.it_ptr_ = nullptr;
      }
      return *this;
    };
    ~ArrayIterators() { it_ptr_ = nullptr; };
    /*____________operators____________*/
    ArrayIterators operator-(size_t n) {
      ArrayIterators buff(*this);
      for (size_t it = 0; it < n; it++) {
        buff--;
      }
      return buff;
    };
    ptrdiff_t operator-(const ArrayIterators& other) {
      return it_ptr_ - other.it_ptr_;
    }
    ArrayIterators operator+(size_t n) {
      ArrayIterators buff(*this);
      for (size_t it = 0; it < n; it++) {
        buff++;
      }
      return buff;
    };
    ArrayIterators& operator-=(size_t n) {
      it_ptr_ = it_ptr_ - n;
      return *this;
    };
    ArrayIterators& operator+=(size_t n) {
      it_ptr_ = it_ptr_ + n;
      return *this;
    };
    ArrayIterators operator--(int) {
      ErrorCheck(it_ptr_);
      ArrayIterators buff(*this);
      --it_ptr_;
      return buff;
    };
    ArrayIterators operator--() {
      ErrorCheck(it_ptr_);
      --it_ptr_;
      return *this;
    };
    ArrayIterators operator++(int) {
      ErrorCheck(it_ptr_);
      ArrayIterators buff(*this);
      ++it_ptr_;
      return buff;
    };
    ArrayIterators operator++() {
      ErrorCheck(it_ptr_);
      ++it_ptr_;
      return *this;
    };
    T& operator*() { return *it_ptr_; };
    bool operator==(const ArrayIterators& other) const {
      return it_ptr_ == other.it_ptr_;
    };
    bool operator!=(const ArrayIterators& other) const {
      return !(*this == other);
    }
    bool operator>(const ArrayIterators& other) const {
      return (it_ptr_ > other.it_ptr_);
    }
    bool operator<(const ArrayIterators& other) const {
      return (it_ptr_ < other.it_ptr_);
    }
    bool operator<=(const ArrayIterators& other) const {
      return (it_ptr_ <= other.it_ptr_);
    }
    bool operator>=(const ArrayIterators& other) const {
      return (it_ptr_ >= other.it_ptr_);
    }

   private:
    T* it_ptr_;
    void ErrorCheck(T* it_ptr_) {
      if (!it_ptr_) throw std::out_of_range("out of range");
    };
  };
  class ConstArrayIterators {
   public:
    ConstArrayIterators() : it_ptr_(nullptr){};
    ConstArrayIterators(const T* ptr) : it_ptr_(ptr){};
    ConstArrayIterators(const ConstArrayIterators& other)
        : it_ptr_(other.it_ptr_){};
    ConstArrayIterators(ConstArrayIterators&& other) : it_ptr_(other.it_ptr_) {
      other.it_ptr_ = nullptr;
    };
    ConstArrayIterators& operator=(const ConstArrayIterators& other) {
      if (this != &other) {
        it_ptr_ = other.it_ptr_;
      }
      return *this;
    };
    ConstArrayIterators& operator=(ConstArrayIterators&& other) noexcept {
      if (this != &other) {
        it_ptr_ = other.it_ptr_;
        other.it_ptr_ = nullptr;
      }
      return *this;
    };
    ~ConstArrayIterators() { it_ptr_ = nullptr; };
    /*____________operators____________*/
    ConstArrayIterators operator-(size_t n) {
      ConstArrayIterators buff(*this);
      for (size_t it = 0; it < n; it++) {
        buff--;
      }
      return buff;
    };
    ptrdiff_t operator-(const ConstArrayIterators& other) {
      return it_ptr_ - other.it_ptr_;
    }
    ConstArrayIterators operator+(size_t n) {
      ConstArrayIterators buff(*this);
      for (size_t it = 0; it < n; it++) {
        buff++;
      }
      return buff;
    };
    ConstArrayIterators& operator-=(size_t n) {
      it_ptr_ = it_ptr_ - n;
      return *this;
    };
    ConstArrayIterators& operator+=(size_t n) {
      it_ptr_ = it_ptr_ + n;
      return *this;
    };
    ConstArrayIterators operator--(int) {
      ErrorCheck(it_ptr_);
      ConstArrayIterators buff(*this);
      --it_ptr_;
      return buff;
    };
    ConstArrayIterators operator--() {
      ErrorCheck(it_ptr_);
      --it_ptr_;
      return *this;
    };
    ConstArrayIterators operator++(int) {
      ErrorCheck(it_ptr_);
      ConstArrayIterators buff(*this);
      ++it_ptr_;
      return buff;
    };
    ConstArrayIterators operator++() {
      ErrorCheck(it_ptr_);
      ++it_ptr_;
      return *this;
    };
    const T& operator*() { return *it_ptr_; };
    bool operator==(const ConstArrayIterators& other) const {
      return it_ptr_ == other.it_ptr_;
    };
    bool operator!=(const ConstArrayIterators& other) const {
      return !(*this == other);
    }
    bool operator>(const ConstArrayIterators& other) const {
      return (it_ptr_ > other.it_ptr_);
    }
    bool operator<(const ConstArrayIterators& other) const {
      return (it_ptr_ < other.it_ptr_);
    }
    bool operator<=(const ConstArrayIterators& other) const {
      return (it_ptr_ <= other.it_ptr_);
    }
    bool operator>=(const ConstArrayIterators& other) const {
      return (it_ptr_ >= other.it_ptr_);
    }

   private:
    const T* it_ptr_;
    void ErrorCheck(const T* it_ptr_) {
      if (!it_ptr_) throw std::out_of_range("out of range");
    };
  };
  using value_type = T;
  using reference = T&;
  using const_reference = const T&;
  using iterator = s21::array<T>::ArrayIterators;
  using iteratorType = T*;
  using const_iterator = s21::array<T>::ConstArrayIterators;
  using size_type = std::size_t;

  array();
  array(std::initializer_list<value_type> const& other);
  array(const array& other);
  array(array&& other) noexcept;
  ~array();
  array<T>& operator=(const array& other);
  array<T>& operator=(array&& other) noexcept;
  reference at(size_type pos);
  reference operator[](size_type pos) const;
  const_reference front() const;
  const_reference back() const;
  iteratorType data();
  iterator begin() const;
  const_iterator cbegin() const noexcept;
  iterator end() const;
  const_iterator cend() const noexcept;
  bool empty();
  size_type size() const;
  size_type max_size() const;
  void swap(array& other);
  void fill(const_reference value);

 private:
  iteratorType array_;
  size_type size_;
};
};  // namespace s21
#include "s21_array.tpp"
#endif  // CPP2_S21_CONTAINERS_SRC_ARRAY_S21_ARRAY_H_
