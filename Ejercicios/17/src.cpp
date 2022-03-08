
/*@ <answer>
 *
 * Nombre y Apellidos:
 * Mario Calvarro Marines
 *
 *@ </answer> */

#include <iostream>
#include <fstream>
#include <vector>
#include <stack>
#include <deque>

/*@ <answer>
  
    Las alturas se introducen en una pila e iteramos. 
    Según avanzamos vamos manteniendo el "mejor" mediano 
    que será el que tenga el valor máximo. Si encontramos 
    un valor que tenga un valor inferior al de la derecha 
    y tal que el mediano sea superior a los dos será posible 
    que se encuentre una solución
    Si el mediano no es el máximo cambiamos el de la derecha 
    al nuevo.

 @ </answer> */


// ================================================================
// Escribe el código completo de tu solución aquí debajo
// ================================================================
//@ <answer>

//Devuelve si es posible encontrar un conjunto que impida "tener premio"
//Lineal sobre el número de elementos de la cola doble
bool resolver(std::stack<size_t>& alturas) {
    size_t der = alturas.top();
    size_t med = der; alturas.pop();
    bool sol = false;
    while (!sol && !alturas.empty()) {
        if (alturas.top() > med) {
            med = alturas.top();
        }
        else if (alturas.top() < der && med > der) {
            sol = true;
        }
        alturas.pop();
    }

    return sol;
}

bool resuelveCaso() {
    // leer los datos de la entrada
    size_t num;
    std::cin >> num;

    if (!std::cin)  // fin de la entrada
        return false;
    
    std::stack<size_t> alturas;
    size_t aux;
    for (size_t i = 0; i < num; ++i) {
        std::cin >> aux;
        alturas.push(aux);
    }

    // resolver el caso posiblemente llamando a otras funciones
    bool sol = resolver(alturas);

    // escribir la solución
    std::cout << (!sol? "SIEMPRE PREMIO" : "ELEGIR OTRA") << '\n'; 

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
