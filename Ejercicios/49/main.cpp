/*
 * ---------------------------------------------------
 *                ESTRUCTURAS DE DATOS
 * ---------------------------------------------------
 *              Facultad de Informática
 *         Universidad Complutense de Madrid
 * ---------------------------------------------------
 */

/*@ <answer>
 
 Introduce el nombre y apellidos de los/as componentes del grupo:
 
 Estudiante 1: Mario Calvarro Marines
 Estudiante 2: Daniel Ramos Rodriguez
 
 Dad una explicación de la solución y justificad su coste.

 El método definitorio ha sido torre_mas_cercana en el sentido 
 de que la implementación se ha desarrollado con la intención de 
 mantener el coste asociado al nº de torres existentes y no al 
 tamaño del mapa. Con este fin hemos optado por utilizar maps
 ordenados que representen cada una de las filas y columnas,
 permitiendo realizar búsquedas en tiempo logarítmico respecto al
 número de torres.
 También se ha añadido un hash map doble ("torres") que permita
 minimizar el coste de encontrar una torre a partir de unas ciertas
 coordenadas, volviéndolo constante amortizado.

 El coste en tiempo se incluye encima de cada método.
 
 @ </answer> */


// Añade los include que necesites
#include <iostream>
#include <cassert>
#include <fstream>
#include <string>
#include <stdexcept>
#include <unordered_map>
#include <map>
#include <climits>

using namespace std;

// Tipo de datos para representar direcciones
// Para hacer referencia a los elementos de este tipo enumerado se utiliza:
//   Direccion::Norte, Direccion::Sur, etc.
enum class Direccion { Norte, Sur, Este, Oeste };

// Operador para leer una dirección desde un flujo de entrada.
// Ejemplo de uso:
//
// Direccion dir;
// cin >> dir;
//
istream & operator>>(istream &is, Direccion &dir) {
  string palabra; is >> palabra;
  if (palabra == "Norte") dir = Direccion::Norte;
  else if (palabra == "Sur") dir = Direccion::Sur;
  else if (palabra == "Este") dir = Direccion::Este;
  else if (palabra == "Oeste") dir = Direccion::Oeste;
  else throw std::domain_error("Lectura de direccion incorrecta");
  return is;
}

// Implementa a continuación la clase Desierto.
//@ <answer>

class Desierto {
public:
  
  Desierto() { }
  
  // O(log n) ya que se realizan operaciones de coste constante pero también
  // se insertan elementos en un map ordenado.
  void anyadir_torre(const string &nombre, int x, int y) {
    if(coors.count(nombre)) {
        throw domain_error("Torre ya existente");
    }
    if(torres[x].count(y)) {
        throw domain_error("Posicion ocupada");
    }
    torres[x][y] = nombre;
    filas[y][x] = nombre;
    columnas[x][y] = nombre;
    coors[nombre] = {x, y};
  }
  
  // O(log n) ya que se realizan operaciones de coste constante pero también
  // se eliminan elementos en un map ordenado.
  void eliminar_torre(const string &nombre) {
    if(!coors.count(nombre)) {
        throw domain_error("Torre no existente");
    }
    auto [x, y] = coors[nombre];
    torres[x].erase(y);
    filas[y].erase(x);
    columnas[x].erase(y);
    coors.erase(nombre);
  }
  
  // O(1) amortizado
  pair<bool, string> torre_en_posicion(int x, int y) const {
    if(!torres.count(x) || !torres.at(x).count(y)) {
        return {false, ""};
    }
    else {
        return {true, torres.at(x).at(y)};
    }
  }

  // O(1) amortizado
  pair<int, int> posicion(const string &nombre) const {
    if(!coors.count(nombre)) {
        throw domain_error("Torre no existente");
    }
    return coors.at(nombre);
  }
  
  // O(log n), ya que se realizan operaciones de coste constante o constante amortizado pero
  // también se busca mediante una clave en un map.
  string torre_mas_cercana(const string &nombre, const Direccion &dir) const {
    if(!coors.count(nombre)) {
        throw domain_error("Torre no existente");
    }
    bool encontrado = false;
    pair<int, int> pos = coors.at(nombre);
    map<int, string>::const_iterator it;
    if(dir == Direccion::Este || dir == Direccion::Oeste) {
      it = filas.at(pos.second).find(pos.first);
    }
    else {
      it = columnas.at(pos.first).find(pos.second);
    }
    switch(dir) {
        case Direccion::Este: {
          ++it;
          if(it != filas.at(pos.second).end()) {
            encontrado = true;
          }
          break;
        }
        case Direccion::Oeste: {
          if(it != filas.at(pos.second).begin()) {
            --it;
            encontrado = true;
          }
          break;
        }
        case Direccion::Norte: {
          ++it;
          if(it != columnas.at(pos.first).end()) {
            encontrado = true;
          }
          break;
        }
        case Direccion::Sur: {
          if(it != columnas.at(pos.first).begin()) {
            --it;
            encontrado = true;
          }
          break;
        }
    }
   
    if(!encontrado) {
        throw domain_error("No hay torres en esa direccion");
    }
    return it->second;
  }

private:
  // Añade aquí los atributos que conforman la representación
  // interna del TAD
  //
  // También puedes añadir métodos auxiliares privados
  
  unordered_map<int, map<int, string>> filas;
  unordered_map<int, map<int, string>> columnas;
  unordered_map<int, unordered_map<int, string>>  torres;
  unordered_map<string, pair<int, int>> coors;

};



//@ </answer>
// ¡No modificar nada debajo de esta línea!
// ----------------------------------------------------------------

bool resuelveCaso() {
  string inst, nombre; int x,y; Direccion dir;
  cin >> inst;
  if (!cin) return false;
  Desierto desierto;
  while (inst != "FIN") {
    try {
      if (inst == "anyadir_torre") {
        cin >> nombre >> x >> y;
        desierto.anyadir_torre(nombre, x, y);
      } else if (inst == "eliminar_torre") {
        cin >> nombre;
        desierto.eliminar_torre(nombre);
      } else if (inst == "posicion") {
        cin >> nombre;
        auto [x,y] = desierto.posicion(nombre);
        cout << x << ' ' << y << '\n';
      } else if (inst == "torre_en_posicion") {
        cin >> x >> y;
        auto [hay, nombre] = desierto.torre_en_posicion(x, y);
        if (hay) cout << "SI " << nombre << '\n';
        else cout << "NO\n";
      } else {
        cin >> nombre >> dir;
        nombre = desierto.torre_mas_cercana(nombre, dir);
        cout << nombre << '\n';
      }
    } catch (domain_error & e) {
      cout << e.what() << '\n';
    }
    cin >> inst;
  }
  cout << "---\n";
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
