
/*@ <answer>
 *
 * Nombre y Apellidos:
 * Mario Calvarro Marines
 *
 *@ </answer> */

#include <iostream>
#include <fstream>
#include <string>
#include <stack>
#include <queue>

/*@ <answer>
  
  Para la primera transformación (primero -> ultimo -> segundo...) almacenamos los 
  caracteres de posiciones pares (empezando en 0) en una cola mientras que las 
  posiciones impares irán a una pila. Una vez se hayan recorrido todas las letras
  volcamos la pila en la cola y devolvemos dicha cola.

  En el caso de la segunda transformación, simplemente creamos una cola que será la solución.
  A su vez, crearemos una pila donde se irán almacenando las constantes consecutivas. En el caso 
  de que aparezca una vocal, volcaremos la pila de consonantes en la cola y, tras esto, incluiremos 
  la vocal. En el caso de que tras recorrer todas las letras, la pila siga con algún elemento
  la volveremos a volcar y la devolveremos. 
  El coste de esta función es lineal de forma amortizada porque las operaciones de la pila son 
  simplemente la de entrada y salida, de la pila, por lo que sería 2n.
 
 @ </answer> */


// ================================================================
// Escribe el código completo de tu solución aquí debajo
// ================================================================
//@ <answer>

//Coste amortizado lineal
void resolver1(std::string& entrada) {
    std::queue<char> sol;
    std::stack<char> pila;
    for (char aux: entrada) {
        if (std::tolower(aux) == 'a' || std::tolower(aux) == 'e' || std::tolower(aux) == 'i' || std::tolower(aux) == 'o' || std::tolower(aux) == 'u') {
            while (!pila.empty()) {
                sol.push(pila.top()); 
                pila.pop();
            }
            sol.push(aux);
        }
        else {
            pila.push(aux);
        }
    }

    while (!pila.empty()) {
        sol.push(pila.top());
        pila.pop();
    }

    size_t i = 0;
    while (!sol.empty()) {
        entrada[i] = sol.front(); sol.pop();
        ++i;
    }
}

// Coste lineal sobre el número de caracteres de entrada 
void resolver2(std::string& entrada) {
    std::queue<char> primeros;
    std::stack<char> ultimos;
    for (size_t i = 0; i < entrada.size(); ++i) {
        if (i % 2 == 0) primeros.push(entrada[i]);
        else ultimos.push(entrada[i]);
    }

    while (!ultimos.empty()) {
        primeros.push(ultimos.top());
        ultimos.pop();
    }

    size_t i = 0;
    while (!primeros.empty()) {
        entrada[i] = primeros.front(); primeros.pop();
        ++i;
    }
}

bool resuelveCaso() {
    // leer los datos de la entrada
    std::string entrada;
    std::getline(std::cin, entrada);
   
    if (!std::cin)  // fin de la entrada
      return false;
   
    // resolver el caso posiblemente llamando a otras funciones
    resolver2(entrada);
    resolver1(entrada);

    // escribir la solución
    std::cout << entrada << '\n';

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
//Coste amortizado lineal
