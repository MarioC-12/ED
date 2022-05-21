/*@ <answer>
 *
 * Nombre y Apellidos:
 * Mario Calvarro Marines
 *
 *@ </answer> */

#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <exception>
#include <list>
#include <algorithm>

// ================================================================
// Escribe el código completo de tu solución aquí debajo
// ================================================================
//@ <answer>

class CarnetPuntos {
public: 
    void nuevo(const std::string &dni);
    void quitar(const std::string &dni, int puntos);
    void recuperar(const std::string &dni, int puntos);
    int consultar(const std::string &dni) const;
    int cuantos_con_puntos(int puntos) const;
    std::list<std::string> lista_por_puntos(int puntos) const;

private:
    std::unordered_map<std::string, int> conductoresMap;
    //1º: Puntos, 2º: nº conductores
    std::unordered_map<int, int> numConductoresPuntos;
    //1º: Puntos, 2º: lista de conductores por antiguedad
    std::unordered_map<int, std::list<std::string>> puntosConductores;
};

void CarnetPuntos::nuevo(const std::string &dni) {
    if(conductoresMap.count(dni)) {
        throw std::domain_error("Conductor duplicado");
    }
    conductoresMap[dni] = 15;
    ++numConductoresPuntos[15];
    puntosConductores[15].push_front(dni);
}

void CarnetPuntos::quitar(const std::string &dni, int puntos) {
    if(puntos < 0 || !conductoresMap.count(dni)) {
        throw std::domain_error("Conductor inexistente");
    }
    int valorAntes = conductoresMap[dni];
    if (valorAntes > 0) {
        --numConductoresPuntos[valorAntes];
        auto it = std::find(puntosConductores[valorAntes].begin(), puntosConductores[valorAntes].end(), dni);
        puntosConductores[valorAntes].erase(it);
        int valorRestar = std::min(puntos, valorAntes);
        int valorDespues = valorAntes - valorRestar; 
        ++numConductoresPuntos[valorDespues];
        puntosConductores[valorDespues].push_front(dni);
        conductoresMap[dni] = valorDespues;
    }
}

void CarnetPuntos::recuperar(const std::string &dni, int puntos) {
    if(puntos < 0 || !conductoresMap.count(dni)) {
        throw std::domain_error("Conductor inexistente");
    }
    int valorAntes = conductoresMap[dni];
    if (valorAntes < 15) {
        auto it = std::find(puntosConductores[valorAntes].begin(), puntosConductores[valorAntes].end(), dni);
        puntosConductores[valorAntes].erase(it);
        int nuevosPuntos = std::min(15, puntos + conductoresMap[dni]);
        conductoresMap[dni] = nuevosPuntos;
        puntosConductores[nuevosPuntos].push_front(dni);
    }
}

int CarnetPuntos::consultar(const std::string &dni) const{
    if(!conductoresMap.count(dni)) {
        throw std::domain_error("Conductor inexistente");
    }
    return conductoresMap.at(dni);
}

int CarnetPuntos::cuantos_con_puntos(int puntos) const {
    if(puntos < 0 || puntos > 15) {
        throw std::domain_error("Puntos no validos");
    }
    if (numConductoresPuntos.count(puntos)) {
        return numConductoresPuntos.at(puntos);
    }
    return 0;
}

std::list<std::string> CarnetPuntos::lista_por_puntos(int puntos) const {
    return puntosConductores.at(puntos); 
}

bool resuelveCaso() {
    // leer los datos de la entrada
    CarnetPuntos caso;
    std::string comando;
    std::string dni;
    int puntos;

    std::cin >> comando;
    if (!std::cin)
        return false;
    
    while (comando != "FIN") {
        try {
            if (comando == "nuevo") {
                std::cin >> dni;
                caso.nuevo(dni);
            }
            else if (comando == "quitar") {
                std::cin >> dni;
                std::cin >> puntos;
                caso.quitar(dni, puntos);
            }
            else if (comando == "recuperar") {
                std::cin >> dni;
                std::cin >> puntos;
                caso.recuperar(dni, puntos);
            }
            else if (comando == "consultar") {
                std::cin >> dni;
                puntos = caso.consultar(dni);
                std::cout << "Puntos de " << dni << ": " << puntos << '\n';
            }
            else if (comando == "cuantos_con_puntos") {
                std::cin >> puntos;
                int numCond = caso.cuantos_con_puntos(puntos);
                std::cout << "Con " << puntos << " puntos hay " << numCond << '\n';
            }
            else if (comando == "lista_por_puntos") {
                std::cin >> puntos;
                std::list<std::string> sol = caso.lista_por_puntos(puntos);
                std::cout << "Tienen " << puntos << " puntos: ";
                for (const std::string &per : sol) {
                    std::cout << per << ' ';
                }
                std::cout << '\n';
            }
        }
        catch (const std::exception& ex) {
            std::cout << "ERROR: " << ex.what() << '\n';
        }
        std::cin >> comando;
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
