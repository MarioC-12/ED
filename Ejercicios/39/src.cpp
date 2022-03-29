/*@ <answer>
 *
 * Nombre y Apellidos:
 * Mario Calvarro Marines
 *
 *@ </answer> */

#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <string>
#include <sstream>

// ================================================================
// Escribe el código completo de tu solución aquí debajo
// ================================================================
//@ <answer>

bool resuelveCaso() {
    // leer los datos de la entrada
    size_t nOraciones;
    std::cin >> nOraciones;

    if (nOraciones == 0)
        return false;

    // resolver el caso posiblemente llamando a otras funciones
    std::cin.ignore(1);
    std::string linea, palabra;
    std::map<std::string, std::vector<size_t>> res;
    for (size_t i = 0; i < nOraciones; ++i) {
        std::getline(std::cin, linea); 
        std::stringstream ss(linea);
        while (ss >> palabra) {
            if (palabra.size() > 2) {
                for (char & c: palabra) c = std::tolower(c);
                if (!res.count(palabra)) {
                    res.insert(std::pair<std::string, std::vector<size_t>> 
                            (palabra, std::vector<size_t>()));
                    res[palabra].push_back(i+1);
                }
                else if (res[palabra].back() != (i + 1)) {
                    res[palabra].push_back(i+1); 
                }
            }
        }
    }

    // escribir la solución
    for (auto [key, val] : res) {
        std::cout << key << ' ';
        for (size_t ln : val) {
            std::cout << ln << ' ';
        }
        std::cout << '\n';
    }
    std::cout << "---\n";

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
