
/*@ <answer>
 *
 * Nombre y Apellidos:
 * Mario Calvarro Marines
 *
 *@ </answer> */

#include <iostream>
#include <fstream>
#include <list>
#include <vector>

/*@ <answer>
  
 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.
 
 @ </answer> */


// ================================================================
// Escribe el código completo de tu solución aquí debajo
// ================================================================
//@ <answer>

void eliminar_pares(std::list<int> & lista) {
    auto i = lista.begin();
    while (i != lista.end()) {
        if ((*i) % 2 == 0) {
            auto aux = std::next(i);
            lista.erase(i);
            i = aux;
        }
        else {
            ++i;
        }
    }
}

template<typename T>
bool ordenada_ascendente(const std::list<T> & lista) {
    bool res = true;
    auto i = lista.begin();
    while (res && i != (--lista.end())) {
        if (*i > *(++i)) {
            res = false;
        }
    }
    return res;
}

//Hacer para iterador genérico
template<typename T>
bool palindromo(const std::vector<T> & lista) {
    bool res = true;
    auto middle = lista.begin() + (lista.size() / 2);
    auto i = lista.begin(); auto fin = --lista.end();
    while (res && i != middle) {
       if (*i != *fin) {
           res = false;
       }
       ++i; --fin;
    }
    return res;
}

void resuelveCaso() {
    // leer los datos de la entrada
    size_t num;
    std::cin >> num;

    std::list<int> lista;
    std::vector<int> arrayList;
    int aux;
    for (size_t i = 0; i < num; ++i) {
        std::cin >> aux;
        lista.push_back(aux);
        arrayList.push_back(aux);
        std::cout << aux << ' ';
    }
    std::cout << '\n';

    // resolver el caso posiblemente llamando a otras funciones
    std::cout << (ordenada_ascendente(lista)? "UP" : "NOTUP") << '\n';
    std::cout << (palindromo(arrayList)? "NICE" : "NOTNICE") << '\n';
    eliminar_pares(lista);

    for (int i : lista) {
        std::cout << i << ' ';
    }
    std::cout << '\n' << "---\n";


    // escribir la solución
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
