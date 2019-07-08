#include "data.h"

Data::Data(int dia, int mes, int ano){
    _dia = dia;
    _mes = mes;
    _ano = ano;
}

int Data::get_dia(){
    return _dia;
}

int Data::get_mes(){
    return _mes;
}

int Data::get_ano(){
    return _ano;
}

std::string Data::get_data_curto(){
    return(std::to_string(_dia) + "/" + std::to_string(_mes) + "/" + std::to_string(_ano));
}

std::string Data::get_data_longo(){
    std::string mes_extenso = "";
    
    switch(_mes){
        case 1:
            mes_extenso = "janeiro";
            break;
        case 2:
            mes_extenso = "fevereiro";
            break;
        case 3:
            mes_extenso = "março";
            break;
        case 4:
            mes_extenso = "abril";
            break;
        case 5:
            mes_extenso = "maio";
            break;
        case 6:
            mes_extenso = "junho";
            break;
        case 7:
            mes_extenso = "julho";
            break;
        case 8:
            mes_extenso = "agosto";
            break;
        case 9:
            mes_extenso = "setembro";
            break;
        case 10:
            mes_extenso = "outubro";
            break;
        case 11:
            mes_extenso = "novembro";
            break;
        case 12:
            mes_extenso = "dezembro";
            break;
    }
    
    return(std::to_string(_dia) + " de " + mes_extenso + " de " + std::to_string(_ano));

    
}