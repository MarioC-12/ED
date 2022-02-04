
/*
 * Mario Calvarro Marines
 */
 

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

#include "Hora.h"
#include "Pelicula.h"

/*@ <answer>
  
 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.
 
 @ </answer> */


//@ <answer>
bool resuelveCaso() {
   // leer los datos de la entrada
   size_t numPeliculas;
   std::cin >> numPeliculas;
   
   if (numPeliculas == 0)
      return false;
   
   // resolver el caso posiblemente llamando a otras funciones
   std::vector<Pelicula> cartelera(numPeliculas);
   for (size_t i = 0; i < numPeliculas; ++i) {
       std::cin >> cartelera[i];
   }

   std::sort(cartelera.begin(), cartelera.end());

   for (size_t i = 0; i < numPeliculas; ++i) {
       std::cout << cartelera[i] << '\n';
   }

   std::cout << "---\n";
   return true;
}

//@ </answer>

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
