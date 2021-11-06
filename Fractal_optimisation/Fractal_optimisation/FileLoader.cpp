#include "FileLoader.h"
#include <sstream>
#include <iostream>

FileLoader::FileLoader(const char* filePath)
{
    filePath_ = filePath;
    file_.exceptions (std::ifstream::failbit | std::ifstream::badbit);
}

std::string FileLoader::load()
{
    std::string content = "";
    try {
        file_.open(filePath_);
        std::stringstream ssContent;
        ssContent << file_.rdbuf();
        file_.close();
        content = ssContent.str();
    }
    catch (std::ifstream::failure e) {
        std::cout << "ERROR::FILE_LOADER::READ_FILE_FAILUER" << std::endl;
    }
    return content;
}
