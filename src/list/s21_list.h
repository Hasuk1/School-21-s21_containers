#ifndef CPP2_S21_CONTAINERS_SRC_LIST_S21_LIST_H_
#define CPP2_S21_CONTAINERS_SRC_LIST_S21_LIST_H_

#include "./../queue/s21_queue.h"

namespace s21 {
template <typename T>
class list {
 public:
  struct Node {
    T data;
    Node *next;
    Node *prev;

    Node(T data = T(), Node *next = nullptr, Node *prev = nullptr)
        : data(data), next(next), prev(prev) {}
  };

  class ListIteratorBase {
   public:
    using difference_type = std::ptrdiff_t;
    using iterator_category = std::bidirectional_iterator_tag;

    ListIteratorBase() : node_(nullptr) {}
    ListIteratorBase(Node *node) : node_(node) {}

    bool operator==(const ListIteratorBase &other) const {
      return node_ == other.node_;
    }

    bool operator!=(const ListIteratorBase &other) const {
      return !(*this == other);
    }

    T &operator*() const { return node_->data; }

    T *operator->() const { return &node_->data; }

    ListIteratorBase &operator++() {
      node_ = node_->next;
      return *this;
    }

    ListIteratorBase operator++(int) {
      ListIteratorBase tmp(*this);
      ++(*this);
      return tmp;
    }

    ListIteratorBase &operator--() {
      node_ = node_->prev;
      return *this;
    }

    ListIteratorBase operator--(int) {
      ListIteratorBase tmp(*this);
      --(*this);
      return tmp;
    }

    ListIteratorBase &operator+=(difference_type n) {
      while (n > 0) {
        ++(*this);
        --n;
      }
      while (n < 0) {
        --(*this);
        ++n;
      }
      return *this;
    }

    ListIteratorBase operator+(difference_type n) const {
      ListIteratorBase tmp(*this);
      return tmp += n;
    }

    ListIteratorBase &operator-=(difference_type n) { return (*this) += -n; }

    ListIteratorBase operator-(difference_type n) const {
      ListIteratorBase tmp(*this);
      return tmp -= n;
    }

    difference_type operator-(const ListIteratorBase &other) const {
      difference_type count = 0;
      ListIteratorBase tmp(*this);
      while (tmp != other) {
        --tmp;
        ++count;
      }
      return count;
    }

    T &operator[](difference_type n) const {
      ListIteratorBase tmp(*this);
      tmp += n;
      return *tmp;
    }

    Node *node() const { return node_; }

   private:
    Node *node_;
  };

  class ListIterator : public ListIteratorBase {
   public:
    using list::ListIteratorBase::ListIteratorBase;
  };

  class ListConstIterator : public ListIteratorBase {
   public:
    using list::ListIteratorBase::ListIteratorBase;
  };

  using iterator = ListIterator;
  using const_iterator = ListConstIterator;

  list()
      : head_(nullptr),
        tail_(nullptr),
        wandering_sentine_(new Node),
        size_(0) {}

  list(std::size_t n) : list() {
    for (std::size_t i = 0; i < n; i++) {
      push_back(T());
    }
  }

  list(std::initializer_list<T> const &items) : list() {
    for (auto iterator = items.begin(); iterator != items.end(); iterator++)
      push_back(*iterator);
  }

  list(const list &other) : list() { copy(other); }

  list(list &&other) : list() { copy(other); }

  ~list() {
    clear();

    delete wandering_sentine_;
    wandering_sentine_ = nullptr;

    head_ = nullptr;
    tail_ = nullptr;
  }

  list &operator=(const list &other) {
    copy(other);
    return *this;
  }

  ListIterator begin() { return ListIterator(head_); }

  ListConstIterator begin() const { return ListConstIterator(head_); }

  ListIterator end() { return ListIterator(wandering_sentine_); }

  ListConstIterator end() const {
    return ListConstIterator(wandering_sentine_);
  }

  const T &front() const {
    return (head_ != nullptr) ? head_->data : wandering_sentine_->data;
  }

  const T &back() const {
    return (tail_ != nullptr) ? tail_->data : wandering_sentine_->data;
  }

  void splice(ListIterator position, list &other) {
    for (auto &item : other) insert(position, item);
  }

  void reverse() {
    list reversedList;
    for (auto it = end(); it != begin();) {
      --it;
      reversedList.push_back(*it);
    }
    *this = std::move(reversedList);
  }

  void unique() {
    auto iterator = begin();
    while (iterator != end()) {
      auto it_next = iterator;
      if (++it_next != end() && *iterator == *it_next)
        erase(it_next);
      else
        ++iterator;
    }
  }

