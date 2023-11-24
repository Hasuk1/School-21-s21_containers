#ifndef CPP2_S21_CONTAINERS_SRC_VECTOR_S21_VECTOR_H_
#define CPP2_S21_CONTAINERS_SRC_VECTOR_S21_VECTOR_H_
namespace s21 {
template <typename T>
class vector {
 public:
  class VectorIterators {
   public:
    VectorIterators() : it_ptr_(nullptr){};
    VectorIterators(T* ptr) : it_ptr_(ptr){};
    VectorIterators(const VectorIterators& other) : it_ptr_(other.it_ptr_){};
    VectorIterators(VectorIterators&& other) : it_ptr_(other.it_ptr_) {
      other.it_ptr_ = nullptr;
    };
    VectorIterators& operator=(const VectorIterators& other) {
      if (this != &other) {
        it_ptr_ = other.it_ptr_;
      }
      return *this;
    };
    VectorIterators& operator=(VectorIterators&& other) noexcept {
      if (this != &other) {
        it_ptr_ = other.it_ptr_;
        other.it_ptr_ = nullptr;
      }
      return *this;
    };
    ~VectorIterators() { it_ptr_ = nullptr; };
    VectorIterators operator-(size_t n) {
      VectorIterators buff(*this);
      for (size_t it = 0; it < n; it++) {
        buff--;
      }
      return buff;
    };
    ptrdiff_t operator-(const VectorIterators& other) {
      return it_ptr_ - other.it_ptr_;
    }
    VectorIterators operator+(size_t n) {
      VectorIterators buff(*this);
      for (size_t it = 0; it < n; it++) {
        buff++;
      }
      return buff;
    };
    VectorIterators& operator-=(size_t n) {
      it_ptr_ = it_ptr_ - n;
      return *this;
    };
    VectorIterators& operator+=(size_t n) {
      it_ptr_ = it_ptr_ + n;
      return *this;
    };
    VectorIterators operator--(int) {
      ErrorCheck(it_ptr_);
      VectorIterators buff(*this);
      --it_ptr_;
      return buff;
    };
    VectorIterators operator--() {
      ErrorCheck(it_ptr_);
      --it_ptr_;
      return *this;
    };
    VectorIterators operator++(int) {
      ErrorCheck(it_ptr_);
      VectorIterators buff(*this);
      ++it_ptr_;
      return buff;
    };
    VectorIterators operator++() {
      ErrorCheck(it_ptr_);
      ++it_ptr_;
      return *this;
    };
    T& operator*() { return *it_ptr_; };
    bool operator==(const VectorIterators& other) const {
      return it_ptr_ == other.it_ptr_;
    };
    bool operator!=(const VectorIterators& other) const {
      return !(*this == other);
    }
    bool operator>(const VectorIterators& other) const {
      return (it_ptr_ > other.it_ptr_);
    }
    bool operator<(const VectorIterators& other) const {
      return (it_ptr_ < other.it_ptr_);
    }
    bool operator<=(const VectorIterators& other) const {
      return (it_ptr_ <= other.it_ptr_);
    }
    bool operator>=(const VectorIterators& other) const {
      return (it_ptr_ >= other.it_ptr_);
    }

