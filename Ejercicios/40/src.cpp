
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
#include <map>
#include <tuple>
#include <vector>
#include <utility>

// ================================================================
// Escribe el código completo de tu solución aquí debajo
// ================================================================
//@ <answer>

template <typename K, typename V>
void readMap(std::map<K, V> &dic) {
    K key; V value;
    std::string linea;
    std::getline(std::cin, linea);
    std::stringstream ss(linea);

    while(ss >> key) {
        ss >> value;
        dic[key] = value;
    }
}

void resuelveCaso() {
    // leer los datos de la entrada
    std::map<std::string, size_t> dicOg, dicCh;

    readMap<std::string, size_t>(dicOg);
    readMap<std::string, size_t>(dicCh);

    // resolver el caso posiblemente llamando a otras funciones
    bool res = false;
    auto itOg = dicOg.begin();
    auto itCh = dicCh.begin();
    std::vector<std::string> newKeys, removedKeys, changedKeys;
    while (itOg != dicOg.end() && itCh != dicCh.end()) {
        if (itOg->first == itCh->first) {
            if (itOg->second != itCh->second) {
               changedKeys.push_back(itOg->first);
               res = true;
            }
            ++itOg; ++itCh;
        }
        else if(itOg->first < itCh->first) {
            removedKeys.push_back(itOg->first);
            res = true;
            ++itOg;
        }
        else {
            newKeys.push_back(itCh->first);
            res = true;
            ++itCh;
        }
    }

    while (itOg != dicOg.end()) {
        removedKeys.push_back(itOg->first);
        res = true;
        ++itOg;
    }
    while (itCh != dicCh.end()) {
        newKeys.push_back(itCh->first);
        res = true;
        ++itCh;
    }

    // escribir la solución
    if (!res) std::cout << "Sin cambios\n";
    else {
        if (newKeys.size() > 0) {
            std::cout << "+ ";
            for (std::string key : newKeys) {
                std::cout << key << ' ';
            }
            std::cout << '\n';
        }
        if (removedKeys.size() > 0) {
            std::cout << "- ";
            for (std::string key : removedKeys) {
                std::cout << key << ' ';
            }
            std::cout << '\n';
        }
        if (changedKeys.size() > 0) {
            std::cout << "* ";
            for (std::string key : changedKeys) {
                std::cout << key << ' ';
            }
            std::cout << '\n';
        }
    }

    std::cout << "---\n";
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
   std::cin.ignore();
   for (int i = 0; i < numCasos; ++i)
      resuelveCaso();
   
   // para dejar todo como estaba al principio
#ifndef DOMJUDGE
   std::cin.rdbuf(cinbuf);
#endif
   return 0;
}
