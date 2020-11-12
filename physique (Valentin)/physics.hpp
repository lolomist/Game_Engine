#include <iostream>
#include <stdexcept>
#include <cstdlib>
#include <vector>
#include <math.h>
#include <algorithm>

bool CheckCollision(float *object1, float *object2);
int dot(float *vect_A, float *vect_B);
float *GetDirectionnalMovementVector(float *cameravector, int direction);