#include "depthshader.h"

DepthShader::DepthShader(Vector3D color_, double maxDist_, Vector3D bgColor_)
	: Shader( bgColor_), maxDist(maxDist_), color(color_)
{}

Vector3D DepthShader::computeColor(const Ray &r, const std::vector<Shape*> &objList, 
									const std::vector<PointLightSource> &lsList) const {
	Vector3D newColor = Shader::bgColor;
	for (size_t objIndex = 0; objIndex < objList.size(); objIndex++)
	{
		// Get the current object
		Intersection its;
		const Shape *obj = objList.at(objIndex);
		bool intersects = obj->rayIntersect(r, its);
		
		if (intersects) {
			Vector3D d = r.o - its.itsPoint;
			double dist = sqrt(d.x* d.x + d.y* d.y + d.z*d.z);
			if (dist < maxDist) {
				newColor = color*(1.0 - dist / maxDist);
			}
		} 

	}

	return newColor;
}

