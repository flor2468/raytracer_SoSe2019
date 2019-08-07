#ifndef CAMERA_HPP
#define CAMERA_HPP
#include <glm/vec3.hpp>
#include "ray.hpp"
#include <string>


class Camera {
    public:
        Camera(std::string name = "Kamera", float oeffnungswinkel = 60.0f, unsigned int breite = 800, unsigned int hoehe = 600, glm::vec3 blickrichtung = {0,0,-1}, 
        glm::vec3 up_vektor = {0,1,0});

        // Camera(std::string name = "Kamera", float oeffnungswinkel = 60.0f);

        Ray calcEyeRay(unsigned int x, unsigned int y);
        glm::vec3 get_Startpunkt();

    private: 
        unsigned int breite_; // breite und leange = aufloesung
        unsigned int hoehe_;
        float oeffnungswinkel_; // <fov-x>
        glm::vec3 startpunkt_ = {0.0f, 0.0f, 0.0f}; // <eye>
        float d;
        std::string name_; // <name>
        glm::vec3 blickrichtung_; // <dir>
        glm::vec3 up_vektor_; // <up>
        
};

#endif