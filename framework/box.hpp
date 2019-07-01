#ifndef BOX_HPP
#define BOX_HPP
#include "shape.hpp"
#include <string>
#include <glm/vec3.hpp>

class Box: public Shape{
    public:
        Box();
        Box(std::string name_, Color color_, glm::vec3 min_, glm::vec3 max_);
        virtual float area() override;
        virtual float volume() override;
        virtual std::ostream& print (std::ostream& os) const override;

    private:
        glm::vec3 min_;
        glm::vec3 max_;


};
#endif