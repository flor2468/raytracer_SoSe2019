#include "box.hpp"
#include <iostream>
#include <cmath>

Box::Box() :
    Shape(),
    min_{0.0f}, //vec 3 besteht aus 3 floats!!!! 3D vektor
    max_{0.0f}
    {};

Box::Box(std::string name, std::shared_ptr<Material> color, glm::vec3 min, glm::vec3 max):
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
    os << "Max: { " << max_.x << ", " << max_.y << ", " << max_.z << "}\nMin: {" 
    << min_.x << ", " << min_.y << ", " << min_.z << "}\n";
    return os;
}

hitpoint Box::intersect(Ray const& ray) {
    hitpoint h{};

    float txmin = (min_.x - ray.origin.x) / ray.direction.x;
    float tymin = (min_.y - ray.origin.y) / ray.direction.y;
    float tzmin = (min_.z - ray.origin.z) / ray.direction.z;
    float txmax = (max_.x - ray.origin.x) / ray.direction.x;
    float tymax = (max_.y - ray.origin.y) / ray.direction.y;
    float tzmax = (max_.z - ray.origin.z) / ray.direction.z;

    glm::vec3 sp1 = ray.origin + txmin * ray.direction; 
    glm::vec3 sp2 = ray.origin + tymin * ray.direction; 
    glm::vec3 sp3 = ray.origin + tzmin * ray.direction; 
    glm::vec3 sp4 = ray.origin + txmax * ray.direction; 
    glm::vec3 sp5 = ray.origin + tymax * ray.direction; 
    glm::vec3 sp6 = ray.origin + tzmax * ray.direction; 

    // std::cout << "INF: " << std::numeric_limits<float>::infinity() << std::endl;

    if(sp1.y > min_.y && sp1.y < max_.y && sp1.z > min_.z && sp1.z < max_.z) {
        h.cut = true;
        if(txmin < h.distance) {
            h.distance = txmin;
            h.point3d.x = ray.origin.x + txmin * ray.direction.x;
            h.point3d.y = ray.origin.y + txmin * ray.direction.y;
            h.point3d.z = ray.origin.z + txmin * ray.direction.z;
            h.normale_ = {-1,0,0};
        }
        h.name = name_;
        h.col = color_;
        h.direction = ray.direction;
        
    }

    if(sp2.x > min_.x && sp2.x < max_.x && sp2.z > min_.z && sp2.z < max_.z) {
        h.cut = true;
        if(tymin < h.distance) {
            h.distance = tymin;
            h.point3d.x = ray.origin.x + tymin * ray.direction.x;
            h.point3d.y = ray.origin.y + tymin * ray.direction.y;
            h.point3d.z = ray.origin.z + tymin * ray.direction.z;
            h.normale_ = {0,-1,0};
        }
        h.name = name_;
        h.col = color_;
        
        h.direction = ray.direction;
        
    }

    if(sp3.y > min_.y && sp3.y < max_.y && sp3.x > min_.x && sp3.x < max_.x) {
        h.cut = true;
        if(tzmin < h.distance) {
            h.distance = tzmin;
            h.point3d.x = ray.origin.x + tzmin * ray.direction.x;
            h.point3d.y = ray.origin.y + tzmin * ray.direction.y;
            h.point3d.z = ray.origin.z + tzmin * ray.direction.z;
            h.normale_ = {0,0,-1};
        }
        h.name = name_;
        h.col = color_;
        
        h.direction = ray.direction;
        
    }

    if(sp4.y > min_.y && sp4.y < max_.y && sp4.z > min_.z && sp4.z < max_.z) {
        h.cut = true;
        if(txmax < h.distance) {
            h.distance = txmax;
            h.point3d.x = ray.origin.x + txmax * ray.direction.x;
            h.point3d.y = ray.origin.y + txmax * ray.direction.y;
            h.point3d.z = ray.origin.z + txmax * ray.direction.z;
            h.normale_ = {1,0,0};
        }
        h.name = name_;
        h.col = color_;
        
        h.direction = ray.direction;

    }

    if(sp5.x > min_.x && sp5.x < max_.x && sp5.z > min_.z && sp5.z < max_.z) {
        h.cut = true;
        if(tymax < h.distance) {
            h.distance = tymax;
            h.point3d.x = ray.origin.x + tymax * ray.direction.x;
            h.point3d.y = ray.origin.y + tymax * ray.direction.y;
            h.point3d.z = ray.origin.z + tymax * ray.direction.z;
            h.normale_ = {0,1,0};
        }
        h.name = name_;
        h.col = color_;
        
        h.direction = ray.direction;
        
    }

    if(sp6.y > min_.y && sp6.y < max_.y && sp6.x > min_.x && sp6.x < max_.x) {
        h.cut = true;
        if(tzmax < h.distance) {
            h.distance = tzmax;
            h.point3d.x = ray.origin.x + tzmax * ray.direction.x;
            h.point3d.y = ray.origin.y + tzmax * ray.direction.y;
            h.point3d.z = ray.origin.z + tzmax * ray.direction.z;
            h.normale_ = {0,0,1};
        }
        h.name = name_;
        h.col = color_;
        
        h.direction = ray.direction;
        
    }

    return h;
}

glm::vec3 Box::get_normal(hitpoint const& hit) {

    glm::vec3 a = {min_.x, min_.y, min_.z};
    glm::vec3 b = {max_.x, min_.y, min_.z};
    glm::vec3 c = {max_.x, min_.y, max_.z};
    glm::vec3 d = {min_.x, min_.y, max_.z};
    glm::vec3 e = {min_.x, max_.y, min_.z};
    glm::vec3 f = {max_.x, max_.y, min_.z};
    glm::vec3 g = {max_.x, max_.y, max_.z};
    glm::vec3 h = {min_.x, max_.y, max_.z};

    glm::vec3 normale;
    
    // glm::vec3 ab = b - a;
    // glm::vec3 ef = f - e;
    // glm::vec3 dc = c - d;
    // glm::vec3 hg = g - h;
    // glm::vec3 ad = d - a;
    // glm::vec3 bc = c - b;
    // glm::vec3 eh = h - e;
    // glm::vec3 fg = g - f;
    // glm::vec3 ae = e - a;
    // glm::vec3 bf = f - b;
    // glm::vec3 dh = h - d;
    // glm::vec3 cg = g - c;

    if((hit.point3d.x == f.x && hit.point3d.x == g.x) || (hit.point3d.x == e.x && hit.point3d.x == h.x)) {
        normale = {-1,0,0};
    }

    if((hit.point3d.y == f.y && hit.point3d.y == g.y) || (hit.point3d.y == b.y && hit.point3d.y == c.y)) {
        normale = {0,1,0};
    }

    if((hit.point3d.z == f.z && hit.point3d.z == b.z) || (hit.point3d.z == g.z && hit.point3d.z == c.z)) {
        normale = {0,0,1};
    }
    
    return normale;
}