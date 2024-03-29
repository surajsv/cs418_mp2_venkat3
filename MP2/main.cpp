
//
//  main.cpp
//  MP2
//
//  Created by Suraj Venkat on 3/6/16.
//  Copyright © 2016 Suraj Venkat. All rights reserved.
//

#ifdef WIN32
#include <windows.h>
#endif

#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <math.h>
#ifdef __APPLE__
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>


#else
#include <GL/glut.h>
#include <GL/glu.h>
#include <GL/gl.h>
#endif


float sealevel;
float polysize;
float movement_speed = 0.001;
double fflag1 = 0.0;
double fflag2 = 0.0;
double fflag3 = 0.0;

int seed(float x, float y) {
    static int a = 1588635695, b = 1117695901;
    int xi = *(int *)&x;
    int yi = *(int *)&y;
    return ((xi * a) % b) - ((yi * b) % a);
}

void key1(int key, int x, int y)
{
    static GLfloat angle = 0.0;
    
    switch(key) {
        case GLUT_KEY_UP:
        {
            fflag1 = -1;
        }
            break;
        case GLUT_KEY_DOWN:
        {
            fflag1 = 1;
            
        }
            break;
        case GLUT_KEY_LEFT:
        {
            
            fflag2 = -1;
        }
            break;
        case GLUT_KEY_RIGHT:
        {
            fflag2 = 1;
        }
            break;
    }
    return;
    
    
}

void key2(int key, int x, int y)
{
    
    
    switch(key) {
        case GLUT_KEY_UP:
        {
            fflag1 = 0;
        }
            break;
        case GLUT_KEY_DOWN:
        {
            fflag1 = 0;
            
        }
            break;
        case GLUT_KEY_LEFT:
        {
            
            fflag2 = 0;
        }
            break;
        case GLUT_KEY_RIGHT:
        {
            fflag2 = 0;
        }
            break;
    }
    return;
    
    
}


void mountain(float x0, float y0, float z0, float x1, float y1, float z1, float x2, float y2, float z2, float s)
{
    float x01,y01,z01,x12,y12,z12,x20,y20,z20;
    
    if (s < polysize) {
        x01 = x1 - x0;
        y01 = y1 - y0;
        z01 = z1 - z0;
        
        x12 = x2 - x1;
        y12 = y2 - y1;
        z12 = z2 - z1;
        
        x20 = x0 - x2;
        y20 = y0 - y2;
        z20 = z0 - z2;
        
        float nx = y01*(-z20) - (-y20)*z01;
        float ny = z01*(-x20) - (-z20)*x01;
        float nz = x01*(-y20) - (-x20)*y01;
        
        float den = sqrt(nx*nx + ny*ny + nz*nz);
        
        if (den > 0.0) {
            nx /= den;
            ny /= den;
            nz /= den;
        }
        
        glNormal3f(nx,ny,nz);
        glBegin(GL_TRIANGLES);
        glVertex3f(x0,y0,z0);
        glVertex3f(x1,y1,z1);
        glVertex3f(x2,y2,z2);
        glEnd();
        
        return;
    }
    
    x01 = 0.5*(x0 + x1);
    y01 = 0.5*(y0 + y1);
    z01 = 0.5*(z0 + z1);
    
    x12 = 0.5*(x1 + x2);
    y12 = 0.5*(y1 + y2);
    z12 = 0.5*(z1 + z2);
    
    x20 = 0.5*(x2 + x0);
    y20 = 0.5*(y2 + y0);
    z20 = 0.5*(z2 + z0);
    
    s *= 0.5;
    
    srand(seed(x01,y01));
    z01 += 0.3*s*(2.0*((float)rand()/(float)RAND_MAX) - 1.0);
    srand(seed(x12,y12));
    z12 += 0.3*s*(2.0*((float)rand()/(float)RAND_MAX) - 1.0);
    srand(seed(x20,y20));
    z20 += 0.3*s*(2.0*((float)rand()/(float)RAND_MAX) - 1.0);
    
    mountain(x0,y0,z0,x01,y01,z01,x20,y20,z20,s);
    mountain(x1,y1,z1,x12,y12,z12,x01,y01,z01,s);
    mountain(x2,y2,z2,x20,y20,z20,x12,y12,z12,s);
    mountain(x01,y01,z01,x12,y12,z12,x20,y20,z20,s);
}

