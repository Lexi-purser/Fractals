#include "ActionData.h"
#include <iostream>

int main() {
    ActionData action_data(std::cin, std::cout);
    int value = askUncleBuckQuestions(action_data);
    return value;
}