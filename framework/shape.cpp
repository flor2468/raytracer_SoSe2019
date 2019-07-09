#include "shape.hpp"
#include "material.hpp"
#include <iostream>

Shape::Shape():
    name_{" "},
    color_{} 
    {};
    
Shape::Shape(std::string name, std::shared_ptr<Material> color):
    name_ {name},
    color_{color}
    {/*std::cout<<"shape konstruktor\n";*/ };

Shape::~Shape(){
    std::cout<<"Shape destructor is called\n";
}

std::ostream& Shape::print (std::ostream& os ) const {
    os <<"Name: " << name_ << "\n"
    <<"ka: " << color_->ka.r << ", "<< color_->ka.g << ", " << color_->ka.b << "\n"
    <<"kd: " << color_->kd.r << ", "<< color_->kd.g << ", " << color_->kd.b << "\n"
    <<"ks: " << color_->ks.r << ", "<< color_->ks.g << ", " << color_->ks.b << "\n";
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