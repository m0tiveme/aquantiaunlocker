//
//  aqc107.h
//  AquantiaUnlocker
//

#ifndef aqc107_h
#define aqc107_h
#include <Headers/kern_api.hpp>

#define PLUGIN_AQC "aqc"

class Aqc107 {
public:
    void init();
    void processKext(KernelPatcher &patcher, size_t index, mach_vm_address_t address, size_t size);
    
    static IOReturn wrapCheckConfigSupport(int* arg0, int* arg1);
    
    static Aqc107* Instance() {
        if(Aqc107::instance == nullptr) {
            Aqc107::instance = new Aqc107;
        }
        return Aqc107::instance;
    }
    
private:
    static Aqc107 *instance;
    
    mach_vm_address_t orgCheckConfigSupport;
};

#endif /* aqc107_h */
