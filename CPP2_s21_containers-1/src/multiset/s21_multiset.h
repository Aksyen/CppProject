#ifndef S21_MULTISET_H
#define S21_MULTISET_H

#include "../tree/s21_set_tree.h"
#include "../vector/s21_vector.h"

namespace s21 {

template <class Key>
class multiset : public SetTree<Key, Key> {
 public:
  using key_type = Key;
  using value_type = Key;
  using reference = value_type&;
  using const_reference = const value_type&;
  using iterator = typename SetTree<Key, Key>::iterator;
  using const_iterator = typename SetTree<Key, Key>::const_iterator;
  using size_type = size_t;
  multiset();
  multiset(std::initializer_list<value_type> const& items);
  multiset(const multiset& ms);
  multiset(multiset&& ms);
  ~multiset();
  multiset operator=(multiset&& ms);
  iterator begin() const;
  iterator end() const;
  bool empty();
  size_type size();
  size_type max_size();
  size_type count(const Key& key);
  void clear();
  iterator insert(const value_type& value);
  template <typename... Args>
  s21::vector<std::pair<iterator, bool>> insert_many(Args&&... args);
  void erase(iterator pos);
  void swap(multiset& other);
  void merge(multiset& other);
  bool contains(const Key& key);
  iterator find(const Key& key);
  std::pair<iterator, iterator> equal_range(const Key& key);
  iterator lower_bound(const Key& key);
  iterator upper_bound(const Key& key);
};
};  // namespace s21

#include "s21_multiset.tpp"

#endif  // S21_MULTISET_H
