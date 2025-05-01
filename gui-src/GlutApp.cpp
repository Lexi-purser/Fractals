#include "GlutApp.h"
#include "glut_app.h"
#include "image_menu.h"

GlutApp::GlutApp(int height, int width)
  : mHeight(height), mWidth(width), mActionData(mInputStream, mOutputStream), mMinX(-2.0), mMaxX(2.0), mMinY(-2.0), mMaxY(2.0), mA(0.38), mB(-0.45), mInteractionMode(IM_FRACTAL), mFractalMode(M_MANDELBROT), mMaxNumber(200), mColor1(62,180,137), mColor2(248, 200, 220), mNumColor(32), mHSVColor(false) {
  configureMenu(mMenuData);
  mActionData.setGrid(new ComplexFractal);
  setColorTable();
  createFractal();


  // // read1
  // mOutputStream.clear();
  // mInputStream.clear();
  // mInputStream.str("pretty-mandel-1.ppm");
  // takeAction("read1", mMenuData, mActionData);
  
  // // copy
  // mOutputStream.clear();
  // mInputStream.clear();
  // mInputStream.str("");
  // takeAction("copy", mMenuData, mActionData);
}

void GlutApp::setSize(int height, int width) {
  mHeight = height;
  mWidth = width;
}

int GlutApp::getHeight() const {
  return mHeight;
}
int GlutApp::getWidth() const {
  return mWidth;
}

void GlutApp::display() {
  if(mInteractionMode == IM_FRACTAL){
    PPM& p = mActionData.getOutputImage();
    double max = static_cast<double>(p.getMaxColorValue());
    double r, g, b;
    int row, column;
    glBegin( GL_POINTS );
    for(row = 0; row < p.getHeight(); row++) {
      for(column = 0; column < p.getWidth(); column++) {
        r = p.getChannel(row, column, 0) / max;
        g = p.getChannel(row, column, 1) / max;
        b = p.getChannel(row, column, 2) / max;
        glColor3d(r, g, b);
        glVertex2i(column, p.getHeight()-row-1);
      }
    }
    glEnd( );
  }else{
    displayColorTable();
  }
}


void GlutApp::createJulia() {
  selectJulia();
  configureGrid(200);
  juliaParameters(0.45,-0.32);
  fractalPlaneSize(-2.0,2.0,-2.0,2.0);
  fractalCalculate();
  gridApplyColorTable();
}

void GlutApp::selectJulia(){
  mOutputStream.clear();
  mOutputStream.str("");
  mInputStream.clear();
  mInputStream.str("");
  takeAction("julia", mMenuData, mActionData);
}

void GlutApp::selectMandelbrot(){
  mOutputStream.clear();
  mInputStream.clear();
  mOutputStream.str("");
  mInputStream.str("");
  takeAction("mandelbrot", mMenuData, mActionData);
}

void GlutApp::selectComplexFractal(){
  mOutputStream.clear();
  mInputStream.clear();
  mOutputStream.str("");
  mInputStream.str("");
  takeAction("complex-fractal", mMenuData, mActionData);
}

void GlutApp::configureGrid(int max){
  mOutputStream.clear();
  mInputStream.clear();
  mOutputStream.str("");
  mInputStream.str("");
  {
    std::stringstream tmp;
    tmp << mHeight << " " << mWidth << " " << max;
      mInputStream.str(tmp.str());
  }
  takeAction("grid", mMenuData, mActionData);
}

void GlutApp::juliaParameters(double a, double b){
  mOutputStream.clear();
  mInputStream.clear();
  mOutputStream.str("");
  mInputStream.str("");
  {
    std::stringstream tmp;
    tmp << a << " " << b;
    mInputStream.str(tmp.str());
  }
  takeAction("julia-parameters", mMenuData, mActionData);
}

void GlutApp::fractalPlaneSize(double x_min, double x_max, double y_min, double y_max){
  mOutputStream.clear();
  mInputStream.clear();
  mOutputStream.str("");
  mInputStream.str("");
  {
    std::stringstream tmp;
    tmp << x_min << " " << x_max << " "<< y_min << " " << y_max;
    mInputStream.str(tmp.str());
  }
  takeAction("fractal-plane-size", mMenuData, mActionData);
}

void GlutApp::fractalCalculate(){
  mOutputStream.clear();
  mInputStream.clear();
  mOutputStream.str("");
  mInputStream.str("");
  takeAction("fractal-calculate", mMenuData, mActionData);
}

