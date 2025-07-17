#include <gtest/gtest.h>

#include <vector>

#include "../s21_containers.h"

using std::cin;
using std::cout;
using std::endl;

TEST(S21_containers_vector, iterator) {
  s21::vector<int> vector_1 = {11, 22, 33, 44, 55};
  s21::vector<int> vector_2 = {11, 77, 88, 99};
  EXPECT_EQ(*vector_1.iter, 11);
  EXPECT_EQ(*vector_2.iter, 11);
  EXPECT_EQ(*vector_1.iter == *vector_2.iter, true);
  vector_1.iter++;
  EXPECT_TRUE(*vector_1.iter != *vector_1.begin());
  EXPECT_EQ(*vector_1.iter != *vector_2.iter, true);
  EXPECT_EQ(*vector_1.iter, 22);
  vector_1.iter--;
  EXPECT_EQ(*vector_1.iter, 11);
  EXPECT_TRUE(*vector_1.iter == *vector_1.begin());
}

TEST(S21_containers_vector, default_constructor) {
  s21::vector<int> vector_1;
  ASSERT_EQ(0, vector_1.size());
}

TEST(S21_containers_vector, parameterized_constructor) {
  s21::vector<int> vector_1(3);
  ASSERT_EQ(3, vector_1.size());

  s21::vector<int> vector_2(0);
  ASSERT_EQ(0, vector_2.size());
}

TEST(S21_containers_vector, list_constructor) {
  s21::vector<int> vector_1 = {11, 22, 33, 44, 55};

  ASSERT_EQ(5, vector_1.size());

  ASSERT_EQ(11, vector_1.at(0));
  ASSERT_EQ(22, vector_1.at(1));
  ASSERT_EQ(33, vector_1.at(2));
  ASSERT_EQ(44, vector_1.at(3));
  ASSERT_EQ(55, vector_1.at(4));

  s21::vector<int> vector_2 = {};
  ASSERT_EQ(0, vector_2.size());
}

TEST(S21_containers_vector, copy_constructor) {
  s21::vector<int> vector_1 = {99, 88, 77};
  s21::vector<int> vector_copy(vector_1);

  ASSERT_EQ(99, vector_copy[0]);
  ASSERT_EQ(88, vector_copy[1]);
  ASSERT_EQ(77, vector_copy[2]);
}

TEST(S21_containers_vector, move_constructor) {
  s21::vector<int> vector_1 = {11, 22, 33, 44, 55};
  s21::vector<int> vector_moved(std::move(vector_1));

  ASSERT_EQ(11, vector_moved[0]);
  ASSERT_EQ(22, vector_moved[1]);
  ASSERT_EQ(33, vector_moved[2]);
  ASSERT_EQ(44, vector_moved[3]);
  ASSERT_EQ(55, vector_moved[4]);

  ASSERT_EQ(5, vector_moved.size());

  ASSERT_EQ(0, vector_1.size());
}

TEST(S21_containers_vector, operator_equals) {
  s21::vector<int> vector_1 = {1, 2, 3, 4};
  s21::vector<int> vector_moved;
  vector_moved = std::move(vector_1);

  ASSERT_EQ(1, vector_moved[0]);
  ASSERT_EQ(2, vector_moved[1]);
  ASSERT_EQ(3, vector_moved[2]);
  ASSERT_EQ(4, vector_moved[3]);

  ASSERT_EQ(4, vector_moved.size());

  ASSERT_EQ(0, vector_1.size());
}

TEST(S21_containers_vector, at) {
  s21::vector<int> vector_1 = {11, 22, 33, 44, 55};

  ASSERT_EQ(11, vector_1.at(0));
  ASSERT_EQ(22, vector_1.at(1));
  ASSERT_EQ(33, vector_1.at(2));
  ASSERT_EQ(44, vector_1.at(3));
  ASSERT_EQ(55, vector_1.at(4));

  EXPECT_THROW({ vector_1.at(5); }, std::out_of_range);
}

