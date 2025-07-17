#include "s21_list.h"

namespace s21 {

// Constructors and Destructor

template <typename T>
list<T>::list(size_type n) : head(nullptr), tail(nullptr), size_(0) {
  for (size_type i = 0; i < n; ++i) {
    push_back(T());
  }
}

template <typename T>
list<T>::list(std::initializer_list<value_type> const &items)
    : head(nullptr), tail(nullptr), size_(0) {
  for (const auto &item : items) {
    push_back(item);
  }
}

template <typename T>
list<T>::list(list &&l) noexcept : head(l.head), tail(l.tail), size_(l.size_) {
  l.head = l.tail = nullptr;
  l.size_ = 0;
}

template <typename T>
list<T>::list(const list &l) : head(nullptr), tail(nullptr), size_(0) {
  for (auto it = l.cbegin(); it != l.cend(); ++it) {
    push_back(*it);
  }
}

template <typename T>
list<T>::~list() {
  clear();
}

template <typename T>
void list<T>::push_back(const T &value) {
  Node<T> *newNode = new Node<T>(value);
  if (tail) {
    tail->next = newNode;
    newNode->prev = tail;
    tail = newNode;
  } else {  // Если список пуст
    head = tail = newNode;
  }
  ++size_;
}

// Перегрузка для rvalue-ссылки
template <typename T>
void list<T>::push_back(T &&value) {
  Node<T> *newNode = new Node<T>(std::move(value));
  if (tail) {
    tail->next = newNode;
    newNode->prev = tail;
    tail = newNode;
  } else {  // Если список пуст
    head = tail = newNode;
  }
  ++size_;
}

template <typename T>
void list<T>::push_front(const T &value) {
  Node<T> *newNode = new Node<T>(value);
  if (head) {
    head->prev = newNode;
    newNode->next = head;
  } else {  // Если список пуст
    tail = newNode;
  }
  head = newNode;
  ++size_;
}

// Перегрузка для rvalue-ссылки
template <typename T>
void list<T>::push_front(T &&value) {
  Node<T> *newNode = new Node<T>(std::move(value));
  if (head) {
    head->prev = newNode;
    newNode->next = head;
  } else {  // Если список пуст
    tail = newNode;
  }
  head = newNode;
  ++size_;
}

template <typename T>
void list<T>::pop_back() {
  // Если список пуст, ничего не делаем
  if (empty()) throw std::out_of_range("List is empty");
  Node<T> *temp = tail;
  if (head == tail) {  // Если в списке один элемент
    head = tail = nullptr;
  } else {
    tail = tail->prev;
    tail->next = nullptr;
  }
  delete temp;
  --size_;
}

template <typename T>
void list<T>::pop_front() {
  // Если список пуст, ничего не делаем
  if (empty()) throw std::out_of_range("List is empty");

  Node<T> *temp = head;
  if (head == tail) {  // Если один элемент в списке
    head = tail = nullptr;
  } else {
    head = head->next;
    head->prev = nullptr;
  }
  delete temp;
  --size_;
}

template <typename T>
void list<T>::swap(list &other) {
  if (this == &other) return;  // Проверка на самосвап

  using std::swap;  // Используем ADL для вызова swap

  // Обмениваем указатели head и tail
  swap(head, other.head);
  swap(tail, other.tail);

  // Обмениваем размер
  swap(size_, other.size_);
}

template <typename T>
void list<T>::merge(list &other) {
  if (this == &other) return;  // Защита от самослияния

  // Предполагаем, что списки уже отсортированы.
  auto it = begin();
  auto otherIt = other.begin();

  while (otherIt != other.end()) {
    // Если `it` дошел до конца, перемещаем оставшиеся узлы из `other`
    if (it == end()) {
      tail->next = otherIt.current;
      otherIt.current->prev = tail;
      tail = other.tail;
      size_ += other.size_;
      other.head = other.tail = nullptr;
      other.size_ = 0;
      return;
    }

    if (*otherIt < *it) {
      // Извлекаем узел из `other` и вставляем его перед `it`
      Node<T> *nodeToMove = otherIt.current;
      otherIt++;

      if (nodeToMove->prev) nodeToMove->prev->next = nodeToMove->next;
      if (nodeToMove->next) nodeToMove->next->prev = nodeToMove->prev;
      if (nodeToMove == other.head) other.head = nodeToMove->next;
      if (nodeToMove == other.tail) other.tail = nodeToMove->prev;

      nodeToMove->next = it.current;
      nodeToMove->prev = it.current->prev;

      if (it.current->prev) it.current->prev->next = nodeToMove;
      it.current->prev = nodeToMove;

      if (nodeToMove->prev == nullptr) head = nodeToMove;

      ++size_;
      --other.size_;
    } else {
      ++it;
    }
  }
}

template <typename T>
void list<T>::splice(const_iterator pos, list &other) {
  if (this == &other || other.empty()) {
    return;  // Защита от самоперемещения и пустого списка
  }

  Node<T> *posNode = const_cast<Node<T> *>(pos.current);

  // Если текущий список пуст
  if (empty()) {
    head = other.head;
    tail = other.tail;
  } else if (posNode == head) {
    // Вставка перед началом текущего списка
    other.tail->next = head;
    head->prev = other.tail;
    head = other.head;
  } else if (posNode == nullptr) {  // Вставка в конец текущего списка
    tail->next = other.head;
    other.head->prev = tail;
    tail = other.tail;
  } else {
    // Вставка в середину списка
    Node<T> *prevNode = posNode->prev;
    prevNode->next = other.head;
    other.head->prev = prevNode;

    other.tail->next = posNode;
    posNode->prev = other.tail;
  }

  // Обновление размера текущего списка и очистка `other`
  size_ += other.size_;
  other.head = nullptr;
  other.tail = nullptr;
  other.size_ = 0;
}

template <typename T>
void list<T>::reverse() {
  if (!head || !head->next)
    return;  // Если список пуст или содержит один элемент, ничего не делаем

  Node<T> *current = head;
  Node<T> *temp = nullptr;

  // Проходим по списку, меняя местами next и prev для каждого узла
  while (current) {
    temp = current->prev;
    current->prev = current->next;
    current->next = temp;
    current = current->prev;  // Переходим к следующему узлу (по старому prev)
  }

  // Меняем местами head и tail
  temp = head;
  head = tail;
  tail = temp;
}

template <typename T>
void list<T>::unique() {
  if (!head || !head->next)
    return;  // Если список пуст или состоит из одного элемента, ничего не
             // делаем

  Node<T> *current = head;

  while (current && current->next) {
    if (current->value == current->next->value) {
      Node<T> *duplicate = current->next;
      current->next = duplicate->next;

      if (duplicate->next) {
        duplicate->next->prev = current;
      } else {
        tail = current;  // Если дубликат — последний элемент, обновляем tail
      }

      delete duplicate;
      --size_;
    } else {
      current = current->next;
    }
  }
}

template <typename T>
void list<T>::sort() {
  if (size_ < 2)
    return;  // Если в списке меньше 2 элементов, сортировка не нужна

  head = mergeSort(head);

  // Обновляем указатель tail после сортировки
  Node<T> *temp = head;
  while (temp->next) {
    temp = temp->next;
  }
  tail = temp;
}

// Вспомогательная функция для сортировки слиянием
template <typename T>
Node<T> *list<T>::mergeSort(Node<T> *node) {
  // Базовый случай: если список пустой или состоит из одного элемента
  if (!node || !node->next) return node;

  Node<T> *middle = split(node);
  Node<T> *left = mergeSort(node);
  Node<T> *right = mergeSort(middle);

  return merge(left, right);
}

// Вспомогательная функция для разделения списка пополам
template <typename T>
Node<T> *list<T>::split(Node<T> *node) {
  Node<T> *fast = node, *slow = node;

  // Двигаемся по списку, чтобы найти середину
  while (fast->next && fast->next->next) {
    fast = fast->next->next;
    slow = slow->next;
  }

  Node<T> *middle = slow->next;
  slow->next = nullptr;  // Разделяем список на две половины
  if (middle) middle->prev = nullptr;

  return middle;
}

// Вспомогательная функция для слияния двух отсортированных списков
template <typename T>
Node<T> *list<T>::merge(Node<T> *left, Node<T> *right) {
  if (!left) return right;
  if (!right) return left;

  if (left->value < right->value) {
    left->next = merge(left->next, right);
    left->next->prev = left;
    left->prev = nullptr;
    return left;
  } else {
    right->next = merge(left, right->next);
    right->next->prev = right;
    right->prev = nullptr;
    return right;
  }
}

template <typename T>
void list<T>::clear() {
  Node<T> *current = head;
  head = nullptr;
  tail = nullptr;
  size_ = 0;

  while (current) {
    Node<T> *temp = current;
    current = current->next;
    delete temp;
  }
}

template <typename T>
typename list<T>::const_reference list<T>::front() const {
  if (empty()) {
    throw std::out_of_range("Cannot access front of an empty list");
  }
  return head->value;
}

template <typename T>
typename list<T>::const_reference list<T>::back() const {
  if (empty()) {
    throw std::out_of_range("Cannot access back of an empty list");
  }
  return tail->value;
}

template <typename T>
typename list<T>::reference list<T>::front() {
  if (empty()) {
    throw std::out_of_range("Cannot access front of an empty list");
  }
  return head->value;
}

template <typename T>
typename list<T>::reference list<T>::back() {
  if (empty()) {
    throw std::out_of_range("Cannot access back of an empty list");
  }
  return tail->value;
}

/*
Функция insert в контейнере list вставляет новый элемент перед позицией, на
которую указывает переданный итератор pos
*/
template <typename T>
typename list<T>::iterator list<T>::insert(iterator pos, const T &value) {
  Node<T> *current = pos.current;
  Node<T> *newNode = new Node<T>(value);

  if (current == head) {  // Вставка в начало списка
    newNode->next = head;
    if (head) {
      head->prev = newNode;
    }
    head = newNode;
    if (!tail) {
      tail = newNode;
    }
  } else if (current) {  // Вставка перед текущим элементом
    newNode->next = current;
    newNode->prev = current->prev;
    current->prev->next = newNode;
    current->prev = newNode;
  } else {  // Вставка в конец списка
    newNode->prev = tail;
    if (tail) {
      tail->next = newNode;
    }
    tail = newNode;
    if (!head) {
      head = newNode;
    }
  }

  ++size_;
  return iterator(newNode);
}

// Перегрузка для rvalue ссылки
template <typename T>
typename list<T>::iterator list<T>::insert(iterator pos, T &&value) {
  return insert(pos, value);  // Вставка с перемещением
}

/*
Функция erase удаляет элемент из списка, на который указывает переданный
итератор
*/
template <typename T>
typename list<T>::iterator list<T>::erase(iterator pos) {
  Node<T> *current = pos.current;

  // Если итератор указывает на end() или список пуст, ничего не делаем
  if (!current || empty()) {
    return end();
  }

  // Получаем итератор на следующий узел
  iterator nextIter(current->next);

  // Обновляем ссылки соседних узлов
  if (current->prev) {
    current->prev->next = current->next;
  } else {
    head = current->next;  // Если удаляем первый элемент
  }

  if (current->next) {
    current->next->prev = current->prev;
  } else {
    tail = current->prev;  // Если удаляем последний элемент
  }

  // Освобождаем память и уменьшаем размер
  delete current;
  --size_;

  // Если список стал пустым, возвращаем end()
  return (head == nullptr) ? end() : nextIter;
}

template <typename T>
list<T> &list<T>::operator=(list &&l) {
  if (this != &l) {  // Защита от самоприсваивания
    clear();         // Очистка текущего списка

    // Перемещение данных из другого списка
    head = l.head;
    tail = l.tail;
    size_ = l.size_;

    // Обнуление указателей у другого списка, так как он больше не владеет
    // данными
    l.head = nullptr;
    l.tail = nullptr;
    l.size_ = 0;
  }
  return *this;
}

template <typename T>
list<T> &list<T>::operator=(const list &other) {
  if (this != &other) {
    clear();
    for (auto it = other.cbegin(); it != other.cend(); ++it) {
      push_back(*it);
    }
  }
  return *this;
}

template <typename T>
typename list<T>::reference list<T>::operator[](size_type index) {
  if (index >= size_) {
    throw std::out_of_range("Index out of bounds");
  }

  Node<T> *current = head;
  for (size_type i = 0; i < index; ++i) {
    current = current->next;
  }
  return current->value;
}

template <typename T>
typename list<T>::const_reference list<T>::operator[](size_type index) const {
  if (index >= size_) {
    throw std::out_of_range("Index out of bounds");
  }

  Node<T> *current = head;
  for (size_type i = 0; i < index; ++i) {
    current = current->next;
  }
  return current->value;
}

template <typename T>
template <typename... Args>
typename list<T>::iterator list<T>::insert_many(const_iterator pos,
                                                Args &&...args) {
  Node<T> *posNode = const_cast<Node<T> *>(
      pos.current);  // Узел, перед которым будем вставлять элементы
  Node<T> *prevNode =
      posNode ? posNode->prev
              : tail;  // Узел перед `posNode` или хвост, если `pos` — конец

  // Перебираем аргументы и создаем новые узлы
  for (const auto &arg : {args...}) {
    Node<T> *newNode = new Node<T>(arg);  // Создаем новый узел

    newNode->next = posNode;
    newNode->prev = prevNode;

    if (prevNode) {
      prevNode->next = newNode;
    } else {
      head = newNode;  // Если вставляем в начало, обновляем `head`
    }

    if (posNode) {
      posNode->prev = newNode;
    } else {
      tail = newNode;  // Если вставляем в конец, обновляем `tail`
    }

    prevNode = newNode;
    ++size_;
  }

  return iterator(
      prevNode, this);  // Возвращаем итератор на последний вставленный элемент
}

template <typename T>
template <typename... Args>
void list<T>::insert_many_back(Args &&...args) {
  for (const auto &arg : {args...}) {
    push_back(arg);
  }
}

template <typename T>
template <typename... Args>
void list<T>::insert_many_front(Args &&...args) {
  for (const auto &arg : {args...}) {
    push_front(arg);
  }
}

}  // namespace s21
