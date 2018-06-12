#include "shape.h"

Shape::Shape( Matrix4x4 &t_, Material *material_, double speed_, Vector3D motionDir_)
{
    objectToWorld = t_;
    objectToWorld.inverse(worldToObject);
    material = material_;
	speed = speed_;
	motionDir = motionDir_.normalized();
}

const Material& Shape::getMaterial() const
{
    return *material;
}
const double Shape::getSpeed() const
{
	return speed;
}
const Vector3D Shape::getMotionDirection() const {
	return motionDir;
}

void Shape::changePosition() {  };