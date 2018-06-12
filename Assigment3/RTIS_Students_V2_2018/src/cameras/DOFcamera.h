#ifndef DOFCAMERA_H
#define DOFCAMERA_H

#include "camera.h"

class DOFCamera : public Camera
{
public:
	DOFCamera() = delete;

	DOFCamera(const Matrix4x4 &cameraToWorld_, const double fov_, const double focalLength_, const double aperture_,
		const Film &film_, double expositionTime_);

	// Member functions
	virtual Ray generateRay(const double u, const double v) const;
	virtual std::vector<Ray> generateMultipleRays(const double u, const double v, int numRays) const;
	virtual Vector3D ndcToCameraSpace(const double u, const double v) const;
	virtual Vector3D computeP(Vector3D dir, Vector3D o) const;

	/* DOF Camera Data */
	double fov; // Radians
	double focalLength; 
	double aperture; 
	Film film;
};

#endif // DOFCAMERA_H

