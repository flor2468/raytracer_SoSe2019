#ifndef BOX_HPP
#define BOX_HPP
#include "shape.hpp"
#include "scene.hpp"
#include <string>
#include <glm/vec3.hpp>

class Box: public Shape{
    public:
        Box();
        Box(std::string name_, std::shared_ptr<Material> color_, glm::vec3 min_, glm::vec3 max_);

        virtual float area() override;
        virtual float volume() override;
        virtual std::ostream& print (std::ostream& os) const override;
        virtual hitpoint intersect(Ray const& ray) override;
        virtual glm::vec3 get_normal(hitpoint const& h) override;
        virtual std::shared_ptr<Material> get_Material() override;
        // virtual Ray transformRay(glm::mat4 const& mat, Ray const& ray) override;
        // Box translate(std::shared_ptr<Box> const& s, Scene const& scene, glm::vec3 verschiebung);

    private:
        glm::vec3 min_;
        glm::vec3 max_;
};
#endif