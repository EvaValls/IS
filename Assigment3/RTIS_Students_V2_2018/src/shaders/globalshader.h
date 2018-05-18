#ifndef GLOBALSHADER_H
#define GLOBALSHADER_H
#define _USE_MATH_DEFINES
#include <vector>

#include "../core/ray.h"
#include "../core/utils.h"
#include "../lightsources/pointlightsource.h"
#include "../shapes/shape.h"
#include "../core/hemisphericalsampler.h"
#include "shader.h"
#include <cmath>
class GlobalShader : public Shader
{
public:
	GlobalShader() = delete;
	GlobalShader(Vector3D color_, double maxDist_, Vector3D bgColor);

	virtual Vector3D computeColor(const Ray &r,
		const std::vector<Shape*> &objList,
		const std::vector<PointLightSource> &lsList) const;


private:
	Vector3D bgColor;
	double maxDist; // Used to store the value of the maximum distance which can be visualized
	Vector3D color; // Used to store the visualization color
};
#endif // GLOBALSHADER

