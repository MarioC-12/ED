/*
 * ---------------------------------------------------
 *                ESTRUCTURAS DE DATOS
 * ---------------------------------------------------
 */

/*@ <answer>
 
 Introduce el nombre y apellidos de los/as componentes del grupo:
 
 Estudiante 1: Mario Calvarro Marines
 Estudiante 2: Daniel Ramos Rodríguez
  
 Dad una explicación de la solución y justificad su coste.
 
 Se evalua la expresión correspondiente al hijo derecho de la raíz 
 del AST y se asigna al nombre de variable que viene dado por el 
 valor del hijo izquierdo.

 La evaluación se realiza recursivamente sabiendo que si un nodo es 
 una hoja es porque le corresponde un valor numérico, ya que es un 
 literal u otra variable, y si es un nodo interno es porque será un 
 operador que se aplicará a sus dos hijos.

 El coste será O(M*S*log(N)) en el caso peor. Esto se debe a que 
 se debe a que se realizarán M evaluaciones de árboles en las que 
 se visitarán S nodos. A lo sumo el nº de variables será del orden 
 de S/2 y el coste de acceder a cada una de estas será O(log(N)) con
 N el nº total de variables.
 
 @ </answer> */

#include <iostream>
#include <fstream>
#include <memory>
#include <cassert>
#include <stack>
#include <cctype>
#include <optional>
#include <map>
#include <sstream>

/*
  Implementación de la clase BinTree para representar árboles binarios.
 */

template<class T>
class BinTree {
public:

  BinTree(): root_node(nullptr) { }
  
  BinTree(const T &elem): root_node(std::make_shared<TreeNode>(nullptr, elem, nullptr)) { }
  
  BinTree(const BinTree &left, const T &elem, const BinTree &right)
    :root_node(std::make_shared<TreeNode>(left.root_node, elem, right.root_node)) { }
  

  bool empty() const {
    return root_node == nullptr;
  }

  const T & root() const {
    assert(root_node != nullptr);
    return root_node->elem;
  }

  BinTree left() const {
    assert (root_node != nullptr);
    BinTree result;
    result.root_node = root_node->left;
    return result;
  }

  BinTree right() const {
    assert (root_node != nullptr);
    BinTree result;
    result.root_node = root_node->right;
    return result;
  }

  void display(std::ostream &out) const {
    display_node(root_node, out);
  }
  
private:
  // Las definiciones de TreeNode y NodePointer dependen recursivamente
  // la una de la otra. Por eso declaro 'struct TreeNode;' antes de NodePointer
  // para que el compilador sepa, cuando analice la definición de NodePointer,
  // que TreeNode va a ser definida más adelante.

  struct TreeNode;
  using NodePointer = std::shared_ptr<TreeNode>;

  struct TreeNode {
    TreeNode(const NodePointer &left, const T &elem, const NodePointer &right): elem(elem), left(left), right(right) { }

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

/*
 * Operador << para mostrar un árbol por pantalla. No es necesario hacer esto
 * en la práctica, pero os lo dejo por si queréis depurar.
 */
template<typename T>
std::ostream & operator<<(std::ostream &out, const BinTree<T> &tree) {
  tree.display(out);
  return out;
}


/*
 * Función para leer un árbol binario de la entrada. El formato es el siguiente:
 *
 *  Árbol vacío: .
 *  Árbol no vacío: (i x r)  donde i es la representación del hijo izquierdo
 *                                 x es la raíz
 *                                 r es la representación del hijo derecho
 */
template<typename T>
BinTree<T> read_tree(std::istream &in) {
  char c;
  in >> c;
  if (c == '.') {
    return BinTree<T>();
  } else {
    assert (c == '(');
    BinTree<T> left = read_tree<T>(in);
    T elem;
    in >> elem;
    BinTree<T> right = read_tree<T>(in);
    in >> c;
    assert (c == ')');
    BinTree<T> result(left, elem, right);
    return result;
  }
}

/*
 * Analizador léxico del lenguaje
 */

class Lexer {
public:
  Lexer(std::istream &in): in(in) { }

  std::string peek() {
    if (next != "") {
      return next;
    } else {
      next = read_next();
      return next;
    }
  }

  std::string get() {
    std::string result = peek();
    next = "";
    return result;
  }

private:
  std::istream &in;

  std::string read_next() {
    std::ostringstream result;
    char current;
    in >> current;
    while (iswspace(current)) {
      in >> current;
    }


    if (isdigit(current)) {
      result << current;
      while (isdigit(in.peek())) {
        in >> current;
        result << current;
      }
    } else if (isalpha(current)) {
      result << current;
      while (isalnum(in.peek())) {
        in >> current;
        result << current;
      }
    } else if (current == '+' || current == '-' || current == '*' || current == ';' || current == '(' || current == ')') {
      result << current;
    } else if (current == ':') {
      result << current;
      in >> current;
      if (current != '=') throw std::domain_error(std::string("invalid token: :") + current);
      result << current;
    } else {
      throw std::domain_error(std::string("invalid_token: ") + current);
    }

    return result.str();
  }



private:
  std::string next;
};

/*
 * Analizador sintáctico del lenguaje
 */


class Parser {
public:
  Parser(std::istream &in): l(in) { }

