/*@ <answer>
 *
 * Nombre y Apellidos:
 * Mario Calvarro Marines
 *
 *@ </answer> */

#include <iostream>
#include <fstream>
#include <unordered_map>

// ================================================================
// Escribe el código completo de tu solución aquí debajo
// ================================================================
//@ <answer>

void resuelveCaso() {
    // leer los datos de la entrada
    size_t sol = 1, numCap;
    size_t ini = 0;
    // clave capitulo, valor posición en el vector
    std::unordered_map<int, size_t> capitulos;
    std::cin >> numCap;

    // resolver el caso posiblemente llamando a otras funciones
    int aux;
    size_t solTemp = 0;
    for (size_t i = 0; i < numCap; ++i) {
        std::cin >> aux;
        if (capitulos.count(aux) && capitulos[aux] >= ini) {
            if (i - ini > sol) {
                sol = i - ini;
            }
            ini = capitulos[aux] + 1;
        }
        capitulos[aux] = i;
    }

    if (numCap - ini > sol) {
        sol = numCap - ini;
    }

    // escribir la solución
    std::cout << sol << '\n';
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
