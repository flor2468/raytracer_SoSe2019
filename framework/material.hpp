#ifndef MATERIAL_HPP
#define MATERIAL_HPP
#include "color.hpp"
#include <string>
#include <glm/vec3.hpp>
#include <memory> //contains shared pointer

struct Material{
    // Material();
    // Material(std::string name_, float ka_r, float ka_g, float ka_b, float kd_r, float kd_g, float kd_b, float ks_r, float ks_g, float ks_b, float m) ;
    //Material(std::string name_, Color ka, Color kd, Color ks, float m);
    //Material(std::string name_, Color ka{float r, float g, float b}, Color kd{float r, float g, float b}, Color ks{float r, float g, float b}, float m);
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