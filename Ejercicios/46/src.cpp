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
#include <set>
#include <vector>
#include <stdexcept>

// ================================================================
// Escribe el código completo de tu solución aquí debajo
// ================================================================
//@ <answer>
using namespace std;

class AutoEscuela {
public: 
    //O(log(n)), n: max entre nº de alumnos de p y del antiguo profesor
    void alta(string a, string p);
    //O(1) amortizado
    bool es_alumno(string a, string p);
    //O(1) amortizado
    int puntuacion(string a);
    //O(1) amortizado
    void actualizar(string a, int N);
    //O(n), n: nº alumnos de p
    vector<string> examen(string p, int N);
    //O(log(n)), n: nº alumnos de profesor de a
    void aprobar(string a);
private: 
    //1: Alumno, 2: Puntuacion
    unordered_map<string, int> alumnoPunt;
    //1: Profesor, 2: Alumnos
    unordered_map<string, set<string>> profesorAlum;
    //1: Alumno, 2: Profesor
    unordered_map<string, string> alumnoProf;
};

void AutoEscuela::alta(string a, string p) {
    if(alumnoProf.count(a)) {
        string profAnt = alumnoProf[a];
        alumnoProf[a] = p;
        profesorAlum[profAnt].erase(a);
    }
    else {
        alumnoPunt[a] = 0;
        alumnoProf[a] = p;
    }
    profesorAlum[p].insert(a);
}

bool AutoEscuela::es_alumno(string a, string p) {
    return profesorAlum[p].count(a);
}

int AutoEscuela::puntuacion(string a) {
    if (!alumnoPunt.count(a)) {
        throw domain_error("El alumno " + a + " no esta matriculado");
    }
    return alumnoPunt[a];
}

void AutoEscuela::actualizar(string a, int N) {
    if (!alumnoPunt.count(a)) {
        throw domain_error("El alumno " + a + " no esta matriculado");
    }
    alumnoPunt[a] += N;
}

vector<string> AutoEscuela::examen(string p, int N) {
    vector<string> sol;
    for (const string &alumno : profesorAlum[p]) {
        if (alumnoPunt[alumno] >= N) {
            sol.push_back(alumno);
        }
    }
    return sol;
}

void AutoEscuela::aprobar(string a) {
    if (!alumnoProf.count(a)) {
        throw domain_error("El alumno " + a + " no esta matriculado");
    }
    alumnoPunt.erase(a);
    profesorAlum[alumnoProf[a]].erase(a);
    alumnoProf.erase(a);
}

bool resuelveCaso() {
    // leer los datos de la entrada
    AutoEscuela autoEsc;
    string comando;
    string alumno, profesor; int num;
    cin >> comando;

    if(!cin) return false;

    while(comando != "FIN") {
        try {
            if (comando == "alta") {
                cin >> alumno >> profesor;
                autoEsc.alta(alumno, profesor);
            }
            else if (comando == "es_alumno") {
                cin >> alumno >> profesor;
                bool res = autoEsc.es_alumno(alumno, profesor);
                if (res) {
                    cout << alumno << " es alumno de " << profesor << '\n';
                }
                else {
                    cout << alumno << " no es alumno de " << profesor << '\n';
                }
            }
            else if (comando == "puntuacion") {
                cin >> alumno;
                int res = autoEsc.puntuacion(alumno);
                cout << "Puntuacion de " << alumno << ": " << res << '\n';
            }
            else if (comando == "actualizar") {
                cin >> alumno >> num;
                autoEsc.actualizar(alumno, num);
            }
            else if (comando == "examen") {
                cin >> profesor >> num;
                vector<string> res = autoEsc.examen(profesor, num);
                cout << "Alumnos de " << profesor << " a examen:\n";
                for (const string &al : res) {
                    cout << al << '\n';
                }
            }
            else if (comando == "aprobar") {
                cin >> alumno;
                autoEsc.aprobar(alumno);
            }
        }
        catch(const domain_error & e) {
            cout << "ERROR\n";
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
