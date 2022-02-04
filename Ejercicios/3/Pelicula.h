#ifndef PELICULA
#define PELICULA
#include <string>
#include <iostream>
#include "Hora.h"

class Pelicula {
public: 
    bool operator<(const Pelicula& p) const{
        return ((this->_horaInicio + this->_duracion) < (p._horaInicio + p._duracion)) || ((this->_horaInicio + this->_duracion) == (p._horaInicio + p._duracion) && (this->_nombre < p._nombre));
    }
    friend std::istream& operator>>(std::istream& out, Pelicula& p);
    friend std::ostream& operator<<(std::ostream& in, const Pelicula& p);
    
private:
    Hora _horaInicio, _duracion;
    std::string _nombre;
};

std::istream& operator>>(std::istream& in, Pelicula& p){
    in >> p._horaInicio >> p._duracion;
    std::getline(in, p._nombre);
    return in;
}

std::ostream& operator<<(std::ostream& out, const Pelicula& p){
    out << p._horaInicio + p._duracion << ' ' << p._nombre;
    return out;
}
#endif
