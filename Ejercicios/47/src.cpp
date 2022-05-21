/*@ <answer>
 *
 * Nombre y Apellidos:
 * Mario Calvarro Marines
 *
 *@ </answer> */

#include <iostream>
#include <fstream>
#include <vector>
#include <utility>
#include <unordered_map>
#include <map>
#include <string>
#include <exception>

using namespace std;

// ================================================================
// Escribe el código completo de tu solución aquí debajo
// ================================================================
//@ <answer>
class ConteoVotos {
public: 
    //O(1) amortizado
    void nuevo_estado(const string &nombre, int num_compromisarios);
    //O(log(n)), n: nº de partidos que en algun momento han ganado en algun estado
    void sumar_votos(const string &estado, const string &partido, int num_votos);
    //O(1) amortizado
    string ganador_en(const string &estado) const;
    //O(n), n: nº de partidos que en algun momento han ganado en algun estado
    vector<pair<string, int>> resultados() const;
private: 
    unordered_map<string, int> estadoCompromisario;
    unordered_map<string, unordered_map<string, int>> estadoPartidoVotos;
    unordered_map<string, pair<string, int>> ganadorEstado;
    map<string, int> partidoCompromisarios;
};

void ConteoVotos::nuevo_estado(const string &nombre, int num_compromisarios) {
    if (estadoCompromisario.count(nombre)) {
        throw domain_error("Estado ya existente");
    }
    estadoCompromisario[nombre] = num_compromisarios;
}

void ConteoVotos::sumar_votos(const string &estado, const string &partido, int num_votos) {
    if (!estadoCompromisario.count(estado)) {
        throw domain_error("Estado no encontrado");
    }
    estadoPartidoVotos[estado][partido] += num_votos;
    if (estadoPartidoVotos[estado][partido] > ganadorEstado[estado].second) {
        if (ganadorEstado.count(estado)) {
            partidoCompromisarios[ganadorEstado[estado].first] -= estadoCompromisario[estado];
        }
        ganadorEstado[estado] = {partido, estadoPartidoVotos[estado][partido]}; 
        partidoCompromisarios[ganadorEstado[estado].first] += estadoCompromisario[estado];
    }
}

string ConteoVotos::ganador_en(const string &estado) const {
    if (!estadoCompromisario.count(estado)) {
        throw domain_error("Estado no encontrado");
    }
    return ganadorEstado.at(estado).first;
}

vector<pair<string, int>> ConteoVotos::resultados() const {
    vector<pair<string, int>> sol;
    for (auto const &[key, value] : partidoCompromisarios) {
        if (value > 0) {
            sol.push_back({key, value});
        }
    }
    return sol;
}

bool resuelveCaso() {
    // leer los datos de la entrada
    string comando;
    cin >> comando;

    string estado, partido; int num;

    if (!cin) return false;

    ConteoVotos cont;
    while(comando != "FIN") {
        try {
            if (comando == "nuevo_estado") {
                cin >> estado >> num;
                cont.nuevo_estado(estado, num);
            }
            else if (comando == "sumar_votos") {
                cin >> estado >> partido >> num;
                cont.sumar_votos(estado, partido, num);
            }
            else if (comando == "ganador_en") {
                cin >> estado;
                string sol = cont.ganador_en(estado);
                cout << "Ganador en " << estado << ": " << sol << '\n';
            }
            else if (comando == "resultados") {
                vector<pair<string, int>> sol = cont.resultados();
                for (const pair<string, int> &res : sol) {
                    cout << res.first << ' ' << res.second << '\n';
                }
            }
        } catch(const domain_error &e) {
            cout << e.what() << '\n';
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
