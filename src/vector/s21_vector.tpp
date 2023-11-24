namespace s21 {
template <typename T>
vector<T>::vector() : container_(nullptr), size_(0), maxsize_(0) {}

template <typename T>
vector<T>::vector(size_type n)
    : container_(new value_type[n]), size_(n), maxsize_(n) {
  for (size_type i = 0; i < n; i++) {
    container_[i] = value_type();
  }
}

template <typename T>
vector<T>::vector(std::initializer_list<value_type> const& other) {
  container_ = new value_type[other.size()];
  size_ = other.size();
  maxsize_ = other.size();
  std::copy(other.begin(), other.end(), container_);
}

template <typename T>
vector<T>::vector(const vector& other) {
  container_ = new value_type[other.size_];
  size_ = other.size_;
  maxsize_ = other.maxsize_;
  std::copy(other.container_, other.container_ + other.size_, container_);
}

template <typename T>
vector<T>::vector(vector&& other) noexcept {
  container_ = other.container_;
  size_ = other.size_;
  maxsize_ = other.maxsize_;
  other.container_ = nullptr;
  other.size_ = 0;
  other.maxsize_ = 0;
}

template <typename T>
vector<T>::~vector() {
  if (container_ != nullptr) delete[] container_;
  container_ = nullptr;
  size_ = 0;
  maxsize_ = 0;
}

template <typename T>
vector<T>& vector<T>::operator=(const vector& other) {
  if (this != &other) {
    if (container_ != nullptr) delete[] container_;
    container_ = new value_type[other.size_];
    size_ = other.size_;
    maxsize_ = other.maxsize_;
    std::copy(other.container_, other.container_ + other.size_, container_);
  }
  return *this;
}

template <typename T>
vector<T>& vector<T>::operator=(vector&& other) noexcept {
  if (this != &other) {
    if (container_ != nullptr) delete[] container_;
    maxsize_ = other.maxsize_;
    size_ = other.size_;
    container_ = other.container_;
    other.container_ = nullptr;
    other.maxsize_ = 0;
    other.size_ = 0;
  }
  return *this;
};

/*________________________Vector Element access________________________*/
template <typename T>
typename vector<T>::reference vector<T>::at(size_type pos) {
  if (pos >= maxsize_) throw std::out_of_range("out of range");
  return container_[pos];
}

template <typename T>
typename vector<T>::reference vector<T>::operator[](size_type pos) const {
  if (pos > size_) throw std::out_of_range("out of range");
  return container_[pos];
}

template <typename T>
typename vector<T>::const_reference vector<T>::front() const {
  if (container_ == nullptr) throw std::out_of_range("out of range");
  return container_[0];
}

template <typename T>
typename vector<T>::const_reference vector<T>::back() const {
  if (container_ == nullptr) throw std::out_of_range("out of range");
  return container_[size_ - 1];
}

template <typename T>
typename vector<T>::iteratorType vector<T>::data() const {
  return container_;
}

/*________________________Vector Iterators________________________*/

template <typename T>
typename vector<T>::iterator vector<T>::begin() const {
  return container_;
}

template <typename T>
typename vector<T>::const_iterator vector<T>::cbegin() const noexcept {
  return container_;
}
template <typename T>
typename vector<T>::iterator vector<T>::end() const {
  return container_ + size_;
}

template <typename T>
typename vector<T>::const_iterator vector<T>::cend() const noexcept {
  return container_ + size_;
}
/*________________________Vector Capacity________________________*/
template <typename T>
bool vector<T>::empty() const {
  return size_ == 0;
}

template <typename T>
typename vector<T>::size_type vector<T>::size() const {
  return size_;
}

template <typename T>
typename vector<T>::size_type vector<T>::max_size() const {
  return std::numeric_limits<size_t>::max() / sizeof(T);
}

template <typename T>
void vector<T>::reserve(size_type size) {
  if (size <= maxsize_) {
    return;
  }
  if (size > max_size()) {
    throw std::out_of_range("out of range");
  }
  value_type* new_container = new value_type[size];
  std::copy(container_, container_ + size_, new_container);
  delete[] container_;
  container_ = new_container;
  maxsize_ = size;
}

template <typename T>
typename vector<T>::size_type vector<T>::capacity() const {
  return maxsize_;
}

template <typename T>
void vector<T>::shrink_to_fit() {
  maxsize_ = maxsize_ - (maxsize_ - size_);
}

/*________________________Vector Modifiers________________________*/
template <typename T>
void vector<T>::clear() noexcept {
  size_ = 0;
}

template <typename T>
typename vector<T>::iterator vector<T>::insert(iterator pos,
                                               const_reference value) {
  if (pos > end()) throw std::out_of_range("out of range");
  size_type index = pos - begin();
  if (size_ >= maxsize_) {
    reserve(maxsize_ ? maxsize_ * 2 : 1);
  }
  iterator res = begin() + index;
  for (iterator i = end(); i != res - 1; --i) {
    if (i == res)
      *res = value;
    else
      *i = *(i - 1);
  }
  size_++;
  return res;
}

template <typename T>
void vector<T>::erase(iterator pos) {
  if (pos >= end()) throw std::out_of_range("out of range");
  for (iterator it = pos; it != end() - 1; ++it) {
    *it = *(it + 1);
  }
  --size_;
}

template <typename T>
void vector<T>::push_back(const_reference value) {
  if (size_ >= maxsize_) {
    reserve(maxsize_ ? maxsize_ * 2 : 1);
  }
  container_[size_++] = value;
}

template <typename T>
void vector<T>::pop_back() {
  if (size_ > 0) {
    --size_;
  }
}

template <typename T>
void vector<T>::swap(vector& other) {
  std::swap(container_, other.container_);
  std::swap(size_, other.size_);
  std::swap(maxsize_, other.maxsize_);
}

template <typename T>
template <typename... Args>
typename vector<T>::iterator vector<T>::insert_many(const_iterator pos,
                                                    Args&&... args) {
  vector<value_type> buffer{args...};
  iterator buffer_pos = begin() + (pos - cbegin());
  for (size_type i = 0; i < buffer.size(); i++) {
    buffer_pos = insert(buffer_pos, buffer[i]);
    buffer_pos++;
  }
  return buffer_pos;
}

template <typename T>
template <typename... Args>
void vector<T>::insert_many_back(Args&&... args) {
  vector<value_type> buffer{args...};
  for (size_type i = 0; i < buffer.size(); i++) {
    push_back(buffer[i]);
  }
}
};  // namespace s21
