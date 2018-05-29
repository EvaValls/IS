#include "DOFcamera.h"

DOFCamera::DOFCamera(const Matrix4x4 &cameraToWorld_, const double fov_, const double focalLength_, const double aperture_,
	const Film &film_)
	: Camera(cameraToWorld_, film_),
	fov(fov_), focalLength(focalLength_), aperture(aperture_)
{ }

Vector3D DOFCamera::ndcToCameraSpace(const double u, const double v) const
{
	// In the following code, we assume a focal distance fd = 1
	double topLeftX, topLeftY;
	// Compute the image height (equal to width before taking into
	//  account the aspect ratio)
	double size = 2.0 * std::tan(fov / 2);

	// Compute the coordinates of the upper left corner at the image
	//  plane in camera coordinate (bedore taking into accoung the
	//  aspect ratio)
	topLeftX = -size * 0.5;
	topLeftY = size * 0.5;
	return Vector3D((topLeftX + u*size) * aspect,
		(topLeftY - v*size),
		1);
}

Ray DOFCamera::generateRay(const double u, const double v) const
{
	// Convert the sample to camera coordinates
	Vector3D rOrig(0, 0, 0);

	Vector3D imagePlanePoint = ndcToCameraSpace(u, v);

	Vector3D rDir = imagePlanePoint - rOrig;
	rDir = rDir.normalized();

	// Construct the ray
	size_t rayDepth = 0;
	Ray r(rOrig, rDir, rayDepth);

	// Convert the ray to world coordinates
	r = cameraToWorld.transformRay(r);

	// Make sure the ray is normalized
	r.d = r.d.normalized();

	return r;
}

Vector3D DOFCamera::computeP(Vector3D imagePlanePoint, Vector3D o) const {
	
	//e is the camera position in world coordinates
	Vector3D e = cameraToWorld.transformPoint(o); 

	
	// d is the perpendicular distance from the camera to imagePlane
	Vector3D d = ndcToCameraSpace(0.5, 0.5) - o;

	// dPrima is the distance from the camera to the pixel
	Vector3D dPrima = imagePlanePoint - o;

	//v is the unit vector from camera to the pixel
	Vector3D v = dPrima.normalized();

	//We ar following the formula : P=e+(d'/(d/(d+f)))*v
	Vector3D df = (d + focalLength);
	Vector3D 
	Vector3D P = e + dPrima**v / (d);
	return  P;


}