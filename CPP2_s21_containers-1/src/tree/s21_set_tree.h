#ifndef S21_BINARY_TREE_H
#define S21_BINARY_TREE_H

#include <iostream>
#include <limits>

namespace s21 {
template <class K, class T>
class SetTree {
 public:
  struct Node {
    Node *left, *right, *parent;
    K key;
    T value;
    Node(K _key, T _value, Node* _parent = nullptr);
    ~Node();
  };
  class Iterator {
   public:
    Node* ptr;
    Iterator();
    explicit Iterator(Node* _ptr);
    Iterator& operator++();
    Iterator operator++(int);
    Iterator operator--(int);
    Iterator& operator--();
    bool operator==(Iterator other) const;
    bool operator!=(Iterator other) const;
    Node* operator->() const;
  };
  using key_type = K;
  using mapped_type = T;
  using value_type = std::pair<const key_type, mapped_type>;
  using reference = value_type&;
  using const_reference = const value_type&;
  using iterator = Iterator;
  using const_iterator = const Iterator;
  using size_type = size_t;

  SetTree();
  SetTree(std::initializer_list<value_type> const& items);
  SetTree(const SetTree& other);
  SetTree(SetTree&& other);
  ~SetTree();

  SetTree operator=(SetTree&& other);
  iterator begin() const;
  iterator end() const;
  size_type Size();
  size_type max_size();
  bool empty();
  void clear();

 protected:
  std::pair<iterator, bool> insert(const value_type& value);
  std::pair<iterator, bool> insert(const K& key, const T& obj);
  std::pair<iterator, bool> insert_or_assign(const K& key, const T& obj);
  iterator insert(const K& key);
  void erase(iterator pos);
  void swap(SetTree& other);
  void merge(SetTree& other);
  bool contains(const K& key);
  size_type count(const K& key);
  iterator find(const K& key);

  std::pair<iterator, iterator> equal_range(const K& key);
  iterator lower_bound(const K& key);
  iterator upper_bound(const K& key);
  iterator root, iter, begin_i, end_i;
  T& at(const K& key);
  T& operator[](const K& key);

 private:
  size_type size;
  Node* fake;
  void assign(const SetTree& other);
  bool contains(Node* root, const K& key);
  void insert(Node* iter, Node* _node);
  Node* insert(Node* iter, const K& key, const T& value);
  iterator set_begin();
  iterator set_end();
  Node* find(Node* root, const K& key);
};
};  // namespace s21

#include "s21_set_tree.tpp"

#endif  // S21_BINARY_TREE_H