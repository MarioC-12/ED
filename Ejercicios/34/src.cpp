
/*@ <answer>
 *
 * Nombre y Apellidos:
 * Mario Calvarro Marines
 *
 *@ </answer> */

#include <cassert>
#include <string>
#include <iostream>
#include <fstream>
#include <iterator>
#include <memory>
#include <queue>
#include <stack>
#include <utility>

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

  template <typename U> void inorder(U func) const {
    std::stack<NodePointer> st;

    descend_and_push(root_node, st);

    while (!st.empty()) {
      NodePointer current = st.top();
      st.pop();

      func(current->elem);

      descend_and_push(current->right, st);
    }
  }

  template <typename U> void postorder(U func) const {
    postorder(root_node, func);
  }

  template <typename U> void levelorder(U func) const;

  class iterator {
  public:
    const T &operator*() const {
      assert(!st.empty());
      return st.top()->elem;
    }

    const T *operator->() const { return &operator*(); }

    iterator &operator++() {
      assert(!st.empty());
      NodePointer top = st.top();
      st.pop();
      BinTree::descend_and_push(top->right, st);
      return *this;
    }

    iterator operator++(int) {
      iterator previous = *this;
      ++(*this);
      return previous;
    }

    bool operator==(const iterator &other) const { return st == other.st; }

    bool operator!=(const iterator &other) const {
      return !this->operator==(other);
    }

  private:
    friend class BinTree;

    iterator() {}

    iterator(const NodePointer &root) { BinTree::descend_and_push(root, st); }

    std::stack<NodePointer> st;
  };

  iterator begin() const { return iterator(root_node); }

  iterator end() const { return iterator(); }

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

  static void descend_and_push(const NodePointer &node,
                               std::stack<NodePointer> &st);

  template <typename U> static void preorder(const NodePointer &node, U func);

  template <typename U> static void postorder(const NodePointer &node, U func);
};

template <typename T>
void BinTree<T>::descend_and_push(const NodePointer &node,
                                  std::stack<NodePointer> &st) {
  NodePointer current = node;
  while (current != nullptr) {
    st.push(current);
    current = current->left;
  }
}

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

template <typename T> 
std::tuple<bool, T, T> isSearch(const BinTree<T> &tree) {
    if (tree.left().empty() && tree.right().empty()) {
        return {true, tree.root(), tree.root()};
    }
    else if (tree.left().empty() && !tree.right().empty()) {
        auto [isSearchR, minR, maxR] = isSearch(tree.right());

        bool search = isSearchR && (tree.root() < minR);
        T min = std::min(tree.root(), minR);
        T max = std::max(tree.root(), maxR);

        return {search, min, max};
    }
    else if (!tree.left().empty() && tree.right().empty()) {
        auto [isSearchL, minL, maxL] = isSearch(tree.left());

        bool search = isSearchL && (tree.root() > maxL);
        T min = std::min(tree.root(), minL);
        T max = std::max(tree.root(), maxL);

        return {search, min, max};
    }
    else {
        auto [isSearchL, minL, maxL] = isSearch(tree.left());
        auto [isSearchR, minR, maxR] = isSearch(tree.right());

        bool search = isSearchR && isSearchL && (tree.root() < minR) && (tree.root() > maxL);
        T min = std::min(tree.root(), std::min(minL, minR)); 
        T max = std::max(tree.root(), std::max(maxL, maxR)); 

        return {search, min, max};
    }
}

template <typename T> 
bool resolver(const BinTree<T> &tree) {
    if (tree.empty()) {
        return true;
    }
    return std::get<0>(isSearch(tree));
}

bool resuelveCaso() {
    char type;
    std::cin >> type;

    if (!std::cin)  // fin de la entrada
      return false;

    bool sol = false;

    switch(type) {
        case 'N': 
            {
            BinTree<int> tree = read_tree<int>(std::cin);
            sol = resolver(tree);
            }
            break;
        case 'P':
            {
            BinTree<std::string> tree = read_tree<std::string>(std::cin);
            sol = resolver(tree);
            }
            break;
        default: 
            break;
    }

    // escribir la solución
    std::cout << (sol? "SI" : "NO") << '\n';

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
