/*
 * ---------------------------------------------------
 *                ESTRUCTURAS DE DATOS
 * ---------------------------------------------------
 */
 
 
/*@ <answer>
 
 Introduce el nombre y apellidos de los/as componentes del grupo:
 
 Estudiante 1: Mario Calvarro Marines
 Estudiante 2: Daniel Ramos Rodríguez
 
 Realizamos un recorrido en anchura y para cada uno de los elementos 
 comprobamos si es el primero en su nivel. En caso afirmativo lo 
 añadimos al vector de soluciones.
 
 El coste será O(n) respecto al número de nodos del árbol ya que se 
 se ejecuta un recorrido en anchura que pasa por cada uno de los nodos 
 ejecutando operaciones de coste constante

 @ </answer> */


#include <iostream>
#include <fstream>
#include <cassert>
#include <memory>
#include <utility>
#include <vector>
#include <queue>

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
//Primero: árbol
//Segundo: altura
vector<int> perfil(BinTree<int> tree) {
    std::vector<int> res;
    if (!tree.empty()) {
        std::queue<std::pair<BinTree<int>, int>> cola; 
        cola.push({tree, 1});
        int alturaActual = 0;
        while (!cola.empty()) {
            std::pair<BinTree<int>, int> current = cola.front();
            cola.pop();
            if (current.second > alturaActual) {
                res.push_back(current.first.root());
                alturaActual = current.second;
            }
            if (!current.first.left().empty()) {
                cola.push({current.first.left(), current.second + 1});
            }
            if (!current.first.right().empty()) {
                cola.push({current.first.right(), current.second + 1});
            }
        }
    }
    return res;
}
//@ </answer>

void resuelveCaso() {
    BinTree<int> tree = read_tree<int>(std::cin);
    vector<int> sol = perfil(tree);
    for (int x: sol) {
        std::cout << x << ' ';
    }
    std::cout << '\n';
}

int main() {
  int n; 
  std::cin >> n;
  while (n > 0) {resuelveCaso(); n--;}
  return 0;
}
