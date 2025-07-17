#ifndef S21_BINARY_TREE_TPP
#define S21_BINARY_TREE_TPP

namespace s21 {

template <typename K, typename T>
SetTree<K, T>::Node::Node(K _key, T _value, Node* _parent)
    : left(nullptr),  // Инициализируем указатель на левое поддерево как nullptr
      right(
          nullptr),  // Инициализируем указатель на правое поддерево как nullptr
      parent(_parent),  // Устанавливаем родительский узел
      key(_key),        // Инициализируем ключ узла
      value(_value) {}  // Инициализируем значение узла

// Деструктор: рекурсивно удаляем правое и левое поддеревья
template <typename K, typename T>
SetTree<K, T>::Node::~Node() {
  if (right) delete right;  // Удаляем правое поддерево, если оно существует
  if (left) delete left;  // Удаляем левое поддерево, если оно существует
}

template <typename K, typename T>
SetTree<K, T>::Iterator::Iterator()
    : ptr(nullptr) {}  // Инициализируем итератор с пустым указателем

template <typename K, typename T>
SetTree<K, T>::Iterator::Iterator(Node* _ptr)
    : ptr(_ptr) {}  // Инициализируем итератор с данным узлом

template <typename K, typename T>
typename SetTree<K, T>::Iterator& SetTree<K, T>::Iterator::operator++() {
  if (ptr != nullptr) {  // Проверяем, что итератор не указывает на пустой узел
    if (ptr->right != nullptr) {  // Если у текущего узла есть правое поддерево
      ptr = ptr->right;  // Переходим в правое поддерево
      if (ptr->left != nullptr)  // Если правый узел имеет левое поддерево
        while (ptr->left !=
               nullptr)  // Идем до самого левого узла в правом поддереве
          ptr = ptr->left;
    } else if (ptr->parent !=
               nullptr) {  // Если правого поддерева нет, проверяем родителя
      Iterator tmp(ptr->parent);  // Создаем временный итератор на родителя
      // Ищем первый родительский узел, который больше текущего (для обхода
      // дерева в прямом порядке)
      while ((tmp.ptr->parent != nullptr && ptr->key >= tmp.ptr->key) ||
             ptr->key >= tmp.ptr->key)
        tmp.ptr = tmp.ptr->parent;  // Идем к родителю, если текущий узел не
                                    // больше родительского
      ptr = tmp.ptr;  // Перемещаем итератор на найденный узел
    }
  }
  return *this;  // Возвращаем итератор для дальнейшего использования
}

template <typename K, typename T>
typename SetTree<K, T>::Iterator SetTree<K, T>::Iterator::operator++(int) {
  Iterator tmp(ptr);  // Создаем копию текущего итератора для постфиксной версии
                      // оператора
  ++(*this);  // Вызываем префиксный оператор ++, чтобы переместить итератор
              // вперед
  return tmp;  // Возвращаем старое значение итератора (до инкремента)
}

template <typename K, typename T>
typename SetTree<K, T>::Iterator& SetTree<K, T>::Iterator::operator--() {
  if (ptr != nullptr) {  // Проверяем, что итератор указывает на допустимый узел
                         // (не null)

    // Если у текущего узла есть левое поддерево
    if (ptr->left != nullptr) {
      ptr = ptr->left;  // Переходим в левое поддерево
      // Если у левого узла есть правое поддерево, переходим к самому правому
      // узлу в нем
      if (ptr->right != nullptr)
        while (ptr->right != nullptr) ptr = ptr->right;
    }
    // Если левого поддерева нет, проверяем родительский узел
    else if (ptr->parent != nullptr) {
      iterator tmp(
          ptr->parent);  // Создаем временный итератор для родительского узла
      // Ищем первый родительский узел, который больше текущего. Это позволяет
      // найти узел, который идет сразу перед текущим узлом в порядке обхода
      // бинарного дерева (по убыванию)
      while ((tmp.ptr->parent != nullptr && ptr->key < tmp.ptr->key) ||
             ptr->key < tmp.ptr->key)
        tmp.ptr = tmp.ptr->parent;  // Двигаемся к родителю, пока не найдем
                                    // узел, который больше
      ptr = tmp.ptr;  // Перемещаем итератор на найденный узел
    }
  }
  return *this;  // Возвращаем текущий итератор, чтобы поддерживать цепочку
                 // вызовов
}

template <typename K, typename T>
typename SetTree<K, T>::Iterator SetTree<K, T>::Iterator::operator--(int) {
  Iterator tmp(ptr);  // Создаем копию текущего итератора для постфиксной версии
                      // оператора
  --(*this);  // Вызываем префиксный оператор --, чтобы переместить итератор
              // назад
  return tmp;  // Возвращаем старое значение итератора (до декремента)
}

// Сравниваем два итератора: проверяем, указывают ли они на одинаковые узлы
template <typename K, typename T>
bool SetTree<K, T>::Iterator::operator==(Iterator other) const {
  return other.ptr == this->ptr;  // Возвращаем true, если указатели на узлы
                                  // равны, иначе false
}

// Сравниваем два итератора на неравенство
template <typename K, typename T>
bool SetTree<K, T>::Iterator::operator!=(Iterator other) const {
  return other.ptr != this->ptr;  // Возвращаем true, если указатели на узлы не
                                  // равны, иначе false
}

// Оператор -> позволяет использовать итератор, как указатель на узел
template <typename K, typename T>
typename SetTree<K, T>::Node* SetTree<K, T>::Iterator::operator->() const {
  return ptr;  // Возвращаем указатель на узел, на который указывает итератор
}

// Конструктор по умолчанию для бинарного дерева
template <typename K, typename T>
SetTree<K, T>::SetTree() : size(0), fake(nullptr) {
  // Инициализируем размер дерева как 0 и устанавливаем указатель fake в nullptr
  // Это дерево еще не содержит элементов
}

// Конструктор, принимающий список инициализации (initializer_list)
template <typename K, typename T>
SetTree<K, T>::SetTree(std::initializer_list<value_type> const& items)
    : size(0), fake(nullptr) {
  // Используется для создания дерева с заранее заданными элементами
  // Инициализируем размер дерева как 0 и устанавливаем указатель fake в nullptr

  // Перебираем все элементы в инициализаторе и добавляем их в дерево
  for (auto i = items.begin(); i != items.end(); ++i)
    insert(i->first, i->second);  // Вставляем пару (ключ, значение) в дерево
}

// Конструктор копирования
template <typename K, typename T>
SetTree<K, T>::SetTree(const SetTree& other) : size(0), fake(nullptr) {
  // Создаем новое дерево, которое является копией другого дерева (other)
  // Инициализируем размер дерева как 0 и устанавливаем указатель fake в nullptr

  assign(other);  // Копируем все элементы из другого дерева в текущее дерево
}

// Конструктор перемещения
// Этот конструктор используется для "перемещения" данных из другого дерева в
// текущее
template <typename K, typename T>
SetTree<K, T>::SetTree(SetTree&& other) : size(0), fake(nullptr) {
  assign(other);  // Копируем элементы из дерева other в текущее дерево
  other
      .clear();  // Очищаем дерево other, чтобы оно больше не содержало элементы
  // После вызова other.clear() дерево other будет пустым, а все его ресурсы
  // будут освобождены
}

// Деструктор
template <typename K, typename T>
SetTree<K, T>::~SetTree() {
  if (root.ptr)
    delete root
        .ptr;  // Если дерево не пустое (root.ptr != nullptr), удаляем корень
  // Корень дерева и все связанные с ним узлы рекурсивно удаляются в деструкторе
  // Node
}

// Оператор перемещения для присваивания
// Этот метод используется для перемещения содержимого другого дерева в текущее
// дерево
template <typename K, typename T>
SetTree<K, T> SetTree<K, T>::operator=(SetTree&& other) {
  assign(other);  // Копируем все элементы из дерева other в текущее дерево
  other.clear();  // Очищаем дерево other, так как его элементы были перенесены
                  // в текущее дерево
  return *this;  // Возвращаем текущее дерево после перемещения
}

// Оператор [] (индексации)
// Этот оператор позволяет получить доступ к значению по ключу.
// Если ключа нет в дереве, он будет добавлен с значением по умолчанию (по
// умолчанию это T()).
template <typename K, typename T>
T& SetTree<K, T>::operator[](const K& key) {
  iter.ptr = root.ptr;  // Устанавливаем итератор на корень дерева.
  // Ищем узел с данным ключом.
  Node* result = find(iter.ptr, key);
  // Если узел с таким ключом не найден, вставляем новый узел с ключом и
  // значением по умолчанию.
  if (result == nullptr) result = insert_or_assign(key, T()).first.ptr;
  // Возвращаем значение, связанное с найденным или вставленным узлом.
  return result->value;
}

// Метод at (для доступа с проверкой на существование)
// Этот метод аналогичен оператору [], но генерирует исключение
// std::out_of_range, если ключ не найден в дереве.
template <typename K, typename T>
T& SetTree<K, T>::at(const K& key) {
  iter.ptr = root.ptr;  // Устанавливаем итератор на корень дерева.
  // Ищем узел с данным ключом.
  Node* result = find(iter.ptr, key);
  // Если узел не найден, генерируем исключение out_of_range.
  if (result == nullptr) throw std::out_of_range("");  // Выброс исключения.
  // Возвращаем значение, связанное с найденным узлом.
  return result->value;
}

// Метод для проверки, содержит ли дерево узел с заданным ключом.
// Этот метод рекурсивно ищет ключ в поддеревьях от переданного узла root.
template <typename K, typename T>
bool SetTree<K, T>::contains(Node* root, const K& key) {
  bool result = false;  // Изначально предполагаем, что ключ не найден.
  // Если текущий узел не пустой
  if (root != nullptr) {
    // Если ключ текущего узла совпадает с искомым
    if (root->key == key)
      result = true;  // Устанавливаем результат в true, если ключ найден.
    // Если ключ искомый больше, ищем в правом поддереве
    else if (root->key < key) {
      if (root->right != nullptr)  // Если правый дочерний узел существует
        result = contains(root->right,
                          key);  // Рекурсивный вызов для правого поддерева
    }
    // Если ключ искомый меньше, ищем в левом поддереве
    else if (root->left != nullptr)
      result =
          contains(root->left, key);  // Рекурсивный вызов для левого поддерева
  }
  return result;  // Возвращаем результат: true, если ключ найден, иначе false
}

// метод contains , который проверяет, содержится ли в дереве ключ.
template <typename K, typename T>
bool SetTree<K, T>::contains(const K& key) {
  return contains(root.ptr, key);  // Передаем корень дерева и искомый ключ
}

// Метод find для нахождения узла по ключу и возврата итератора на этот узел.
template <typename K, typename T>
typename SetTree<K, T>::iterator SetTree<K, T>::find(const K& key) {
  iter.ptr = root.ptr;  // Устанавливаем итератор на корень дерева
  iter.ptr = find(iter.ptr, key);  // Ищем узел с данным ключом, начиная с корня

  return iter;  // Возвращаем итератор на найденный узел (или на nullptr, если
                // ключ не найден)
}

// Вставка нового элемента в дерево, используя пару значений (key, obj).
// Это перегрузка метода, которая извлекает ключ и значение из переданной пары
// и вызывает основной метод insert, который работает с отдельными ключом и
// значением.
template <typename K, typename T>
std::pair<typename SetTree<K, T>::iterator, bool> SetTree<K, T>::insert(
    const value_type& value) {
  return insert(
      value.first,
      value.second);  // Передаем ключ и значение в основной метод вставки
}

// Вставка нового элемента в дерево с ключом key и значением obj.
// Метод возвращает пару: итератор на вставленный узел и булево значение,
// которое указывает, был ли элемент вставлен (true — вставлен, false — элемент
// уже существует).
template <typename K, typename T>
std::pair<typename SetTree<K, T>::iterator, bool> SetTree<K, T>::insert(
    const K& key, const T& obj) {
  bool result = false;  // Переменная для хранения результата вставки
  std::pair<iterator, bool>
      pair;  // Пара, которая будет содержать итератор и статус (успех/неудача)
  // Если в дереве нет элемента с таким ключом
  if (!contains(key)) {
    // Вставляем новый элемент или обновляем существующий и сохраняем результат
    // вставки
    pair = insert_or_assign(key, obj);
    result = pair.second;  // Устанавливаем результат вставки: true, если новый
                           // элемент добавлен
  }
  // Возвращаем пару: итератор на элемент и результат вставки (true или false)
  return std::pair<iterator, bool>(pair.first, result);
}

//реализация метода empty
template <typename K, typename T>
bool SetTree<K, T>::empty() {
  return size ==
         0;  // Возвращаем true, если дерево пусто (размер == 0), иначе false
}

// Функция вставки или обновления значения в дереве.
// Если элемент с таким ключом существует, его значение будет обновлено,
// если нет — будет вставлен новый элемент с указанным ключом и значением.
template <typename K, typename T>
std::pair<typename SetTree<K, T>::iterator, bool>
SetTree<K, T>::insert_or_assign(const K& key, const T& obj) {
  bool result = true;  // Флаг для возвращаемого значения (всегда true, так как
                       // элемент вставлен или обновлен)
  // Если существует "фейковый" элемент (для поддержки конца), удаляем его
  if (fake != nullptr && end_i.ptr != nullptr) {
    --end_i;  // Перемещаем итератор на предыдущий элемент (перед фейковым)
    end_i->right = nullptr;  // Отключаем фейковый узел от дерева
    delete fake;  // Удаляем фейковый узел
  }
  // Если дерево не пустое, начинаем вставку с корня дерева
  if (!empty()) iter.ptr = root.ptr;
  // Вставка нового элемента или обновление значения существующего
  iter.ptr = insert(iter.ptr, key, obj);
  size++;  // Увеличиваем размер дерева после вставки
  // Обновляем указатели на начало и конец дерева (для корректного перебора
  // элементов)
  set_begin();  // Обновляем указатель на первый элемент
  set_end();  // Обновляем указатель на последний элемент (включая фейковый
              // узел)
  // Возвращаем пару: итератор на вставленный или обновленный элемент и флаг
  // результата (всегда true)
  return std::pair<iterator, bool>(iter, result);
}

// реализация метода insert
template <typename K, typename T>
typename SetTree<K, T>::Node* SetTree<K, T>::insert(Node* iter, const K& key,
                                                    const T& value) {
  // Если дерево пустое, создаем новый узел и назначаем его корнем
  if (root.ptr == nullptr) {
    root.ptr = new Node(key, value, nullptr);  // Создаем новый узел
    iter = root.ptr;  // Устанавливаем iter в новый узел (он будет корнем)
  } else {
    // Если ключ уже существует в текущем узле, обновляем значение
    if (iter->key == key) {
      iter->value = value;  // Обновляем значение существующего узла
    }
    // Если ключ больше текущего узла, идем вправо
    else if (key > iter->key) {
      if (iter->right == nullptr) {
        // Если правый потомок пуст, создаем новый узел справа
        iter->right =
            new Node(key, value, iter);  // Новый узел справа от текущего
        iter = iter->right;  // Перемещаем iter на только что добавленный узел
      } else {
        // Иначе рекурсивно вызываем insert для правого поддерева
        iter = insert(iter->right, key, value);
      }
    }
    // Если ключ меньше текущего узла, идем влево
    else {
      if (iter->left == nullptr) {
        // Если левый потомок пуст, создаем новый узел слева
        iter->left =
            new Node(key, value, iter);  // Новый узел слева от текущего
        iter = iter->left;  // Перемещаем iter на только что добавленный узел
      } else {
        // Иначе рекурсивно вызываем insert для левого поддерева
        iter = insert(iter->left, key, value);
      }
    }
  }
  return iter;  // Возвращаем указатель на добавленный узел
}

template <typename K, typename T>
void SetTree<K, T>::insert(Node* iter, Node* _node) {
  // Если дерево пустое, назначаем новый узел корнем
  if (root.ptr == nullptr) {
    root.ptr = _node;  // Новый узел становится корнем дерева
    iter = _node;  // Устанавливаем iter на только что добавленный узел
  } else if (_node->key >= iter->key) {
    // Если ключ нового узла больше или равен текущему, идем вправо
    if (iter->right == nullptr) {
      _node->parent = iter;  // Назначаем родителя для нового узла
      iter->right = _node;  // Новый узел становится правым потомком
    } else {
      // Иначе рекурсивно вызываем insert для правого поддерева
      insert(iter->right, _node);
    }
  } else {
    // Если ключ нового узла меньше текущего, идем влево
    if (iter->left == nullptr) {
      _node->parent = iter;  // Назначаем родителя для нового узла
      iter->left = _node;  // Новый узел становится левым потомком
    } else {
      // Иначе рекурсивно вызываем insert для левого поддерева
      insert(iter->left, _node);
    }
  }
}

template <typename K, typename T>
typename SetTree<K, T>::iterator SetTree<K, T>::set_end() {
  // Инициализируем итератор end_i указателем на корень дерева
  end_i.ptr = root.ptr;
  // Если дерево не пустое
  if (root.ptr != nullptr) {
    // Ищем самый правый узел дерева (последний узел в дереве)
    while (end_i->right != nullptr)
      end_i.ptr = end_i->right;  // Переходим вправо, пока не дойдем до самого
                                 // правого узла
    // Создаем фиктивный узел (замещающий позицию после последнего элемента
    // дерева)
    fake = new Node(end_i->key, end_i->value);
    // Назначаем родителем фиктивного узла самый правый узел
    fake->parent = end_i.ptr;
    // Подключаем фиктивный узел как правый потомок самого правого узла
    end_i->right = fake;
    // Итератор теперь указывает на фиктивный узел, который будет играть роль
    // "конца"
    end_i.ptr = fake;
  }
  // Возвращаем итератор, указывающий на фиктивный узел, который считается
  // концом
  return end_i;
}

template <typename K, typename T>
typename SetTree<K, T>::iterator SetTree<K, T>::set_begin() {
  // Инициализируем итератор begin_i указателем на корень дерева
  begin_i.ptr = root.ptr;
  // Если дерево не пустое
  if (root.ptr != nullptr)
    // Ищем самый левый узел дерева (первый узел в дереве)
    while (begin_i->left != nullptr)
      begin_i.ptr =
          begin_i
              ->left;  // Переходим влево, пока не дойдем до самого левого узла
  // Возвращаем итератор, указывающий на самый левый узел
  return begin_i;
}

template <typename K, typename T>
typename SetTree<K, T>::iterator SetTree<K, T>::begin() const {
  // Просто возвращаем итератор на самый левый узел (начало дерева)
  return begin_i;
}

template <typename K, typename T>
typename SetTree<K, T>::iterator SetTree<K, T>::end() const {
  // Возвращаем итератор, указывающий на конец дерева
  // Это тот итератор, который был установлен в методе set_end() на фиктивный
  // узел
  return end_i;
}

template <typename K, typename T>
typename SetTree<K, T>::size_type SetTree<K, T>::Size() {
  // Возвращаем текущий размер дерева, хранящийся в поле size
  // size - это количество элементов в дереве
  return SetTree<K, T>::size;
}

template <typename K, typename T>
typename SetTree<K, T>::size_type SetTree<K, T>::max_size() {
  // Рассчитываем максимально возможный размер дерева
  // Используем максимальное значение типа size_type и делим на размер одного
  // элемента (value_type) Это приближенное значение максимального числа
  // элементов, которое может быть в дереве
  return std::numeric_limits<typename SetTree<K, T>::size_type>::max() /
         sizeof(typename SetTree<K, T>::value_type);
}

template <typename K, typename T>
void SetTree<K, T>::clear() {
  // Если дерево не пустое (корень существует), удаляем все узлы дерева
  if (root.ptr) {
    // Удаление корневого узла (это приведет к рекурсивному удалению всех
    // поддеревьев, если реализован деструктор с рекурсией)
    delete root.ptr;
  }

  // Обнуляем указатели, чтобы они не указывали на несуществующие или
  // освобожденные объекты
  root.ptr =
      nullptr;  // Корень дерева теперь указывает на nullptr, дерево пустое
  fake = nullptr;  // Фиктивный узел больше не нужен
  iter.ptr = nullptr;  // Итератор, скорее всего, больше не используется
  begin_i.ptr = nullptr;  // Итератор на начало дерева больше не нужен
  end_i.ptr = nullptr;  // Итератор на конец дерева больше не нужен

  // Сбрасываем размер дерева на 0, так как дерево теперь пусто
  size = 0;
}

template <typename K, typename T>
void SetTree<K, T>::erase(iterator pos) {
  // Инициализируем временный указатель на узел, который будет удален
  Node* tmp = nullptr;
  // Ищем узел, который соответствует позиции pos в дереве
  for (auto i = begin(); i != end(); ++i) {
    // Если нашли узел, равный pos, сохраняем его в tmp
    if (pos == i) {
      tmp = i.ptr;
    }
  }
  // Если узел был найден (tmp != nullptr)
  if (tmp != nullptr) {
    // Если есть фиктивный узел (используется в set_end), удаляем его
    if (fake != nullptr) {
      --end_i;  // Двигаем итератор на предыдущий элемент
      end_i->right = nullptr;  // Убираем связь с фиктивным узлом
      delete fake;  // Удаляем фиктивный узел
    }
    // Если удаляемый узел является корнем дерева
    if (tmp->parent == nullptr) {
      // Корень дерева теперь будет правым или левым дочерним узлом (если они
      // есть)
      root.ptr = (tmp->right != nullptr) ? tmp->right : tmp->left;
    } else {
      // Если узел не корень, ищем его родителя
      iter.ptr = tmp->parent;
      // Если удаляемый узел — правый потомок, убираем его из правых потомков
      // родителя
      if (iter->right == tmp)
        iter->right = nullptr;
      else
        iter->left = nullptr;
    }
    // Если у узла есть правый потомок и правый потомок не является корнем,
    // вставляем его в дерево
    if (tmp->right != nullptr && root.ptr != tmp->right) {
      iter.ptr = root.ptr;
      insert(iter.ptr, tmp->right);  // Вставляем правого потомка на его место
    }
    // Если у узла есть левый потомок и левый потомок не является корнем,
    // вставляем его в дерево
    if (tmp->left != nullptr && root.ptr != tmp->left) {
      iter.ptr = root.ptr;
      insert(iter.ptr, tmp->left);  // Вставляем левого потомка на его место
    }
    // Уменьшаем размер дерева, так как узел был удален
    size--;
    // Очищаем указатели на потомков удаляемого узла
    tmp->right = nullptr;
    tmp->left = nullptr;
    // Удаляем сам узел
    delete tmp;
    // Обновляем итераторы для начала и конца дерева
    set_begin();  // Устанавливаем begin итератор на самый левый узел
    set_end();  // Устанавливаем end итератор на фиктивный узел (после
                // последнего элемента)
  }
}

template <typename K, typename T>
void SetTree<K, T>::assign(const SetTree& other) {
  // Копируем элементы из другого дерева в текущее дерево
  // Перебираем все элементы в другом дереве и вставляем их в текущее дерево
  for (auto i = other.begin(); i != other.end(); ++i)
    insert(i->key, i->value);  // Вставляем каждый ключ и значение
}

template <typename K, typename T>
void SetTree<K, T>::swap(SetTree& other) {
  // Меняем содержимое текущего дерева с содержимым другого дерева
  // Создаем временное дерево tmp, копируя содержимое другого дерева
  SetTree tmp(other);
  // Очищаем текущее дерево и копируем в него содержимое другого дерева
  other.clear();
  other.assign(*this);
  // Очищаем текущее дерево
  SetTree<K, T>::clear();
  // Копируем содержимое временного дерева tmp в текущее дерево
  assign(tmp);
  // Очищаем временное дерево tmp, освобождая память
  tmp.clear();
}

template <typename K, typename T>
void SetTree<K, T>::merge(SetTree& other) {
  // Сливаем два дерева, добавляя все элементы из другого дерева в текущее
  assign(other);  // Вставляем все элементы другого дерева в текущее дерево
}

template <typename K, typename T>
typename SetTree<K, T>::Node* SetTree<K, T>::find(Node* root, const K& key) {
  // Рекурсивный поиск узла с ключом key в поддереве с корнем root
  if (root != nullptr && root->key != key) {
    // Если ключ текущего узла не совпадает с искомым
    if (root->key < key) {
      // Если ключ больше, ищем в правом поддереве
      if (root->right != nullptr)
        root = find(root->right, key);  // Рекурсивно ищем в правом поддереве
      else
        root = nullptr;  // Если правого поддерева нет, возвращаем nullptr
    } else {
      // Если ключ меньше, ищем в левом поддереве
      if (root->left != nullptr)
        root = find(root->left, key);  // Рекурсивно ищем в левом поддереве
      else
        root = nullptr;  // Если левого поддерева нет, возвращаем nullptr
    }
  }
  // Возвращаем найденный узел (или nullptr, если узел не найден)
  return root;
}

template <typename K, typename T>
typename SetTree<K, T>::iterator SetTree<K, T>::insert(const K& key) {
  // Вставляем новый элемент с ключом key и значением по умолчанию
  // Если существует фиктивный узел (конец дерева), удаляем его
  if (fake != nullptr && end_i.ptr != nullptr) {
    --end_i;  // Сдвигаем итератор конца дерева
    end_i->right = nullptr;  // Убираем ссылку на фиктивный узел
    delete fake;  // Удаляем фиктивный узел
  }
  // Если дерево не пустое, начинаем вставку с корня
  if (!empty()) iter.ptr = root.ptr;
  // Создаем новый узел с данным ключом и значением по умолчанию, и вставляем
  // его в дерево
  insert(iter.ptr, new Node(key, K()));
  // Увеличиваем размер дерева
  size++;
  // Обновляем итераторы для начала и конца дерева
  set_begin();
  set_end();
  // Возвращаем итератор на вставленный узел
  return iter;
}

template <typename K, typename T>
typename SetTree<K, T>::size_type SetTree<K, T>::count(const K& key) {
  // Подсчитываем количество элементов с данным ключом key в дереве
  size_type _count = 0;
  // Перебираем все элементы дерева
  for (auto i = begin(); i != end(); ++i)
    if (key == i->key)  // Если ключ совпадает, увеличиваем счетчик
      _count++;
  // Возвращаем количество элементов с ключом key
  return _count;
}

template <typename K, typename T>
std::pair<typename SetTree<K, T>::iterator, typename SetTree<K, T>::iterator>
SetTree<K, T>::equal_range(const K& key) {
  return std::pair<iterator, iterator>(lower_bound(key), upper_bound(key));
}

template <typename K, typename T>
typename SetTree<K, T>::iterator SetTree<K, T>::lower_bound(const K& key) {
  iter.ptr = nullptr;
  for (auto i = begin(); i != end(); ++i)
    if (key == i->key) {
      iter.ptr = i.ptr;
      break;
    }
  return iter;
}

template <typename K, typename T>
typename SetTree<K, T>::iterator SetTree<K, T>::upper_bound(const K& key) {
  iter.ptr = nullptr;
  auto i = end();
  while (i != begin()) {
    --i;
    if (key == i->key) {
      ++i;
      iter.ptr = i.ptr;
      break;
    }
  }
  return iter;
}

};  // namespace s21

#endif  // S21_BINARY_TREE_TPP