void init(void)
{
    GLfloat white[] = {1.0,1.0,1.0,1.0};
    GLfloat lpos[] = {0.0,1.0,0.0,0.0};
    
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    
    glLightfv(GL_LIGHT0, GL_POSITION, lpos);
    glLightfv(GL_LIGHT0, GL_AMBIENT, white);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, white);
    glLightfv(GL_LIGHT0, GL_SPECULAR, white);
    
    glClearColor (0.5, 0.5, 1.0, 0.0);
    glEnable(GL_DEPTH_TEST);
    gluLookAt (0.5, 0.1, 0.25, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);

    sealevel = 0.0;
    polysize = 0.01;
}

void display(void)
{
    static GLfloat angle = 0.0;
    
    GLfloat tanamb[] = {0.2,0.15,0.1,1.0};
    GLfloat tandiff[] = {0.4,0.3,0.2,1.0};
    
    GLfloat seaamb[] = {0.0,0.0,0.2,1.0};
    GLfloat seadiff[] = {0.0,0.0,0.8,1.0};
    GLfloat seaspec[] = {0.5,0.5,1.0,1.0};
    
    
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColor3f (1.0, 1.0, 1.0);

    
    
    GLdouble matrix[16];
    glGetDoublev(GL_MODELVIEW_MATRIX, matrix);
    glLoadIdentity();
    
    glRotatef(fflag1*0.05, 1.0, 0.0, 0.0);
    
    glRotatef(fflag2*0.07, 0.0, 0.0, 1.0);
  
    glRotatef(fflag3*0.07, 0.0, 1.0, 0.0); //yaw
    
    glTranslatef(0.0,0.0,0.1*movement_speed);
    glMultMatrixd(matrix);
    
    
    
    
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, tanamb);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, tandiff);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, tandiff);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 10.0);
    
    mountain(0.0,0.0,0.0, 1.0,0.0,0.0, 0.0,1.0,0.0, 1.0);
    mountain(1.0,1.0,0.0, 0.0,1.0,0.0, 1.0,0.0,0.0, 1.0);
    
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, seaamb);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, seadiff);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, seaspec);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 10.0);
    
    glNormal3f(0.0,0.0,1.0);
    glBegin(GL_QUADS);
    glVertex3f(0.0,0.0,sealevel);
    glVertex3f(1.0,0.0,sealevel);
    glVertex3f(1.0,1.0,sealevel);
    glVertex3f(0.0,1.0,sealevel);
    glEnd();
    
    glutSwapBuffers();
    glFlush ();
    
    angle += 1.0;
    
    glutPostRedisplay();
}

void reshape (int w, int h)
{
    glViewport (0, 0, (GLsizei) w, (GLsizei) h);
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity ();
    gluPerspective(90.0,1.0,0.01,10.0);
    glMatrixMode (GL_MODELVIEW);
}




void keyboard(unsigned char key, int x, int y)
{
    switch (key) {
        case '-':
            sealevel -= 0.01;
            break;
        case 'w':
            movement_speed*=2; //increase speed
            break;
        case 'e':
            movement_speed*=0.5; //decrease speed
            break;
            
        case '+':
        case '=':
            sealevel += 0.01;
            break;
        case 'f':
            polysize *= 0.5;
            break;
        case 'c':
            polysize *= 2.0;
            break;
        case 'u':
            fflag3 = -1;//yawing first case
            break;
        case 'i':
            fflag3 = 1;// yawing second case
            break;
        case 27:
            exit(0);
            break;
    }
}

/*

To turn off Yaw
 
*/
void key3(unsigned char key,int x,int y)
{
    
    switch(key)
    {
            case 'u':
            fflag3 = 0;
            break;
            
            case 'i':
            fflag3 = 0;
            break;
            
    }
    
    
}


int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize (500, 500); 
    glutInitWindowPosition (100, 100);
    glutCreateWindow (argv[0]);
    init ();
    glutDisplayFunc(display);
    glutSpecialFunc(key1);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutKeyboardUpFunc(key3);
    glutSpecialUpFunc(key2);
    glutMainLoop();
    return 0;
}