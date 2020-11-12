#include "../include/physics.hpp"

int main() {
    /*float face1[10] = {0, 5, 0, 8, 0, 0, 0, 0, 0};
    float face2[10] = {6, 8, 3, 6, 8, -2, 6, -4, -2};

    std::cout << "Début du test" << std::endl;
    bool test = CheckCollision(face1, face2);
    if (test == true)
        std::cout << "Ils sont en collision" << std::endl;
    if (test == false)
        std::cout << "Ils ne sont pas en collision" << std::endl;*/

    float camera[4] = {1, 0, 1};

    float *result = GetDirectionnalMovementVector(camera, 4);

    if (result != NULL) {
        std::cout << result[0] << std::endl;
        std::cout << result[1] << std::endl;
        std::cout << result[2] << std::endl;
    }
    else
        std::cout << "Error" << std::endl;
    

    return (0);
}