#include "../materials/phongmaterial.h"
#include "directshader.h"
#include "../materials/mirrormaterial.h"
#include "../materials/transmissivematerial.h"

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
			//const Material *m = &its.shape->getMaterial();

			//const TransmissiveMaterial* mm = dynamic_cast<const TransmissiveMaterial*>(m);
			Vector3D wr = Utils::computeReflectionDirection(r.d, its.normal);
			Ray reflectionRay(its.itsPoint, wr.normalized(), r.depth+1);
			Lo = computeColor(reflectionRay, objList, lsList);
		}
		if (transmission) {
			//const Material *m = &its.shape->getMaterial();
			

			
		
				
			//Compute eta coeffs
			double eta2= its.shape->getMaterial().getIndexOfRefraction();
			double eta1 = 1;
			double eta = eta2/eta1;

			//computing wt
			double cosThetaI = dot(r.d, -its.normal);
			Vector3D n;
			if (cosThetaI < 0) {
				n = -its.normal;
				eta = eta1 / eta2;
			}
			else
				n = its.normal;
			double cosThetaT;
			bool hasTotalReflection = Utils::isTotalInternalReflection(eta, cosThetaI, cosThetaT);

			if (hasTotalReflection) {
				Vector3D wr = Utils::computeReflectionDirection(r.d, n);
				Ray reflectionRay(its.itsPoint, wr.normalized(), r.depth + 1);
				Lo = computeColor(reflectionRay, objList, lsList);
			}
			else {
				Ray transRay(its.itsPoint, r.d.normalized());
				Vector3D wt = Utils::computeTransmissionDirection(transRay, n, eta, cosThetaI, cosThetaT);
				Ray refracRay(its.itsPoint, wt.normalized(), r.depth + 1);
				Lo += computeColor(refracRay, objList, lsList);
			}
			
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