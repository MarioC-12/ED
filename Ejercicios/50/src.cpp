/*@ <answer>
 *
 * Nombre y Apellidos:
 * Mario Calvarro Marines
 *
 *@ </answer> */

#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <list>

// ================================================================
// Escribe el código completo de tu solución aquí debajo
// ================================================================
//@ <answer>
using namespace std;

class IPud {
public: 
    void addSong(const string &song, const string &artista, const size_t &dur);
    void addToPlayList(const string &song);
    string current();
    string play();
    size_t totalTime();
    vector<string> recent(size_t N);
    void deleteSong(const string &song);
private: 
    //Cancion -> (Autor, duracion)
    unordered_map<string, pair<string, size_t>> canciones;
    //Primero las más recientes, al final las más antiguas (que se reproducirán antes)
    list<string> listaReproduccion;
    //Primero las más nuevas
    list<string> recentSongs;
    //Cancion -> (iterador ListaReproduccion, iterador cancionesRecientes) 
    unordered_map<string, list<string>::iterator> songItPlayList;
    unordered_map<string, list<string>::iterator> songItRecent;
    size_t _totalTime;
};

void IPud::addSong(const string &song, const string &artista, const size_t &dur) {
    if (canciones.count(song)) {
        throw domain_error("addSong");
    }
    canciones[song] = {artista, dur};
}

void IPud::addToPlayList(const string &song) {
    if(canciones.count(song)) {
        throw domain_error("addToPlayList");
    }
    if(!songItPlayList.count(song)) { 
        listaReproduccion.push_front(song);
        songItPlayList[song] = listaReproduccion.begin();
        _totalTime += canciones[song].second;
    }
}

string IPud::current() {
    if(listaReproduccion.empty()) {
        throw domain_error("current");
    }
    return listaReproduccion.back();
}

string IPud::play() {
    if(!listaReproduccion.empty()) {
        string song = current();
        listaReproduccion.pop_back();
        songItPlayList.erase(song);
        _totalTime -= canciones[song].second;

        if (songItRecent.count(song)) {
            recentSongs.erase(songItRecent[song]);
        }
        recentSongs.push_front(song);
        songItRecent[song] = recentSongs.begin();

        return song;
    }
    else {
        return "No hay canciones en la lista";
    }
}

size_t IPud::totalTime() {
    return _totalTime;
}

vector<string> IPud::recent(size_t N) {
    vector<string> sol;
    size_t i = 0;
    auto it = recentSongs.begin();
    while (i < N && i < recentSongs.size()) {
        sol.push_back(*it);
        ++i; ++it;
    }
    return sol;
}

void IPud::deleteSong(const string &song) {
    if (canciones.count(song)) {
        if (songItPlayList.count(song)) {
            listaReproduccion.erase(songItPlayList[song]);
            _totalTime -= canciones[song].second;
            songItPlayList.erase(song);
        }
        if (songItRecent.count(song)) {
            recentSongs.erase(songItRecent[song]);
            songItRecent.erase(song);
        }
        canciones.erase(song);
    }
}

bool resuelveCaso() {
    // leer los datos de la entrada
    string comando, song, artista;
    size_t duracion;
    IPud dis;

    cin >> comando;
    if (!std::cin)  // fin de la entrada
        return false;

    // resolver el caso posiblemente llamando a otras funciones
    while (comando != "FIN") {
        try {
            if (comando == "addSong") {
                cin >> song >> artista >> duracion;
                dis.addSong(song, artista, duracion);
            }
            else if(comando == "addToPlayList") {
                cin >> song;
                dis.addToPlayList(song);
            }
            else if(comando == "current") {
                dis.current();
            }
            else if(comando == "play") {
                string sol = dis.play();
                if (sol != "No hay canciones en la lista") {
                    cout << "Sonando " << sol << '\n';
                }
                else {
                    cout << sol << '\n';
                }
            }
            else if(comando == "totalTime") {
                int sol = dis.totalTime();
                cout << "Tiempo total " << sol << '\n';
            }
            else if(comando == "recent") {
                int aux;
                cin >> aux;
                vector<string> sol = dis.recent(aux);
                if (sol.empty()) {
                    cout << "No hay canciones recientes\n";
                }
                else {
                    cout << "Las " << aux << " mas recientes\n";
                    for (const string &txt : sol) {
                        cout << '\t' << txt << '\n';
                    }
                }
            }
        }
        catch (const domain_error &e) {
            cout << "ERROR: " << e.what() << '\n';
        }
        cin >> comando;
    }

    // escribir la solución

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
