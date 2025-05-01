#ifndef _IMAGE_H_
#define _IMAGE_H_
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <map>
#include <ostream>


class Image {
public:

    Image();

    Image( const int& height, const int& width );

    int getHeight() const;

    int getWidth() const;

    bool indexValid( const int& row, const int& column, const int& channel ) const;
    
    int index( const int& row, const int& column, const int& channel ) const;
   
    int getChannel( const int& row, const int& column, const int& channel ) const;
    
    void setHeight( const int& height );
    
    void setWidth( const int& width );
    
    void setChannel( const int& row, const int& column, const int& channel, const int& value );

protected:
    std::vector<int> myvector;
    int mH;
    int mW;

};

#endif /* _IMAGE_H_ */
/* Local Variables: */
/* mode:c++         */
/* End:             */