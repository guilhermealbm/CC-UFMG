#ifndef PDS2_AQUECEDOR_H
#define PDS2_AQUECEDOR_H

class Aquecedor {
    private:
        double _temperatura;
        double _temperatura_minima;
        double _temperatura_maxima;
        double _fator_incremento;
    public:
    Aquecedor();
    Aquecedor(double temperatura_inicial);
    Aquecedor(double temperatura_inicial, double fator_incremento);
    void aquecer();
    void resfriar();
    double get_temperatura();
    void set_fator_incremento(double fator_incremento);
};

#endif