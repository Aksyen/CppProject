#include <gtest/gtest.h>

#include "../queue/s21_queue.h"

TEST(Queue_Constructor, Default) {
  s21::queue<int> int_q;
  s21::queue<double> double_q;

  EXPECT_EQ(int_q.empty(), 1);
  EXPECT_EQ(double_q.empty(), 1);
}

TEST(Queue_Constructor, Initializer_List) {
  s21::queue<int> int_q = {1, 2, 3};

  EXPECT_EQ(int_q.empty(), 0);
}

TEST(Queue_Constructor, Copy) {
  s21::queue<int> int_q1 = {1, 2, 3};
  s21::queue<int> int_q2(int_q1);

  EXPECT_EQ(int_q2.empty(), 0);
}

TEST(Queue_Constructor, Move) {
  s21::queue<int> int_q1 = {1, 2, 3};
  s21::queue<int> int_q2(std::move(int_q1));

  EXPECT_EQ(int_q2.empty(), 0);
  EXPECT_EQ(int_q1.empty(), 1);
}

TEST(Queue_Constructor, Operator_eq) {
  s21::queue<int> int_q1 = {1, 2, 3};
  s21::queue<int> int_q2;
  int_q2 = std::move(int_q1);

  EXPECT_EQ(int_q2.empty(), 0);
}

// element access

TEST(Queue_Element_Access, Front) {
  s21::queue<int> int_q = {1, 2, 3};

  EXPECT_EQ(int_q.front(), 1);
}

TEST(Queue_Element_Access, Front_Empty) {
  s21::queue<int> int_q;

  EXPECT_THROW(int_q.front(), std::out_of_range);
}

TEST(Queue_Element_Access, Back) {
  s21::queue<int> int_q = {1, 2, 3};

  EXPECT_EQ(int_q.back(), 3);
}

TEST(Queue_Element_Access, Back_Empty) {
  s21::queue<int> int_q;

  EXPECT_THROW(int_q.back(), std::out_of_range);
}

// capacity

TEST(Queue_Capacity, Empty) {
  s21::queue<int> int_q1 = {1, 2, 3};
  s21::queue<int> int_q2;

  EXPECT_EQ(int_q1.empty(), 0);
  EXPECT_EQ(int_q2.empty(), 1);
}

TEST(Queue_Capacity, Size) {
  s21::queue<int> int_q1 = {1, 2, 3};
  s21::queue<int> int_q2;

  EXPECT_EQ(int_q1.size(), 3);
  EXPECT_EQ(int_q2.size(), 0);
}

// modifiers

TEST(Queue_Modifiers, Push) {
  s21::queue<int> int_q = {1, 2, 3};
  int_q.push(7);

  EXPECT_EQ(int_q.size(), 4);
  EXPECT_EQ(int_q.back(), 7);
}

TEST(Queue_Modifiers, Push_Empty) {
  s21::queue<int> int_q;
  int_q.push(7);

  EXPECT_EQ(int_q.empty(), 0);
  EXPECT_EQ(int_q.size(), 1);
}

TEST(Queue_Modifiers, Pop) {
  s21::queue<int> int_q = {1, 2, 3};
  int_q.pop();

  EXPECT_EQ(int_q.front(), 2);
}

TEST(Queue_Modifiers, Pop_Empty) {
  s21::queue<int> int_q;

  EXPECT_THROW(int_q.pop(), std::out_of_range);
}

TEST(Queue_Modifiers, Swap) {
  s21::queue<int> int_q1 = {1, 2, 3};
  s21::queue<int> int_q2;

  EXPECT_EQ(int_q1.empty(), 0);
  EXPECT_EQ(int_q2.empty(), 1);

  int_q1.swap(int_q2);

  EXPECT_EQ(int_q1.empty(), 1);
  EXPECT_EQ(int_q2.empty(), 0);
}

TEST(Queue_Insert_Many, Insert_Many_Back) {
  s21::queue<int> int_q = {1, 2, 3};
  int_q.insert_many_back(4, 5, 6);

  EXPECT_EQ(int_q.size(), 6);
  EXPECT_EQ(int_q.back(), 6);
}
