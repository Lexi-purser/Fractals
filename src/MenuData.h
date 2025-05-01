#ifndef _MENUDATA_H_
#define _MENUDATA_H_
#include "ActionData.h"
#include "PPM.h"
#include <iostream>
#include <string>
#include <vector>
#include <map>

typedef void (*ActionFunctionType)(ActionData& action_data);

class MenuData {
public:
    MenuData();
    
    void addAction(const std::string& name, ActionFunctionType func, const std::string& description);
    
    const std::vector<std::string>& getNames() const;
    
    ActionFunctionType getFunction(const std::string& name);
    
    const std::string& getDescription(const std::string& name);


private:
    std::vector<std::string> c_names;
    std::map<std::string,ActionFunctionType> c_to_action;
    std::map<std::string,std::string> c_to_ds;
};

#endif /* _MENUDATA_H_*/
/* Local Variables: */
/* mode:c++         */
/* End:             */