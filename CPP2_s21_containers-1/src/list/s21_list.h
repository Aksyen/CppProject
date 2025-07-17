#ifndef S21_LIST_H
#define S21_LIST_H

#include <iostream>
#include <limits>

namespace s21 {

template <typename T>
struct Node {
  T value;
  Node *next;
  Node *prev;

  Node() = default;
  Node(const T &val) : value(val), next(nullptr), prev(nullptr) {}
  Node(T &&val) : value(std::move(val)), next(nullptr), prev(nullptr) {}
};

template <typename T>
class list {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = std::size_t;

  class ListIterator;
  class ListConstIterator;

  using iterator = ListIterator;
  using const_iterator = ListConstIterator;

 private:
  Node<T> *head;
  Node<T> *tail;
  size_type size_;

  // Предварительные объявления приватных вспомогательных методов
  Node<T> *mergeSort(Node<T> *node);
  Node<T> *split(Node<T> *node);
  Node<T> *merge(Node<T> *left, Node<T> *right);

 public:
  list() : head(nullptr), tail(nullptr), size_(0) {}
  list(size_type n);
  list(std::initializer_list<value_type> const &items);
  list(const list &l);
  list(list &&l) noexcept;
  ~list();

  void push_back(const T &value);
  void push_back(T &&value);
  void push_front(const T &value);
  void push_front(T &&value);
  void pop_back();
  void pop_front();
  void swap(list &other);
  void merge(list &other);
  void splice(const_iterator pos, list &other);
  void reverse();
  void unique();
  void sort();

  template <class... Args>
  iterator insert_many(const_iterator pos, Args &&...args);
  template <class... Args>
  void insert_many_back(Args &&...args);
  template <class... Args>
  void insert_many_front(Args &&...args);

  reference front();
  reference back();
  reference operator[](size_type index);
  const_reference front() const;
  const_reference back() const;
  const_reference operator[](size_type index) const;

  iterator begin() { return iterator(head, this); }
  iterator end() { return iterator(nullptr, this); }
  const_iterator cbegin() const { return const_iterator(head, this); }
  const_iterator cend() const { return const_iterator(nullptr, this); }

  size_type size() const { return size_; }
  size_type max_size() const {
    return std::numeric_limits<size_type>::max() / sizeof(Node<T>);
  }
  bool empty() const { return size_ == 0; }
  void clear();

  iterator insert(iterator pos, const T &value);
  iterator insert(iterator pos, T &&value);
  iterator erase(iterator pos);

  list &operator=(const list &other);
  list &operator=(list &&l);

  class ListIterator {
    Node<T> *current;
    const list *list_ptr;
    friend class list;

   public:
    ListIterator() : current(nullptr), list_ptr(nullptr) {}
    explicit ListIterator(Node<T> *node, const list *lst = nullptr)
        : current(node), list_ptr(lst) {}

    ListIterator(const ListIterator &other)
        : current(other.current), list_ptr(other.list_ptr) {}

    ListIterator &operator=(const ListIterator &other) {
      if (this != &other) {
        current = other.current;
        list_ptr = other.list_ptr;
      }
      return *this;
    }

    T &operator*() const { return current->value; }

    ListIterator &operator++() {
      if (current) current = current->next;
      return *this;
    }

    ListIterator operator++(int) {
      ListIterator temp = *this;
      ++(*this);
      return temp;
    }

    ListIterator &operator--() {
      if (!current && list_ptr && list_ptr->tail) {
        current = list_ptr->tail;
      } else if (current) {
        current = current->prev;
      }
      return *this;
    }

    ListIterator operator--(int) {
      ListIterator temp = *this;
      --(*this);
      return temp;
    }

    bool operator==(const ListIterator &other) const {
      return current == other.current;
    }
    bool operator!=(const ListIterator &other) const {
      return current != other.current;
    }
  };

  class ListConstIterator {
    const Node<T> *current;
    const list *list_ptr;
    friend class list<T>;

   public:
    ListConstIterator() : current(nullptr), list_ptr(nullptr) {}
    explicit ListConstIterator(const Node<T> *node, const list *lst = nullptr)
        : current(node), list_ptr(lst) {}

    // Конструктор, создающий ListConstIterator из ListIterator
    ListConstIterator(const ListIterator &other)
        : current(other.current), list_ptr(other.list_ptr) {}

    ListConstIterator &operator=(const ListConstIterator &other) {
      if (this != &other) {
        current = other.current;
        list_ptr = other.list_ptr;
      }
      return *this;
    }

    const T &operator*() const { return current->value; }

    ListConstIterator &operator++() {
      if (current) current = current->next;
      return *this;
    }

    ListConstIterator operator++(int) {
      ListConstIterator temp = *this;
      ++(*this);
      return temp;
    }

    ListConstIterator &operator--() {
      if (!current && list_ptr && list_ptr->tail) {
        current = list_ptr->tail;
      } else if (current) {
        current = current->prev;
      }
      return *this;
    }

    ListConstIterator operator--(int) {
      ListConstIterator temp = *this;
      --(*this);
      return temp;
    }

    bool operator==(const ListConstIterator &other) const {
      return current == other.current;
    }
    bool operator!=(const ListConstIterator &other) const {
      return current != other.current;
    }
  };
};

}  // namespace s21

#include "s21_list.tpp"

#endif  // S21_LIST_H
