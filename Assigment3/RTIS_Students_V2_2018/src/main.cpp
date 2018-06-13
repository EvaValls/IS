#include <iostream>
#include <stdlib.h> /* srand, rand */
#include <vector>
#include <algorithm>

#include "core/film.h"
#include "core/matrix4x4.h"
#include "core/ray.h"
#include "core/utils.h"

#include "shapes/sphere.h"
#include "shapes/infiniteplane.h"
#include "shapes\triangle.h"

#include "cameras/ortographic.h"
#include "cameras/perspective.h"
#include "cameras\DOFcamera.h"

#include "shaders/intersectionshader.h"
#include "shaders/depthshader.h"
#include "shaders/directshader.h"
#include "shaders\globalshader.h"
#include "shaders/directshader.h"


#include "materials/material.h"
#include "materials/phongmaterial.h"
#include "materials\mirrormaterial.h"
#include "materials\transmissivematerial.h"

void buildSceneSphere(Camera* &cam, Film* &film,
                      std::vector<Shape*>* &objectsList,
                      std::vector<PointLightSource>* &lightSourceList,
					  double focalLength)
{
    /* **************************** */
    /* Declare and place the camera */
    /* **************************** */
    // By default, this gives an ID transform
    //  which means that the camera is located at (0, 0, 0)
    //  and looking at the "+z" direction
	Matrix4x4 cameraToWorld = Matrix4x4::translate(Vector3D(0, 0, -3));
	double fovDegrees = 60;
	double fovRadians = Utils::degreesToRadians(fovDegrees);
	/* ************************** */
	/* CAMERAS */
	/* ************************** */
	///CAMERAS NOW VILL HAVE EXPOSURE TIME
	double expTime = 8, expTimeDoF=3;
	cam = new PerspectiveCamera(cameraToWorld, fovRadians, *film, expTime);

	///	DoF camera whit an aperture
	double aperture = 30;
	//cam = new DOFCamera(cameraToWorld, fovRadians, focalLength, aperture, *film, expTimeDoF);


    /* ************************** */
    /* DEFINE YOUR MATERIALS HERE */
    /* ************************** */
   
	Material *redDiffuse = new PhongMaterial(Vector3D(0, 0, 0), Vector3D(0.7, 0.2, 0.3), 100);
	Material *greenDiffuse = new PhongMaterial(Vector3D(0, 0, 0), Vector3D(0.2, 0.7, 0.3), 100);
	Material *greyDiffuse = new PhongMaterial(Vector3D(0, 0, 0), Vector3D(0.8, 0.8, 0.8), 100);
	Material *blueDiffuse = new PhongMaterial(Vector3D(0, 0, 0), Vector3D(0.3, 0.2, 0.7), 100);
	Material *transmissive = new TransmissiveMaterial(1.1, Vector3D(1, 1, 1));
	Material *mirror = new MirrorMaterial(Vector3D(1, 0.9, 0.85));
	Material *red_100 = new PhongMaterial(Vector3D(0.7, 0.2, 0.3), Vector3D(0.7, 0.2, 0.3), 100);


    /* ******* */
    /* Objects */
    /* ******* */
	///SHAPES WILL HAVE A VELOCITY and A DIRECTION
    // Create a heterogeneous list of objects of type shape
    // (some might be triangles, other spheres, plans, etc)
    objectsList = new std::vector<Shape*>;
	double offset = 3.0;
    // Define and place a sphere
    Matrix4x4 sphereTransform1;
	double radius = 1;
	sphereTransform1 = Matrix4x4::translate(Vector3D(-offset + radius, -offset + radius, 3.5));
	Shape *s1 = new Sphere(1.5, sphereTransform1, greyDiffuse, 0.02, Vector3D(1, 0, 0));
	
    // Define and place a sphere
    Matrix4x4 sphereTransform2;
	sphereTransform2 = Matrix4x4::translate(Vector3D(1.0, 0.0, 0.5));
	Shape *s2 = new Sphere(1, sphereTransform2, transmissive, 0, Vector3D(0, 0, 0));

    // Define and place a sphere
    Matrix4x4 sphereTransform3;
	radius = 1;
	sphereTransform3 = Matrix4x4::translate(Vector3D(0.3, -offset + radius, 5));
	Shape *s3 = new Sphere(radius, sphereTransform3, red_100,0, Vector3D(0,0,0));

	// Store the objects in the object list
	objectsList->push_back(s1);
	objectsList->push_back(s2);
	objectsList->push_back(s3);

	//Define and place infinite plane
	Matrix4x4 idTransform;
	// Construct the Cornell Box
	
	Shape *leftPlan = new InfinitePlane(Vector3D(-offset, 0, 0), Vector3D(1, 0, 0), redDiffuse, 0, Vector3D(0, 0, 0));
	Shape *rightPlan = new InfinitePlane(Vector3D(offset, 0, 0), Vector3D(-1, 0, 0), greenDiffuse, 0, Vector3D(0, 0, 0));
	Shape *topPlan = new InfinitePlane(Vector3D(0, offset, 0), Vector3D(0, -1, 0), greyDiffuse, 0, Vector3D(0, 0, 0));
	Shape *bottomPlan = new InfinitePlane(Vector3D(0, -offset, 0), Vector3D(0, 1, 0), greyDiffuse, 0, Vector3D(0, 0, 0));
	Shape *backPlan = new InfinitePlane(Vector3D(0, 0, 3 * offset), Vector3D(0, 0, -1), blueDiffuse, 0, Vector3D(0, 0, 0));
	objectsList->push_back(leftPlan);
	objectsList->push_back(rightPlan);
	objectsList->push_back(topPlan);
	objectsList->push_back(bottomPlan);
	objectsList->push_back(backPlan);
   
	Shape *triangleOne = new Triangle(Vector3D(-1, -1,2), Vector3D(0, -1, 2), Vector3D(0.5, -2, 2),red_100, 0, Vector3D(0, 0, 0));
	objectsList->push_back(triangleOne);
    /* ****** */
    /* Lights */
    /* ****** */
    //
    // ADD YOUR LIGHT SOURCES HERE
	Vector3D lightPosition1 = Vector3D(0, offset - 1, 2 * offset);
	Vector3D lightPosition2 = Vector3D(0, offset - 1, 0);
	Vector3D lightPosition3 = Vector3D(0, offset - 1, offset);

	Vector3D intensity = Vector3D(5, 5, 5); // Radiant intensity (watts/sr)
	PointLightSource pointLS1(lightPosition1, intensity);
	PointLightSource pointLS2(lightPosition2, intensity);
	PointLightSource pointLS3(lightPosition3, intensity);
	
    // DO NOT FORGET TO STORE THE LIGHT SOURCES IN THE "lightSourceList"
	lightSourceList = new std::vector<PointLightSource>;
	lightSourceList->push_back(pointLS1);
	lightSourceList->push_back(pointLS2);
	lightSourceList->push_back(pointLS3);
}

