#include <iostream>

#define SMALL_NUM   0.00000001

float *GerDirectionnalVectorForward(float *cameravector)
{
    // We set le length of the cameravector to 1 in any cases (exept if x and y are at 0)
    float i = 1 / (sqrt(cameravector[0] * cameravector[0]) + sqrt(cameravector[2] * cameravector[2]));
    float *fixedvector = cameravector;
    fixedvector[0] = (cameravector[0] * i);
    fixedvector[1] = 0;
    fixedvector[2] = (cameravector[2] * i);

    return (fixedvector);
}


float *GerDirectionnalVectorRight(float *cameravector)
{
    float *direction = cameravector;
    // We set le length of the cameravector to 1 in any cases (exept if x and y are at 0)
    float i = 1 / (sqrt(cameravector[0] * cameravector[0]) + sqrt(cameravector[2] * cameravector[2]));
    float fixedvector[4] = {cameravector[0] * i, 0, cameravector[2] * i};

    if (cameravector[0] >= 0 && cameravector[2] >= 0) {
        direction[0] = (fixedvector[0] - 1);
        direction[1] = 0;
        direction[2] = (1 - fixedvector[2]);
    }
    else if (cameravector[0] <= 0 && cameravector[2] >= 0) {
        direction[0] = (-1 - fixedvector[0]);
        direction[1] = 0;
        direction[2] = (fixedvector[2] - 1);
    }
    else if (cameravector[0] <= 0 && cameravector[2] <= 0) {
        direction[0] = (fixedvector[0] + 1);
        direction[1] = 0;
        direction[2] = (-1 - fixedvector[2]);
    }
    else if (cameravector[0] >= 0 && cameravector[2] <= 0) {
        direction[0] = (1 - fixedvector[0]);
        direction[1] = 0;
        direction[2] = (fixedvector[2] + 1);
    }

    return (direction);
}


float *GerDirectionnalVectorBackward(float *cameravector)
{
    // We set le length of the cameravector to 1 in any cases (exept if x and y are at 0)
    float i = 1 / (sqrt(cameravector[0] * cameravector[0]) + sqrt(cameravector[2] * cameravector[2]));
    float *fixedvector = cameravector;
    fixedvector[0] = -(cameravector[0] * i);
    fixedvector[1] = 0;
    fixedvector[2] = -(cameravector[2] * i);

    return (fixedvector);
}


float *GerDirectionnalVectorLeft(float *cameravector)
{
    float *direction = cameravector;
    // We set le length of the cameravector to 1 in any cases (exept if x and y are at 0)
    float i = 1 / (sqrt(cameravector[0] * cameravector[0]) + sqrt(cameravector[2] * cameravector[2]));
    float fixedvector[4] = {cameravector[0] * i, 0, cameravector[2] * i};

    if (cameravector[0] >= 0 && cameravector[2] >= 0) {
        direction[0] = (1 - fixedvector[0]);
        direction[1] = 0;
        direction[2] = (fixedvector[2] - 1);
    }
    else if (cameravector[0] <= 0 && cameravector[2] >= 0) {
        direction[0] = (fixedvector[0] + 1);
        direction[1] = 0;
        direction[2] = (1 - fixedvector[2]);
    }
    else if (cameravector[0] <= 0 && cameravector[2] <= 0) {
        direction[0] = (-1 - fixedvector[0]);
        direction[1] = 0;
        direction[2] = (fixedvector[2] + 1);
    }
    else if (cameravector[0] >= 0 && cameravector[2] <= 0) {
        direction[0] = (fixedvector[0] - 1);
        direction[1] = 0;
        direction[2] = (-1 - fixedvector[2]);
    }

    return (direction);
}



// Calculate the directionnal vector according to where the camera looks at
//  the camera vector values cannot be lower than -1 or higher than 1 for x and y;
// For the direction, it's the second parameter "direction" that is used:
//          1 for forward
//          2 for right
//          3 for backward
//          4 for left
// Errors: return NULL
float *GetDirectionnalMovementVector(float *cameravector, int direction) {
    // Checks if the carema direction vector given is correct
    /*if ((sizeof(cameravector) + 1) != 3) {
        std::cerr << "GetDirectionnalMovementVector(): the given camera direction vector is invalid" << std::endl;
        std::cout << sizeof(cameravector) << std::endl;
        return (NULL);
    }*/
    if (cameravector[0] == 0 && cameravector[2] == 0) {
        std::cerr << "GetDirectionnalMovementVector(): in the given directional vector of the camera, x et y values equals 0" << std::endl;
        return (NULL);
    }
    if (direction < 1 || direction > 4) {
        std::cerr << "GetDirectionnalMovementVector(): the direction asked is invalid, it is " << direction << " instead of 1/2/3 or 4" << std::endl;
        return (NULL);
    }
    
    if (direction == 1)
        return (GerDirectionnalVectorForward(cameravector));
    else if (direction == 2)
        return (GerDirectionnalVectorRight(cameravector));
    else if (direction == 3)
        return (GerDirectionnalVectorBackward(cameravector));
    else
        return (GerDirectionnalVectorLeft(cameravector));
}