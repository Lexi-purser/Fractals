#include "MandelbrotSet.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <cmath>

    MandelbrotSet::MandelbrotSet( ) : ComplexFractal( ) {

    }

    MandelbrotSet::MandelbrotSet( const int& height, const int& width, const double& min_x, const double& max_x, const double& min_y, const double& max_y ) : ComplexFractal(height,width,min_x, max_x, min_y, max_y) {
        
    }

    MandelbrotSet::~MandelbrotSet( ){
        //remains empty
    }

    void MandelbrotSet::calculateNextPoint( const double x0, const double y0, const double& a, const double& b, double& x1, double &y1 ) const{
        x1 = x0*x0 - y0*y0 + a;
        y1 = 2*x0*y0 + b;
    }

    int MandelbrotSet::calculatePlaneEscapeCount( const double& a, const double& b ) const{
        int loop = 0;
        double x;
        double y;
        calculateNextPoint(0,0,a,b,x,y);
        while(std::sqrt(((x-0)*(x-0))+((y-0)*(y-0))) <= 2.0 && loop != getMaxNumber()){
            calculateNextPoint(x,y,a,b,x,y);
            ++loop;
        }
        return loop;
    }   

    int MandelbrotSet::calculateNumber( const int& row, const int& column ) const{
        double x;
        double y;
        if(row >= 0 && row < getHeight() && column >= 0 && column < getWidth()){
            calculatePlaneCoordinatesFromPixelCoordinates(row,column,x,y);
            return calculatePlaneEscapeCount(x,y);
        }
        return -1;
    }



    MandelbrotPower::MandelbrotPower() :  MandelbrotSet(), power(2.0) {

    }

    MandelbrotPower::~MandelbrotPower(){
        //remains blank
    }

    double MandelbrotPower::getPower() const{
        return power;
    }

    void MandelbrotPower::setPower(const double& power1){
        power = power1;
    }

    void MandelbrotPower::calculateNextPoint(const double x0, const double y0, const double& a, const double& b, double& x1, double &y1) const{
        double r = std::sqrt( x0*x0 + y0*y0 );
        double theta = std::atan2( y0, x0 );
        x1 = std::pow(r ,power) * std::cos( power * theta ) + a;
        y1 = std::pow(r,power) * std::sin( power * theta ) + b;
    }
