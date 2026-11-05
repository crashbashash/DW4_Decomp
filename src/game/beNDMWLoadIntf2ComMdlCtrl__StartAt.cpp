#include "dw4/reflected.h"
/* The retail unit was C++ with exceptions on (it keeps an exception index record); the function
 * keeps C linkage, the record reference is a C++ stack object (ObjectRef below). */
extern "C" {
int FUN_002eb010(int);
int Memory_GetAllocatorBySelector(int);
int ObjectList_AppendRetained(int, beLoadIntf2ComMdlData *);
int StringChunk_ReleaseHeader(int, struct StringTokenHeader *);
int StringPool_Construct(int);
void *StringPool_Intern(int, int);
int beMessenger_AppendVec3(int, float *);
int beMessenger_DispatchSelected(int, int *);
int beMessenger_SelectReceivers(int, int *, int, int);
int beMessenger_SendNamed(int, int *, int, int, int);
int igObject_Destroy(beLoadIntf2ComMdlData *);
int igObject_GetAllocator(beNDMWLoadIntf2ComMdlCtrl *);
beLoadIntf2ComMdlData *beLoadIntf2ComMdlData__Create(int);
/* Messenger group "MODELCTRL" and message "GENERATE" (data/strings.json). */
extern int s_MODELCTRL_005171f8[4];
extern int s_GENERATE_00517208[4];
extern int g_stringPool_00586f20[4];
/* Default allocator selector (docs/engine/subwindow-preparation.md). */
extern int g_defaultAllocatorSelector_00587110[4];
/* Byte flag at gp-relative 0x554c14: when nonzero the object allocator is used
 * as returned instead of the selector (docs/engine/xdata-controller.md). */
extern unsigned char GPR_00554c14;

/* Header in front of every interned string token: owning chunk, then a full
 * 32-bit reference count (docs/engine/messenger-results.md). */
typedef struct StringTokenHeader {
    int owner;
    int refCount;
} StringTokenHeader;
}

/* Owning stack reference to the new open-request record: constructed from the object and released on
 * scope exit, after the open list has retained it (reference count in the low 23 bits of _refCount).
 * The out-of-line copy the exception table names is the retail body 0x003e3d80
 * (config/SLUS-20836/unit-objects.json, duplicate __dt__9ObjectRefFv). */
class ObjectRef {
public:
    beLoadIntf2ComMdlData *p;
    ObjectRef(beLoadIntf2ComMdlData *o) : p(o) {}
    ~ObjectRef() { beLoadIntf2ComMdlData *o = p; if (o != 0) { --o->_refCount; if ((o->_refCount & 0x7fffff) == 0) igObject_Destroy(o); } }
};

/* 0x003e3e00: ask the MODELCTRL receivers named (infoName, ramNo) to GENERATE
 * at `position`, then send them `openSQ` as a named message.  When
 * `recordOpen` is 1 the request is also remembered as a
 * beLoadIntf2ComMdlData record (ram number, info name, open sequence) on the
 * controller's open list; the two names are interned in the shared string
 * pool, releasing whatever the fresh record held; the creating reference is
 * released when the block ends. */
extern "C" void beNDMWLoadIntf2ComMdlCtrl__StartAt(beNDMWLoadIntf2ComMdlCtrl *self, int ramNo, int infoName, int openSQ, float *position, int recordOpen) {
    struct { float x, y, z; } v3;
    StringTokenHeader *oldNameHeader;
    StringTokenHeader *oldOpenSQHeader;
    int newRefCount;
    int newRefCount2;
    int allocator;
    int pool;
    int pool2;
    void *internedOpenSQ;
    void *internedInfoName;
    void *oldInfoName;
    void *oldOpenSQ;
    beLoadIntf2ComMdlData *record;

    beMessenger_SelectReceivers(self->_messenger, &s_MODELCTRL_005171f8[0], infoName, ramNo);
    v3.x = position[0];
    v3.y = position[1];
    v3.z = position[2];
    beMessenger_AppendVec3(self->_messenger, (float*)&v3);
    beMessenger_DispatchSelected(self->_messenger, &s_GENERATE_00517208[0]);
    beMessenger_SendNamed(self->_messenger, &s_MODELCTRL_005171f8[0], infoName, ramNo, openSQ);
    if ((recordOpen & 0xFF) == 1) {
        int objectAllocator = igObject_GetAllocator(self);
        if (GPR_00554c14 != 0) { allocator = objectAllocator; } else { allocator = Memory_GetAllocatorBySelector(g_defaultAllocatorSelector_00587110[0]); }
        ObjectRef newRecord(beLoadIntf2ComMdlData__Create(allocator));
        newRecord.p->_ramNo = ramNo;
        record = newRecord.p;
        if (g_stringPool_00586f20[0] == 0) {
            pool = FUN_002eb010(0x10);
            if (pool != 0) {
                pool = StringPool_Construct(pool);
            }
            g_stringPool_00586f20[0] = pool;
        }
        internedInfoName = (void *)(StringPool_Intern(g_stringPool_00586f20[0], infoName));
        oldInfoName = (void *)(record->_infoName);
        if (oldInfoName != 0) {
            oldNameHeader = (StringTokenHeader *)((char *)oldInfoName - 8);
            newRefCount = oldNameHeader->refCount - 1;
            oldNameHeader->refCount = newRefCount;
            if (newRefCount == 0) {
                StringChunk_ReleaseHeader(oldNameHeader->owner, oldNameHeader);
            }
        }
        record->_infoName = (int)(internedInfoName);
        record = newRecord.p;
        if (g_stringPool_00586f20[0] == 0) {
            pool2 = FUN_002eb010(0x10);
            if (pool2 != 0) {
                pool2 = StringPool_Construct(pool2);
            }
            g_stringPool_00586f20[0] = pool2;
        }
        internedOpenSQ = (void *)(StringPool_Intern(g_stringPool_00586f20[0], openSQ));
        oldOpenSQ = (void *)(record->_openSQ);
        if (oldOpenSQ != 0) {
            oldOpenSQHeader = (StringTokenHeader *)((char *)oldOpenSQ - 8);
            newRefCount2 = oldOpenSQHeader->refCount - 1;
            oldOpenSQHeader->refCount = newRefCount2;
            if (newRefCount2 == 0) {
                StringChunk_ReleaseHeader(oldOpenSQHeader->owner, oldOpenSQHeader);
            }
        }
        record->_openSQ = (int)(internedOpenSQ);
        ObjectList_AppendRetained(self->_openDataList, newRecord.p);
    }
}
