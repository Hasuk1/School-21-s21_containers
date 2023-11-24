#include <gtest/gtest.h>

#include <iostream>

#include "s21_containers.h"
#include "s21_containersplus.h"

/*--->List tests<---*/

TEST(tests_of_list, PushBack) {
  std::cout << "\n\n\033[1;32m";
  std::cout << "LIST TESTS";
  std::cout << "\033[0m\n\n";
  s21::list<int> s21_list = {42};
  s21_list.push_back(17);
  s21_list.push_back(89);
  s21_list.push_back(123);
  s21_list.push_back(55);
  s21_list.push_back(72);
  s21_list.push_back(33);
  auto Mylist_2 = s21_list;
  auto it_2 = Mylist_2.begin();
  for (auto it = s21_list.begin(); it != s21_list.end();) {
    EXPECT_EQ(*it_2, *it);
    ++it;
    ++it_2;
  }

  s21::list<int> Mylist_4;
  Mylist_4 = s21_list;

  auto it = s21_list.begin();
  auto it_4 = Mylist_4.begin();
  for (size_t i = 42; i <= s21_list.size(); i += 17) {
    EXPECT_EQ(*it_4, *it);
    ++it;
    ++it_4;
  }

  it = s21_list.begin();
  for (size_t i = 42; i <= s21_list.size(); i += 17) {
    EXPECT_EQ(i, *it);
    ++it;
  }
  auto Mylist_3 = std::move(s21_list);
}

TEST(tests_of_List, PushFront) {
  s21::list<int> s21_list = {0};
  s21_list.push_front(77);
  s21_list.push_front(123);
  s21_list.push_front(99);
  int i = 4;
  EXPECT_EQ(i, s21_list.size());
}

TEST(ListSortTest, SortSingleElement) {
  s21::list<int> myList = {42};
  myList.sort();
  EXPECT_EQ(myList.front(), 42);
  EXPECT_EQ(myList.back(), 42);
}

TEST(ListSortTest, SortSortedList) {
  s21::list<int> myList = {1, 2, 3, 4, 5};
  myList.sort();
  EXPECT_EQ(myList.front(), 1);
  EXPECT_EQ(myList.back(), 5);
}

TEST(ListSortTest, SortReverseSortedList) {
  s21::list<int> myList = {5, 4, 3, 2, 1};
  myList.sort();
  EXPECT_EQ(myList.front(), 1);
  EXPECT_EQ(myList.back(), 5);
}

TEST(ListSortTest, SortRandomOrderedList) {
  s21::list<int> myList = {3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5};
  myList.sort();
  EXPECT_EQ(myList.size(), 11);
  EXPECT_EQ(myList.front(), 1);
  EXPECT_EQ(myList.back(), 9);

  int prev = myList.front();
  for (auto it = myList.begin(); it != myList.end(); ++it) {
    EXPECT_LE(prev, *it);
    prev = *it;
  }
}

TEST(ListSortTest, SortAlreadySortedList) {
  s21::list<int> myList = {1, 2, 3, 4, 5};
  myList.sort();
  myList.sort();
  EXPECT_EQ(myList.front(), 1);
  EXPECT_EQ(myList.back(), 5);
}

TEST(tests_of_List, Sort) {
  s21::list<int> list;

  list.push_back(3);
  list.push_back(1);
  list.push_back(2);

  list.sort();

  std::list<int> expected = {1, 2, 3};

  auto it1 = list.begin();
  auto it2 = expected.begin();
  while (it1 != list.end()) {
    EXPECT_EQ(*it1, *it2);
    ++it1;
    ++it2;
  }
}

TEST(tests_of_List, SortOneElement) {
  s21::list<int> list;

  list.push_back(5);
  list.sort();

  EXPECT_EQ(list.front(), 5);
}

TEST(tests_of_List, pop_back) {
  s21::list<int> s21_list;
  s21_list.push_back(12);
  s21_list.push_back(64);
  s21_list.push_back(29);
  s21_list.pop_back();
  auto it = s21_list.begin();
  int i = 12;
  size_t size = 0;
  while (size < s21_list.size()) {
    ASSERT_EQ(i, *it);
    if (i == 64) {
      i = 12;
    } else if (i == 12) {
      i = 64;
    }
    ++it;
    size++;
  }
}

TEST(tests_of_List, pop_Front) {
  s21::list<int> s21_list = {0};
  s21_list.push_front(7);
  s21_list.push_front(123);
  s21_list.push_front(88);
  int i = 4;
  EXPECT_EQ(i, s21_list.size());
}

TEST(tests_of_List, Front) {
  s21::list<int> s21_list = {11, 22, 33};
  int a = s21_list.front();
  ASSERT_EQ(11, a);
}

TEST(tests_of_List, back) {
  s21::list<int> s21_list = {111, 222, 333};
  int a = s21_list.back();
  ASSERT_EQ(333, a);
}

TEST(tests_of_List, empty) {
  s21::list<int> s21_list = {4, 6, 8};
  int a = s21_list.empty();
  ASSERT_EQ(0, a);
}
TEST(tests_of_List, size) {
  s21::list<int> s21_list = {4, 8, 15, 16};
  size_t a = s21_list.size();
  ASSERT_EQ(4, a);
}

TEST(tests_of_List, unique) {
  s21::list<int> s21_list_2 = {21, 22, 21, 33, 44, 33};
  std::list<int> List = {21, 22, 21, 33, 44, 33};
  s21_list_2.unique();
  List.unique();
  auto it = s21_list_2.begin();
  for (auto itStd = List.begin(); itStd != List.end(); itStd++) {
    EXPECT_EQ(*it, *itStd);
    it++;
  }
}
TEST(tests_of_List, unique_2) {
  s21::list<int> s21_list_2 = {1, 2, 2, 2, 3, 4, 4, 4, 5, 5};
  std::list<int> List = {1, 2, 2, 2, 3, 4, 4, 4, 5, 5};
  s21_list_2.unique();
  List.unique();
  auto it = s21_list_2.begin();
  for (auto itStd = List.begin(); itStd != List.end(); ++itStd) {
    EXPECT_EQ(*it, *itStd);
    ++it;
  }
}

TEST(tests_of_List, unique_3) {
  s21::list<int> s21_list_2 = {1, 2, 3, 4, 1};
  std::list<int> List = {1, 2, 3, 4, 1};
  s21_list_2.unique();
  List.unique();
  auto it = s21_list_2.begin();
  for (auto itStd = List.begin(); itStd != List.end(); ++itStd) {
    EXPECT_EQ(*it, *itStd);
    ++it;
  }
}

TEST(tests_of_List, merge) {
  s21::list<int> s21_list = {2, 4, 6, 8, 10};
  s21::list<int> s21_list_2 = {1, 3, 5, 7, 9};
  s21::list<int> result = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  s21_list.merge(s21_list_2);

  auto it = s21_list.begin();
  for (auto it_res = result.begin(); it_res != result.end(); ++it_res) {
    EXPECT_EQ(*it, *it_res);
    ++it;
  }
  EXPECT_EQ(s21_list.size(), result.size());
}

TEST(tests_of_List, splice) {
  s21::list<int> s21_list = {1, 4, 5, 6};
  s21::list<int> s21_list_2 = {2, 3};
  auto it_1 = s21_list.begin();
  ++it_1;
  s21_list.splice(it_1.node(), s21_list_2);
  auto it = s21_list.begin();
  std::list<int> result = {1, 2, 3, 4, 5, 6};

  for (auto it_res = result.begin(); it_res != result.end(); it_res++) {
    EXPECT_EQ(*it, *it_res);
    ++it;
  }

  std::list<int> result_2 = {1, 2, 3, 4, 5, 6, 7, 8, 9};
  s21::list<int> s21_list_3 = {7, 8, 9};
  s21_list.splice(s21_list.end(), s21_list_3);
  it = s21_list.begin();
  for (auto it_res = result_2.begin(); it_res != result_2.end(); it_res++) {
    EXPECT_EQ(*it, *it_res);
    ++it;
  }

  std::list<int> result_3 = {-3, -2, -1, 1, 2, 3, 4, 5, 6, 7, 8, 9};
  s21::list<int> s21_list_4 = {-3, -2, -1};
  s21_list.splice(s21_list.begin(), s21_list_4);
  it = s21_list.begin();
  for (auto it_res = result_3.begin(); it_res != result_3.end(); it_res++) {
    EXPECT_EQ(*it, *it_res);
    ++it;
  }
}

TEST(tests_of_List, Insert) {
  s21::list<int> s21_list = {1, 2, 3, 4, 5};
  std::list<int> List = {1, 2, 3, 4, 5};
  auto it_1 = s21_list.begin();
  auto it_std = List.begin();

  auto it_2 = s21_list.insert(it_1, 0);
  auto it_std_2 = List.insert(it_std, 0);

  ASSERT_EQ(*it_std_2, *it_2);

  it_1 += 3;
  for (size_t i = 0; i < 3; i++) {
    it_std++;
  }

  it_2 = s21_list.insert(it_1, 6);
  it_std_2 = List.insert(it_std, 6);
  ASSERT_EQ(*it_std_2, *it_2);

  it_1 = s21_list.end();
  it_std = List.end();
  it_2 = s21_list.insert(it_1, 7);
  it_std_2 = List.insert(it_std, 7);
  ASSERT_EQ(*it_std_2, *it_2);
}
TEST(list, EmplaceBack_test) {
  struct structure {
    int x_;
    long double y_;
    char z_;
    bool operator==(const structure& other) const {
      return (x_ == other.x_ && y_ == other.y_ && z_ == other.z_);
    }
    structure() {
      x_ = 0;
      y_ = 0.0;
      z_ = '0';
    }
    structure(int x, long double y, char z) : x_(x), y_(y), z_(z) {}
  };

  structure arg_1 = {5, 3.14, 'A'};
  structure arg_2 = {10, 2.718, 'B'};
  structure expecting_result = {7, 1.618, 'C'};

  s21::list<structure> my_list = {arg_1, arg_2};
  auto itr = my_list.begin();

  my_list.EmplaceBack(7, 1.618, 'C');
  EXPECT_TRUE(*itr == arg_1);
  ++itr;
  EXPECT_TRUE(*itr == arg_2);
  ++itr;
  EXPECT_TRUE(*itr == expecting_result);
}

