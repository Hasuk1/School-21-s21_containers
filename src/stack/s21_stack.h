#ifndef CPP2_S21_CONTAINERS_SRC_STACK_S21_STACK_H_
#define CPP2_S21_CONTAINERS_SRC_STACK_S21_STACK_H_

namespace s21 {

template <class T>
class stack {
 public:
  struct Node {
    T data;
    Node* next = nullptr;
  };

  class StackIterator {
   public:
    explicit StackIterator(Node* node) : current_(node) {}

    T& operator*() { return current_->data; }

    StackIterator& operator++() {
      current_ = current_->next;
      return *this;
    }

    StackIterator operator++(int) {
      StackIterator temp = *this;
      ++(*this);
      return temp;
    }

    bool operator==(const StackIterator& other) const {
      return current_ == other.current_;
    }

    bool operator!=(const StackIterator& other) const {
      return !(*this == other);
    }

   private:
    Node* current_;
  };

  class StackConstIterator {
   public:
    explicit StackConstIterator(const Node* node) : current_(node) {}

    const T& operator*() const { return current_->data; }

    StackConstIterator& operator++() {
      current_ = current_->next;
      return *this;
    }

    StackConstIterator operator++(int) {
      StackConstIterator temp = *this;
      ++(*this);
      return temp;
    }

    bool operator==(const StackConstIterator& other) const {
      return current_ == other.current_;
    }

    bool operator!=(const StackConstIterator& other) const {
      return !(*this == other);
    }

   private:
    const Node* current_;
  };
  using iterator = s21::stack<T>::StackIterator;
  using const_iterator = s21::stack<T>::StackConstIterator;

  stack() = default;

  stack(const stack& other) : stack() { Copy(other); }

  stack(stack&& other) noexcept : stack() { Swap(other); }

  ~stack() { clear(); }

  stack<T>& operator=(const stack& other) {
    if (this != &other) {
      clear();
      Copy(other);
    }
    return *this;
  }
  iterator begin() { return iterator(head_); }

  iterator end() { return iterator(nullptr); }

  StackConstIterator begin() const { return StackConstIterator(head_); }

  StackConstIterator end() const { return StackConstIterator(nullptr); }

  StackConstIterator cbegin() const { return StackConstIterator(head_); }

  StackConstIterator cend() const { return StackConstIterator(nullptr); }

  const T& Top() const {
    if (Empty()) {
      throw std::out_of_range("Error: Stack is Empty");
    }
    return head_->data;
  }

  bool Empty() const { return size_ == 0; }

  size_t Size() const { return size_; }

  void Push(const T& value) {
    Node* node = new Node{value};
    node->next = head_;
    head_ = node;
    size_++;
  }

  void Pop() {
    if (Empty()) {
      throw std::out_of_range("Error: Stack is Empty");
    }
    Node* node = head_->next;
    delete head_;
    head_ = node;
    size_--;
  }

  void Swap(stack& other) {
    using std::swap;
    swap(head_, other.head_);
    swap(size_, other.size_);
  }

  template <class... Args>
  void Emplace(Args&&... args) {
    Push(T(std::forward<Args>(args)...));
  }

  void clear() {
    while (!Empty()) {
      Pop();
    }
  }

  void Copy(const stack& other) {
    clear();
    Node* node = other.head_;
    stack temp_stack;
    while (node) {
      temp_stack.Push(node->data);
      node = node->next;
    }
    while (!temp_stack.Empty()) {
      Push(temp_stack.Top());
      temp_stack.Pop();
    }
  }

 private:
  Node* head_ = nullptr;
  size_t size_ = 0;
};

}  // namespace s21

#endif  // CPP2_S21_CONTAINERS_SRC_STACK_S21_STACK_H_
