//
//  kern_start.cpp
//  AquantiaUnlocker
//

#include <Headers/plugin_start.hpp>
#include <Headers/kern_api.hpp>
#include "aqc107.h"

// main function
static void pluginStart() {
    SYSLOG(PLUGIN_AQC, "started AquantiaUnlocker");
    auto aq = Aqc107::Instance();
    aq->init();
}

// Boot args.
static const char *bootargOff[] {
    "-aqoff"
};
static const char *bootargDebug[] {
    "-aqdebug"
};
static const char *bootargBeta[] {
    "-aqbeta"
};

// Plugin configuration.
PluginConfiguration ADDPR(config) {
    xStringify(PRODUCT_NAME),
    parseModuleVersion(xStringify(MODULE_VERSION)),
    LiluAPI::AllowNormal | LiluAPI::AllowInstallerRecovery,
    bootargOff,
    arrsize(bootargOff),
    bootargDebug,
    arrsize(bootargDebug),
    bootargBeta,
    arrsize(bootargBeta),
    KernelVersion::Monterey,
    KernelVersion::Monterey,
    []() {
        pluginStart();
    }
};
