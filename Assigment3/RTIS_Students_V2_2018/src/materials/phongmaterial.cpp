#include "phongmaterial.h"

PhongMaterial::PhongMaterial(Vector3D ks_, Vector3D kd_, double n_)
	: Material(), ks(ks_), kd(kd_), n(n_)
{}

Vector3D PhongMaterial::getReflectance(const Vector3D &normal, const Vector3D &wo,
	const Vector3D &wi) const {
	
	double win = dot(wi, normal); 
	//ideal reflection direction
	Vector3D wr = normal*2*win-wi;

	//diffuse reflectance
	Vector3D rd = kd* win;

	
	//specular reflectance
	double wowr = dot(wo, wr);
	Vector3D rs  =ks * pow(wowr, n);

	//total reflectance

	Vector3D r = rd+rs;

	return r;
}

/*bool PhongMaterial::hasSpecular() const {
	if (ks != Vector3D(0,0,0)) {
		return true;
	}
	return false;
}
virtual bool hasTransmission() const = 0;
virtual bool hasDiffuseOrGlossy() const = 0;
virtual double getIndexOfRefraction() const;*/