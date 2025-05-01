#ifndef _ACTIONDATA_H_
#define _ACTIONDATA_H_
#include "PPM.h"
#include "Image.h"
#include "NumberGrid.h"
#include "ColorTable.h"
#include "ComplexFractal.h"
#include "JuliaSet.h"
#include "MandelbrotSet.h"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <map>
#include <ostream>

class ActionData {
public:
    ActionData(std::istream& is, std::ostream& os);

    std::istream& getIS();

    std::ostream& getOS();

    PPM& getInputImage1();

    PPM& getInputImage2();

    PPM& getOutputImage();

    bool getDone() const;

    void setDone();

    ~ActionData();

    NumberGrid& getGrid();

    void setGrid(NumberGrid *grid);

    ColorTable& getTable();

private:

    std::istream& IS;

    std::ostream& OS;

    PPM input_image_1;

    PPM input_image_2;

    PPM output_image;

    bool bye;

    NumberGrid * numb;

    ColorTable color_table;
};

#endif /* _ACTIONDATA_H_*/
/* Local Variables: */
/* mode:c++         */
/* End:             */