  BinTree<std::string> parse() {
    return S();
  }

private:
  Lexer l;

  bool is_identifier(const std::string &token) {
    return (!token.empty() && isalpha(token[0]));
  }

  bool is_identifier_or_number(const std::string &token) {
    return (!token.empty() && isalnum(token[0]));
  }

    
  BinTree<std::string> S() {
    std::string identifier = l.get();
    if (!is_identifier(identifier)) throw std::domain_error(std::string("identifier expected, found ") + identifier);

    std::string equal = l.get();
    if (equal != ":=") throw std::domain_error(std::string(":= expected, found ") + equal);

    BinTree<std::string> rhs = E();

    std::string semicolon = l.get();
    if (semicolon != ";") throw std::domain_error(std::string("; expected, found ") + semicolon);

    return { { identifier }, ":=", rhs };
  }

  BinTree<std::string> E() {
    BinTree<std::string> term = T();
    return Ep(term);
  }

  BinTree<std::string> Ep(const BinTree<std::string> &left) {
    std::string op = l.peek();
    if (op == "+" || op == "-") {
      l.get();
      BinTree<std::string> term = T();
      return Ep({ left, op, term });
    } else {
      return left;
    }
  }

  BinTree<std::string> T() {
    BinTree<std::string> factor = F();
    return Tp(factor);
  }

  BinTree<std::string> Tp(const BinTree<std::string> &left) {
    std::string op = l.peek();
    if (op == "*") {
      l.get();
      BinTree<std::string> factor = F();
      return Tp({left, "*", factor});
    } else {
      return left;
    }
  }

  BinTree<std::string> F() {
    std::string next = l.get();
    if (is_identifier_or_number(next)) {
      return { next };
    } else if (next == "(") {
      BinTree<std::string> inner = E();
      std::string closing = l.get();
      if (closing != ")") throw std::domain_error(std::string(") expected, found ") + closing);
      return inner;
    } else {
      throw std::domain_error(std::string("number or identifier expected, found ") + next);
    }
  }
};

/*
 * Función que lee una sentencia y devuelve su árbol sintáctico.
 */

BinTree<std::string> parse(std::istream &in) {
  return Parser(in).parse();
}

#include <map>
using namespace std;

/* ======================================================================
 * Escribe tu solución entre las etiquetas "answer" que se muestran a
 * continuación.
 *
 * No es necesario añadir ni modificar ningún método de las clases
 * anteriores, pero puedes implementar las funciones auxiliares
 * que necesites.
 * ====================================================================== */
/*@ <answer> */

int toInt(const std::string &value) {
  int res = 0;
  int pot = 1;
  for (int i = value.size() - 1; i >= 0; --i) {
    res += (value[i] - '0') * pot;
    pot *= 10;
  }

  return res;
}
 
int resolver(const BinTree<std::string> &value, const std::map<std::string, int> &dic) {
  if (value.left().empty() && value.right().empty()) {
    if (value.root()[0] >= 'a' && value.root()[0] <= 'z') {
      return dic.at(value.root());
    }
    else {
      return toInt(value.root());
    }
  }
  else {
    switch(value.root()[0]) {
        case '+': {
          return resolver(value.left(), dic) + resolver(value.right(), dic);
        }
        case '-': {
          return resolver(value.left(), dic) - resolver(value.right(), dic); 
        }
        case '*': {
          return resolver(value.left(), dic) * resolver(value.right(), dic);
        }
        default: {
          return 0;
        }
    }
  }
}

bool resuelveCaso() {
  int N;
  cin >> N;
  if (N == 0)
    return false;
  
  std::map<std::string, int> dic;

  for (size_t i = 0; i < N; ++i) {
    BinTree<std::string> value = parse(std::cin);
    dic[value.left().root()] = resolver(value.right(), dic);
  } 
  
  for (const auto &[key, value] : dic) {
    std::cout << key << " = " << value << '\n';
  }

  std::cout << "---\n";

  return true;
}

/*@ </answer> */

int main() {
#ifndef DOMJUDGE
  std::ifstream in("casos.txt");
  auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif
  
  while (resuelveCaso()) {}

#ifndef DOMJUDGE
  std::cin.rdbuf(cinbuf);
#endif
  return 0;
}

/*
 
 3
 x := 3;
 y := 5;
 z := x + y;
 2
 b := 5 + 6 * 3;
 a := b - 1;
 3
 x := 1;
 x := x * 2;
 x := x * 2;
 0
 */
