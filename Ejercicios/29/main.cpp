/*
 * ---------------------------------------------------
 *                ESTRUCTURAS DE DATOS
 * ---------------------------------------------------
 */
 
 
/*@ <answer>
 
 Introduce el nombre y apellidos de los/as componentes del grupo:
 
 Estudiante 1: Mario Calvarro Marines
 Estudiante 2: Daniel Ramos Rodríguez
 
 Dad una explicación de la solución.

 Para cada uno de los nodos el resultado buscado será el máximo de los 
 resultados parciales de sus hijos y el que se pueda construir considerando 
 las mayores ramas a su izquierda y derecha.
 
 Indicad aquí el coste del algoritmo y las recurrencias planteadas en
 el caso del árbol equilibrado, y en el caso del árbol degenerado.

 - Equilibrado: T(n) = 
                { 
                    c_0 si n == 0 
                    2T(n/2) + c_1 si n > 0
                }
   Por lo que el coste será lineal
 
 - Degenerado: T(n) = 
                { 
                    c_0 si n == 0 
                    T(n - 1) + c_1 + c_0 si n > 0
                } 
   Por lo que el coste será lineal
 @ </answer> */


#include <iostream>
#include <fstream>
#include <cassert>
#include <memory>
#include <utility>
#include <algorithm>


// Clase para representar árboles binarios.
// No es posible modificar esta clase para resolver el problema.

template <class T> class BinTree {
public:
  BinTree() : root_node(nullptr) {}

  BinTree(const T &elem)
      : root_node(std::make_shared<TreeNode>(nullptr, elem, nullptr)) {}

  BinTree(const BinTree &left, const T &elem, const BinTree &right)
      : root_node(std::make_shared<TreeNode>(left.root_node, elem,
                                             right.root_node)) {}

  bool empty() const { return root_node == nullptr; }

  const T &root() const {
    assert(root_node != nullptr);
    return root_node->elem;
  }

  BinTree left() const {
    assert(root_node != nullptr);
    BinTree result;
    result.root_node = root_node->left;
    return result;
  }

  BinTree right() const {
    assert(root_node != nullptr);
    BinTree result;
    result.root_node = root_node->right;
    return result;
  }

  void display(std::ostream &out) const { display_node(root_node, out); }

private:
  struct TreeNode;
  using NodePointer = std::shared_ptr<TreeNode>;

  struct TreeNode {
    TreeNode(const NodePointer &left, const T &elem, const NodePointer &right)
        : elem(elem), left(left), right(right) {}

    T elem;
    NodePointer left, right;
  };

  NodePointer root_node;

  static void display_node(const NodePointer &root, std::ostream &out) {
    if (root == nullptr) {
      out << ".";
    } else {
      out << "(";
      display_node(root->left, out);
      out << " " << root->elem << " ";
      display_node(root->right, out);
      out << ")";
    }
  }
};

template <typename T>
std::ostream &operator<<(std::ostream &out, const BinTree<T> &tree) {
  tree.display(out);
  return out;
}

template <typename T> BinTree<T> read_tree(std::istream &in) {
  char c;
  in >> c;
  if (c == '.') {
    return BinTree<T>();
  } else {
    assert(c == '(');
    BinTree<T> left = read_tree<T>(in);
    T elem;
    in >> elem;
    BinTree<T> right = read_tree<T>(in);
    in >> c;
    assert(c == ')');
    BinTree<T> result(left, elem, right);
    return result;
  }
}


using namespace std;


// ----------------------------------------------------------------
// Define aquí la función pedida en el enunciado.
// Puedes definir las funciones auxiliares que necesites, pero siempre
// entre las marcas <answer> y </answer>

//@ <answer>
std::pair<int, int> max_hitos_height(const BinTree<int> &tree) {
    if (tree.empty()) {
        return {0, 0};
    }
    else {
        auto [maxHitosL, heightL] = max_hitos_height(tree.left()); 
        auto [maxHitosR, heightR] = max_hitos_height(tree.right()); 

        int height = std::max(heightL, heightR) + 1;
        int maxHitos = heightR + heightL + 1;

        return {std::max(maxHitos, std::max(maxHitosL, maxHitosR)), height};
    }
}

int max_hitos_visitados(const BinTree<int> &montanya) {
  return max_hitos_height(montanya).first;
}

//@ </answer>

// ¡No modificar nada debajo de esta línea!
// ----------------------------------------------------------------

bool resuelveCaso() {
  BinTree<int> arbol = read_tree<int>(cin);
  if (arbol.empty()) return false;
  cout << max_hitos_visitados(arbol) << '\n';
  return true;
}

int main() {
#ifndef DOMJUDGE
  std::ifstream in("casos.txt");
  auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

  while (resuelveCaso()) { }

#ifndef DOMJUDGE
  std::cin.rdbuf(cinbuf);
  // Descomentar si se trabaja en Windows
  // system("PAUSE");
#endif

  return 0;
}
