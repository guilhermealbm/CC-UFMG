#ifndef PDS2_VPL_DATA_H
#define PDS2_VPL_DATA_H

/*
 * Sua classe deve conter:
 * - atributos: dia, mes e ano
 * - metodos: get_dia(), get_mes(), get_ano(), get_data_curto(),
 *            get_data_longo();
 * - get_data_curto() -> 22/08/2018
 * - get_data_longo() -> 22 de agosto de 2018
 *                       para este, c++ suporta array de strings
 *                       std::string cor[3] = {"Blue", "Red", "Orange"};
 *
 * C++ também suporta o operador + em strings:
 * std::string s = "Hello";
 * std::string greet = s + " World";
 * greet == "Hello World"
 */
 
#include <string>


class Data {
    
    private:
        int _dia;
        int _mes;
        int _ano;
        
    public:
    
        Data(int dia, int mes, int ano);
        int get_dia();
        int get_mes();
        int get_ano();
        std::string get_data_curto();
        std::string get_data_longo();
    
};

#endif