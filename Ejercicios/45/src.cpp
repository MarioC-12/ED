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

/*@ <answer>
  
 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.
 
 @ </answer> */


// ================================================================
// Escribe el código completo de tu solución aquí debajo
// ================================================================
//@ <answer>

class CarnetPuntos {
public: 
    void nuevo(std::string dni);
    void quitar(std::string dni, int puntos);
    int consultar(std::string dni);
    int cuantos_con_puntos(int puntos);

private:
    std::unordered_map<std::string, int> conductoresMap;
    //1º: Puntos, 2º: nº conductores
    std::unordered_map<int, int> numConductoresPuntos;
};

void CarnetPuntos::nuevo(std::string dni) {
    if(conductoresMap.count(dni)) {
        throw std::domain_error("Conductor duplicado");
    }
    conductoresMap[dni] = 15;
    ++numConductoresPuntos[15];
}

void CarnetPuntos::quitar(std::string dni, int puntos) {
    if(puntos < 0 || !conductoresMap.count(dni)) {
        throw std::domain_error("Conductor inexistente");
    }
    int valorAntes = conductoresMap[dni];
    if (valorAntes > 0) {
        --numConductoresPuntos[valorAntes];
        int valorRestar = std::min(puntos, valorAntes);
        int valorDespues = valorAntes - valorRestar; 
        ++numConductoresPuntos[valorDespues];
        conductoresMap[dni] = valorDespues;
    }
}

int CarnetPuntos::consultar(std::string dni) {
    if(!conductoresMap.count(dni)) {
        throw std::domain_error("Conductor inexistente");
    }
    return conductoresMap[dni];
}

int CarnetPuntos::cuantos_con_puntos(int puntos) {
    if(puntos < 0 || puntos > 15) {
        throw std::domain_error("Puntos no validos");
    }
    return numConductoresPuntos[puntos];
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
