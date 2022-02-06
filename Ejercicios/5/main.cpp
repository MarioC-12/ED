/*
 * ---------------------------------------------------
 *                ESTRUCTURAS DE DATOS
 * ---------------------------------------------------
 */

/*
 * MUY IMPORTANTE: Solo se corregirán los comentarios y el código
 * contenidos entre las etiquetas <answer> y </answer>.
 * Toda modificación fuera de esas etiquetas no será corregida.
 */

/*@ <answer>
  Mario Calvarro Marines
 *@ </answer> */

#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <fstream>
using namespace std;

/*@ <answer> */

class Polinomio {
private:
    struct monomio {
        int coef;
        int exp;
        monomio(int c, int e): coef(c), exp(e){}
        bool operator<(const monomio& m) const {
            return exp < m.exp;
        }
        bool operator==(const monomio& m) const {
            return exp == m.exp;
        }
    };
    std::vector<monomio> polinomio;
    

public:
    //Coste logarítmico
    void sumaMono(int coef, int exp) {
        monomio m {coef, exp};
        auto pos = std::lower_bound(polinomio.begin(), polinomio.end(), m);
        if (pos < polinomio.end() && *pos == m) {
            pos->coef += coef;
            //Eliminamos el monomio si el coeficiente es 0
            if (pos->coef == 0) polinomio.erase(pos);
        }
        else {
            polinomio.insert(pos, m);
        }
    }
    
    //Coste lineal
    int64_t evalua(int valor) const {
        int64_t pot {1}, resultado{0};
        size_t exp {0};
        for (size_t i = 0; i < polinomio.size(); ++i) {
            while(exp < polinomio[i].exp) {
                pot *= valor;
                ++exp;
            }
            resultado += pot * polinomio[i].coef;
        }      
        return resultado;
    }
};


bool resuelveCaso() {
  int coef, exp;
  cin >> coef >> exp;
  
  if (!cin)
      return false;
  
  // leemos el polinomio, monomio a monomio
  Polinomio poli;
  while (coef != 0 || exp != 0) {
      poli.sumaMono(coef, exp);
      cin >> coef >> exp;
  }
  
  int N;
  cin >> N;
  while (N--) {
      // evaluamos para un nuevo valor
      int valor;
      cin >> valor;
      cout << poli.evalua(valor);
      if (N) cout << ' ';
  }
  cout << '\n';
  return true;
}

/*@ </answer> */

int main() {
  
#ifndef DOMJUDGE
  std::ifstream in("../casos.txt");
  auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif
  
  while (resuelveCaso()) {}
  
#ifndef DOMJUDGE
  std::cin.rdbuf(cinbuf);
#endif
  
  return 0;
}


