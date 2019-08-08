#include "camera.hpp"
#include <glm/vec3.hpp>
#include <glm/glm.hpp>
#include <cmath>


Camera::Camera(std::string name, float oeffnungswinkel, unsigned int breite, unsigned int hoehe, glm::vec3 blickrichtung, glm::vec3 up_vektor) :
    name_{name},
    oeffnungswinkel_{oeffnungswinkel},
    breite_{breite},
    hoehe_{hoehe},
    blickrichtung_{blickrichtung},
    up_vektor_{up_vektor}
    {
        // d = Abstand vom Startpunkt zur "Pixelwand"
        d = (breite_/ 2.0f) / std::tan(oeffnungswinkel_  /* * (180 / M_PI)) / 2.0f)*/ / 2.0f * M_PI / 180);
    };

Ray Camera::calcEyeRay(unsigned int x, unsigned int y) {

    /* Die Strahlen von der Kamera zu allen Pixeln werden berechnet */

    Ray strahl;

    // strahl = {0.0f, 0.0f, 0.0f} + t * {x - (width/ 2), y - (height/ 2), -d}
    float strahlx = x - (breite_ / 2.0f);
    float strahly = y - (hoehe_ / 2.0f);
    float strahlz = -d;
    strahl.origin = startpunkt_;
    glm::vec3 normstrahl = {strahlx, strahly, strahlz};
    strahl.direction = glm::normalize(normstrahl);
    
    return strahl;
}

glm::vec3 Camera::get_Startpunkt() {
    return startpunkt_;
}