#include "ComplexFractal.h"
#include <cmath>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>


    ComplexFractal::ComplexFractal( ) : ThreadedGrid(200,300), x_min(-1.5), x_max(1.5), y_min(-1), y_max(1), delta_x(0.01), delta_y(0.01) {
    }

    ComplexFractal::ComplexFractal( const int& height, const int& width, const double& min_x, const double& max_x, const double& min_y, const double& max_y ) : ThreadedGrid(height,width), x_min(min_x), x_max(max_x), y_min(min_y), y_max(max_y) {
      
    }

    ComplexFractal::~ComplexFractal( ){
        //remains empty
    }

    double ComplexFractal::getMinX( ) const{
        return x_min;
    }

    double ComplexFractal::getMaxX( ) const{
        return x_max;
    }

    double ComplexFractal::getMinY( ) const{
        return y_min;
    }

    double ComplexFractal::getMaxY( ) const{
        return y_max;
    }

    void ComplexFractal::setGridSize( const int& height, const int& width ){
        if(height >= 2 && width >= 2){
            ThreadedGrid::setGridSize(height, width);
            setDeltas(calculateDeltaX(),calculateDeltaY());
        }
    }

    void ComplexFractal::setPlaneSize( const double& min_x, const double& max_x, const double& min_y, const double& max_y ){
        if(min_x >= -2.0 && min_x <= 2.0 && max_x >= -2.0 && max_x <= 2.0 && min_x != max_x &&  min_y >= -2.0 && min_y <= 2.0 && max_y >= -2.0 && max_y <= 2.0 && min_y != max_y){
            if(min_x > max_x){
                x_min = max_x;
                x_max = min_x;
                
            }else{
                x_min = min_x;
                x_max = max_x;
            }
            if(min_y > max_y){
                y_min = max_y;
                y_max = min_y;
                
            }else{
                y_min = min_y;
                y_max = max_y;
            }
            setDeltas(calculateDeltaX(),calculateDeltaY());
        }
    }
    

    double ComplexFractal::getDeltaX( ) const{
        return delta_x;
    }

    double ComplexFractal::getDeltaY( ) const{
        return delta_y;
    }

    void ComplexFractal::setDeltas( const double& x_delta, const double& y_delta ){
        if(x_delta >= 0 && y_delta >=0){
            delta_x = x_delta;
            delta_y = y_delta;
        }
    }

    double ComplexFractal::calculateDeltaY( ) const{
        return (y_max - y_min) / (getHeight() - 1);
    }

    double ComplexFractal::calculateDeltaX( ) const{
        return (x_max - x_min) / (getWidth() -1);
    }

    double ComplexFractal::calculatePlaneXFromPixelColumn( const int& column ) const{
        if(column >= 0 && column < getWidth()){
            return (x_min + column * getDeltaX());
        }
        return 0;
    }

    double ComplexFractal::calculatePlaneYFromPixelRow( const int& row ) const{
        if(row >= 0 && row < getHeight()){
            return (y_max - row * getDeltaY());
        }
        return 0;
    }

    void ComplexFractal::calculatePlaneCoordinatesFromPixelCoordinates( const int& row, const int& column, double& x, double& y ) const{
        if(column >= 0 && column < getWidth() && row >= 0 && row < getHeight()){
            y = calculatePlaneYFromPixelRow(row);
            x = calculatePlaneXFromPixelColumn(column);
        }else{
            y = 0;
            x = 0;
        }
    }

    int ComplexFractal::calculateNumber( const int& row, const int& column ) const{
        if(column >= 0 && column < getWidth() && row >= 0 && row < getHeight()){
            double y = calculatePlaneYFromPixelRow(row);
            double x = calculatePlaneXFromPixelColumn(column);
            return (std::abs(getMaxNumber() * std::sin(10*x) * std::cos(10*y)));
        }
        return -1;
    }

    