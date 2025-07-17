#include "s21_vector.h"

namespace s21 {

template <class T>
vector<T>::vector() {
  this->arr_ = nullptr;
  this->size_ = 0;
  this->capacity_ = 0;
  this->iter = nullptr;
};

template <class T>
vector<T>::vector(size_type n) {
  this->arr_ = n ? new value_type[n] : nullptr;
  this->size_ = n;
  this->capacity_ = n;
  this->iter = arr_;
};

template <class T>
vector<T>::vector(std::initializer_list<value_type> const &items) {
  this->arr_ = new value_type[items.size()];
  for (auto it = items.begin(), i = 0; it != items.end(); it++) {
    this->arr_[i++] = *it;
  }
  this->size_ = this->capacity_ = items.size();
  this->iter = arr_;
};

template <class T>
vector<T>::vector(const vector &v) {
  this->arr_ = new value_type[v.size_];
  for (size_type i = 0; i < v.size_; i++) {
    this->arr_[i] = v.arr_[i];
  }
  this->size_ = v.size_;
  this->capacity_ = v.capacity_;
  this->iter = v.arr_;
};

template <class T>
vector<T>::vector(vector &&v) {
  this->arr_ = v.arr_;
  this->size_ = v.size_;
  this->capacity_ = v.capacity_;
  this->iter = v.arr_;

  v.arr_ = nullptr;
  v.size_ = 0;
  v.capacity_ = 0;
  v.iter = nullptr;
}

template <class T>
vector<T> &vector<T>::operator=(vector &&v) {
  if (this != &v) {
    delete[] this->arr_;
    this->arr_ = v.arr_;
    this->size_ = v.size_;
    this->capacity_ = v.capacity_;
    this->iter = v.arr_;

    v.arr_ = nullptr;
    v.size_ = 0;
    v.capacity_ = 0;
    v.iter = nullptr;
  }
  return *this;
}

template <class T>
vector<T>::~vector() {
  delete[] this->arr_;
}

template <class T>
typename vector<T>::reference vector<T>::at(size_type pos) {
  if ((int)pos < 0 || pos >= this->size_) {
    throw std::out_of_range("at()");
  }
  return this->arr_[pos];
}

template <class T>
typename vector<T>::reference vector<T>::operator[](size_type pos) {
  return this->arr_[pos];
}

template <class T>
typename vector<T>::const_reference vector<T>::front() {
  if (this->size_ < 1) {
    throw std::out_of_range("front()");
  }
  return this->arr_[0];
}

template <class T>
typename vector<T>::const_reference vector<T>::back() {
  if (this->size_ < 1) {
    throw std::out_of_range("back()");
  }
  return this->arr_[size_ - 1];
}

template <class T>
typename vector<T>::iterator vector<T>::data() {
  return this->arr_;
}

template <class T>
typename vector<T>::iterator vector<T>::begin() {
  return this->arr_;
}

template <class T>
typename vector<T>::iterator vector<T>::end() {
  return this->arr_ + this->size_;
}

template <class T>
bool vector<T>::empty() {
  return this->size_ == 0;
}

template <class T>
typename vector<T>::size_type vector<T>::size() {
  return this->size_;
};

template <class T>
typename vector<T>::size_type vector<T>::max_size() {
  return std::numeric_limits<vector<T>::size_type>::max() / sizeof(value_type) /
         2;
};

template <class T>
void vector<T>::reserve(size_type size) {
  if (size > this->capacity_) {
    value_type *new_arr = new value_type[size];

    for (size_type i = 0; i < size_; i++) {
      new_arr[i] = std::move(this->arr_[i]);
    }
    delete[] arr_;
    this->arr_ = new_arr;
    this->capacity_ = size;
  }
}

template <class T>
typename vector<T>::size_type vector<T>::capacity() {
  return this->capacity_;
};

template <class T>
void vector<T>::shrink_to_fit() {
  if (this->size_ != this->capacity_) {
    value_type *new_arr = new value_type[size_];
    for (size_type i = 0; i < size_; i++) {
      new_arr[i] = this->arr_[i];
    }
    delete[] arr_;
    this->arr_ = new_arr;
    this->capacity_ = size_;
  }
}

template <class T>
void vector<T>::clear() {
  this->size_ = 0;
}

template <class T>
typename vector<T>::iterator vector<T>::insert(iterator pos,
                                               const_reference value) {
  size_type index = pos - this->arr_;
  if (this->size_ == this->capacity_) {
    reserve(this->capacity_ ? this->capacity_ * 2 : 1);
    pos = arr_ + index;
  }
  for (size_type i = this->size_; i > index; --i) {
    this->arr_[i] = this->arr_[i - 1];
  }
  this->arr_[index] = value;
  this->size_++;
  return this->arr_ + index;
}

template <class T>
void vector<T>::erase(iterator pos) {
  size_type index = pos - this->arr_;
  for (size_type i = index; i < this->size_ - 1; i++) {
    this->arr_[i] = this->arr_[i + 1];
  }
  this->size_--;
}

template <class T>
void vector<T>::push_back(const_reference value) {
  if (this->size_ == this->capacity_) {
    reserve(this->capacity_ ? this->capacity_ * 2 : 1);
  }
  this->arr_[this->size_] = value;
  this->size_++;
}

template <class T>
void vector<T>::pop_back() {
  if (this->size_ > 0) {
    this->size_--;
  }
}

template <class T>
void vector<T>::swap(vector &other) {
  value_type *new_arr_ = other.arr_;
  size_type new_size_ = other.size_;
  size_type new_capacity_ = other.capacity_;

  other.arr_ = this->arr_;
  other.size_ = this->size_;
  other.capacity_ = this->capacity_;

  this->arr_ = new_arr_;
  this->size_ = new_size_;
  this->capacity_ = new_capacity_;
}

template <class T>
template <class... Args>
typename vector<T>::iterator vector<T>::insert_many(const_iterator pos,
                                                    Args &&...args) {
  iterator position = (iterator)pos;
  for (const auto &arg : {args...}) {
    position = insert(position, arg) + 1;
  }
  return position;
}

template <class T>
template <class... Args>
void vector<T>::insert_many_back(Args &&...args) {
  insert_many(this->end(), args...);
}

};  // namespace s21