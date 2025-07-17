#ifndef S21_MAP_H
#define S21_MAP_H

#include <initializer_list>
#include <utility>

#include "../tree/s21_tree.h"  // Подключаем бинарное дерево

namespace s21 {

template <typename Key, typename T>
class map {
 public:
  using key_type = Key;
  using mapped_type = T;
  using value_type = std::pair<const Key, T>;
  using reference = value_type &;
  using const_reference = const value_type &;
  using size_type = std::size_t;

  // Типы итераторов
  using iterator = typename BinaryTree<Key, T>::iterator;
  using const_iterator = typename BinaryTree<Key, T>::const_iterator;

  // Конструкторы
  map() : tree_() {}
  map(std::initializer_list<value_type> const &items) : tree_() {
    for (const auto &item : items) {
      insert(item);
    }
  }

  map(const map &m) : tree_() {
    for (auto it = m.begin(); it != m.end(); ++it) {
      insert(*it);
    }
  }

  // Конструктор перемещения
  map(map &&m) noexcept : tree_(std::move(m.tree_)) {
    m.tree_.clear();  // Очистка other после перемещения
  }

  map &operator=(const map &m) {
    if (this != &m) {
      clear();
      for (auto it = m.begin(); it != m.end(); ++it) {
        insert(*it);
      }
    }
    return *this;
  }

  // Оператор присваивания перемещением
  map &operator=(map &&m) noexcept {
    if (this != &m) {
      clear();  // Очистка текущего дерева
      tree_ = std::move(m.tree_);
      m.tree_.clear();  // Очистка other после перемещения
    }
    return *this;
  }

  ~map() { clear(); }

  // Доступ к элементам
  T &at(const Key &key) {
    auto it = find(key);
    if (it == end()) {
      throw std::out_of_range("Key not found");
    }
    return it->second;
  }

  T &operator[](const Key &key) {
    auto result = insert(std::make_pair(key, T()));
    return result.first->second;
  }

  // Итерирование
  iterator begin() { return tree_.begin(); }
  iterator end() { return tree_.end(); }
  const_iterator begin() const { return tree_.begin(); }
  const_iterator end() const { return tree_.end(); }

  // Информация о наполнении
  bool empty() const { return tree_.empty(); }
  size_type size() const { return tree_.size(); }
  size_type max_size() const { return tree_.max_size(); }

  // Модификация контейнера
  void clear() { tree_.clear(); }

  std::pair<iterator, bool> insert(const value_type &value) {
    return tree_.insert(value.first, value.second);
  }

  std::pair<iterator, bool> insert(const Key &key, const T &obj) {
    return tree_.insert(key, obj);
  }

  std::pair<iterator, bool> insert_or_assign(const Key &key, const T &obj) {
    return tree_.insert_or_assign(key, obj);
  }

  void erase(iterator pos) { tree_.erase(pos); }
  void erase(const Key &key) { tree_.erase(key); }

  void swap(map &other) { tree_.swap(other.tree_); }

  void merge(map &other) { tree_.merge(other.tree_); }

  // Поиск и проверка существования
  iterator find(const Key &key) { return tree_.find(key); }
  const_iterator find(const Key &key) const { return tree_.find(key); }

  bool contains(const Key &key) const { return tree_.contains(key); }

 private:
  BinaryTree<Key, T> tree_;
};

}  // namespace s21

#endif  // S21_MAP_H
