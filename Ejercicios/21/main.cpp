//Mario Calvarro Marines. DG05. ED-UCM

#include <cassert>
#include <fstream>
#include <iostream>

template <typename T>
class ListLinkedDouble {
private:
  struct Node {
    T value;
    Node *next;
    Node *prev;
  };
  
public:
  ListLinkedDouble() : num_elems(0) {
    head = new Node;
    head->next = head;
    head->prev = head;
  }
  
  ListLinkedDouble(const ListLinkedDouble &other) : ListLinkedDouble() {
    copy_nodes_from(other);
    num_elems = other.num_elems;
  }
  
  ~ListLinkedDouble() { delete_nodes(); }
  
  void push_front(const T &elem) {
    Node *new_node = new Node{elem, head->next, head};
    head->next->prev = new_node;
    head->next = new_node;
    num_elems++;
  }
  
  void push_back(const T &elem) {
    Node *new_node = new Node{elem, head, head->prev};
    head->prev->next = new_node;
    head->prev = new_node;
    num_elems++;
  }
  
  void pop_front() {
    assert(num_elems > 0);
    Node *target = head->next;
    head->next = target->next;
    target->next->prev = head;
    delete target;
    num_elems--;
  }
  
  void pop_back() {
    assert(num_elems > 0);
    Node *target = head->prev;
    target->prev->next = head;
    head->prev = target->prev;
    delete target;
    num_elems--;
  }
  
  int size() const { return num_elems; }
  
  bool empty() const { return num_elems == 0; };
  
  const T &front() const {
    assert(num_elems > 0);
    return head->next->value;
  }
  
  T &front() {
    assert(num_elems > 0);
    return head->next->value;
  }
  
  const T &back() const {
    assert(num_elems > 0);
    return head->prev->value;
  }
  
  T &back() {
    assert(num_elems > 0);
    return head->prev->value;
  }
  
  const T &operator[](int index) const {
    assert(0 <= index && index < num_elems);
    Node *result_node = nth_node(index);
    return result_node->value;
  }
  
  T &operator[](int index) {
    assert(0 <= index && index < num_elems);
    Node *result_node = nth_node(index);
    return result_node->value;
  }
  
  ListLinkedDouble &operator=(const ListLinkedDouble &other) {
    if (this != &other) {
      delete_nodes();
      head = new Node;
      head->next = head->prev = head;
      copy_nodes_from(other);
      num_elems = other.num_elems;
    }
    return *this;
  }
  
  void display(std::ostream &out) const;
  
  void display() const { display(std::cout); }
  
  class iterator {
  public:
    iterator & operator++() {
      assert(current != head);
      current = current->next;
      return *this;
    }
    
    iterator & operator--() {
      assert(current != head->next);
      current = current->prev;
      return *this;
    }

    T &operator*() const {
      assert(current != head);
      return current->value;
    }
    
    bool operator==(const iterator &other) const {
      return (head == other.head) && (current == other.current);
    }
    
    bool operator!=(const iterator &other) const { return !(*this == other); }
    
    friend class ListLinkedDouble;
    
  private:
    iterator(Node *head, Node *current) : head(head), current(current) {}
    Node *head;
    Node *current;
  };

  iterator begin() { return iterator(head, head->next); }
  
  iterator end() { return iterator(head, head); }

  class reverse_iterator {
  public:
    reverse_iterator & operator++() {
      assert(current != head->next);
      current = current->prev;
      return *this;
    }
    
    T &operator*() const {
      assert(current != head->next);
      return current->prev->value;
    }

    bool operator==(const reverse_iterator &other) const {
      return (head == other.head) && (current == other.current);
    }
    
    bool operator!=(const reverse_iterator &other) const { return !(*this == other); }
    
    friend class ListLinkedDouble;
    
  private:
    reverse_iterator(Node *head, Node *current) : head(head), current(current) {}
    Node *head;
    Node *current;
  };
  
  reverse_iterator rbegin() { return reverse_iterator(head, head); }
  
  reverse_iterator rend() { return reverse_iterator(head, head->next); }
  
private:
  Node *head;
  int num_elems;
  
  Node *nth_node(int n) const;
  void delete_nodes();
  void copy_nodes_from(const ListLinkedDouble &other);
};

template <typename T>
typename ListLinkedDouble<T>::Node *ListLinkedDouble<T>::nth_node(int n) const {
  int current_index = 0;
  Node *current = head->next;
  
  while (current_index < n && current != head) {
    current_index++;
    current = current->next;
  }
  
  return current;
}

template <typename T> void ListLinkedDouble<T>::delete_nodes() {
  Node *current = head->next;
  while (current != head) {
    Node *target = current;
    current = current->next;
    delete target;
  }
  
  delete head;
}

template <typename T>
void ListLinkedDouble<T>::copy_nodes_from(const ListLinkedDouble &other) {
  Node *current_other = other.head->next;
  Node *last = head;
  
  while (current_other != other.head) {
    Node *new_node = new Node{current_other->value, head, last};
    last->next = new_node;
    last = new_node;
    current_other = current_other->next;
  }
  head->prev = last;
}

template <typename T>
void ListLinkedDouble<T>::display(std::ostream &out) const {
  out << "[";
  if (head->next != head) {
    out << head->next->value;
    Node *current = head->next->next;
    while (current != head) {
      out << ", " << current->value;
      current = current->next;
    }
  }
  out << "]";
}

template <typename T>
std::ostream &operator<<(std::ostream &out, const ListLinkedDouble<T> &l) {
  l.display(out);
  return out;
}

using namespace std;

void resuelveCaso() {
  ListLinkedDouble<int> lista;
  int v;
  cin >> v;
  while (v != 0) {
    lista.push_back(v);
    cin >> v;
  }
  
  auto i = lista.end();
  while (i != lista.begin()) {
      --i;
      std::cout << *i << ' ';
  }

  std::cout << '\n';

}

int main() {
#ifndef DOMJUDGE
  std::ifstream in("casos.txt");
  auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif
  
  int casos;
  cin >> casos;
  
  while (casos--) {
    resuelveCaso();
  }
  
#ifndef DOMJUDGE
  std::cin.rdbuf(cinbuf);
#endif
  return 0;
}
