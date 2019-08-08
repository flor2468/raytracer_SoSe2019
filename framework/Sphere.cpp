#include "Sphere.hpp"
#include <math.h>
#include <string>
#include "material.hpp"

Sphere::Sphere():
    Shape(),
    center_{},
    radius_{0.0f}
    {};

Sphere::Sphere(std::string name, std::shared_ptr<Material> color, glm::vec3 center, float radius):
    Shape{name, color},
    center_{center},
    radius_{radius}
    {};
Sphere::~Sphere(){
    std::cout<<"Sphere destructor is called\n";
}

float Sphere::area(){
    return 4*M_PI*radius_*radius_;
}

float Sphere::volume(){
    return 4.0f/3.0f* M_PI*radius_*radius_*radius_;    
}


std::ostream& Sphere::print (std::ostream& os) const{
    Shape::print(os);
    os << ", { " << center_.x << ", " << center_.y << ", " << center_.z << "}, {" 
    << radius_ << "}\n";
    return os;
}

hitpoint Sphere::intersect(Ray const& ray/*, float& distance*/){
    hitpoint h{};
    
    h.cut = glm::intersectRaySphere(ray.origin, glm::normalize(ray.direction), center_, radius_*radius_, h.distance);
    if(h.cut == false){ //wenn sie sich nicht schneiden
        return h;
    }
    else{
        // h.distance = distance;
        // std::cout << "Test" << std::endl;
        h.name = name_;
        h.col = color_;
        h.point3d.x = ray.origin.x + h.distance * ray.direction.x;
        h.point3d.y = ray.origin.y + h.distance * ray.direction.y;
        h.point3d.z = ray.origin.z + h.distance * ray.direction.z;
        h.direction = ray.direction;

        /* Normale des Hitpoints zeigt von center_ zum Schnittpunkt (Hitpoint) auf der Kugel */
        h.normale_ = glm::normalize(h.point3d - center_);
        return h;
    }

}

std::string Sphere::get_name() {
    return name_;
}

std::shared_ptr<Material> Sphere::get_Material() {
    return color_;
}

glm::vec3 Sphere::get_Center() {
    return center_;
}

// Ray Sphere::transformRay(glm::mat4 const& mat, Ray const& ray) {
//     // Transformation des Strahls = Strahl in die andere Richtung schießen?
// }

// void Sphere::translate(std::shared_ptr<Sphere> const& s, Scene const& scene, glm::vec3 verschiebung) {
//     /* Verschiebung des Objekts */

//     glm::vec3 center = s->get_Center();
//     glm::vec4 p;
//     glm::vec4 center_verschoben;
//     p.w = center.x;
//     p.x = center.y;
//     p.y = center.z;
//     p.z = 1;
    
//     glm::mat4 matrix = {
//         glm::vec4 {1, 0, 0, 0},
//         glm::vec4 {0, 1, 0, 0},
//         glm::vec4 {0, 0, 1, 0},
//         glm::vec4 {verschiebung.x, verschiebung.y, verschiebung.z, 1}
//     };

//     center_verschoben = matrix * p;

//     center_.x = center_verschoben.w;
//     center_.y = center_verschoben.x;
//     center_.z = center_verschoben.y;
    
//     // center.x = center_verschoben.w;
//     // center.y = center_verschoben.x;
//     // center.z = center_verschoben.y;
// }

// void Sphere::set_Center(glm::vec3 c) {
//     center_ = c;
// }
