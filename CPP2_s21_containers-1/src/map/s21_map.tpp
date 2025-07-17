#ifndef S21_MAP_TPP
#define S21_MAP_TPP

#include "s21_map.h"

namespace s21 {

// Конструктор с initializer_list
template <typename Key, typename T>
map<Key, T>::map(std::initializer_list<value_type> const &items) : tree_() {
  for (const auto &item : items) {
    insert(item);
  }
}

// Конструктор копирования
template <typename Key, typename T>
map<Key, T>::map(const map &other) : tree_() {
  for (auto it = other.begin(); it != other.end(); ++it) {
    insert(*it);
  }
}

// Оператор присваивания копированием
template <typename Key, typename T>
map<Key, T> &map<Key, T>::operator=(const map &other) {
  if (this != &other) {
    clear();
    for (auto it = other.begin(); it != other.end(); ++it) {
      insert(*it);
    }
  }
  return *this;
}

// Оператор присваивания перемещением
template <typename Key, typename T>
map<Key, T> &map<Key, T>::operator=(map &&other) noexcept {
  if (this != &other) {
    clear();
    tree_ = std::move(other.tree_);
  }
  return *this;
}

// Метод at с проверкой на наличие ключа
template <typename Key, typename T>
T &map<Key, T>::at(const Key &key) {
  auto it = find(key);
  if (it == end()) {
    throw std::out_of_range("Key not found");
  }
  return it->second;
}

// Метод operator[] для доступа или вставки элемента
template <typename Key, typename T>
T &map<Key, T>::operator[](const Key &key) {
  auto result = insert(std::make_pair(key, T()));
  return result.first->second;
}

// Очистка карты
template <typename Key, typename T>
void map<Key, T>::clear() {
  tree_.clear();
}

// Вставка пары ключ-значение
template <typename Key, typename T>
std::pair<typename map<Key, T>::iterator, bool> map<Key, T>::insert(
    const value_type &value) {
  return tree_.insert(value.first, value.second);
}

// Вставка по ключу и значению
template <typename Key, typename T>
std::pair<typename map<Key, T>::iterator, bool> map<Key, T>::insert(
    const Key &key, const T &obj) {
  return tree_.insert(key, obj);
}

// Вставка или обновление значения по ключу
template <typename Key, typename T>
std::pair<typename map<Key, T>::iterator, bool> map<Key, T>::insert_or_assign(
    const Key &key, const T &obj) {
  return tree_.insert_or_assign(key, obj);
}

// Удаление элемента по итератору
template <typename Key, typename T>
void map<Key, T>::erase(iterator pos) {
  tree_.erase(pos);
}

// Удаление элемента по ключу
template <typename Key, typename T>
void map<Key, T>::erase(const Key &key) {
  tree_.erase(key);
}

// Обмен содержимым с другой картой
template <typename Key, typename T>
void map<Key, T>::swap(map &other) {
  tree_.swap(other.tree_);
}

// Объединение с другой картой
template <typename Key, typename T>
void map<Key, T>::merge(map &other) {
  tree_.merge(other.tree_);
}

// Поиск элемента по ключу
template <typename Key, typename T>
typename map<Key, T>::iterator map<Key, T>::find(const Key &key) {
  return tree_.find(key);
}

// Поиск элемента по ключу (const)
template <typename Key, typename T>
typename map<Key, T>::const_iterator map<Key, T>::find(const Key &key) const {
  return tree_.find(key);
}

// Проверка наличия ключа
template <typename Key, typename T>
bool map<Key, T>::contains(const Key &key) const {
  return tree_.contains(key);
}

}  // namespace s21

#endif  // S21_MAP_TPP
