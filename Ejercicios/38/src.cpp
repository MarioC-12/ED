/*@ <answer>
 *
 * Nombre y Apellidos:
 * Mario Calvarro Marines
 *
 *@ </answer> */

#include <iostream>
#include <fstream>
#include <string>
#include <map>

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
   
   std::cin.ignore(1);
   std::map<std::string, int> correcciones;
   std::string name;
   std::string correccion;
   int suma;
   for (size_t i = 0; i < num; ++i) {
       std::getline(std::cin, name);
       std::cin >> correccion; std::cin.ignore(1);
       suma = (correccion == "CORRECTO")? 1 : -1;
       if (!correcciones.count(name)) {
           correcciones[name] = suma;
       }
       else {
           correcciones[name] += suma;
       }
   }
   
   // escribir la solución
   for (auto const& [key, value] : correcciones) {
       if (value != 0) {
           std::cout << key << ", " << value << '\n';
       }
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
