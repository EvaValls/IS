#include "mirrormaterial.h"

MirrorMaterial::MirrorMaterial(Vector3D ks_)
	: Material(), ks(ks_)
{}

Vector3D MirrorMaterial::getReflectance(const Vector3D &normal, const Vector3D &wo, const Vector3D &wi) const {
	
	double won = dot(wo, normal);
	//ideal reflection direction
	Vector3D wr = normal * 2 * won - wo;

	return wr;
}

