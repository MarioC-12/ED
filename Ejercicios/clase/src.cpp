
/*@ <answer>
 *
 * Nombre y Apellidos:
 * Mario Calvarro Marines
 *
 *@ </answer> */

#include <iostream>
#include <fstream>
#include <list>
#include <vector>

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
 * Implementación del TAD Conjunto mediante árboles binarios de búsqueda
 *
 * Versión inicial
 */
#include <cassert>
#include <utility>

template <typename T> class SetTree {
public:
  SetTree() : root_node(nullptr), num_elems(0) {}
  SetTree(const SetTree &other)
      : num_elems(other.num_elems), root_node(copy_nodes(other.root_node)) {}
  SetTree(const vector<T> &elems) {
      std::sort(elems.begin(), elems.end());
      return cons(elems, 0, elems.size());
  }
  ~SetTree() { delete_nodes(root_node); }

  void insert(const T &elem) {
    auto [new_root, inserted] = insert(root_node, elem);
    root_node = new_root;
    if (inserted) {
      num_elems++;
    }
  }

  bool contains(const T &elem) const { return search(root_node, elem); }

  void erase(const T &elem) {
    auto [new_root, removed] = erase(root_node, elem);
    root_node = new_root;
    if (removed) {
      num_elems--;
    }
  }

  int size() const { return num_elems; }
  bool empty() const { return num_elems == 0; }

  SetTree &operator=(const SetTree &other) {
    if (this != &other) {
      num_elems = other.num_elems;
      delete_nodes(root_node);
      root_node = copy_nodes(other.root_node);
    }
    return *this;
  }

  void display(std::ostream &out) const {
    out << "{";
    display(root_node, out);
    out << "}";
  }

private:
  struct Node {
    T elem;
    Node *left, *right;

    Node(Node *left, const T &elem, Node *right)
        : left(left), elem(elem), right(right) {}
  };

  Node *root_node;
  int num_elems;

  static Node *copy_nodes(const Node *node) {
    if (node == nullptr) {
      return nullptr;
    } else {
      return new Node(copy_nodes(node->left), node->elem,
                      copy_nodes(node->right));
    }
  }

  static void delete_nodes(const Node *node) {
    if (node != nullptr) {
      delete_nodes(node->left);
      delete_nodes(node->right);
      delete node;
    }
  }

  static std::pair<Node *, bool> insert(Node *root, const T &elem) {
    if (root == nullptr) {
      return {new Node(nullptr, elem, nullptr), true};
    } else if (elem < root->elem) {
      auto [new_root_left, inserted] = insert(root->left, elem);
      root->left = new_root_left;
      return {root, inserted};
    } else if (root->elem < elem) {
      auto [new_root_right, inserted] = insert(root->right, elem);
      root->right = new_root_right;
      return {root, inserted};
    } else {
      return {root, false};
    }
  }

  static bool search(const Node *root, const T &elem) {
    if (root == nullptr) {
      return false;
    } else if (elem == root->elem) {
      return true;
    } else if (elem < root->elem) {
      return search(root->left, elem);
    } else {
      return search(root->right, elem);
    }
  }

  static std::pair<Node *, bool> erase(Node *root, const T &elem) {
    if (root == nullptr) {
      return {root, false};
    } else if (elem < root->elem) {
      auto [new_root_left, erased] = erase(root->left, elem);
      root->left = new_root_left;
      return {root, erased};
    } else if (root->elem < elem) {
      auto [new_root_right, erased] = erase(root->right, elem);
      root->right = new_root_right;
      return {root, erased};
    } else {
      return {remove_root(root), true};
    }
  }

  static Node *remove_root(Node *root) {
    Node *left_child = root->left, *right_child = root->right;
    delete root;
    if (left_child == nullptr && right_child == nullptr) {
      return nullptr;
    } else if (left_child == nullptr) {
      return right_child;
    } else if (right_child == nullptr) {
      return left_child;
    } else {
      auto [lowest, new_right_root] = remove_lowest(right_child);
      lowest->left = left_child;
      lowest->right = new_right_root;
      return lowest;
    }
  }

  static std::pair<Node *, Node *> remove_lowest(Node *root) {
    assert(root != nullptr);
    if (root->left == nullptr) {
      return {root, root->right};
    } else {
      auto [removed_node, new_root_left] = remove_lowest(root->left);
      root->left = new_root_left;
      return {removed_node, root};
    }
  }

  static void display(Node *root, std::ostream &out) {
    if (root != nullptr) {
      if (root->left != nullptr) {
        display(root->left, out);
        out << ", ";
      }
      out << root->elem;
      if (root->right != nullptr) {
        out << ", ";
        display(root->right, out);
      }
    }
  }

  BinTree<T> cons(const std::vector<T> &elems, size_t ini, size_t fin) {
      if (ini == fin) {
        return BinTree<T>; 
      }
      else (ini + 1 == fin) {
        SetTree<T> sol;
        sol.insert(elems[ini]);
        return sol;
      }
      else {
        size_t mitad = (ini + fin) / 2;
        BinTree<T> leftT = cons(elems, ini, mitad);
        BinTree<T> rightT = cons(elems, mitad + 1, fin);
        BinTree<T> sol;
        sol.insert(elems[mitad]); sol.insert(leftT); sol.insert(rightT);
        return sol;
      }
  }
};

template <typename T>
std::ostream &operator<<(std::ostream &out, const SetTree<T> &set) {
  set.display(out);
  return out;
}


// ================================================================
// Escribe el código completo de tu solución aquí debajo
// ================================================================
//@ <answer>

void eliminar_pares(std::list<int> & lista) {
    auto i = lista.begin();
    while (i != lista.end()) {
        if ((*i) % 2 == 0) {
            auto aux = std::next(i);
            lista.erase(i);
            i = aux;
        }
        else {
            ++i;
        }
    }
}

template<typename T>
bool ordenada_ascendente(const std::list<T> & lista) {
    bool res = true;
    auto i = lista.begin();
    while (res && i != (--lista.end())) {
        if (*i > *(++i)) {
            res = false;
        }
    }
    return res;
}

//Hacer para iterador genérico
template<typename T>
bool palindromo(const std::vector<T> & lista) {
    bool res = true;
    auto middle = lista.begin() + (lista.size() / 2);
    auto i = lista.begin(); auto fin = --lista.end();
    while (res && i != middle) {
       if (*i != *fin) {
           res = false;
       }
       ++i; --fin;
    }
    return res;
}

void resuelveCaso() {
    // leer los datos de la entrada
    size_t num;
    std::cin >> num;

    std::list<int> lista;
    std::vector<int> arrayList;
    int aux;
    for (size_t i = 0; i < num; ++i) {
        std::cin >> aux;
        lista.push_back(aux);
        arrayList.push_back(aux);
        std::cout << aux << ' ';
    }
    std::cout << '\n';

    // resolver el caso posiblemente llamando a otras funciones
    std::cout << (ordenada_ascendente(lista)? "UP" : "NOTUP") << '\n';
    std::cout << (palindromo(arrayList)? "NICE" : "NOTNICE") << '\n';
    eliminar_pares(lista);

    for (int i : lista) {
        std::cout << i << ' ';
    }
    std::cout << '\n' << "---\n";


    // escribir la solución
}

//@ </answer>
//  Lo que se escriba dejado de esta línea ya no forma parte de la solución.

int main() {
   // ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
   std::ifstream in("../casos.txt");
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
