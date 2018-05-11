#include "../materials/phongmaterial.h"
#include "directshader.h"
#include "../materials/mirrormaterial.h"

DirectShader::DirectShader(Vector3D color_, double maxDist_, Vector3D bgColor_)
	:Shader(bgColor_), maxDist(maxDist_), color(color_)
{}

Vector3D DirectShader::computeColor(const Ray &r, const std::vector<Shape*> &objList,
	const std::vector<PointLightSource> &lsList) const {
	
	Vector3D Lo = bgColor;

	// Get the current object
	Intersection its;
	
	bool intersects = Utils::getClosestIntersection(r, objList, its); 

	if (intersects) {
		//Viewing direction
		Vector3D wo = -r.d;
		
		//Phong Material of the object 
		/*const Material *m = &its.shape->getMaterial();
		
		const PhongMaterial* pm = dynamic_cast<const PhongMaterial*>(m);*/
		bool specular = its.shape->getMaterial().hasSpecular();
		bool diffuse = its.shape->getMaterial().hasDiffuseOrGlossy();
		bool transmission = its.shape->getMaterial().hasTransmission();

		if (specular) {
			const Material *m = &its.shape->getMaterial();

			const MirrorMaterial* mm = dynamic_cast<const MirrorMaterial*>(m); 
			Vector3D wr = Utils::computeReflectionDirection(r.d, its.normal);
			Ray reflectionRay(its.itsPoint, wr.normalized(), r.depth+1);
			Lo = computeColor(reflectionRay, objList, lsList);
		}
		if(diffuse)
		{
			for (int lsIndex = 0; lsIndex < lsList.size(); lsIndex++) {

				//Light source
				const PointLightSource ls = lsList.at(lsIndex);
				Vector3D I = ls.getIntensity(its.itsPoint);

				//Light direction
				Vector3D wi = (ls.getPosition() - its.itsPoint);


				Ray rShadow(its.itsPoint, wi.normalized());
				rShadow.maxT = wi.length();

				Vector3D rf = its.shape->getMaterial().getReflectance(its.normal.normalized(), wo.normalized(), wi.normalized());

				if (dot(its.normal, wi) > 0 && !Utils::hasIntersection(rShadow, objList)) {
					Lo += Utils::multiplyPerCanal(I, rf);
				}
			}
		}
		
	}
	
	return Lo;
}