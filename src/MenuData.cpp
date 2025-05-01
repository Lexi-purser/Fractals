#include "MenuData.h"
#include <iostream>

    MenuData::MenuData(){

    }
    
    void MenuData::addAction(const std::string& name, ActionFunctionType func, const std::string& description){
        c_names.push_back(name);
        c_to_action[name] = func;
        c_to_ds[name] = description;
    }
    
    const std::vector<std::string>& MenuData::getNames() const{
        return c_names;
    }
    
    ActionFunctionType MenuData::getFunction(const std::string& name){
        ActionFunctionType func;
        if(c_to_action.find(name) != c_to_action.end()){
            func = c_to_action[name];
            return func;
        }else{
            return 0;
        }
    }
    
    const std::string& MenuData::getDescription(const std::string& name){
        static std::string empt;
        if(c_to_ds.count(name) == 1 ){
            return c_to_ds[name];
        }else{
            return empt;
        }   
    }