/*--->Map tests<---*/

TEST(MapTest, EmptyMap) {
  std::cout << "\n\n\033[1;32m";
  std::cout << "MAP TESTS";
  std::cout << "\033[0m\n\n";
  s21::map<int, std::string> m;
  std::map<int, std::string> m_o;
  EXPECT_TRUE(m.empty() == m_o.empty());
  EXPECT_EQ(m.size(), m_o.size());
}

TEST(MapTest, InsertSingleElement) {
  s21::map<int, std::string> m;
  m.insert(std::make_pair(1, "one"));
  EXPECT_FALSE(m.empty());
  EXPECT_EQ(m.size(), 1);
  EXPECT_EQ(m[1], "one");
}

TEST(MapTest, InsertAndRetrieveMultipleElements) {
  s21::map<int, std::string> m;
  m.insert(std::make_pair(1, "one"));
  m.insert(std::make_pair(2, "two"));
  EXPECT_EQ(m.size(), 2);
  EXPECT_EQ(m[1], "one");
  EXPECT_EQ(m[2], "two");
}

TEST(MapTest, CopyConstructor) {
  s21::map<int, std::string> m1;
  m1[1] = "one";
  s21::map<int, std::string> m2(m1);
  EXPECT_EQ(m1[1], m2[1]);
}

TEST(MapTest, AtNonExistentKey) {
  s21::map<int, std::string> m;
  EXPECT_THROW(m.at(1), std::out_of_range);
}

TEST(MapTest, InsertOrAssign) {
  s21::map<int, std::string> m;
  m.insert_or_assign(1, "one");
  EXPECT_EQ(m[1], "one");
  m.insert_or_assign(1, "new_one");
  EXPECT_EQ(m[1], "new_one");
}

TEST(MapTest, EraseElement) {
  s21::map<int, std::string> m;
  m.insert(std::make_pair(1, "one"));
  auto it = m.begin();
  m.erase(it);
  EXPECT_TRUE(m.empty());
  EXPECT_EQ(m.size(), 0);
}

TEST(MapTest, MoveConstructor) {
  s21::map<int, std::string> m1;
  m1[1] = "one";
  s21::map<int, std::string> m2(std::move(m1));
  EXPECT_EQ(m2[1], "one");
  EXPECT_TRUE(m1.empty());
}

TEST(MapTest, SwapMaps) {
  s21::map<int, std::string> m1;
  m1[1] = "one";
  s21::map<int, std::string> m2;
  m2[2] = "two";
  m1.swap(m2);
  EXPECT_EQ(m1[2], "two");
  EXPECT_EQ(m2[1], "one");
}

TEST(MapTest, MergeMaps) {
  s21::map<int, std::string> m1;
  m1[1] = "one";
  s21::map<int, std::string> m2;
  m2[2] = "two";
  m1.merge(m2);
  EXPECT_EQ(m1[1], "one");
  EXPECT_EQ(m1[2], "two");
  EXPECT_TRUE(m2.empty());
}

TEST(MapTest, IteratorTraversal) {
  s21::map<int, std::string> m;
  m.insert(std::make_pair(1, "one"));
  m.insert(std::make_pair(2, "two"));
  m.insert(std::make_pair(3, "three"));

  auto it = m.begin();
  EXPECT_EQ((*it).first, 1);
  EXPECT_EQ((*it).second, "one");
  ++it;
  EXPECT_EQ((*it).first, 2);
  EXPECT_EQ((*it).second, "two");
  ++it;
  EXPECT_EQ((*it).first, 3);
  EXPECT_EQ((*it).second, "three");
}

TEST(MapTest, AssignmentOperator) {
  s21::map<int, std::string> m1;
  m1[1] = "one";
  s21::map<int, std::string> m2;
  m2 = m1;
  EXPECT_EQ(m2[1], "one");
}

TEST(MapTest, InitializerListConstructor) {
  s21::map<int, std::string> m{{1, "one"}, {2, "two"}};
  EXPECT_EQ(m[1], "one");
  EXPECT_EQ(m[2], "two");
  EXPECT_EQ(m.size(), 2);
}

TEST(MapTest, ContainsMethod) {
  s21::map<int, std::string> m;
  m[1] = "one";
  EXPECT_TRUE(m.contains(1));
  EXPECT_FALSE(m.contains(2));
}

TEST(MapTest, EmptyMapAfterClear) {
  s21::map<int, std::string> m;
  m.insert(std::make_pair(1, "one"));
  m.clear();
  EXPECT_TRUE(m.empty());
  EXPECT_EQ(m.size(), 0);
}

TEST(MapTest, InsertDuplicateKey) {
  s21::map<int, std::string> m;
  m.insert(std::make_pair(1, "one"));
  m.insert(std::make_pair(1, "duplicate"));
  EXPECT_EQ(m.size(), 1);
  EXPECT_EQ(m[1], "one");
}

TEST(MapTest, EraseSingleElement) {
  s21::map<int, std::string> m;
  m.insert(std::make_pair(1, "one"));
  m.erase(m.begin());
  EXPECT_TRUE(m.empty());
  EXPECT_EQ(m.size(), 0);
}

TEST(MapTest, MergeDuplicateKeys) {
  s21::map<int, std::string> m1{{1, "one"}, {2, "two"}};
  s21::map<int, std::string> m2{{2, "duplicate"}, {3, "three"}};
  m1.merge(m2);
  EXPECT_EQ(m1.size(), 3);
  EXPECT_EQ(m1[2], "two");
}

TEST(MapTest, FindNonExistingKeyWithConstMap) {
  const s21::map<int, std::string> m{{1, "one"}, {2, "two"}};
  auto it = m.find(3);
  EXPECT_EQ(it, m.cend());
}

TEST(MapTest, MergeWithoutModifyingOriginal) {
  s21::map<int, std::string> m1{{1, "one"}, {2, "two"}};
  s21::map<int, std::string> m2{{3, "three"}};
  s21::map<int, std::string> m1_copy = m1;
  m1.merge(m2);
  EXPECT_EQ(m1.size(), 3);
  EXPECT_EQ(m1_copy.size(), 2);
}

/*--->queue tests<---*/

TEST(queueTest, PushPopSize) {
  std::cout << "\n\n\033[1;32m";
  std::cout << "queue TESTS";
  std::cout << "\033[0m\n\n";
  s21::queue<int> queue;
  EXPECT_TRUE(queue.empty());
  EXPECT_EQ(queue.size(), 0);

  queue.push(1);
  EXPECT_FALSE(queue.empty());
  EXPECT_EQ(queue.size(), 1);

  queue.push(2);
  queue.push(3);
  EXPECT_EQ(queue.size(), 3);

  queue.pop();
  EXPECT_EQ(queue.size(), 2);

  queue.pop();
  queue.pop();
  EXPECT_EQ(queue.size(), 0);
  EXPECT_TRUE(queue.empty());
}

TEST(queueTest, FrontBack) {
  s21::queue<int> queue;
  queue.push(1);
  queue.push(2);
  queue.push(3);

  EXPECT_EQ(queue.front(), 1);
  EXPECT_EQ(queue.back(), 3);

  queue.pop();
  EXPECT_EQ(queue.front(), 2);

  queue.pop();
  queue.pop();
  EXPECT_THROW(queue.front(), std::out_of_range);
  EXPECT_THROW(queue.back(), std::out_of_range);
}

TEST(queueTest, CopyConstructor) {
  s21::queue<int> original;
  original.push(1);
  original.push(2);
  original.push(3);

  s21::queue<int> copy(original);
  EXPECT_EQ(original.size(), copy.size());
  EXPECT_EQ(original.front(), copy.front());
  EXPECT_EQ(original.back(), copy.back());
}

TEST(queueTest, MoveConstructor) {
  s21::queue<int> original;
  original.push(1);
  original.push(2);
  original.push(3);

  s21::queue<int> moved(std::move(original));
  EXPECT_EQ(original.size(), 0);
  EXPECT_EQ(moved.size(), 3);
}

TEST(queueTest, Iterators) {
  s21::queue<int> queue;
  queue.push(1);
  queue.push(2);
  queue.push(3);

  int expected_value = 1;
  for (s21::queue<int>::iterator it = queue.begin(); it != queue.end(); ++it) {
    EXPECT_EQ(*it, expected_value);
    expected_value++;
  }

  expected_value = 1;
  for (s21::queue<int>::const_iterator it = queue.cbegin(); it != queue.cend();
       ++it) {
    EXPECT_EQ(*it, expected_value);
    expected_value++;
  }
}

TEST(queueTest, EmplaceBack) {
  s21::queue<std::string> queue;
  queue.EmplaceBack("one");
  queue.EmplaceBack("two");

  EXPECT_EQ(queue.size(), 2);
  EXPECT_EQ(queue.front(), "one");
  EXPECT_EQ(queue.back(), "two");
}

TEST(queueTest, Clear) {
  s21::queue<int> queue;
  queue.push(1);
  queue.push(2);
  queue.push(3);

  EXPECT_EQ(queue.size(), 3);

  queue.clear();
  EXPECT_EQ(queue.size(), 0);
  EXPECT_TRUE(queue.empty());
}

TEST(queueTest, CopyAssignment) {
  s21::queue<int> queue1;
  queue1.push(1);
  queue1.push(2);
  queue1.push(3);

  s21::queue<int> queue2;
  queue2 = queue1;

  EXPECT_EQ(queue1.size(), 3);
  EXPECT_EQ(queue2.size(), 3);
  EXPECT_EQ(queue1.front(), 1);
  EXPECT_EQ(queue2.front(), 1);

  queue1.pop();
  EXPECT_EQ(queue1.size(), 2);
  EXPECT_EQ(queue2.size(), 3);
}

