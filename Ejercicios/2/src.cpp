
/*
 * Mario Calvarro Marines
 */
 

#include <iostream>
#include <fstream>
#include <cmath>

/*@ <answer>
   Definimos la clase Complejo con sus operadores y  
   ejecutamos el algoritmo para ver si el modulo de algún miembro de la sucesión es 
   superior estrictamente de 2.
 @ </answer> */


// ================================================================
// Escribe el código completo de tu solución aquí debajo
// ================================================================
//@ <answer>
class Complejo {
public: 
   Complejo (double real, double imaginario): real(real), imaginario(imaginario){};
   Complejo operator+(const Complejo& z) const{
      return {this->real + z.real, this->imaginario + z.imaginario};
   }
   Complejo operator*(const Complejo& z) const{
      return {this->real * z.real - this->imaginario * z.imaginario, this->real * z.imaginario + this->imaginario * z.real};
   }
   double mod() const{
      return sqrt((this->real * this->real) + (this->imaginario * this->imaginario));
   }
private:
   double real;
   double imaginario;
};

bool resolver(const Complejo& z, const size_t iteraciones) {
   bool res = true; size_t i = 0;
   Complejo Mandelbrot(0, 0);

   while (res && i < iteraciones) {
      if (Mandelbrot.mod() > 2) {
         res = false;
      }
      Mandelbrot = (Mandelbrot * Mandelbrot) + z; ++i; 
   }

   return res;
}

void resuelveCaso() { 
   // leer los datos de la entrada
   double real, imaginario;
   size_t iteraciones;
   std::cin >> real >> imaginario >> iteraciones;

   Complejo z(real, imaginario); 

   // resolver el caso posiblemente llamando a otras funciones
   bool sol = resolver(z, iteraciones);
 
   // escribir la solución
   std::cout << (sol? "SI" : "NO") << '\n';
}

//@ </answer>

int main() {
   // ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
   std::ifstream in("../casos.txt");
   auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif
   
   int numCasos;
   std::cin >> numCasos;
   for (int i = 0; i < numCasos; ++i)
      resuelveCaso();
   
   // para dejar todo como estaba al principio
#ifndef DOMJUDGE
   std::cin.rdbuf(cinbuf);
#endif
   return 0;
}
