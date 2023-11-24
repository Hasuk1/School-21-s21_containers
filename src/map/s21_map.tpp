namespace s21 {

template <typename Key, typename Type>
map<Key, Type>::map() : tree_(new tree_type{}) {}

template <typename Key, typename Type>
map<Key, Type>::map(std::initializer_list<value_type> const &items) : map() {
  for (const auto &item : items) insert(item);
}

template <typename Key, typename Type>
map<Key, Type>::map(const map &other) : tree_(new tree_type(*other.tree_)) {}

template <typename Key, typename Type>
map<Key, Type> &map<Key, Type>::operator=(const map &other) {
  if (this != &other) {
    auto *copiedTree = new tree_type(*other.tree_);
    std::swap(tree_, copiedTree);
    delete copiedTree;
  }
  return *this;
}

template <typename Key, typename Type>
map<Key, Type>::map(map &&other) noexcept
    : tree_(new tree_type(std::move(*other.tree_))) {}

template <typename Key, typename Type>
map<Key, Type> &map<Key, Type>::operator=(map &&other) noexcept {
  if (this != &other) {
    std::swap(tree_, other.tree_);
  }
  return *this;
}

template <typename Key, typename Type>
map<Key, Type>::~map() {
  delete tree_;
}

template <typename Key, typename Type>
typename map<Key, Type>::mapped_type &map<Key, Type>::at(const key_type &key) {
  iterator searchIterator = tree_->Find(value_type(key, mapped_type{}));
  if (searchIterator == cend())
    throw std::out_of_range("There is no value with this key.");
  return (*searchIterator).second;
}

template <typename Key, typename Type>
const typename map<Key, Type>::mapped_type &map<Key, Type>::at(
    const key_type &key) const {
  const_iterator searchIterator = tree_->Find(value_type(key, mapped_type{}));
  if (searchIterator == cend())
    throw std::out_of_range("There is no value with this key.");
  return (*searchIterator).second;
}

template <typename Key, typename Type>
typename map<Key, Type>::mapped_type &map<Key, Type>::operator[](
    const key_type &key) {
  value_type temp_value_to_search(key, mapped_type{});
  iterator search_iterator = tree_->Find(temp_value_to_search);
  if (search_iterator != cend()) return (*search_iterator).second;
  std::pair<iterator, bool> insertion_result =
      tree_->InsertUnique(temp_value_to_search);
  return (*insertion_result.first).second;
}

template <typename Key, typename Type>
typename map<Key, Type>::iterator map<Key, Type>::begin() noexcept {
  return tree_->Begin();
}

template <typename Key, typename Type>
typename map<Key, Type>::const_iterator map<Key, Type>::cbegin()
    const noexcept {
  return tree_->Begin();
}

template <typename Key, typename Type>
typename map<Key, Type>::iterator map<Key, Type>::end() noexcept {
  return tree_->End();
}

template <typename Key, typename Type>
typename map<Key, Type>::const_iterator map<Key, Type>::cend() const noexcept {
  return tree_->End();
}

template <typename Key, typename Type>
bool map<Key, Type>::empty() const noexcept {
  return tree_->isEmpty();
}

template <typename Key, typename Type>
typename map<Key, Type>::size_type map<Key, Type>::size() const noexcept {
  return tree_->Size();
}

template <typename Key, typename Type>
typename map<Key, Type>::size_type map<Key, Type>::max_size() const noexcept {
  return tree_->MaxSize();
}

template <typename Key, typename Type>
void map<Key, Type>::clear() noexcept {
  tree_->Clear();
}

template <typename Key, typename Type>
std::pair<typename map<Key, Type>::iterator, bool> map<Key, Type>::insert(
    const value_type &element_to_insert) {
  return tree_->InsertUnique(element_to_insert);
}

template <typename Key, typename Type>
std::pair<typename map<Key, Type>::iterator, bool> map<Key, Type>::insert(
    const key_type &key, const mapped_type &value) {
  return tree_->InsertUnique(value_type{key, value});
}

template <typename Key, typename Type>
std::pair<typename map<Key, Type>::iterator, bool>
map<Key, Type>::insert_or_assign(const key_type &key,
                                 const mapped_type &value) {
  auto [it, inserted] = tree_->InsertUnique(value_type{key, value});
  if (!inserted) (*it).second = value;
  return {it, inserted};
}

template <typename Key, typename Type>
void map<Key, Type>::erase(iterator pos) {
  tree_->Erase(pos);
}

template <typename Key, typename Type>
void map<Key, Type>::swap(map &other) noexcept {
  tree_->Swap(*other.tree_);
}

template <typename Key, typename Type>
void map<Key, Type>::merge(map &other) noexcept {
  tree_->MergeUnique(*other.tree_);
}

template <typename Key, typename Type>
bool map<Key, Type>::contains(const key_type &key) const noexcept {
  value_type keyValuePair(key, mapped_type{});
  return tree_->Find(keyValuePair) != cend();
}

template <typename Key, typename Type>
typename map<Key, Type>::iterator map<Key, Type>::find(
    const key_type &key) noexcept {
  value_type temporary_entry(key, mapped_type{});
  return tree_->Find(temporary_entry);
}

template <typename Key, typename Type>
typename map<Key, Type>::const_iterator map<Key, Type>::find(
    const key_type &key) const noexcept {
  value_type temporary_entry(key, mapped_type{});
  return tree_->Find(temporary_entry);
}

}  // namespace s21