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
#include <vector>
#include <list>
#include <algorithm>

using namespace std;

// ================================================================
// Escribe el código completo de tu solución aquí debajo
// ================================================================
//@ <answer>

class CarnetPuntos {
public: 
    CarnetPuntos(): puntosConductores(16) {};
    //O(1) amortizado
    void nuevo(const string &dni);
    //O(1) amortizado
    void quitar(const string &dni, int puntos);
    //O(1) amortizado
    void recuperar(const string &dni, int puntos);
    //O(1) amortizado
    int consultar(const string &dni) const;
    //O(1) 
    int cuantos_con_puntos(int puntos) const;
    //O(1)
    list<string> lista_por_puntos(int puntos) const;

private:
    unordered_map<string, int> conductoresMap;
    unordered_map<string, list<string>::iterator> conductorIt;
    //1º: Puntos, 2º: lista de conductores por antiguedad
    vector<list<string>> puntosConductores;
};

void CarnetPuntos::nuevo(const string &dni) {
    if(conductoresMap.count(dni)) {
        throw domain_error("Conductor duplicado");
    }
    conductoresMap[dni] = 15;
    puntosConductores[15].push_front(dni);
    auto it = puntosConductores[15].begin();
    conductorIt[dni] = it;
}

void CarnetPuntos::quitar(const string &dni, int puntos) {
    if(puntos < 0 || !conductoresMap.count(dni)) {
        throw domain_error("Conductor inexistente");
    }
    int valorAntes = conductoresMap[dni];
    if (valorAntes > 0) {
        puntosConductores[valorAntes].erase(conductorIt[dni]);
        int valorRestar = min(puntos, valorAntes);
        int valorDespues = valorAntes - valorRestar; 
        conductoresMap[dni] = valorDespues;
        puntosConductores[valorDespues].push_front(dni);
        conductorIt[dni] = puntosConductores[valorDespues].begin();
    }
}

void CarnetPuntos::recuperar(const string &dni, int puntos) {
    if(puntos < 0 || !conductoresMap.count(dni)) {
        throw domain_error("Conductor inexistente");
    }
    int valorAntes = conductoresMap[dni];
    if (valorAntes < 15) {
        puntosConductores[valorAntes].erase(conductorIt[dni]);
        int nuevosPuntos = min(15, puntos + conductoresMap[dni]);
        conductoresMap[dni] = nuevosPuntos;
        puntosConductores[nuevosPuntos].push_front(dni);
        conductorIt[dni] = puntosConductores[nuevosPuntos].begin();
    }
}

int CarnetPuntos::consultar(const string &dni) const{
    if(!conductoresMap.count(dni)) {
        throw domain_error("Conductor inexistente");
    }
    return conductoresMap.at(dni);
}

int CarnetPuntos::cuantos_con_puntos(int puntos) const {
    if(puntos < 0 || puntos > 15) {
        throw domain_error("Puntos no validos");
    }
    return puntosConductores[puntos].size();
}

list<string> CarnetPuntos::lista_por_puntos(int puntos) const {
    if(puntos < 0 || puntos > 15) {
        throw domain_error("Puntos no validos");
    }
    return puntosConductores.at(puntos); 
}

bool resuelveCaso() {
    // leer los datos de la entrada
    CarnetPuntos caso;
    string comando;
    string dni;
    int puntos;

    cin >> comando;
    if (!cin)
        return false;
    
    while (comando != "FIN") {
        try {
            if (comando == "nuevo") {
                cin >> dni;
                caso.nuevo(dni);
            }
            else if (comando == "quitar") {
                cin >> dni;
                cin >> puntos;
                caso.quitar(dni, puntos);
            }
            else if (comando == "recuperar") {
                cin >> dni;
                cin >> puntos;
                caso.recuperar(dni, puntos);
            }
            else if (comando == "consultar") {
                cin >> dni;
                puntos = caso.consultar(dni);
                cout << "Puntos de " << dni << ": " << puntos << '\n';
            }
            else if (comando == "cuantos_con_puntos") {
                cin >> puntos;
                int numCond = caso.cuantos_con_puntos(puntos);
                cout << "Con " << puntos << " puntos hay " << numCond << '\n';
            }
            else if (comando == "lista_por_puntos") {
                cin >> puntos;
                list<string> sol = caso.lista_por_puntos(puntos);
                cout << "Tienen " << puntos << " puntos: ";
                for (const string &per : sol) {
                    cout << per << ' ';
                }
                cout << '\n';
            }
        }
        catch (const domain_error &ex) {
            cout << "ERROR: " << ex.what() << '\n';
        }
        cin >> comando;
    }

    cout << "---\n";

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
