#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <cmath>
#include <chrono>
#include <thread>
#include <mutex>
#include "ThreadedGrid.h"
#include "ThreadedVector.h"
#include "NumberGrid.h"
#include "ColorTable.h"

    ThreadedGrid::ThreadedGrid() : NumberGrid(){
        //Leaves task queue empty, sets default NumberGrid
    }

    ThreadedGrid::ThreadedGrid(const int& height, const int& width) : NumberGrid(height,width) {
        //Leaves task queue empty, sets custom NumberGrid
    }

    ThreadedGrid::~ThreadedGrid(){
        //Destructor, remains empty
    }

    void ThreadedGrid::calculateAllNumbers(){
        for(int y = 0; y < getHeight(); y++){
            t_objects.push_back(y);
        }
        std::vector<std::thread> threads;
        unsigned int my_threads = std::thread::hardware_concurrency();
        unsigned int i;
        for(i = 0; i < my_threads-1; i++){
            try {
               threads.push_back(std::thread(&ThreadedGrid::worker, this)); 
            }catch(...) {
                break;
            }
        }
        for(i = 0; i < threads.size(); i++) {
            threads[i].join();
        }
    }

    void ThreadedGrid::worker(){
        std::vector<int> the_tasks;
        while(t_objects.size() > 0){
            the_tasks.clear();
            t_objects.pop_back(the_tasks, 1);
            unsigned int n;
            for(n = 0; n < the_tasks.size(); n++) {
                int row = the_tasks[n];
                for(int x = 0; x < getWidth(); x++){
                    setNumber(row,x,calculateNumber(row,x));
                }
            }
        }
    }


    void ThreadedGrid::setPPM( PPM& ppm, const ColorTable& colors ){
        if(colors.getNumberOfColors() >= 2){
            ppm.setHeight(getHeight());
            ppm.setWidth(getWidth());
            ppm.setMaxColorValue(colors.getMaxChannelValue());
            for(int y = 0; y < ppm.getHeight(); y++){
                t_objects.push_back(y);
            }
            std::vector<std::thread> threads;
            unsigned int my_threads = std::thread::hardware_concurrency();
            unsigned int i;
            for(i = 0; i < my_threads-1; i++){
                for(i = 0; i < my_threads-1; i++){
                    try {
                        threads.push_back( std::thread(&ThreadedGrid::workerSetPPM, this, std::ref(ppm), std::ref(colors)) ); 
                    } catch(...) {
                        break;
                        }
                    }
                for(i = 0; i < threads.size(); i++) {
                    threads[i].join();
                }
            }
        }
    }
    



    void ThreadedGrid::workerSetPPM(PPM& ppm, const ColorTable& colors){
        std::cout << "tgrid called" << std::endl;
        std::vector<int> the_tasks;
        int num = colors.getNumberOfColors();
        while(t_objects.size() > 0){
            the_tasks.clear();
            t_objects.pop_back(the_tasks, 1);
            unsigned int n;
            for(n = 0; n < the_tasks.size(); n++) {
                int row = the_tasks[n];
                for(int x = 0; x < ppm.getWidth(); x++){
                    if(getNumber(row,x) == max){
                        ppm.setPixel(row,x,colors[num-1].getRed(),colors[num-1].getGreen(),colors[num-1].getBlue());
                    }else{
                        int index = getNumber(row,x) % num;
                        ppm.setPixel(row,x,colors[index].getRed(),colors[index].getGreen(),colors[index].getBlue());
                    }
                }
            }
        }
    }

    

