
/*@ <answer>
 *
 * Nombre y Apellidos:
 * Mario Calvarro Marines
 *
 *@ </answer> */

#include <iostream>
#include <fstream>
#include <queue>
#include <stack>

/*@ <answer>
  
    Para la realización de este ejercicio mantenemos tres estructuras: 
    una cola con la sucesión de máximos, otra con los k elementos "actuales" 
    y una doble cola con los posibles máximos "actuales".
    
    El procedimiento es el siguiente.
    En primer lugar introducimos el "siguiente" elemento en la cola de actuales.
    En el caso de que la cola tenga un tamaño k debemos eliminar el primer elemento. 
    Tras esto, introducimos el siguiente elemento en la lista de posibles máximos del 
    siguiente modo: vemos los ultimos elementos que serán los posibles más pequeños y 
    si el elemento actual es mayor los vamos sacando hasta llegar a uno igual o superior. 
    En ese momento introducimos el actual al final de esta doble cola. 
    Anteriormente, hemos eliminado el primer elemento en el caso de que este coincida 
    con el primer elemento de la cola actual. Como el primer elemento de la lista de 
    posibles máximos es el máximo actual si este no coincide con el elemento saliente 
    esto quiere decir que este ya ha salido de la lista de posibles máximos por lo que 
    no necesitamos considerarlo.

    Por último, si la cola de actuales tiene tamaño k, añadimos el primer elemento de 
    la lista de máximos.
 
 @ </answer> */


// ================================================================
// Escribe el código completo de tu solución aquí debajo
// ================================================================
//@ <answer>

// Coste lineal sobre N
void resolver(const size_t N, const size_t k, std::queue<size_t>& sol) {
    size_t aux;
    size_t max = 0;
    std::queue<size_t> colaActual;
    std::deque<size_t> possibleMax;
    for (size_t i = 0; i < N; ++i) {
        std::cin >> aux;
        if (colaActual.size() < k) {
            colaActual.push(aux);
        }
        else {
            if (colaActual.front() == possibleMax.front()) {
                possibleMax.pop_front();
            }
            colaActual.pop();
            colaActual.push(aux);
        }
        if (possibleMax.empty()) {
            possibleMax.push_back(aux);
        }
        else {
            while (!possibleMax.empty() && possibleMax.back() < aux) {
                possibleMax.pop_back();
            }
            possibleMax.push_back(aux);
        }
        if (colaActual.size() == k) {
            sol.push(possibleMax.front());
        }
    }
        
}

bool resuelveCaso() {
    // leer los datos de la entrada
    size_t N, k;
    std::cin >> N >> k;

    if (!std::cin)  // fin de la entrada
        return false;

    // resolver el caso posiblemente llamando a otras funciones

    std::queue<size_t> sol;
    
    resolver(N, k, sol);

    // escribir la solución
    while (!sol.empty()) {
        std::cout << sol.front() << ' ';
        sol.pop();
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
