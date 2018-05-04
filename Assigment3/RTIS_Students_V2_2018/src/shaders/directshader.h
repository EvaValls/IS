#ifndef DIRECTSHADER_H
#define DIRECTSHADER_H

#include <vector>

#include "../core/ray.h"
#include "../lightsources/pointlightsource.h"
#include "../shapes/shape.h"
#include "../lightsources/pointlightsource.h"
#include "shader.h"
class DirectShader : public Shader
{
public:
	DirectShader();
	DirectShader(Vector3D bgColor_);

	virtual Vector3D computeColor(const Ray &r,
		const std::vector<Shape*> &objList,
		const std::vector<PointLightSource> &lsList) const;

	Vector3D bgColor;
};

#endif // DIRECTSHADER_H