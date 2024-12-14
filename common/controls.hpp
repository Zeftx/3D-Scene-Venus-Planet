#ifndef CONTROLS_HPP
#define CONTROLS_HPP

#include "glm/detail/type_mat.hpp"

void computeMatricesFromInputs();
glm::mat4 getViewMatrix();
glm::mat4 getProjectionMatrix();

#endif