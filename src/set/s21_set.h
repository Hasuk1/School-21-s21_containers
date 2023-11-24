#ifndef CPP2_S21_CONTAINERS_SRC_SET_S21_SET_H_
#define CPP2_S21_CONTAINERS_SRC_SET_S21_SET_H_

#include "./../rb_tree/RB_tree.h"

namespace s21 {
template <typename Key>
class set : public RedBlackTree<Key, Key> {
 public:
  /*Member type*/
  using key_type = Key;
  using value_type = key_type;
  using reference = value_type &;
  using const_reference = const value_type &;
  using tree_type = RedBlackTree<value_type>;
  using iterator = typename tree_type::iterator;
  using const_iterator = typename tree_type::const_iterator;
  using size_type = size_t;

  /*Member functions*/
  set();
  set(std::initializer_list<value_type> const &items);
  set(const set &other);
  set &operator=(set &&other) noexcept;
  set(set &&other) noexcept;
  set &operator=(const set &other);
  ~set();

  /*Non-member functions*/
  template <typename T>
  friend bool operator==(const set<T> &lhs, const set<T> &rhs);

  /*Iterators*/
  iterator begin() noexcept;
  const_iterator cbegin() const noexcept;
  iterator end() noexcept;
  const_iterator cend() const noexcept;

  /*Capacity*/
  bool empty() const;
  size_type size() const noexcept;
  size_type max_size() const noexcept;

  /*Modifiers*/
  void clear();
  std::pair<iterator, bool> insert(const value_type &value);
  void erase(iterator pos) noexcept;
  size_type erase(const key_type &key) noexcept;
  void swap(set &other) noexcept;
  void merge(set &other) noexcept;

  /*Lookup*/
  iterator find(const key_type &key) noexcept;
  const_iterator find(const key_type &key) const noexcept;
  size_type count(const key_type &key) const noexcept;
  bool contains(const key_type &key) const noexcept;

 private:
  tree_type *tree_;
};
}  // namespace s21

#include "s21_set.tpp"
#endif  // CPP2_S21_CONTAINERS_SRC_SET_S21_SET_H_