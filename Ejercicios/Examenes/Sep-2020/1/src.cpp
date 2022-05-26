/*@ <answer>
 *
 * Nombre y Apellidos:
 * Mario Calvarro Marines
 *
 *@ </answer> */

#include <iostream>
#include <fstream>

/*
 * ---------------------------------------------------
 *                ESTRUCTURAS DE DATOS
 * ---------------------------------------------------
 *              Manuel Montenegro Montes
 *              Facultad de Informática
 *         Universidad Complutense de Madrid
 * ---------------------------------------------------
 */

/*
 * Implementación del TAD Doble Cola utilizando una lista
 * doblemente enlazada con nodo fantasma.
 */

#include <cassert>

template <typename Elem> class Dequeue {
private:
  struct Node {
    Elem value;
    Node *next;
    Node *prev;
  };

public:
  Dequeue() {
    head = new Node;
    head->next = head;
    head->prev = head;
  }

  Dequeue(const Dequeue &other) : Dequeue() { copy_nodes_from(other); }

  ~Dequeue() { delete_nodes(); }

  void push_front(const Elem &elem) {
    Node *new_node = new Node{elem, head->next, head};
    head->next->prev = new_node;
    head->next = new_node;
  }

  void push_back(const Elem &elem) {
    Node *new_node = new Node{elem, head, head->prev};
    head->prev->next = new_node;
    head->prev = new_node;
  }

  void pop_front() {
    assert(head->next != head);
    Node *target = head->next;
    head->next = target->next;
    target->next->prev = head;
    delete target;
  }

  void pop_back() {
    assert(head->next != head);
    Node *target = head->prev;
    target->prev->next = head;
    head->prev = target->prev;
    delete target;
  }

  bool empty() const { return head->next == head; };

  const Elem &front() const {
    assert(head->next != head);
    return head->next->value;
  }

  Elem &front() {
    assert(head->next != head);
    return head->next->value;
  }

  const Elem &back() const {
    assert(head->next != head);
    return head->prev->value;
  }

  Elem &back() {
    assert(head->next != head);
    return head->prev->value;
  }

  Dequeue &operator=(const Dequeue &other) {
    if (this != &other) {
      delete_nodes();
      head = new Node;
      head->next = head->prev = head;
      copy_nodes_from(other);
    }
    return *this;
  }

  void intersect(Dequeue &other);
  void print() {
      Node *curr = head->next;
      while(curr != head) {
          std::cout << curr->value << ' ';
          curr = curr->next;
      }
  }

private:
  Node *head;

  void delete_nodes();
  void copy_nodes_from(const Dequeue &other);
};

template <typename Elem> void Dequeue<Elem>::delete_nodes() {
  Node *current = head->next;
  while (current != head) {
    Node *target = current;
    current = current->next;
    delete target;
  }

  delete head;
}

template <typename Elem>
void Dequeue<Elem>::copy_nodes_from(const Dequeue &other) {
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

// ================================================================
// Escribe el código completo de tu solución aquí debajo
// ================================================================
//@ <answer>
using namespace std;

template <typename T>
void Dequeue<T>::intersect(Dequeue<T> &other) {
    Node *thisCurr = head->next, *otherCurr = other.head->next;    
    while(thisCurr != head && otherCurr != head) {
        if (thisCurr->value < otherCurr->value) {
            Node *aux = thisCurr->next;
            thisCurr->prev->next = thisCurr->next;
            thisCurr->next->prev = thisCurr->prev;
            delete thisCurr;
            thisCurr = aux;
        }
        else if (thisCurr->value > otherCurr->value) {
            otherCurr = otherCurr->next;
        }
        else {
            thisCurr = thisCurr->next;
            otherCurr = otherCurr->next;
        }
    }

    while(thisCurr != head) {
        Node *aux = thisCurr->next;
        thisCurr->prev->next = thisCurr->next;
        thisCurr->next->prev = thisCurr->prev;
        delete thisCurr;
        thisCurr = aux;
    }
}

void resuelveCaso() {
    // leer los datos de la entrada
    Dequeue<int> ini; Dequeue<int> other;

    int aux;
    cin >> aux;
    while (aux != 0) {
        ini.push_back(aux);
        cin >> aux;
    }
    cin >> aux;
    while (aux != 0) {
        other.push_back(aux);
        cin >> aux;
    }

    // resolver el caso posiblemente llamando a otras funciones
    ini.intersect(other);

    // escribir la solución
    ini.print();
    cout << '\n';
}

//@ </answer>
//  Lo que se escriba dejado de esta línea ya no forma parte de la solución.

int main() {
   // ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
   std::ifstream in("casos.txt");
   auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif
   
   int numCasos;
   std::cin >> numCasos;
   for (int i = 0; i < numCasos; ++i)
      resuelveCaso();
   
   // para dejar todo como estaba al principio
#ifndef DOMJUDGE
   std::cin.rdbuf(cinbuf);
#endif
   return 0;
}
