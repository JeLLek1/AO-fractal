#pragma once
#define CL_HPP_ENABLE_EXCEPTIONS
#define CL_HPP_TARGET_OPENCL_VERSION 300
#include <CL/cl.hpp>
#include <vector>
#include <map>
#include <string>

class OpenCL
{
protected:
    std::vector<cl::Platform> platforms_;
    std::vector<cl::Device> devices_;
    cl::Platform defaultPlatform_;
    cl::Device defaultDevice_;
    cl::Context context_;
    cl::Program program_;
    cl::CommandQueue queue_;
    cl::Kernel kernel_;

    std::map<std::string, cl_uint> argsOrder_;
    std::map<std::string, cl::Buffer> buffers_;
public:
    OpenCL();

    std::vector<std::string> getAvailablePlatforms();
    bool applyPlatform(size_t index);
    std::vector<std::string> getAvailableDevices();
    bool applyDevide(size_t index);

    template <typename T>
    void enqueueVectorData(std::string name, std::vector<T>& vec);
    template <typename T>
    void enqueueData(std::string name, T& el);
    template <typename T>
    void readVectorResult(std::string name, std::vector<T>& vec);
    template <typename T>
    void enqueueReadVector(std::string name, std::vector<T>& vec);

    void run(size_t workers);

    void init(const char* programPath, const char* programName, std::vector<std::string> argsOrder);
};

#include "OpenCL.inl"
