#include "OpenCL.h"
#include "FileLoader.h"
#include <iostream>
OpenCL::OpenCL()
{
}

std::vector<std::string> OpenCL::getAvailablePlatforms()
{
    cl::Platform::get(&platforms_);
    std::vector<std::string> platformNames;
    for (auto platform : platforms_) {
        platformNames.push_back(platform.getInfo<CL_PLATFORM_VERSION>());
    }
    return platformNames;
}

bool OpenCL::applyPlatform(size_t index)
{
    if(index >= platforms_.size())
        return false;
    
    defaultPlatform_ = platforms_[index];
    return true;
}

std::vector<std::string> OpenCL::getAvailableDevices()
{
    defaultPlatform_.getDevices(CL_DEVICE_TYPE_ALL, &devices_);
    std::vector<std::string> deviceNames;
    for (auto device : devices_) {
        deviceNames.push_back(device.getInfo<CL_DEVICE_NAME>());
    }
    return deviceNames;
}

bool OpenCL::applyDevide(size_t index)
{
    if (index >= devices_.size())
        return false;
    
    defaultDevice_ = devices_[index];
    return true;
}

void OpenCL::run(size_t workers)
{
    queue_.enqueueNDRangeKernel(kernel_, cl::NullRange, cl::NDRange(workers), cl::NullRange);
    queue_.finish();
}

void OpenCL::init(const char* programPath, const char* programName, std::vector<std::string> argsOrder)
{
    FileLoader programLoader(programPath);
    std::string programCode = programLoader.load();
    if (programCode.length() == 0) {
        std::cout << "ERROR::OPEN_CL: empty program" << std::endl;
        exit(EXIT_FAILURE);
    }

    context_ = cl::Context({ defaultDevice_ });
    cl::Program::Sources sources;
    sources.push_back({ programCode.c_str(), programCode.length() });
    program_ = cl::Program(context_, sources);
    if (program_.build({ defaultDevice_ }, "-cl-std=CL3.0") != CL_SUCCESS) {
        std::cout << "ERROR::OPEN_CL: Error building:" << std::endl << program_.getBuildInfo<CL_PROGRAM_BUILD_LOG>(defaultDevice_) << "\n";
        exit(EXIT_FAILURE);
    }
    queue_ = cl::CommandQueue(context_, defaultDevice_);
    cl_int error = 0;
    kernel_ = cl::Kernel(program_, programName, &error);
    if (error != 0) {
        std::cout << "ERROR::OPEN_CL: Error during kernel creation. Error code: " << error;
        exit(EXIT_FAILURE);
    }
    cl_uint id = 0;
    for (auto arg : argsOrder) {
        argsOrder_.insert({ arg, id++ });
    }
}
