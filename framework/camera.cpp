#include "camera.hpp"
#include <cmath>


Camera::Camera(unsigned int breite, unsigned int hoehe, float oeffnungswinkel) :
    breite_{breite},
    hoehe_{hoehe},
    oeffnungswinkel_{oeffnungswinkel}
    {
        // d = Abstand vom Startpunkt zur "Pixelwand"
        d = (breite_/ 2.0f) / (std::tan((oeffnungswinkel_ * (180 / M_PI)) / 2.0f));
    };

Ray Camera::calcEyeRay(unsigned int x, unsigned int y) {
    float distanceMitte = 0.0f;
    distanceMitte = (breite_/ 2.0) / (std::tan(oeffnungswinkel_/ 2));

    Ray strahl;
    // mittelstrahl.origin = startpunkt_;
    // mittelstrahl.direction = {0.0f, 0.0f, -distanceMitte};

    // strahl = {0.0f, 0.0f, 0.0f} + t * {x - (width/ 2), y - (height/ 2), -d}
    float strahlx = x - (breite_ / 2);
    float strahly = y - (hoehe_ / 2);
    float strahlz = -d;
    strahl.origin = startpunkt_;
    strahl.direction = {strahlx, strahly, strahlz};
    
    return strahl;
}