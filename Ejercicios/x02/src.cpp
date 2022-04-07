/*@ <answer>
 *
 * Nombre y Apellidos:
 * Mario Calvarro Marines
 *
 *@ </answer> */

#include <iostream>
#include <fstream>

// ================================================================
// Escribe el código completo de tu solución aquí debajo
// ================================================================
//@ <answer>
size_t resolver(const std::vector<size_t> &clave, const std::vector<size_t> &mensaje) {
}

bool resuelveCaso() {
    // leer los datos de la entrada
    size_t tamClave; std::cin >> tamClave;

    if (!std::cin)  // fin de la entrada
        return false;

    std::vector<size_t> clave; 
    for (size_t i = 0; i < tamClave; ++i) {
        std::cin >> clave[i];
    }
    size_t tamMen; std::cin >> tamMen;
    std::vector<size_t> mensaje;
    for (size_t i = 0; i < tamMen; ++i) {
        std::cin >> mensaje[i];
    }

    // resolver el caso posiblemente llamando a otras funciones
    std::cout << resolver(clave, mensaje) << '\n';

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
