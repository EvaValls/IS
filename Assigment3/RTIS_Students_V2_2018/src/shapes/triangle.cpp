#include "triangle.h"

Triangle::Triangle(const Vector3D &pA_, const Vector3D &pB_, const Vector3D &pC_,
	Material *mat_) :
	Shape(Matrix4x4(), mat_),
	pAWorld(pA_), pBWorld(pB_), pCWorld(pC_), nWorld(cross(pA_-pB_,pA_-pC_))
{ }

Vector3D Triangle::getNormalWorld() const
{
	return nWorld;
}

bool Triangle::rayIntersectP(const Ray &rayWorld) const
{
	// Compute the denominator of the tHit formula
	double denominator = dot(rayWorld.d, nWorld);

	// If the denominator is very close to zero, then the ray and the
	// plane are almost parallel
	if (std::abs(denominator) < Epsilon)
		return false;

	// Effectivelly compute the intersection point
	double tHit = dot((pAWorld - rayWorld.o), nWorld) / denominator;

	// Is tHit outside the bounds of the ray segment we want to test intersecion with?
	if (tHit < rayWorld.minT || tHit > rayWorld.maxT)
		return false;
	// Compute ray/plane the intersection point
	Vector3D pHit = rayWorld.o + rayWorld.d * tHit;

	//To compute if the intersection is inside the triangle we assume the formula: 
	//(vecAB x vecAPhit)*normal>0
	Vector3D vecAB = pAWorld - pBWorld;
	Vector3D vecApHit = pAWorld - pHit;
	Vector3D vecBC = pBWorld - pCWorld;
	Vector3D vecBpHit = pBWorld - pHit;
	Vector3D vecCA = pCWorld - pAWorld;
	Vector3D vecCpHit = pBWorld - pHit;

	if(dot(cross(vecAB, vecApHit), nWorld)<0)
		return false;
	if (dot(cross(vecBC, vecBpHit), nWorld)<0)
		return false;
	if (dot(cross(vecCA, vecCpHit), nWorld)<0)
		return false;

	// Arriving here, we know that the ray segment intersects the plan
	return true;
}

bool Triangle::rayIntersect(const Ray &rayWorld, Intersection &its) const
{
	// Compute the denominator of the tHit formula
 	double denominator = dot(rayWorld.d, nWorld);

	// If the denominator is very close to zero, then the ray and the
	// plane are almost parallel
	if (std::abs(denominator) < Epsilon)
		return false;

	// Effectivelly compute the intersection point
	double tHit = dot((pAWorld - rayWorld.o), nWorld) / denominator;

	// Is tHit outside the bounds of the ray segment we want to test intersecion with?
	if (tHit < rayWorld.minT || tHit > rayWorld.maxT)
		return false;
	// Compute ray/plane the intersection point
	Vector3D pHit = rayWorld.o + rayWorld.d * tHit;

	//To compute if the intersection is inside the triangle we assume the formula: 
	//(vecAB x vecAPhit)*normal>0
	Vector3D vecAB = pAWorld - pBWorld;
	Vector3D vecApHit = pAWorld - pHit;
	Vector3D vecBC = pBWorld - pCWorld;
	Vector3D vecBpHit = pBWorld - pHit;
	Vector3D vecCA = pCWorld - pAWorld;
	Vector3D vecCpHit = pCWorld - pHit;

	if (dot(cross(vecAB, vecApHit), nWorld)<0)
		return false;
	if (dot(cross(vecBC, vecBpHit), nWorld)<0)
		return false;
	if (dot(cross(vecCA, vecCpHit), nWorld)<0)
		return false;

	// Fill the intersection details
	its.itsPoint = pHit;
	its.normal = nWorld;
	its.shape = this;

	// Update the ray maxT
	rayWorld.maxT = tHit;

	return true;
}




