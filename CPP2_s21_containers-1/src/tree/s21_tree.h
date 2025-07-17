#ifndef S21_TREE_H
#define S21_TREE_H

#include <iostream>
#include <utility>

#include "../list/s21_list.h"
// #include <list>

namespace s21 {

// Узел дерева
template <typename Key, typename Value>
struct TreeNode {
  using value_type = std::pair<const Key, Value>;

  value_type data;  // Данные узла
  TreeNode* left;   // Указатель на левое поддерево
  TreeNode* right;  // Указатель на правое поддерево

  TreeNode(const value_type& data)
      : data(data), left(nullptr), right(nullptr) {}
};

// Бинарное дерево
template <typename Key, typename Value = Key>
class BinaryTree {
 public:
  using size_type = std::size_t;
  using value_type = std::pair<const Key, Value>;

  // Итератор
  class Iterator {
   protected:
    using Node = TreeNode<Key, Value>;

    s21::list<Node*> ancestors;  // Стек предков узлов
    Node* current;               // Текущий узел
    const BinaryTree* tree;      // Ссылка на дерево

    void pushLeft(Node* node);  // Вспомогательная функция для добавления всех
                                // левых узлов в стек
    void pushRight(Node* node);

   public:
    Iterator(Node* root = nullptr, const BinaryTree* tree = nullptr);

    value_type& operator*() const;
    value_type* operator->() const;

    Iterator& operator++();
    Iterator& operator--();
    Iterator operator++(int) {
      Iterator temp = *this;
      ++(*this);
      return temp;
    }

    Iterator operator--(int) {
      Iterator temp = *this;
      --(*this);
      return temp;
    }

    bool operator==(const Iterator& other) const;
    bool operator!=(const Iterator& other) const;

    friend class BinaryTree<Key, Value>;  // Даем BinaryTree доступ к защищённым
                                          // членам
  };

  // Константный итератор
  class ConstIterator : public Iterator {
   public:
    ConstIterator(TreeNode<Key, Value>* root = nullptr,
                  const BinaryTree* tree = nullptr)
        : Iterator(root, tree) {}

    const std::pair<const Key, Value>& operator*() const {
      return Iterator::operator*();
    }

    const std::pair<const Key, Value>* operator->() const {
      return Iterator::operator->();
    }
  };

  using iterator = Iterator;
  using const_iterator = ConstIterator;

  // Конструкторы и деструкторы
  BinaryTree() : root(nullptr), size_(0) {}
  BinaryTree(const BinaryTree& other) : root(nullptr), size_(0) {
    for (const auto& pair : other) {
      insert(pair.first, pair.second);
    }
  }
  BinaryTree(BinaryTree&& other) noexcept;
  BinaryTree& operator=(BinaryTree&& other) noexcept;
  ~BinaryTree() { clear(); }

  // Методы контейнера
  size_type size() const { return size_; }
  bool empty() const { return size_ == 0; }
  size_type max_size() const {
    return std::numeric_limits<size_type>::max() / sizeof(TreeNode<Key, Value>);
  }

  // Операции с элементами
  std::pair<iterator, bool> insert(const Key& key, const Value& value);
  iterator erase(iterator pos);
  void erase(const Key& key);
  iterator find(const Key& key);
  const_iterator find(const Key& key) const;
  bool contains(const Key& key) const { return find(key) != end(); }

  // Итераторы
  iterator begin() { return iterator(root, this); }
  iterator end() { return iterator(nullptr, this); }
  const_iterator begin() const { return const_iterator(root, this); }
  const_iterator end() const { return const_iterator(nullptr, this); }

  iterator lower_bound(const Key& key);
  iterator upper_bound(const Key& key);
  std::pair<iterator, iterator> equal_range(const Key& key);

  // Другие методы
  void clear();
  std::pair<iterator, bool> insert_or_assign(const Key& key,
                                             const Value& value);
  void swap(BinaryTree& other);
  void merge(BinaryTree& other);
  void printTree() const;

 private:
  TreeNode<Key, Value>* root;  // Корень дерева
  size_type size_;  // Текущее количество элементов

  // Вспомогательные методы
  TreeNode<Key, Value>* eraseNode(TreeNode<Key, Value>* node, const Key& key,
                                  bool& erased);
  TreeNode<Key, Value>* findMin(TreeNode<Key, Value>* node) const;
  TreeNode<Key, Value>* findMax(TreeNode<Key, Value>* node) const;

  void destroy(TreeNode<Key, Value>* node);
  void printTree(TreeNode<Key, Value>* node, int depth) const;
};

}  // namespace s21

#include "s21_tree.tpp"

#endif  // S21_TREE_H
