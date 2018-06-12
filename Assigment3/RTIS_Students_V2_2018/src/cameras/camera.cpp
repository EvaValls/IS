#include "camera.h"

Camera::Camera(const Matrix4x4 &cameraToWorld_, const Film &film_, double expositionTime_)
    : cameraToWorld(cameraToWorld_), film(film_), expositionTime(expositionTime_)
{
    aspect = (double) (film.getWidth()) / (double) (film.getHeight());
}

