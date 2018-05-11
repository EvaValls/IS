#include "transmissivematerial.h"

TransmissiveMaterial::TransmissiveMaterial(double coef_, Vector3D ks_)
	: Material(), ks(ks_), coef(coef_)
{}

Vector3D TransmissiveMaterial::getReflectance(const Vector3D &normal, const Vector3D &wo, const Vector3D &wi) const {

	double won = dot(wo, normal);
	//ideal reflection direction
	Vector3D wr = normal * 2 * won - wo;

	return wr;
}

