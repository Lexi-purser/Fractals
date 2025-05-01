#include "ActionData.h"
#include "NumberGrid.h"
#include "ColorTable.h"
#include "Image.h"
#include "ComplexFractal.h"
#include "JuliaSet.h"
#include "MandelbrotSet.h"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <map>
#include <ostream>

    ActionData::ActionData(std::istream& is, std::ostream& os) : IS(is), OS(os), bye(false), numb(0), color_table(16) {
        Color color1(0,255,0);
        Color color2(255,0,255);
        color_table.insertGradient(color1,color2,0,color_table.getNumberOfColors()-1);
    }
    std::istream& ActionData::getIS(){
        return IS;

    }
    std::ostream& ActionData::getOS(){
        return OS;
    }

    PPM& ActionData::getInputImage1(){
        return input_image_1;

    }

    PPM& ActionData::getInputImage2(){
        return input_image_2;
    }

    PPM& ActionData::getOutputImage(){
        return output_image;
    }

    bool ActionData::getDone() const{
        return bye;
    }

    void  ActionData::setDone(){
        bye = true;
    }

    ActionData::~ActionData(){
        if (numb != 0){
            delete numb;   
        }
    }

    NumberGrid& ActionData::getGrid(){
        return *numb; 
    }

    void ActionData::setGrid(NumberGrid *grid){
        if(numb != 0){
            delete numb;
        }
        numb = grid;
    }

    ColorTable& ActionData::getTable(){
        return color_table;
    }









