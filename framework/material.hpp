#ifndef MATERIAL_HPP
#define MATERIAL_HPP
#include "color.hpp"
#include <string>
#include <glm/vec3.hpp>
#include <memory> //contains shared pointer

struct Material{
    std::string name_ = {" "};
    Color ka; 
    Color kd; 
    Color ks;
    float m; 

    std::ostream& operator<<(std::ostream& os){
        os << name_ << " (" << ka.r << ", " << ka.g << ", " << ka.b <<")\n" 
        << " (" << kd.r << ", " << kd.g << ", " << kd.b << ")\n" << " (" << ks.r << ", " << ks.g << ", " << ks.b << ")\n" << m << "\n";
        return os;
    }
};



#endif