#include <list>
#include <stack>

namespace s21 {

template <typename Key, typename Value>
RedBlackTree<Key, Value>::RedBlackTree()
    : head_(new RedBlackTreeNode), size_(0U) {}

template <typename Key, typename Value>
RedBlackTree<Key, Value>::RedBlackTree(const RedBlackTree &other)
    : RedBlackTree() {
  if (other.Size() > 0) CopyTreeFromOther(other);
}

template <typename Key, typename Value>
RedBlackTree<Key, Value>::RedBlackTree(RedBlackTree &&other) noexcept
    : RedBlackTree() {
  if (this != &other) Swap(other);
}

template <typename Key, typename Value>
typename RedBlackTree<Key, Value>::RedBlackTree &
RedBlackTree<Key, Value>::operator=(const RedBlackTree &other) {
  if (this != &other) {
    Clear();
    if (other.Size() > 0) CopyTreeFromOther(other);
  }
  return *this;
}

template <typename Key, typename Value>
typename RedBlackTree<Key, Value>::RedBlackTree &
RedBlackTree<Key, Value>::operator=(RedBlackTree &&other) noexcept {
  Clear();
  Swap(other);
  return *this;
}

template <typename Key, typename Value>
RedBlackTree<Key, Value>::~RedBlackTree() {
  Clear();
  delete head_;
  head_ = nullptr;
}

template <typename Key, typename Value>
void RedBlackTree<Key, Value>::Clear() {
  Destroy(head_->parent_);
  InitializeHead();
  size_ = 0;
}

template <typename Key, typename Value>
typename RedBlackTree<Key, Value>::size_type RedBlackTree<Key, Value>::Size()
    const noexcept {
  return size_;
}

template <typename Key, typename Value>
bool RedBlackTree<Key, Value>::isEmpty() const noexcept {
  return size_ == 0;
}

template <typename Key, typename Value>
typename RedBlackTree<Key, Value>::size_type RedBlackTree<Key, Value>::MaxSize()
    const noexcept {
  std::size_t s = sizeof(RedBlackTree);
  return ((std::numeric_limits<size_type>::max() / 2) - (s * 2)) / s;
}

template <typename Key, typename Value>
typename RedBlackTree<Key, Value>::iterator
RedBlackTree<Key, Value>::Begin() noexcept {
  return iterator(head_->left_);
}

template <typename Key, typename Value>
typename RedBlackTree<Key, Value>::const_iterator
RedBlackTree<Key, Value>::Begin() const noexcept {
  return const_iterator(head_->left_);
}

template <typename Key, typename Value>
typename RedBlackTree<Key, Value>::iterator
RedBlackTree<Key, Value>::End() noexcept {
  return iterator(head_);
}

template <typename Key, typename Value>
typename RedBlackTree<Key, Value>::const_iterator
RedBlackTree<Key, Value>::End() const noexcept {
  return const_iterator(head_);
}

template <typename Key, typename Value>
void RedBlackTree<Key, Value>::Merge(RedBlackTree &other) {
  if (this != &other) {
    if (other.isEmpty()) return;
    if (this->isEmpty()) {
      *this = std::move(other);
      return;
    }
    for (auto it = other.Begin(); it != other.End(); ++it) this->Insert(*it);
    other.Clear();
  }
}

template <typename Key, typename Value>
void RedBlackTree<Key, Value>::MergeUnique(RedBlackTree &other) {
  if (this != &other) {
    iterator other_iter = other.Begin();
    const iterator other_end = other.End();
    while (other_iter != other_end) {
      const Key &current_key = other_iter.node_->key_;
      iterator found_iter = Find(current_key);
      if (found_iter == End()) {
        iterator tmp = other_iter;
        ++other_iter;
        RedBlackTreeNode *moving_node = other.ExtractNode(tmp);
        Insert(head_->parent_, moving_node, false);
      } else
        ++other_iter;
    }
    other.Clear();
  }
}

template <typename Key, typename Value>
typename RedBlackTree<Key, Value>::iterator RedBlackTree<Key, Value>::Insert(
    const key_type &key) {
  RedBlackTreeNode *newNode = new RedBlackTreeNode{key};
  return Insert(head_->parent_, newNode, false).first;
}

template <typename Key, typename Value>
std::pair<typename RedBlackTree<Key, Value>::iterator, bool>
RedBlackTree<Key, Value>::InsertUnique(const key_type &key) {
  iterator it = Find(key);
  if (it != End()) {
    return {it, false};
  }
  RedBlackTreeNode *newNode = new RedBlackTreeNode{key};
  std::pair<iterator, bool> result = Insert(head_->parent_, newNode, true);
  return result;
}

template <typename Key, typename Value>
template <typename... Args>
std::vector<std::pair<typename RedBlackTree<Key, Value>::iterator, bool>>
RedBlackTree<Key, Value>::Emplace(Args &&...args) {
  std::vector<std::pair<iterator, bool>> insertion_results;
  insertion_results.reserve(sizeof...(args));
  auto emplaceItem = [&](auto &&item) {
    RedBlackTreeNode *newNode =
        new RedBlackTreeNode(std::forward<decltype(item)>(item));
    std::pair<iterator, bool> insertion_result =
        Insert(head_->parent_, newNode, false);
    insertion_results.push_back(insertion_result);
  };
  (emplaceItem(std::forward<Args>(args)), ...);
  return insertion_results;
}

template <typename Key, typename Value>
template <typename... Args>
std::vector<std::pair<typename RedBlackTree<Key, Value>::iterator, bool>>
RedBlackTree<Key, Value>::EmplaceUnique(Args &&...args) {
  std::vector<std::pair<iterator, bool>> insertion_results;
  insertion_results.reserve(sizeof...(args));
  auto emplaceUniqueItem = [&](auto &&item) {
    RedBlackTreeNode *newNode =
        new RedBlackTreeNode(std::forward<decltype(item)>(item));
    std::pair<iterator, bool> insertion_result =
        Insert(head_->parent_, newNode, true);
    if (!insertion_result.second) {
      delete newNode;
    }
    insertion_results.push_back(insertion_result);
  };
  (emplaceUniqueItem(std::forward<Args>(args)), ...);
  return insertion_results;
}

template <typename Key, typename Value>
typename RedBlackTree<Key, Value>::iterator RedBlackTree<Key, Value>::Find(
    const_reference key) {
  RedBlackTreeNode *current_node = head_->parent_;
  while (current_node) {
    if (key_comparator_(key, current_node->key_)) {
      current_node = current_node->left_;
    } else if (key_comparator_(current_node->key_, key)) {
      current_node = current_node->right_;
    } else {
      return iterator(current_node);
    }
  }
  return End();
}

template <typename Key, typename Value>
typename RedBlackTree<Key, Value>::iterator
RedBlackTree<Key, Value>::LowerBound(const_reference key) {
  RedBlackTreeNode *current_node = head_->parent_;
  RedBlackTreeNode *result_node = End().node_;
  while (current_node) {
    if (!key_comparator_(current_node->key_, key)) {
      result_node = current_node;
      current_node = current_node->left_;
    } else {
      current_node = current_node->right_;
    }
  }
  return iterator(result_node);
}

template <typename Key, typename Value>
typename RedBlackTree<Key, Value>::iterator
RedBlackTree<Key, Value>::UpperBound(const_reference key) {
  RedBlackTreeNode *current_node = head_->parent_;
  RedBlackTreeNode *result_node = End().node_;
  while (current_node) {
    if (key_comparator_(key, current_node->key_)) {
      result_node = current_node;
      current_node = current_node->left_;
    } else
      current_node = current_node->right_;
  }
  return iterator(result_node);
}

template <typename Key, typename Value>
void RedBlackTree<Key, Value>::Erase(iterator position) {
  RedBlackTreeNode *result = ExtractNode(position);
  delete result;
}

template <typename Key, typename Value>
void RedBlackTree<Key, Value>::Swap(RedBlackTree &other) noexcept {
  std::swap(head_, other.head_);
  std::swap(size_, other.size_);
  std::swap(key_comparator_, other.key_comparator_);
}

template <typename Key, typename Value>
bool RedBlackTree<Key, Value>::isBlack(const RedBlackTreeNode *node) const {
  return node != nullptr && node->color_ == kBlack;
}

template <typename Key, typename Value>
bool RedBlackTree<Key, Value>::isRed(const RedBlackTreeNode *node) const {
  return node != nullptr && node->color_ == kRed;
}

template <typename Key, typename Value>
void RedBlackTree<Key, Value>::CopyTreeFromOther(const RedBlackTree &other) {
  Clear();
  head_->parent_ = CopyTree(other.head_->parent_, nullptr);
  head_->parent_->parent_ = head_;
  RedBlackTreeNode *node = head_->parent_;
  while (node->left_) node = node->left_;
  head_->left_ = node;
  node = head_->parent_;
  while (node->right_) node = node->right_;
  head_->right_ = node;
  size_ = other.size_;
  key_comparator_ = other.key_comparator_;
}

template <typename Key, typename Value>
typename RedBlackTree<Key, Value>::RedBlackTreeNode *
RedBlackTree<Key, Value>::CopyTree(const RedBlackTreeNode *source_node,
                                   RedBlackTreeNode *new_parent) {
  if (!source_node) return nullptr;
  std::stack<std::pair<const RedBlackTreeNode *, RedBlackTreeNode **>>
      node_stack;
  RedBlackTreeNode *new_subtree_root = nullptr;
  node_stack.push({source_node, &new_subtree_root});
  while (!node_stack.empty()) {
    auto [current_source_node, new_node_ptr] = node_stack.top();
    node_stack.pop();
    if (current_source_node) {
      *new_node_ptr = new RedBlackTreeNode{current_source_node->key_,
                                           current_source_node->color_};
      (*new_node_ptr)->parent_ = new_parent;
      node_stack.push({current_source_node->right_, &(*new_node_ptr)->right_});
      node_stack.push({current_source_node->left_, &(*new_node_ptr)->left_});
    }
  }
  return new_subtree_root;
}

template <typename Key, typename Value>
void RedBlackTree<Key, Value>::Destroy(RedBlackTreeNode *node) noexcept {
  std::stack<RedBlackTreeNode *> nodes;
  while (node != nullptr || !nodes.empty()) {
    if (node != nullptr) {
      nodes.push(node);
      node = node->left_;
    } else {
      node = nodes.top();
      nodes.pop();
      RedBlackTreeNode *right_child = node->right_;
      delete node;
      node = right_child;
    }
  }
}

template <typename Key, typename Value>
void RedBlackTree<Key, Value>::InitializeHead() {
  if (!head_) head_ = new RedBlackTreeNode();
  head_->parent_ = nullptr;
  head_->left_ = head_;
  head_->right_ = head_;
}

template <typename KeyType, typename Compare>
std::pair<typename RedBlackTree<KeyType, Compare>::iterator, bool>
RedBlackTree<KeyType, Compare>::Insert(RedBlackTreeNode *root,
                                       RedBlackTreeNode *newNnode,
                                       bool check_duplicates) {
  RedBlackTreeNode *parent = head_;
  RedBlackTreeNode **node = &root;
  while (*node != nullptr) {
    parent = *node;
    bool is_less = key_comparator_(newNnode->key_, (*node)->key_);
    if (is_less) {
      node = &(*node)->left_;
    } else {
      if (check_duplicates && !key_comparator_((*node)->key_, newNnode->key_)) {
        return {iterator(*node), false};
      }
      node = &(*node)->right_;
    }
  }
  newNnode->parent_ = parent;
  *node = newNnode;
  if (parent == head_ || parent == nullptr) {
    newNnode->color_ = kBlack;
    head_->parent_ = newNnode;
    head_->left_ = newNnode;
    head_->right_ = newNnode;
  } else {
    if (key_comparator_(newNnode->key_, head_->left_->key_)) {
      head_->left_ = newNnode;
    }
    if (!key_comparator_(newNnode->key_, head_->right_->key_)) {
      head_->right_ = newNnode;
    }
  }
  ++size_;
  BalancingInsert(newNnode);
  return {iterator(newNnode), true};
}

template <typename KeyType, typename Compare>
void RedBlackTree<KeyType, Compare>::BalancingInsert(RedBlackTreeNode *node) {
  while (node != head_->parent_ && isRed(node->parent_)) {
    if (node->parent_->parent_->left_ == node->parent_) {
      HandleLeftCase(node);
    } else {
      HandleRightCase(node);
    }
  }
  head_->parent_->color_ = kBlack;
}

template <typename KeyType, typename Compare>
void RedBlackTree<KeyType, Compare>::HandleLeftCase(RedBlackTreeNode *node) {
  RedBlackTreeNode *parent = node->parent_;
  RedBlackTreeNode *gparent = parent->parent_;
  RedBlackTreeNode *uncle = gparent->right_;
  if (uncle != nullptr && isRed(uncle)) {
    HandleRedUncle(parent, uncle, gparent);
  } else {
    if (parent->right_ == node) {
      RotateLeft(parent);
      std::swap(parent, node);
    }
    RotateRight(gparent);
    std::swap(parent->color_, gparent->color_);
  }
}

template <typename KeyType, typename Compare>
void RedBlackTree<KeyType, Compare>::HandleRightCase(RedBlackTreeNode *node) {
  RedBlackTreeNode *parent = node->parent_;
  RedBlackTreeNode *gparent = parent->parent_;
  RedBlackTreeNode *uncle = gparent->left_;

  if (uncle != nullptr && isRed(uncle)) {
    HandleRedUncle(parent, uncle, gparent);
  } else {
    if (parent->left_ == node) {
      RotateRight(parent);
      std::swap(parent, node);
    }
    RotateLeft(gparent);
    std::swap(parent->color_, gparent->color_);
  }
}

template <typename KeyType, typename Compare>
void RedBlackTree<KeyType, Compare>::HandleRedUncle(RedBlackTreeNode *parent,
                                                    RedBlackTreeNode *uncle,
                                                    RedBlackTreeNode *gparent) {
  parent->color_ = kBlack;
  uncle->color_ = kBlack;
  gparent->color_ = kRed;
}

template <typename KeyType, typename Value>
void RedBlackTree<KeyType, Value>::Rotate(RedBlackTreeNode *node,
                                          bool rotateRight) noexcept {
  RedBlackTreeNode *pivot = rotateRight ? node->left_ : node->right_;
  RedBlackTreeNode *parentBeforeRotation = node->parent_;
  if (node == head_->parent_) {
    head_->parent_ = pivot;
  } else if (parentBeforeRotation->left_ == node) {
    parentBeforeRotation->left_ = pivot;
  } else
    parentBeforeRotation->right_ = pivot;
  pivot->parent_ = parentBeforeRotation;
  if (rotateRight) {
    node->left_ = pivot->right_;
    if (pivot->right_ != nullptr) pivot->right_->parent_ = node;
    pivot->right_ = node;
  } else {
    node->right_ = pivot->left_;
    if (pivot->left_ != nullptr) pivot->left_->parent_ = node;
    pivot->left_ = node;
  }
  node->parent_ = pivot;
}

template <typename KeyType, typename Value>
void RedBlackTree<KeyType, Value>::RotateRight(
    RedBlackTreeNode *node) noexcept {
  Rotate(node, true);
}

template <typename KeyType, typename Value>
void RedBlackTree<KeyType, Value>::RotateLeft(RedBlackTreeNode *node) noexcept {
  Rotate(node, false);
}

template <typename Key, typename Value>
typename RedBlackTree<Key, Value>::RedBlackTreeNode *
RedBlackTree<Key, Value>::ExtractNode(iterator position) {
  if (position == End()) return nullptr;
  RedBlackTreeNode *deleted_node = position.node_;
  HandleDeletionCases(deleted_node);
  UpdateParentAndHeadLinks(deleted_node);
  --size_;
  deleted_node->ToDefault();
  return deleted_node;
}

template <typename Key, typename Value>
void RedBlackTree<Key, Value>::HandleDeletionCases(
    RedBlackTreeNode *deleted_node) {
  if (deleted_node->left_ != nullptr && deleted_node->right_ != nullptr) {
    HandleK2Case(deleted_node);
  } else if (isBlack(deleted_node))
    HandleBlackCases(deleted_node);
}

template <typename Key, typename Value>
void RedBlackTree<Key, Value>::UpdateParentAndHeadLinks(
    RedBlackTreeNode *deleted_node) {
  if (deleted_node == head_->parent_) {
    InitializeHead();
  } else {
    RedBlackTreeNode *parent = deleted_node->parent_;
    if (deleted_node == parent->left_)
      parent->left_ = nullptr;
    else
      parent->right_ = nullptr;
    if (head_->left_ == deleted_node)
      head_->left_ = SearchMinimum(head_->parent_);
    if (head_->right_ == deleted_node)
      head_->right_ = SearchMaximum(head_->parent_);
  }
}

template <typename Key, typename Value>
void RedBlackTree<Key, Value>::HandleK2Case(RedBlackTreeNode *deleted_node) {
  RedBlackTreeNode *replacement_node = SearchMinimum(deleted_node->right_);
  SwapNodesAndUpdateAfterErase(deleted_node, replacement_node);
}

template <typename Key, typename Value>
void RedBlackTree<Key, Value>::HandleBlackCases(
    RedBlackTreeNode *deleted_node) {
  if ((deleted_node->left_ != nullptr && deleted_node->right_ == nullptr) ||
      (deleted_node->left_ == nullptr && deleted_node->right_ != nullptr)) {
    RedBlackTreeNode *replacement =
        deleted_node->left_ ? deleted_node->left_ : deleted_node->right_;
    SwapNodesAndUpdateAfterErase(deleted_node, replacement);
  } else if (!deleted_node->left_ && !deleted_node->right_) {
    EraseBalancing(deleted_node);
  }
}

template <typename KeyType, typename Value>
void RedBlackTree<KeyType, Value>::SwapNodes(
    RedBlackTreeNode *node_a, RedBlackTreeNode *node_b) noexcept {
  std::swap(node_a->parent_, node_b->parent_);
  std::swap(node_a->left_, node_b->left_);
  std::swap(node_a->right_, node_b->right_);
  std::swap(node_a->color_, node_b->color_);
}

template <typename KeyType, typename Value>
void RedBlackTree<KeyType, Value>::UpdateParent(
    RedBlackTreeNode *node, RedBlackTreeNode *newNode) noexcept {
  if (node->parent_->left_ == node)
    node->parent_->left_ = newNode;
  else
    node->parent_->right_ = newNode;
}

template <typename KeyType, typename Value>
void RedBlackTree<KeyType, Value>::SwapNodesAndUpdateAfterErase(
    RedBlackTreeNode *node, RedBlackTreeNode *survivor) noexcept {
  if (node == survivor) return;
  UpdateParent(node, survivor);
  UpdateParent(survivor, node);
  if (node == head_->parent_) head_->parent_ = survivor;
  SwapNodes(node, survivor);
  if (node->left_) node->left_->parent_ = node;
  if (node->right_) node->right_->parent_ = node;
  if (survivor->left_) survivor->left_->parent_ = survivor;
  if (survivor->right_) survivor->right_->parent_ = survivor;
}

template <typename KeyType, typename Value>
void RedBlackTree<KeyType, Value>::HandleRedSibling(
    RedBlackTreeNode *parent, RedBlackTreeNode *&check_node) {
  RedBlackTreeNode *sibling =
      (check_node == parent->left_) ? parent->right_ : parent->left_;
  std::swap(sibling->color_, parent->color_);
  if (check_node == parent->left_)
    RotateLeft(parent);
  else
    RotateRight(parent);
  parent = check_node->parent_;
}

template <typename KeyType, typename Value>
void RedBlackTree<KeyType, Value>::HandleBlackSiblingWithBlackChildren(
    RedBlackTreeNode *parent, RedBlackTreeNode *&check_node) {
  RedBlackTreeNode *sibling =
      (check_node == parent->left_) ? parent->right_ : parent->left_;
  sibling->color_ = kRed;
  if (isRed(parent)) {
    parent->color_ = kBlack;
    return;
  }
  check_node = parent;
  parent = check_node->parent_;
}

template <typename KeyType, typename Value>
void RedBlackTree<KeyType, Value>::HandleBlackSiblingWithRedChild(
    RedBlackTreeNode *parent, RedBlackTreeNode *&check_node) {
  RedBlackTreeNode *sibling =
      (check_node == parent->left_) ? parent->right_ : parent->left_;
  if (check_node == parent->left_ && sibling->left_ != nullptr &&
      isRed(sibling->left_) &&
      (sibling->right_ == nullptr || isBlack(sibling->right_))) {
    std::swap(sibling->color_, sibling->left_->color_);
    RotateRight(sibling);
    sibling = parent->right_;
  } else if (sibling->right_ != nullptr && isRed(sibling->right_) &&
             (sibling->left_ == nullptr || isBlack(sibling->left_))) {
    std::swap(sibling->color_, sibling->right_->color_);
    RotateLeft(sibling);
    sibling = parent->left_;
  }
  sibling->left_->color_ = kBlack;
  sibling->color_ = parent->color_;
  parent->color_ = kBlack;
  if (check_node == parent->left_)
    RotateLeft(parent);
  else
    RotateRight(parent);
}

template <typename KeyType, typename Value>
void RedBlackTree<KeyType, Value>::EraseBalancing(
    RedBlackTreeNode *deleted_node) noexcept {
  RedBlackTreeNode *node_to_check = deleted_node;
  RedBlackTreeNode *parent_node = deleted_node->parent_;
  while (node_to_check != head_->parent_ && isBlack(node_to_check)) {
    if (node_to_check == parent_node->left_ ||
        node_to_check == parent_node->right_) {
      RedBlackTreeNode *sibling_node = (node_to_check == parent_node->left_)
                                           ? parent_node->right_
                                           : parent_node->left_;
      if (isRed(sibling_node)) HandleRedSibling(parent_node, node_to_check);
      sibling_node = (node_to_check == parent_node->left_) ? parent_node->right_
                                                           : parent_node->left_;
      if (isBlack(sibling_node) &&
          (!sibling_node->left_ || isBlack(sibling_node->left_)) &&
          (!sibling_node->right_ || isBlack(sibling_node->right_))) {
        HandleBlackSiblingWithBlackChildren(parent_node, node_to_check);
      } else {
        HandleBlackSiblingWithRedChild(parent_node, node_to_check);
        break;
      }
    }
  }
}

template <typename KeyType, typename Value>
typename RedBlackTree<KeyType, Value>::RedBlackTreeNode *
RedBlackTree<KeyType, Value>::GoLeft(
    typename RedBlackTree<KeyType, Value>::RedBlackTreeNode *node)
    const noexcept {
  return node->left_;
}

template <typename KeyType, typename Value>
typename RedBlackTree<KeyType, Value>::RedBlackTreeNode *
RedBlackTree<KeyType, Value>::GoRight(
    typename RedBlackTree<KeyType, Value>::RedBlackTreeNode *node)
    const noexcept {
  return node->right_;
}

template <typename KeyType, typename Value>
typename RedBlackTree<KeyType, Value>::RedBlackTreeNode *
RedBlackTree<KeyType, Value>::SearchMinimum(
    typename RedBlackTree<KeyType, Value>::RedBlackTreeNode *node)
    const noexcept {
  while (GoLeft(node) != nullptr) {
    node = GoLeft(node);
  };
  return node;
}

template <typename KeyType, typename Value>
typename RedBlackTree<KeyType, Value>::RedBlackTreeNode *
RedBlackTree<KeyType, Value>::SearchMaximum(
    typename RedBlackTree<KeyType, Value>::RedBlackTreeNode *node)
    const noexcept {
  while (GoRight(node) != nullptr) {
    node = GoRight(node);
  };
  return node;
}

template <typename KeyType, typename Compare>
int RedBlackTree<KeyType, Compare>::ComputeBlackHeight(
    const RedBlackTreeNode *node) const noexcept {
  if (!node) return 0;
  int left_height = ComputeBlackHeight(node->left_);
  int right_height = ComputeBlackHeight(node->right_);
  if (left_height == -1 || right_height == -1 || left_height != right_height)
    return -1;
  return left_height + (isBlack(node) ? 1 : 0);
}

template <typename KeyType, typename Compare>
bool RedBlackTree<KeyType, Compare>::isRedNodes(
    const RedBlackTreeNode *Node) const noexcept {
  if (!Node) return 0;
  if (isRed(Node)) {
    if ((!Node->left_ && isRed(Node->left_)) ||
        (!Node->right_ && isRed(Node->right_))) {
      return false;
    }
  }
  return isRedNodes(Node->left_) && isRedNodes(Node->right_);
}

template <typename KeyType, typename Compare>
struct RedBlackTree<KeyType, Compare>::RedBlackTreeNode {
  RedBlackTreeNode *parent_;
  RedBlackTreeNode *left_;
  RedBlackTreeNode *right_;
  key_type key_;
  Color color_;

