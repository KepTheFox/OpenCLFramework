#include "clFramework.h"

/*device functions*/
void clDevice::initDevice(cl_device_id did){
    cl_int err;
    this->id = did;
    err |= clGetDeviceInfo(this->id, CL_DEVICE_AVAILABLE, sizeof(this->deviceAvailable), (void *)&(this->deviceAvailable), NULL);
    err |= clGetDeviceInfo(this->id, CL_DEVICE_COMPILER_AVAILABLE, sizeof(this->deviceCompilerAvailable), (void *)&(this->deviceCompilerAvailable), NULL);
    err |= clGetDeviceInfo(this->id, CL_DEVICE_EXTENSIONS, sizeof(this->deviceExtensions), (void *)&(this->deviceExtensions), NULL);
    err |= clGetDeviceInfo(this->id, CL_DEVICE_GLOBAL_MEM_SIZE, sizeof(this->deviceGlobalMemSize), (void *)&(this->deviceGlobalMemSize), NULL);
    err |= clGetDeviceInfo(this->id, CL_DEVICE_MAX_WORK_GROUP_SIZE, sizeof(this->deviceWorkgroupSize), (void *)&(this->deviceWorkgroupSize), NULL);
    err |= clGetDeviceInfo(this->id, CL_DEVICE_MAX_COMPUTE_UNITS, sizeof(this->deviceMaxComputeUnits), (void *)&(this->deviceMaxComputeUnits), NULL);
    err |= clGetDeviceInfo(this->id, CL_DEVICE_NAME, sizeof(this->deviceName), (void *)&(this->deviceName), NULL);
    err |= clGetDeviceInfo(this->id, CL_DEVICE_VENDOR, sizeof(this->deviceVendor), (void *)&(this->deviceVendor), NULL);

}

void clDevice::printDeviceInfo(){
    printf("-------------------------------------\n");
    printf("DEVICE NAME:\t\t%s\n", this->deviceName);
    printf("DEVICE VENDOR: \t\t%s\n", this->deviceVendor);
    printf("MAX WORKGROUP SIZE:\t%ld\n", this->deviceWorkgroupSize);
    printf("MAX COMPUTE UNITS:\t%d\n", this->deviceMaxComputeUnits);
    printf("MAX DEVICE THREADS:\t%d\n", this->deviceMaxComputeUnits * 64);
    printf("GLOBAL MEM SIZE:\t%ldMiB\n", this->deviceGlobalMemSize/(1024*1024));
    printf("-------------------------------------\n");
}



/*platform functions*/
clPlatform::clPlatform(){
}

void clPlatform::initPlatform(cl_platform_id pid){
    /*Init Platform Here*/
    cl_int err;
    this->id = pid;
    err |= clGetPlatformInfo(this->id, CL_PLATFORM_PROFILE, sizeof(this->platformProfile), this->platformProfile, NULL);
    err |= clGetPlatformInfo(this->id, CL_PLATFORM_VERSION, sizeof(this->platformVersion), this->platformVersion, NULL);
    err |= clGetPlatformInfo(this->id, CL_PLATFORM_NAME, sizeof(this->platformName), this->platformName, NULL);
    err |= clGetPlatformInfo(this->id, CL_PLATFORM_VENDOR, sizeof(this->platformVendor), this->platformVendor, NULL);
    err |= clGetPlatformInfo(this->id, CL_PLATFORM_EXTENSIONS, sizeof(this->platformExtensions), this->platformExtensions, NULL);
    this->getDevices();
}

void clPlatform::printPlatformInfo(){
    printf("========= PLATFORM =========\n");
    printf("-------------------------------------\n");
    printf("PLATFORM PROFILE:\t%s\n", this->platformProfile);
    printf("PLATFORM VERSION:\t%s\n", this->platformVersion);
    printf("PLATFORM NAME:\t\t%s\n", this->platformName);
    printf("PLATFORM VENDOR:\t%s\n", this->platformVendor);
    printf("PLATFORM EXTENSIONS:\t%s\n", this->platformExtensions);
    printf("-------------------------------------\n");
    printf("\n");
    printf("======= DEVICE(S): %d =======\n", this->numDevices);
    for(int i = 0; i < this->numDevices; ++i){
        this->clDevices[i].printDeviceInfo();
    }
}

void clPlatform::getDevices(){
    cl_int err;

    err |= clGetDeviceIDs(this->id, CL_DEVICE_TYPE_ALL, 0, NULL, &(this->numDevices));
    // printf("Found %d platform(s)\n", this->numPlatforms);

    cl_device_id *tmp_cl_devices = new cl_device_id[this->numDevices];
    err |= clGetDeviceIDs(this->id, CL_DEVICE_TYPE_ALL, this->numDevices, tmp_cl_devices, NULL);

    this->clDevices = new clDevice[this->numDevices];

    for(int i = 0; i < this->numDevices; ++i){
        this->clDevices[i].initDevice(tmp_cl_devices[i]);
    }
}




/*info functions*/
clInfo::clInfo(){
    cl_int err;

    err |= clGetPlatformIDs(0, NULL, &(this->numPlatforms));
    // printf("Found %d platform(s)\n", this->numPlatforms);

    cl_platform_id *tmp_cl_platforms = new cl_platform_id[this->numPlatforms];
    err |= clGetPlatformIDs(this->numPlatforms, tmp_cl_platforms, NULL);

    this->clPlatforms = new clPlatform[this->numPlatforms];

    for(int i = 0; i < this->numPlatforms; ++i){
        this->clPlatforms[i].initPlatform(tmp_cl_platforms[i]);
    }
}

void clInfo::printInfo(){
    for(int i = 0; i < this->numPlatforms; ++i){
        this->clPlatforms[i].printPlatformInfo();
    }
}