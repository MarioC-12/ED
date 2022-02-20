
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
 * Implementación del TAD Pila mediante listas enlazadas simples.
 */
#include <cassert>

template <typename T> class StackLinkedList {
public:
  StackLinkedList() : top_node(nullptr) {}
  StackLinkedList(const StackLinkedList &other)
      : top_node(copy_nodes_from(other.top_node)) {}

  ~StackLinkedList() { free_nodes_from(top_node); }

  StackLinkedList &operator=(const StackLinkedList &other) {
    if (this != &other) {
      free_nodes_from(top_node);
      top_node = copy_nodes_from(other.top_node);
    }
    return *this;
  }

  void push(const T &elem) { top_node = new Node{elem, top_node}; }

  void pop() {
    assert(top_node != nullptr);
    Node *target = top_node;
    top_node = top_node->next;
    delete target;
  }

  T &top() {
    assert(top_node != nullptr);
    return top_node->value;
  }

  const T &top() const {
    assert(top_node != nullptr);
    return top_node->value;
  }

  bool empty() const { return (top_node == nullptr); }

private:
  struct Node {
    T value;
    Node *next;
  };

  Node *copy_nodes_from(Node *other);
  void free_nodes_from(Node *other);

  Node *top_node;
};

template <typename T>
typename StackLinkedList<T>::Node *
StackLinkedList<T>::copy_nodes_from(Node *other) {
  if (other == nullptr) {
    return nullptr;
  } else {
    Node *first = new Node{other->value, nullptr};
    Node *last = first;
    Node *current = other->next;
    while (current != nullptr) {
      Node *new_node = new Node{current->value, nullptr};
      last->next = new_node;
      current = current->next;
      last = new_node;
    }
    return first;
  }
}

template <typename T> void StackLinkedList<T>::free_nodes_from(Node *other) {
  Node *current = other;
  while (current != nullptr) {
    Node *next = current->next;
    delete current;
    current = next;
  }
}

/*@ <answer>
  
  Utilizamos una pila en la que se almacenan los abiertos. 
  En el caso de que aparezca en el texto una letra correspondiente a un cerrado, comprobamos que la pila no 
  está vacía, es decir, que ha aparecido antes un abierto y que, efectivamente, este abierto se corresponde 
  con el cerrado que acaba de aparecer. Tras esto, eliminamos el abierto de la pila. 
  En caso contrario, la pila está vacía o el abierto no se corresponde con el cerrado, la secuencia no está 
  equilibrada.

  El coste en el caso peor es O(n) con n = nº de char en la secuencia que se está procesando ya que si 
  la secuencia está equilibrada será necesario revisar todos los caracteres.
 
 @ </answer> */

bool resolver(const std::string& texto) {
    StackLinkedList<char> pila;
    char aux;

    for (size_t i = 0; i < texto.size(); ++i) {
       aux = texto[i];
       if (aux == '{' || aux == '(' || aux == '[') {
           pila.push(aux);
       }
       else if (aux == '}' || aux == ')' || aux == ']') {
           if (pila.empty()) {
               return false;
           }
           else {
           switch (aux) {
               case '}': 
                   if (pila.top() != '{') return false;
                   else pila.pop();
                   break;
               case ')': 
                   if (pila.top() != '(') return false;
                   else pila.pop();
                   break;
               case ']':
                   if (pila.top() != '[') return false;
                   else pila.pop();
                   break;
           }
           }
       }
    }

    return pila.empty();
}

// ================================================================
// Escribe el código completo de tu solución aquí debajo
// ================================================================
//@ <answer>

bool resuelveCaso() {
   // leer los datos de la entrada
    std::string texto;
    std::getline(std::cin, texto);
   
   if (!std::cin)  // fin de la entrada
      return false;
   
   // resolver el caso posiblemente llamando a otras funciones
   bool res = resolver(texto);
   
   // escribir la solución
   std::cout << (res? "SI" : "NO") << '\n';

   return true;
}

//@ </answer>
//  Lo que se escriba dejado de esta línea ya no forma parte de la solución.

int main() {
   // ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
   std::ifstream in("../casos.txt");
   auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif
   
   while (resuelveCaso());
   
   // para dejar todo como estaba al principio
#ifndef DOMJUDGE
   std::cin.rdbuf(cinbuf);
#endif
   return 0;
}
