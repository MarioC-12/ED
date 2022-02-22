
/*@ <answer>
 *
 * Nombre y Apellidos:
 * Mario Calvarro Marines
 *
 *@ </answer> */

#include <iostream>
#include <fstream>
#include <string>
#include <stack>
#include <queue>

/*@ <answer>
  
 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.
 
 @ </answer> */


// ================================================================
// Escribe el código completo de tu solución aquí debajo
// ================================================================
//@ <answer>

std::string resolver1(const std::string& entrada) {
    std::string sol;
    std::stack<char> pila;
    for (char aux: entrada) {
        if (std::tolower(aux) == 'a' || std::tolower(aux) == 'e' || std::tolower(aux) == 'i' || std::tolower(aux) == 'o' || std::tolower(aux) == 'u') {
            while (!pila.empty()) {
                sol.push_back(pila.top()); 
                pila.pop();
            }
            sol.push_back(aux);
        }
        else {
            pila.push(aux);
        }
    }

    while (!pila.empty()) {
        sol.push_back(pila.top());
        pila.top();
    }

    return entrada;
}

void resolver2(std::string& entrada) {
    for (size_t i = 0; i < entrada.size(); ++i) {
        if (i % 2 == 0) entrada[i] = entrada[i / 2];
        else entrada[i] = entrada[entrada.size() - i / 2];
    }
}

bool resuelveCaso() {
    // leer los datos de la entrada
    std::string entrada;
    std::getline(std::cin, entrada);
   
    if (!std::cin)  // fin de la entrada
      return false;
   
    // resolver el caso posiblemente llamando a otras funciones
    resolver2(entrada);
    // entrada = resolver1(entrada);

    // escribir la solución
    std::cout << entrada << '\n';

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
