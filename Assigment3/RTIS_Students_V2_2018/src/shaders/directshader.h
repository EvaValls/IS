#ifndef DIRECTSHADER_H
#define DIRECTSHADER_H

#include <vector>

#include "../core/ray.h"
#include "../core/utils.h"
#include "../lightsources/pointlightsource.h"
#include "../shapes/shape.h"
#include "../lightsources/pointlightsource.h"
#include "shader.h"
class DirectShader : public Shader
{
public:
	DirectShader()= delete;
	DirectShader(Vector3D color_, double maxDist_, Vector3D bgColor);

	virtual Vector3D computeColor(const Ray &r,
		const std::vector<Shape*> &objList,
		const std::vector<PointLightSource> &lsList) const;
	virtual double computeDistance(const Ray &r, const std::vector<Shape*> &objList, const double &focalLength) const;
	
private:
	Vector3D bgColor;
	double maxDist; // Used to store the value of the maximum distance which can be visualized
	Vector3D color; // Used to store the visualization color
};

#endif // DIRECTSHADER_H