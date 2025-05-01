#ifndef _JULIASET_H_
#define _JULIASET_H_
#include "ComplexFractal.h"
#include <cmath>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>


class JuliaSet : public ComplexFractal {

public:
    JuliaSet( );

    JuliaSet( const int& height, const int& width, const double& min_x, const double& max_x, const double& min_y, const double& max_y, const double& a, const double& b );

    virtual ~JuliaSet( );

    double getA( ) const;

    double getB( ) const;

    void setParameters( const double& a, const double& b );

    virtual void calculateNextPoint( const double x0, const double y0, double& x1, double &y1 ) const;

    virtual int calculatePlaneEscapeCount( const double& x0, const double& y0 ) const;

    virtual int calculateNumber( const int& row, const int& column ) const;

private:
    double a_par; // the A parameter for the Julia sset function
    double b_par; // the B parameter for the Julia sset function

};
#endif /* _JULIASET_H_ */
/* Local Variables: */
/* mode:c++         */
/* End:             */