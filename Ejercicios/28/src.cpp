/*
 * ---------------------------------------------------
 *                ESTRUCTURAS DE DATOS
 * ---------------------------------------------------
 *              Facultad de Informática
 *         Universidad Complutense de Madrid
 * ---------------------------------------------------
 */
 
/*
 * MUY IMPORTANTE: Para realizar este ejercicio solo podéis
 * modificar el código contenido entre las etiquetas <answer>
 * y </answer>. Toda modificación fuera de esas etiquetas está
 * prohibida, pues no se tendrá en cuenta para la corrección.
 *
 * Tampoco esta permitido modificar las líneas que contienen
 * las etiquetas <answer> y </answer>, obviamente 
 */
 
//@ <answer>
/*
  Introduce aquí los nombres de los componentes del grupo:
  
  Mario Calvarro Marines
*/
//@ </answer>

#include <iostream>
#include <cassert>
#include <fstream>
#include <memory>
#include <utility>
#include <tuple>

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

using namespace std;

//@ <answer>
//---------------------------------------------------------------
// Modificar a partir de aquí
// --------------------------------------------------------------
template <typename T>
std::tuple<bool, bool, size_t> estable_altura(const BinTree<T> &arbol) {
    if (arbol.empty()) {
        return {true, false, 0};
    }
    else { 
        auto [estableL, pierdeAltL, altL] = estable_altura(arbol.left());
        auto [estableR, pierdeAltR, altR] = estable_altura(arbol.right());

        bool pierdeAltMax = false; 
        bool pierdeAltMin = false;
        bool pierdeAlt = false;
        if (altL > altR) { 
            pierdeAltMax = pierdeAltL;
            pierdeAltMin = pierdeAltR;
            pierdeAlt = true;
        }
        else if (altL < altR) { 
            pierdeAltMax = pierdeAltR;
            pierdeAltMin = pierdeAltL;
            pierdeAlt = true;
        }
        else if (altL == 0 && altR == 0) {
            pierdeAlt = true;
        }

        size_t altMax = std::max(altL, altR);
        size_t altMin = std::min(altL, altR);
        bool estable = estableL && estableR && 
            ((pierdeAltMin && (altMax - altMin < 1)) || (!pierdeAltMin && (altMax - altMin <= 1)));

        size_t alt = std::max(altL, altR) + 1;
        return {estable, pierdeAlt, alt};
    }
}

template <typename T>
bool estable(const BinTree<T> &arbol) {
    auto [sol, aux, aux2] = estable_altura(arbol);
    return sol; 
}

// Función que trata un caso de prueba
void tratar_caso() {
  BinTree<int> t = read_tree<int>(cin);
  cout << (estable(t) ? "SI" : "NO") << "\n";
}

//---------------------------------------------------------------
// No modificar por debajo de esta línea
// --------------------------------------------------------------
//@ </answer>


int main() {
#ifndef DOMJUDGE
  std::ifstream in("../casos.txt");
  auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif
  int num_casos;
  cin >> num_casos;
  
  for (int i = 0; i < num_casos; i++) {
    tratar_caso();
  }

#ifndef DOMJUDGE
  std::cin.rdbuf(cinbuf);
#endif
  return 0;
}

