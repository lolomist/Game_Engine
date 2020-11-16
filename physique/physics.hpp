#include <iostream>
#include <stdexcept>
#include <cstdlib>
#include <vector>
#include <math.h>
#include <algorithm>

bool CheckCollision(const std::vector<float> &object1, const std::vector<float> &object2);

float dot(const std::vector<float> &vect_A, const std::vector<float> &vect_B);

std::vector<float> GetDirectionnalMovementVector(const std::vector<float> &cameravector, int direction);