  void pop_back() {
    if (empty()) {
      throw std::out_of_range("empty");
    }
    ListIterator iterator = end();
    --iterator;
    erase(iterator);
  }

  void pop_front() {
    if (this->empty()) {
      throw std::out_of_range("empty");
    }
    erase(begin());
  }

  void push_front(const T &value) {
    head_ = new Node(value, head_, nullptr);
    if (head_->next) head_->next->prev = head_;
    if (!tail_) tail_ = head_;
    size_++;
    InitializeFakeNode();
  }

  void push_back(const T &value) {
    tail_ = (tail_ ? tail_->next : head_) = new Node(value, nullptr, tail_);
    size_++;
    InitializeFakeNode();
  }

  bool empty() const { return (head_ == nullptr); }

  std::size_t size() const { return size_; }

  std::size_t max_size() const { return alloc_.max_size(); }

  ListIterator insert(ListIterator position, const T &value) {
    if (position == begin()) {
      push_front(value);
      return begin();
    } else if (position == end()) {
      push_back(value);
      auto tmp = end();
      --tmp;
      return tmp;
    } else {
      Node *node_pos = new Node{value, position.node(), position.node()->prev};
      position.node()->prev->next = node_pos;
      position.node()->prev = node_pos;
      size_++;
      return ListIterator(node_pos);
    }
  }

  void erase(ListIterator position) {
    if (size_ == 0)
      throw std::out_of_range("Trying to erase from an empty list");

    Node *node = position.node();
    Node *node_next = node->next;
    Node *node_back = node->prev;

    if (size_ > 1) {
      if (node_next != wandering_sentine_) node_next->prev = node_back;
      if (node_back != wandering_sentine_) node_back->next = node_next;
    }

    if (position == begin()) head_ = node_next;
    if (position == --end()) tail_ = node_back;

    size_--;

    delete node;
    InitializeFakeNode();
  }

  void swap(list &other) {
    std::swap(head_, other.head_);
    std::swap(tail_, other.tail_);
    std::swap(wandering_sentine_, other.wandering_sentine_);
    std::swap(size_, other.size_);
    std::swap(alloc_, other.alloc_);
    InitializeFakeNode();
    other.InitializeFakeNode();
  }

  void merge(list &other) {
    ListIterator itThis = begin();
    T prevValue = other.front();
    for (auto itOther = other.begin(); itOther != other.end();
         prevValue = *itOther) {
      if (*itOther < prevValue || *itThis > *itOther) {
        insert(itThis, *itOther++);
      } else {
        ++itThis;
      }
    }
  }

  void copy(const list &other) {
    if (other.size_ != 0) {
      for (auto iter = other.begin(); iter != other.end(); ++iter) {
        push_back(*iter);
      }
    }
  }

  void ClearNode(Node *node) {
    if (!std::is_pointer<T>::value) {
      node->data.~T();
    }
  }
  void clear() {
    ListIterator b = begin();
    while (b != end()) {
      ListIterator pre = b;
      ++b;
      ClearNode(pre.node());
      delete pre.node();
    }

    head_ = nullptr;
    tail_ = nullptr;
    size_ = 0;

    InitializeFakeNode();
  }

  template <class... Args>
  ListIterator Emplace(ListConstIterator position, Args &&...args) {
    ListIterator iterator(const_cast<Node *>(position.base()));
    return insert(iterator, T(std::forward<Args>(args)...));
  }

  template <class... Args>
  void EmplaceBack(Args &&...args) {
    push_back(T(std::forward<Args>(args)...));
  }

  template <class... Args>
  void EmplaceFront(Args &&...args) {
    push_front(T(std::forward<Args>(args)...));
  }

  void sort() {
    if (size_ > 1) {
      for (auto i = begin(); i != end(); ++i) {
        for (auto j = begin(); j != end(); ++j) {
          if (*i < *j) {
            std::swap(*i, *j);
          }
        }
      }
    }
  }

 private:
  Node *head_;
  Node *tail_;
  Node *wandering_sentine_;
  std::size_t size_;
  typename std::allocator<T>::template rebind<Node>::other alloc_;

  void InitializeFakeNode() {
    if (head_ != nullptr && tail_ != nullptr) {
      head_->prev = wandering_sentine_;
      tail_->next = wandering_sentine_;
      wandering_sentine_->prev = tail_;
      wandering_sentine_->next = head_;
    } else {
      wandering_sentine_->prev = wandering_sentine_;
      wandering_sentine_->next = wandering_sentine_;
    }
  }
};
}  // namespace s21

#endif  // CPP2_S21_CONTAINERS_SRC_LIST_S21_LIST_H_