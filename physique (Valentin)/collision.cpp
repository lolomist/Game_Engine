#include "../include/physics.hpp"
#include <iostream>

#define SMALL_NUM   0.00000001


float dot(float *vect_A, float *vect_B) 
{ 
  
    float product = 0; 

    // Loop for calculate dot product 
    for (int i = 0; i < 3; i++)
        product = product + vect_A[i] * vect_B[i];
    return product; 
}

float norm(float *v) 
{
	return (v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
}

// cross product
float *cross(float *b, float *c) 
{
    float *result = (float*)malloc(sizeof(float) * 3);
    result[0] = b[1] * c[2] - c[1] * b[2];
    result[1] = b[2] * c[0] - c[2] * b[0];
    result[2] = b[0] * c[1] - c[0] * b[1];

	return (result);
}


bool CheckCollision_RayTriangle(float *P0, float *P1, float *P2, float *V0, float *V1, float *V2)
{
    // triangle vectors
    float *u = (float*)malloc(sizeof(float) * 3);
    float *v = (float*)malloc(sizeof(float) * 3);
    float *n = (float*)malloc(sizeof(float) * 3);
    // ray vectors      
    float dir[3];
    float w0[3];
    float w[3];
    float w1[3];
    // params to calc ray-plane intersect       
    float r, a, b;              

    // get triangle edge vectors and plane normal
    u[0] = V1[0] - V0[0];
    u[1] = V1[1] - V0[1];
    u[2] = V1[2] - V0[2];

    v[0] = V2[0] - V0[0];
    v[1] = V2[1] - V0[1];
    v[2] = V2[2] - V0[2];

    n = cross(u, v);

    // ray direction vector
    dir[0] = P1[0] - P0[0];
    dir[1] = P1[1] - P0[1];
    dir[2] = P1[2] - P0[2];


    w0[0] = P0[0] - V0[0];
    w0[1] = P0[1] - V0[1];
    w0[2] = P0[2] - V0[2];


    a = -dot(n, w0);
    b = dot(n, dir);

    std::cout << "Check parallel/coplanar" << std::endl;
    // Check if the segment of the first object is parallel to the second object's face
    // If they are parallel AND coplanar (in the same plane), then checks if they intersect each others
    if (fabs(b) < SMALL_NUM) {
        if (fabs(a) < SMALL_NUM) {

            //std::cout << "V0: " << V0[0] << " / "<< V0[1] << " / "<< V0[2] << std::endl;
            //std::cout << "P0: " << P0[0] << " / "<< P0[1] << " / "<< P0[2] << std::endl;
            w1[0] = V0[0] - P0[0];
            w1[1] = V0[1] - P0[1];
            w1[2] = V0[2] - P0[2];

            double s = dot(cross(w1, u), cross(dir, u)) / norm(cross(dir, u));
            if (s >= 0.0 && s <= 1.0)
                return (true);
        }
    }


    // check intersect point of ray with triangle plane
    r = a / b;
    if (r < 0.0 || r > 1.0)
        return (false);             // => no intersection
    else
        return (true);              // => intersection
}


// Checks if an object collides with another object
// The function needs an array of floats corresponding to the vertex/faces coordinates
// Errors: returns NULL
bool CheckCollision(float *object1, float *object2)
{
    // Checks if the arrays given are empty/incorrect
    if ((sizeof(object1) + 1) < 9 || (sizeof(object2) + 1) < 9
        || ((sizeof(object1) + 1) % 9) != 0 || ((sizeof(object2) + 1) % 9) != 0) {
        std::cerr << "CheckCollision(): one of the given arrays of coordinates contains a non-rectangular face (must contain a multiple of x9 coordinates, 3 vertex for each faces, 3 coordinates for each vertexes)" << std::endl;
        return (NULL);
    }
    if (((sizeof(object1) + 1) % 3) != 0 || (sizeof(object1) + 1) == 0) {
        std::cerr << "CheckCollision(): first array of coordinates is invalid, it's size is " << (sizeof(object1) + 1) << " instead of a multiplicator of 3 (each vertex has 3 coordinates)" << std::endl;
        return (NULL);
    }
    if (((sizeof(object2) + 1) % 3) != 0 || (sizeof(object2) + 1) == 0) {
        std::cerr << "CheckCollision(): second array of coordinates is invalid, it's size is " << (sizeof(object2) + 1) << " instead of a multiplicator of 3 (each vertex has 3 coordinates)" << std::endl;
        return (NULL);
    }
    std::cout << "Fin gestion d'erreur" << std::endl;



    for (int i = 0; i < (sizeof(object1) + 1); i = i + 9) {
        for (int x = 0; x < (sizeof(object2) + 1); x = x + 9) {
            float P0[3] = {object1[x], object1[x + 1], object1[x + 2]};
            float P1[3] = {object1[x + 3], object1[x + 4], object1[x + 5]};
            float P2[3] = {object1[x + 6], object1[x + 7], object1[x + 8]};
            float V0[3] = {object2[x], object2[x + 1], object2[x + 2]};
            float V1[3] = {object2[x + 3], object2[x + 4], object2[x + 5]};
            float V2[3] = {object2[x + 6], object2[x + 7], object2[x + 8]};

            std::cout << "Début de vérification 1" << std::endl;
            if (CheckCollision_RayTriangle(P0, P1, P2, V0, V1, V2) == true)
                return (true);
            std::cout << "Début de vérification 2" << std::endl;
            if (CheckCollision_RayTriangle(P1, P2, P0, V0, V1, V2) == true)
                return (true);
            std::cout << "Début de vérification 3" << std::endl;
            if (CheckCollision_RayTriangle(P2, P0, P1, V0, V1, V2) == true)
                return (true);
        }
    }

    // They are not colliding
    return (false);
}