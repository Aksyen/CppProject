#include "s21_set.h"

namespace s21 {

// Конструктор по умолчанию
template <typename Key>
set<Key>::set() : SetTree<Key, Key>() {}

// Конструктор с инициализацией
template <typename Key>
set<Key>::set(std::initializer_list<value_type> const& items)
    : SetTree<Key, Key>() {
  for (auto i = items.begin(); i != items.end(); ++i) {
    SetTree<Key, Key>::insert(*i, Key());
  }
}

// Конструктор копирования
template <typename Key>
set<Key>::set(const set& s) : SetTree<Key, Key>(s) {}

// Конструктор перемещения
template <typename Key>
set<Key>::set(set&& s) : SetTree<Key, Key>(std::move(s)) {}

// Деконструктор
template <typename Key>
set<Key>::~set() {}

// Оператор перемещения
template <typename Key>
set<Key>& set<Key>::operator=(set&& s) {
  if (this != &s) {  // предотвращаем самоприсваивание
    SetTree<Key, Key>::operator=(std::move(s));  // перемещаем данные
  }
  return *this;  // возвращаем ссылку на текущий объект
}

// Реализация метода insert
template <typename Key>
std::pair<typename set<Key>::iterator, bool> set<Key>::insert(
    const value_type& value) {
  return SetTree<Key, Key>::insert(value, Key());
}

// Реализация метода erase
template <typename Key>
void set<Key>::erase(iterator pos) {
  SetTree<Key, Key>::erase(pos);
}

// Реализация метода contains
template <typename Key>
bool set<Key>::contains(const Key& key) {
  return SetTree<Key, Key>::contains(key);
}

// Реализация метода size
template <typename Key>
typename set<Key>::size_type set<Key>::size() {
  return SetTree<Key, Key>::Size();
}

// Реализация метода empty
template <typename Key>
bool set<Key>::empty() {
  return SetTree<Key, Key>::empty();
}

//реализация метода find
template <typename Key>
typename set<Key>::iterator set<Key>::find(const Key& key) {
  return SetTree<Key, Key>::find(key);
}

// Реализация метода max_size
template <typename Key>
typename set<Key>::size_type set<Key>::max_size() {
  return std::numeric_limits<typename set<Key>::size_type>::max() /
         sizeof(typename set<Key>::value_type);
}

// Реализация метода swap
template <typename Key>
void set<Key>::swap(set& other) {
  SetTree<Key, Key>::swap(other);
}

// Реализация метода merge
template <typename Key>
void set<Key>::merge(set& other) {
  SetTree<Key, Key>::merge(other);
}

// Реализация метода clear
// template <typename Key>
// void set<Key>::clear() {
//     this->destroy(this->getRoot());  // Удаляем все узлы дерева
//     this->getRoot() = nullptr;            // Обнуляем корень
// }
template <typename Key>
void set<Key>::clear() {
  SetTree<Key, Key>::clear();
}

// Метод вставки нескольких элементов
template <typename Key>
template <typename... Args>
s21::vector<std::pair<typename set<Key>::iterator, bool>> set<Key>::insert_many(
    Args&&... args) {
  s21::vector<std::pair<iterator, bool>> result_vector;
  for (const auto& arg : {args...}) {
    result_vector.push_back(insert(arg));
  }
  return result_vector;
}

// Итератор начала множества
template <typename Key>
typename set<Key>::iterator set<Key>::begin() const {
  return SetTree<Key, Key>::begin();
}

// Итератор конца множества
template <typename Key>
typename set<Key>::iterator set<Key>::end() const {
  return SetTree<Key, Key>::end();
}

};  // namespace s21
