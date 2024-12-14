#ifndef PLAYGROUND_H
#define PLAYGROUND_H

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <vector>
#include <common/texture.hpp>
#include "RenderObject.h"
#include "glfw3.h"
#include <common/objloader.hpp>

// shader id
GLuint shaderProgramm;

// vertex buffer variables
GLuint vertexBuffer[2];
GLuint VertexArrayID;

// MVP matrix
GLuint MatrixID;
glm::mat4 MVP;
GLuint MatrixIDMV;
glm::mat4 MV;

// texture
GLuint texID;
GLuint uvBuffer;
GLuint Texture;

RenderObject renderingObject;

std::vector<glm::vec3> vertices;
std::vector<glm::vec2> uvs;
std::vector<glm::vec3> normals;

float cameraZoom{35};

//global variables to handle the object pose
float var_x;
float var_y;
float var_angle;
float tilt;
bool autoRotate;
bool ispressed;


int main(); //<<< main function, called at startup
void updateAnimationLoop(); //<<< updates the animation loop
void handleInput();//<< handles keyboard input
void handleRotationToggle();//<< handle Rotation Toggle
bool initializeWindow(); //<<< initializes the window using GLFW and GLEW
void framebuffer_size_callback(GLFWwindow *, int width, int height); // callback for resizing window
bool updateMVPTransformation(); //<<< updates the MVP transform with the current pose
bool initializeVertexBuffer(); //<<< initializes the vertex buffer array and binds it OpenGL
bool cleanupVertexBuffer(); //<<< frees all recources from the vertex buffer
bool closeWindow(); //<<< Closes the OpenGL window and terminates GLFW


#endif
