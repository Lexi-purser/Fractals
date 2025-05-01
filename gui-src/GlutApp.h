#ifndef _GLUTAPP_H_
#define _GLUTAPP_H_

#include "ActionData.h"
#include "MenuData.h"
#include <sstream>


class GlutApp {
public:
  GlutApp(int height, int width);
  void setSize(int height, int width);
  int getHeight() const;
  int getWidth() const;
  enum InteractionMode { IM_FRACTAL, IM_COLORTABLE }; 
  enum FractalMode { M_MANDELBROT, M_JULIA, M_COMPLEX }; 
  void display();

  void createJulia();

  void selectJulia();
  void selectMandelbrot();
  void selectComplexFractal();
  void configureGrid(int max);
  void juliaParameters(double a, double b);
  void fractalPlaneSize(double x_min, double x_max, double y_min, double y_max);
  void fractalCalculate();
  void gridApplyColorTable();

  void createJulia2();
  void createMandelbrot();
  void createMandelbrot2();
  void createComplexFractal();
  void createComplexFractal2();

  void displayColorTable(); 
  void setInteractionMode(InteractionMode mode); 
  void setColorTable(); 
  void decreaseColorTableSize(); 
  void increaseColorTableSize();

  void zoomIn(); 
  void zoomOut(); 

  void moveLeft(); 
  void moveRight(); 
  void moveDown(); 
  void moveUp(); 

  void setFractalMode(FractalMode mode); 
  void increaseMaxNumber(); 
  void decreaseMaxNumber(); 
  void setAB(int x, int y); 
  void resetPlane(); 
  void createFractal(); 

  void toggleHSVColor();

protected:
  int mHeight, mWidth;
  std::stringstream mInputStream;
  std::stringstream mOutputStream;
  ActionData mActionData;
  MenuData mMenuData;
  double mMinX, mMaxX, mMinY, mMaxY; //Used to call fractalPlaneSize() in createFractal(). 
  double mA, mB; //Used to call juliaParameters() in createFractal(). 
  InteractionMode mInteractionMode; //Used to choose display mode in display(). 
  FractalMode mFractalMode; //Used to choose the fractal type in createFractal(). 
  int mMaxNumber; //Used to call configureGrid() in createFractal(). 
  Color mColor1; //Used to configure the gradient in setColorTable(). 
  Color mColor2; //Used to configure the gradient in setColorTable(). 
  int mNumColor; //Used to configure the color table size in setColorTable(). 
  bool mHSVColor;
 
};

#endif /* _GLUTAPP_H_ */
/* Local Variables: */
/* mode:c++         */
/* End:             */