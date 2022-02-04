#ifndef MULTICONJUNTO_H
#define MULTICONJUNTO_H
#include <algorithm>
#include <string>

const size_t MAX_ELEMS = 2000;

class Multiconjunto {
public:
    Multiconjunto(): num_elems(0) {}
    void anyadir(size_t elem);
    void eliminar(size_t elem);
    bool pertenece(size_t elem) const;

private: 
    struct Elem {
        size_t valor, multiplicidad;
    };
    Elem elems[MAX_ELEMS];
    size_t num_elems;

    struct Busq {
        size_t indice;
        bool pertenece;
    };
    Busq busqBinaria(size_t elem) const;
};

//Coste logarítmico
Multiconjunto::Busq Multiconjunto::busqBinaria(size_t elem) const {
    size_t ini = 0, fin = num_elems;
    Multiconjunto::Busq sol = {0, false};
    while (ini < fin) {

        size_t m = (ini + fin) / 2;

        if (elems[m].valor < elem) {
            ini = m + 1;
            sol.indice = m + 1;
        }
        else {
            fin = m;
            if (elems[m].valor == elem) {
                sol.pertenece = true; 
            }
            sol.indice = m;
        }

    }
    return sol;
}

//Coste lineal
//Si el elemento pertenece simplemente se suma multiplicidad
//Si no, se desplazan los de valor superior y se sitúa en la posición del índice con multiplicidad 1.
void Multiconjunto::anyadir(size_t elem) {
    if (num_elems < MAX_ELEMS) {
        Busq busq = busqBinaria(elem);
        if (busq.pertenece){
            elems[busq.indice].multiplicidad++;
        }
        else {
            for (size_t i = num_elems; i > busq.indice; --i) {
                elems[i] = elems[i - 1];
            }
            elems[busq.indice] = {elem, 1}; ++num_elems;
        }
    }
}

//Coste lineal
//Si la multiplicidad es mayor que uno simplemente se le resta.
//Si es 1, se desplazan los elementos superiores hacia la izquierda.
void Multiconjunto::eliminar(size_t elem) {
    Busq busq = busqBinaria(elem);
    if (busq.pertenece) {
        if (elems[busq.indice].multiplicidad > 1) {
            elems[busq.indice].multiplicidad--;
        }
        else {
            for (size_t i = busq.indice; i < num_elems; ++i) {
                elems[i] = elems[i+1];
            }
            --num_elems;
        }
    }
}

//Coste logaritmico
bool Multiconjunto::pertenece(size_t elem) const {
    return busqBinaria(elem).pertenece;
}

#endif
