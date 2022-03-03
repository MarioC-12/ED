
/*@ <answer>
 *
 * Nombre y Apellidos:
 * Mario Calvarro Marines
 *
 *@ </answer> */

#include <iostream>
#include <fstream>
#include <list>

/*@ <answer>
  
    Recorremos la linea letra por letra, llevando una list que será la solución y 
    un iterador que nos indica donde introducir la nueva letra que se va a introducir. 

    En el caso de que aparezca un signo especial se modificará el iterador. 

 @ </answer> */


// ================================================================
// Escribe el código completo de tu solución aquí debajo
// ================================================================
//@ <answer>

//Coste lineal sobre el número de caracteres de la linea
std::list<char> resolver (const std::string& linea) {
    std::list<char> sol;
    auto it = sol.begin();
    for(char aux: linea) {
        char auxLow = std::tolower(aux);
        if (auxLow == '-') {
            //Inicio
            it = sol.begin();
        }
        else if (auxLow == '+') {
            //Fin
            it = sol.end();
        }
        else if (auxLow == '*') {
            //Derecha
            if (it != sol.end()) {
                ++it; 
            }
        }
        else if (auxLow == '3') {
            //Supr
            if (it != sol.end()) {
                it = sol.erase(it);
            }
        }
        else {
            sol.insert(it, aux);
        }
    }
    return sol;
}

bool resuelveCaso() {
    // leer los datos de la entrada
    std::string linea;
    std::getline(std::cin, linea);

    if (!std::cin)  // fin de la entrada
        return false;

    std::list<char> sol = resolver(linea);

    // escribir la solución
    while (!sol.empty()) {
        std::cout << sol.front();
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
