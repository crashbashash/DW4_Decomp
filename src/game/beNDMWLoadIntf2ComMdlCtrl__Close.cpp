/* Sends the MODELCTRL message "<infoName> <ramNo> <sequence>" through the controller's messenger
 * and, when `trackClose` is 1, also remembers the request as a beLoadIntf2ComMdlData record on the
 * close list, which Poll later visits until each entry's ISRUN check finishes. */
#include "dw4/igSmartPointer.h"
/* String handles are 4-byte reference fields; the casts give the typed views. */
extern "C" {
int igObject_GetAllocator(...);
int Memory_GetAllocatorBySelector(...);
void *beLoadIntf2ComMdlData__Create(...);
int FUN_002eb010(...);
int StringPool_Construct(...);
const char *StringPool_Intern(...);
int StringChunk_ReleaseHeader(...);
int ObjectList_AppendRetained(...);
int beMessenger_SendNamed(...);
/* "MODELCTRL", the messenger receiver name. */
extern int MODELCTRL[4];
/* lazily created shared string pool */
extern int g_stringPool[4];
/* Default allocator selector, used when byte 0x554c14 is zero. */
extern int g_defaultAllocatorSelector[4];
extern unsigned char GPR_00554c14;
void beNDMWLoadIntf2ComMdlCtrl__Close(beNDMWLoadIntf2ComMdlCtrl *self, int ramNo, const char *infoName, const char *openSequence, unsigned char trackClose);
}
/* Owning stack reference to the new close record: constructed from the creating call and released
 * on scope exit once the close list holds its own reference (reference count in the low 23 bits of
 * _refCount). Its destructor is emitted out of line. */

/* drop one reference on an interned string token; its header (owner, refCount) sits just before the text */
#define RELEASE_STR(s) { int *q = (int *)(s); if (q) { int *h = q - 2; int c = q[-1] - 1; q[-1] = c; if (c == 0) StringChunk_ReleaseHeader(*h, h); } }
void beNDMWLoadIntf2ComMdlCtrl__Close(beNDMWLoadIntf2ComMdlCtrl *self, int ramNo, const char *infoName, const char *openSequence, unsigned char trackClose) {
    beMessenger_SendNamed((void *)self->_messenger, &MODELCTRL[0], infoName, ramNo, openSequence);
    if (trackClose == 1) {
        int base = igObject_GetAllocator(self); /* used as-is when GPR_00554c14 is set, else the default selector's allocator */
        int allocator;
        const char *infoNameToken;
        beLoadIntf2ComMdlData *infoOwner;
        const char *openSequenceToken;
        beLoadIntf2ComMdlData *sequenceOwner;
        if (GPR_00554c14 != 0) { allocator = base; } else { allocator = Memory_GetAllocatorBySelector(g_defaultAllocatorSelector[0]); }
        igSmartPointer<beLoadIntf2ComMdlData> record((beLoadIntf2ComMdlData *)beLoadIntf2ComMdlData__Create(allocator));
        record.p->_ramNo = ramNo;
        infoOwner = record.p;
        if (g_stringPool[0] == 0) {
            int pool = FUN_002eb010(0x10);
            if (pool != 0) pool = StringPool_Construct(pool);
            g_stringPool[0] = pool;
        }
        infoNameToken = StringPool_Intern(g_stringPool[0], infoName);
        RELEASE_STR(infoOwner->_infoName)
        infoOwner->_infoName = (int)infoNameToken;
        sequenceOwner = record.p;
        if (g_stringPool[0] == 0) {
            int pool = FUN_002eb010(0x10);
            if (pool != 0) pool = StringPool_Construct(pool);
            g_stringPool[0] = pool;
        }
        openSequenceToken = StringPool_Intern(g_stringPool[0], openSequence);
        RELEASE_STR(sequenceOwner->_openSQ)
        sequenceOwner->_openSQ = (int)openSequenceToken;
        ObjectList_AppendRetained((void *)self->_closeDataList, record.p);
    }
}
