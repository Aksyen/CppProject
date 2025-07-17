#ifndef S21_CONTAINERS_QUEUE_H
#define S21_CONTAINERS_QUEUE_H

#include <iostream>

namespace s21 {

template <typename T>
class queue {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = size_t;

  // Структура узла
  struct Node {
    value_type data;
    Node *next;
    Node(const_reference value) : data(value), next(nullptr) {}
  };

  // Конструкторы и деструктор
  queue();
  queue(std::initializer_list<value_type> const &items);
  queue(const queue &q);
  queue(queue &&q);
  ~queue();

  queue &operator=(queue &&q);

  // Функции доступа
  const_reference front();
  const_reference back();

  bool empty() const;
  size_type size() const;

  // Модификаторы
  void push(const_reference value);
  void pop();
  void swap(queue &other);

  template <typename... Args>
  void insert_many_back(Args &&...args);

 private:
  Node *front_;
  Node *back_;
  size_type size_;
};

}  // namespace s21

#include "s21_queue.tpp"

#endif
