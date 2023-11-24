namespace s21 {

template <typename Key>
set<Key>::set() : tree_(new tree_type{}) {}

template <typename Key>
set<Key>::set(std::initializer_list<value_type> const &items) : set() {
  for (const auto item : items) {
    if (!contains(item)) insert(item);
  }
}

template <typename Key>
set<Key>::set(const set &other) : set() {
  if (this != &other) *tree_ = *other.tree_;
}

template <typename Key>
set<Key>::set(set &&other) noexcept
    : tree_(new tree_type(std::move(*other.tree_))) {}

template <typename Key>
set<Key> &set<Key>::operator=(const set &other) {
  if (this != &other) {
    tree_->Clear();
    *tree_ = *other.tree_;
  }
  return *this;
}

template <typename Key>
set<Key> &set<Key>::operator=(set &&other) noexcept {
  if (this != &other) std::swap(tree_, other.tree_);
  return *this;
}

template <typename Key>
set<Key>::~set() {
  if (tree_) {
    delete tree_;
    tree_ = nullptr;
  }
}

template <typename Key>
bool operator==(const set<Key> &lhs, const set<Key> &rhs) {
  return std::equal(lhs.cbegin(), lhs.cend(), rhs.cbegin(), rhs.cend()) &&
         lhs.size() == rhs.size();
}

template <typename Key>
typename set<Key>::iterator set<Key>::begin() noexcept {
  return tree_->Begin();
}

template <typename Key>
typename set<Key>::const_iterator set<Key>::cbegin() const noexcept {
  return tree_->Begin();
}

template <typename Key>
typename set<Key>::iterator set<Key>::end() noexcept {
  return tree_->End();
}

template <typename Key>
typename set<Key>::const_iterator set<Key>::cend() const noexcept {
  return tree_->End();
}

template <typename Key>
inline bool set<Key>::empty() const {
  return tree_ ? tree_->isEmpty() : true;
}

template <typename Key>
inline typename set<Key>::size_type set<Key>::size() const noexcept {
  return tree_ ? tree_->Size() : 0;
}

template <typename Key>
typename set<Key>::size_type set<Key>::max_size() const noexcept {
  if (tree_) {
    return tree_->MaxSize();
  }
  return 0;
}

template <typename Key>
void set<Key>::clear() {
  delete tree_;
  tree_ = new tree_type{};
}

template <typename Key>
std::pair<typename set<Key>::iterator, bool> set<Key>::insert(
    const value_type &value) {
  return tree_->InsertUnique(value);
}

template <typename Key>
void set<Key>::erase(iterator position) noexcept {
  if (position == end()) {
    return;
  }
  tree_->Erase(position);
}

template <typename Key>
typename set<Key>::size_type set<Key>::erase(const key_type &key) noexcept {
  auto it = find(key);
  if (it != end()) {
    erase(it);
    return 1;
  }
  return 0;
}

template <typename Key>
void set<Key>::swap(set &other) noexcept {
  tree_->Swap(*other.tree_);
}

template <typename Key>
void set<Key>::merge(set &other) noexcept {
  if (this == &other) return;
  tree_->MergeUnique(*other.tree_);
  other.clear();
}

template <typename Key>
typename set<Key>::iterator set<Key>::find(const key_type &key) noexcept {
  if (!tree_) return this->end();
  return tree_->Find(key);
}

template <typename Key>
typename set<Key>::const_iterator set<Key>::find(
    const key_type &key) const noexcept {
  if (!tree_) return this->cend();
  return tree_->Find(key);
}

template <typename Key>
typename set<Key>::size_type set<Key>::count(
    const key_type &key) const noexcept {
  return find(key) != cend() ? 1 : 0;
}

template <typename Key>
bool set<Key>::contains(const key_type &key) const noexcept {
  auto end = tree_->End();
  return tree_->Find(key) != end;
}

}  // namespace s21