#include "image_menu.h"
#include "PPM.h"
#include "ActionData.h"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <map>
#include <ostream>

void plusEquals( ActionData& action_data ){
    action_data.getInputImage1().operator+=(action_data.getInputImage2());
}

void minusEquals( ActionData& action_data ){
    action_data.getInputImage1().operator-=(action_data.getInputImage2());
}

void timesEquals( ActionData& action_data ){
    double dvalue = getDouble(action_data, "Factor? ");
    action_data.getInputImage1().operator*=(dvalue);
}

void divideEquals( ActionData& action_data ){
    double dvalue = getDouble(action_data, "Factor? ");
    action_data.getInputImage1().operator/=(dvalue);
}

void plus( ActionData& action_data ){
    action_data.getOutputImage() = action_data.getInputImage1().operator+(action_data.getInputImage2());
}

void minus( ActionData& action_data ){
    action_data.getOutputImage() = action_data.getInputImage1().operator-(action_data.getInputImage2());
}

void times( ActionData& action_data ){
    double dvalue = getDouble(action_data, "Factor? ");
    action_data.getOutputImage() = action_data.getInputImage1().operator*(dvalue);
}

void divide( ActionData& action_data ){
    double dvalue = getDouble(action_data, "Factor? ");
    action_data.getOutputImage() = action_data.getInputImage1().operator/(dvalue);
}

void grayFromRed(ActionData& action_data){
    action_data.getInputImage1().PPM::grayFromRed(action_data.getOutputImage());

}

void grayFromGreen(ActionData& action_data){
    action_data.getInputImage1().PPM::grayFromGreen(action_data.getOutputImage());
}

void grayFromBlue(ActionData& action_data){
    action_data.getInputImage1().PPM::grayFromBlue(action_data.getOutputImage());
}

void grayFromLinearColorimetric(ActionData& action_data){
    action_data.getInputImage1().PPM::grayFromLinearColorimetric(action_data.getOutputImage());
}