TEST(S21_containers_vector, access_brackets) {
  s21::vector<int> vector_1 = {1, 2, 3, 4, 5};

  ASSERT_EQ(1, vector_1[0]);
  ASSERT_EQ(2, vector_1[1]);
  ASSERT_EQ(3, vector_1[2]);
  ASSERT_EQ(4, vector_1[3]);
  ASSERT_EQ(5, vector_1[4]);
}

TEST(S21_containers_vector, front) {
  s21::vector<int> vector_1 = {1, 2, 3, 4, 5};
  ASSERT_EQ(1, vector_1.front());

  s21::vector<int> empty_vector = {};
  EXPECT_THROW({ empty_vector.front(); }, std::out_of_range);
}

TEST(S21_containers_vector, back) {
  s21::vector<int> vector_1 = {1, 2, 3, 4, 5};
  ASSERT_EQ(5, vector_1.back());

  s21::vector<int> empty_vector = {};
  EXPECT_THROW({ empty_vector.back(); }, std::out_of_range);
}

TEST(S21_containers_vector, data) {
  s21::vector<int> vector_1 = {11, 22, 33, 44, 55};
  s21::vector<int> vector_empty;

  ASSERT_EQ(11, *(vector_1.data()));
  ASSERT_EQ(nullptr, vector_empty.data());
}

TEST(S21_containers_vector, begin) {
  std::vector<int> vector_1 = {77, 88, 99};
  ASSERT_EQ(77, *(vector_1.begin()));
}

TEST(S21_containers_vector, end) {
  s21::vector<int> vector_1 = {11, 22, 33};
  ASSERT_EQ(33, *(vector_1.end() - 1));
}

TEST(S21_containers_vector, empty) {
  s21::vector<int> empty_vector;
  s21::vector<int> not_empty_vector = {1, 2, 3};

  ASSERT_EQ(1, empty_vector.empty());
  ASSERT_EQ(0, not_empty_vector.empty());
}

TEST(S21_containers_vector, size) {
  s21::vector<int> vector_1 = {11, 22, 33};
  s21::vector<int> vector_2(5);
  s21::vector<int> empty_vector;

  ASSERT_EQ(3, vector_1.size());
  ASSERT_EQ(5, vector_2.size());
  ASSERT_EQ(0, empty_vector.size());
}

TEST(S21_containers_vector, max_size) {
  std::vector<int> vector_1 = {11, 22, 33};
  std::vector<double> vector_2 = {2.5, 7.123};

  s21::vector<int> vector_3 = {11, 22, 33};
  s21::vector<double> vector_4 = {2.5, 7.123};

  ASSERT_EQ(vector_1.max_size(), vector_3.max_size());
  ASSERT_EQ(vector_2.max_size(), vector_4.max_size());
}

TEST(S21_containers_vector, reserve) {
  s21::vector<int> vector_1 = {1, 2, 3, 4};
  vector_1.reserve(10);

  ASSERT_EQ(10, vector_1.capacity());
}

TEST(S21_containers_vector, capacity) {
  s21::vector<int> vector_1 = {1, 2, 3};
  s21::vector<double> vector_2(20);

  ASSERT_EQ(3, vector_1.capacity());
  ASSERT_EQ(20, vector_2.capacity());
}

TEST(S21_containers_vector, shrink_to_fit) {
  s21::vector<int> vector_1 = {1, 2, 3, 4, 5};
  vector_1.reserve(10);
  ASSERT_EQ(10, vector_1.capacity());

  vector_1.shrink_to_fit();
  ASSERT_EQ(5, vector_1.capacity());
}

TEST(S21_containers_vector, clear) {
  s21::vector<int> vector_1 = {11, 22, 33};
  vector_1.clear();
  s21::vector<double> vector_2 = {11.89, 22.78};
  vector_2.clear();
  s21::vector<char> vector_3 = {11, 22, 33, 44};
  vector_3.clear();
  ASSERT_EQ(0, vector_1.size());
  ASSERT_EQ(3, vector_1.capacity());
  ASSERT_EQ(0, vector_2.size());
  ASSERT_EQ(2, vector_2.capacity());
  ASSERT_EQ(0, vector_3.size());
  ASSERT_EQ(4, vector_3.capacity());
}

