#include <gtest/gtest.h>

#include "../tree/s21_tree.h"

// Тест 1. Вставка и удаление в пустом дереве
TEST(BinaryTreeTest, InsertAndEraseInEmptyTree) {
  s21::BinaryTree<int, int> tree;

  EXPECT_TRUE(tree.empty());
  auto result = tree.insert(1, 10);
  EXPECT_TRUE(result.second);
  EXPECT_EQ(tree.size(), 1);
  EXPECT_EQ(result.first->first, 1);

  tree.erase(1);
  EXPECT_TRUE(tree.empty());
  EXPECT_EQ(tree.size(), 0);
}

// Тест 2. Удаление корня дерева
TEST(BinaryTreeTest, EraseRoot) {
  s21::BinaryTree<int, int> tree;

  tree.insert(20, 200);
  tree.insert(10, 100);
  tree.insert(30, 300);

  EXPECT_EQ(tree.size(), 3);

  tree.erase(20);  // Удаление корня с двумя потомками

  EXPECT_EQ(tree.size(), 2);
  EXPECT_FALSE(tree.contains(20));
  EXPECT_TRUE(tree.contains(10));
  EXPECT_TRUE(tree.contains(30));

  auto it = tree.begin();
  EXPECT_EQ(it->first, 10);
  ++it;
  EXPECT_EQ(it->first, 30);
}

// Тест 3. Удаление единственного элемента в дереве
TEST(BinaryTreeTest, EraseSingleElement) {
  s21::BinaryTree<int, int> tree;

  // Вставка единственного элемента
  tree.insert(42, 420);

  EXPECT_EQ(tree.size(), 1);

  // Удаление
  tree.erase(42);

  EXPECT_TRUE(tree.empty());
  EXPECT_EQ(tree.size(), 0);
  EXPECT_FALSE(tree.contains(42));
}

// Тест 4. Использование итераторов на пустом дереве
TEST(BinaryTreeTest, IteratorsOnEmptyTree) {
  s21::BinaryTree<int, int> tree;

  EXPECT_EQ(tree.begin(), tree.end());
  EXPECT_THROW(*tree.begin(), std::out_of_range);
}

// Тест 5. Вставка большого количества элементов и их последовательное удаление
TEST(BinaryTreeTest, LargeInsertAndErase) {
  s21::BinaryTree<int, int> tree;

  const int num_elements = 10000;
  for (int i = 0; i < num_elements; ++i) {
    tree.insert(i, i * 10);
  }

  EXPECT_EQ(tree.size(), num_elements);

  int count = 0;
  for (auto it = tree.begin(); it != tree.end(); ++it) {
    EXPECT_EQ(it->first, count);
    EXPECT_EQ(it->second, count * 10);
    ++count;
  }

  for (int i = 0; i < num_elements; ++i) {
    tree.erase(i);
  }

  EXPECT_TRUE(tree.empty());
}

TEST(BinaryTreeTest, PrintTreeAndEraseRoot) {
  s21::BinaryTree<int, int> tree;

  // Вставка элементов
  tree.insert(10, 100);  // Корень
  tree.insert(5, 50);    // Левый потомок
  tree.insert(15, 150);  // Правый потомок
  tree.insert(3, 30);  // Левый потомок левого потомка
  tree.insert(7, 70);  // Правый потомок левого потомка
  tree.insert(13, 130);  // Левый потомок правого потомка
  tree.insert(17, 170);  // Правый потомок правого потомка

  // Вывод дерева до удаления
  // std::cout << "Дерево до удаления корня:" << std::endl;
  // tree.printTree();

  // Удаляем корень
  tree.erase(10);

  // Вывод дерева после удаления
  // std::cout << "\nДерево после удаления корня:" << std::endl;
  // tree.printTree();

  // Проверка содержимого дерева
  EXPECT_FALSE(tree.contains(10));  // Корень должен быть удалён
  EXPECT_TRUE(tree.contains(5));
  EXPECT_TRUE(tree.contains(15));
  EXPECT_TRUE(tree.contains(3));
  EXPECT_TRUE(tree.contains(7));
  EXPECT_TRUE(tree.contains(13));
  EXPECT_TRUE(tree.contains(17));

  // Проверка размера
  EXPECT_EQ(tree.size(), 6);
}

TEST(BinaryTreeIteratorTest, IncrementTest) {
  s21::BinaryTree<int, int> tree;
  tree.insert(10, 100);
  tree.insert(5, 50);
  tree.insert(15, 150);

  auto it = tree.begin();
  EXPECT_EQ((*it).first, 5);

  ++it;
  EXPECT_EQ((*it).first, 10);

  ++it;
  EXPECT_EQ((*it).first, 15);

  ++it;
  EXPECT_EQ(it, tree.end());
}

TEST(BinaryTreeIteratorTest, DecrementTest) {
  s21::BinaryTree<int, int> tree;
  tree.insert(10, 100);
  tree.insert(5, 50);
  tree.insert(15, 150);

  auto it = tree.end();

  --it;
  EXPECT_EQ((*it).first, 15);

  --it;

  EXPECT_EQ((*it).first, 10);

  --it;

  EXPECT_EQ((*it).first, 5);

  EXPECT_THROW(--it, std::out_of_range);

  // Проверка пустого дерева
  s21::BinaryTree<int, int> empty_tree;
  auto empty_it = empty_tree.begin();
  EXPECT_THROW(--empty_it, std::out_of_range);
}

TEST(BinaryTreeTest, BoundsAndEqualRange) {
  s21::BinaryTree<int, int> tree;

  tree.insert(10, 100);
  tree.insert(20, 200);
  tree.insert(30, 300);

  auto lb = tree.lower_bound(15);
  EXPECT_EQ(lb->first, 20);  // Первый элемент >= 15

  auto ub = tree.upper_bound(20);
  EXPECT_EQ(ub->first, 30);  // Первый элемент > 20

  auto range = tree.equal_range(20);
  EXPECT_EQ(range.first->first, 20);   // lower_bound(20)
  EXPECT_EQ(range.second->first, 30);  // upper_bound(20)
}