TEST(queueTest, MoveAssignment) {
  s21::queue<int> queue1;
  s21::queue<int> queue2;

  queue2 = std::move(queue1);

  EXPECT_EQ(queue1.size(), 0);
}

TEST(queueTest, BoundaryCases) {
  s21::queue<int> empty_queue;

  EXPECT_THROW(empty_queue.front(), std::out_of_range);
  EXPECT_THROW(empty_queue.back(), std::out_of_range);

  s21::queue<int>::iterator it = empty_queue.begin();
  s21::queue<int>::iterator end = empty_queue.end();
  EXPECT_EQ(it, end);

  s21::queue<int>::const_iterator cit = empty_queue.cbegin();
  s21::queue<int>::const_iterator cend = empty_queue.cend();
  EXPECT_EQ(cit, cend);
}

TEST(queueTest, Swap) {
  s21::queue<int> queue1;
  queue1.push(1);
  queue1.push(2);

  s21::queue<int> queue2;
  queue2.push(3);

  queue1.swap(queue2);

  EXPECT_EQ(queue1.size(), 1);
  EXPECT_EQ(queue2.size(), 2);
  EXPECT_EQ(queue1.front(), 3);
  EXPECT_EQ(queue2.front(), 1);
}

TEST(queueTest, EmplaceBackWithUserDefinedType) {
  struct MyStruct {
    int x;
    std::string str;
    MyStruct(int x, const std::string& str) : x(x), str(str) {}
  };

  s21::queue<MyStruct> queue;
  queue.EmplaceBack(1, "one");
  queue.EmplaceBack(2, "two");

  EXPECT_EQ(queue.size(), 2);
  EXPECT_EQ(queue.front().x, 1);
  EXPECT_EQ(queue.back().str, "two");
}

TEST(queueTest, IteratorBoundaryCases) {
  s21::queue<int> empty_queue;

  s21::queue<int>::iterator it = empty_queue.begin();
  s21::queue<int>::iterator end = empty_queue.end();
  EXPECT_EQ(it, end);

  s21::queue<int>::const_iterator cit = empty_queue.cbegin();
  s21::queue<int>::const_iterator cend = empty_queue.cend();
  EXPECT_EQ(cit, cend);

  s21::queue<int> single_element_queue;
  single_element_queue.push(42);

  it = single_element_queue.begin();
  end = single_element_queue.end();
  EXPECT_NE(it, end);
  EXPECT_EQ(*it, 42);

  cit = single_element_queue.cbegin();
  cend = single_element_queue.cend();
  EXPECT_NE(cit, cend);
  EXPECT_EQ(*cit, 42);
}

/*--->Set tests<---*/

TEST(set, ConstructorDefaultSet) {
  std::cout << "\n\n\033[1;32m";
  std::cout << "SET TESTS";
  std::cout << "\033[0m\n\n";
  s21::set<char> my_empty_set;
  std::set<char> orig_empty_set;
  EXPECT_EQ(my_empty_set.empty(), orig_empty_set.empty());
}

TEST(set, ConstructorInitializerSet) {
  s21::set<char> my_set = {'x', 'b', 'z', 'y'};
  std::set<char> orig_set = {'x', 'b', 'z', 'y'};
  EXPECT_EQ(my_set.size(), orig_set.size());
  auto my_it = my_set.begin();
  auto orig_it = orig_set.begin();
  for (; my_it != my_set.end(); ++my_it, ++orig_it) {
    EXPECT_TRUE(*orig_it == *my_it);
  }
}

TEST(set, ConstructorInitializer2Set) {
  s21::set<char> my_set = {};
  std::set<char> orig_set = {};
  EXPECT_EQ(my_set.size(), orig_set.size());
  auto my_it = my_set.begin();
  auto orig_it = orig_set.begin();
  for (; my_it != my_set.end(); ++my_it, ++orig_it) {
    EXPECT_TRUE(*orig_it == *my_it);
  }
}

TEST(set, ConstructorCopySet) {
  s21::set<int> my_set = {1, 2, 3, 4, 5};
  std::set<int> orig_set = {1, 2, 3, 4, 5};
  s21::set<int> my_set_copy = my_set;
  std::set<int> orig_set_copy = orig_set;
  EXPECT_EQ(my_set_copy.size(), orig_set_copy.size());
  EXPECT_EQ(*my_set_copy.find(3), *orig_set_copy.find(3));
}

TEST(SetTest, MoveConstructor) {
  s21::set<int> original{1, 2, 3};
  s21::set<int> moved(std::move(original));
  EXPECT_EQ(moved.size(), 3);
  EXPECT_TRUE(original.empty());
}

TEST(SetTest, Insert) {
  s21::set<int> s;
  auto [it, success] = s.insert(42);
  EXPECT_TRUE(success);
  EXPECT_EQ(*it, 42);
  EXPECT_EQ(s.size(), 1);

  auto [it2, success2] = s.insert(42);
  EXPECT_FALSE(success2);
  EXPECT_EQ(s.size(), 1);
}

TEST(SetTest, Erase) {
  s21::set<int> s{1, 2, 3};
  auto it = s.find(2);
  s.erase(it);
  EXPECT_EQ(s.size(), 2);
  EXPECT_EQ(s.find(2), s.end());
}

TEST(SetTest, Merge) {
  s21::set<int> s1{1, 2, 3};
  s21::set<int> s2{3, 4, 5};
  s1.merge(s2);
  EXPECT_EQ(s1.size(), 5);
  EXPECT_TRUE(s1.contains(4));
  EXPECT_TRUE(s2.empty());
}

TEST(SetTest, Swap) {
  s21::set<int> s1{1, 2, 3};
  s21::set<int> s2{4, 5, 6};
  s1.swap(s2);
  EXPECT_EQ(s1.size(), 3);
  EXPECT_EQ(*s1.find(4), 4);
  EXPECT_EQ(s2.size(), 3);
  EXPECT_EQ(*s2.find(1), 1);
}

TEST(SetTest, Clear) {
  s21::set<int> s{1, 2, 3};
  s.clear();
  EXPECT_TRUE(s.empty());
  EXPECT_EQ(s.size(), 0);
}

TEST(SetTest, MergeEmptyTrees) {
  s21::set<int> s1;
  s21::set<int> s2;
  s1.merge(s2);
  EXPECT_TRUE(s1.empty());
  EXPECT_TRUE(s2.empty());
}

TEST(SetTest, MergeWithSelf) {
  s21::set<int> s1{1, 2, 3};
  s1.merge(s1);
  EXPECT_EQ(s1.size(), 3);
}

TEST(SetTest, ContainsMethod) {
  s21::set<int> s{1, 2, 3};
  EXPECT_TRUE(s.contains(2));
  EXPECT_FALSE(s.contains(4));
}

TEST(SetTest, MaxSizeMethod) {
  s21::set<int> s;
  EXPECT_GT(s.max_size(), 0);
}

TEST(SetTest, CopyAssignment) {
  s21::set<int> original{1, 2, 3};
  s21::set<int> copy;
  copy = original;
  EXPECT_EQ(copy.size(), 3);
  EXPECT_EQ(*copy.find(2), 2);
}

TEST(SetTest, MoveAssignment) {
  s21::set<int> original{1, 2, 3};
  s21::set<int> moved;
  moved = std::move(original);
  EXPECT_EQ(moved.size(), 3);
  EXPECT_TRUE(original.empty());
}

TEST(SetTest, BeginEndIterators) {
  s21::set<int> s{1, 2, 3};
  auto it = s.begin();
  EXPECT_EQ(*it, 1);
  ++it;
  EXPECT_EQ(*it, 2);
  ++it;
  EXPECT_EQ(*it, 3);
  ++it;
  EXPECT_EQ(it, s.end());
}

TEST(SetTest, MergeWithEmptySet) {
  s21::set<int> s1{1, 2, 3};
  s21::set<int> s2;
  s1.merge(s2);
  EXPECT_EQ(s1.size(), 3);
  EXPECT_TRUE(s2.empty());
}

TEST(SetTest, FindNonExistentElement) {
  s21::set<int> s{1, 2, 3};
  EXPECT_EQ(s.find(42), s.end());
}

TEST(SetTest, CountMethod) {
  s21::set<int> my_set;
  my_set.insert(5);
  my_set.insert(10);
  EXPECT_EQ(my_set.count(5), 1);
  EXPECT_EQ(my_set.count(3), 0);
}

TEST(SetTest, EraseByKey) {
  s21::set<int> set1 = {1, 2, 3};

  EXPECT_EQ(set1.erase(2), 1);
  EXPECT_EQ(set1.count(2), 0);
  EXPECT_EQ(set1.erase(4), 0);
  EXPECT_EQ(set1.count(4), 0);
}

TEST(SetTest, CompareSets) {
  s21::set<int> s1{1, 2, 3};
  s21::set<int> s2{1, 2, 3};
  s21::set<int> s3{4, 5, 6};
  EXPECT_TRUE(s1 == s2);
  EXPECT_FALSE(s1 == s3);
}

/*--->Stack tests<---*/

TEST(tests_of_stack, push1) {
  std::cout << "\n\n\033[1;32m";
  std::cout << "STACK TESTS";
  std::cout << "\033[0m\n\n";
  s21::stack<int> s21Stack;
  s21Stack.Push(1);
  s21Stack.Push(2);
  s21Stack.Push(3);

  int i = 3;
  size_t size = 0;
  while (size < s21Stack.Size()) {
    ASSERT_EQ(i, s21Stack.Top());
    i--;

    size++;
    s21Stack.Pop();
  }
}

TEST(tests_of_stack, pop1) {
  s21::stack<int> s21Stack;
  s21Stack.Push(1);
  s21Stack.Push(2);
  s21Stack.Push(3);

  s21Stack.Pop();
  s21Stack.Pop();
  s21Stack.Pop();

  bool emptyStack = s21Stack.Empty();
  ASSERT_EQ(true, emptyStack);
}

