#ifndef PHONGMATERIAL
#define PHONGMATERIAL

#include "material.h"
#include "../core/vector3d.h"

class PhongMaterial: public Material
{
public:
	PhongMaterial() = delete;
	PhongMaterial(Vector3D ks_, Vector3D kd_, double n_);
	
	virtual Vector3D getReflectance(const Vector3D &n, const Vector3D &wo,
		const Vector3D &wi) const ;
	virtual bool hasSpecular() const { return false; };
	virtual bool hasTransmission() const { return false; };
	virtual bool hasDiffuseOrGlossy() const { return false; };
	virtual double getIndexOfRefraction() const { return false; };

private:
	Vector3D ks;
	Vector3D kd;
	double n;
};


#endif // PHONGMATERIAL
