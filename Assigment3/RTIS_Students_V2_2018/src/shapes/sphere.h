#ifndef SPHERE_H
#define SPHERE_H

#include <iostream>
#include <string>

#include "shape.h"
#include "../core/eqsolver.h"

class Sphere : public Shape
{
public:
    Sphere() = delete;
    Sphere(const double radius_, Matrix4x4 &t, Material *material_, double speed_, Vector3D motionDir_);

    Vector3D getNormalWorld(const Vector3D &pt_world) const;

    virtual bool rayIntersect(const Ray &ray, Intersection &its) const;
    virtual bool rayIntersectP(const Ray &ray) const;

    std::string toString() const;
	virtual void changePosition();

private:
    // The center of the sphere in local coordinates is assumed
    // to be (0, 0, 0). To pass to world coordinates just apply the
    // objectToWorld transformation contained in the mother class
    double radius;
};

std::ostream& operator<<(std::ostream &out, const Sphere &s);

#endif // SPHERE_H