TEST(tests_of_stack, top) {
  s21::stack<int> s21Stack;
  s21Stack.Push(1);
  s21Stack.Push(2);
  s21Stack.Push(3);
  auto it = s21Stack.Top();
  ASSERT_EQ(3, it);
}

TEST(tests_of_stack, top2) {
  s21::stack<int> s21Stack;
  s21Stack.Push(1);
  s21Stack.Push(2);
  s21Stack.Pop();
  s21Stack.Pop();

  ASSERT_THROW(s21Stack.Top(), std::out_of_range);
}

TEST(tests_of_stack, size1) {
  s21::stack<int> s21Stack;
  s21Stack.Push(1);
  s21Stack.Push(2);
  s21Stack.Push(3);
  auto it = s21Stack.Size();
  ASSERT_EQ(3, it);
}

TEST(tests_of_stack, size2) {
  s21::stack<int> s21Stack;
  s21Stack.Push(1);
  auto it = s21Stack.Size();
  ASSERT_EQ(1, it);
}

TEST(tests_of_stack, equal) {
  s21::stack<int> s21Stack;
  s21Stack.Push(1);
  s21Stack.Push(2);
  s21Stack.Push(3);
  int i = 3;
  size_t size = 0;
  while (size < s21Stack.Size()) {
    ASSERT_EQ(i, s21Stack.Top());
    i--;
    size++;
    s21Stack.Pop();
  }
}

TEST(tests_of_stack, push2) {
  s21::stack<int> s21Stack;
  s21Stack.Push(1);
  s21Stack.Push(2);
  s21Stack.Push(3);
  s21Stack.Push(4);

  ASSERT_EQ(4, s21Stack.Size());
  ASSERT_EQ(4, s21Stack.Top());
}

TEST(tests_of_stack, push3) {
  s21::stack<std::string> s21Stack;
  s21Stack.Push("Hello");
  s21Stack.Push("World");

  ASSERT_EQ(2, s21Stack.Size());
  ASSERT_EQ("World", s21Stack.Top());
}

TEST(tests_of_stack, pop2) {
  s21::stack<int> s21Stack;
  s21Stack.Push(1);
  s21Stack.Push(2);
  s21Stack.Push(3);

  s21Stack.Pop();
  s21Stack.Pop();

  ASSERT_EQ(1, s21Stack.Size());
  ASSERT_EQ(1, s21Stack.Top());
}

TEST(tests_of_stack, empty) {
  s21::stack<int> s21Stack;

  ASSERT_TRUE(s21Stack.Empty());

  s21Stack.Push(1);

  ASSERT_FALSE(s21Stack.Empty());

  s21Stack.Pop();

  ASSERT_TRUE(s21Stack.Empty());
}

TEST(tests_of_stack, copy_constructor) {
  s21::stack<int> s21Stack;
  s21Stack.Push(1);
  s21Stack.Push(2);
  s21Stack.Push(3);

  s21::stack<int> myStack_2(s21Stack);

  ASSERT_EQ(s21Stack.Size(), myStack_2.Size());
  ASSERT_EQ(s21Stack.Top(), myStack_2.Top());
}

TEST(tests_of_stack, assignment_operator) {
  s21::stack<int> s21Stack;
  s21Stack.Push(1);
  s21Stack.Push(2);
  s21Stack.Push(3);

  s21::stack<int> myStack_2;
  myStack_2 = s21Stack;

  ASSERT_EQ(s21Stack.Size(), myStack_2.Size());
  ASSERT_EQ(s21Stack.Top(), myStack_2.Top());
}

TEST(tests_of_stack, resize) {
  s21::stack<int> s21Stack;
  s21Stack.Push(1);
  s21Stack.Push(2);
  s21Stack.Push(3);
  s21Stack.Push(4);

  ASSERT_EQ(4, s21Stack.Size());
  ASSERT_EQ(4, s21Stack.Top());
}

TEST(tests_of_stack, out_of_range) {
  s21::stack<int> s21Stack;

  ASSERT_THROW(s21Stack.Top(), std::out_of_range);
  ASSERT_THROW(s21Stack.Pop(), std::out_of_range);
}

/*--->Vector tests<---*/

TEST(VectorTest, DefaultConstructor) {
  std::cout << "\n\n\033[1;32m";
  std::cout << "VECTOR TESTS";
  std::cout << "\033[0m\n\n";
  s21::vector<int> s21_vec_int;
  s21::vector<double> s21_vec_double;
  s21::vector<std::string> s21_vec_string;

  EXPECT_EQ(s21_vec_int.size(), 0);
  EXPECT_EQ(s21_vec_int.capacity(), 0);
  EXPECT_EQ(s21_vec_int.data(), nullptr);

  EXPECT_EQ(s21_vec_double.size(), 0);
  EXPECT_EQ(s21_vec_double.capacity(), 0);
  EXPECT_EQ(s21_vec_int.data(), nullptr);

  EXPECT_EQ(s21_vec_string.size(), 0);
  EXPECT_EQ(s21_vec_string.capacity(), 0);
  EXPECT_EQ(s21_vec_int.data(), nullptr);
}

TEST(VectorTest, SizeConstructor) {
  s21::vector<int> int_size_constructor(5);
  s21::vector<double> double_size_constructor(5);
  s21::vector<std::string> char_size_constructor(5);

  EXPECT_EQ(int_size_constructor.size(), 5);
  EXPECT_EQ(int_size_constructor.capacity(), 5);
  EXPECT_EQ(int_size_constructor.front(), 0);
  EXPECT_EQ(int_size_constructor.back(), 0);
  int_size_constructor = {1, 2, 3, 4, 5};
  EXPECT_EQ(int_size_constructor.front(), 1);
  EXPECT_EQ(int_size_constructor.back(), 5);
  for (size_t i = 0; i < int_size_constructor.size(); i++)
    EXPECT_EQ(int_size_constructor[i], i + 1);

  EXPECT_EQ(double_size_constructor.size(), 5);
  EXPECT_EQ(double_size_constructor.capacity(), 5);
  EXPECT_EQ(double_size_constructor.front(), 0);
  EXPECT_EQ(double_size_constructor.back(), 0);
  double_size_constructor = {1.2, 2.3, 3.4, 4.5, 5.6};
  double test_double[] = {1.2, 2.3, 3.4, 4.5, 5.6};
  EXPECT_EQ(double_size_constructor.front(), 1.2);
  EXPECT_EQ(double_size_constructor.back(), 5.6);
  for (size_t i = 0; i < double_size_constructor.size(); i++)
    EXPECT_EQ(double_size_constructor[i], test_double[i]);

  EXPECT_EQ(char_size_constructor.size(), 5);
  EXPECT_EQ(char_size_constructor.capacity(), 5);
  EXPECT_EQ(char_size_constructor.front(), "");
  EXPECT_EQ(char_size_constructor.back(), "");
  char_size_constructor = {"one", "two", "three", "four", "five"};
  std::string test_string[] = {"one", "two", "three", "four", "five"};
  EXPECT_EQ(char_size_constructor.front(), "one");
  EXPECT_EQ(char_size_constructor.back(), "five");
  for (size_t i = 0; i < char_size_constructor.size(); i++)
    EXPECT_EQ(char_size_constructor[i], test_string[i]);
}

TEST(VectorTest, InitializerListConstructor) {
  s21::vector<int> init_int{1, 2, 3, 4, 5};
  s21::vector<double> init_double{1.2, 2.3, 3.4, 4.5, 5.6};
  s21::vector<std::string> init_string{"one", "two", "three", "four", "five"};

  EXPECT_EQ(init_int.size(), 5);
  EXPECT_EQ(init_int.capacity(), 5);
  EXPECT_EQ(init_int.front(), 1);
  EXPECT_EQ(init_int.back(), 5);
  for (size_t i = 0; i < init_int.size(); i++) EXPECT_EQ(init_int[i], i + 1);

  EXPECT_EQ(init_double.size(), 5);
  EXPECT_EQ(init_double.capacity(), 5);
  double test_double[] = {1.2, 2.3, 3.4, 4.5, 5.6};
  EXPECT_EQ(init_double.front(), 1.2);
  EXPECT_EQ(init_double.back(), 5.6);
  for (size_t i = 0; i < init_double.size(); i++)
    EXPECT_EQ(init_double[i], test_double[i]);

  EXPECT_EQ(init_string.size(), 5);
  EXPECT_EQ(init_string.capacity(), 5);
  std::string test_string[] = {"one", "two", "three", "four", "five"};
  EXPECT_EQ(init_string.front(), "one");
  EXPECT_EQ(init_string.back(), "five");
  for (size_t i = 0; i < init_string.size(); i++)
    EXPECT_EQ(init_string[i], test_string[i]);
}

TEST(VectorTest, CopyConstructor) {
  s21::vector<int> copy_int{1, 2, 3, 4, 5};
  s21::vector<int> copy_int_2(copy_int);
  s21::vector<double> copy_double{1.2, 2.3, 3.4, 4.5, 5.6};
  s21::vector<double> copy_double_2(copy_double);
  s21::vector<std::string> copy_string{"one", "two", "three", "four", "five"};
  s21::vector<std::string> copy_string_2(copy_string);

  EXPECT_EQ(copy_int.size(), copy_int_2.size());
  EXPECT_EQ(copy_int.capacity(), copy_int_2.capacity());
  EXPECT_EQ(copy_int.front(), copy_int.front());
  EXPECT_EQ(copy_int.back(), copy_int.back());
  for (size_t i = 0; i < copy_int.size(); ++i)
    EXPECT_EQ(copy_int[i], copy_int_2[i]);

  EXPECT_EQ(copy_double.size(), copy_double_2.size());
  EXPECT_EQ(copy_double.capacity(), copy_double_2.capacity());
  EXPECT_EQ(copy_double.front(), copy_double_2.front());
  EXPECT_EQ(copy_double.back(), copy_double_2.back());
  for (size_t i = 0; i < copy_double_2.size(); ++i)
    EXPECT_EQ(copy_double[i], copy_double_2[i]);

  EXPECT_EQ(copy_string.size(), copy_string_2.size());
  EXPECT_EQ(copy_string.capacity(), copy_string_2.capacity());
  EXPECT_EQ(copy_string.front(), copy_string_2.front());
  EXPECT_EQ(copy_string.back(), copy_string_2.back());
  for (size_t i = 0; i < copy_string_2.size(); ++i)
    EXPECT_EQ(copy_string[i], copy_string_2[i]);
}

