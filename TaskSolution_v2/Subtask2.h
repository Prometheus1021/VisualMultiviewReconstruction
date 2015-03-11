//
//  Subtask2.h
//  TaskSolution_v1
//
//  Created by Jay on 3/4/15.
//  Copyright (c) 2015 Jay. All rights reserved.
//

#ifndef TaskSolution_v1_Subtask2_h
#define TaskSolution_v1_Subtask2_h


#endif

#include <cmath>
#include <string>
#include <iostream>
#include <GL/glew.h>
#include <GLUT/glut.h>
#include <OpenGL/OpenGL.h>
//#include <libpng16/png.h>
#include "LoadPng.h"

#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <vector>

// Include GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

using namespace cv;

using namespace std;

const int width = 640;
const int height = 480;

int _width = 640;
int _height = 480;

// We'll be using buffer objects to store the depth camera point cloud
GLuint vboId;
GLuint cboId;

//GLubyte *textureImage;
GLuint textureImage;

int cam_Num = 4;//camera number
vector<vector<vector<vector<float>>>> depth_data(cam_Num, vector<vector<vector<float>>>(height, vector<vector<float>>(width, vector<float>(3,0))));
string root = "/Users/Jay/Development/Career/_Apple/Task/TaskSolution_v1/";
string depthFile[] = {"frame-0.depth.png","frame-1.depth.png","frame-2.depth.png","frame-3.depth.png"};
string rgbFile[] = {"frame-0.color.png","frame-1.color.png","frame-2.color.png","frame-3.color.png"};

GLfloat PhysicsTransformMatrix[4][16] = {{  0.9381,	 -0.2686,	  0.2180,	 -1.4903,
                                            0.1679,	  0.9046,	  0.3915,	 -0.4973,
                                            -0.3024,	 -0.3307,	  0.8938,	 -0.05469,
                                            0,	  0,	  0,	  1.0	},
                                        {  0.8694,	 -0.3983,	  0.2920,	 -0.5225,
                                            0.2638,	  0.8743,	  0.4071,	 -0.6765,
                                            -0.4175,	 -0.2769,	  0.8653,	  0.0892,
                                           0,0,0,1},
                                        {  0.9422,	 -0.2202,	  0.2518,	 -0.1589,
                                            0.1648,	  0.9605,	  0.2234,	 -0.9902,
                                            -0.2911,	 -0.1690,	  0.9414,	  0.6662,
                                            0,0,0,1},
                                        {  0.9797,	 -0.0979,	  0.1738,	  0.0051,
                                            0.1044,	  0.9940,	 -0.0282,	 -1.8611,
                                            -0.1700,	  0.0458,	  0.9842,	  1.8885
                                            ,0,0,0,1}
};

// OpenGL Variables
long depthToRgbMap[width*height*2];


bool init(int argc, char* argv[]);
void drawDepthCameraData();
void draw();
void rotateCamera();
void getDepthData(GLubyte* dest);
void getRGBData(GLubyte* dest);
void getDepthCameraData();
