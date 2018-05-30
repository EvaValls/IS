#include "DOFcamera.h"

DOFCamera::DOFCamera(const Matrix4x4 &cameraToWorld_, const double fov_, const double focalLength_, const double aperture_,
	const Film &film_, const int &numRays_)
	: Camera(cameraToWorld_, film_),
	fov(fov_), focalLength(focalLength_), aperture(aperture_), numRays(numRays_),film(film_)
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

Vector3D DOFCamera::computeP(Vector3D rDirNorm, Vector3D o) const {
	Vector3D P = o + rDirNorm*focalLength;
	
	return P;
}
std::vector<Ray> DOFCamera::generateMultipleRays(const double u, const double v) const {
	std::vector<Ray> rays;
	Ray cameraRay = generateRay(u, v);
	Vector3D imagePlanePoint = ndcToCameraSpace(u, v);
	Vector3D rDir = imagePlanePoint - cameraRay.o;
	Vector3D P = computeP(rDir, cameraRay.o);

	for (int i = 0; i < numRays; i++) { // shooting N random rays
		double apW = aperture / film.getWidth()*(double)(std::rand() / RAND_MAX) * 2 - 1;//generating random number
		double apH = aperture / film.getHeight()*(double)(std::rand() / RAND_MAX) * 2 - 1;
		Vector3D newRayCenter(imagePlanePoint.x + apW, imagePlanePoint.y + apH, imagePlanePoint.z);
		Vector3D newRayDir = P - newRayCenter;
		Ray newRay(newRayCenter, newRayDir.normalized());
		rays.push_back(newRay);
	}
	return rays;
}