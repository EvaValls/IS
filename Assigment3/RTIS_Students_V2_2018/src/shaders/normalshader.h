#ifndef NORMALSHADER_H
#define NORMALSHADER_H

#include "shader.h"

class NormalShader : public Shader
{
public:
    NormalShader();
    NormalShader(Vector3D bgColor_);

    virtual Vector3D computeColor(const Ray &r,
                             const std::vector<Shape*> &objList,
                             const std::vector<PointLightSource> &lsList) const;
	virtual double computeDistance(const Ray &r, const std::vector<Shape*> &objList, const double &focalLength) const=0;
};

#endif // NORMALSHADER_H
