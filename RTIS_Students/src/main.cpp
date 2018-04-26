#include <iostream>
#include <stdlib.h> /* srand, rand */
#include <vector>
#include <algorithm>

#include "core/film.h"
#include "core/matrix4x4.h"
#include "core/ray.h"
#include "core/utils.h"
#include "shapes/sphere.h"
#include "cameras/ortographic.h"
#include "cameras/perspective.h"

void transformationsExercise()
{
    /* *************** */
    /* TRANSFORMATIONS */
    /* *************** */
    std::string separator     = "\n----------------------------------------------\n";
    std::string separatorStar = "\n**********************************************\n";

    std::cout << separatorStar << "Construct and visualize transforms" << separatorStar << std::endl;

    // Identity Matrix
    Matrix4x4 idMat; // By default, a matrix4x4 is initialized with the identity matrix
    std::cout << "The content of matrix idMat is: \n" << std::endl;
    std::cout << idMat << separator << std::endl;

    // Translation Matrix
    double deltaX, deltaY, deltaZ;
    deltaX = 1; deltaY = -2; deltaZ = 3;
    Vector3D delta(deltaX, deltaY, deltaZ);
    Matrix4x4 translationMat = Matrix4x4::translate(delta);
    std::cout << "The content of matrix translationMat is: \n" << std::endl;
    std::cout << translationMat << separator << std::endl;

    // Scale Matrix
    //(...)
	double Sx, Sy, Sz;
	Sx = 2; Sy = 1; Sz = -1;
	Vector3D scaling(Sx, Sy, Sz);
	Matrix4x4 scaleMatrix = Matrix4x4::scale(scaling);
    std::cout << "The content of matrix scaleMatrix is: \n" << std::endl;
    std::cout << scaleMatrix << separator << std::endl;

    // Rotate around X Matrix
    double angleInDegrees = 60;
    double thetaInRadians = Utils::degreesToRadians(angleInDegrees);
	Vector3D x_axis(1,0,0);
	Matrix4x4 rotateXMatrix = Matrix4x4::rotate(thetaInRadians,x_axis);
    std::cout << "The content of matrix rotateXMatrix is: \n" << std::endl;
    std::cout << rotateXMatrix << separator << std::endl;

    // Rotate around an arbitrary axis Matrix
	angleInDegrees = 30;
	thetaInRadians = Utils::degreesToRadians(angleInDegrees);
	Vector3D arbitrary_axis(1, 1, 1);
	Matrix4x4 rotateArtitraryAxisMatrix = Matrix4x4::rotate(thetaInRadians, arbitrary_axis);
    std::cout << "The content of matrix rotateArtitraryAxisMatrix is: \n" << std::endl;
    std::cout << rotateArtitraryAxisMatrix << separator << std::endl;

    // Transposed and Inversion
    std::cout << separatorStar << "Inverting and Transposing a Matrix" << separatorStar << std::endl;
    Matrix4x4 translationMatTransposed;
    translationMat.transpose(translationMatTransposed);
    std::cout << "The transpose of matrix \n\n" << translationMat << "\n is \n\n"
              << translationMatTransposed << separator << std::endl;

    Matrix4x4 inverseTranslationMat;
	translationMat.inverse(inverseTranslationMat);
    std::cout << "The inverse of matrix \n\n" << translationMat << "\n is \n\n" << inverseTranslationMat << std::endl;
    std::cout << "And their multiplication should thus give the identity matrix:\n\n";
	
	Matrix4x4 comprovationIdentityMatrix;
	comprovationIdentityMatrix = translationMat*inverseTranslationMat;
	std::cout << comprovationIdentityMatrix << "\n\n" << std::endl;


    // Combine here some transforms, and visualize the result
    std::cout << separatorStar << "Combine transforms and visualize the result" << separatorStar << std::endl;

    Matrix4x4 scaleTranslate = scaleMatrix*translationMat; 
    std::cout << "The content of matrix scaleTranslate is: \n" << std::endl;
    std::cout << scaleTranslate << separator << std::endl;

    Matrix4x4 translateScale = translationMat*scaleMatrix;
    std::cout << "The content of matrix translateScale is: \n" << std::endl;
    std::cout << translateScale << separator << std::endl;
}

