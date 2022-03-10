
/*@ <answer>
 *
 * Nombre y Apellidos:
 * Mario Calvarro Marines
 *
 *@ </answer> */

#include <iostream>
#include <fstream>
#include <memory>
#include <cassert>
#include <utility>

const size_t MUL = 7;

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

  //Primero: Valor encontrado
  //Segundo: Valor de la solución 
  //Tercero: Profundidad del valor solución
  template<typename U, typename V>
  std::tuple<bool, T, size_t> bfs(U searchCondition, V cutCondition) const;

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
bool primo(const size_t num) {
    if (num == 0 || num == 1) return false;
    if (num == 2) return true;
    size_t v = num / 2;
    for (size_t i = 2; i <= v; ++i) {
        if (num % i == 0) return false;
    }
    return true;
}

//Primero: Valor encontrado 
//Segundo: Valor de la solución 
//Tercero: Profundidad de la solución
std::tuple<bool, size_t, size_t> resolver(const BinTree<size_t> &tree, const size_t depth) {
    if (tree.empty()) {
        return {false, 0, depth};
    }
    else if (tree.left().empty() && tree.right().empty()) {
        if (tree.root() % MUL == 0 && !primo(tree.root())) {
            return {true, tree.root(), depth};
        }
        else {
            return {false, 0, depth};
        }
    }
    else {
        if (tree.root() % MUL == 0 && !primo(tree.root())) {
            return {true, tree.root(), depth};
        }
        if (primo(tree.root())) {
            return {false, 0, depth};
        }

        auto [found_left, value_left, depth_left] = resolver(tree.left(), depth + 1);
        auto [found_right, value_right, depth_right] = resolver(tree.right(), depth + 1);

        bool found = found_left || found_right;
        size_t value = 0; size_t depth_sol = depth;
        if (found_left && !found_right) {
          value = value_left;
          depth_sol = depth_left;
        }
        else if (!found_left && found_right) {
          value = value_right;
          depth_sol = depth_right;
        }
        else if (found && depth_left <= depth_right) { 
            value = value_left; 
            depth_sol = depth_left;
        }
        else if (found && depth_left > depth_right) {
            value = value_right;
            depth_sol = depth_right;
        }

        return {found, value, depth_sol};
    }
}

void resuelveCaso() {
    // leer los datos de la entrada
    BinTree<size_t> tree = read_tree<size_t>(std::cin);

    // resolver el caso posiblemente llamando a otras funciones
    auto [existence, value, depth] = resolver(tree, 1);

    // escribir la solución
    if (existence) {
        std::cout << value << ' ' << depth;
    }
    else {
        std::cout << "NO HAY";
    }
    std::cout << '\n';
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
