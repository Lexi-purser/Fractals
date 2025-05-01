#include "image_menu.h"
#include "PPM.h"
#include "MenuData.h"
#include "NumberGrid.h"
#include "ColorTable.h"
#include "ComplexFractal.h"
#include "JuliaSet.h"
#include "MandelbrotSet.h"
#include "ThreadedGrid.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <cmath>


void diagonalQuadPattern( ActionData& action_data ) {
    int height = getInteger(action_data, "Image height? ");
    action_data.getInputImage1().setHeight(height);
    int width = getInteger(action_data, "Image width? ");
    action_data.getInputImage1().setWidth(width);
    action_data.getInputImage1().setMaxColorValue(255);
    int i;
    int x;
    for(i = 0; i < height; i++){
        for(x = 0; x < width; x++){
            action_data.getInputImage1().setChannel( i, x, 1, (( 2*i + 2*x ) % 256));//green
            if(i < (height/2)){ //red top
                action_data.getInputImage1().setChannel( i, x, 0, 0);
            }else{
                action_data.getInputImage1().setChannel( i, x, 0, 255);//red bottom
            }
            if(x < (width/2)){
                action_data.getInputImage1().setChannel( i, x, 2, 0);//blue left
            }else{
                action_data.getInputImage1().setChannel( i, x, 2, 255);//blue right
            }
        }
    }
}

void stripedDiagonalPattern( ActionData& action_data ){
    int height = getInteger(action_data, "Image height? ");
    action_data.getInputImage1().setHeight(height);
    int width = getInteger(action_data, "Image width? ");
    action_data.getInputImage1().setWidth(width);
    int mcv = (width+height)/3;
    if(mcv > 255){
        action_data.getInputImage1().setMaxColorValue(255);
    }else{
        action_data.getInputImage1().setMaxColorValue(mcv);
    }
    int i; //height
    int x; //width
    int max = action_data.getInputImage1().getMaxColorValue();
    //std::cout << max << std::endl;
    for(i = 0; i < height; i++){ //loops through the rows (height)
        for(x = 0; x < width; x++){ //loops through the columns (width)
            action_data.getInputImage1().setChannel( i, x, 1, ((i + width - x - 1)%(max+1))); //green equation
            if(i < (height/2)){ //red top
                action_data.getInputImage1().setChannel( i, x, 0, 0);
            }else if(i % 3 == 0){
                action_data.getInputImage1().setChannel( i, x, 0, 0);
            }else{
                action_data.getInputImage1().setChannel( i, x, 0, max);
            }
            if(x < i){
                action_data.getInputImage1().setChannel( i, x, 2, 0);
            }else{
                action_data.getInputImage1().setChannel( i, x, 2, max);
            }
        }
    }
}

void setSize( ActionData& action_data ){
    int height = getInteger(action_data, "Height? ");
    //std::cout << height << std::endl;
    action_data.getInputImage1().setHeight(height);
    int width = getInteger(action_data, "Width? ");
    //std::cout << width << std::endl;
    action_data.getInputImage1().setWidth(width);
}

void setMaxColorValue( ActionData& action_data ){
    int max = getInteger(action_data, "Max color value? ");
    action_data.getInputImage1().setMaxColorValue(max);
}

void setChannel( ActionData& action_data ){
    int row = getInteger(action_data, "Row? ");
    int col = getInteger(action_data, "Column? ");
    int chan = getInteger(action_data, "Channel? ");
    int value = getInteger(action_data, "Value? ");
    //std::cout <<  row << " " << col << " " << chan << " " << value << std::endl;
    action_data.getInputImage1().setChannel( row, col, chan, value);
}

void setPixel( ActionData& action_data ){
    int row = getInteger(action_data, "Row? ");
    int col = getInteger(action_data, "Column? ");
    int red = getInteger(action_data, "Red? ");
    int green = getInteger(action_data, "Green? ");
    int blue = getInteger(action_data, "Blue? ");
    action_data.getInputImage1().setPixel( row, col, red, green, blue);
}

void clearAll( ActionData& action_data ){
    int height = action_data.getInputImage1().getHeight();
    int width = action_data.getInputImage1().getWidth();
    int i;
    int x;
    for(i = 0; i < height; i++){
        for(x = 0; x < width; x++){
            action_data.getInputImage1().setPixel( i, x, 0, 0, 0);
        }
    }
}

void drawCircle(ActionData& action_data){
    action_data.getInputImage1().getHeight();
    int centr = getInteger(action_data, "Center Row? ");
    int centc = getInteger(action_data, "Center Column? ");
    int rad = getInteger(action_data, "Radius? ");
    int red = getInteger(action_data, "Red? ");
    int green = getInteger(action_data, "Green? ");
    int blue = getInteger(action_data, "Blue? ");
    int height = action_data.getInputImage1().getHeight();
    int width = action_data.getInputImage1().getWidth();
    int i;
    int x;
    for(i = 0; i < height; i++){ //loops rows
        for(x = 0; x < width; x++){ //Loops columns
            double distance = std::sqrt(((i-centr)*(i-centr))+((x-centc)*(x-centc)));
            if(distance <= rad){
                action_data.getInputImage1().setChannel( i, x, 0, red);
                action_data.getInputImage1().setChannel( i, x, 1, green);
                action_data.getInputImage1().setChannel( i, x, 2, blue);
            }
        }
    }
}

