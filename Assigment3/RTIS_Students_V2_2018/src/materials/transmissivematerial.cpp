#include "transmissivematerial.h"

TransmissiveMaterial::TransmissiveMaterial(double coef_, Vector3D ks_)
	: Material(), ks(ks_), coef(coef_)
{}

Vector3D TransmissiveMaterial::getReflectance(const Vector3D &normal, const Vector3D &wo, const Vector3D &wi) const {

	double won = dot(wo, normal);
	//ideal reflection direction
	Vector3D ref = normal;
	double win = dot(wi, ref);
	double eta2 = coef;

	float eta1 = 1;
	if (win < 0) {
		// we are outside the surface, we want cos(theta) to be positive
		win = -win;
	}
	else {
		// we are inside the surface, cos(theta) is already positive but reverse normal direction
		ref = -normal;
		// swap the refraction indices
		double aux = eta1;
		eta1 = eta2;
		eta2 = aux;
	}
	float eta = eta1 / eta2; // n_1 / n_2 
	float k = 1 - eta * eta * (1 - win * win);
	Vector3D wr =  wi.normalized()*eta + normal.normalized()*(eta * win - sqrtf(k));

	return wr;
}

