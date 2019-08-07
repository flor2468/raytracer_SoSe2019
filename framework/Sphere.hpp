#ifndef SPHERE_HPP
#define SPHERE_HPP
#include "shape.hpp"
#include <glm/glm.hpp>
#include <glm/vec3.hpp>
#include <glm/gtx/intersect.hpp>
#include "hitpont.hpp"
#include "ray.hpp"
#include "scene.hpp"

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
        std::shared_ptr<Material> get_Material() override;
        // void translate(std::shared_ptr<Sphere> const& s, Scene const& scene, glm::vec3 verschiebung);
        glm::vec3 get_Center();
        void set_Center(glm::vec3 c);
        // Ray transformRay(glm::mat4 const& mat, Ray const& ray) override;

    private:
        glm::vec3 center_;
        float radius_;
};
#endif