TEST(VectorTest, MoveConstructor) {
  s21::vector<int> move_int{1, 2, 3, 4, 5};
  s21::vector<double> move_double{1.2, 2.3, 3.4, 4.5, 5.6};
  s21::vector<std::string> move_string{"one", "two", "three", "four", "five"};

  s21::vector<int> move_int_2(std::move(move_int));
  s21::vector<double> move_double_2(std::move(move_double));
  s21::vector<std::string> move_string_2(std::move(move_string));

  EXPECT_EQ(move_int.size(), 0);
  EXPECT_EQ(move_int_2.size(), 5);
  EXPECT_EQ(move_int.data(), nullptr);
  for (size_t i = 0; i < move_int.size(); i++) EXPECT_EQ(move_int_2[i], i);

  EXPECT_EQ(move_double.size(), 0);
  EXPECT_EQ(move_double_2.size(), 5);
  EXPECT_EQ(move_double.data(), nullptr);
  for (size_t i = 0; i < move_double.size(); i++)
    EXPECT_EQ(move_double_2[i], i);

  EXPECT_EQ(move_string.size(), 0);
  EXPECT_EQ(move_string_2.size(), 5);
  EXPECT_EQ(move_string.data(), nullptr);
  std::string test_string[] = {"one", "two", "three", "four", "five"};
  for (size_t i = 0; i < move_string.size(); i++)
    EXPECT_EQ(move_string_2[i], test_string[i]);
}

TEST(VectorTest, at_checking) {
  s21::vector<int> move_int{1, 2, 3, 4, 5};
  s21::vector<double> move_double{1.2, 2.3, 3.4, 4.5, 5.6};
  s21::vector<std::string> move_string{"one", "two", "three", "four", "five"};

  for (size_t i = 0; i < move_int.size(); i++) EXPECT_EQ(move_int.at(i), i + 1);

  double test_double[] = {1.2, 2.3, 3.4, 4.5, 5.6};
  for (size_t i = 0; i < move_double.size(); i++)
    EXPECT_EQ(move_double.at(i), test_double[i]);

  std::string test_string[] = {"one", "two", "three", "four", "five"};
  for (size_t i = 0; i < move_string.size(); i++)
    EXPECT_EQ(move_string.at(i), test_string[i]);
}

TEST(VectorTest, operator1) {
  s21::vector<int> operator1_int(2);
  s21::vector<double> operator1_double(2);
  s21::vector<std::string> operator1_string(2);

  operator1_int[0] = 1;
  operator1_int[1] = 2;
  for (size_t i = 0; i < operator1_int.size(); i++)
    EXPECT_EQ(operator1_int.at(i), i + 1);

  operator1_double[0] = 1.2;
  operator1_double[1] = 2.3;
  double test_double[] = {1.2, 2.3};
  for (size_t i = 0; i < operator1_double.size(); i++)
    EXPECT_EQ(operator1_double[i], test_double[i]);

  operator1_string[0] = "one";
  operator1_string[1] = "two";
  std::string test_string[] = {"one", "two"};
  for (size_t i = 0; i < operator1_string.size(); i++)
    EXPECT_EQ(operator1_string[i], test_string[i]);
}

TEST(VectorTest, Erase_Beginning) {
  s21::vector<int> v = {1, 2, 3, 4};
  v.erase(v.begin());
  EXPECT_EQ(v.size(), 3);
  EXPECT_EQ(v[0], 2);
}

TEST(VectorTest, Erase_Middle) {
  s21::vector<int> v = {1, 2, 3, 4};
  v.erase(v.begin() + 1);
  EXPECT_EQ(v.size(), 3);
  EXPECT_EQ(v[1], 3);
}

TEST(VectorTest, Erase_End) {
  s21::vector<int> v = {1, 2, 3, 4};
  v.erase(v.end() - 1);
  EXPECT_EQ(v.size(), 3);
  EXPECT_EQ(v[2], 3);
}

TEST(VectorTest, erase_checking) {
  s21::vector<int> vec_int{1, 2, 3, 4, 5};
  vec_int.erase(vec_int.begin() + 2);
  size_t expected_int[] = {1, 2, 4, 5};
  ASSERT_EQ(vec_int.size(), 4);
  for (size_t i = 0; i < vec_int.size(); i++) {
    EXPECT_EQ(vec_int.at(i), expected_int[i]);
  }

  s21::vector<double> vec_double{1.2, 2.3, 3.4, 4.5, 5.6};
  vec_double.erase(vec_double.begin() + 2);
  double expected_double[] = {1.2, 2.3, 4.5, 5.6};
  ASSERT_EQ(vec_double.size(), 4);
  for (size_t i = 0; i < vec_double.size(); i++) {
    EXPECT_EQ(vec_double.at(i), expected_double[i]);
  }

  s21::vector<std::string> vec_string{"one", "two", "three", "four", "five"};
  vec_string.erase(vec_string.begin() + 2);
  std::string expected_string[] = {"one", "two", "four", "five"};
  ASSERT_EQ(vec_string.size(), 4);
  for (size_t i = 0; i < vec_string.size(); i++) {
    EXPECT_EQ(vec_string.at(i), expected_string[i]);
  }
}

TEST(VectorTest, EmptyTest) {
  s21::vector<int> empty_int;
  s21::vector<double> empty_double;
  s21::vector<std::string> empty_string;

  EXPECT_TRUE(empty_int.empty());
  EXPECT_TRUE(empty_double.empty());
  EXPECT_TRUE(empty_string.empty());

  empty_int.push_back(10);
  empty_double.push_back(3.14);
  empty_string.push_back("test");

  EXPECT_FALSE(empty_int.empty());
  EXPECT_FALSE(empty_double.empty());
  EXPECT_FALSE(empty_string.empty());
}

TEST(VectorTest, Reserve_IncreaseCapacity) {
  s21::vector<int> v;
  size_t initialCapacity = v.capacity();
  size_t newCapacity = initialCapacity + 10;
  v.reserve(newCapacity);
  EXPECT_GE(v.capacity(), newCapacity);
}

TEST(vectorIteratorsTest, OperatorIncrement) {
  s21::vector<int> myVector{1, 2, 3, 4, 5};
  s21::vector<int>::iterator iter = myVector.begin();

  EXPECT_EQ(*iter, 1);
  ++iter;
  EXPECT_EQ(*iter, 2);
}

TEST(vectorIteratorsTest, OperatorDecrement) {
  s21::vector<int> myVector{1, 2, 3, 4, 5};
  s21::vector<int>::iterator iter = myVector.end();
  --iter;
  EXPECT_EQ(*iter, 5);
  --iter;
  EXPECT_EQ(*iter, 4);
}

TEST(vectorIteratorsTest, OperatorMinus) {
  s21::vector<int> myVector{1, 2, 3, 4, 5};
  s21::vector<int>::iterator iter = myVector.end();
  iter = iter - 2;
  EXPECT_EQ(*iter, 4);
}

TEST(vectorIteratorsTest, OperatorPlus) {
  s21::vector<int> myVector{1, 2, 3, 4, 5};
  s21::vector<int>::iterator iter = myVector.begin();
  iter = iter + 2;

  EXPECT_EQ(*iter, 3);
}

TEST(vectorIteratorsTest, OperatorEqual) {
  s21::vector<int> vector1{1, 2, 3, 4, 5};
  s21::vector<int>::iterator iterator1 = vector1.begin();
  s21::vector<int>::iterator iterator2 = vector1.begin();
  EXPECT_TRUE(iterator1 == iterator2);
}

TEST(vectorIteratorsTest, OperatorNotEqual) {
  s21::vector<int> vector1{1, 2, 3, 4, 5};
  s21::vector<int> vector2{1, 2, 3, 4, 6};
  EXPECT_TRUE(vector1.end() != vector2.end());
}

TEST(vectorIteratorsTesst, OperatorMinusPlusInt) {
  s21::vector<int> numbers{10, 20, 30, 40};
  s21::vector<int>::iterator iter = numbers.begin();
  ++iter;
  EXPECT_EQ(*iter, 20);
  iter += 2;
  EXPECT_EQ(*iter, 40);
  iter -= 3;
  EXPECT_EQ(*iter, 10);
}

TEST(VectorTest, Reserve_DecreaseCapacity) {
  s21::vector<int> v = {1, 2, 3, 4, 5};
  size_t initialCapacity = v.capacity();
  size_t newCapacity = initialCapacity - 2;
  v.reserve(newCapacity);
  EXPECT_LE(v.capacity(), initialCapacity);
  EXPECT_GE(v.capacity(), newCapacity);
}

TEST(VectorTest, PushBackTest) {
  s21::vector<int> push_int;
  s21::vector<double> push_double;
  s21::vector<std::string> push_string;

  push_int.push_back(10);
  push_double.push_back(3.14);
  push_string.push_back("test");

  EXPECT_FALSE(push_int.empty());
  EXPECT_EQ(push_int.back(), 10);

  EXPECT_FALSE(push_double.empty());
  EXPECT_EQ(push_double.back(), 3.14);

  EXPECT_FALSE(push_string.empty());
  EXPECT_EQ(push_string.back(), "test");
}

TEST(VectorTest, ShrinkToFitTest) {
  s21::vector<int> shrink_vec{1, 2, 3, 4, 5, 6};
  shrink_vec.reserve(20);
  ASSERT_EQ(shrink_vec.capacity(), 20);

  shrink_vec.shrink_to_fit();
  EXPECT_EQ(shrink_vec.capacity(), shrink_vec.size());
}

