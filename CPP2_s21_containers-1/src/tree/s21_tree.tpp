#include "s21_tree.h"

namespace s21 {

template <typename Key, typename Value>
BinaryTree<Key, Value>::Iterator::Iterator(Node* root, const BinaryTree* tree)
    : current(nullptr), tree(tree) {  // Здесь уже без параметров по умолчанию
  if (root) {
    pushLeft(root);
    current = ancestors.empty() ? nullptr : ancestors.back();
  }
}

// Вспомогательная функция для обхода вправо (зеркально pushLeft)
template <typename Key, typename Value>
void BinaryTree<Key, Value>::Iterator::pushRight(Node* node) {
  while (node) {
    ancestors.push_back(node);
    node = node->right;  // Двигаемся вправо
  }
}

template <typename Key, typename Value>
void BinaryTree<Key, Value>::Iterator::pushLeft(Node* node) {
  // Пока переданный узел не является nullptr
  while (node) {
    // Добавляем текущий узел в стек предков
    ancestors.push_back(node);

    // Переходим к левому поддереву текущего узла
    node = node->left;
  }
}

template <typename Key, typename Value>
typename BinaryTree<Key, Value>::value_type&
BinaryTree<Key, Value>::Iterator::operator*() const {
  // Если стек предков пуст, итератор находится вне допустимого диапазона
  if (ancestors.empty()) {
    throw std::out_of_range("Iterator out of range");
  }

  // Возвращаем данные узла, находящегося на вершине стека предков
  return ancestors.back()->data;
}

template <typename Key, typename Value>
typename BinaryTree<Key, Value>::value_type*
BinaryTree<Key, Value>::Iterator::operator->() const {
  // Если стек предков пуст, итератор находится вне допустимого диапазона
  if (ancestors.empty()) {
    throw std::out_of_range("Iterator out of range");
  }

  // Возвращаем указатель на данные узла, находящегося на вершине стека предков
  return &(ancestors.back()->data);
}

template <typename Key, typename Value>
typename BinaryTree<Key, Value>::Iterator&
BinaryTree<Key, Value>::Iterator::operator++() {
  // Проверяем, не пуст ли стек предков
  if (!ancestors.empty()) {
    // Текущий узел — вершина стека
    current = ancestors.back();

    // Удаляем текущий узел из стека
    ancestors.pop_back();

    // Если у текущего узла есть правое поддерево, обходим его
    pushLeft(current->right);

    // Обновляем текущий узел
    current = ancestors.empty() ? nullptr : ancestors.back();
  }

  // Возвращаем ссылку на обновлённый итератор
  return *this;
}

template <typename Key, typename Value>
typename BinaryTree<Key, Value>::Iterator&
BinaryTree<Key, Value>::Iterator::operator--() {
  if (!current) {  // Если итератор указывает на end()
    if (tree->root) {
      pushRight(tree->root);  // Идём к самому правому узлу
      current = ancestors.empty() ? nullptr : ancestors.back();
    } else {
      throw std::out_of_range("Iterator out of range: tree is empty");
    }
  } else {
    Node* node = ancestors.back();
    ancestors.pop_back();  // Удаляем текущий узел из стека

    if (node->left) {  // Если есть левое поддерево, спускаемся в него
      pushRight(node->left);
    }

    current = ancestors.empty() ? nullptr : ancestors.back();
  }

  if (!current) {
    throw std::out_of_range("Iterator out of range");
  }

  return *this;
}

template <typename Key, typename Value>
bool BinaryTree<Key, Value>::Iterator::operator==(const Iterator& other) const {
  // Итераторы равны, если их текущие узлы совпадают
  return current == other.current;
}

template <typename Key, typename Value>
bool BinaryTree<Key, Value>::Iterator::operator!=(const Iterator& other) const {
  // Итераторы не равны, если их текущие узлы различны
  return current != other.current;
}

template <typename Key, typename Value>
BinaryTree<Key, Value>::BinaryTree(BinaryTree&& other) noexcept
    : root(other.root), size_(other.size_) {
  // Передаём владение данными из `other` в текущий объект
  other.root = nullptr;  // Обнуляем указатель корня у исходного дерева
  other.size_ = 0;  // Обнуляем размер исходного дерева
}

template <typename Key, typename Value>
BinaryTree<Key, Value>& BinaryTree<Key, Value>::operator=(
    BinaryTree&& other) noexcept {
  // Проверяем самоприсваивание
  if (this != &other) {
    // Очищаем текущее дерево
    clear();

    // Передаём владение данными из `other` в текущий объект
    root = other.root;
    size_ = other.size_;

    // Обнуляем исходный объект
    other.root = nullptr;
    other.size_ = 0;
  }

  // Возвращаем текущий объект
  return *this;
}

template <typename Key, typename Value>
std::pair<typename BinaryTree<Key, Value>::iterator, bool>
BinaryTree<Key, Value>::insert(const Key& key, const Value& value) {
  TreeNode<Key, Value>* parent = nullptr;  // Родитель текущего узла
  TreeNode<Key, Value>* node = root;  // Текущий узел, начинаем с корня

  // Ищем подходящее место для вставки
  while (node) {
    parent = node;
    if (key == node->data.first) {
      // Если ключ уже существует, возвращаем итератор на найденный узел и false
      return {iterator(node), false};
    }
    // Двигаемся влево или вправо в зависимости от значения ключа
    node = (key < node->data.first) ? node->left : node->right;
  }

  // Создаём новый узел с переданным ключом и значением
  TreeNode<Key, Value>* newNode = new TreeNode<Key, Value>({key, value});

  // Вставляем узел в дерево
  if (!parent) {
    // Если дерево пустое, новый узел становится корнем
    root = newNode;
  } else if (key < parent->data.first) {
    // Если ключ меньше родительского, вставляем в левое поддерево
    parent->left = newNode;
  } else {
    // Если ключ больше родительского, вставляем в правое поддерево
    parent->right = newNode;
  }

  ++size_;  // Увеличиваем размер дерева

  // Возвращаем итератор на новый узел и true, так как вставка успешна
  return {iterator(newNode), true};
}

template <typename Key, typename Value>
typename BinaryTree<Key, Value>::iterator BinaryTree<Key, Value>::erase(
    iterator pos) {
  // Извлекаем ключ из позиции итератора
  Key key = pos->first;

  // Сохраняем итератор на следующий элемент перед удалением
  auto next = pos;
  ++next;

  // Удаляем узел с заданным ключом
  erase(key);

  // Возвращаем итератор на следующий элемент
  return next;
}

template <typename Key, typename Value>
void BinaryTree<Key, Value>::erase(const Key& key) {
  bool erased = false;  // Флаг, указывающий, был ли элемент удалён
  root = eraseNode(root, key, erased);  // Удаляем узел с заданным ключом
  if (erased) {
    --size_;  // Если элемент удалён, уменьшаем размер дерева
  }
}

// Вспомогательный метод для рекурсивного удаления узла
template <typename Key, typename Value>
TreeNode<Key, Value>* BinaryTree<Key, Value>::eraseNode(
    TreeNode<Key, Value>* node, const Key& key, bool& erased) {
  if (!node) return nullptr;  // Если узел пуст, возвращаем nullptr

  if (key < node->data.first) {
    // Если ключ меньше, ищем в левом поддереве
    node->left = eraseNode(node->left, key, erased);
  } else if (key > node->data.first) {
    // Если ключ больше, ищем в правом поддереве
    node->right = eraseNode(node->right, key, erased);
  } else {
    // Узел найден
    erased = true;  // Устанавливаем флаг удаления

    if (!node->left && !node->right) {
      // Узел — лист
      delete node;
      return nullptr;
    }

    if (!node->left) {
      // Узел без левого поддерева
      TreeNode<Key, Value>* temp = node->right;
      delete node;
      return temp;
    }

    if (!node->right) {
      // Узел без правого поддерева
      TreeNode<Key, Value>* temp = node->left;
      delete node;
      return temp;
    }

    // Узел с двумя поддеревьями
    TreeNode<Key, Value>* successor = findMin(node->right);

    // Создаём новый узел с данными successor
    TreeNode<Key, Value>* newNode = new TreeNode<Key, Value>(successor->data);

    // Подключаем поддеревья
    newNode->left = node->left;
    newNode->right = eraseNode(node->right, successor->data.first, erased);

    delete node;
    return newNode;
  }

  return node;  // Возвращаем (возможно) изменённый узел
}

// Вспомогательный метод для поиска минимального узла
template <typename Key, typename Value>
TreeNode<Key, Value>* BinaryTree<Key, Value>::findMin(
    TreeNode<Key, Value>* node) const {
  while (node && node->left) {
    node = node->left;  // Двигаемся влево, пока не найдём самый маленький узел
  }
  return node;
}

template <typename Key, typename Value>
TreeNode<Key, Value>* BinaryTree<Key, Value>::findMax(
    TreeNode<Key, Value>* node) const {
  if (!node) {
    return nullptr;
  }
  while (node->right) {
    std::cout << "Moving right from " << node->data.first << " to "
              << node->right->data.first << ".\n";
    node = node->right;
  }
  return node;
}

template <typename Key, typename Value>
typename BinaryTree<Key, Value>::iterator BinaryTree<Key, Value>::find(
    const Key& key) {
  TreeNode<Key, Value>* node = root;  // Начинаем поиск с корня дерева

  // Пока узел не равен nullptr
  while (node) {
    if (key == node->data.first) {
      // Если ключ найден, возвращаем итератор на этот узел
      return iterator(node);
    }

    // Двигаемся влево или вправо в зависимости от значения ключа
    node = (key < node->data.first) ? node->left : node->right;
  }

  // Если ключ не найден, возвращаем итератор на конец дерева
  return end();
}

template <typename Key, typename Value>
typename BinaryTree<Key, Value>::const_iterator BinaryTree<Key, Value>::find(
    const Key& key) const {
  TreeNode<Key, Value>* node = root;  // Начинаем поиск с корня дерева

  // Пока узел не равен nullptr
  while (node) {
    if (key == node->data.first) {
      // Если ключ найден, возвращаем константный итератор на этот узел
      return const_iterator(node);
    }

    // Двигаемся влево или вправо в зависимости от значения ключа
    node = (key < node->data.first) ? node->left : node->right;
  }

  // Если ключ не найден, возвращаем константный итератор на конец дерева
  return end();
}

template <typename Key, typename Value>
void BinaryTree<Key, Value>::clear() {
  // Вызываем вспомогательный метод destroy для удаления всех узлов
  destroy(root);

  // Сбрасываем корень дерева и размер
  root = nullptr;
  size_ = 0;
}

// Вспомогательный метод для рекурсивного удаления узлов
template <typename Key, typename Value>
void BinaryTree<Key, Value>::destroy(TreeNode<Key, Value>* node) {
  if (node) {
    // Рекурсивно удаляем левое поддерево
    destroy(node->left);

    // Рекурсивно удаляем правое поддерево
    destroy(node->right);

    // Удаляем текущий узел
    delete node;
  }
}

template <typename Key, typename Value>
std::pair<typename BinaryTree<Key, Value>::iterator, bool>
BinaryTree<Key, Value>::insert_or_assign(const Key& key, const Value& value) {
  // Используем метод insert для попытки вставить элемент
  auto result = insert(key, value);

  // Если элемент уже существует, обновляем его значение
  if (!result.second) {
    result.first->second = value;  // Меняем значение существующего узла
  }

  // Возвращаем итератор на элемент и информацию об успешности операции вставки
  return result;
}

template <typename Key, typename Value>
void BinaryTree<Key, Value>::swap(BinaryTree& other) {
  // Обмениваем указатели на корни деревьев
  std::swap(root, other.root);

  // Обмениваем размеры деревьев
  std::swap(size_, other.size_);
}

template <typename Key, typename Value>
void BinaryTree<Key, Value>::merge(BinaryTree& other) {
  // Если деревья совпадают или другое дерево пустое, ничего не делаем
  if (this == &other || other.empty()) {
    return;
  }

  // Проходим по всем элементам другого дерева
  for (auto it = other.begin(); it != other.end();) {
    // Если элемент не содержится в текущем дереве, вставляем его
    if (!contains(it->first)) {
      insert(it->first, it->second);
      // Удаляем элемент из другого дерева после вставки
      it = other.erase(it);
    } else {
      ++it;  // Пропускаем элемент, если он уже существует в текущем дереве
    }
  }
}

template <typename Key, typename Value>
void BinaryTree<Key, Value>::printTree() const {
  // Вызываем вспомогательный рекурсивный метод для печати дерева
  printTree(root, 0);
}

// Вспомогательный рекурсивный метод для печати дерева
template <typename Key, typename Value>
void BinaryTree<Key, Value>::printTree(TreeNode<Key, Value>* node,
                                       int depth) const {
  if (node) {
    // Сначала печатаем правое поддерево
    printTree(node->right, depth + 1);

    // Выводим текущий узел с отступами
    std::cout << std::string(depth * 4, ' ') << node->data.first << std::endl;

    // Затем печатаем левое поддерево
    printTree(node->left, depth + 1);
  }
}

template <typename Key, typename Value>
typename BinaryTree<Key, Value>::iterator BinaryTree<Key, Value>::lower_bound(
    const Key& key) {
  TreeNode<Key, Value>* current = root;  // Используем полный тип
  TreeNode<Key, Value>* result = nullptr;

  while (current) {
    if (key <= current->data.first) {
      result = current;         // Потенциальный результат
      current = current->left;  // Идём влево
    } else {
      current = current->right;  // Идём вправо
    }
  }

  return iterator(result, this);
}

template <typename Key, typename Value>
typename BinaryTree<Key, Value>::iterator BinaryTree<Key, Value>::upper_bound(
    const Key& key) {
  TreeNode<Key, Value>* current = root;  // Используем полный тип
  TreeNode<Key, Value>* result = nullptr;

  while (current) {
    if (key < current->data.first) {
      result = current;         // Потенциальный результат
      current = current->left;  // Идём влево
    } else {
      current = current->right;  // Идём вправо
    }
  }

  return iterator(result, this);
}

template <typename Key, typename Value>
std::pair<typename BinaryTree<Key, Value>::iterator,
          typename BinaryTree<Key, Value>::iterator>
BinaryTree<Key, Value>::equal_range(const Key& key) {
  return {lower_bound(key), upper_bound(key)};
}

}  // namespace s21
