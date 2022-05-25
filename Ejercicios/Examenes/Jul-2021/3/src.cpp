/*@ <answer>
 *
 * Nombre y Apellidos:
 * Mario Calvarro Marines
 *
 *@ </answer> */

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <set>

// ================================================================
// Escribe el código completo de tu solución aquí debajo
// ================================================================
//@ <answer>
using namespace std;
class Partida {
public: 
    void anyadir_jugador(const string &jugador);
    void colocar_caballero(const string &jugador, const string &region);
    size_t puntuacion(const string &jugador) const;
    vector<string> regiones_en_disputa() const;
    void expulsar_caballeros(const string &region);
private: 
    unordered_map<string, int> jugadorControladas;
    unordered_map<string, unordered_map<string, int>> regionJugadorCab;
    unordered_map<string, pair<string, int>> regionDominador;
    set<string> disputadas; 
};

//O(1)
void Partida::anyadir_jugador(const string &jugador) {
    if (jugadorControladas.count(jugador)) {
        throw domain_error("Jugador existente");
    }
    jugadorControladas[jugador] = 0;
}

//O(1)
void Partida::colocar_caballero(const string &jugador, const string &region) {
    if (!jugadorControladas.count(jugador)) {
        throw domain_error("Jugador no existente");
    }
    ++regionJugadorCab[region][jugador];
    if(regionDominador[region].second == regionJugadorCab[region][jugador]) {
        if (regionDominador[region].first != "") {
            --jugadorControladas[regionDominador[region].first];
            regionDominador[region].first = "";
        }
        disputadas.insert(region);
    }
    else if (regionDominador[region].second < regionJugadorCab[region][jugador]) {
        --jugadorControladas[regionDominador[region].first];
        regionDominador[region] = {jugador, regionJugadorCab[region][jugador]};
        ++jugadorControladas[jugador];
    }
}

//O(1)
size_t Partida::puntuacion(const string &jugador) const {
    if (!jugadorControladas.count(jugador)) {
        throw domain_error("Jugador no existente");
    }
    return jugadorControladas.at(jugador);
}

//O(n), n: nº disputadas
vector<string> Partida::regiones_en_disputa() const{
    vector<string> sol;
    for (const string &dis : disputadas) {
        sol.push_back(dis);
    }
    return sol;
}

//O(1)
void Partida::expulsar_caballeros(const string &region) {
    if (!regionJugadorCab.count(region)) {
        throw domain_error("Region vacia");
    }
    regionJugadorCab.erase(region);
    if (regionDominador[region].first != "") {
        --jugadorControladas[regionDominador[region].first];
        regionDominador[region] = {"", 0};
    }
    else {
        disputadas.erase(region);
    }
}

bool resuelveCaso() {
    // leer los datos de la entrada
    Partida p;
    string comando, jugador, region;
    cin >> comando;

    if (!std::cin)  // fin de la entrada
        return false;

    while(comando != "FIN") {
        try {
            if (comando == "anyadir_jugador") {
                cin >> jugador;
                p.anyadir_jugador(jugador); 
            }
            else if (comando == "colocar_caballero") {
                cin >> jugador >> region;
                p.colocar_caballero(jugador, region);
            }
            else if (comando == "puntuacion") {
                cin >> jugador;
                size_t s = p.puntuacion(jugador);
                cout << "Puntuacion de " << jugador << ": " << s << '\n';
            }
            else if (comando == "regiones_en_disputa") {
                vector<string> s = p.regiones_en_disputa();
                cout << "Regiones en disputa:\n";
                for (const string &text : s) {
                    cout << text << '\n';
                }
            }
            else if (comando == "expulsar_caballeros") {
                cin >> region;
                p.expulsar_caballeros(region);
            }
        }
        catch (const domain_error &e) {
            cout << "ERROR: " << e.what() << '\n';
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
   std::ifstream in("casos.txt");
   auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif
   
   while (resuelveCaso());
   
   // para dejar todo como estaba al principio
#ifndef DOMJUDGE
   std::cin.rdbuf(cinbuf);
#endif
   return 0;
}
