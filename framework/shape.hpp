#ifndef SHAPE_HPP
#define SHAPE_HPP
#include "color.hpp"
#include <glm/glm.hpp>
#include <iostream>
#include <string>
#include "hitpont.hpp"
#include "ray.hpp"
#include "material.hpp"

class Shape{  
    
    public:
        Shape();
        Shape(std::string name_, std::shared_ptr<Material> color_);
        ~Shape();
        virtual float area() = 0;
        virtual float volume() = 0;
        virtual std::ostream& print (std::ostream& os ) const;
        virtual hitpoint intersect(Ray const& ray) = 0;
        virtual glm::vec3 get_normal(hitpoint const& h) = 0;
        virtual std::shared_ptr<Material> get_Material() = 0;

        // virtual Shape translate(std::shared_ptr<Shape> const& s, Scene const& scene, glm::vec3 verschiebung) = 0;
        // virtual Ray transformRay(glm::mat4 const& mat, Ray const& ray) = 0;
        
    protected:
        std::string name_;
        std::shared_ptr<Material> color_;

    public:
        glm::mat4 world_transformation_ = {
            glm::vec4 {1, 0, 0, 0},
            glm::vec4 {0, 1, 0, 0},
            glm::vec4 {0, 0, 1, 0},
            glm::vec4 {0, 0, 0, 1},
        };
        glm::mat4 world_transformation_invers_ = glm::inverse(world_transformation_);
};

std::ostream& operator<<(std::ostream& os, Shape const& s);


#endif