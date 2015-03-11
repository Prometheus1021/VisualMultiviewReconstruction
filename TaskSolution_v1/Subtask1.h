//
//  Subtask1.h
//  TaskSolution_v1
//
//  Created by Jay on 3/3/15.
//  Copyright (c) 2015 Jay. All rights reserved.
//

#ifndef TaskSolution_v1_Subtask1_h
#define TaskSolution_v1_Subtask1_h


#endif


#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
using namespace cv;


// Standard includes
#include <stdio.h>
#include <string.h>
#include <assert.h>

// OpenGL/Glut includes
#ifdef __APPLE__
#  include <GLUT/glut.h>
#else
#  include <GL/glut.h>
#endif

// Timing includes
#include <sys/time.h>

#define KEY_ESCAPE 27


CvCapture* g_Capture;
GLint g_hWindow;

// Frame size
int frame_width  = 640;
int frame_height = 480;

// current frames per second, slightly smoothed over time
double fps;
// show mirror image
bool mirror = true;
// Return current time in seconds
double current_time_in_seconds();
// Initialize glut window
GLvoid init_glut();
// Glut display callback, draws a single rectangle using video buffer as texture
GLvoid display();
// Glut reshape callback
GLvoid reshape(GLint w, GLint h);
// Glut keyboard callback
GLvoid key_press (unsigned char key, GLint x, GLint y);
// Glut idle callback, fetches next video frame
GLvoid idle();
