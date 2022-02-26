/*
 * ---------------------------------------------------
 *                ESTRUCTURAS DE DATOS
 * ---------------------------------------------------
 */

/*
 * MUY IMPORTANTE: Para realizar este ejercicio solo puedes
 * modificar el código contenido entre las etiquetas <answer>
 * y </answer>. Toda modificación fuera de esas etiquetas está
 * prohibida, pues no será corregida.
 *
 * Tampoco esta permitido modificar las líneas que contienen
 * las etiquetas <answer> y </answer>, obviamente :-)
 */


/*@ <answer>
 
 Introduce el nombre y apellidos de los/as componentes del grupo:

 Estudiante 1: Mario Calvarro Marines
 Estudiante 2: Daniel Ramos Rodríguez

 
 Dad una explicación de la solución y justificad su coste.
 
 @ </answer> */


#include <iostream>
#include <fstream>
#include <stack>
#include <queue>

// ----------------------------------------------------------------
//@ <answer>

// Coste en el caso peor: O(n) donde n es el número de elementos de 
// la entrada. 
// En primer lugar, se itera una sola vez cada elemento de la entrada y 
// cada uno de ellos pasará, a lo sumo, una sola vez por la pila. Por lo 
// tanto, el coste total en lo referente a las operaciones relacionadas 
// con la pila a lo largo de todo el algoritmo será lineal.
// El resto de operaciones de cada iteración tiene coste constante.

bool resuelveCaso() {
    std::queue<int> elems;
    int aux;
    std::cin >> aux;
    while (aux != -1) {
        elems.push(aux);
        std::cin >> aux;
    }
    if (elems.empty()) return false;

    std::queue<int> resultados;
    std::stack<int> pila;
    pila.push(elems.front());
    resultados.push(-1);
    elems.pop();

    while (!elems.empty()) {
        while (!pila.empty() && pila.top() <= elems.front()) {
            pila.pop();
        }
        if (pila.empty()) { resultados.push(-1); }
        else { resultados.push(pila.top()); }
        pila.push(elems.front()); 
        elems.pop();
    }
  
    while (!resultados.empty()) {
        if (resultados.front() == -1) {
            std::cout << "NO HAY";
        }
        else {
            std::cout << resultados.front();
        }
        std::cout << '\n';
        resultados.pop();
    }

    std::cout << "---\n";

    return true;
}

//@ </answer>

// ¡No modificar nada debajo de esta línea!
// ----------------------------------------------------------------

int main() {
#ifndef DOMJUDGE
  std::ifstream in("casos.txt");
  auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

  while (resuelveCaso()) { }

#ifndef DOMJUDGE
  std::cin.rdbuf(cinbuf);
#endif
  return 0;
}
