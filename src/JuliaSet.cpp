#include "ComplexFractal.h"
#include "JuliaSet.h"
#include <cmath>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>


    JuliaSet::JuliaSet( ) : ComplexFractal(), a_par(-0.650492), b_par(-0.478235) {
        setMaxNumber(255);
    }

    JuliaSet::JuliaSet( const int& height, const int& width, const double& min_x, const double& max_x, const double& min_y, const double& max_y, const double& a, const double& b ) : ComplexFractal(height,width,min_x,max_x,min_y,max_y), a_par(a), b_par(b) {

    }

    JuliaSet::~JuliaSet( ){

    }

    double JuliaSet::getA( ) const{
        return a_par;
    }

    double JuliaSet::getB( ) const{
        return b_par;
    }

    void JuliaSet::setParameters( const double& a, const double& b ){
        if(a >= -2.0 && a <= 2.0 && b >= -2.0 && b <= 2.0){
            a_par = a;
            b_par = b;
        }
    }

    void JuliaSet::calculateNextPoint( const double x0, const double y0, double& x1, double& y1 ) const{
        x1 = x0*x0 - y0*y0 + a_par;
        y1 = 2*x0*y0 + b_par;
    }

    int JuliaSet::calculatePlaneEscapeCount( const double& x0, const double& y0 ) const{
        int loop = 0;
        double x = x0;
        double y = y0;
        while(std::sqrt(((x-0)*(x-0))+((y-0)*(y-0))) <= 2.0 && loop != getMaxNumber()){
            calculateNextPoint(x,y,x,y);
            ++loop;
        }
        return loop;
    }

    

    int JuliaSet::calculateNumber( const int& row, const int& column ) const{
        double x;
        double y;
        if(row >= 0 && row < getHeight() && column >= 0 && column < getWidth()){
            calculatePlaneCoordinatesFromPixelCoordinates(row,column,x,y);
            return calculatePlaneEscapeCount(x,y);
        }
        return -1;
    }

/*
    int i;
        double x1;
        double y1;
        double x2;
        double y2;
        x1 = x0;
        y1 = y0;
        for(i = 0; i <= getMaxNumber(); i++){
            calculateNextPoint(x1,y1,x2,y2);
            if((std::sqrt(((x2-x0)*(x2-x0))+((y2-y0)*(y2-y0)))) > 2.0){
                return i;
            }else{
                x1 = x2;
                y1 = y2;
            }
        }
        return getMaxNumber();
    }

    */