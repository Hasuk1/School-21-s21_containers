namespace s21 {
template <typename T>
array<T>::array() : array_(nullptr), size_(0){};
template <typename T>
array<T>::array(std::initializer_list<value_type> const& other) {
  array_ = new value_type[other.size()];
  size_ = other.size();
  std::copy(other.begin(), other.begin() + other.size(), array_);
};
template <typename T>
array<T>::array(const array& other) {
  array_ = new value_type[other.size_];
  size_ = other.size_;
  std::copy(other.array_, other.array_ + other.size_, array_);
};
template <typename T>
array<T>::array(array&& other) noexcept {
  array_ = other.array_;
  size_ = other.size_;
  other.array_ = nullptr;
  other.size_ = 0;
};
template <typename T>
array<T>::~array() {
  if (array_ != nullptr) delete[] array_;
  size_ = 0;
};
template <typename T>
array<T>& array<T>::operator=(const array& other) {
  if (this != &other) {
    if (array_ != nullptr) delete[] array_;
    array_ = new value_type[other.size_];
    size_ = other.size_;
    std::copy(other.array_, other.array_ + other.size_, array_);
  }
  return *this;
};

template <typename T>
array<T>& array<T>::operator=(array&& other) noexcept {
  if (this != &other) {
    if (array_ != nullptr) delete[] array_;
    array_ = other.array_;
    size_ = other.size_;
    other.array_ = nullptr;
    other.size_ = 0;
  }
  return *this;
};
template <typename T>
typename array<T>::reference array<T>::at(size_type pos) {
  if (pos >= size_) throw std::out_of_range("out of range");
  return array_[pos];
};
template <typename T>
typename array<T>::reference array<T>::operator[](size_type pos) const {
  if (pos >= size_) throw std::out_of_range("out of range");
  return array_[pos];
};
template <typename T>
typename array<T>::const_reference array<T>::front() const {
  if (array_ == nullptr) throw std::out_of_range("out of range");
  return array_[0];
};
template <typename T>
typename array<T>::const_reference array<T>::back() const {
  if (array_ == nullptr) throw std::out_of_range("out of range");
  return array_[size_ - 1];
};
template <typename T>
typename array<T>::iteratorType array<T>::data() {
  return array_;
};
template <typename T>
typename array<T>::iterator array<T>::begin() const {
  return array_;
};
template <typename T>
typename array<T>::iterator array<T>::end() const {
  return array_ + size_;
};
template <typename T>
typename array<T>::const_iterator array<T>::cbegin() const noexcept {
  return array_;
};
template <typename T>
typename array<T>::const_iterator array<T>::cend() const noexcept {
  return array_ + size_;
};
template <typename T>
bool array<T>::empty() {
  return size_ == 0;
};
template <typename T>
typename array<T>::size_type array<T>::size() const {
  return size_;
};
template <typename T>
typename array<T>::size_type array<T>::max_size() const {
  return size_;
};
template <typename T>
void array<T>::swap(array& other) {
  std::swap(size_, other.size_);
  std::swap(array_, other.array_);
};
template <typename T>
void array<T>::fill(const_reference value) {
  for (size_type i = 0; i < size(); i++) {
    array_[i] = value;
  }
};
};  // namespace s21
