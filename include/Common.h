#pragma once
#include <PCH.h>

const int WIDTH = 800;
const int HEIGHT = 600;

extern float fov;
extern float deltaTime;	// time between current frame and last frame
extern float lastFrame;
extern Camera camera;

void framebufferSizeCallback(GLFWwindow*, int, int);

void processInput(GLFWwindow* window);

void mouseEvent(GLFWwindow* window, double xpos, double ypos);
void scollEvent(GLFWwindow* window, double xoffset, double yoffset);
unsigned int loadTexture(char const* path);