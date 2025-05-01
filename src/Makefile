CXX := g++
CXXFLAGS := -std=c++11 -Wall -Wextra -Wpedantic -Werror 
TARGETS := hello questions_3 ascii_image image_file ppm_menu
LDFLAGS := -lpthread

all:$(TARGETS)

hello: hello.o
	$(CXX) $(CXXFLAGS) -o $@ $^

hello.o: hello.cpp
	$(CXX) $(CXXFLAGS) -c $<

questions_3: questions_3.o user_io.o controllers.o image_drawing.o image_output.o Image.o PPM.o MenuData.o ActionData.o image_filters.o NumberGrid.o ColorTable.o ComplexFractal.o JuliaSet.o MandelbrotSet.o ThreadedGrid.o
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

questions_3.o: questions_3.cpp image_menu.h Image.h PPM.h MenuData.h ActionData.h ColorTable.h ComplexFractal.h JuliaSet.h MandelbrotSet.h ThreadedGrid.h
	$(CXX) $(CXXFLAGS) -c $< 

user_io.o: user_io.cpp image_menu.h Image.h PPM.h ActionData.h MenuData.h ColorTable.h ComplexFractal.h JuliaSet.h MandelbrotSet.h ThreadedGrid.h
	$(CXX) $(CXXFLAGS) -c $<

controllers.o: controllers.cpp image_menu.h Image.h PPM.h ActionData.h MenuData.h NumberGrid.h ColorTable.h ComplexFractal.h JuliaSet.h MandelbrotSet.h ThreadedGrid.h
	$(CXX) $(CXXFLAGS) -c $<

image_output.o : image_output.cpp image_menu.h Image.h PPM.h ActionData.h MenuData.h ColorTable.h ComplexFractal.h JuliaSet.h MandelbrotSet.h ThreadedGrid.h
	$(CXX) $(CXXFLAGS) -c $<

image_drawing.o : image_drawing.cpp image_menu.h Image.h PPM.h ActionData.h MenuData.h NumberGrid.h ColorTable.h ComplexFractal.h JuliaSet.h MandelbrotSet.h ThreadedGrid.h
	$(CXX) $(CXXFLAGS) -c $<

Image.o : Image.cpp image_menu.h Image.h 
	$(CXX) $(CXXFLAGS) -c $<

PPM.o : PPM.cpp image_menu.h Image.h PPM.h
	$(CXX) $(CXXFLAGS) -c $<

#buck: buck.o user_io.o controllers.o Image.o image_drawing.o image_output.o PPM.o ActionData.o MenuData.o
#	$(CXX) $(CXXFLAGS) -o $@ $^

#buck.o: buck.cpp image_menu.h ActionData.h MenuData.h
#	$(CXX) $(CXXFLAGS) -c $<

ascii_image: ascii_image.o user_io.o controllers.o image_output.o image_drawing.o Image.o PPM.o ActionData.o MenuData.o image_filters.o NumberGrid.o ColorTable.o ComplexFractal.o JuliaSet.o MandelbrotSet.o ThreadedGrid.o
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

ascii_image.o: ascii_image.cpp image_menu.h Image.h ActionData.h MenuData.h NumberGrid.h ColorTable.h ComplexFractal.h JuliaSet.h MandelbrotSet.h ThreadedGrid.h
	$(CXX) $(CXXFLAGS) -c $<

image_file: image_file.o user_io.o controllers.o image_output.o image_drawing.o Image.o PPM.o ActionData.o MenuData.o image_filters.o NumberGrid.o ColorTable.o ComplexFractal.o JuliaSet.o MandelbrotSet.o ThreadedGrid.o
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

image_file.o: image_file.cpp image_menu.h Image.h PPM.h ActionData.h MenuData.h NumberGrid.h ColorTable.h ComplexFractal.h JuliaSet.h MandelbrotSet.h ThreadedGrid.h
	$(CXX) $(CXXFLAGS) -c $<

ActionData.o: ActionData.cpp image_menu.h Image.h PPM.h ActionData.h MenuData.h NumberGrid.h ColorTable.h ComplexFractal.h JuliaSet.h MandelbrotSet.h ThreadedGrid.h
	$(CXX) $(CXXFLAGS) -c $<

MenuData.o: MenuData.cpp image_menu.h MenuData.h ActionData.h Image.h PPM.h ColorTable.h ComplexFractal.h JuliaSet.h MandelbrotSet.h ThreadedGrid.h
	$(CXX) $(CXXFLAGS) -c $<

ppm_menu: ppm_menu.o user_io.o controllers.o image_output.o image_drawing.o Image.o PPM.o ActionData.o MenuData.o image_filters.o NumberGrid.o ColorTable.o ComplexFractal.o JuliaSet.o MandelbrotSet.o ThreadedGrid.o
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

ppm_menu.o: ppm_menu.cpp image_menu.h Image.h PPM.h ActionData.h MenuData.h NumberGrid.h ColorTable.h ComplexFractal.h JuliaSet.h MandelbrotSet.h ThreadedGrid.h
	$(CXX) $(CXXFLAGS) -c $<

image_filters.o: image_filters.cpp image_menu.h Image.h PPM.h ActionData.h MenuData.h ColorTable.h ComplexFractal.h JuliaSet.h MandelbrotSet.h ThreadedGrid.h
	$(CXX) $(CXXFLAGS) -c $<

NumberGrid.o: NumberGrid.cpp image_menu.h Image.h PPM.h ActionData.h MenuData.h ColorTable.h ComplexFractal.h JuliaSet.h MandelbrotSet.h ThreadedGrid.h
	$(CXX) $(CXXFLAGS) -c $<

ColorTable.o: ColorTable.cpp image_menu.h Image.h PPM.h ActionData.h MenuData.h NumberGrid.h ColorTable.h ComplexFractal.h JuliaSet.h MandelbrotSet.h ThreadedGrid.h
	$(CXX) $(CXXFLAGS) -c $<

ComplexFractal.o: ComplexFractal.cpp image_menu.h Image.h PPM.h ActionData.h MenuData.h NumberGrid.h ColorTable.h JuliaSet.h MandelbrotSet.h ThreadedGrid.h ThreadedVector.h
	$(CXX) $(CXXFLAGS) -c $<

JuliaSet.o: JuliaSet.cpp image_menu.h Image.h PPM.h ActionData.h MenuData.h NumberGrid.h ColorTable.h ComplexFractal.h ThreadedGrid.h
	$(CXX) $(CXXFLAGS) -c $<

MandelbrotSet.o: MandelbrotSet.cpp image_menu.h Image.h PPM.h ActionData.h MenuData.h NumberGrid.h ColorTable.h ComplexFractal.h ThreadedGrid.h
	$(CXX) $(CXXFLAGS) -c $<

ThreadedGrid.o: ThreadedGrid.cpp image_menu.h Image.h PPM.h ActionData.h MenuData.h NumberGrid.h ColorTable.h ComplexFractal.h ThreadedVector.h
	$(CXX) $(CXXFLAGS) -c $<
clean:
	-rm -f *.o *~ $(TARGETS)

