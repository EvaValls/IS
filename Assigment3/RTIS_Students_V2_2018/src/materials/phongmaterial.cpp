#include "phongmaterial.h"

PhongMaterial::PhongMaterial(Vector3D ks_, Vector3D kd_, double n_)
	: Material(), ks(ks_), kd(kd_), n(n_)
{}

Vector3D PhongMaterial::getReflectance(const Vector3D &normal, const Vector3D &wo,
	const Vector3D &wi) const {
	Vector3D wr( 2 * (normal.x*wi.x)*normal.x - wi.x, 2 * (normal.y*wi.y)*normal.y - wi.y, 2 * (normal.z*wi.z)*normal.z - wi.z);
	Vector3D r(kd.x*(wi.x*normal.x) + ks.x*pow(wo.x*wr.x, n), kd.y*(wi.y*normal.y) + ks.y*pow(wo.y*wr.y, n), kd.z*(wi.z*normal.z) + ks.z*pow(wo.z*wr.z, n));
	return r;
}