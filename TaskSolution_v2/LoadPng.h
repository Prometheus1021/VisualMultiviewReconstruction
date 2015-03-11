//
//  LoadPng.h
//  TaskSolution_v1
//
//  Created by Jay on 3/4/15.
//  Copyright (c) 2015 Jay. All rights reserved.
//

#ifndef __TaskSolution_v1__LoadPng__
#define __TaskSolution_v1__LoadPng__

#include <stdio.h>

#endif /* defined(__TaskSolution_v1__LoadPng__) */
#include <cstdlib>
#include <cstring>
#include <GLUT/GLUT.h>
#include <libpng16/png.h>

//#include <GL/gl.h>
//#include <GL/glu.h>
//#include <png.h>
//#include <cstdio>
#include <string>

#define TEXTURE_LOAD_ERROR 0



using namespace std;



GLuint loadTexture(const string filename, int &width, int &height);