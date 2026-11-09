/* Asks the model controller to play a sequence on a model slot and, when `wait` is 1, remembers
 * the request so the poll can release the caller once ISSEQNAME reports completion. The MODELCTRL
 * message is always sent; only the tracking is conditional. */
#include "dw4/reflected.h"
extern "C" {
int FUN_002eb010(int);
int *beLoadIntf2ComMdlData__Create(int);
int Memory_GetAllocatorBySelector(int);
int ObjectList_AppendRetained(int, beLoadIntf2ComMdlData *);
int StringChunk_ReleaseHeader(int, int *);
int StringPool_Construct(int);
int *StringPool_Intern(int, int *);
int beMessenger_SendNamed(int, int *, int *, int, int *);
int igObject_Destroy(beLoadIntf2ComMdlData *);
int igObject_GetAllocator(beNDMWLoadIntf2ComMdlCtrl *);
extern int MODELCTRL[4];
extern int g_stringPool[4];
/* Default allocator selector. */
extern int g_defaultAllocatorSelector[4];
/* Byte flag at gp-relative 0x554c14: when nonzero the object allocator is used as returned instead
 * of the selector. */
extern unsigned char GPR_00554c14;
void beNDMWLoadIntf2ComMdlCtrl__Play(beNDMWLoadIntf2ComMdlCtrl *self, int slot, int *modelName, int *sequenceName, int wait);
}
/* Only `wait == 1` (low byte) tracks the request; 2 and 255 do not, 257 does. */
#define WAIT_TRACKED 1
/* Owning stack reference to the tracked entry: constructed from the object and released on scope
 * exit (reference count in the low 23 bits of _refCount); the open list owns the entry afterwards.
 * Its destructor is emitted out of line. */
template <class T> class igSmartPointer {
public:
    T *p;
    igSmartPointer(T *o) : p(o) {}
    ~igSmartPointer() { T *o = p; if (o != 0) { --o->_refCount; if ((o->_refCount & 0x7fffff) == 0) igObject_Destroy(o); } }
};
void beNDMWLoadIntf2ComMdlCtrl__Play(beNDMWLoadIntf2ComMdlCtrl *self, int slot, int *modelName, int *sequenceName, int wait) {
    int *interned;
    beLoadIntf2ComMdlData *entry;
    int allocator;
    int objectAllocator;
    int pool;
    int *oldToken;
    int *oldTokenHeader;
    int refCount;
    beMessenger_SendNamed(self->_messenger, MODELCTRL, modelName, slot, sequenceName);
    if ((wait & 0xFF) == WAIT_TRACKED) {
        objectAllocator = igObject_GetAllocator(self);
        if (GPR_00554c14 != 0) {
            allocator = objectAllocator;
        } else {
            allocator = Memory_GetAllocatorBySelector(g_defaultAllocatorSelector[0]);
        }
        igSmartPointer<beLoadIntf2ComMdlData> trackedEntry((beLoadIntf2ComMdlData *)beLoadIntf2ComMdlData__Create(allocator));
        trackedEntry.p->_ramNo = slot;
        entry = trackedEntry.p;
        /* Lazily create the shared string pool, intern the model name and
         * drop the entry's previous token (owner at -8, count at -4). */
        if (g_stringPool[0] == 0) {
            pool = FUN_002eb010(16);
            if (pool != 0) {
                pool = StringPool_Construct(pool);
            }
            g_stringPool[0] = pool;
        }
        interned = StringPool_Intern(g_stringPool[0], modelName);
        oldToken = (int *)entry->_infoName;
        if (oldToken != 0) {
            oldTokenHeader = oldToken - 2;
            refCount = oldToken[-1] - 1;
            oldToken[-1] = refCount;
            if (refCount == 0) {
                StringChunk_ReleaseHeader(*oldTokenHeader, oldTokenHeader);
            }
        }
        entry->_infoName = (int)interned;
        entry = trackedEntry.p;
        /* Same for the sequence name. */
        if (g_stringPool[0] == 0) {
            pool = FUN_002eb010(16);
            if (pool != 0) {
                pool = StringPool_Construct(pool);
            }
            g_stringPool[0] = pool;
        }
        interned = StringPool_Intern(g_stringPool[0], sequenceName);
        oldToken = (int *)entry->_openSQ;
        if (oldToken != 0) {
            oldTokenHeader = oldToken - 2;
            refCount = oldToken[-1] - 1;
            oldToken[-1] = refCount;
            if (refCount == 0) {
                StringChunk_ReleaseHeader(*oldTokenHeader, oldTokenHeader);
            }
        }
        entry->_openSQ = (int)interned;
        ObjectList_AppendRetained(self->_openDataList, trackedEntry.p);
        /* The stack reference is released here; the open list now owns the entry. */
    }
}
