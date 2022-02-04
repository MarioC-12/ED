#ifndef HORA
#define HORA
#include <assert.h>
#include <iostream>
#include <iomanip>

const size_t SEGUNDOS_DIA = 86400;

class Hora {
public: 
    bool operator<(const Hora& h) const{
        return this->segundosTotales() < h.segundosTotales();
    }
    bool operator<=(const Hora& h) const{
        return this->segundosTotales() <= h.segundosTotales();
    }
    bool operator==(const Hora& h) const{
        return this->segundosTotales() == h.segundosTotales();
    }
    Hora operator+(const Hora& h) const;
    friend std::istream& operator>>(std::istream& input, Hora& h);
    friend std::ostream& operator<<(std::ostream& output, const Hora& h);
        
private:
    size_t segundosTotales() const {
        return _horas * 3600 + _minutos * 60 + _segundos;
    }
    size_t _horas;
    size_t _minutos;
    size_t _segundos;
};

Hora Hora::operator+(const Hora& h) const {
    Hora res;
    size_t segundos = this->segundosTotales() + h.segundosTotales();
    assert(segundos <= SEGUNDOS_DIA);
    res._horas = segundos / 3600; res._minutos = (segundos % 3600) / 60; res._segundos = (segundos % 3600) % 60; 
    return res;
}

std::istream& operator>>(std::istream& input, Hora& h) {
    char aux;
    input >> h._horas; input.get(aux);
    input >> h._minutos; input.get(aux);
    input >> h._segundos; input.get(aux);
    return input;
}

std::ostream& operator<<(std::ostream& output, const Hora& h) {
    output << std::setfill('0') << std::setw(2) << h._horas << ':' << std::setw(2) << h._minutos << ':' << std::setw(2) << h._segundos;
    return output;
}

#endif