   private:
    T* it_ptr_;
    void ErrorCheck(T* it_ptr_) {
      if (!it_ptr_) throw std::out_of_range("out of range");
    };
  };
  class ConstVectorIterators {
   public:
    ConstVectorIterators() : it_ptr_(nullptr){};
    ConstVectorIterators(const T* ptr) : it_ptr_(ptr){};
    ConstVectorIterators(const ConstVectorIterators& other)
        : it_ptr_(other.it_ptr_){};
    ConstVectorIterators(ConstVectorIterators&& other)
        : it_ptr_(other.it_ptr_) {
      other.it_ptr_ = nullptr;
    };
    ConstVectorIterators& operator=(const ConstVectorIterators& other) {
      if (this != &other) {
        it_ptr_ = other.it_ptr_;
      }
      return *this;
    };
    ConstVectorIterators& operator=(ConstVectorIterators&& other) noexcept {
      if (this != &other) {
        it_ptr_ = other.it_ptr_;
        other.it_ptr_ = nullptr;
      }
      return *this;
    };
    ~ConstVectorIterators() { it_ptr_ = nullptr; };
    ConstVectorIterators operator-(size_t n) {
      ConstVectorIterators buff(*this);
      for (size_t it = 0; it < n; it++) {
        buff--;
      }
      return buff;
    };
    ptrdiff_t operator-(const ConstVectorIterators& other) {
      return it_ptr_ - other.it_ptr_;
    }
    ConstVectorIterators operator+(size_t n) {
      ConstVectorIterators buff(*this);
      for (size_t it = 0; it < n; it++) {
        buff++;
      }
      return buff;
    };
    ConstVectorIterators& operator-=(size_t n) {
      it_ptr_ = it_ptr_ - n;
      return *this;
    };
    ConstVectorIterators& operator+=(size_t n) {
      it_ptr_ = it_ptr_ + n;
      return *this;
    };
    ConstVectorIterators operator--(int) {
      ErrorCheck(it_ptr_);
      ConstVectorIterators buff(*this);
      --it_ptr_;
      return buff;
    };
    ConstVectorIterators operator--() {
      ErrorCheck(it_ptr_);
      --it_ptr_;
      return *this;
    };
    ConstVectorIterators operator++(int) {
      ErrorCheck(it_ptr_);
      ConstVectorIterators buff(*this);
      ++it_ptr_;
      return buff;
    };
    ConstVectorIterators operator++() {
      ErrorCheck(it_ptr_);
      ++it_ptr_;
      return *this;
    };
    const T& operator*() { return *it_ptr_; };
    bool operator==(const ConstVectorIterators& other) const {
      return it_ptr_ == other.it_ptr_;
    };
    bool operator!=(const ConstVectorIterators& other) const {
      return !(*this == other);
    }
    bool operator>(const ConstVectorIterators& other) const {
      return (it_ptr_ > other.it_ptr_);
    }
    bool operator<(const ConstVectorIterators& other) const {
      return (it_ptr_ < other.it_ptr_);
    }
    bool operator<=(const ConstVectorIterators& other) const {
      return (it_ptr_ <= other.it_ptr_);
    }
    bool operator>=(const ConstVectorIterators& other) const {
      return (it_ptr_ >= other.it_ptr_);
    }

   private:
    const T* it_ptr_;
    void ErrorCheck(const T* it_ptr_) {
      if (!it_ptr_) throw std::out_of_range("out of range");
    };
  };
  /*____________Vector Member type____________*/
  using value_type = T;
  using reference = T&;
  using const_reference = const T&;
  using iterator = s21::vector<T>::VectorIterators;
  using iteratorType = T*;
  using const_iterator = s21::vector<T>::ConstVectorIterators;
  using size_type = std::size_t;

  /*____________Vector Member functions____________*/
  vector();
  vector(size_type n);
  vector(std::initializer_list<value_type> const& items);
  vector(const vector& v);
  vector(vector&& v) noexcept;
  ~vector();
  vector<T>& operator=(const vector& other);
  vector<T>& operator=(vector&& other) noexcept;
  /*____________Vector Element access____________*/
  reference at(size_type pos);
  reference operator[](size_type pos) const;
  const_reference front() const;
  const_reference back() const;
  iteratorType data() const;
  /*____________Vector Iterators____________*/
  iterator begin() const;
  const_iterator cbegin() const noexcept;
  iterator end() const;
  const_iterator cend() const noexcept;
  /*____________Vector Capacity____________*/
  bool empty() const;
  size_type size() const;
  size_type max_size() const;
  void reserve(size_type size);
  size_type capacity() const;
  void shrink_to_fit();
  /*____________Vector Modifiers____________*/
  void clear() noexcept;
  iterator insert(iterator pos, const_reference value);
  void erase(iterator pos);
  void push_back(const_reference value);
  void pop_back();
  void swap(vector& other);
  /*____________Bonus____________*/
  template <typename... Args>
  iterator insert_many(const_iterator pos, Args&&... args);
  template <typename... Args>
  void insert_many_back(Args&&... args);

 private:
  iteratorType container_;
  size_type size_;
  size_type maxsize_;
};
};  // namespace s21
#include "s21_vector.tpp"
#endif  // CPP2_S21_CONTAINERS_SRC_VECTOR_S21_VECTOR_H_
