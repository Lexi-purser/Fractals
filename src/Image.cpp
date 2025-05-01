
#include "Image.h"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <map>
#include <ostream>

    Image::Image(){
        mH = 0;
        mW = 0;
        myvector.resize(mH*mW*3);
    }
    
    Image::Image( const int& height, const int& width ) : mH(height), mW(width) {
        myvector.resize(mH*mW*3);
    }

    int Image::getHeight() const {
        return mH;
    }

    int Image::getWidth() const {
        return mW;
    }

    bool Image::indexValid( const int& row, const int& column, const int& channel ) const {
        if(row < mH && row >= 0 && column < mW && column >= 0 && channel <= 2 && channel >= 0) {
            return true;
        } else {
        return false;
        }
    }
    
    int Image::index( const int& row, const int& column, const int& channel ) const {
        int vindex;
        vindex = ((row * mW * 3 + column * 3) + channel);
        return vindex;
    }
   
    int Image::getChannel( const int& row, const int& column, const int& channel ) const {
        bool tf = indexValid(row, column, channel);
        if (tf == true){
            int chan = index( row, column, channel);
            return myvector[chan];
        }else{
            return -1;
        }
    }
    
    void Image::setHeight( const int& height) {
        if(height >= 0){
            mH = height;
            myvector.resize(mH*mW*3);
        }
    }

    
    void Image::setWidth( const int& width ) {
       if(width >= 0){
        mW = width;
        myvector.resize(mH*mW*3);
       }
    }
    
    void Image::setChannel( const int& row, const int& column, const int& channel, const int& value ) {
        bool tf = indexValid( row, column, channel);
        if (tf == true){
            int chan = index(row, column, channel);
            myvector[chan] = value;
        }
    }




