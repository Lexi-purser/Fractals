#include "NumberGrid.h"
#include "PPM.h"
#include "ColorTable.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <cmath>

    NumberGrid::NumberGrid( ){
        gH = 300;
        gW = 400;
        max = 255;
        grid.resize(gH*gW);
        unsigned int i;
        for(i = 0; i < grid.size(); i++){ //loops rows
            grid[i] = 0;
        }
    }
    

    NumberGrid::NumberGrid( const int& height, const int& width ){
        gH = height;
        gW = width;
        max = 255;
        grid.resize(gH*gW);
        unsigned int i;
        for(i = 0; i < grid.size(); i++){ //loops rows
                grid[i] = 0;
        }
    }


    NumberGrid::~NumberGrid(){
    }

    int NumberGrid::getHeight( ) const{
        return gH;
    }

    int NumberGrid::getWidth( ) const{
        return gW;
    }

    int NumberGrid::getMaxNumber( ) const{
        return max;
    }

    void NumberGrid::setGridSize( const int& height, const int& width ){
        if(height >= 2 && width >= 2){
            gH = height;
            gW = width;
            grid.resize(gH*gW);
        }
    }

    void NumberGrid::setMaxNumber( const int& number ){
        if(number >= 0){
            max = number;
        }
    }

    const std::vector<int>& NumberGrid::getNumbers( ) const{
        return grid;
    }

    int NumberGrid::index( const int& row, const int& column ) const{
        return (row * gW) + column;
    }

    bool NumberGrid::indexValid( const int& row, const int& column ) const{
        return (row < gH && row >= 0 && column >= 0 && column < gW);
    }

    bool NumberGrid::numberValid( const int& number ) const{
        return (number >= 0 && number <= max);
    }

    int NumberGrid::getNumber( const int& row, const int& column ) const{
        if(indexValid(row, column) == true){
            return grid[index(row, column)];
        }
        return -1;
    }

    void NumberGrid::setNumber( const int& row, const int& column, const int& number ){
        if (numberValid(number) == true && indexValid(row,column) == true){
            grid[index(row,column)] = number;
        }
    }

    void NumberGrid::setPPM( PPM& ppm ) const{
        ppm.setHeight(gH);
        ppm.setWidth(gW);
        ppm.setMaxColorValue(63);
        int i;
        int x;
        for(i = 0; i < gH; i++){
            for(x = 0; x < gW; x++){
                if(getNumber(i,x) == 0){
                    ppm.setPixel(i,x,0,0,0);
                }else if(getNumber(i,x) == max){
                    ppm.setPixel(i,x,63,31,31);
                }else if(getNumber(i,x) % 8 == 0){
                    ppm.setPixel(i,x,63,63,63);
                }else if(getNumber(i,x) % 8 == 1){
                    ppm.setPixel(i,x,63,31,31);
                }else if(getNumber(i,x) % 8 == 2){
                    ppm.setPixel(i,x,63,63,31);
                }else if(getNumber(i,x) % 8 == 3){
                    ppm.setPixel(i,x,31,63,31);
                }else if(getNumber(i,x) % 8 == 4){
                    ppm.setPixel(i,x,0,0,0);
                }else if(getNumber(i,x) % 8 == 5){
                    ppm.setPixel(i,x,31,63,63);
                }else if(getNumber(i,x) % 8 == 6){
                    ppm.setPixel(i,x,31,31,63);
                }else if(getNumber(i,x) % 8 == 7){
                    ppm.setPixel(i,x,63,31,63);
                }
            }
        }
    }
        
    void NumberGrid::setPPM( PPM& ppm, const ColorTable& colors) {
        if(colors.getNumberOfColors() >= 2){
            ppm.setHeight(gH);
            ppm.setWidth(gW);
            ppm.setMaxColorValue(colors.getMaxChannelValue());
            int i;
            int x;
            int num = colors.getNumberOfColors();
            for(i = 0; i < gH; i++){
                for(x = 0; x < gW; x++){
                    if(getNumber(i,x) == max){
                        ppm.setPixel(i,x,colors[num-1].getRed(),colors[num-1].getGreen(),colors[num-1].getBlue());
                    }else{
                        int index = getNumber(i,x) % num;
                        ppm.setPixel(i,x,colors[index].getRed(),colors[index].getGreen(),colors[index].getBlue());
                    }
                }
            }
        }
    }

    void NumberGrid::calculateAllNumbers(){
        int x;
        int y;
        for(y = 0; y < gH; y++){
            for(x = 0; x < gW; x++){
                setNumber(y,x,calculateNumber(y,x));
            }
        }
    }




    ManhattanNumbers::ManhattanNumbers() : NumberGrid() {

    }

    ManhattanNumbers::ManhattanNumbers(const int& height, const int& width) : NumberGrid(height,width) {

    }

    ManhattanNumbers::~ManhattanNumbers(){

    }

    int ManhattanNumbers::calculateNumber(const int& row, const int& column) const{
        int h = getHeight() / 2;
        int w = getWidth() / 2;
        return std::abs(row -h) + std::abs(column - w);
    }


