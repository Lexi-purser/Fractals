#ifndef _NUMBERGRID_H_
#define _NUMBERGRID_H_
#include "PPM.h"
#include "ColorTable.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>

class NumberGrid {
public:
    NumberGrid( );

    NumberGrid( const int& height, const int& width );

    virtual ~NumberGrid();

    int getHeight( ) const;

    int getWidth( ) const;

    int getMaxNumber( ) const;

    virtual void setGridSize( const int& height, const int& width );

    void setMaxNumber( const int& number );

    const std::vector< int >& getNumbers( ) const;

    int index( const int& row, const int& column ) const;

    bool indexValid( const int& row, const int& column ) const;

    bool numberValid( const int& number ) const;

    int getNumber( const int& row, const int& column ) const;

    void setNumber( const int& row, const int& column, const int& number );

    virtual void setPPM( PPM& ppm ) const;

    void setPPM( PPM& ppm, const ColorTable& colors );

    virtual int calculateNumber(const int& row, const int& column) const = 0;

    virtual void calculateAllNumbers();

protected:   
    int gH;
    int gW;
    int max;
    std::vector<int> grid;

};

class ManhattanNumbers : public NumberGrid {
public:
    ManhattanNumbers();

    ManhattanNumbers(const int& height, const int& width);

    virtual ~ManhattanNumbers();

    int calculateNumber(const int& row, const int& column) const;

};


#endif /* _NUMBERGRID_H_ */
/* Local Variables: */
/* mode:c++         */
/* End:             */