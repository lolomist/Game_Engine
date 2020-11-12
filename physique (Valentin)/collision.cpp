#include "../include/physics.hpp"
#include <iostream>

#define SMALL_NUM   0.00000001


int dot(float *vect_A, float *vect_B) 
{ 
  
    int product = 0; 
  
    // Loop for calculate dot product 
    for (int i = 0; i < 3; i++) 
  
        product = product + vect_A[i] * vect_B[i]; 
    return product; 
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
        // Calculation of the vectors of all segments of the face of the triangle of the first object
        float v1[3] = {(object1[i + 3] - object1[i]), (object1[i + 3] - object1[i]), (object1[i + 3] - object1[i])};
        float v2[3] = {(object1[i + 6] - object1[i + 3]), (object1[i + 6] - object1[i + 3]), (object1[i + 6] - object1[i + 3])};
        float v3[3] = {(object1[i] - object1[i + 6]), (object1[i] - object1[i + 6]), (object1[i] - object1[i + 6])};
        for (int x = 0; x < (sizeof(object2) + 1); x = x + 9) {
            // Calculation of the normal vector of the face of the triangle of the second object
            float normalvector[3];
            normalvector[0] = (((object2[i + 3] - object2[i]) * (object2[i + 6] - object2[i])) - ((object2[i + 3] - object2[i]) * (object2[i + 6] - object2[i])));
            normalvector[1] = (((object2[i + 3] - object2[i]) * (object2[i + 6] - object2[i])) - ((object2[i + 3] - object2[i]) * (object2[i + 6] - object2[i])));
            normalvector[2] = (((object2[i + 3] - object2[i]) * (object2[i + 6] - object2[i])) - ((object2[i + 3] - object2[i]) * (object2[i + 6] - object2[i])));

            
            float D1 = dot(normalvector, v1);
            float D2 = dot(normalvector, v2);
            float D3 = dot(normalvector, v3);
            float w1[3] = {(object1[i] - object2[i]), (object1[i] - object2[i]), (object1[i] - object2[i])};
            float w2[3] = {(object1[i + 3] - object2[i]), (object1[i + 3] - object2[i]), (object1[i + 3] - object2[i])};
            float w3[3] = {(object1[i + 6] - object2[i]), (object1[i + 6] - object2[i]), (object1[i + 6] - object2[i])};
            float N1 = -dot(normalvector, w1);
            float N2 = -dot(normalvector, w2);
            float N3 = -dot(normalvector, w3);

            // Check if the segments of the first object face are parallel to the second object face
            if (fabs(D1) < SMALL_NUM) {
                if (N1 == 0)
                    return (true);
            }
            if (fabs(D2) < SMALL_NUM) {
                if (N2 == 0)
                    return (true);
            }
            if (fabs(D3) < SMALL_NUM) {
                if (N3 == 0)
                    return (true);
            }

            // They are not parallel, so we compute the intersection parameter
            float sI1 = N1 / D1;
            float sI2 = N2 / D2;
            float sI3 = N3 / D3;

            if ((sI1 >= 0  && sI1 <= 1) || (sI2 >= 0  && sI2 <= 1) || (sI3 >= 0  && sI3 <= 1))
                return (true);
        }
    }

    // They are not colliding
    return (false);
}