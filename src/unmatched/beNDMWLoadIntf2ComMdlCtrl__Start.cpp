#include "dw4/igSmartPointer.h"
extern "C" {
int FUN_002eb010(int);
int Memory_GetAllocatorBySelector(int);
int ObjectList_AppendRetained(int, beLoadIntf2ComMdlData *);
int StringChunk_ReleaseHeader(int, struct StringTokenHeader *);
int StringPool_Construct(int);
void *StringPool_Intern(int, int);
int beMessenger_SendNamed(int, int *, int, int, int *);
int igObject_GetAllocator(beNDMWLoadIntf2ComMdlCtrl *);
beLoadIntf2ComMdlData *beLoadIntf2ComMdlData__Create(int);
extern int MODELCTRL[4];
extern int GENERATE[4];
extern int g_stringPool[4];
extern int g_defaultAllocatorSelector[4];
extern unsigned char GPR_00554c14;

typedef struct StringTokenHeader {
    int owner;
    int refCount;
} StringTokenHeader;
}

extern "C" void beNDMWLoadIntf2ComMdlCtrl__Start(beNDMWLoadIntf2ComMdlCtrl *self, int ramNo, int infoName, int openSQ, int recordOpen) {
    /* matching construct: declaration-order sweep (40 random orders) — sets the s-register colouring of the reused parameter registers */
    void *internedInfoName;
    int newRefCount;
    StringTokenHeader *oldOpenSQHeader;
    void *oldInfoName;
    StringTokenHeader *oldNameHeader;
    int pool2;
    int newRefCount2;
    int pool;
    void *internedOpenSQ;
    beLoadIntf2ComMdlData *record;
    int allocator;
    void *oldOpenSQ;

    beMessenger_SendNamed(self->_messenger, &MODELCTRL[0], infoName, ramNo, &GENERATE[0]);
    beMessenger_SendNamed(self->_messenger, &MODELCTRL[0], infoName, ramNo, (int *)openSQ);
    if ((recordOpen & 0xFF) == 1) {
        int objectAllocator = igObject_GetAllocator(self);
        if (GPR_00554c14 != 0) { allocator = objectAllocator; } else { allocator = Memory_GetAllocatorBySelector(g_defaultAllocatorSelector[0]); }
        igSmartPointer<beLoadIntf2ComMdlData> newRecord(beLoadIntf2ComMdlData__Create(allocator));
        newRecord.p->_ramNo = ramNo;
        record = newRecord.p;
        if (g_stringPool[0] == 0) {
            pool = FUN_002eb010(0x10);
            if (pool != 0) {
                pool = StringPool_Construct(pool);
            }
            g_stringPool[0] = pool;
        }
        internedInfoName = (void *)(StringPool_Intern(g_stringPool[0], infoName));
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
        if (g_stringPool[0] == 0) {
            pool2 = FUN_002eb010(0x10);
            if (pool2 != 0) {
                pool2 = StringPool_Construct(pool2);
            }
            g_stringPool[0] = pool2;
        }
        internedOpenSQ = (void *)(StringPool_Intern(g_stringPool[0], openSQ));
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
