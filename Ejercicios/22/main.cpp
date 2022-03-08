/*
 * ---------------------------------------------------
 *                ESTRUCTURAS DE DATOS
 * ---------------------------------------------------
 */


/*@ <answer>
 
 Introduce el nombre y apellidos de los/as componentes del grupo:
 
 Estudiante 1: Mario Calvarro Marines
 Estudiante 2: Daniel Ramos Rodríguez
 
 
 Dad una explicación de la solución y justificad su coste.

 Coste en el caso peor: O(n*m) donde n es el nº de filas y m el de columnas 
 de la matriz. Esto se debe a que se itera sobre cada fila 2 veces haciendo 
 operaciones de coste constante.

 Se itera sobre las filas de la matriz comparando cada elemento con el que se 
 encuentra inmediatamente abajo a la derecha. En caso de que sean distintos, 
 el resultado es falso. 
 
 @ </answer> */

#include <iostream>
#include <fstream>
#include <list>
using namespace std;

// ----------------------------------------------------------------
//@ <answer>

//O(n*m)
bool es_toeplitz(const list<list<int>> &matriz) {
    auto row1 = matriz.begin();
    auto row2 = ++matriz.begin();
    while (row2 != matriz.end()) {
        auto col1 = (*row1).begin();
        auto col2 = ++(*row2).begin();
        while (col2 != (*row2).end()) {
            if (*col1 != *col2) {
                return false; 
            }
            else {
                ++col1; ++col2;
            }
        }
        ++row1; ++row2;
    }
    return true;
}

//@ </answer>

// ¡No modificar nada debajo de esta línea!
// ----------------------------------------------------------------

list<int> leer_fila() {
  list<int> result;
  int num;
  cin >> num;
  while (num != 0) {
    result.push_back(num);
    cin >> num;
  }
  return result;
}

list<list<int>> leer_matriz() {
  list<list<int>> result;
  list<int> fila_actual = leer_fila();
  while (!fila_actual.empty()) {
    result.push_back(fila_actual);
    fila_actual = leer_fila();
  }
  
  return result;
}

bool resuelveCaso() {
  list<list<int>> m = leer_matriz();
  if (m.empty()) return false;
  
  if (es_toeplitz(m)) {
    cout << "SI" << endl;
  } else {
    cout << "NO" << endl;
  }
  
  return true;
}

int main() {
#ifndef DOMJUDGE
  std::ifstream in("casos.txt");
  auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif
  
  while (resuelveCaso()) { }
  
#ifndef DOMJUDGE
  std::cin.rdbuf(cinbuf);
#endif
  
  return 0;
}
