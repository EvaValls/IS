#ifndef TRANSMISSIVEMATERIAL
#define TRANSMISSIVEMATERIAL

#include "material.h"
#include "../core/utils.h"
#include "../core/vector3d.h"

class TransmissiveMaterial : public Material
{
public:
	TransmissiveMaterial() = delete;
	TransmissiveMaterial(double coef,Vector3D ks_);

	virtual Vector3D getReflectance(const Vector3D &n, const Vector3D &wo,
		const Vector3D &wi) const;
	virtual bool hasSpecular() const { return false; };
	virtual bool hasTransmission() const { return true; };
	virtual bool hasDiffuseOrGlossy() const { return false; };
	virtual double getIndexOfRefraction() const;

private:
	Vector3D ks;
	double coef;
};


#endif // TRANSMISSIVEMATERIAL

