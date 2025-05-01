#include "ColorTable.h"
#include "PPM.h"
#include <iostream> 
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <cmath>

    Color::Color( ){
        redval = 0;
        greenval = 0;
        blueval = 0;
    }

    Color::Color( const int& red, const int& green, const int& blue ){
        redval = red;
        blueval = blue;
        greenval = green;
    }

    int Color::getRed( ) const{
        return redval;
    }

    int Color::getGreen( ) const{
        return greenval;
    }

    int Color::getBlue( ) const{
        return blueval;
    }

    int Color::getChannel( const int& channel ) const{
        if(channel == 0){
            return getRed();
        }else if(channel == 1){
            return getGreen();
        }else if(channel == 2){
            return getBlue();
        }else{
            return -1;
        }
    }

    void Color::setRed( const int& value ){
        if(value >= 0){
            redval = value;
        }
    }

    void Color::setGreen( const int& value ){
        if(value >= 0){
            greenval = value;
        }
    }

    void Color::setBlue( const int& value ){
        if(value >= 0){
            blueval = value;
        }
    }

    void Color::setChannel( const int& channel, const int& value ){
        if(value >= 0){
            if(channel == 0){
                setRed(value);
            }else if(channel == 1){
                setGreen(value);
            }else if(channel == 2){
                setBlue(value);
            }
        }
    }

    void Color::invert( const int& max_color_value ){
        int r = getRed();
        int g = getGreen();
        int b = getBlue();
        if(r <= max_color_value && g <= max_color_value && b <= max_color_value ){
            setRed(max_color_value - r);
            setGreen(max_color_value - g);
            setBlue(max_color_value - b);
        }
    }

    bool Color::operator==( const Color& rhs ) const{
        if(getBlue() == rhs.getBlue() && getRed() == rhs.getRed() && getGreen() == rhs.getGreen() ){
            return true;
        }else{
            return false;}
    }

    std::ostream& operator<<( std::ostream& os, const Color& color ){
        os << color.getRed() << ":" << color.getGreen() << ":" << color.getBlue() ;
        return os;
    }

    void Color::setFromHSV(const double& hue, const double& saturation, const double& value){
        double r;
        double g;
        double b;
        HSV_to_RGB(hue,saturation,value,r,g,b);
        setRed(r);
        setGreen(g);
        setBlue(b);
    }

    void Color::getHSV(double& hue, double& saturation, double& value) const{
        double red = getRed();
        double green = getGreen();
        double blue = getBlue();
        RGB_to_HSV( red, green, blue, hue, saturation, value);
    }



    ColorTable::ColorTable( const int& num_color ){
        colors.resize(num_color);
    }

    int ColorTable::getNumberOfColors( ) const{
        return colors.size();
    }

    void ColorTable::setNumberOfColors( const int& num_color ){
        colors.resize(num_color);
    }

    const Color& ColorTable::operator[]( const int& i ) const{
        if(i < getNumberOfColors() && i >= 0){
            return colors[i];
        }else{
            static Color ec( -1, -1, -1 );
            static Color c( -1, -1, -1 );
            c = ec;
            return c;
        }
    }

    Color& ColorTable::operator[]( const int& i ){
        if(i < getNumberOfColors() && i >= 0){
            return colors[i]; 
        }else{
            static Color ec( -1, -1, -1 );
            static Color c( -1, -1, -1 );
            c = ec;
            return c;
        }
    }

    void ColorTable::setRandomColor( const int& max_color_value, const int& position ){
        if(position < getNumberOfColors() && position >= 0 && max_color_value >= 0){
            int i;
            for(i = 0; i < 3; i++){
                if(max_color_value > 0){
                    int r = std::rand() % max_color_value - 0;
                    colors[position].setChannel(i,r);
                }else if(max_color_value == 0){
                    colors[position].setChannel(i,0);
            }
        }
    }
    }

    double ColorTable::gradientSlope(const double y1, const double y2, const double x1, const double x2) const{
        double slope = ((y2 - y1) / (x2 - x1));
        return slope;
    }

    double ColorTable::gradientValue(const double y1, const double x1, const double slope, const double x) const{
        double val = (slope*(x - x1)) + y1;
        return val;
    }

    void ColorTable::insertGradient(const Color& color1, const Color& color2, const int& position1, const int& position2){
        if(position1 < position2 && position1 >= 0 && position2 < getNumberOfColors()){
            int i;
            colors[position1].setRed(color1.getRed());
            colors[position1].setGreen(color1.getGreen());
            colors[position1].setBlue(color1.getBlue());

            colors[position2].setBlue(color2.getBlue());
            colors[position2].setRed(color2.getRed());
            colors[position2].setGreen(color2.getGreen());

            for(i = position1+1; i < position2; i++){
                double red_slope = gradientSlope((double)color2.getRed(), (double)color1.getRed(), (double)position2, (double)position1);
                double green_slope = gradientSlope((double)color2.getGreen(), (double)color1.getGreen(), (double)position2, (double)position1);
                double blue_slope = gradientSlope((double)color2.getBlue(), (double)color1.getBlue(), (double)position2, (double)position1);
                double red_grad = gradientValue((double)color1.getRed(), (double)position1, red_slope, (double)i);
                double green_grad = gradientValue((double)color1.getGreen(), (double)position1, green_slope, (double)i);
                double blue_grad = gradientValue((double)color1.getBlue(), (double)position1, blue_slope, (double)i);
                colors[i].setChannel(0,(int)red_grad);
                colors[i].setChannel(1,(int)green_grad);
                colors[i].setChannel(2,(int)blue_grad);
            }
        }
    
    }


    void ColorTable::insertHueSaturationValueGradient(const Color& color1, const Color& color2, const int& position1, const int& position2){
        if(position1 < position2 && position1 >= 0 && position2 < getNumberOfColors()){
            //sets starting HSV values for color 1
            double hue1;
            double saturation1;
            double value1;
            color1.getHSV(hue1,saturation1,value1);
            colors[position1].setFromHSV(hue1, saturation1,value1);

            //sets starting HSV values for color 2
            double hue2;
            double saturation2;
            double value2;
            color2.getHSV(hue2,saturation2,value2);
            colors[position2].setFromHSV(hue2,saturation2,value2);

            int i;
            for(i = position1+1; i < position2; i++){
                double hue_slope = gradientSlope(hue2,hue1,position2,position1);
                double sat_slope = gradientSlope(saturation2,saturation1,position2,position1);
                double val_slope = gradientSlope(value2,value1,position2,position1);
                double hue_grad = gradientValue(hue1,(double)position1,hue_slope,(double)i);
                double sat_grad = gradientValue(saturation1,(double)position1,sat_slope,(double)i);
                double val_grad = gradientValue(value1,(double)position1,val_slope,(double)i);
                colors[i].setFromHSV(hue_grad,sat_grad,val_grad);
            }
        }
    }

    int ColorTable::getMaxChannelValue( ) const{
        int i;
        int maxcolor = 0;
        for(i = 0; i < getNumberOfColors(); i++){
            if(colors[i].getRed() > maxcolor){
                maxcolor = colors[i].getRed();
            }
            if (colors[i].getGreen() > maxcolor){
                maxcolor = colors[i].getGreen();
            }
            if (colors[i].getBlue() > maxcolor){
                maxcolor = colors[i].getBlue();
            }
        }
        return maxcolor;
    }

    void HSV_to_RGB(const double& hue, const double& saturation, const double& value, double& red, double &green, double& blue){
         /* Convert Hue, Saturation, Value to Red, Green, Blue
        * Implementation of algorithm from:
        * https://en.wikipedia.org/wiki/HSL_and_HSV#HSV_to_RGB
        *
        * Inputs and ranges:
        * 0.0 <= hue <= 360.0
        * 0.0 <= saturation <= 1.0
        * 0.0 <= value <= 1.0
        *
        * Outputs and ranges:
        * 0.0 <= red <= 255.0
        * 0.0 <= green <= 255.0
        * 0.0 <= blue <= 255.0
        */
        if(hue < 0.0 || hue > 360.0 || saturation < 0.0 || saturation > 1.0 || value < 0.0 || value > 1.0) {
            red = green = blue = 0.0;
                std::cerr << "HSV_to_RGB() input parameters out of range." << std::endl
                        << " hue: " << hue  << std::endl
                        << " saturation: " << saturation << std::endl
                        << " value: " << value << std::endl;
            return;
        }

        // chroma selects the strength of the "primary" color of the current area of the wheel
        double chroma = value * saturation;
        // hue2 selects which 60-degree wedge of the color wheel we are in
        double hue2 = hue / 60.0;
        // x selects the strength of the "secondary" color of the current area of the wheel
        double x = chroma * ( 1 - std::abs( std::fmod( hue2, 2 ) - 1 ) );
        if( hue2 >= 0 && hue2 < 1 ) {
            red = chroma;
            green = x;
            blue = 0.0;
        } else if( hue2 >= 1 && hue2 < 2 ) {
            red = x;
            green = chroma;
            blue = 0.0;
        } else if( hue2 >= 2 && hue2 < 3 ) {
            red = 0.0;
            green = chroma;
            blue = x;
        } else if( hue2 >= 3 && hue2 < 4 ) {
            red = 0.0;
            green = x;
            blue = chroma;
        } else if( hue2 >= 4 && hue2 < 5 ) {
            red = x;
            green = 0.0;
            blue = chroma;
        } else if( hue2 >= 5 && hue2 <= 6 ) {
            red = chroma;
            green = 0.0;
            blue = x;
        } else {
            red = 0;
            green = 0;
            blue = 0;
        }
        // m scales all color channels to obtain the overall brightness.
        double m = value - chroma;
        red = 255.0*( red + m );
        green = 255.0*( green + m );
        blue = 255.0*( blue + m );
    }


    void RGB_to_HSV(const double& red0, const double &green0, const double& blue0, double& hue, double& saturation, double& value) {
        /* Red, Green, Blue to Convert Hue, Saturation, Value
        * Implementation of algorithm from:
        * https://en.wikipedia.org/wiki/HSL_and_HSV#From_RGB
        *
        * Inputs and ranges:
        * 0.0 <= red <= 255.0
        * 0.0 <= green <= 255.0
        * 0.0 <= blue <= 255.0
        *
        * Outputs and ranges:
        * 0.0 <= hue <= 360.0
        * 0.0 <= saturation <= 1.0
        * 0.0 <= value <= 1.0
        */
        if(red0 < 0.0 || red0 > 255.0 || green0 < 0.0 || green0 > 255.0 || blue0 < 0.0 || blue0 > 255.0) {
            hue = saturation = value = 0.0;
            std::cerr << "RGB_to_HSV() input parameters out of range." << std::endl
                    << " red: " << red0  << std::endl
                    << " green: " << green0 << std::endl
                    << " blue: " << blue0 << std::endl;
            return;
        }

        double red   = red0 / 255.0;
        double green = green0 / 255.0;
        double blue  = blue0 / 255.0;

        // x_max helps identify the primary hue
        double x_max = red;
        if(green > x_max) { x_max = green; }
        if(blue > x_max) { x_max = blue; }
        value = x_max;

        double x_min = red;
        if(green < x_min) { x_min = green; }
        if(blue < x_min) { x_min = blue; }

        double chroma = x_max - x_min;

        if(chroma == 0) {
            hue = 0;
        } else if(value == red) {
            hue = 60.0 * (0 + (green - blue)/chroma);
        } else if(value == green) {
            hue = 60.0 * (2 + (blue - red)/chroma);
        } else if(value == blue) {
            hue = 60.0 * (4 + (red - green)/chroma);
        } else {
            hue = -720.0;
        }
        if(hue < 0.0) {
            hue += 360.0;
        }

        if(value == 0.0) {
            saturation = 0.0;
        } else {
            saturation = chroma/value;
        }

    }
