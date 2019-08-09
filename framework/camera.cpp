#include "camera.hpp"
#include "renderer.hpp"
#include <glm/vec3.hpp>
// #include <glm/glm.hpp>
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
    
    glm::mat4 matrix = camera_transformation();
    strahl = transformRay(matrix, strahl);

    return strahl;
    
}

glm::vec3 Camera::get_Startpunkt() {
    return startpunkt_;
}

glm::mat4 Camera::camera_transformation() {
    glm::vec3 n = glm::normalize(blickrichtung_);
    glm::vec3 e = startpunkt_;
    glm::vec3 u = glm::normalize(glm::cross(n, up_vektor_));
    glm::vec3 v = glm::normalize(glm::cross(u, n));

    glm::mat4 c = {
        glm::vec4 {u.x, u.y, u.z, 0},
        glm::vec4 {v.x, v.y, v.z, 0},
        glm::vec4 {-1 * n.x, -1 * n.y, -1 * n.z, 0},
        glm::vec4 {e.x, e.y, e.z, 1}
    };
    
    return c;
}