#ifndef CPP2_S21_CONTAINERS_SRC_queue_S21_queue_H_
#define CPP2_S21_CONTAINERS_SRC_queue_S21_queue_H_

namespace s21 {

template <class T>
class queue {
 public:
  struct Node {
    T data;
    Node *next = nullptr;

    Node(T value) : data(std::move(value)) {}
  };

  class QueueIterator {
   public:
    explicit QueueIterator(Node *node) : current_(node) {}

    T &operator*() { return current_->data; }

    QueueIterator &operator++() {
      current_ = current_->next;
      return *this;
    }

    QueueIterator operator++(int) {
      QueueIterator temp = *this;
      ++(*this);
      return temp;
    }

    bool operator==(const QueueIterator &other) const {
      return current_ == other.current_;
    }

    bool operator!=(const QueueIterator &other) const {
      return !(*this == other);
    }

   private:
    Node *current_;
  };

  class QueueConstIterator {
   public:
    explicit QueueConstIterator(const Node *node) : current_(node) {}

    const T &operator*() const { return current_->data; }

    QueueConstIterator &operator++() {
      current_ = current_->next;
      return *this;
    }

    QueueConstIterator operator++(int) {
      QueueConstIterator temp = *this;
      ++(*this);
      return temp;
    }

    bool operator==(const QueueConstIterator &other) const {
      return current_ == other.current_;
    }

    bool operator!=(const QueueConstIterator &other) const {
      return !(*this == other);
    }

   private:
    const Node *current_;
  };
  using iterator = s21::queue<T>::QueueIterator;
  using const_iterator = s21::queue<T>::QueueConstIterator;
  queue() = default;

  queue(std::initializer_list<T> items) {
    for (const auto &item : items) {
      push(item);
    }
  }

  queue(const queue &other) : queue() { copy(other); }

  queue(queue &&other) noexcept : queue() { swap(other); }

  ~queue() { clear(); }

  queue<T> &operator=(const queue &other) {
    if (this != &other) {
      queue temp(other);
      swap(temp);
    }
    return *this;
  }

  iterator begin() { return iterator(head_); }

  iterator end() { return iterator(nullptr); }

  QueueConstIterator begin() const { return QueueConstIterator(head_); }

  QueueConstIterator end() const { return QueueConstIterator(nullptr); }

  QueueConstIterator cbegin() const { return QueueConstIterator(head_); }

  QueueConstIterator cend() const { return QueueConstIterator(nullptr); }

  const T &front() const {
    if (empty()) {
      throw std::out_of_range("Error: queue is empty");
    }
    return head_->data;
  }

  const T &back() const {
    if (empty()) {
      throw std::out_of_range("Error: queue is empty");
    }
    return tail_->data;
  }

  bool empty() const { return size_ == 0; }

  size_t size() const { return size_; }

  void push(const T &value) {
    Node *node = new Node(value);
    if (!head_) {
      head_ = node;
      tail_ = node;
    } else {
      tail_->next = node;
      tail_ = node;
    }
    size_++;
  }

  void pop() {
    if (head_) {
      Node *node = head_->next;
      delete head_;
      head_ = node;
      size_--;
      if (size_ < 2) {
        tail_ = node;
      }
    }
  }

  void swap(queue &other) {
    using std::swap;
    swap(head_, other.head_);
    swap(tail_, other.tail_);
    swap(size_, other.size_);
  }

  template <class... Args>
  void EmplaceBack(Args &&...args) {
    push(T(std::forward<Args>(args)...));
  }

  void clear() {
    while (!empty()) {
      pop();
    }
  }

  void copy(const queue &other) {
    clear();
    Node *node = other.head_;
    while (node) {
      push(node->data);
      node = node->next;
    }
  }

 private:
  Node *head_ = nullptr;
  Node *tail_ = nullptr;
  size_t size_ = 0;
};

}  // namespace s21

#endif  // CPP2_S21_CONTAINERS_SRC_queue_S21_queue_H_
