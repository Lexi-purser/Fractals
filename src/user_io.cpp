#include "image_menu.h"
#include "ActionData.h"
#include "MenuData.h"
#include  "ColorTable.h"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <map>


double getDouble(ActionData& action_data, const std::string& prompt) {
    double dvalue;
    action_data.getOS() << prompt;
    action_data.getIS() >> dvalue;
    return dvalue;
}

std::string getString(ActionData& action_data, const std::string& prompt){
    std::string word;
    action_data.getOS() << prompt;
    action_data.getIS() >> word;
    return word;
}

int getInteger(ActionData& action_data, const std::string& prompt){
    int ivalue;
    action_data.getOS() << prompt;
    action_data.getIS() >> ivalue;
    return ivalue;
}

int askQuestions3(ActionData& action_data){
    std::string word = getString(action_data, "What is your favorite color? ");
    int ivalue = getInteger(action_data, "What is your favorite integer? ");
    double dvalue = getDouble(action_data, "What is your favorite number? ");
    int i;
    for(i = 1; i <= ivalue; i++) {
        if (ivalue > 0){
            action_data.getOS() << i << " " << word << " " << dvalue << "\n";
        }
        
        }
   
    return ivalue;
}

/*int askUncleBuckQuestions(ActionData& action_data) {
    std::string q1 = getString(action_data, "Where do you live?: ");
    std::string q2 = getString(action_data, "Own or rent?: ");
    int q3 = getInteger(action_data, "What is your record for consecutive questions asked?: ");
    std::string r1;
    if (q3 < 20){
        r1 = "okay.";
    } else {
            r1 = "pretty good.";
        }
    action_data.getOS() << q3 << " is " << r1 << " Enjoy " << q2 << "ing in the " << q1;
    return q3;
}*/

/////////////////////////////////////////

std::string getChoice( ActionData& action_data ){
    std::string c = getString(action_data, "Choice? ");
    return c;
}

void commentLine(ActionData& action_data){
    while(action_data.getIS().good() == true){
        unsigned char ch;
        action_data.getIS().read((char *)&ch, 1);
        if(ch == '\n'){
            return;
        }
    }
return;
}

void quit(ActionData& action_data){
    action_data.setDone();
}