  RedBlackTreeNode()
      : parent_(nullptr),
        left_(this),
        right_(this),
        key_(key_type{}),
        color_(kRed) {}

  explicit RedBlackTreeNode(const key_type &key)
      : parent_(nullptr),
        left_(nullptr),
        right_(nullptr),
        key_(key),
        color_(kRed) {}

  explicit RedBlackTreeNode(key_type &&key)
      : parent_(nullptr),
        left_(nullptr),
        right_(nullptr),
        key_(std::move(key)),
        color_(kRed) {}

  RedBlackTreeNode(key_type key, Color color)
      : parent_(nullptr),
        left_(nullptr),
        right_(nullptr),
        key_(key),
        color_(color) {}

  void ToDefault() noexcept {
    left_ = nullptr;
    right_ = nullptr;
    parent_ = nullptr;
    color_ = kRed;
  }

  RedBlackTreeNode *NextNode() const noexcept {
    auto *node = const_cast<RedBlackTreeNode *>(this);
    if (node->color_ == kRed &&
        (!node->parent_ || node->parent_->parent_ == node)) {
      node = node->left_;
    } else if (node->right_) {
      node = node->right_;
      while (node->left_) node = node->left_;
    } else {
      RedBlackTreeNode *parent = node->parent_;
      while (node == parent->right_) {
        node = parent;
        parent = parent->parent_;
      }
      if (node->right_ != parent) node = parent;
    }
    return node;
  }

