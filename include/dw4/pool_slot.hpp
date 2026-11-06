/* pool_slot.hpp - reference-counted pool slot helpers shared by the Gap::Core visual-context
 * managers (inlined into Gap__Core__igVisualContextCapabilityManager__vfunc_31). igObjectSlotView:
 * a local view of the Alchemy base object (the reflected layout is igObject in dw4/reflected.h;
 * this view adds the one virtual the manager calls). The 23-bit reference count lives in the word
 * at +4 (decrement, then destroy when the masked count reaches zero). The 29 dummy virtuals place
 * vfunc_29 at vtable byte +124 = +0x08 + 4*29 (MWCC puts two header words ahead of the slots),
 * i.e. the project's slot 29. The helpers must stay `static inline` in a header: the retail code
 * expands them in place, and units.py drops static definitions that live in the candidate file. */
#include "dw4/igobject_release.h"

class igObjectSlotView {
public:
    virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28();
    virtual void vfunc_29();
    unsigned int _refCount; /* +4: 23-bit reference count, flags above it */
};

extern "C" {
extern unsigned char GPR_00554c14;
extern int DAT_00587020[4];
extern void igObject_Destroy(igObjectSlotView *o);
extern igObjectSlotView *igObject_GetAllocator(void *self);
extern igObjectSlotView *Memory_GetAllocatorBySelector(int selector);
}
static inline void retain(igObjectSlotView *o)
{
    if (o != 0) {
        o->_refCount = o->_refCount + 1;
    }
}

static inline void release(igObjectSlotView *o)
{
    IG_OBJECT_RELEASE(o);
}

/* Slot fill with a selector fallback: shared pool if present, else the owner's
 * allocator (or the selector's allocator when the engine flag is clear). */
static inline void fill_pool_slot(void *self, igObjectSlotView **slot, igObjectSlotView *shared, int *selector)
{
    igObjectSlotView *p = shared;
    if (p != 0) {
        retain(p);
        release(*slot);
        *slot = p;
    } else {
        igObjectSlotView *a = igObject_GetAllocator(self);
        a = GPR_00554c14 != 0 ? a : Memory_GetAllocatorBySelector(selector[0]);
        if (a != Memory_GetAllocatorBySelector(DAT_00587020[0])) {
            p = igObject_GetAllocator(self);
            p = GPR_00554c14 != 0 ? p : Memory_GetAllocatorBySelector(selector[0]);
            retain(p);
            release(*slot);
            *slot = p;
        } else {
            p = igObject_GetAllocator(self);
            retain(p);
            release(*slot);
            *slot = p;
        }
    }
}

/* Slot fill without a selector: shared pool if present, else the owner's allocator. */
static inline void fill_pool_slot_plain(void *self, igObjectSlotView **slot, igObjectSlotView *shared)
{
    igObjectSlotView *p = shared;
    if (p != 0) {
        retain(p);
        release(*slot);
        *slot = p;
    } else {
        p = igObject_GetAllocator(self);
        retain(p);
        release(*slot);
        *slot = p;
    }
}
