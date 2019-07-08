#ifndef SHAPE_HPP
#define SHAPE_HPP
#include "color.hpp"
#include <iostream>
#include <string>
#include "hitpont.hpp"
#include "ray.hpp"

class Shape{  
    
    public:
        Shape();
        Shape(std::string name_, Color color_);
        ~Shape();
        virtual float area() = 0;
        virtual float volume() = 0;
        virtual std::ostream& print (std::ostream& os ) const;
        virtual hitpoint intersect(Ray const& ray, float& t) = 0;
        
    protected:
        std::string name_;
        Color color_;
};

std::ostream& operator<<(std::ostream& os, Shape const& s);


#endif