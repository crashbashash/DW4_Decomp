#include "dw4/reflected.h"
/* igMemoryPoolContextInfo: the destructor and the retained-allocator slot setter.
 *
 * A context holds 46 records of 144 bytes starting at +0x14 (clearing them is
 * the 6,624-byte memset in the destructor).  Each record is the allocator bound
 * to that slot, a 128-byte inline name, a descriptor and flag words.  The object
 * header is the igObject vtable word and reference word, followed by a count at
 * +8 (30 after construction, then the highest populated slot + 1), a flag word at
 * +12 and a parent object at +16 that the destructor releases with the igObject
 * reference-count idiom.
 * Evidence: docs/engine/context-lifecycle.md.
 * The views below describe the observed 32-bit layout, not the original C++ spelling. */

struct ContextRecord {
    void *allocator;       /* retained by the slot setter */
    char name[128];        /* 127 characters copied in plus an explicit terminator */
    void *descriptor;
    unsigned storageFlags, flags;
};

/* Dispatch-only view of the context's virtual table: the dummies pad the table so
 * that InitializeRecordNames lands on vtable offset 180 and Clear on offset 212
 * (docs/engine/context-lifecycle.md; the other slots are never called here). */
class ContextVirtuals {
public:
    virtual void slot0();  virtual void slot1();  virtual void slot2();  virtual void slot3();
    virtual void slot4();  virtual void slot5();  virtual void slot6();  virtual void slot7();
    virtual void slot8();  virtual void slot9();  virtual void slot10(); virtual void slot11();
    virtual void slot12(); virtual void slot13(); virtual void slot14(); virtual void slot15();
    virtual void slot16(); virtual void slot17(); virtual void slot18(); virtual void slot19();
    virtual void slot20(); virtual void slot21(); virtual void slot22(); virtual void slot23();
    virtual void slot24(); virtual void slot25(); virtual void slot26(); virtual void slot27();
    virtual void slot28(); virtual void slot29(); virtual void slot30(); virtual void slot31();
    virtual void slot32(); virtual void slot33(); virtual void slot34(); virtual void slot35();
    virtual void slot36(); virtual void slot37(); virtual void slot38(); virtual void slot39();
    virtual void slot40(); virtual void slot41(); virtual void slot42();
    virtual void InitializeRecordNames();  /* 0x002f49e0, vtable offset 180 */
    virtual void slot44(); virtual void slot45(); virtual void slot46(); virtual void slot47();
    virtual void slot48(); virtual void slot49(); virtual void slot50();
    virtual void Clear(int index);         /* vtable offset 212: release the allocator of one record */
};

struct ContextView : igObject {
    int usedRecords;       /* +8: highest populated slot + 1 (30 right after construction) */
    unsigned flags;        /* +12 */
    igObject *parent;      /* +16 */
    ContextRecord records[46];
};

/* vtable of igMemoryPoolContextInfo (published by the constructor at 0x002f25d0) */
extern "C" char g_igMemoryPoolContextInfo_vtable[];
extern "C" void memset(void *, int, unsigned);
extern "C" void igObject_Destroy(void *);
extern "C" void igMemoryPoolContextInfo_DeleteAllocation(void *);

/* 0x002f28d0 (vtable offset 100)
 * Bind `value` to record `index` (0..45).  Re-binding the same object is a
 * no-op; a different old binding is released through Clear first.  The new
 * object is retained, and a non-null binding raises the used-record count. */
extern "C" void Gap__Core__igMemoryPoolContextInfo__vfunc_53(ContextView *self, int index, igObject *value) {
    if (index >= 0 && index < 46) {
        /* record address spelled as index * 144 + self (+ 20 for the allocator word); the
         * typed spelling &self->records[index] changes the bytes */
        unsigned int address = (unsigned int)index * 9; address <<= 4; address += (unsigned int)self;
        igObject **slot = (igObject **)(address + 20);
        igObject *previous = *slot;
        if (!previous || previous != value) {
            if (previous) ((ContextVirtuals *)self)->Clear(index);
            *slot = value;
            if (value) {
                ++value->_refCount;
                if (index >= self->usedRecords) self->usedRecords = index + 1;
            }
        }
    }
}

/* 0x002f2670
 * Destructor: republish the vtable, clear the reference word and all records,
 * rebuild the 46 record names, release the parent, and free the allocation when
 * the low 16 bits of `deleteFlags` are positive (deleting destructor).  Per
 * docs/engine/context-lifecycle.md the parent word is left in place. */
extern "C" void *igMemoryPoolContextInfo_Destruct(ContextView *self, long long deleteFlags) {
    if (self) {
        self->_vtable = (int)g_igMemoryPoolContextInfo_vtable; self->_refCount = 0;
        memset(self->records, 0, 6624); ((ContextVirtuals *)self)->InitializeRecordNames();
        if ((char *)self + 16) {
            igObject *parent = self->parent;
            if (parent) {
                --parent->_refCount;
                if (!(parent->_refCount & 0x7fffff)) igObject_Destroy(parent);
            }
        }
        if ((short)deleteFlags > 0) igMemoryPoolContextInfo_DeleteAllocation(self);
    }
    return self;
}
