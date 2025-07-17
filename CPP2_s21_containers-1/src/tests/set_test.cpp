#include <gtest/gtest.h>

#include <set>

#include "../set/s21_set.h"

TEST(set_constructor, no_arg) {
  s21::set<int> _set;
  EXPECT_EQ(_set.empty(), 1);
}

TEST(set_constructor, initializer_list) {
  s21::set<int> _set({11, 2, 99, 0});
  EXPECT_EQ(_set.empty(), 0);
}

TEST(set_constructor, copy) {
  s21::set<int> _set({11, 2, 99, 0});
  s21::set<int> set_copy(_set);
  auto j = set_copy.begin();
  for (auto i = _set.begin(); i != _set.end(); ++i) {
    ASSERT_TRUE(i->key == j->key);
    ++j;
  }
}

TEST(set_constructor, move) {
  s21::set<int> _set({11, 2, 99, 0});
  s21::set<int> set_copy(_set);
  s21::set<int> set_moved(std::move(_set));
  auto j = set_moved.begin();
  for (auto i = set_copy.begin(); i != set_copy.end(); ++i) {
    ASSERT_TRUE(i->key == j->key);
    ++j;
  }
  EXPECT_EQ(_set.empty(), 1);
}

TEST(set_operator, move_assignment) {
  s21::set<std::string> first({"this", "world", "is mine"});
  s21::set<std::string> copy(first);
  s21::set<std::string> second;
  second = std::move(first);
  auto j = second.begin();
  for (auto i = copy.begin(); i != copy.end(); ++i) {
    ASSERT_TRUE(i->key == j->key);
    ++j;
  }
  EXPECT_EQ(first.empty(), 1);
}

TEST(set_iterator, begin) {
  s21::set<std::string> _set({"this", "world", "is mine"});
  auto i = _set.begin();
  EXPECT_EQ(i->key, "is mine");
}

TEST(set_iterator, end) {
  s21::set<std::string> _set({"this", "world", "is mine"});
  auto i = _set.end();
  EXPECT_EQ(i->key, "world");
}

TEST(set_iterator_operator, increment) {
  s21::set<std::string> _set({"this", "world", "is mine"});
  auto i = _set.begin();
  ++i;
  EXPECT_EQ(i->key, "this");
  i++;
  EXPECT_EQ(i->key, "world");
}

TEST(set_iterator_operator, decrement_test_0) {
  s21::set<int> _set({5, 4, 1, 0, 2, 1, 4, 3, 3, 2});
  auto i = _set.end();
  --i;
  EXPECT_EQ(i->key, 5);
  i--;
  EXPECT_EQ(i->key, 4);
}

TEST(set_iterator_operator, decrement_test_1) {
  s21::set<int> _set({5, 4, 1, 0, 2, 1, 4, 3, 3, 2});
  auto i = _set.end();
  int j = 5;
  while (i != _set.begin()) {
    --i;
    EXPECT_EQ(i->key, j);
    --j;
  }
}

TEST(set_size, size_check) {
  s21::set<int> _set({5, 4, 1, 0, 2, 1, 4, 3, 3, 2});
  EXPECT_EQ(_set.size(), 6);
  _set.clear();
  EXPECT_EQ(_set.empty(), 1);
  EXPECT_EQ(_set.max_size(), std::numeric_limits<size_t>::max() / sizeof(int));
  EXPECT_EQ(_set.size(), 0);
}

TEST(set_insert, insert_test_0) {
  s21::set<int> _set;
  _set.insert(9);
  auto i = _set.begin();
  EXPECT_EQ(i->key, 9);
}

TEST(set_insert, insert_test_1) {
  s21::set<int> _set({5, 4, 1, 0, 2, 1, 4, 3, 3, 2});
  _set.insert(90);
  EXPECT_EQ(_set.contains(90), 1);
}

TEST(set_insert, insert_many_test_0) {
  s21::set<int> _set({5, 4, 1, 0, 2, 1, 4, 3, 3, 2});
  auto v = _set.insert_many(1, 90, 10);
  EXPECT_EQ(_set.contains(90), 1);
  EXPECT_EQ(_set.contains(10), 1);
  EXPECT_EQ(v[0].second, 0);
  EXPECT_EQ(v[1].second, 1);
  EXPECT_EQ(v[2].second, 1);
}

TEST(set_erase, erase_test_0) {
  s21::set<int> _set({5, 4, 1, 0, 2, 1, 4, 3, 3, 2});
  auto i = _set.insert(8).first;
  _set.erase(i);
  EXPECT_EQ(_set.contains(8), 0);
}

TEST(set_swap, swap_test_0) {
  s21::set<int> _set({5, 4, 1, 0, 12, 1, 4, 3, 2});
  s21::set<int> set_copy(_set);
  s21::set<int> _s({9, 20, 30, 40});
  s21::set<int> s_copy(_s);
  _set.swap(_s);
  auto it = _s.begin();
  for (auto i = set_copy.begin(); i != set_copy.end(); ++i) {
    EXPECT_EQ(i->key, it->key);
    ++it;
  }
  it = _set.begin();
  for (auto i = s_copy.begin(); i != s_copy.end(); ++i) {
    EXPECT_EQ(i->key, it->key);
    ++it;
  }
}

TEST(set_merge, merge_test_0) {
  s21::set<int> _set({5, 0, 12, 1, 4, 3, 2});
  s21::set<int> _s({13, 10, 6, 9, 7, 11, 8});
  _set.merge(_s);
  int i = 0;
  for (auto it = _set.begin(); it != _set.end(); ++it) EXPECT_EQ(it->key, i++);
}

TEST(set_contains, contains_test_0) {
  s21::set<int> _set({5, 0, 12, 1, 4, 3, 2});
  _set.insert(33);
  EXPECT_EQ(_set.contains(33), 1);
  EXPECT_EQ(_set.contains(36), 0);
}

TEST(set_find, find_test_0) {
  s21::set<int> _set({5, 0, 12, 1, 4, 3, 2});
  int k = 5;
  auto i = _set.find(k);
  for (auto it = _set.begin(); it != _set.end(); ++it) {
    if (it->key == k) {
      EXPECT_EQ(it, i);
    }
  }
}