TEST(VectorTest, InsertTest) {
  s21::vector<int> insert_vec{1, 2, 4, 5};
  insert_vec.insert(insert_vec.begin() + 2, 3);
  EXPECT_EQ(insert_vec[2], 3);
}

TEST(VectorTest, PushBackIncreaseCapacity) {
  s21::vector<int> v;
  size_t cap = v.capacity();
  for (size_t i = 0; i < cap + 5; i++) {
    v.push_back(i);
  }
  EXPECT_TRUE(v.capacity() > cap);
}

TEST(VectorTest, PopBackDecreaseCapacity) {
  s21::vector<int> v = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  size_t cap = v.capacity();
  for (size_t i = 0; i < 5; i++) {
    v.pop_back();
  }
  EXPECT_TRUE(v.size() < cap);
}

TEST(VectorTest, SwapTest) {
  s21::vector<int> v1 = {1, 2, 3, 4, 5};
  s21::vector<int> v2 = {6, 7, 8, 9, 10};

  v1.swap(v2);
  int expected_v2[] = {1, 2, 3, 4, 5};
  int expected_v1[] = {6, 7, 8, 9, 10};

  for (size_t i = 0; i < v1.size(); i++) {
    EXPECT_EQ(v1[i], expected_v1[i]);
    EXPECT_EQ(v2[i], expected_v2[i]);
  }
}

TEST(VectorTest, AssignmentOperator) {
  s21::vector<int> v1 = {1, 2, 3, 4, 5};
  s21::vector<int> v2 = v1;
  EXPECT_EQ(v1.size(), v2.size());
  for (size_t i = 0; i < v1.size(); i++) {
    EXPECT_EQ(v1[i], v2[i]);
  }
}

TEST(VectorTest, At_OutOfRange) {
  s21::vector<int> v = {1, 2, 3, 4, 5};
  EXPECT_THROW(v.at(5), std::out_of_range);
}

TEST(VectorTest, Erase_OutOfRange) {
  s21::vector<int> v = {1, 2, 3, 4, 5};
  EXPECT_THROW(v.erase(v.begin() + 6), std::out_of_range);
}
TEST(VectorTest, AssignmentOperatorToItself) {
  s21::vector<int> v1 = {1, 2, 3, 4, 5};
  s21::vector<int> v2 = v1;
  v1 = v2;
  EXPECT_EQ(v1.size(), v2.size());
  for (size_t i = 0; i < v1.size(); i++) EXPECT_EQ(v1[i], v2[i]);
}
TEST(VectorTest, FrontBackForEmptyVector) {
  s21::vector<std::string> empty_vec;
  EXPECT_THROW(empty_vec.front(), std::out_of_range);
  EXPECT_THROW(empty_vec.back(), std::out_of_range);
}
TEST(VectorTest, CapacityInitializationCheck) {
  s21::vector<double> vec(5);
  EXPECT_EQ(vec.capacity(), 5);
}
TEST(VectorTest, SwapWithEmptyVector) {
  s21::vector<int> vec = {1, 2, 3};
  s21::vector<int> empty_vec;
  vec.swap(empty_vec);
  EXPECT_EQ(vec.size(), 0);
  EXPECT_EQ(empty_vec.size(), 3);
}
TEST(VectorTest, InsertInEmptyVector) {
  s21::vector<int> empty_vec;
  empty_vec.insert(empty_vec.begin(), 3);
  EXPECT_EQ(empty_vec.front(), 3);
  EXPECT_EQ(empty_vec.size(), 1);
}

TEST(VectorTest, EraseInEmptyVector) {
  s21::vector<int> empty_vec;
  EXPECT_THROW(empty_vec.erase(empty_vec.begin()), std::out_of_range);
}

TEST(VectorTest, InsertAtIteratorBeyondEnd) {
  s21::vector<int> vec = {1, 2, 3};
  EXPECT_THROW(vec.insert(vec.end() + 1, 4), std::out_of_range);
}

TEST(VectorTest, IteratorPostfixOperators) {
  s21::vector<int> vec = {1, 2, 3, 4};
  s21::vector<int>::iterator iter = vec.begin();
  ASSERT_EQ(*iter, 1);
  iter++;
  ASSERT_EQ(*iter, 2);
  iter--;
  ASSERT_EQ(*iter, 1);
}

TEST(VectorTest, InsertManyTest) {
  s21::vector<int> test_vector{0, 1, 2, 3, 4, 5};
  test_vector.insert_many(test_vector.cbegin() + 2, 10, 20, 30);
  ASSERT_EQ(test_vector[2], 10);
  ASSERT_EQ(test_vector[3], 20);
  ASSERT_EQ(test_vector[4], 30);
  ASSERT_EQ(test_vector[5], 2);
  ASSERT_EQ(test_vector[6], 3);
  ASSERT_EQ(test_vector[7], 4);
  ASSERT_EQ(test_vector.size(), 9);
}
TEST(VectorTest, InsertManyBackTest) {
  s21::vector<int> test_vector{1, 2, 3, 4, 5};
  test_vector.insert_many_back(10, 20, 30);
  ASSERT_EQ(test_vector[0], 1);
  ASSERT_EQ(test_vector[1], 2);
  ASSERT_EQ(test_vector[2], 3);
  ASSERT_EQ(test_vector[3], 4);
  ASSERT_EQ(test_vector[4], 5);
  ASSERT_EQ(test_vector[5], 10);
  ASSERT_EQ(test_vector[6], 20);
  ASSERT_EQ(test_vector[7], 30);
  ASSERT_EQ(test_vector.size(), 8);
}

/*--->Array tests<---*/

TEST(S21ArrayTest, TestAt) {
  std::cout << "\n\n\033[1;32m";
  std::cout << "ARRAY TESTS";
  std::cout << "\033[0m\n\n";
  s21::array<int> int_array = {1, 2, 3, 4, 5};
  ASSERT_NO_THROW(int_array.at(3));
  ASSERT_THROW(int_array.at(5), std::out_of_range);

  s21::array<double> double_array = {1.1, 2.2, 3.3, 4.4, 5.5};
  ASSERT_NO_THROW(double_array.at(3));
  ASSERT_THROW(double_array.at(5), std::out_of_range);

  s21::array<std::string> string_array = {"one", "two", "three", "four",
                                          "five"};
  ASSERT_NO_THROW(string_array.at(2));
  ASSERT_THROW(string_array.at(5), std::out_of_range);
}

TEST(S21ArrayTest, TestSwap) {
  s21::array<int> int_array1 = {1, 2, 3, 4, 5};
  s21::array<int> int_array2 = {6, 7, 8, 9};
  ASSERT_NO_THROW(int_array1.swap(int_array2));

  s21::array<double> double_array1 = {1.1, 2.2, 3.3, 4.4, 5.5};
  s21::array<double> double_array2 = {6.6, 7.7, 8.8, 9.9};
  ASSERT_NO_THROW(double_array1.swap(double_array2));

  s21::array<std::string> string_array1 = {"one", "two", "three", "four",
                                           "five"};
  s21::array<std::string> string_array2 = {"six", "seven", "eight", "nine"};
  ASSERT_NO_THROW(string_array1.swap(string_array2));
}

TEST(S21ArrayTest, TestFrontBack) {
  s21::array<int> int_array = {1, 2, 3, 4, 5};
  ASSERT_EQ(int_array.front(), 1);
  ASSERT_EQ(int_array.back(), 5);

  s21::array<double> double_array = {1.1, 2.2, 3.3, 4.4, 5.5};
  ASSERT_EQ(double_array.front(), 1.1);
  ASSERT_EQ(double_array.back(), 5.5);

  s21::array<std::string> string_array = {"one", "two", "three", "four",
                                          "five"};
  ASSERT_EQ(string_array.front(), "one");
  ASSERT_EQ(string_array.back(), "five");

  s21::array<int> empty_array;
  ASSERT_THROW(empty_array.front(), std::out_of_range);
  ASSERT_THROW(empty_array.back(), std::out_of_range);
}

TEST(S21ArrayTest, TestFront) {
  s21::array<int> int_array = {1, 2, 3, 4, 5};
  ASSERT_NO_THROW(int_array.front());
  ASSERT_EQ(int_array.front(), 1);

  s21::array<double> double_array = {1.1, 2.2, 3.3, 4.4, 5.5};
  ASSERT_NO_THROW(double_array.front());
  ASSERT_EQ(double_array.front(), 1.1);

  s21::array<std::string> string_array = {"one", "two", "three", "four",
                                          "five"};
  ASSERT_NO_THROW(string_array.front());
  ASSERT_EQ(string_array.front(), "one");
}

TEST(S21ArrayTest, TestBack) {
  s21::array<int> int_array = {1, 2, 3, 4, 5};
  ASSERT_NO_THROW(int_array.back());
  ASSERT_EQ(int_array.back(), 5);

  s21::array<double> double_array = {1.1, 2.2, 3.3, 4.4, 5.5};
  ASSERT_NO_THROW(double_array.back());
  ASSERT_EQ(double_array.back(), 5.5);

  s21::array<std::string> string_array = {"one", "two", "three", "four",
                                          "five"};
  ASSERT_NO_THROW(string_array.back());
  ASSERT_EQ(string_array.back(), "five");
}

TEST(S21ArrayTest, TestBeginEnd) {
  s21::array<int> int_array = {1, 2, 3, 4, 5};
  ASSERT_NE(int_array.begin(), int_array.end());

  s21::array<double> double_array = {1.1, 2.2, 3.3, 4.4, 5.5};
  ASSERT_NE(double_array.begin(), double_array.end());

  s21::array<std::string> string_array = {"one", "two", "three", "four",
                                          "five"};
  ASSERT_NE(string_array.begin(), string_array.end());
}

TEST(S21ArrayTest, TestEmpty) {
  s21::array<int> int_array;
  ASSERT_TRUE(int_array.empty());

  s21::array<double> double_array;
  ASSERT_TRUE(double_array.empty());

  s21::array<std::string> string_array;
  ASSERT_TRUE(string_array.empty());
}

