#include "aquecedor.h"
#include <iostream>

Aquecedor::Aquecedor(){
    _temperatura = 20.00;
    _temperatura_minima = 10.00;
    _temperatura_maxima = 40.00;
    _fator_incremento = 5.00;
}

Aquecedor::Aquecedor(double temperatura_inicial){
    _temperatura = temperatura_inicial;
    _fator_incremento = 5.00;
    _temperatura_minima = 10.00;
    _temperatura_maxima = 40.00;
}

Aquecedor::Aquecedor(double temperatura_inicial, double fator_incremento){
    _temperatura = temperatura_inicial;
    _fator_incremento = fator_incremento;
    _temperatura_minima = 10.00;
    _temperatura_maxima = 40.00;
}

void Aquecedor::aquecer(){
    if (_temperatura + _fator_incremento > _temperatura_maxima){
        std::cout << "Impossivel aumentar mais a temperatura!\n";
        return;
    }else{
        _temperatura += _fator_incremento;
    }
}

void Aquecedor::resfriar(){
    if (_temperatura - _fator_incremento < _temperatura_minima){
        std::cout << "Impossivel abaixar mais a temperatura!\n";
        return;
    }else{
        _temperatura -= _fator_incremento;
    }
}

double Aquecedor::get_temperatura(){
    return _temperatura;
}

void Aquecedor::set_fator_incremento(double fator_incremento){
    _fator_incremento = fator_incremento;
}