/*
 * ---------------------------------------------------
 *                ESTRUCTURAS DE DATOS
 * ---------------------------------------------------
 *              Facultad de Informática
 *         Universidad Complutense de Madrid
 * ---------------------------------------------------
 */
 
 /*
  Mario Calvarro Marines
*/

#include <iostream>
#include <cassert>
#include <fstream>
#include <vector>

#include "Multiconjunto.h"

// Función que trata un caso de prueba.
// Devuelve false si se ha leído el 0 que marca el fin de la entrada,
// o true en caso contrario.
bool tratar_caso() {
  size_t numElementos;
  std::cin >> numElementos;

  if (numElementos == 0) {
      return false;
  }

  size_t aux;
  Multiconjunto secSecreta;
  std::vector<size_t> secSecretaDes (numElementos);
  for(size_t i = 0; i < numElementos; ++i) {
      std::cin >> aux;
      secSecreta.anyadir(aux);
      secSecretaDes[i] = aux;
  }

  std::vector<size_t> secIntento (numElementos);
  std::vector<char> respuesta (numElementos);

  for (size_t i = 0; i < numElementos; ++i) {
      std::cin >> aux;
      if (aux == secSecretaDes[i]) {
          respuesta[i] = '#';
          secSecreta.eliminar(aux);
      }
      secIntento[i] = aux;
  }

  for (size_t i = 0; i < numElementos; ++i) {
      if (secSecreta.pertenece(secIntento[i]) && respuesta[i] != '#') {
          respuesta[i] = 'O';
          secSecreta.eliminar(secIntento[i]);
      }
      else if (respuesta[i] != '#'){
          respuesta[i] = '.';
      }
  }

  for (size_t i = 0; i < numElementos; ++i) {
      std::cout << respuesta[i];
  }
  std::cout << '\n';
  return true;
}

int main() {
#ifndef DOMJUDGE
  std::ifstream in("../casos.txt");
  auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif
  
  while (tratar_caso()) {  }

#ifndef DOMJUDGE
  std::cin.rdbuf(cinbuf);
#endif
  return 0;
}
