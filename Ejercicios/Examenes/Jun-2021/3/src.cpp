/*@ <answer>
 *
 * Nombre y Apellidos:
 * Mario Calvarro Marines
 *
 *@ </answer> */

#include <iostream>
#include <fstream>
#include <unordered_map>
#include <vector>
#include <set>
#include <unordered_set>
#include <list>
using namespace std;

// ================================================================
// Escribe el código completo de tu solución aquí debajo
// ================================================================
//@ <answer>
class Consultorio {
public: 
    void altaMedico(const string &medico);
    void pedirConsulta(const string &paciente, const string &medico);
    string siguientePaciente(const string &medico);
    void atenderConsulta(const string &medico);
    vector<string> abandonarConsulta(const string &paciente);
private:
    unordered_set<string> medicos;
    //Más tiempo esperando al final, recien llegados al principio
    unordered_map<string, list<string>> medicoCola;
    unordered_map<string, set<string>> pacienteMedicos;
    unordered_map<string, unordered_map<string, list<string>::iterator>> pacienteIteradores;
};

void Consultorio::altaMedico(const string &medico) {
    if (medicos.count(medico)) {
        throw domain_error("Medico existente");
    }
    medicos.insert(medico);
}

void Consultorio::pedirConsulta(const string &paciente, const string &medico) {
    if (!medicos.count(medico)) {
        throw domain_error("Medico inexistente");
    }
    if (pacienteMedicos[paciente].count(medico)) {
        throw domain_error("Paciente ya esperando");
    }
    pacienteMedicos[paciente].insert(medico);
    medicoCola[medico].push_front(paciente);
    pacienteIteradores[paciente][medico] = medicoCola[medico].begin();
}

string Consultorio::siguientePaciente(const string &medico) {
    if(!medicos.count(medico)) {
        throw domain_error("Medico inexistente");
    }
    if(medicoCola.at(medico).empty()) {
        throw domain_error("Medico sin pacientes");
    }
    return medicoCola.at(medico).back();
}

void Consultorio::atenderConsulta(const string &medico) { 
    if(!medicos.count(medico)) {
        throw domain_error("Medico inexistente");
    }
    if(medicoCola.at(medico).empty()) {
        throw domain_error("Medico sin pacientes");
    }
    medicoCola.at(medico).pop_back();
}

vector<string> Consultorio::abandonarConsulta(const string &paciente) {
    vector<string> sol;
    for (const string &txt : pacienteMedicos.at(paciente)) {
        medicoCola.at(txt).erase(pacienteIteradores[paciente][txt]);
        sol.push_back(txt);
    }

    return sol;
}

bool resuelveCaso() {
    // leer los datos de la entrada
    Consultorio c;
    string comando, paciente, medico;
    cin >> comando;

    if (!std::cin)  // fin de la entrada
        return false;

    while (comando != "FIN") {
        try {
            if (comando == "altaMedico") {
                cin >> medico;
                c.altaMedico(medico);
            }
            else if (comando == "pedirConsulta") {
                cin >> paciente >> medico; 
                c.pedirConsulta(paciente, medico);
            }
            else if (comando == "siguientePaciente") {
                cin >> medico; 
                string pac = c.siguientePaciente(medico);
                cout << pac << '\n';
            }
            else if (comando == "atenderConsulta") {
                cin >> medico;
                c.atenderConsulta(medico);
            }
            else if (comando == "abandonarConsulta") {
                cin >> paciente;
                auto lista = c.abandonarConsulta(paciente);
                cout << "Medicos abandonados: ";
                for (const auto &doc : lista) {
                    cout << doc << ' ';
                }
                cout << '\n';
            }
        }
        catch(const domain_error &e) {
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
