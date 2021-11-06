#pragma once
#include "OpenCL.h"

template<typename T>
inline void OpenCL::enqueueVectorData(std::string name, std::vector<T>& vec)
{
    auto it = argsOrder_.find(name);
    if (it == argsOrder_.end()) {
        return;
    }
    buffers_[name] = cl::Buffer(context_, CL_MEM_READ_WRITE, vec.size() * sizeof(T));
    queue_.enqueueWriteBuffer(buffers_[name], CL_TRUE, 0, vec.size() * sizeof(T), vec.data());
    kernel_.setArg(it->second, buffers_[name]);
}

template<typename T>
inline void OpenCL::enqueueData(std::string name, T& el)
{
    auto it = argsOrder_.find(name);
    if (it == argsOrder_.end()) {
        return;
    }
    kernel_.setArg(it->second, el);
}

template<typename T>
inline void OpenCL::readVectorResult(std::string name, std::vector<T>& vec)
{
    auto it = buffers_.find(name);
    if (it == buffers_.end()) {
        return;
    }
    queue_.enqueueReadBuffer(it->second, CL_TRUE, 0, vec.size() * sizeof(T), vec.data());
}

template<typename T>
inline void OpenCL::enqueueReadVector(std::string name, std::vector<T>& vec)
{
    auto it = argsOrder_.find(name);
    if (it == argsOrder_.end()) {
        return;
    }
    buffers_[name] = cl::Buffer(context_, CL_MEM_READ_WRITE, vec.size() * sizeof(T));
    kernel_.setArg(it->second, buffers_[name]);
}
