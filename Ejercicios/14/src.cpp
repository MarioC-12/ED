
/*@ <answer>
 *
 * Nombre y Apellidos:
 * Mario Calvarro Marines
 *
 *@ </answer> */

#include <iostream>
#include <fstream>
#include <queue>

/*@ <answer>
 
    Tenemos una cola con todos los números y llevamos cuenta de la longitud de los saltos.
    Si un nº no debe ser eliminado, se pone al final de la cola. En caso contrario, se 
    elimina de la cola.
    Al final, quedará en la cola el resultado. 

    Coste en el peor caso: O(n^2) sobre el número de alumnos?

 @ </answer> */


// ================================================================
// Escribe el código completo de tu solución aquí debajo
// ================================================================
//@ <answer>

size_t resolver(std::queue<size_t>& cola, const size_t& salto) {
    size_t i = 0;

    while (cola.size() > 1) {
        size_t tmp;
        
        if (i == salto) {
            cola.pop();
            i = 0; 
        }
        tmp = cola.front();
        cola.pop(); cola.push(tmp);
        ++i;
    }

    return cola.front();
}

bool resuelveCaso() {
    // leer los datos de la entrada
    size_t numAlumnos, salto;
    std::cin >> numAlumnos >> salto;

    if (numAlumnos == 0 || salto == 0)
        return false;

    std::queue<size_t> cola;
    for (size_t i = 1; i <= numAlumnos; ++i) {
        cola.push(i); 
    }
    // resolver el caso posiblemente llamando a otras funciones
    size_t res = resolver(cola, salto);

    // escribir la solución
    std::cout << res << '\n';

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