void normalTransformExercise()
{
    std::string separator = "\n----------------------------------------------\n";

    // NOTE: points, vectors and normals are represented, in this framework, using
    //  the Vector3D class. It is up to the programmer to take care of whether the
    //  Vector3D is representing a point, a vector or a normal. For example, when
    //  applying a transform using a Matrix4x4, the programmer must choose which
    //  "applyTransform" method of the namespace Matrix4x4 should be used.

    Vector3D v(1, 1, 0);
    Vector3D n(-1.0/sqrt(2), 1.0/sqrt(2), 0);
    Matrix4x4 S = Matrix4x4::scale(Vector3D(2, 1, 1));

    std::cout << "Vector v = " << v << "\n" << std::endl;
    std::cout << "Normal n = " << n << "\n" << std::endl;
    std::cout << "Scale Matrix: \n" << std::endl;
    std::cout << S << std::endl;

	///Vector v transformat
    Vector3D vTransformed = S.transformVector(v);
    std::cout << "Vector v\' = " << vTransformed << "\n" << std::endl;

	///Vector n transformat malament
	Vector3D nWrongTransformed = S.transformVector(n);
	std::cout << "Vector n\' = " << nWrongTransformed << "\n" << std::endl;
	
	///Comprovem que el dotProduct no es 0 
	double dotOperation;
	dotOperation = dot(nWrongTransformed, vTransformed);
	std::cout << "dot( n\', v\') = " << dotOperation << "\n" << std::endl;

	///Calculem n transformada de manera correcte (n'=(St)^-1 * n)
	Vector3D nTransformed;
	Matrix4x4 sTransposed, sInversed;
	S.transpose(sTransposed);
	sTransposed.inverse(sInversed);
	nTransformed = sInversed.transformVector(n);

	std::cout << "Vector n\' = " << nTransformed << "\n" << std::endl;
	
	dotOperation = dot(nTransformed, vTransformed);
	std::cout << "dot( n\', v\') = " << dotOperation << "\n" << std::endl;

}

std::vector<double> NDC(int col, int lin, size_t resX, size_t resY) {
	double x, y;
	x = (col + 0.5) / resX;
	y = (lin + 0.5) / resY;

	std::vector<double> pndc;
	pndc.push_back(x);
	pndc.push_back(y);

	return pndc;
}

void paintingAnImageExercise()
{
    // Define the film (i.e., image) resolution
    size_t resX, resY;
    resX = 512;
    resY = 512;
    Film film(resX, resY);
	std::vector<double> pndc;


    for(unsigned int col = 0; col < resX; col++)
        {
            for(unsigned int row = 0; row < resY; row++)
            {
				pndc = NDC(col, row, resX, resY);
				Vector3D color(pndc.at(0), pndc.at(1), 0);
                film.setPixelValue(col, row, color);
            }
        }

    // Save the final result to file
    film.save();
}

void filteringAnImageExercise()
{
    // Create two instances of the film class with the same resolution
    int resX, resY;
    resX = 512;
    resY = 512;
    Film f1(resX, resY);
    Film f2(resX, resY);

    // Create the original image
    //  Draw a circle centered at centerX, centerY (in pixels, image space)
    //   and with ray r (also in pixels)
    int centerX = resX / 2;
    int centerY = resY / 2;
    int r = std::min(centerX, centerY)/2;
    for(int lin=0; lin<resX; lin++)
    {
        for(int col=0; col<resY; col++)
        {
            // Use the equation of the sphere to determine the pixel color
            if( (lin-centerX)*(lin-centerX) + (col-centerY)*(col-centerY) < r*r )
                f1.setPixelValue(col, lin, Vector3D(1, 1, 0));
        }
    }

    // Filter-related variables
    // Declare here your filter-related variables
	int const size = 5;
	int halfSize;
	halfSize = ceil(size / 2);
	int iterations = 900;
	Film *aux1,*aux2, *aux3;
	aux1 = &f1;
	aux2 = &f2;
	Vector3D filter = Vector3D();
	int avg;
	avg= 0;
	bool gaussian = false;
	double kernel[size][size];
	double sigma = 1.0;
	double s = 2*sigma*sigma;
	double sum = 0.0;

    // Implement here your image filtering algorithm

	//Generating sizeXsize gaussian kernel
	if (gaussian) {
		for (int x = -halfSize; x <= halfSize; x++) {
			for (int y = -halfSize; y <= halfSize; y++) {
				//Gaussian equation
				r = x*x + y*y;
				kernel[x + halfSize][y + halfSize] =(exp(-r / s)) / (3.1415926535897  * s);
				sum += kernel[x + halfSize][y + halfSize];
			}
		}
		for (int i = 0; i < size ; i++) {
			for (int j = 0; j < size ; j++) {
				kernel[i][j] /= sum;
			}
		}
	} else { 
		//If there is no gausian filter we will multiply by 1 (the identity)
		for (int x = -halfSize; x <= halfSize; x++) {
			for (int y = -halfSize; y <= halfSize; y++) {
	
				kernel[x + halfSize][y + halfSize] = 1;
			}
		}
	}

	int m,n;

	//Going thru the image
	for (int i = 0; i < iterations; i++) {
		///All the image
		for (int lin = 0; lin < resX; lin++) {
			for (int col = 0; col < resY; col++) {
				///The size of the blur
				m = 0;//Num of rows (x)
				for (int x = lin - halfSize; x <= lin + halfSize; x++) {
					n = 0; // num of cols(y)
					for (int y = col - halfSize; y <= col + halfSize; y++) {
							
						if (x >= 0 && y >= 0 && x<resX && y<resY) {
								

							filter += aux1->getPixelValue(x, y)*kernel[m][n];
							avg += 1;

						}
						n++;
					}
					m++;
				}
				if (!gaussian) {
					//We only normalise if it isn't gaussian because the gaussian filTeR is alreAdy normalized
					filter /= avg;
				}
				aux2->setPixelValue(lin, col, filter);
				filter -= filter;
				avg = 0;
			}
		}
		aux3 = aux1;
		aux1 = aux2;
		aux2 = aux3;

	}
	aux1->save();

}

