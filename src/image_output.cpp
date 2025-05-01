#include "image_menu.h"
#include "ActionData.h"
#include "MenuData.h"
#include "PPM.h"
#include "Image.h"
#include <fstream>
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

void drawAsciiImage(ActionData& action_data) {
    int height = action_data.getOutputImage().getHeight();
    int width = action_data.getOutputImage().getWidth();
    int i;
    int x;
    //std::cout << p.getWidth() << " " << p.getHeight() << std::endl;
    for(i = 0; i < height; i++){
        for(x = 0; x < width; x++){
            double red = action_data.getOutputImage().getChannel(i, x, 0);
            double green = action_data.getOutputImage().getChannel(i, x, 1);
            double blue = action_data.getOutputImage().getChannel(i, x, 2);
            //std::cout << i << " " << x << std::endl;
            //std::cout << red <<" " << green << "" << blue << std::endl;
            double asum = ((red + green + blue)/765.0);
            if(asum >= 1.0) {
                action_data.getOS() << "@";
            } else if(asum >= 0.9) {
                action_data.getOS() << "#";
            } else if(asum >= 0.8) {
                action_data.getOS() << "%";
            } else if(asum >= 0.7) {
                action_data.getOS() << "*";
            } else if(asum >= 0.6) {
                action_data.getOS() << "|";
            } else if(asum >= 0.5) {
                action_data.getOS() << "+";
            } else if(asum >= 0.4) {
                action_data.getOS() << ";";
            } else if(asum >= 0.3) {
                action_data.getOS() << "~";
            } else if(asum >= 0.2) {
                action_data.getOS() << "-";
            } else if(asum >= 0.1) {
                action_data.getOS() << ".";
            } else if(asum >= 0.0) {
                action_data.getOS() << " ";
            } else {
                action_data.getOS() << "f";
            }
        }
        action_data.getOS() << "\n";
    }   
}

void writeUserImage( ActionData& action_data ){
    std::string filename = getString(action_data, "Output filename? ");
    std::ofstream fileout(filename, std::ios::binary);
    action_data.getOutputImage().writeStream(fileout);
    fileout.close();
}

void copyImage(ActionData& action_data){
    action_data.getOutputImage() = action_data.getInputImage1();
}

void readUserImage1( ActionData& action_data ){
    std::string filename = getString(action_data, "Input filename? ");
    std::ifstream fileout(filename);
    if(fileout.fail()){
       action_data.getOS() <<  filename << " could not be opened."; 
    }
    action_data.getInputImage1().readStream(fileout);

}

void readUserImage2( ActionData& action_data ){
    std::string filename = getString(action_data, "Input filename? ");
    std::ifstream fileout(filename);
    if(fileout.fail()){
       action_data.getOS() <<  filename << " could not be opened."; 
    }
    action_data.getInputImage2().readStream(fileout);
}



