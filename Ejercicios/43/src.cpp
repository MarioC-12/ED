/*@ <answer>
 *
 * Nombre y Apellidos:
 * Mario Calvarro Marines
 *
 *@ </answer> */

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <unordered_map>
#include <unordered_set>
#include <set>
#include <map>
#include <queue>

// ================================================================
// Escribe el código completo de tu solución aquí debajo
// ================================================================
//@ <answer>
std::set<std::string> resolver(std::map<std::string, std::unordered_set<int>> &jugadores, std::queue<int> &bingo) {
    std::set<std::string> winners;
    while(!bingo.empty() && winners.empty()) {
        int currNum = bingo.front(); bingo.pop();
        for (auto &[key, elems] : jugadores) {
            if (elems.count(currNum)) {
                elems.erase(currNum);
                if (elems.empty()) {
                    winners.insert(key);
                }
            }
        }
    }
    return winners;
}

bool resuelveCaso() {
    // leer los datos de la entrada
    size_t num;
    std::cin >> num;

    if (num == 0)
        return false;

    // resolver el caso posiblemente llamando a otras funciones
    std::unordered_map<std::string, std::unordered_set<int>> jugadores;
    std::unordered_map<int, std::unordered_set<std::string>> numeros;
    for (size_t i = 0; i < num; ++i) {
        std::string nombre; std::cin >> nombre;
        int aux;
        std::cin >> aux;
        std::unordered_set<int> set_aux;
        while(aux != 0) {
            set_aux.insert(aux);
            numeros[aux].insert(nombre);
            std::cin >> aux;
        }
        jugadores[nombre] = set_aux;
    }
    std::set<std::string> winners;
    std::string bingo_txt; std::cin.ignore(1); std::getline(std::cin, bingo_txt);
    std::stringstream ss(bingo_txt);
    int aux;
    while(ss >> aux && winners.empty()) {
        if(numeros.count(aux)) {
            for (const std::string &nombre : numeros[aux]) {
                jugadores[nombre].erase(aux);
                if (jugadores[nombre].empty()) {
                    winners.insert(nombre);
                }
            }
        }
    }

    // escribir la solución
    for (std::string nombre : winners) {
        std::cout << nombre << ' ';
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
