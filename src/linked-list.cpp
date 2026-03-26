#include "linked-list.hpp"

template <typename T> int insertNode(LinkedList<T> *list, T data) {
  LinkedList<T> *node = new LinkedList<T>;

  node->data = data;

  if (list == nullptr) {
    node->next = list;
    list = node;
  } else {
    list->next = node;
  }

  return 0;
}