TEST(S21_containers_vector, insert) {
  s21::vector<int> vector_1 = {1, 2, 3, 4, 5};
  vector_1.insert(vector_1.begin(), 100);
  ASSERT_EQ(100, vector_1[0]);
  ASSERT_EQ(6, vector_1.size());

  s21::vector<int> vector_2 = {10, 20, 30, 40};
  vector_2.insert(vector_2.end(), 99);
  ASSERT_EQ(99, vector_2[4]);
  ASSERT_EQ(5, vector_2.size());

  s21::vector<int> vector_3 = {1, 2, 3, 4, 5, 6, 7, 8, 9};
  vector_3.insert(vector_3.begin() + 3, 1000);
  ASSERT_EQ(1000, vector_3[3]);
  ASSERT_EQ(10, vector_3.size());
}

TEST(S21_containers_vector, erase) {
  s21::vector<int> vector_1 = {11, 22, 33, 44, 55};

  ASSERT_EQ(5, vector_1.size());
  vector_1.erase(vector_1.begin() + 2);

  ASSERT_EQ(4, vector_1.size());
  ASSERT_EQ(5, vector_1.capacity());
  ASSERT_EQ(vector_1.at(0), 11);
  ASSERT_EQ(vector_1.at(1), 22);
  ASSERT_EQ(vector_1.at(2), 44);
  ASSERT_EQ(vector_1.at(3), 55);
}

TEST(S21_containers_vector, push_back) {
  s21::vector<int> vector_1 = {1, 2, 3};
  vector_1.push_back(400);

  ASSERT_EQ(400, vector_1[3]);
  ASSERT_EQ(4, vector_1.size());

  s21::vector<int> vector_2;
  vector_2.push_back(33);
  ASSERT_EQ(33, vector_2[0]);
  ASSERT_EQ(1, vector_2.size());
}

TEST(S21_containers_vector, pop_back) {
  s21::vector<int> vector_1 = {1, 2, 3};
  vector_1.pop_back();

  ASSERT_EQ(2, vector_1.size());
}

TEST(S21_containers_vector, swap) {
  s21::vector<int> vector_1 = {1, 2, 3};
  s21::vector<int> vector_2 = {99, 88, 77, 66};

  vector_1.swap(vector_2);

  ASSERT_EQ(4, vector_1.size());
  ASSERT_EQ(99, vector_1[0]);

  ASSERT_EQ(3, vector_2.size());
  ASSERT_EQ(1, vector_2[0]);
}

TEST(S21_containers_vector, insert_many) {
  s21::vector<int> vector_1 = {1, 2, 3, 4, 5};
  vector_1.insert_many(vector_1.begin(), 11, 12, 13);

  ASSERT_EQ(8, vector_1.size());
  ASSERT_EQ(11, vector_1[0]);
  ASSERT_EQ(12, vector_1[1]);
  ASSERT_EQ(13, vector_1[2]);

  s21::vector<int> vector_2 = {0, 0, 0};
  vector_2.insert_many(vector_2.begin() + 1, 100, 200);

  ASSERT_EQ(5, vector_2.size());
  ASSERT_EQ(0, vector_2[0]);
  ASSERT_EQ(100, vector_2[1]);
  ASSERT_EQ(200, vector_2[2]);
  ASSERT_EQ(0, vector_2[3]);
}

TEST(S21_containers_vector, insert_many_back) {
  s21::vector<int> vector_1 = {11, 22, 33, 44, 55};
  vector_1.insert_many_back(100, 200, 300);

  ASSERT_EQ(8, vector_1.size());
  ASSERT_EQ(100, vector_1[5]);
  ASSERT_EQ(200, vector_1[6]);
  ASSERT_EQ(300, vector_1[7]);

  s21::vector<int> vector_2;
  vector_2.insert_many_back(88, 99);
  ASSERT_EQ(2, vector_2.size());
  ASSERT_EQ(88, vector_2[0]);
  ASSERT_EQ(99, vector_2[1]);
}
