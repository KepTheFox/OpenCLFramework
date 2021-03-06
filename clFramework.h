#include <stdio.h>
#include <stdlib.h>
    
#ifdef __APPLE__
#include <OpenCL/opencl.h>
#else
#include <CL/cl.h>
#endif


#include <stdio.h>
#include <string>
#include <vector>
#include <map>

// template <typename T>;
// class clBuffers{
//     int createBuffer(std::string name, size_t size);
//     int writeBuffer(std::string name, size_t size, void *data);
//     int readBuffer(std::string name, size_t size, void *data);

//     std::map<std::string, cl_mem> buffers;
// };

// class clKernels{
//     /*Functions*/
//     int addKernel();
//     int setKernelArg();
//     int enqueueNDRangeKernel(std::string kernelName);
//     void printKernels();


//     std::map<std::string, cl_kernel> kernels;
// };

class clDevice{
public:

    /*Functions*/
    void initDevice(cl_device_id did);
    void printDeviceInfo();
    void loadKernelsFromFile(char *filename);
    bool checkAvailable(){return deviceAvailable;}

    int createBuffer(char *name, size_t size);
    cl_mem *getBuffer(char *name);

    int enqueueWriteBuffer(char *name, size_t size, void *data, bool blocking);
    int enqueueReadBuffer(char *name, size_t size, void *data, bool blocking);

    int createKernel(char *name);
    cl_kernel *getKernel(char *name);
    int setKernelArg(char *kernelName, char *bufferName, int argNum);
    int enqueueNDRangeKernel(char *kernelName, size_t *global, size_t *local);
    void printKernels();



    cl_device_id id;

    cl_program program;
    cl_context context;
    cl_command_queue commandQueue;

    cl_bool deviceAvailable;
    cl_bool deviceCompilerAvailable;
    char deviceExtensions[156];
    cl_ulong deviceGlobalMemSize;
    size_t deviceWorkgroupSize;
    cl_uint deviceMaxComputeUnits;
    char deviceName[156];
    char deviceVendor[156];

    cl_event ev;

    std::map<char *, cl_mem> buffers;

    std::map<char *, cl_kernel> kernels;
};

class clPlatform{
public:
    clPlatform();
    void initPlatform(cl_platform_id pid);
    void getDevices();
    void printPlatformInfo();
    void loadKernelsFromFile(char *filename);
    clDevice* getFirstAvailableDevice();

    cl_platform_id id;
    char platformProfile[156];
    char platformVersion[156];
    char platformName[156];
    char platformVendor[156];
    char platformExtensions[156];

    cl_uint numDevices;
    clDevice *clDevices;
};

class clInfo{
public:
    clInfo();
    void printInfo();
    void loadKernelsFromFile(char *filename);
    clDevice *getFirstAvailableDevice();

    cl_platform_id *clPlatformIDs;
    cl_uint numPlatforms;
    clPlatform *clPlatforms;
};