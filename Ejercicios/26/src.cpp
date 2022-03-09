
/*@ <answer>
 *
 * Nombre y Apellidos:
 * Mario Calvarro Marines
 *
 *@ </answer> */

#include <iostream>
#include <fstream>
#include <cassert>
#include <memory>
#include <utility>

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
  // Las definiciones de TreeNode y NodePointer dependen recursivamente
  // la una de la otra. Por eso declaro 'struct TreeNode;' antes de NodePointer
  // para que el compilador sepa, cuando analice la definición de NodePointer,
  // que TreeNode va a ser definida más adelante.

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

// ================================================================
// Escribe el código completo de tu solución aquí debajo
// ================================================================
//@ <answer>

//Primero: Nº de equipos 
//Segundo: Nº de excursionistas en la ruta más larga
std::pair<size_t, size_t> resolver(const BinTree<size_t> &tree) {
    std::pair<size_t, size_t> res {0, 0};
    if (tree.empty()) {
        return {0, 0};
    }
    else {
        auto [numEquipos_left, numExcursionistas_left] = resolver(tree.left());
        auto [numEquipos_right, numExcursionistas_right] = resolver(tree.right());

        size_t numEquipos = numEquipos_left + numEquipos_right;
        if (numEquipos_right == 0 && numEquipos_left == 0 && tree.root() != 0) {
            ++numEquipos;
        }
        size_t numExcursionistas = std::max(numExcursionistas_left, numExcursionistas_right) + tree.root();
        return {numEquipos, numExcursionistas};
    }
}

void resuelveCaso() {
    // leer los datos de la entrada
    BinTree<size_t> tree = read_tree<size_t>(std::cin);

    // resolver el caso posiblemente llamando a otras funciones
    //Nº de equipos de rescate y nº excursionistas en la ruta mayor
    auto [numEquipos, numExcursionistas] = resolver(tree);

    // escribir la solución
    std::cout << numEquipos << ' ' << numExcursionistas << '\n';
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
