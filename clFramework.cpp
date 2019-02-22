#include "clFramework.h"

/*device functions*/
void clDevice::printDeviceInfo(){
}



/*platform functions*/
void clPlatform::initPlatform(cl_platform_id id){
    printf("Initializing platform\n");
    // cl_int err;
    // this->id = id;
    // err |= clGetPlatformInfo(id, CL_PLATFORM_PROFILE, sizeof(this->platformProfile), this->platformProfile, NULL);
    // err |= clGetPlatformInfo(id, CL_PLATFORM_VERSION, sizeof(this->platformVersion), this->platformVersion, NULL);
    // err |= clGetPlatformInfo(id, CL_PLATFORM_NAME, sizeof(this->platformName), this->platformName, NULL);
    // err |= clGetPlatformInfo(id, CL_PLATFORM_VENDOR, sizeof(this->platformVendor), this->platformVendor, NULL);
    // err |= clGetPlatformInfo(id, CL_PLATFORM_EXTENSIONS, sizeof(this->platformExtensions), this->platformExtensions, NULL);
}


/*info functions*/
clInfo::clInfo(){
    cl_int err;
    // printf("CREATING CLINFO\n");
    this->clPlatformIDs = new cl_platform_id[10];
    err = clGetPlatformIDs(NULL, this->clPlatformIDs, &(this->numPlatforms));
    printf("Found %d platform(s)\n", this->numPlatforms);
    this->clPlatforms = new clPlatform[this->numPlatforms];
    for(int i = 0; i < this->numPlatforms; ++i){
        this->clPlatforms[i].initPlatform(this->clPlatformIDs[i]);
    }
}