  RedBlackTreeNode *PrevNode() const noexcept {
    RedBlackTreeNode *node = const_cast<RedBlackTreeNode *>(this);

    if (node->color_ == kRed &&
        (!node->parent_ || node->parent_->parent_ == node)) {
      node = node->right_;
    } else if (node->left_) {
      node = node->left_;
      while (node->right_) node = node->right_;
    } else {
      RedBlackTreeNode *parent = node->parent_;
      while (node == parent->left_) {
        node = parent;
        parent = parent->parent_;
      }
      if (node->left_ != parent) node = parent;
    }
    return node;
  }
};

template <typename KeyType, typename Compare>
struct RedBlackTree<KeyType, Compare>::RedBlackTreeIterator {
  using iterator_category = std::forward_iterator_tag;
  using difference_type = std::ptrdiff_t;
  using value_type = RedBlackTree::key_type;
  using pointer = value_type *;
  using reference = value_type &;

  RedBlackTreeIterator() = delete;
  explicit RedBlackTreeIterator(RedBlackTreeNode *node) : node_(node) {}
  reference operator*() const noexcept { return node_->key_; }
  iterator &operator++() noexcept {
    node_ = node_->NextNode();
    return *this;
  }

  iterator operator++(int) noexcept {
    iterator tmp{node_};
    ++(*this);
    return tmp;
  }

