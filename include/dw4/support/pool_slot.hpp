/* Reference-counted pool slot helpers shared by the Gap::Core visual-context managers.
 * igObjectSlotView is a local view of igObject that adds the one virtual the manager calls. The 23-bit
 * reference count lives in the word at +4 (decrement, then destroy when the masked count reaches zero).
 * The 29 dummy virtuals place vfunc_29 at vtable byte +124 = +0x08 + 4*29 (MWCC puts two header words
 * ahead of the slots). The helpers must stay `static inline` in a header so they expand in place. */
#include "dw4/core/igobject_release.h"
#include "dw4/core/igObject.h"
#include "dw4/core/igMemoryPoolContext.h"

class igObjectSlotView {
public:
    virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28();
    virtual void vfunc_29();
    unsigned int _refCount; /* +4: 23-bit reference count, flags above it */
};

static inline void igObject_Destroy(igObjectSlotView *object) { igObject_Destroy((igObject *)object); }

/* The pool allocators, seen through the slot view the manager's slots hold. */
static inline igObjectSlotView *slot_owner_allocator(void *self) { return (igObjectSlotView *)((Gap::Core::igObject *)self)->getMemoryPool(); }
static inline igObjectSlotView *slot_selector_allocator(int selector) { return (igObjectSlotView *)Memory_GetAllocatorBySelector(selector); }

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
        igObjectSlotView *a = slot_owner_allocator(self);
        a = g_useOwnerAllocator != 0 ? a : slot_selector_allocator(selector[0]);
        if (a != slot_selector_allocator(kIGMemoryPoolHandleDefault)) {
            p = slot_owner_allocator(self);
            p = g_useOwnerAllocator != 0 ? p : slot_selector_allocator(selector[0]);
            retain(p);
            release(*slot);
            *slot = p;
        } else {
            p = slot_owner_allocator(self);
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
        p = slot_owner_allocator(self);
        retain(p);
        release(*slot);
        *slot = p;
    }
}