void drawBox(ActionData& action_data){
    int top = getInteger(action_data, "Top Row? ");
    int left = getInteger(action_data, "Left Column? ");
    int bottom = getInteger(action_data, "Bottom Row? ");
    int right = getInteger(action_data, "Right Column? ");
    int red = getInteger(action_data, "Red? ");
    int green = getInteger(action_data, "Green? ");
    int blue = getInteger(action_data, "Blue? ");
    int height = action_data.getInputImage1().getHeight();
    int width = action_data.getInputImage1().getWidth();
    int i;
    int x;
    for(i = 0; i < height; i++){ //loops rows
        for(x = 0; x < width; x++){ //Loops columns
            if(i >= top && i <= bottom && x >= left && x <= right){
                action_data.getInputImage1().setChannel( i, x, 0, red);
                action_data.getInputImage1().setChannel( i, x, 1, green);
                action_data.getInputImage1().setChannel( i, x, 2, blue);
            }
        }
    }
}

void configureGrid(ActionData& action_data){
    int height = getInteger(action_data, "Grid Height? ");
    int width = getInteger(action_data, "Grid Width? ");
    int max_value = getInteger(action_data, "Grid Max Value? ");
    action_data.getGrid().setGridSize(height,width);
    action_data.getGrid().setMaxNumber(max_value);
}

void setGrid(ActionData& action_data){
    int row = getInteger(action_data, "Grid Row? ");
    int column = getInteger(action_data, "Grid Column? ");
    int value = getInteger(action_data, "Grid Value? "); 
    action_data.getGrid().setNumber(row,column,value);
}

void applyGrid(ActionData& action_data){
    PPM p;
    action_data.getGrid().setPPM(p);
    action_data.getOutputImage() = p;
}

void setColorTableSize(ActionData& action_data){
    int size = getInteger(action_data, "Size? ");
    action_data.getTable().setNumberOfColors(size);
}

void setColor(ActionData& action_data){
    int spot = getInteger(action_data, "Position? ");
    int red = getInteger(action_data, "Red? ");
    int green = getInteger(action_data, "Green? ");
    int blue = getInteger(action_data, "Blue? ");
    action_data.getTable()[spot].setRed(red);
    action_data.getTable()[spot].setGreen(green);
    action_data.getTable()[spot].setBlue(blue);
}

void setRandomColor(ActionData& action_data){
    int position = getInteger(action_data,"Position? ");
    action_data.getTable().setRandomColor(255, position);
}

void setColorGradient(ActionData& action_data){
    int spot1 = getInteger(action_data, "First position? ");
    int red1 = getInteger(action_data, "First red? ");
    int green1 = getInteger(action_data, "First green? ");
    int blue1 = getInteger(action_data, "First blue? ");
    int spot2 = getInteger(action_data, "Second position? ");
    int red2 = getInteger(action_data, "Second red? ");
    int green2 = getInteger(action_data, "Second green? ");
    int blue2 = getInteger(action_data, "Second blue? ");
    Color color1(red1,green1,blue1);
    Color color2(red2,green2,blue2);
    action_data.getTable().insertGradient(color1,color2,spot1,spot2);
}

void applyGridColorTable(ActionData& action_data){
    PPM p;
    action_data.getGrid().setPPM(p,action_data.getTable());
    action_data.getOutputImage() = p;
}

void setFractalPlaneSize(ActionData& action_data){
    ComplexFractal *cf = dynamic_cast<ComplexFractal *>(&action_data.getGrid());
        if(cf != 0){
            double minx = getDouble(action_data, "Min X? ");
            double maxx = getDouble(action_data, "Max X? ");
            double miny = getDouble(action_data, "Min Y? ");
            double maxy = getDouble(action_data, "Max Y? ");
            cf->setPlaneSize(minx,maxx,miny,maxy);
    }else{
        action_data.getOS() << "Not a ComplexFractal object. Can't set plane size." << std::endl;
    }
}

void calculateFractal(ActionData& action_data){
    action_data.getGrid().calculateAllNumbers();
}

void setJuliaParameters(ActionData& action_data){
    JuliaSet *js = dynamic_cast<JuliaSet *>(&action_data.getGrid());
        if(js != 0){
            double a = getDouble(action_data, "Parameter a? ");
            double b = getDouble(action_data,"Parameter b? ");
            js->setParameters(a,b);
        }else{
            action_data.getOS() << "Not a JuliaSet object. Can't set parameters." << std::endl;
        }
}

void setMandelbrotPower(ActionData& action_data){
    MandelbrotPower *mp = dynamic_cast<MandelbrotPower *>(&action_data.getGrid());
        if(mp != 0){
            double power = getDouble(action_data, "Power? ");
            mp->setPower(power);
        }else{
            action_data.getOS() << "Not a MandelbrotPower object. Can't set parameters." << std::endl;
        }
}


void calculateFractalSingleThread(ActionData& action_data){
    action_data.getGrid().NumberGrid::calculateAllNumbers();
}

void setHueSaturationValueGradient(ActionData& action_data){
    double red1;
    double green1;
    double blue1;
    double red2;
    double green2;
    double blue2;
    int pos1 = getInteger(action_data, "First position? ");
    double hue1 = getDouble(action_data, "First hue? ");
    double sat1 = getDouble(action_data, "First saturation? ");
    double val1 = getDouble(action_data, "First value? ");
    int pos2 = getInteger(action_data, "Second position? ");
    double hue2 = getDouble(action_data, "Second hue? ");
    double sat2 = getDouble(action_data, "Second saturation? ");
    double val2 = getDouble(action_data, "Second value? ");
    HSV_to_RGB(hue1,sat1,val1,red1,green1,blue1);
    HSV_to_RGB(hue2,sat2,val2,red2,green2,blue2);
    Color color1(red1,green1,blue1);
    Color color2(red2,green2,blue2);
    action_data.getTable().insertHueSaturationValueGradient(color1,color2,pos1,pos2);
}

