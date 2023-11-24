#ifndef CPP2_S21_CONTAINERS_SRC_SET_S21_MAP_H_
#define CPP2_S21_CONTAINERS_SRC_SET_S21_MAP_H_

#include <list>

#include "./../rb_tree/RB_tree.h"

namespace s21 {

template <typename Key, typename Type>
class map {
 public:
  /*Member type*/
  using key_type = Key;
  using mapped_type = Type;
  using value_type = std::pair<const key_type, mapped_type>;
  using reference = value_type &;
  using const_reference = const value_type &;

  struct KeyComparator {
    template <typename PairType>
    bool operator()(const PairType &lhs, const PairType &rhs) const noexcept {
      return lhs.first < rhs.first;
    }
  };

  using tree_type = RedBlackTree<value_type, KeyComparator>;
  using iterator = typename tree_type::iterator;
  using const_iterator = typename tree_type::const_iterator;
  using size_type = size_t;

  /*Member functions*/
  map();
  map(std::initializer_list<value_type> const &items);
  map(const map &otherMap);
  map &operator=(const map &otherMap);
  map(map &&otherMap) noexcept;
  map &operator=(map &&otherMap) noexcept;
  ~map();

  /*Element access*/
  mapped_type &at(const key_type &key);
  const mapped_type &at(const key_type &key) const;
  mapped_type &operator[](const key_type &key);

  /*Iterators*/
  iterator begin() noexcept;
  const_iterator cbegin() const noexcept;
  iterator end() noexcept;
  const_iterator cend() const noexcept;

  /*Capacity*/
  bool empty() const noexcept;
  size_type size() const noexcept;
  size_type max_size() const noexcept;

  /*Modifiers*/
  void clear() noexcept;
  std::pair<iterator, bool> insert(const value_type &element_to_insert);
  std::pair<iterator, bool> insert(const key_type &key,
                                   const mapped_type &value);
  std::pair<iterator, bool> insert_or_assign(const key_type &key,
                                             const mapped_type &value);
  void erase(iterator pos);
  void swap(map &otherMap) noexcept;
  void merge(map &otherMap) noexcept;

  /*Lookup*/
  iterator find(const key_type &key) noexcept;
  const_iterator find(const key_type &key) const noexcept;
  bool contains(const key_type &key) const noexcept;

 private:
  tree_type *tree_;
};

}  // namespace s21

#include "s21_map.tpp"

#endif  // CPP2_S21_CONTAINERS_SRC_SET_S21_MAP_H_