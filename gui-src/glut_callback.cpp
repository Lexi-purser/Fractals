#include "glut_app.h"
#include <iostream>
#include <cstdlib>
#include <cmath>

//
// GLUT callback functions
//

// This callback function gets called by the Glut
// system whenever it decides things need to be redrawn.
void display_cb(void) {
  glClear(GL_COLOR_BUFFER_BIT);
  g_app_data->display();
  glutSwapBuffers();
}

// This callback function gets called by the Glut
// system whenever a key is pressed.
void keyboard_cb(unsigned char c, int x, int y) {
  (void)x;
  (void)y;
  // just for demonstration purposes
  std::cout << "key: " << (int)c << std::endl;
  switch (c) {
  case 'q':
  case 27: // escape character means to quit the program
    exit(0);
    break;
  case 'J':
    g_app_data->createJulia();
    break;
  case 'j':
    g_app_data->createJulia2();
    break;
  case 'M':
    g_app_data->createMandelbrot();
    break;
  case 'm':
    g_app_data->createMandelbrot2();
    break;
  case 'C':
    g_app_data->createComplexFractal();
    break;
  case 'c':
    g_app_data->createComplexFractal2();
    break;
  case 'T': //changes the interaction mode to color table
    g_app_data->setInteractionMode(GlutApp::InteractionMode::IM_COLORTABLE);
    break;
  case 't': //changes the interaction mode to fractal
    g_app_data->setInteractionMode(GlutApp::InteractionMode::IM_FRACTAL);
    break;
  case '>': //increases the color table size
    g_app_data->increaseColorTableSize();
    break;
  case '.': //increases the color table size
    g_app_data->increaseColorTableSize();
    break;
  case '<': //decreases the color table size
    g_app_data->decreaseColorTableSize();
    break;
  case ',': //decreases the color table size
    g_app_data->decreaseColorTableSize();
    break;
  case 'b': //changes the fractal mode to Mandelbrot
    g_app_data->setFractalMode(GlutApp::FractalMode::M_MANDELBROT);
    g_app_data->createFractal();
    break;
  case 'n': //changes the fractal mode to Julia
    g_app_data->setFractalMode(GlutApp::FractalMode::M_JULIA);
    g_app_data->createFractal();
    break;
  case 'F': //changes the fractal mode to ComplexFractal
    g_app_data->setFractalMode(GlutApp::FractalMode::M_COMPLEX);
    g_app_data->createFractal();
    break;
  case 'z': //changes the complex plane boundaries so a smaller area of the plane is viewed
    g_app_data->zoomIn();
    g_app_data->createFractal();
    break;
  case 'Z': //changes the complex plane boundaries so that a larger area of the plane is viewed
    g_app_data->zoomOut();
    g_app_data->createFractal();
    break;
  case 'R': //changes the complex plane boundaries to [-2, 2] in both x and y dimensions
    g_app_data->resetPlane();
    g_app_data->createFractal();
    break;
  case '+': //increases the grid’s maximum number
    g_app_data->increaseMaxNumber();
    g_app_data->createFractal();
    break;
  case '=': //increases the grid’s maximum number
    g_app_data->increaseMaxNumber();
    g_app_data->createFractal();
    break;
  case '-': //decreases the grid’s maximum number
    g_app_data->decreaseMaxNumber();
    g_app_data->createFractal();
    break;
  case 'h': //decreases the grid’s maximum number
    g_app_data->toggleHSVColor();
    break;
  default:
    return; // if we don't care, return without glutPostRedisplay()
  }

  
  
  glutPostRedisplay(); // tell glut to call display() as soon as possible.
}

void special_cb(int c, int x, int y) {
  (void)x;
  (void)y;
  // just for demonstration purposes
  std::cout << "special key: " << (int)c << std::endl;
  switch(c) {
  case GLUT_KEY_UP: //increases the complex plane boundary y values
    g_app_data->moveUp();
    g_app_data->createFractal();
    break;
  case GLUT_KEY_DOWN: //decreases the complex plane boundary y values
    g_app_data->moveDown();
    g_app_data->createFractal();
    break;
  case GLUT_KEY_LEFT: //decreases the complex plane boundary x values
    g_app_data->moveLeft();
    g_app_data->createFractal();
    break;
  case GLUT_KEY_RIGHT: //increases the complex plane boundary x values
    g_app_data->moveRight();
    g_app_data->createFractal();
    break;
  default:
    return; // if we don't care, return without glutPostRedisplay()
  }
  glutPostRedisplay(); // tell glut to call display() as soon as possible.
}

// This callback function gets called by the Glut
// system whenever the window is resized by the user.
void reshape_cb(int w, int h) {
  // Reset our global variables to the new width and height.
  g_app_data->setSize(h, w);

  // all of the gl*() function calls below are part of the openGL
  // library, not our code.

  // Set the pixel resolution of the final picture (Screen coordinates).
  glViewport(0, 0, w, h);

  // Set the projection mode to 2D orthographic, and set the world coordinates:
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(0, w, 0, h);
  glMatrixMode(GL_MODELVIEW);

}

// This callback function gets called by the Glut
// system whenever any mouse button goes up or down.
void mouse_cb(int mouse_button, int state, int x, int y) {
  // translate pixel coordinates to display coordinates
  int xdisplay = x;
  int ydisplay = g_app_data->getHeight() - y;
  if (mouse_button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
    std::cout << "Left Mouse Down. @" << xdisplay << "," << ydisplay << std::endl;
    //LEFT CLICK sets the Julia parameters a and b,
   // but only if fractal mode is Mandelbrot
    g_app_data->setAB(x,y);
  }
  if (mouse_button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
    std::cout << "Left Mouse Up. @" << xdisplay << "," << ydisplay << std::endl;
  }
  if (mouse_button == GLUT_MIDDLE_BUTTON && state == GLUT_DOWN) {
    std::cout << "Middle Mouse Down. @" << xdisplay << "," << ydisplay << std::endl;
  }
  if (mouse_button == GLUT_MIDDLE_BUTTON && state == GLUT_UP) {
    std::cout << "Middle Mouse Up. @" << xdisplay << "," << ydisplay << std::endl;
  }
  glutPostRedisplay();
}
