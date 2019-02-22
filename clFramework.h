#include <stdio.h>
#include <stdlib.h>
    
#ifdef __APPLE__
#include <OpenCL/opencl.h>
#else
#include <CL/cl.h>
#endif


#include <stdio.h>
#include <string>

class clDevice{
public:
    /*Variables*/
    cl_device_id device_id;
    cl_bool deviceAvailable;
    cl_bool deviceCompilerAvailable;
    char deviceExtensions[156];
    cl_ulong deviceGlobalMemSize;
    size_t deviceWorkgroupSize;
    cl_uint deviceMaxComputeUnits;
    char deviceName[156];
    char deviceVendor[156];

    /*Functions*/
    void getDeviceInfo();
    void printDeviceInfo();
private:
};

class clPlatform{
public:
    void initPlatform(cl_platform_id id);
private:
    cl_platform_id id;
    char platformProfile[156];
    char platformVersion[156];
    char platformName[156];
    char platformVendor[156];
    char platformExtensions[156];
};

class clInfo{
public:
    clInfo();
    void loadKernelsFromFile(std::string filename);

    cl_platform_id *clPlatformIDs;
    cl_uint numPlatforms;
    clPlatform *clPlatforms;
};