void completeSphereClassExercise()
{
    // Make your intersection tests here
	double radius = 1;

	Vector3D delta(0, 0, 3);
	Matrix4x4 objectToWorld = Matrix4x4::translate(delta);
	Sphere sphere(radius, objectToWorld);

	std::cout << "Sphere:"<< sphere << std::endl;

	Vector3D origin(0,0,0);
	Vector3D direction1(0, 0, 1);
	Vector3D direction2(0, 1, 0);
	Ray ray1(origin, direction1);
	Ray ray2(origin, direction2);
	bool hasRoots1 = sphere.rayIntersectP(ray1);
	bool hasRoots2 = sphere.rayIntersectP(ray2);

	std::cout << "Ray 1 intersects the sphere: " << hasRoots1 << std::endl;
	std::cout << "Ray 2 intersects the sphere: " << hasRoots2 << std::endl;

}

void eqSolverExercise()
{
    EqSolver solver;
    rootValues roots;

    double A, B, C;

	A = 5.0;
	B = 6;
	C = 1;

	bool hasRoots = true;
    hasRoots = solver.rootQuadEq(A, B, C, roots);

    if(!hasRoots)
    {
        std::cout << "Equation has no real roots!" << std::endl;
    }
    else
    {
        // SHOW THE SOLUTIONS OF THE EQUATION
		std::cout << "Solution:" << roots.values[0] << ","<< roots.values[1] << std::endl;
    }
}

void raytrace()
{
    // Define the film (i.e., image) resolution
    size_t resX, resY;
    resX = 512;
    resY = 512;
    Film film(resX, resY);
	Ray ray;
	double radius = 1;
	Vector3D delta(0, 0, 3);
	Matrix4x4 objectToWorld = Matrix4x4::translate(delta);
	Sphere sphere(radius, objectToWorld);
    /* ******************* */
    /* Orthographic Camera */
    /* ******************* */
    Matrix4x4 cameraToWorld; // By default, this gives an ID transform
                             // meaning that the camera space = world space
	    OrtographicCamera camOrtho(cameraToWorld, film);

	for (int lin = 0; lin < resX; lin++) {
		for (int col = 0; col < resY; col++) {
			ray = camOrtho.generateRay((lin+0.5)/resX, (col+0.5)/resY);
			bool intersects = sphere.rayIntersectP(ray);
			if (intersects) {
				film.setPixelValue(lin, col,Vector3D(1, 0, 0));
			}
			else {
				film.setPixelValue(lin, col, Vector3D(0, 0, 0));
			}
		}
	}
    /* ******************* */
    /* Perspective Camera */
    /* ******************* */
    double fovRadians = Utils::degreesToRadians(60);
    PerspectiveCamera camPersp(cameraToWorld, fovRadians, film);

    // Save the final result to file
    film.save();
}

int main()
{
    std::string separator = "\n----------------------------------------------\n";

    std::cout << separator << "RTIS - Ray Tracer for \"Imatge Sintetica\"" << separator << std::endl;

    // ASSIGNMENT 1
    //transformationsExercise();
    //normalTransformExercise();
    //paintingAnImageExercise();
    //filteringAnImageExercise();

    // ASSIGNMENT 2
    //eqSolverExercise();
    //completeSphereClassExercise();
    raytrace();

    std::cout << "\n\n" << std::endl;
    return 0;
}
