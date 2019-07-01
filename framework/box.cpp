#include "box.hpp"

Box::Box() :
    Shape(),
    min_{0.0f}, //vec 3 besteht aus 3 floats!!!! 3D vektor
    max_{0.0f}
    {};

Box::Box(std::string name, Color color, glm::vec3 min, glm::vec3 max):
    Shape{name, color},
    min_{min},
    max_{max}
    {};


float Box::area(){
    float x = max_.x-min_.x;
    float y = max_.y-min_.y;
    float z = max_.z-min_.z;

    return 2*x*y + 2*x*z + 2*y*z;
}

float Box::volume(){
    float x = max_.x-min_.x;
    float y = max_.y-min_.y;
    float z = max_.z-min_.z;
    return x*y*z;    
}

std::ostream& Box::print (std::ostream& os) const{ //<< überladen 
    Shape::print(os);
    os << ", { " << max_.x << ", " << max_.y << ", " << max_.z << "}, {" 
    << min_.x << ", " << min_.y << ", " << min_.z << "}\n";
    return os;
}