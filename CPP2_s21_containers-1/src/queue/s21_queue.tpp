#include "s21_queue.h"

namespace s21 {

// Конструктор по умолчанию
template <typename T>
queue<T>::queue() : front_(nullptr), back_(nullptr), size_(0) {}

// Параметризованный конструктор
template <typename T>
queue<T>::queue(std::initializer_list<value_type> const &items)
    : front_(nullptr), back_(nullptr), size_(0) {
  for (const auto &item : items) {
    push(item);
  }
}

// Конструктор копирования
template <typename T>
queue<T>::queue(const queue &q) : front_(nullptr), back_(nullptr), size_(0) {
  Node *current = q.front_;
  while (current != nullptr) {
    push(current->data);
    current = current->next;
  }
}

// Конструктор перемещения
template <typename T>
queue<T>::queue(queue &&q) : front_(q.front_), back_(q.back_), size_(q.size_) {
  q.front_ = nullptr;
  q.back_ = nullptr;
  q.size_ = 0;
}

// Деконструктор
template <typename T>
queue<T>::~queue() {
  while (!empty()) pop();
}

// Оператор присваивания
template <typename T>
queue<T> &queue<T>::operator=(queue &&q) {
  if (this != &q) {  // Проверка на самоприсваивание
    while (!empty()) pop();

    front_ = q.front_;
    back_ = q.back_;
    size_ = q.size_;

    q.front_ = nullptr;
    q.back_ = nullptr;
    q.size_ = 0;
  }
  return *this;
}

// Доступ к первому элементу
template <typename T>
typename queue<T>::const_reference queue<T>::front() {
  if (empty()) throw std::out_of_range("Пустая очередь!");
  return front_->data;
}

// Доступ к последнему элементу
template <typename T>
typename queue<T>::const_reference queue<T>::back() {
  if (empty()) throw std::out_of_range("Пустая очередь!");
  return back_->data;
}

// Проверка на пустоту очереди
template <typename T>
bool queue<T>::empty() const {  // Добавлен const
  return (front_ == nullptr && back_ == nullptr && size_ == 0);
}

// Размер очереди
template <typename T>
typename queue<T>::size_type queue<T>::size() const {
  return size_;
}

// Вставка элемента в конец очереди
template <typename T>
void queue<T>::push(const_reference value) {
  Node *new_node = new Node(value);
  if (empty()) {
    front_ = new_node;
  } else {
    back_->next = new_node;
  }
  back_ = new_node;
  ++size_;
}

// Удаление первого элемента
template <typename T>
void queue<T>::pop() {
  if (empty()) throw std::out_of_range("Queue is empty");
  Node *temp = front_;
  front_ = front_->next;
  delete temp;
  --size_;
  if (front_ == nullptr) {
    back_ = nullptr;
  }
}

// Обмен содержимого двух очередей
template <typename T>
void queue<T>::swap(queue &other) {
  std::swap(front_, other.front_);
  std::swap(back_, other.back_);
  std::swap(size_, other.size_);
}

// Вставка нескольких аргументов
template <typename T>
template <typename... Args>
void queue<T>::insert_many_back(Args &&...args) {
  for (const auto &arg : {args...}) {
    push(arg);
  }
}

}  // namespace s21
