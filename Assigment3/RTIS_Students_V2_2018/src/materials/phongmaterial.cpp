#include "phongmaterial.h"

PhongMaterial::PhongMaterial(Vector3D ks_, Vector3D kd_, double n_)
	: Material(), ks(ks_), kd(kd_), n(n_)
{}

Vector3D PhongMaterial::getReflectance(const Vector3D &normal, const Vector3D &wo,
	const Vector3D &wi) const {
	//ideal reflection direction
	Vector3D win = dot(wi, normal);
	Vector3D wr( 2 * win.x*normal.x - wi.x, 2 * win.y*normal.y - wi.y, 2 * win.z*normal.z - wi.z);
	//diffuse reflectance
	Vector3D rd(kd.x*win.x, kd.y*win.y, kd.z*win.z);
	//specular reflectance
	Vector3D wowr = dot(wo, wr);
	Vector3D rs(ks.x*pow(wowr.x,n), ks.y*pow(wowr.y, n), ks.z*pow(wowr.z, n));
	Vector3D r = rd + rs;
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