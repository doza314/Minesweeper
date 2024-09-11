#include "NSB.h"

std::string getResourcePath(std::string& resourceName, std::string& resourceType) {
    CFBundleRef mainBundle = CFBundleGetMainBundle();  // Get the app's main bundle
    CFStringRef cfResourceName = CFStringCreateWithCString(NULL, resourceName.c_str(), kCFStringEncodingUTF8);
    CFStringRef cfResourceType = CFStringCreateWithCString(NULL, resourceType.c_str(), kCFStringEncodingUTF8);
    
    CFURLRef resourceURL = CFBundleCopyResourceURL(mainBundle, cfResourceName, cfResourceType, NULL);
    
    if (resourceURL) {
        CFStringRef resourcePath = CFURLCopyFileSystemPath(resourceURL, kCFURLPOSIXPathStyle);
        char path[1024];
        CFStringGetCString(resourcePath, path, sizeof(path), kCFStringEncodingUTF8);
        return std::string(path);
    }
    return "";
}

