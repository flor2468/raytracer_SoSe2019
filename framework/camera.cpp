#include "camera.hpp"
#include <cmath>

Camera::Camera() :
    breite_{800},
    laenge_{600},
    oeffnungswinkel_{60},
    startpunkt_{0.0f, 0.0f, 0.0f}
    {};

Camera::Camera(int breite, int laenge) :
    breite_{breite},
    laenge_{laenge}
    {};

Ray Camera::calcEyeRay(int x, int y) {
    float distanceMitte = 0.0f;
    distanceMitte = (breite_/ 2) / (tan(oeffnungswinkel_/ 2));

    Ray mittelstrahl;
    mittelstrahl.origin = startpunkt_;
    mittelstrahl.direction = {0.0f, 0.0f, -distanceMitte};
}