void GlutApp::gridApplyColorTable(){
  mOutputStream.clear();
  mInputStream.clear();
  mOutputStream.str("");
  mInputStream.str("");
  takeAction("grid-apply-color-table", mMenuData, mActionData);
}

void GlutApp::createJulia2(){
  selectJulia();
  configureGrid(200);
  juliaParameters(0.38,-0.45);
  fractalPlaneSize(-3.0,3.0,-3.0,2.0);
  fractalCalculate();
  gridApplyColorTable();
}

void GlutApp::createMandelbrot(){
  selectMandelbrot();
  configureGrid(200);
  fractalPlaneSize(-2.0,2.0,-2.0,2.0);
  fractalCalculate();
  gridApplyColorTable();

}

void GlutApp::createMandelbrot2(){
  selectMandelbrot();
  configureGrid(180);
  fractalPlaneSize(-4.0,4.0,-4.0,4.0);
  fractalCalculate();
  gridApplyColorTable();
}

void GlutApp::createComplexFractal(){
  selectComplexFractal();
  configureGrid(200);
  fractalPlaneSize(-2.0,2.0,-2.0,2.0);
  fractalCalculate();
  gridApplyColorTable();
}

void GlutApp::createComplexFractal2(){
  selectComplexFractal();
  configureGrid(239);
  fractalPlaneSize(-3.0,3.0,-3.0,3.0);
  fractalCalculate();
  gridApplyColorTable();
}

void GlutApp::displayColorTable(){
  ColorTable& c = mActionData.getTable();
  double r, g, b;
  int row, column;
  glBegin( GL_POINTS );
  for(row = 0; row < getHeight(); row++) {
    for(column = 0; column < getWidth(); column++) {
      int i = column * c.getNumberOfColors() / getWidth();
      r = c[i].getChannel(0) / 255.0;
      g = c[i].getChannel(1) / 255.0;
      b = c[i].getChannel(2) / 255.0;
      glColor3d(r, g, b);
      glVertex2i(column, row);
    }
  }
  glEnd( );
}

void GlutApp::setInteractionMode(InteractionMode mode){
  mInteractionMode = mode;
}

void GlutApp::setColorTable(){
  mOutputStream.clear();
  mInputStream.clear();
  mOutputStream.str("");
  mInputStream.str("");
  {
    std::stringstream tmp;
    tmp << mNumColor;
      mInputStream.str(tmp.str());
  }
  takeAction("set-color-table-size", mMenuData, mActionData);
  if(mHSVColor == true){
    mOutputStream.clear();
    mInputStream.clear();
    mOutputStream.str("");
    mInputStream.str("");
    ColorTable& h = mActionData.getTable();
    double hue1;
    double sat1;
    double val1;
    mColor1.getHSV(hue1,sat1,val1);
    double hue2;
    double sat2;
    double val2;
    mColor2.getHSV(hue2,sat2,val2);
    {
      std::stringstream imp;
      imp << "0" << " " << hue1 << " " << sat1 << " " << val1 << " " << h.getNumberOfColors()-1 << " " << hue2 << " " << sat2 << " " << val2;
        mInputStream.str(imp.str());
    }
    takeAction("set-hsv-gradient", mMenuData, mActionData);
    
  }else{
    mOutputStream.clear();
    mInputStream.clear();
    mOutputStream.str("");
    mInputStream.str("");
    ColorTable& c = mActionData.getTable();
    {
      std::stringstream imp;
      imp << "0" << " " << mColor1.getRed() << " " << mColor1.getGreen() << " " << mColor1.getBlue() << " " << c.getNumberOfColors()-1 << " " << mColor2.getRed() << " " << mColor2.getGreen() << " " << mColor2.getBlue();
        mInputStream.str(imp.str());
    }
    takeAction("set-color-gradient", mMenuData, mActionData);
    }
  
}

void GlutApp::decreaseColorTableSize(){
  ColorTable& c = mActionData.getTable();
  if(c.getNumberOfColors() > 10){
    mNumColor = c.getNumberOfColors() / 1.1;
    setColorTable();
    gridApplyColorTable();
  }
}

void GlutApp::increaseColorTableSize(){
  ColorTable& c = mActionData.getTable();
  if(c.getNumberOfColors() < 1024){
    mNumColor = c.getNumberOfColors() * 1.1;
    setColorTable();
    gridApplyColorTable();
  }
}

