
/*@ <answer>
 *
 * Nombre y Apellidos:
 * Mario Calvarro Marines
 *
 *@ </answer> */

#include <iostream>
#include <fstream>
#include <vector>
#include <stack>
#include <deque>

/*@ <answer>
  
 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.
 
 @ </answer> */


// ================================================================
// Escribe el código completo de tu solución aquí debajo
// ================================================================
//@ <answer>

bool resolver(const std::vector<size_t>& alturas) {
}

bool resuelveCaso() {
    // leer los datos de la entrada
    size_t num;
    std::cin >> num;

    if (!std::cin)  // fin de la entrada
        return false;
    
    std::vector<size_t> alturas (num);
    for (size_t& i: alturas) {
        std::cin >> i;
    }

    // resolver el caso posiblemente llamando a otras funciones
    bool sol = resolver(alturas);

    // escribir la solución
    std::cout << (sol? "SIEMPRE PREMIO" : "ELEGIR OTRA") << '\n'; 

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
