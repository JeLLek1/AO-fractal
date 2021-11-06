#pragma once
#include <vector>
#include <string>
class CommandListSelect
{
protected:
    std::vector<std::string> selections_;
    size_t currentSelection_ = 0;
    bool applySelected_ = false;

    void handleInput(char key);
    void display();
public:
    CommandListSelect(std::vector<std::string> &selections);
    size_t run();
};

