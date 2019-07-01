#include "shape.hpp"
#include <iostream>

Shape::Shape():
    name_{" "},
    color_{0.0f, 0.0f, 0.0f}
    {};
    
Shape::Shape(std::string name, Color color):
    name_ {name},
    color_{color}
    {/*std::cout<<"shape konstruktor\n";*/ };

Shape::~Shape(){
    std::cout<<"Shape destructor is called\n";
}

std::ostream& Shape::print (std::ostream& os ) const {
    os <<"Name: " << name_ << "\n"
    << "{ " << color_.r << ", " << color_.g << ", " << color_.b << "}";
    return os;
}

std::ostream& operator<<(std::ostream& os, Shape const& s ){
    s.print(os);
}

//Aufgabe 1
   // virtual float Shape::area() = 0{

    //} 

    //virtual float Shape::volume() = 0{
    //}