void raytrace(Camera* &cam, Shader* &shader, Film* &film,
              std::vector<Shape*>* &objectsList, std::vector<PointLightSource>* &lightSourceList, double focalLength)
{
    unsigned int sizeBar = 40;

    size_t resX = film->getWidth();
    size_t resY = film->getHeight();
	Vector3D pixelColor;
    // Main raytracing loop
	///Loop to compute the severl images of the exposition time to compute motion blur
	double vt = 3;
	for (int t = 0; t <= vt*cam->expositionTime; t++) {
		// Out-most loop invariant: we have rendered lin lines
		for (size_t lin = 0; lin < resY; lin++)
		{
			// Show progression
			if (lin % (resY / sizeBar) == 0)
				std::cout << ".";

			// Inner loop invariant: we have rendered col columns
			for (size_t col = 0; col < resX; col++)
			{
				pixelColor = Vector3D(0, 0, 0);
				// Compute the pixel position in NDC
				double x = (double)(col + 0.5) / resX;
				double y = (double)(lin + 0.5) / resY;

				// Generate the camera ray to compute the distance
				Ray cameraRay = cam->generateRay(x, y);

				///computing distance between intersectionPoint and focalPlane
				double dist = shader->computeDistance(cameraRay, *objectsList, focalLength);
				
				///Changing dinamicaly the num of rays depending on the distance to compute the pixel color
				int numRays = (int)log2(dist + 1) * 400 + 20;

				if (dist >= 0) {  //If the ray intersects with an object

					std::vector<Ray> rays = cam->generateMultipleRays(x, y, numRays);

					for (int i = 0; i < rays.size(); i++) {
						// Compute ray color according to the used shader
						pixelColor += shader->computeColor(rays[i], *objectsList, *lightSourceList);
					}
					pixelColor /= rays.size();
					// Store the pixel color
					Vector3D currentColor = film->getPixelValue(col, lin)+pixelColor;
					
					film->setPixelValue(col, lin, currentColor);
				}
			}
		}
		///if an object has speed -> change its position acording to its speed
		for (size_t objIndex = 0; objIndex < objectsList->size(); objIndex++) {
			if (objectsList->at(objIndex)->getSpeed() != 0) {
				objectsList->at(objIndex)->changePosition();
			}
			

		}
	}
	//This is the sum of all colours and we have to divide to make the mean
	film->division(vt*cam->expositionTime+1);
}

int main()
{
    std::string separator     = "\n----------------------------------------------\n";
    std::string separatorStar = "\n**********************************************\n";
    std::cout << separator << "RTIS - Ray Tracer for \"Imatge Sintetica\"" << separator << std::endl;

    // Create an empty film
    Film *film;
    film = new Film(720, 576);


    // Declare the shader
    Vector3D bgColor(0.0, 0.0, 0.0); // Background color (for rays which do not intersect anything)
    Vector3D intersectionColor(1,0,0);
    //Shader *shader = new IntersectionShader (intersectionColor, bgColor);
	//Shader *shader = new DepthShader(Vector3D(0.4, 1, 0.4), 8, bgColor);
	Shader *shader = new DirectShader(Vector3D(0.4, 1, 0.4), 8, bgColor);
	//Shader *shader = new GlobalShader(Vector3D(0.3, 0.3,0.3),3, bgColor);

    // Declare pointers to all the variables which describe the scene
    Camera *cam;
    std::vector<Shape*> *objectsList;
    std::vector<PointLightSource> *lightSourceList;
	double focalLength = 3.5;
    // Build the scene
    buildSceneSphere(cam, film, objectsList, lightSourceList, focalLength);

    // Launch some rays!
    raytrace(cam, shader, film, objectsList, lightSourceList, focalLength);

    // Save the final result to file
    std::cout << "\n\nSaving the result to file output.bmp\n" << std::endl;
    film->save();

    std::cout << "\n\n" << std::endl;
    return 0;
}