void GlutApp::zoomIn(){
  double dx = (1.0 - 0.9)*(mMaxX - mMinX) / 2.0;
  mMinX = mMinX + dx;
  mMaxX = mMaxX - dx;
  double dy = (1.0 - 0.9)*(mMaxY - mMinY) / 2.0;
  mMinY = mMinY + dy;
  mMaxY = mMaxY - dy;
}

void GlutApp::zoomOut(){
  double dx = (1.0 - 0.9)*(mMaxX - mMinX) / 2.0;
  double dy = (1.0 - 0.9)*(mMaxY - mMinY) / 2.0;  
  double newMinX = mMinX - dx;
  double newMaxX = mMaxX + dx;
  double newMinY = mMinY - dy;
  double newMaxY = mMaxY + dy;
  if(newMaxX <= 2.0 && newMinX >= -2.0 && newMaxY <= 2.0 && newMinY >= -2.0){
    mMaxX = newMaxX;
    mMinX = newMinX;
    mMaxY = newMaxY;
    mMinY = newMinY;
  }
}

void GlutApp::moveLeft(){
  double xmax = mMaxX;
  double xmin = mMinX;
  double dx = (1.0 - 0.9)*(mMaxX-mMinX) / 2.0;
  if(mMinX - dx >= -2.0){
    mMinX = xmin - dx;
    mMaxX = xmax - dx;
  }
}

void GlutApp::moveRight(){
  double xmax = mMaxX;
  double xmin = mMinX;
  double dx = (1.0 - 0.9)*(mMaxX-mMinX) / 2.0;
  if(mMaxX + dx <= 2.0){
    mMinX = xmin + dx;
    mMaxX = xmax + dx;
  }
}

void GlutApp::moveDown(){
  double ymax = mMaxY;
  double ymin = mMinY;
  double dy = (1.0 - 0.9)*(mMaxY-mMinY) / 2.0;
  if(mMinY - dy >= -2.0){
    mMinY = ymin - dy;
    mMaxY = ymax - dy;
  }
}

void GlutApp::moveUp(){
  double dy = (1.0 - 0.9)*(mMaxY-mMinY) / 2.0;
  //double xmax = mMaxX;
  //double xmin = mMinX;
  double ymax = mMaxY;
  double ymin = mMinY;
  if(mMaxY + dy <= 2.0){
    mMinY = ymin + dy;
    mMaxY = ymax + dy;
  }
}

void GlutApp::setFractalMode(FractalMode mode){
  mFractalMode = mode;
} 

void GlutApp::increaseMaxNumber(){
  if(mMaxNumber < 2048){
    mMaxNumber = mMaxNumber * 1.1;
  }
}

void GlutApp::decreaseMaxNumber(){
  if(mMaxNumber > 11){
    mMaxNumber = mMaxNumber / 1.1;
  }
}

void GlutApp::setAB(int x, int y){
  ComplexFractal *cf = dynamic_cast<ComplexFractal *>(&mActionData.getGrid());
  if(cf != 0){
    double dx = cf->getDeltaX();
    double dy = cf->getDeltaY();
    std::cout << dx << " " << dy << std::endl;
    if(mFractalMode == M_MANDELBROT){
      mA = mMinX + x * dx;
      mB = mMinY + y * dy;
      std::cout << mA << " " << mB << std::endl;
    }
  }
}

void GlutApp::resetPlane(){
  mMaxX = 2.0;
  mMinX = -2.0;
  mMaxY = 2.0;
  mMinY = -2.0;
}

void GlutApp::createFractal(){
  if(mFractalMode == M_MANDELBROT){
    selectMandelbrot();
    configureGrid(mMaxNumber);
    fractalPlaneSize(mMinX,mMaxX,mMinY,mMaxY);
    fractalCalculate();
    gridApplyColorTable();
  }else if(mFractalMode == M_JULIA){
    selectJulia();
    juliaParameters(mA,mB);
    configureGrid(mMaxNumber);
    fractalPlaneSize(mMinX,mMaxX,mMinY,mMaxY);
    fractalCalculate();
    gridApplyColorTable();
  }else if(mFractalMode == M_COMPLEX){
    selectComplexFractal();
    configureGrid(mMaxNumber);
    fractalPlaneSize(mMinX,mMaxX,mMinY,mMaxY);
    fractalCalculate();
    gridApplyColorTable();
  }
}


void GlutApp::toggleHSVColor(){
  if(mHSVColor == true){
    mHSVColor = false;
    setColorTable();
    gridApplyColorTable();
  }else if(mHSVColor == false){
    mHSVColor = true;
    setColorTable();
    gridApplyColorTable();
  }
}