TEST(S21ArrayTest, TestSize) {
  s21::array<int> int_array = {1, 2, 3, 4, 5};
  ASSERT_EQ(int_array.size(), 5);

  s21::array<double> double_array = {1.1, 2.2, 3.3, 4.4, 5.5};
  ASSERT_EQ(double_array.size(), 5);

  s21::array<std::string> string_array = {"one", "two", "three", "four",
                                          "five"};
  ASSERT_EQ(string_array.size(), 5);
}

TEST(S21ArrayTest, TestFill) {
  s21::array<int> int_array = {1, 2, 3, 4, 5};
  ASSERT_NO_THROW(int_array.fill(9));
  ASSERT_EQ(int_array.front(), 9);
  ASSERT_EQ(int_array.back(), 9);

  s21::array<double> double_array = {1.1, 2.2, 3.3, 4.4, 5.5};
  ASSERT_NO_THROW(double_array.fill(9.9));
  ASSERT_EQ(double_array.front(), 9.9);
  ASSERT_EQ(double_array.back(), 9.9);

  s21::array<std::string> string_array = {"one", "two", "three", "four",
                                          "five"};
  ASSERT_NO_THROW(string_array.fill("nine"));
  ASSERT_EQ(string_array.front(), "nine");
  ASSERT_EQ(string_array.back(), "nine");
}

TEST(S21ArrayTest, TestOperatorBrackets) {
  s21::array<int> int_array = {1, 2, 3, 4, 5};
  ASSERT_EQ(int_array[0], 1);
  ASSERT_EQ(int_array[4], 5);
  ASSERT_THROW(int_array[5], std::out_of_range);

  s21::array<double> double_array = {1.1, 2.2, 3.3, 4.4, 5.5};
  ASSERT_EQ(double_array[0], 1.1);
  ASSERT_EQ(double_array[4], 5.5);
  ASSERT_THROW(double_array[5], std::out_of_range);

  s21::array<std::string> string_array = {"one", "two", "three", "four",
                                          "five"};
  ASSERT_EQ(string_array[0], "one");
  ASSERT_EQ(string_array[4], "five");
  ASSERT_THROW(string_array[5], std::out_of_range);
}

TEST(S21ArrayTest, TestCopyAssignmentOperator) {
  s21::array<int> int_array1 = {1, 2, 3, 4, 5};
  s21::array<int> int_array2;
  ASSERT_NO_THROW(int_array2 = int_array1);
  ASSERT_EQ(int_array1[2], int_array2[2]);

  s21::array<double> double_array1 = {1.1, 2.2, 3.3, 4.4, 5.5};
  s21::array<double> double_array2;
  ASSERT_NO_THROW(double_array2 = double_array1);
  ASSERT_EQ(double_array1[2], double_array2[2]);

  s21::array<std::string> string_array1 = {"one", "two", "three", "four",
                                           "five"};
  s21::array<std::string> string_array2;
  ASSERT_NO_THROW(string_array2 = string_array1);
  ASSERT_EQ(string_array1[2], string_array2[2]);
}

TEST(S21ArrayTest, TestMoveAssignmentOperator) {
  s21::array<int> int_array1 = {1, 2, 3, 4, 5};
  s21::array<int> int_array2;
  ASSERT_NO_THROW(int_array2 = std::move(int_array1));
  ASSERT_EQ(int_array2[2], 3);
  ASSERT_EQ(int_array1.size(), 0);

  s21::array<double> double_array1 = {1.1, 2.2, 3.3, 4.4, 5.5};
  s21::array<double> double_array2;
  ASSERT_NO_THROW(double_array2 = std::move(double_array1));
  ASSERT_EQ(double_array2[2], 3.3);
  ASSERT_EQ(double_array1.size(), 0);

  s21::array<std::string> string_array1 = {"one", "two", "three", "four",
                                           "five"};
  s21::array<std::string> string_array2;
  ASSERT_NO_THROW(string_array2 = std::move(string_array1));
  ASSERT_EQ(string_array2[2], "three");
  ASSERT_EQ(string_array1.size(), 0);
}

TEST(S21ArrayTest, TestIteratorBeginEnd) {
  s21::array<int> int_array = {1, 2, 3, 4, 5};
  ASSERT_EQ(*(int_array.begin()), 1);
  ASSERT_EQ(*(int_array.end() - 1), 5);
  s21::array<int> int_array_empty;
  ASSERT_EQ(int_array_empty.begin(), int_array_empty.end());

  s21::array<double> double_array = {1.1, 2.2, 3.3, 4.4, 5.5};
  ASSERT_EQ(*(double_array.begin()), 1.1);
  ASSERT_EQ(*(double_array.end() - 1), 5.5);
  s21::array<double> double_array_empty;
  ASSERT_EQ(double_array_empty.begin(), double_array_empty.end());

  s21::array<std::string> string_array = {"one", "two", "three", "four",
                                          "five"};
  ASSERT_EQ(*(string_array.begin()), "one");
  ASSERT_EQ(*(string_array.end() - 1), "five");
  s21::array<std::string> string_array_empty;
  ASSERT_EQ(string_array_empty.begin(), string_array_empty.end());
}

TEST(S21ArrayTest, TestEmptyOnEmptyArrays) {
  s21::array<int> int_array;
  ASSERT_TRUE(int_array.empty());

  s21::array<double> double_array;
  ASSERT_TRUE(double_array.empty());

  s21::array<std::string> string_array;
  ASSERT_TRUE(string_array.empty());
}

TEST(S21ArrayTest, TestFillWithEmptyArray) {
  s21::array<int> int_array;
  ASSERT_NO_THROW(int_array.fill(9));

  s21::array<double> double_array;
  ASSERT_NO_THROW(double_array.fill(9.9));

  s21::array<std::string> string_array;
  ASSERT_NO_THROW(string_array.fill("nine"));
}

TEST(S21ArrayTest, TestSwapContents) {
  s21::array<int> int_array1 = {1, 2, 3, 4, 5};
  s21::array<int> int_array2 = {6, 7, 8};

  int_array1.swap(int_array2);

  ASSERT_EQ(int_array1[0], 6);
  ASSERT_EQ(int_array1[2], 8);
  ASSERT_EQ(int_array2[0], 1);
  ASSERT_EQ(int_array2[4], 5);
}

TEST(S21ArrayTest, TestInvalidAt) {
  s21::array<int> int_array = {1, 2, 3, 4, 5};
  ASSERT_THROW(int_array.at(-1), std::out_of_range);
  ASSERT_THROW(int_array.at(50), std::out_of_range);
}

TEST(S21ArrayTest, TestInvalidOperatorBrackets) {
  s21::array<int> int_array = {1, 2, 3, 4, 5};
  ASSERT_THROW(int_array[-1], std::out_of_range);
  ASSERT_THROW(int_array[50], std::out_of_range);
}

TEST(S21ArrayTest, TestFillOnEmptyArray) {
  s21::array<int> int_array;
  ASSERT_NO_THROW(int_array.fill(9));
  ASSERT_TRUE(int_array.empty());
}

TEST(S21ArrayTest, TestSwapEmptyArrays) {
  s21::array<int> int_array1;
  s21::array<int> int_array2;
  ASSERT_NO_THROW(int_array1.swap(int_array2));
  ASSERT_TRUE(int_array1.empty());
  ASSERT_TRUE(int_array2.empty());
}

TEST(S21ArrayTest, TestSwapArrayWithEmpty) {
  s21::array<int> int_array1 = {1, 2, 3, 4, 5};
  s21::array<int> int_array2;
  ASSERT_NO_THROW(int_array1.swap(int_array2));
  ASSERT_TRUE(int_array1.empty());
  ASSERT_EQ(int_array2.size(), 5);
}
TEST(S21ArrayTest, TestIteratorsIncrementDecrement) {
  s21::array<int> int_array = {1, 2, 3, 4, 5};
  s21::array<int>::iterator iter = int_array.begin();
  ASSERT_EQ(*iter, 1);
  iter++;
  ASSERT_EQ(*iter, 2);
  iter--;
  ASSERT_EQ(*iter, 1);
}

TEST(S21ArrayTest, TestConstIterators) {
  s21::array<int> int_array = {1, 2, 3, 4, 5};
  s21::array<int>::iterator citer = int_array.begin();
  ASSERT_EQ(*citer, 1);
  citer++;
  ASSERT_EQ(*citer, 2);
  citer--;
  ASSERT_EQ(*citer, 1);
}

TEST(S21ArrayTest, TestIteratorsEquality) {
  s21::array<int> int_array = {1, 2, 3, 4, 5};

  s21::array<int>::iterator iter1 = int_array.begin();
  s21::array<int>::iterator iter2 = int_array.begin();

  ASSERT_TRUE(iter1 == iter2);
  iter2++;
  ASSERT_TRUE(iter1 != iter2);
}

TEST(S21ArrayTest, TestIteratorsArithmetic) {
  s21::array<int> int_array = {1, 2, 3, 4, 5};
  s21::array<int>::iterator iter = int_array.begin();

  s21::array<int>::iterator adv_iter = iter + 3;
  ASSERT_EQ(*adv_iter, 4);

  s21::array<int>::iterator rev_iter = adv_iter - 2;
  ASSERT_EQ(*rev_iter, 2);

  adv_iter -= 1;
  ASSERT_EQ(*adv_iter, 3);

  rev_iter += 2;
  ASSERT_EQ(*rev_iter, 4);
}

TEST(S21ArrayTest, TestMaxSize) {
  s21::array<int> int_array = {1, 2, 3, 4, 5};
  ASSERT_EQ(int_array.max_size(), 5);

  s21::array<int> empty_array;
  ASSERT_EQ(empty_array.max_size(), 0);
}

TEST(S21ArrayTest, TestData) {
  s21::array<int> int_array = {1, 2, 3, 4, 5};
  s21::array<int>::iterator data_ptr = int_array.data();
  ASSERT_TRUE(data_ptr != nullptr);
  ASSERT_EQ(*data_ptr, 1);

  s21::array<int> empty_array;
  data_ptr = empty_array.data();
  ASSERT_TRUE(data_ptr == nullptr);
}

