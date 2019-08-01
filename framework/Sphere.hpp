#ifndef SPHERE_HPP
#define SPHERE_HPP
#include "shape.hpp"
#include <glm/vec3.hpp>
#include <glm/gtx/intersect.hpp>
#include "hitpont.hpp"
#include "ray.hpp"

class Sphere: public Shape{
    

    public:
        public:Sphere();
        ~Sphere();
        Sphere(std::string name_, std::shared_ptr<Material> color_, glm::vec3 center_, float radius_);
        virtual float area() override;
        virtual float volume() override;
        virtual std::ostream& print (std::ostream& os) const override;
        hitpoint intersect(Ray const& ray) override;
        glm::vec3 get_normal(hitpoint const& h) override;

    private:
        glm::vec3 center_;
        float radius_;
};
#endif