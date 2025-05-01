#ifndef _THREADEDGRID_H_
#define _THREADEDGRID_H_
#include "NumberGrid.h"
#include "ThreadedVector.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <cmath>

class ThreadedGrid : public NumberGrid {

public:
    ThreadedGrid();

    ThreadedGrid(const int& height, const int& width);

    virtual ~ThreadedGrid();

    virtual void calculateAllNumbers();

    virtual void worker();

    virtual void setPPM( PPM& ppm, const ColorTable& ct );

    virtual void workerSetPPM(PPM& ppm, const ColorTable& ct);

protected:    
    ThreadedVector<int> t_objects;

};






#endif /* _THREADEDGRID_H_ */
/* Local Variables: */
/* mode:c++         */
/* End:             */