/*--->Tree tests<---*/

TEST(RedBlackTreeTest, Insert_Size) {
  std::cout << "\n\n\033[1;32m";
  std::cout << "RED-BLACK TREE TESTS";
  std::cout << "\033[0m\n\n";
  s21::RedBlackTree<int> tree;
  EXPECT_TRUE(tree.isEmpty());
  EXPECT_EQ(tree.Size(), 0);
  tree.Insert(5);
  EXPECT_FALSE(tree.isEmpty());
  EXPECT_EQ(tree.Size(), 1);

  tree.Insert(10);
  EXPECT_EQ(tree.Size(), 2);
}

TEST(RedBlackTreeTest, Find_Erase) {
  s21::RedBlackTree<int> tree;
  tree.Insert(5);
  tree.Insert(10);

  auto it = tree.Find(5);
  EXPECT_NE(it, tree.End());
  EXPECT_EQ(*it, 5);

  tree.Erase(it);
  EXPECT_EQ(tree.Size(), 1);
  it = tree.Find(5);
  EXPECT_EQ(it, tree.End());
}

TEST(RedBlackTreeTest, Merge) {
  s21::RedBlackTree<int> tree1;
  tree1.Insert(5);
  tree1.Insert(10);

  s21::RedBlackTree<int> tree2;
  tree2.Insert(15);
  tree2.Insert(20);

  tree1.Merge(tree2);

  EXPECT_EQ(tree1.Size(), 4);
  EXPECT_EQ(tree2.Size(), 0);
}

TEST(RedBlackTreeTest, UpperBound) {
  s21::RedBlackTree<int> tree;
  tree.Insert(5);
  tree.Insert(10);
  tree.Insert(15);

  auto it = tree.UpperBound(7);
  EXPECT_NE(it, tree.End());
  EXPECT_EQ(*it, 10);
}

TEST(RedBlackTreeTest, Clear) {
  s21::RedBlackTree<int> tree;
  tree.Insert(5);
  tree.Insert(10);
  tree.Insert(15);

  EXPECT_EQ(tree.Size(), 3);
  tree.Clear();
  EXPECT_TRUE(tree.isEmpty());
  EXPECT_EQ(tree.Size(), 0);
}

TEST(RedBlackTreeTest, InsertDuplicateKeys) {
  s21::RedBlackTree<int> tree;
  tree.Insert(5);
  tree.Insert(5);
  tree.Insert(5);
  EXPECT_EQ(tree.Size(), 3);
}

TEST(RedBlackTreeTest, ReverseOrderIteration) {
  s21::RedBlackTree<int> tree;
  for (int i = 9; i >= 0; --i) {
    tree.Insert(i);
  }

  int expectedValue = 0;
  for (auto it = tree.Begin(); it != tree.End(); ++it) {
    EXPECT_EQ(*it, expectedValue);
    ++expectedValue;
  }
}

TEST(RedBlackTreeTest, LowerBoundCheck) {
  s21::RedBlackTree<int> tree;
  tree.Insert(5);
  tree.Insert(10);
  tree.Insert(15);

  auto it = tree.LowerBound(7);
  EXPECT_NE(it, tree.End());
  EXPECT_EQ(*it, 10);

  it = tree.LowerBound(5);
  EXPECT_EQ(*it, 5);
}

TEST(RedBlackTreeTest, EraseAndBalance) {
  s21::RedBlackTree<int> tree;
  tree.Insert(5);
  tree.Insert(10);
  tree.Insert(15);
  tree.Insert(20);
  tree.Insert(25);

  auto it = tree.Find(15);
  tree.Erase(it);

  EXPECT_EQ(tree.Size(), 4);
  EXPECT_EQ(*tree.Find(5), 5);
  EXPECT_EQ(*tree.Find(10), 10);
  EXPECT_EQ(*tree.Find(20), 20);
  EXPECT_EQ(*tree.Find(25), 25);
  it = tree.Find(15);
  EXPECT_EQ(it, tree.End());
}

TEST(RedBlackTreeTest, CopyConstructor) {
  s21::RedBlackTree<int> original;
  original.Insert(5);
  original.Insert(10);
  original.Insert(15);

  s21::RedBlackTree<int> copy = original;

  EXPECT_EQ(copy.Size(), 3);
  EXPECT_EQ(*copy.Find(5), 5);
  EXPECT_EQ(*copy.Find(10), 10);
  EXPECT_EQ(*copy.Find(15), 15);

  EXPECT_EQ(original.Size(), 3);
  EXPECT_EQ(*original.Find(5), 5);
}

TEST(RedBlackTreeTest, AssignmentOperator) {
  s21::RedBlackTree<int> original;
  original.Insert(5);
  original.Insert(10);
  original.Insert(15);

  s21::RedBlackTree<int> assigned;
  assigned = original;

  EXPECT_EQ(assigned.Size(), 3);
  EXPECT_EQ(*assigned.Find(5), 5);
  EXPECT_EQ(*assigned.Find(10), 10);
  EXPECT_EQ(*assigned.Find(15), 15);

  EXPECT_EQ(original.Size(), 3);
  EXPECT_EQ(*original.Find(5), 5);
}

TEST(RedBlackTreeTest, InsertAndFindNegativeNumbers) {
  s21::RedBlackTree<int> tree;
  tree.Insert(-5);
  tree.Insert(-10);
  EXPECT_EQ(tree.Size(), 2);
  EXPECT_EQ(*tree.Find(-5), -5);
  EXPECT_EQ(*tree.Find(-10), -10);
}

TEST(RedBlackTreeTest, MoveConstructorAndAssignment) {
  s21::RedBlackTree<int> original;
  original.Insert(5);
  original.Insert(10);
  original.Insert(15);

  s21::RedBlackTree<int> moved = std::move(original);

  EXPECT_EQ(moved.Size(), 3);
  EXPECT_EQ(*moved.Find(5), 5);
  EXPECT_EQ(*moved.Find(10), 10);
  EXPECT_EQ(*moved.Find(15), 15);

  s21::RedBlackTree<int> anotherTree;
  anotherTree.Insert(20);

  anotherTree = std::move(moved);

  EXPECT_EQ(anotherTree.Size(), 3);
  EXPECT_EQ(*anotherTree.Find(5), 5);
  EXPECT_EQ(*anotherTree.Find(10), 10);
  EXPECT_EQ(*anotherTree.Find(15), 15);
}

TEST(RedBlackTreeTest, OperationsOnEmptyTree) {
  s21::RedBlackTree<int> tree;

  EXPECT_TRUE(tree.isEmpty());
  EXPECT_EQ(tree.Size(), 0);
  EXPECT_EQ(tree.Find(5), tree.End());
  EXPECT_NO_THROW(tree.Clear());
  auto it = tree.Begin();
  EXPECT_EQ(it, tree.End());
  EXPECT_NO_THROW(tree.Erase(it));
}

TEST(RedBlackTreeTest, EraseVariousNodes) {
  s21::RedBlackTree<int> tree;
  tree.Insert(30);
  tree.Insert(20);
  tree.Insert(40);
  tree.Insert(10);
  tree.Insert(25);
  tree.Insert(35);
  tree.Insert(50);

  EXPECT_EQ(tree.Size(), 7);

  tree.Erase(tree.Find(30));
  EXPECT_EQ(tree.Size(), 6);
  EXPECT_EQ(tree.Find(30), tree.End());

  tree.Erase(tree.Find(20));
  EXPECT_EQ(tree.Size(), 5);
  EXPECT_EQ(tree.Find(20), tree.End());

  tree.Erase(tree.Find(40));
  EXPECT_EQ(tree.Size(), 4);
  EXPECT_EQ(tree.Find(40), tree.End());

  tree.Erase(tree.Find(10));
  EXPECT_EQ(tree.Size(), 3);
  EXPECT_EQ(tree.Find(10), tree.End());
}

TEST(RedBlackTreeTest, ExtractNode) {
  s21::RedBlackTree<int> tree;
  tree.Insert(30);
  tree.Insert(20);
  tree.Insert(40);
  tree.Insert(10);
  tree.Insert(25);
  tree.Insert(35);
  tree.Insert(50);

  EXPECT_EQ(tree.Size(), 7);

  tree.Erase(tree.Find(30));

  EXPECT_EQ(tree.Size(), 6);

  EXPECT_EQ(tree.Find(30), tree.End());
}

TEST(RedBlackTreeTest, MergeAndFindElements) {
  s21::RedBlackTree<int> tree1;
  tree1.Insert(5);
  tree1.Insert(10);

  s21::RedBlackTree<int> tree2;
  tree2.Insert(15);
  tree2.Insert(20);

  tree1.Merge(tree2);

  EXPECT_EQ(tree1.Size(), 4);
  EXPECT_EQ(tree2.Size(), 0);

  EXPECT_NE(tree1.Find(5), tree1.End());
  EXPECT_NE(tree1.Find(10), tree1.End());
  EXPECT_NE(tree1.Find(15), tree1.End());
  EXPECT_NE(tree1.Find(20), tree1.End());
}

TEST(RedBlackTreeTest, DestroyFunctionality) {
  s21::RedBlackTree<int> tree;
  tree.Insert(5);
  tree.Insert(10);

  tree.Clear();

  EXPECT_TRUE(tree.isEmpty());
  EXPECT_EQ(tree.Size(), 0);
}

TEST(RedBlackTreeTest, InitializeHeadFunctionality) {
  s21::RedBlackTree<int> tree;

  EXPECT_TRUE(tree.isEmpty());
  EXPECT_EQ(tree.Size(), 0);
}

TEST(RedBlackTreeTest, RandomInsertAndFind) {
  s21::RedBlackTree<int> tree;

  for (int i = 0; i < 1000; ++i) {
    tree.Insert(i);
  }

  for (int i = 0; i < 1000; ++i) {
    auto it = tree.Find(i);
    EXPECT_NE(it, tree.End());
    EXPECT_EQ(*it, i);
  }
}

int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
