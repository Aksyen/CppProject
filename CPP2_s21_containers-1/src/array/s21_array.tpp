#include "s21_array.h"

namespace s21 {

template <class T, size_t S>
array<T, S>::array() {
  this->arr_ = nullptr;
}

template <class T, size_t S>
array<T, S>::array(std::initializer_list<value_type> const &items) {
  this->arr_ = new value_type[S];
  for (auto it = items.begin(), i = 0; it != items.end(); it++) {
    this->arr_[i++] = *it;
  }
}

template <class T, size_t S>
array<T, S>::array(const array &a) {
  this->arr_ = new value_type[S];
  for (size_t i = 0; i < S; i++) {
    this->arr_[i] = a.arr_[i];
  }
}

template <class T, size_t S>
array<T, S>::array(array<T, S> &&a) {
  this->arr_ = a.arr_;
  a.arr_ = nullptr;
}

template <class T, size_t S>
array<T, S>::~array() {
  delete[] this->arr_;
}
template <class T, size_t S>
array<T, S> &array<T, S>::operator=(array<T, S> &&a) {
  if (this != &a) {
    this->arr_ = a.arr_;
    a.arr_ = nullptr;
  }
  return *this;
}

template <class T, size_t S>
typename array<T, S>::reference array<T, S>::at(size_type pos) {
  if ((int)pos < 0 || pos >= S) {
    throw std::out_of_range("array::at: out of range");
  }
  return this->arr_[pos];
}

template <class T, size_t S>
typename array<T, S>::reference array<T, S>::operator[](size_type pos) {
  return this->arr_[pos];
}

template <class T, size_t S>
typename array<T, S>::const_reference array<T, S>::front() {
  return this->arr_[0];
}

template <class T, size_t S>
typename array<T, S>::const_reference array<T, S>::back() {
  return this->arr_[S - 1];
}

template <class T, size_t S>
typename array<T, S>::iterator array<T, S>::data() {
  return this->arr_;
}

template <class T, size_t S>
typename array<T, S>::iterator array<T, S>::begin() {
  return this->arr_;
}

template <class T, size_t S>
typename array<T, S>::iterator array<T, S>::end() {
  return this->arr_ + S;
}

template <class T, size_t S>
bool array<T, S>::empty() {
  return S == 0;
}

template <class T, size_t S>
typename array<T, S>::size_type array<T, S>::size() {
  return S;
}

template <class T, size_t S>
typename array<T, S>::size_type array<T, S>::max_size() {
  return S;
}

template <class T, size_t S>
void array<T, S>::swap(array<T, S> &other) {
  std::swap(this->arr_, other.arr_);
}

template <class T, size_t S>
void array<T, S>::fill(const_reference value) {
  for (size_t i = 0; i < S; i++) {
    this->arr_[i] = value;
  }
}

};  // namespace s21
