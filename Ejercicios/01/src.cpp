
/*
 * Mario Calvarro Marines
 */

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>

/*@ <answer>
  
  Creamos la clase Hora que tendrá tres atributos (horas, minutos, segundo) y sobrecargamos los operadores 
  <, <=, >>, <<. Estos dos últimos no serán miembros de la clase para permitir la sintaxis habitual (cin >> hora)
  y no tener que invertirla (hora >> cin).

  El método resolver realiza una búsqueda binaria entre las posibles horas y nos quedamos entre las que son >= con la menor.
  
  No es necesario almacenar las consultas en un vector, se puede hacer una a una.
 
 @ </answer> */


class Hora {
public: 
    bool operator<(const Hora& h) const{
        return this->horas < h.horas || (this->horas == h.horas && (this->minutos < h.minutos || (this->minutos == h.minutos && this->segundos < h.segundos)));
    }
    bool operator<=(const Hora& h) const{
        return *this < h || (this->horas == h.horas && this->minutos == h.minutos && this->segundos == h.segundos);
    }
    friend std::istream& operator>>(std::istream& input, Hora& h);
    friend std::ostream& operator<<(std::ostream& output, const Hora& h);
        
private:
    size_t horas;
    size_t minutos;
    size_t segundos;
};

std::istream& operator>>(std::istream& input, Hora& h) {
    char aux;
    input >> h.horas; input.get(aux);
    input >> h.minutos; input.get(aux);
    input >> h.segundos; input.get(aux);
    return input;
}

std::ostream& operator<<(std::ostream& output, const Hora& h) {
    output << std::setfill('0') << std::setw(2) << h.horas << ':' << std::setw(2) << h.minutos << ':' << std::setw(2) << h.segundos;
    return output;
}

bool resolver(const std::vector<Hora>& horarioTrenes, const Hora& consulta, Hora& sol) {
    bool res = false;
    size_t ini = 0, fin = horarioTrenes.size();
    while (ini < fin) {
        size_t m = (ini + fin) / 2;
        if (consulta <= horarioTrenes[m]) {
            sol = horarioTrenes[m];
            res = true; fin = m;
        }
        else {
            ini = m + 1;
        }
    }

    return res;
}

bool resuelveCaso() {
    
   // leer los datos de la entrada
   size_t nTrenes, nHoras;
   std::cin >> nTrenes >> nHoras;
   
   if (nTrenes == 0 || nHoras == 0)
      return false;
   
   std::vector<Hora> horarioTrenes (nTrenes);
   for (size_t i = 0; i < nTrenes; ++i) {
       std::cin >> horarioTrenes[i];
   }
   Hora consulta, sol;
   bool posible;

   // resolver el caso posiblemente llamando a otras funciones
   for (size_t i = 0; i < nHoras; ++i) {
       std::cin >> consulta;
       posible = resolver(horarioTrenes, consulta, sol);
       if (!posible) {std::cout << "NO\n";}
       else {std::cout << sol << '\n';}
   }
   
   std::cout << "---\n";

   return true;
}

//@ </answer>

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
