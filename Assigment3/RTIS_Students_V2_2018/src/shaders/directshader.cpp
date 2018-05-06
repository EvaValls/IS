#include "../materials/phongmaterial.h"
#include "directshader.h"


DirectShader::DirectShader(Vector3D color_, double maxDist_, Vector3D bgColor_)
	:Shader(bgColor_), maxDist(maxDist_), color(color_)
{}

Vector3D DirectShader::computeColor(const Ray &r, const std::vector<Shape*> &objList,
	const std::vector<PointLightSource> &lsList) const {
	int V = 0;
	Vector3D wo = r.o;
	Vector3D Lo(0, 0, 0);
	for (size_t objIndex = 0; objIndex < objList.size(); objIndex++)
	{
		// Get the current object
		Intersection its;
		const Shape *obj = objList.at(objIndex);
		bool intersects = obj->rayIntersect(r, its);
	
		if (intersects) {
			
			for (int lsIndex = 0; lsIndex < lsList.size(); lsIndex++) {
				const PointLightSource ls = lsList.at(lsIndex);
				Vector3D I = ls.getIntensity(its.itsPoint);
				Vector3D wi = ls.getPosition();
				const Material *m = &obj->getMaterial();
				const PhongMaterial* pm = dynamic_cast<const PhongMaterial*>(m);
				//PhongMaterial phong = &m;
				Vector3D rf = pm->getReflectance(its.normal, wo, wi);
				Lo += Vector3D(I.x*rf.x, I.y*rf.y, I.z*rf.z);
			}
		}
	}
	
	return Lo;
}