template <typename T>
struct LinkedList {
  T data;
  struct LinkedList* next;
};

template<typename T>
int insertNode(LinkedList<T> *, T);
