#pragma once
#include <fstream>
#include <string>
class FileLoader
{
protected:
    const char* filePath_;
    std::ifstream file_;
public:
    FileLoader(const char* filePath);
    std::string load();
};

