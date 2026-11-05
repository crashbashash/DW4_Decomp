/* 0x00167210
 * Capability query forwarded to the owned igVisualContext: calls the context's
 * virtual at vtable byte offset 148 (35 slots precede it) and returns its
 * answer, or 0 while no context is attached.  The igGenericCapabilityManager
 * version of this slot (0x00155330) just returns 1, so the slot is a
 * yes/no style query; what exactly the context is asked is not recovered. */
#include "dw4/reflected.h"
extern "C" {

int Gap__Core__igVisualContextCapabilityManager__vfunc_23(igVisualContextCapabilityManager *self);
}
/* Dummy class: igVisualContext virtual at vtable byte offset 148. */
class VisualContextQuerySlot {
public:
    virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4();
    virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9();
    virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14();
    virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19();
    virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24();
    virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29();
    virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34();
    virtual int Query();
};
int Gap__Core__igVisualContextCapabilityManager__vfunc_23(igVisualContextCapabilityManager *self) {
    int result;
    void **visualContext;

    visualContext = (void **)(self->_visualContext);
    result = 0;
    if (visualContext != 0) {
        result = ((VisualContextQuerySlot *)(visualContext))->Query();
    }
    return result;
}
