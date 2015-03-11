//
//  main.cpp
//  TaskSolution_v2
//
//  Created by Jay on 3/4/15.
//  Copyright (c) 2015 Jay. All rights reserved.

#include "Subtask2.h"

void rotateCamera() {
    static double angle = 0.;
    static double radius = 1.;
    double x = radius*sin(angle);
    double z = radius*(1-cos(angle)) - radius/2;
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(x,0,z,0,0,radius/2,0,1,0);
    angle += 0.03;
}

void getDepthData(GLubyte* dest){
 
    float* fdest = (float*) dest;
    float cx = 320.227; // center of projection
    float cy = 241.984; // center of projection
    float fx = 588.517; // focal length in pixels
    float fy = 584.730; // focal length in pixels
    
    glMatrixMode(GL_PROJECTION);
    
    //glMatrixMode(GL_MODELVIEW);

    // rendering stuff...
    
    for (int num = 0; num<cam_Num; num++)
    {
        glPushMatrix();
        glLoadMatrixf(PhysicsTransformMatrix[num]);
        
        Mat depthImage = imread(root + depthFile[num],  CV_LOAD_IMAGE_UNCHANGED); //frame-1.depth.png
        
        // Check for invalid input
        if(! depthImage.data )
        {
            cout <<  "Could not open or find the Depth image" << std::endl ;
        }

        for (int v=0; v<height; v++)
        {
            for (int u=0; u<width; u++)
            {
                float z = 1.0 / (depthImage.at<uint16_t>(v,u)*-0.0030711016 + 3.3309495161);
                *fdest++ = depth_data[num][v][u][0] = (u - cx) * z / fx;
                *fdest++ = depth_data[num][v][u][1] = (v - cy) * z / fy;
                *fdest++ = depth_data[num][v][u][2] = z;
            }
        }
        glPopMatrix();

    }
}

void getRGBData(GLubyte* dest){
    
    float cx = 318.406; // center of projection
    float cy = 263.468; // center of projection
    float fx = 520.971; // focal length in pixels
    float fy = 517.855; // focal length in pixels
    
    //getRgbData(ptr);
    float* fdest = (float*) dest;

    for (int num = 0; num<cam_Num; num++)
    {
        Mat rgbImage = imread(root + rgbFile[num],CV_LOAD_IMAGE_UNCHANGED);//CV_LOAD_IMAGE_COLOR);
        
        if(! rgbImage.data ) // Check for invalid input
        {
            cout <<  "Could not open or find the RGB image" << std::endl;
        }

        for (int v = 0; v < height; ++v)
        {
            for (int u = 0; u < width; ++u)
            {
//                The RGB image from dataset is calibrated and mapped to Depth map.
                *(fdest++) = rgbImage.at<Vec3b>(v,u)[0]/255.0f;
                *(fdest++) = rgbImage.at<Vec3b>(v,u)[1]/255.0f;
                *(fdest++) = rgbImage.at<Vec3b>(v,u)[2]/255.0f;
                
//                If the RGB dataset is uncalibrated, we can use code below. And comment out previous 3 lines.
//                                float tmp[3] = {depth_data[num][v][u][0], depth_data[num][v][u][1], depth_data[num][v][u][2]};
//                                depth_data[num][v][u][0] = 0.999*tmp[0]+(0.00126)*tmp[1]+(-0.01748)*tmp[2]+0.0199;
//                                depth_data[num][v][u][1] = -0.001478*tmp[0]+0.999*tmp[1]-0.01225*tmp[2]-0.00074;
//                                depth_data[num][v][u][2] = 0.01747*tmp[0]+(0.01227)*tmp[1]+0.9999*tmp[2]-0.0109;
//                
//                                float x_rgbcam = fx*depth_data[num][v][u][0]/depth_data[num][v][u][2]+cx;
//                                float y_rgbcam = fy*depth_data[num][v][u][1]/depth_data[num][v][u][2]+cy;
//                
//                                int px_rgbcam = cvRound(x_rgbcam);
//                                int py_rgbcam = cvRound(y_rgbcam);
//                
//                                if(px_rgbcam<480 && py_rgbcam<640){
//                                    *(fdest++) = rgbImage.at<Vec3b>(px_rgbcam,py_rgbcam)[0]/255.0f;
//                                    *(fdest++) = rgbImage.at<Vec3b>(px_rgbcam,py_rgbcam)[1]/255.0f;
//                                    *(fdest++) = rgbImage.at<Vec3b>(px_rgbcam,py_rgbcam)[2]/255.0f;
//                                }
//                                else{
//                                    *(fdest++) = 0;
//                                    *(fdest++) = 0;
//                                    *(fdest++) = 0;
//                                }
                
            }
        }
    }
}
void getDepthCameraData() {
    
    const int dataSize = width*height*3*4*cam_Num;
    
    GLubyte* ptr;
    
    glBindBuffer(GL_ARRAY_BUFFER, vboId);
    glBufferData(GL_ARRAY_BUFFER, dataSize, 0, GL_DYNAMIC_DRAW);
    ptr = (GLubyte*) glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
    if (ptr) {
        getDepthData(ptr);
    }
    glUnmapBuffer(GL_ARRAY_BUFFER);
    
    glBindBuffer(GL_ARRAY_BUFFER, cboId);
    glBufferData(GL_ARRAY_BUFFER, dataSize, 0, GL_DYNAMIC_DRAW);
    ptr = (GLubyte*) glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
    if (ptr) {
        getRGBData(ptr);
    }
    glUnmapBuffer(GL_ARRAY_BUFFER);
}

void drawDepthCameraData() {
    getDepthCameraData();
    rotateCamera();
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);
    
    glBindBuffer(GL_ARRAY_BUFFER, vboId);
    glVertexPointer(3, GL_FLOAT, 0, NULL);
    
    glBindBuffer(GL_ARRAY_BUFFER, cboId);
    glColorPointer(3, GL_FLOAT, 0, NULL);
    
    glPointSize(1.f);
    glDrawArrays(GL_POINTS, 0, width*height*cam_Num);
    
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);
}

void draw() {
    drawDepthCameraData();
    glutSwapBuffers();
}

bool init(int argc, char* argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowSize(width,height);
    glutCreateWindow("Task Solution");
    
    glutDisplayFunc(draw);
    glutIdleFunc(draw);
    glewInit();
    return true;
}

int main(int argc, char * argv[]) {
    if (!init(argc, argv)) return 1;
    
    //Enable OpenGL Multithreading
    CGLError err;// = 0;
    CGLContextObj ctx = CGLGetCurrentContext();
    // Enable the multithreading
    err =  CGLEnable( ctx, kCGLCEMPEngine);
    if (err != kCGLNoError )
    {
        // Multithreaded execution may not be available
        // Insert your code to take appropriate action
    }
    
    // OpenGL setup
    glClearColor(0,0,0,0);
    glClearDepth(1.0f);
    
    // Set up array buffers
    glGenBuffers(1, &vboId);
    glBindBuffer(GL_ARRAY_BUFFER, vboId);
    glGenBuffers(1, &cboId);
    glBindBuffer(GL_ARRAY_BUFFER, cboId);
        
    // Camera setup
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    
    glLoadIdentity();
    gluPerspective(90, width /(GLdouble) height, 0.1, 1000);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0,0,0,0,0,1,0,1,0);
    
    // Main loop
    glutMainLoop();
    return 0;
}
//