#include "Image.h"
#include "PPM.h"
#include "ColorTable.h"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <map>
#include <ostream>

    PPM::PPM() {
        Image();
        mC = 1;

    }

    PPM::PPM(const int& height, const int& width ) : Image(height,width), mC(1) {

    }

    int PPM::getMaxColorValue( ) const{
        return mC;
    }

    bool PPM::valueValid( const int& value ) const{
        if(value >= 0 && value <= getMaxColorValue()){
            return true;
        }else{
            return false;
        }
    }

    void PPM::setMaxColorValue( const int& max_color_value ){
        if(max_color_value >= 1 &&  max_color_value <= 255){
            mC = max_color_value;
        }
    }

    void PPM::setChannel( const int& row, const int& column, const int& channel, const int& value ){
        if(valueValid(value) == true){
            Image::setChannel( row, column, channel, value);
        }
    }

    void PPM::setPixel( const int& row, const int& column, const int& red, const int& green, const int& blue ){
        PPM::setChannel(row,column, 0, red);
        PPM::setChannel(row,column, 1, green);
        PPM::setChannel(row,column, 2, blue);
    }

    void PPM::writeStream(std::ostream& os) const{ 
        os << "P6" << " " << mW << " " << mH << " " << mC << "\n";
        int height = getHeight();
        int width = getWidth();
        int i;
        int x;
        int y;
        unsigned char chan;
        for(i = 0; i < height; i++){
            for(x = 0; x < width; x++){
                for(y = 0; y < 3; y++){
                    chan = getChannel(i, x, y);
                    os.write((char *) &chan, sizeof(chan));
                }
            }
        }
        //os << "\n";
        return;
    }

    void PPM::readStream(std::istream& is){
        std::string s;
        int w;
        int h;
        int c;
        is >> s >> w >> h >> c;
        unsigned char sk;
        is.read((char*)&sk,1);
        setHeight(h);
        setWidth(w);
        setMaxColorValue(c);
        int i;
        int x;
        int y;
        unsigned char val;
        for(i = 0; i < mH; i++){ //loops rows
            for(x = 0; x < mW; x++){ //Loops columns
                for(y = 0; y < 3; y++){ //Loops channels
                    is.read((char*)&val,sizeof(val));
                    setChannel( i, x, y, val); 
                }
            }
        }
    }


    bool PPM::operator==( const PPM& rhs ) const{ 
        return (getHeight() * getWidth()) == (rhs.getHeight() * getWidth());
    } 

    bool PPM::operator!=( const PPM& rhs ) const{ 
        return (getHeight() * getWidth()) != (rhs.getHeight() * rhs.getWidth());
    } 

    bool PPM::operator<( const PPM& rhs ) const{ 
        return (getHeight() * getWidth()) < (rhs.getHeight() * rhs.getWidth());
    } 

    bool PPM::operator<=( const PPM& rhs ) const{ 
        return (getHeight() * getWidth()) <= (rhs.getHeight() * rhs.getWidth());
    } 

    bool PPM::operator>( const PPM& rhs ) const{ 
        return (getHeight() * getWidth()) > (rhs.getHeight() * rhs.getWidth());
    } 

    bool PPM::operator>=( const PPM& rhs ) const{ 
        return (getHeight() * getWidth()) >= (rhs.getHeight() * rhs.getWidth());
    }

    PPM& PPM::operator+=( const PPM& rhs ){
        int height = getHeight();
        int width = getWidth();
        int i;
        int x;
        int y;
        for(i = 0; i < height; i++){ //loops rows
            for(x = 0; x < width; x++){ //Loops columns
                for(y = 0; y < 3; y++){ //loops channels
                    int newchan = getChannel(i,x,y) + rhs.getChannel(i,x,y);
                    if(newchan > mC){
                        newchan = mC;
                    }
                    setChannel(i,x,y,newchan);
                }
            }
        }
        return *this;
    }

    PPM& PPM::operator-=( const PPM& rhs ){
        int height = getHeight();
        int width = getWidth();
        int i;
        int x;
        int y;
        for(i = 0; i < height; i++){ //loops rows
            for(x = 0; x < width; x++){ //Loops columns
                for(y = 0; y < 3; y++){ //loops channels
                    int newchan = getChannel(i,x,y) - rhs.getChannel(i,x,y);
                    if(newchan < 0){
                        newchan = 0;
                    }else if(newchan > mC){
                        newchan = mC;}
                    setChannel(i,x,y,newchan);
                }
            }
        }
        return *this;
    }

    PPM& PPM::operator*=( const double& rhs ){
        int height = getHeight();
        int width = getWidth();
        int i;
        int x;
        int y;
        for(i = 0; i < height; i++){ //loops rows
            for(x = 0; x < width; x++){ //Loops columns
                for(y = 0; y < 3; y++){ //loops channels
                    int newchan = getChannel(i,x,y) * rhs;
                    if(newchan < 0){
                        newchan = 0;
                    }else if(newchan > mC){
                        newchan = mC;}
                    setChannel(i,x,y,newchan);
                }
            }
        }
        return *this;
    }

    PPM& PPM::operator/=( const double& rhs ){
        int height = getHeight();
        int width = getWidth();
        int i;
        int x;
        int y;
        for(i = 0; i < height; i++){ //loops rows
            for(x = 0; x < width; x++){ //Loops columns
                for(y = 0; y < 3; y++){ //loops channels
                    int newchan = getChannel(i,x,y) / rhs;
                    if(newchan < 0){
                        newchan = 0;
                    }else if(newchan > mC){
                        newchan = mC;}
                    setChannel(i,x,y,newchan);
                }
            }
        }
        return *this;
    }

    PPM PPM::operator+( const PPM& rhs ) const{
        int height = getHeight();
        int width = getWidth();
        PPM p(height,width);
        p.setMaxColorValue(mC);
        int i;
        int x;
        int y;
        for(i = 0; i < height; i++){ //loops rows
            for(x = 0; x < width; x++){ //Loops columns
                for(y = 0; y < 3; y++){ //loops channels
                    int newchan = getChannel(i,x,y) + rhs.getChannel(i,x,y);
                    if(newchan < 0){
                        newchan = 0;
                    }else if(newchan > mC){
                        newchan = mC;}
                    p.setChannel(i,x,y,newchan);
                }
            }
        }
        return p;
    }

    PPM PPM::operator-( const PPM& rhs ) const{
        int height = getHeight();
        int width = getWidth();
        int i;
        int x;
        int y;
        PPM p(height,width);
        p.setMaxColorValue(mC);
        for(i = 0; i < height; i++){ //loops rows
            for(x = 0; x < width; x++){ //Loops columns
                for(y = 0; y < 3; y++){ //loops channels
                    int newchan = getChannel(i,x,y) - rhs.getChannel(i,x,y);
                    if(newchan < 0){
                        newchan = 0;
                    }else if(newchan > mC){
                        newchan = mC;}
                    p.setChannel(i,x,y,newchan);
                }
            }
        }
        return p;
    }

    PPM PPM::operator*( const double& rhs ) const{
        int height = getHeight();
        int width = getWidth();
        PPM p(height,width);
        p.setMaxColorValue(mC);
        int i;
        int x;
        int y;
        for(i = 0; i < height; i++){ //loops rows
            for(x = 0; x < width; x++){ //Loops columns
                for(y = 0; y < 3; y++){ //loops channels
                    int newchan = getChannel(i,x,y) * rhs;
                    if(newchan < 0){
                        newchan = 0;
                    }else if(newchan > mC){
                        newchan = mC;}
                    p.setChannel(i,x,y,newchan);
                }
            }
        }
        return p;
    }

    PPM PPM::operator/( const double& rhs ) const{
        int height = getHeight();
        int width = getWidth();
        PPM p(height,width);
        p.setMaxColorValue(mC);
        int i;
        int x;
        int y;
        for(i = 0; i < height; i++){ //loops rows
            for(x = 0; x < width; x++){ //Loops columns
                for(y = 0; y < 3; y++){ //loops channels
                    int newchan = getChannel(i,x,y) / rhs;
                    if(newchan < 0){
                        newchan = 0;
                    }else if(newchan > mC){
                        newchan = mC;}
                    p.setChannel(i,x,y,newchan);
                }
            }
        }
        return p;
    }


    void PPM::grayFromChannel( PPM& dst, const int& src_channel ) const{
        int height = getHeight();
        int width = getWidth();
        int maxC = getMaxColorValue();
        dst.setHeight(height);
        dst.setWidth(width);
        dst.setMaxColorValue(maxC);
        int i;
        int x;
        int y;
        for(i = 0; i < height; i++){ //loops rows
            for(x = 0; x < width; x++){ //Loops columns
                for(y = 0; y < 3; y++){ //loops channels
                    dst.setChannel(i, x, y, getChannel(i,x,src_channel));
                }
            }
        }
    }

    void PPM::grayFromRed( PPM& dst ) const{
        grayFromChannel(dst,0);
    }

    void PPM::grayFromGreen( PPM& dst ) const{
        grayFromChannel(dst,1);
    }

    void PPM::grayFromBlue( PPM& dst ) const{
        grayFromChannel(dst,2);
    }

    double PPM::linearColorimetricPixelValue( const int& row, const int& column ) const{
        double red = getChannel(row,column,0);
        double green = getChannel(row,column,1);
        double blue = getChannel(row,column,2);
        double brightness = 0.2126 * red + 0.7152 * green + 0.0722 * blue;
        return brightness;
    }

    void PPM::grayFromLinearColorimetric( PPM& dst ) const{
        int height = getHeight();
        int width = getWidth();
        int maxC = getMaxColorValue();
        dst.setHeight(height);
        dst.setWidth(width);
        dst.setMaxColorValue(maxC);
        int i;
        int x;
        int y;
        for(i = 0; i < height; i++){ //loops rows
            for(x = 0; x < width; x++){ //Loops columns
                for(y = 0; y < 3; y++){ //loops channels
                    dst.setChannel( i, x, y, linearColorimetricPixelValue(i,x));
                }
            }
        }
    }


