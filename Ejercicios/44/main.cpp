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

 Se almacena el nº de alumnos que se han apuntado a cada deporte 
 y el deporte que practica cada alumno. En caso de que un alumno 
 aparezca más de una vez en el mismo deporte se ignora, pero si 
 aparece en más de un deporte simultaneamente no se tiene en cuenta 
 ese alumno, utilizando el valor centinela "NINGUNO". Estas 
 condiciones se verifican tras leer el nombre de cada alumno. 

 Respecto al coste en el caso peor será O(n * m + nlog(n)), donde
 n es el nº de deportes y m es el nº máximo de alumnos en un 
 deporte.
 
 @ </answer> */

#include <iostream>
#include <fstream>
#include <unordered_map>
#include <set>

using namespace std;

// Implementa a continuación la función que resuelve un caso de
// prueba. Puedes utilizar otras funciones auxiliares, pon su
// implementación debajo de la etiqueta <answer>.
//@ <answer>

bool esDeporte(const string &aux) {
  for (const char c : aux) {
    if (c < 'A' || c > 'Z') {
      return false;
    }
  }
  return true;
}

bool resuelveCaso() {
  // completar
  std::unordered_map<string, int> deportes;
  std::unordered_map<string, string> alumnos;
  string aux, auxDep;
  std::cin >> aux; 
  if (!std::cin) {
      return false;
  }

  while (aux != "_FIN_") {
    deportes[aux] = 0;
    auxDep = aux;
    std::cin >> aux; 
    while (!esDeporte(aux) && aux != "_FIN_") {
      if (alumnos.count(aux)) {
        if (alumnos[aux] != auxDep && alumnos[aux] != "NINGUNO") {
          --deportes[alumnos[aux]];
          alumnos[aux] = "NINGUNO";
        }
      }
      else {
        alumnos[aux] = auxDep;
        ++deportes[auxDep];
      }
      std::cin >> aux;
    }
  }

  auto comp = [&deportes](const string &x, const string &y){ 
    int depX = deportes[x], depY = deportes[y];
    return depX > depY || (depX == depY && x < y);
  };

  set<string, decltype(comp)> depOrd(comp);
  for (const auto &[key, val] : deportes) {
    depOrd.insert(key);
  }

  for (const std::string &dep : depOrd) {
    std::cout << dep << ' ' << deportes[dep] << '\n';
  }

  std::cout << "---\n";
  
  return true;
}


//@ </answer>
// ¡No modificar nada debajo de esta línea!
// ----------------------------------------------------------------

int main() {
#ifndef DOMJUDGE
  std::ifstream in("casos.txt");
  auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif
  
  while (resuelveCaso());

#ifndef DOMJUDGE
  std::cin.rdbuf(cinbuf);
#endif
  return 0;
}
