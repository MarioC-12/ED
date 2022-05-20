
/*@ <answer>
 *
 * Nombre y Apellidos:
 * Mario Calvarro Marines
 *
 *@ </answer> */

#include <iostream>
#include <fstream>
#include <vector>
#include <cassert>
#include <iterator>
#include <memory>
#include <queue>
#include <algorithm>

template <class T> class BinTree {

private:
  struct TreeNode;
  using NodePointer = std::shared_ptr<TreeNode>;

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

  template <typename U> void preorder(U func) const {
    preorder(root_node, func);
  }

  template <typename U> void inorder(U func) const { inorder(root_node, func); }

  template <typename U> void postorder(U func) const {
    postorder(root_node, func);
  }

  template <typename U> void levelorder(U func) const;

private:
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

  template <typename U> static void preorder(const NodePointer &node, U func);

  template <typename U> static void inorder(const NodePointer &node, U func);

  template <typename U> static void postorder(const NodePointer &node, U func);
};

template <typename T>
template <typename U>
void BinTree<T>::preorder(const NodePointer &node, U func) {
  if (node != nullptr) {
    func(node->elem);
    preorder(node->left, func);
    preorder(node->right, func);
  }
}

template <typename T>
template <typename U>
void BinTree<T>::inorder(const NodePointer &node, U func) {
  if (node != nullptr) {
    inorder(node->left, func);
    func(node->elem);
    inorder(node->right, func);
  }
}

template <typename T>
template <typename U>
void BinTree<T>::postorder(const NodePointer &node, U func) {
  if (node != nullptr) {
    postorder(node->left, func);
    postorder(node->right, func);
    func(node->elem);
  }
}

template <typename T>
template <typename U>
void BinTree<T>::levelorder(U func) const {
  std::queue<NodePointer> pending;
  if (root_node != nullptr) {
    pending.push(root_node);
  }
  while (!pending.empty()) {
    NodePointer current = pending.front();
    pending.pop();
    func(current->elem);
    if (current->left != nullptr) {
      pending.push(current->left);
    }
    if (current->right != nullptr) {
      pending.push(current->right);
    }
  }
}

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
template<typename T>
BinTree<T> reconstruir_aux(std::queue<T>& preorden, const std::vector<T>& inorden, const size_t ini, const size_t fin) {
    if (ini == fin) {
        return {};
    }
    else {
        T aux = preorden.front();
        preorden.pop();

        auto aux_it = std::find(inorden.begin(), inorden.end(), aux);
        size_t pos = std::distance(inorden.begin(), aux_it);

        BinTree<T> izq = reconstruir_aux(preorden, inorden, ini, pos);
        BinTree<T> der = reconstruir_aux(preorden, inorden, pos + 1, fin);

        return {izq, aux, der};
    }
}

template<typename T>
BinTree<T> reconstruir(std::queue<T>& preorden, const std::vector<T>& inorden) {
    return reconstruir_aux(preorden, inorden, 0, inorden.size());
}

bool resuelveCaso() {
    // leer los datos de la entrada
    size_t numNodos; 
    std::cin >> numNodos;

    if (!std::cin)  // fin de la entrada
        return false;

    std::queue<int> preorden; 
    int auxV;
    for (size_t i = 0; i < numNodos; ++i) {
        std::cin >> auxV;
        preorden.push(auxV);
    }
    std::vector<int> inorden (numNodos);
    for (size_t i = 0; i < numNodos; ++i) {
        std::cin >> auxV;
        inorden[i] = auxV;
    }

    // resolver el caso posiblemente llamando a otras funciones
    BinTree<int> sol = reconstruir(preorden, inorden);

    // escribir la solución
    std::cout << sol << '\n';

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
