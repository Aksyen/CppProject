#ifndef S21_STACK_H
#define S21_STACK_H

#include <iostream>
// #include <initializer_list>
// #include <stdexcept> // для std::runtime_error
// #include <utility>   // для std::swap

namespace s21 {

template <typename T>
class stack {
 public:
  // Определяем типы для удобства, аналогично std::stack
  using value_type = T;
  using reference = T&;
  using const_reference = const T&;
  using size_type = std::size_t;

  // Конструктор по умолчанию, создающий пустой стек
  stack() : top_(nullptr), size_(0) {}

  // Конструктор с инициализатором, позволяющий создавать стек с заданными
  // значениями
  stack(std::initializer_list<value_type> const& items) : stack() {
    for (const auto& item : items) {  // Перебираем все элементы списка
      push(item);  // Добавляем каждый элемент в стек
    }
  }

  // Конструктор копирования
  stack(const stack& s) : stack() {
    copy_stack(s);  // Копируем элементы из другого стека
  }

  // Конструктор перемещения (забирает ресурсы у другого объекта)
  stack(stack&& s) noexcept : top_(s.top_), size_(s.size_) {
    s.top_ = nullptr;  // Очищаем указатель у переданного объекта
    s.size_ = 0;  // Обнуляем размер переданного объекта
  }

  // Деструктор освобождает всю выделенную память
  ~stack() {
    clear();  // Удаляем все элементы стека
  }

  // Оператор присваивания для перемещения
  stack& operator=(stack&& s) {
    if (this != &s) {  // Проверяем, что не присваиваем сами себе
      clear();        // Очищаем текущий стек
      top_ = s.top_;  // Забираем указатель на вершину и размер у переданного
                      // объекта
      size_ = s.size_;
      s.top_ = nullptr;  // Обнуляем указатель у переданного объекта
      s.size_ = 0;
    }
    return *this;
  }

  stack& operator=(const stack& s) {
    if (this != &s) {
      clear();
      copy_stack(s);
    }
    return *this;
  }

  // Метод доступа к верхнему элементу (с проверкой на пустоту)
  const_reference top() const {
    if (empty()) {  // Если стек пуст, выбрасываем исключение
      throw std::runtime_error("Stack is empty");
    }
    return top_->data;  // Возвращаем данные верхнего элемента
  }

  // Проверка, пуст ли стек
  bool empty() const {
    return size_ == 0;  // Если размер стека 0, значит он пуст
  }

  // Возвращаем количество элементов в стеке
  size_type size() const { return size_; }

  // Добавление нового элемента в стек
  void push(const_reference value) {
    Node* new_node =
        new Node(value);  // Создаем новый узел с переданным значением
    new_node->next = top_;  // Устанавливаем новый узел на вершину
    top_ = new_node;  // Перемещаем указатель вершины на новый узел
    ++size_;          // Увеличиваем размер стека
  }

  // Удаление верхнего элемента из стека
  void pop() {
    if (empty()) {  // Если стек пуст, выбрасываем исключение
      throw std::runtime_error("Stack is empty");
    }
    Node* temp = top_;  // Сохраняем указатель на текущую вершину
    top_ = top_->next;  // Перемещаем вершину на следующий элемент
    delete temp;  // Удаляем старую вершину
    --size_;      // Уменьшаем размер стека
  }

  // Обмен содержимым с другим стеком
  void swap(stack& other) noexcept {
    std::swap(top_, other.top_);  // Обмениваем указатели на вершину
    std::swap(size_, other.size_);  // Обмениваем размеры
  }

  template <typename... Args>
  void insert_many_back(Args&&... args) {
    (push(std::forward<Args>(args)), ...);
  }

 private:
  // Структура узла, представляющего элемент в стеке
  struct Node {
    value_type data;  // Данные узла
    Node* next;  // Указатель на следующий элемент
    Node(const value_type& value)
        : data(value), next(nullptr) {}  // Инициализация узла
  };

  Node* top_;  // Указатель на вершину стека
  size_type size_;  // Текущее количество элементов в стеке

  // Вспомогательный метод для копирования элементов из другого стека
  void copy_stack(const stack& s) {
    if (s.size_ > 0) {
      Node* temp = s.top_;  // Временный указатель для прохода по другому стеку
      stack temp_stack;  // Временный стек для обратного порядка элементов
      while (temp) {     // Пока есть элементы
        temp_stack.push(temp->data);  // Копируем элемент во временный стек
        temp = temp->next;  // Переходим к следующему элементу
      }
      while (!temp_stack.empty()) {  // Переносим элементы в наш стек
        push(temp_stack.top_->data);
        temp_stack.pop();
      }
    }
  }

  // Очистка всех элементов стека
  void clear() {
    while (!empty()) {  // Пока стек не пуст
      pop();            // Удаляем верхний элемент
    }
  }
};

}  // namespace s21

#endif  // S21_STACK_H
