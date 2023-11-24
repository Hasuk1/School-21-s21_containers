#ifndef CPP2_S21_CONTAINERS_SRC_RB_TREE_RB_TREE_H_
#define CPP2_S21_CONTAINERS_SRC_RB_TREE_RB_TREE_H_

namespace s21 {
enum Color { kBlack, kRed };

template <typename Key, typename Value = std::less<Key>>
class RedBlackTree {
  struct RedBlackTreeNode;
  struct RedBlackTreeIterator;
  struct RedBlackTreeIteratorConst;

 public:
  using key_type = Key;
  using reference = key_type &;
  using const_reference = const key_type &;
  using iterator = RedBlackTreeIterator;
  using const_iterator = RedBlackTreeIteratorConst;
  using size_type = size_t;

  RedBlackTree();
  RedBlackTree(const RedBlackTree &other);
  RedBlackTree(RedBlackTree &&other) noexcept;
  RedBlackTree &operator=(const RedBlackTree &other);
  RedBlackTree &operator=(RedBlackTree &&other) noexcept;
  ~RedBlackTree();

  iterator Insert(const key_type &key);
  std::pair<iterator, bool> InsertUnique(const key_type &key);
  template <typename... Args>
  std::vector<std::pair<iterator, bool>> Emplace(Args &&...args);
  template <typename... Args>
  std::vector<std::pair<iterator, bool>> EmplaceUnique(Args &&...args);
  iterator Find(const_reference key);
  iterator LowerBound(const_reference key);
  iterator UpperBound(const_reference key);
  void Erase(iterator position);

  iterator Begin() noexcept;
  const_iterator Begin() const noexcept;
  iterator End() noexcept;
  const_iterator End() const noexcept;

  void Clear();
  size_type Size() const noexcept;
  bool isEmpty() const noexcept;
  size_type MaxSize() const noexcept;
  void Merge(RedBlackTree &other);
  void MergeUnique(RedBlackTree &other);
  void Swap(RedBlackTree &other) noexcept;

  bool isBlack(const RedBlackTreeNode *node) const;
  bool isRed(const RedBlackTreeNode *node) const;

 private:
  void HandleBlackCases(RedBlackTreeNode *deleted_node);
  void HandleK2Case(RedBlackTreeNode *deleted_node);
  void HandleDeletionCases(RedBlackTreeNode *deleted_node);
  void UpdateParentAndHeadLinks(RedBlackTreeNode *deleted_node);
  void CopyTreeFromOther(const RedBlackTree &other);
  RedBlackTreeNode *CopyTree(const RedBlackTreeNode *node,
                             RedBlackTreeNode *parent);
  void Destroy(RedBlackTreeNode *node) noexcept;
  void InitializeHead();
  void HandleLeftCase(RedBlackTreeNode *node);
  void HandleRightCase(RedBlackTreeNode *node);
  void HandleRedUncle(RedBlackTreeNode *parent, RedBlackTreeNode *uncle,
                      RedBlackTreeNode *gparent);
  void Rotate(RedBlackTreeNode *node, bool rotateRight) noexcept;
  std::pair<iterator, bool> Insert(RedBlackTreeNode *root,
                                   RedBlackTreeNode *newNnode,
                                   bool check_duplicates);
  void BalancingInsert(RedBlackTreeNode *node);
  void RotateRight(RedBlackTreeNode *node) noexcept;
  void RotateLeft(RedBlackTreeNode *node) noexcept;
  RedBlackTreeNode *ExtractNode(iterator position);
  void SwapNodes(RedBlackTreeNode *node_a, RedBlackTreeNode *node_b) noexcept;
  void UpdateParent(RedBlackTreeNode *node, RedBlackTreeNode *newNode) noexcept;
  void SwapNodesAndUpdateAfterErase(RedBlackTreeNode *node,
                                    RedBlackTreeNode *survivor) noexcept;
  void EraseBalancing(RedBlackTreeNode *deleted_node) noexcept;
  void HandleBlackSiblingWithRedChild(RedBlackTreeNode *parent,
                                      RedBlackTreeNode *&check_node);
  void HandleBlackSiblingWithBlackChildren(RedBlackTreeNode *parent,
                                           RedBlackTreeNode *&check_node);
  void HandleRedSibling(RedBlackTreeNode *parent,
                        RedBlackTreeNode *&check_node);
  RedBlackTreeNode *GoRight(RedBlackTreeNode *node) const noexcept;
  RedBlackTreeNode *GoLeft(RedBlackTreeNode *node) const noexcept;
  RedBlackTreeNode *SearchMinimum(RedBlackTreeNode *node) const noexcept;
  RedBlackTreeNode *SearchMaximum(RedBlackTreeNode *node) const noexcept;
  int ComputeBlackHeight(const RedBlackTreeNode *node) const noexcept;
  bool isRedNodes(const RedBlackTreeNode *Node) const noexcept;

  struct RedBlackTreeNode;
  struct RedBlackTreeIterator;
  struct RedBlackTreeIteratorConst;

  RedBlackTreeNode *head_;
  size_type size_;
  Value key_comparator_;
};
}  // namespace s21

#include "RB_tree.tpp"
#endif  // CPP2_S21_CONTAINERS_SRC_RB_TREE_RB_TREE_H_