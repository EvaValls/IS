#ifndef MIRRORMATERIAL
#define MIRRORMATERIAL

#include "material.h"
#include "../core/vector3d.h"

class MirrorMaterial : public Material
{
public:
	MirrorMaterial() = delete;
	MirrorMaterial(Vector3D ks_);

	virtual Vector3D getReflectance(const Vector3D &n, const Vector3D &wo,
		const Vector3D &wi) const;
	virtual bool hasSpecular() const { return true; };
	virtual bool hasTransmission() const { return false; };
	virtual bool hasDiffuseOrGlossy() const { return false; };
	virtual double getIndexOfRefraction() const { return false; };

private:
	Vector3D ks;

};


#endif // MIRRORMATERIAL

