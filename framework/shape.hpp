#ifndef SHAPE_HPP
#define SHAPE_HPP
#include "color.hpp"
#include <iostream>
#include <string>

class Shape{  
    
    public:
        Shape();
        Shape(std::string name_, Color color_);
        ~Shape();
        virtual float area() = 0;
        virtual float volume() = 0;
        virtual std::ostream& print (std::ostream& os ) const;
        
    protected:
        std::string name_;
        Color color_;
};

std::ostream& operator<<(std::ostream& os, Shape const& s);


#endif