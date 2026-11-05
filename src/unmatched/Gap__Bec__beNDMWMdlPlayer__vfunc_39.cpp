#include "dw4/reflected.h"
extern "C" {
void igObject_Destroy(igObject *);
igObject *beBaseInfoDataList_Create(...);
int FUN_002eb010(...);
int FUN_00395250(...);
int Memory_GetAllocatorBySelector(...);
int StringChunk_ReleaseHeader(...);
int StringPool_Construct(...);
int *StringPool_Intern(...);
int beMessenger_GetBool(...);
int beMessenger_SendNamed(...);
bePadData *bePadManager_GetPadForPlayer(...);
int igObject_GetAllocator(...);
int igStrCmp(...);
struct PropertyRecord { char header[20]; beNDMWMdlPlayerInfoWork *value; };
PropertyRecord *igProperty_FindByName(...);
extern int DAT_004e0858[4];
extern int DAT_00516110[4];
extern int DAT_00516270[4];
extern int DAT_00516278[4];
extern int DAT_00516280[4];
extern int DAT_00516290[4];
extern int DAT_00516298[4];
extern int DAT_005162a0[4];
extern int DAT_00585be0[4];
extern int DAT_00586f20[4];
extern int DAT_00587110[4];
extern unsigned char GPR_00554c14;
void Gap__Bec__beNDMWMdlPlayer__vfunc_39(beNDMWMdlPlayer *arg0, beBaseInfoRam *arg1);
}
/* matching construct: inline release helper reproduces the retail release sequence */
struct ReleaseRef { static inline void go(igObject *object) {
    if (object) {
        --object->_refCount;
        if (((unsigned long long)(long long)object->_refCount & 0x7fffffULL) == 0)
            igObject_Destroy(object);
    }
} };
/* matching construct: dummy-virtual class: filler virtual slots place vX at the retail vtable offset */
struct MdlPlayerVirtualSlots { virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void vX(void *, void *);};
/* Owning stack reference to the freshly created property list: constructed from the creating call and
 * released on scope exit once the ram holds its own reference (reference count in the low 23 bits of
 * _refCount).  The out-of-line copy the exception table names is the retail body 0x0033e9c0
 * (config/SLUS-20836/unit-objects.json, duplicate __dt__9ObjectRefFv). */
class ObjectRef {
public:
    igObject *p;
    ObjectRef(igObject *o) : p(o) {}
    ~ObjectRef() { igObject *o = p; if (o != 0) { --o->_refCount; if ((o->_refCount & 0x7fffff) == 0) igObject_Destroy(o); } }
};
void Gap__Bec__beNDMWMdlPlayer__vfunc_39(beNDMWMdlPlayer *arg0, beBaseInfoRam *arg1) {
    igObject *t0;
    beBaseInfo *s1;
    beNDMWMdlPlayerInfoWork *s0;
    int s4;
    /* matching construct: separate per-arm ni/old locals, declared in this order, fix register allocation */
    int *ni1;
    int *ni2;
    int *ni3;
    int *old1;
    int *old2;
    int *old3;
    int *a2;
    int a3;
    s1 = (beBaseInfo *)arg1->_parentInfo;
    if (arg1->_dataList == 0) {
        int alloc = igObject_GetAllocator(arg1);
        int a;
        if (GPR_00554c14 != 0) {
            a = alloc;
        } else {
            a = Memory_GetAllocatorBySelector(DAT_00587110[0]);
        }
        ObjectRef created(beBaseInfoDataList_Create(a));
        t0 = created.p;
        if (t0 != 0) {
            t0->_refCount++;
        }
        ReleaseRef::go((igObject *)arg1->_dataList);
        arg1->_dataList = (int)t0;
    }
    s0 = igProperty_FindByName((void *)arg1->_dataList, DAT_00585be0[0], DAT_00516110)->value;
    s4 = 0;
    if (s0->_isOnCtrl != 0) {
        s4 = bePadManager_GetPadForPlayer(arg0->_padManager, arg1->_ramNo)->_button;
    }
    if (igStrCmp(s0->_wCheckName, DAT_00516270) == 0) {
        switch (s0->_wCheckSt) {
        case 0:
            s0->_wCheckMode = 0;
            s0->_wCheckSt = 1;
        case 1:
            if (!(s4 & 0x4000)) {
                s0->_wCheckMode = 1;
            }
            a2 = (int *)s1->_name;
            a3 = arg1->_ramNo;
            a2 = a2 ? a2 : DAT_004e0858;
            beMessenger_SendNamed(arg0->_messenger, DAT_00516278, a2, a3, DAT_00516280);
            if (beMessenger_GetBool(arg0->_messenger, 0) != 0) {
                if (DAT_00586f20[0] == 0) {
                    int n = FUN_002eb010(16);
                    if (n != 0) n = StringPool_Construct(n);
                    DAT_00586f20[0] = n;
                }
                ni1 = StringPool_Intern(DAT_00586f20[0], 0);
                old1 = (int *)s0->_wCheckName;
                if (old1 != 0) {
                    int *hd = old1 - 2;
                    int c = old1[-1] - 1;
                    old1[-1] = c;
                    if (c == 0) StringChunk_ReleaseHeader(*hd, hd);
                }
                s0->_wCheckName = (int)ni1;
                s0->_wCheckSt = 0;
                if (s0->_wCheckMode == 0) {
                    FUN_00395250(arg0, s1, arg1, s0);
                    return;
                }
                ((MdlPlayerVirtualSlots *)arg0)->vX(arg1, DAT_00516290);
                return;
            }
            break;
        }
    } else if (igStrCmp(s0->_wCheckName, DAT_00516298) == 0) {
        if (!(s4 & 0x4000)) {
            ((MdlPlayerVirtualSlots *)arg0)->vX(arg1, DAT_00516290);
        }
        a2 = (int *)s1->_name;
        a3 = arg1->_ramNo;
        a2 = a2 ? a2 : DAT_004e0858;
        beMessenger_SendNamed(arg0->_messenger, DAT_00516278, a2, a3, DAT_00516280);
        if (beMessenger_GetBool(arg0->_messenger, 0) != 0) {
            if (DAT_00586f20[0] == 0) {
                int n = FUN_002eb010(16);
                if (n != 0) n = StringPool_Construct(n);
                DAT_00586f20[0] = n;
            }
            ni2 = StringPool_Intern(DAT_00586f20[0], 0);
            old2 = (int *)s0->_wCheckName;
            if (old2 != 0) {
                int *hd = old2 - 2;
                int c = old2[-1] - 1;
                old2[-1] = c;
                if (c == 0) StringChunk_ReleaseHeader(*hd, hd);
            }
            s0->_wCheckName = (int)ni2;
            FUN_00395250(arg0, s1, arg1, s0);
        }
    } else if (igStrCmp(s0->_wCheckName, DAT_005162a0) == 0 && !(s4 & 0x4000)) {
        if (DAT_00586f20[0] == 0) {
            int n = FUN_002eb010(16);
            if (n != 0) n = StringPool_Construct(n);
            DAT_00586f20[0] = n;
        }
        ni3 = StringPool_Intern(DAT_00586f20[0], 0);
        old3 = (int *)s0->_wCheckName;
        if (old3 != 0) {
            int *hd = old3 - 2;
            int c = old3[-1] - 1;
            old3[-1] = c;
            if (c == 0) StringChunk_ReleaseHeader(*hd, hd);
        }
        s0->_wCheckName = (int)ni3;
        FUN_00395250(arg0, s1, arg1, s0);
    }
}