  iterator &operator--() noexcept {
    node_ = node_->PrevNode();
    return *this;
  }

  iterator operator--(int) noexcept {
    iterator tmp{node_};
    --(*this);
    return tmp;
  }

  bool operator==(const iterator &other) const noexcept {
    return node_ == other.node_;
  }

  bool operator!=(const iterator &other) const noexcept {
    return node_ != other.node_;
  }

  RedBlackTreeNode *node_;
};

template <typename KeyType, typename Compare>
struct RedBlackTree<KeyType, Compare>::RedBlackTreeIteratorConst {
  using iterator_category = std::forward_iterator_tag;
  using difference_type = std::ptrdiff_t;
  using value_type = RedBlackTree::key_type;
  using pointer = const value_type *;
  using reference = const value_type &;

  RedBlackTreeIteratorConst() = delete;
  explicit RedBlackTreeIteratorConst(const RedBlackTreeNode *node)
      : node_(node) {}
  RedBlackTreeIteratorConst(const iterator &it) : node_(it.node_) {}
  reference operator*() const noexcept { return node_->key_; }

  const_iterator &operator++() noexcept {
    node_ = node_->NextNode();
    return *this;
  }

  const_iterator operator++(int) noexcept {
    const_iterator tmp{node_};
    ++(*this);
    return tmp;
  }

  const_iterator &operator--() noexcept {
    node_ = node_->PrevNode();
    return *this;
  }

  const_iterator operator--(int) noexcept {
    const_iterator tmp{node_};
    --(*this);
    return tmp;
  }

  friend bool operator==(const const_iterator &it1,
                         const const_iterator &it2) noexcept {
    return it1.node_ == it2.node_;
  }

  friend bool operator!=(const const_iterator &it1,
                         const const_iterator &it2) noexcept {
    return it1.node_ != it2.node_;
  }

  const RedBlackTreeNode *node_;
};
}  // namespace s21