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
	//// Compute the denominator of the tHit formula
	//double denominator = dot(rayWorld.d, nWorld);

	//// If the denominator is very close to zero, then the ray and the
	//// plane are almost parallel
	//if (std::abs(denominator) < Epsilon)
	//	return false;

	//// Effectivelly compute the intersection point
	//double tHit = dot((p0World - rayWorld.o), nWorld) / denominator;

	//// Is tHit outside the bounds of the ray segment we want to test intersecion with?
	//if (tHit < rayWorld.minT || tHit > rayWorld.maxT)
	//	return false;

	//// Arriving here, we know that the ray segment intersects the plan
	//return true;
}

bool Triangle::rayIntersect(const Ray &rayWorld, Intersection &its) const
{
	//// Compute the denominator of the tHit formula
	//double denominator = dot(rayWorld.d, nWorld);

	//// Test for parallel ray/plane
	//if (std::abs(denominator) < Epsilon)
	//	return false;

	//// Effectivelly compute the intersection distance
	//double tHit = dot((p0World - rayWorld.o), nWorld) / denominator;

	//// Is tHit outside the bounds of the ray segment we want to test intersecion with?
	//if (tHit < rayWorld.minT || tHit > rayWorld.maxT)
	//	return false;

	//// Compute ray/plane the intersection point
	//Vector3D pHit = rayWorld.o + rayWorld.d * tHit;

	//// Fill the intersection details
	//its.itsPoint = pHit;
	//its.normal = nWorld;
	//its.shape = this;

	//// Update the ray maxT
	//rayWorld.maxT = tHit;

	//return true;
}




std::string Triangle::toString() const
{
	std::stringstream s;
	s << "\tInfinitePlan attributes: \n";

	s << "\t p0 (world coordinates): " << p0World << "\n";
	s << "\t normal (world coordinates): " << nWorld << "\n" << std::endl;

	return s.str();
}

