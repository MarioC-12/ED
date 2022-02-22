
/*@ <answer>
 *
 * Nombre y Apellidos:
 * Mario Calvarro Marines
 *
 *@ </answer> */

#include <iostream>
#include <fstream>
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

bool resuelveCaso() {
    // leer los datos de la entrada
    size_t num;
    std::cin >> num;

    if (num == 0)
        return false;

    // resolver el caso posiblemente llamando a otras funciones
    std::deque<int> sol;

    int aux;
    for (size_t i = 0; i < num; ++i) {
        std::cin >> aux;
        if (aux >= 0) sol.push_back(aux);
        else sol.push_front(aux);
    }

    // escribir la solución
    for (size_t i = 0; i < num; ++i) {
        std::cout << sol.front() << ' ';
        sol.pop_front();
    }
    std::cout << '\n';

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
