#include "rectangle.h"
      
Rectangle::Rectangle(double width, double height){
    _height = height;
    _width = width;
}

Rectangle::Rectangle(){
    _height = 1.0;
    _width = 1.0;
}

double Rectangle::get_height(){
    return _height;
}

double Rectangle::get_width(){
    return _width;
}

void Rectangle::set_height(double height){
    if (height > 0.0 && height < 20.0)
        _height = height;
}

void Rectangle::set_width(double width){
    if (width > 0.0 && width < 20.0)
        _width = width;
    
}


double Rectangle::get_perimeter(){
    return _width + _width + _height + _height;
    
}
double Rectangle::get_area(){
    return _width * _height;
    
}