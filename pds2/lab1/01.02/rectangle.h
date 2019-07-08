#ifndef PDS2_VPL_RECT_H
#define PDS2_VPL_RECT_H

/* 
 * Para suportar valores padrões. Crie 2 construtores, 1 sem parâmetros e outro
 * com parâmetros.
 */ 
 
#include <string>


class Rectangle{
    
    private:
        double _height;
        double _width;
        
    public:
        Rectangle(double width, double height);
        Rectangle();
        double get_height();
        double get_width();
        void set_height(double height);
        void set_width(double width);
        
        double get_perimeter();
        double get_area();
    
};

#endif