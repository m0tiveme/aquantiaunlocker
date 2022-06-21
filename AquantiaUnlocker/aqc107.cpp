//
//  aqc107.cpp
//  AquantiaUnlocker
//

#include <Headers/kern_api.hpp>
#include "aqc107.h"

static const char *pathAquantiaAQC107[]        { "/System/Library/Extensions/IONetworkingFamily.kext/Contents/PlugIns/AppleEthernetAquantiaAqtion.kext/Contents/MacOS/AppleEthernetAquantiaAqtion",
};

static KernelPatcher::KextInfo kextAquantiaAQC107 =
    { "com.apple.driver.AppleEthernetAquantiaAqtion", pathAquantiaAQC107, arrsize(pathAquantiaAQC107), {true}, {}, KernelPatcher::KextInfo::Unloaded };

static const char *checkConfigSupportSymbol = "__ZN30AppleEthernetAquantiaAqtion10718checkConfigSupportERiS0_";

void Aqc107::init() {
    lilu.onKextLoadForce(&kextAquantiaAQC107, 1, [](void* user, KernelPatcher& patcher, size_t index, mach_vm_address_t address, size_t size) {
        static_cast<Aqc107*>(user)->processKext(patcher, index, address, size);
    }, this);
}

void Aqc107::processKext(KernelPatcher &patcher, size_t index, mach_vm_address_t address, size_t size) {
    SYSLOG(PLUGIN_AQC, "processing kext %i", index);
    SYSLOG(PLUGIN_AQC, "target kext is %i", kextAquantiaAQC107.loadIndex);
    if (kextAquantiaAQC107.loadIndex == index) {
        KernelPatcher::RouteRequest request(checkConfigSupportSymbol, wrapCheckConfigSupport, this->orgCheckConfigSupport);
        if(!patcher.routeMultiple(index, &request, 1, address, size)) {
            SYSLOG(PLUGIN_AQC, "unable to route checkConfigSupport symbol");
        } else {
            SYSLOG(PLUGIN_AQC, "routed checkConfigSupport successfully");
        }
    }
}

IOReturn Aqc107::wrapCheckConfigSupport(int *arg0, int *arg1) {
    auto original = Aqc107::Instance()->orgCheckConfigSupport;
    //IOReturn result = FunctionCast(wrapCheckConfigSupport, original)(arg0, arg1);
    //SYSLOG(PLUGIN_AQC, "original checkConfigSupport result %i", result);
    IOLog("wrapped checkConfigSupport called");
    kprintf("wrapped checkConfigSupport called");
    SYSLOG(PLUGIN_AQC, "wrapped checkConfigSupport called");
    return kIOReturnSuccess;
}
