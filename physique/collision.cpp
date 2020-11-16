#include "physics.hpp"
#include <iostream>
#include <vector>

#define SMALL_NUM   0.00000001


float dot(const std::vector<float>& vect_A, const std::vector<float>& vect_B)
{ 
  
    float product = 0; 

    // Loop for calculate dot product 
    for (int i = 0; i < 3; i++)
        product += vect_A[i] * vect_B[i];
    return product; 
}

float norm(const std::vector<float>&  v)
{
	return (v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
}

// cross product
std::vector<float> cross(const std::vector<float>& b, const std::vector<float>& c)
{
    std::vector<float> result;
    result.push_back(b[1] * c[2] - c[1] * b[2]);
    result.push_back(b[2] * c[0] - c[2] * b[0]);
    result.push_back(b[0] * c[1] - c[0] * b[1]);

	return (result);
}


bool CheckCollision_RayTriangle(const std::vector<float>& P0, const std::vector<float>& P1, const std::vector<float>& P2, const std::vector<float>& V0, const std::vector<float>& V1, const std::vector<float>& V2)
{
    std::cout << "P0: " << P0[0] << " / "<< P0[1] << " / "<< P0[2] << std::endl;
    std::cout << "P1: " << P1[0] << " / "<< P1[1] << " / "<< P1[2] << std::endl;
    std::cout << "P2: " << P2[0] << " / "<< P2[1] << " / "<< P2[2] << std::endl;
    std::cout << "V0: " << V0[0] << " / "<< V0[1] << " / "<< V0[2] << std::endl;
    std::cout << "V1: " << V1[0] << " / "<< V1[1] << " / "<< V1[2] << std::endl;
    std::cout << "V2: " << V2[0] << " / "<< V2[1] << " / "<< V2[2] << std::endl;
    // triangle vectors
    std::vector<float> u;
    std::vector<float> v;
    std::vector<float> n;
    // ray vectors
    std::vector<float> dir;
    std::vector<float> w0;
    std::vector<float> w;
    std::vector<float> w1;
    std::vector<float> w2;
    // params to calc ray-plane intersect
    float r, a, b;              

    // get triangle edge vectors and plane normal
    u.push_back(V1[0] - V0[0]);
    u.push_back(V1[1] - V0[1]);
    u.push_back(V1[2] - V0[2]);
    std::cout << "u: " << u[0] << " / "<< u[1] << " / "<< u[2] << "  -> OK" << std::endl;

    v.push_back(V2[0] - V0[0]);
    v.push_back(V2[1] - V0[1]);
    v.push_back(V2[2] - V0[2]);
    std::cout << "v: " << v[0] << " / "<< v[1] << " / "<< v[2] << "  -> OK" << std::endl;

    n = cross(u, v);
    std::cout << "n: " << n[0] << " / "<< n[1] << " / "<< n[2] << "  -> OK" << std::endl;

    // ray direction vector
    dir.push_back(P1[0] - P0[0]);
    dir.push_back(P1[1] - P0[1]);
    dir.push_back(P1[2] - P0[2]);
    std::cout << "dir: " << dir[0] << " / "<< dir[1] << " / "<< dir[2] << "  -> OK" << std::endl;


    w0.push_back(P0[0] - V0[0]);
    w0.push_back(P0[1] - V0[1]);
    w0.push_back(P0[2] - V0[2]);
    std::cout << "w0: " << w0[0] << " / "<< w0[1] << " / "<< w0[2] << "  -> OK" << std::endl;


    a = -dot(n, w0);
    b = dot(n, dir);
    std::cout << "a: " << a << "  -> OK" << std::endl;
    std::cout << "b: " << b << "  -> OK" << std::endl;

    std::cout << "Check parallel/coplanar" << std::endl;
    // Check if the segment of the first object is parallel to the second object's face
    // If they are parallel AND coplanar (in the same plane), then checks if they intersect each others
    if (fabs(b) < SMALL_NUM) {
        if (fabs(a) < SMALL_NUM) {

            w1.push_back(V0[0] - P0[0]);
            w1.push_back(V0[1] - P0[1]);
            w1.push_back(V0[2] - P0[2]);

            w2.push_back(P1[0] - V0[0]);
            w2.push_back(P1[1] - V0[1]);
            w2.push_back(P1[2] - V0[2]);

            std::cout << "w1: " << w1[0] << " / "<< w1[1] << " / "<< w1[2] << "  -> OK" << std::endl;
            double s = dot(cross(u, w0), cross(dir, w2));
            std::cout << "cross(w1, u): " << cross(w1, u)[0] << " / "<< cross(w1, u)[1] << " / "<< cross(w1, u)[2] << "  -> OK" << std::endl;
            std::cout << "cross(dir, u): " << cross(dir, u)[0] << " / "<< cross(dir, u)[1] << " / "<< cross(dir, u)[2] << "  -> OK" << std::endl;
            std::cout << "norm(cross(dir, u)): " << norm(cross(dir, u)) << std::endl;
            std::cout << "s: " << s << std::endl;
            return (s >= 0.0 && s <= 1.0);
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
bool CheckCollision(const std::vector<float>& object1, const std::vector<float>& object2)
{
    // Checks if the arrays given are empty/incorrect
    if (object1.size() < 9 || object2.size() < 9
        || (object1.size() % 9) != 0 || (object2.size() % 9) != 0) {
        std::cerr << "CheckCollision(): one of the given arrays of coordinates contains a non-rectangular face (must contain a multiple of x9 coordinates, 3 vertex for each faces, 3 coordinates for each vertexes)" << std::endl;
        return (NULL);
    }
    if ((object1.size() % 3) != 0 || object1.size() == 0) {
        std::cerr << "CheckCollision(): first array of coordinates is invalid, it's size is " << (sizeof(object1) + 1) << " instead of a multiplicator of 3 (each vertex has 3 coordinates)" << std::endl;
        return (NULL);
    }
    if ((object2.size() % 3) != 0 || object2.size() == 0) {
        std::cerr << "CheckCollision(): second array of coordinates is invalid, it's size is " << (sizeof(object2) + 1) << " instead of a multiplicator of 3 (each vertex has 3 coordinates)" << std::endl;
        return (NULL);
    }
    std::cout << "Fin gestion d'erreur" << std::endl;


    
    std::cout << "Taille du premier tableau: " << object1.size() << std::endl;
    std::cout << "Taille du deuxieme tableau: " << object2.size() << std::endl;
    for (int i = 0; i < object1.size(); i = i + 9) {
        for (int x = 0; x < object2.size(); x = x + 9) {
            std::vector<float> P0 = {object1[x], object1[x + 1], object1[x + 2]};
            std::vector<float> P1 = {object1[x + 3], object1[x + 4], object1[x + 5]};
            std::vector<float> P2 = {object1[x + 6], object1[x + 7], object1[x + 8]};
            std::vector<float> V0 = {object2[x], object2[x + 1], object2[x + 2]};
            std::vector<float> V1 = {object2[x + 3], object2[x + 4], object2[x + 5]};
            std::vector<float> V2 = {object2[x + 6], object2[x + 7], object2[x + 8]};

            std::cout << "Début de vérification 1" << std::endl;
            if (CheckCollision_RayTriangle(P0, P1, P2, V0, V1, V2))
                return (true);
            std::cout << "Début de vérification 2" << std::endl;
            if (CheckCollision_RayTriangle(P1, P2, P0, V0, V1, V2))
                return (true);
            std::cout << "Début de vérification 3" << std::endl;
            if (CheckCollision_RayTriangle(P2, P0, P1, V0, V1, V2))
                return (true);
        }
    }

    // They are not colliding
    return (false);
}