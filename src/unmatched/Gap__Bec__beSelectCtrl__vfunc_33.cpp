/* reference-counted engine object header: refcount word at +4 */
#include "dw4/reflected.h"
/* matching construct: macro reproduces the retail refcount release sequence inline */
#define REL(o) { igObject *rr = (igObject *)(o); if (rr != 0) { rr->_refCount = (int)rr->_refCount - 1; if (((unsigned long long)((long long)(int)rr->_refCount << 0x29) >> 0x29) == 0) igObject_Destroy(rr); } }
extern "C" {
int FUN_002cb0d0(int);
int FUN_00345680(int);
int FUN_003459a0();
int beBaseInfoDataList_Create(int);
int List_Resize(igBoolList *, int, int);
int Memory_GetAllocatorBySelector(int);
int beMessenger_AppendBool(int, int);
int beMessenger_AppendInt(int, int);
int beMessenger_GetBool(int, int);
int beMessenger_GetBoolCount(int);
int beMessenger_GetInt(int, int);
int beMessenger_GetIntCount(int);
int beMessenger_GetString(int, int);
int beMessenger_GetStringCount(int);
int beMessenger_GetVec3(float *, int, int);
int beMessenger_GetVec3Count(int);
unsigned int beMessenger_ResolveEnumValue(int, int, int);
int igObject_Destroy(igObject *);
int igObject_GetAllocator(void *);
int igProperty_FindByName(int, int, int *);
int igStrCmp(int, int *);
extern float DAT_004e1058[4];
extern float DAT_004e105c[4];
extern float DAT_004e1060[4];
extern int DAT_0050f800[4];
extern int DAT_0050f8d0[4];
extern int DAT_00585be0[4];
extern int DAT_00587110[4];
extern unsigned char GPR_00554c14;
int Gap__Bec__beSelectCtrl__vfunc_33(beSelectCtrl *arg0, beBaseInfoRam *arg1, int arg2);
}
/* Owning stack reference to the freshly created property data list: constructed from the object and
 * released at the end of the full expression that stores it (reference count in the low 23 bits of
 * _refCount).  The out-of-line copy the exception table names is the retail body 0x0033e9c0
 * (config/SLUS-20836/unit-objects.json, duplicate __dt__7ListRefFv). */
class ListRef {
public:
    igObject *p;
    ListRef(igObject *o) : p(o) {}
    ~ListRef() { igObject *o = p; if (o != 0) { --o->_refCount; if ((o->_refCount & 0x7fffff) == 0) igObject_Destroy(o); } }
};
/* Owning stack reference to the select work created on start: released on scope exit.  The
 * out-of-line copy the exception table names is the retail body 0x00345410 (config/SLUS-20836/unit-objects.json,
 * duplicate __dt__7WorkRefFv). */
class WorkRef {
public:
    beSelectCtrlInfoWork *p;
    WorkRef(beSelectCtrlInfoWork *o) : p(o) {}
    ~WorkRef() { beSelectCtrlInfoWork *o = p; if (o != 0) { --o->_refCount; if ((o->_refCount & 0x7fffff) == 0) igObject_Destroy((igObject *)o); } }
};
/* Owning stack reference to a new decide list while it is filled: released on scope exit.  The
 * out-of-line copy the exception table names is the retail body 0x00226990 (config/SLUS-20836/unit-objects.json,
 * duplicate __dt__11BoolListRefFv). */
class BoolListRef {
public:
    igObject *p;
    BoolListRef(igObject *o) : p(o) {}
    ~BoolListRef() { igObject *o = p; if (o != 0) { --o->_refCount; if ((o->_refCount & 0x7fffff) == 0) igObject_Destroy(o); } }
};
/* Store a freshly created data list in the ram, taking the ram's share and dropping the previous list;
 * the caller passes the list as a temporary holder that gives up the creating share at the end of the
 * full expression (matching construct: a temporary takes its frame slot after the named locals). */
struct DataList { static inline void store(beBaseInfoRam *ram, const ListRef &list) {
    igObject *created = list.p;
    if (created != 0) created->_refCount = (int)created->_refCount + 1;
    REL(ram->_dataList)
    ram->_dataList = (int)created;
} };
int Gap__Bec__beSelectCtrl__vfunc_33(beSelectCtrl *arg0, beBaseInfoRam *arg1, int arg2) {
    float sp80[3];
    int n;
    int i;
    int a;
    beSelectCtrlInfoRamData *s3;
    beSelectCtrlInfoWork *s2;
    int i2;
    int v;
    beSelectCtrlInfoWork *u;
    int v2;
    int b2;
    igBoolList *l2;
    int b;
    igObject *t;
    igBoolList *l;
    if (arg1->_dataList == 0) {
        a = igObject_GetAllocator(arg1);
        a = (GPR_00554c14 != 0) ? a : Memory_GetAllocatorBySelector(DAT_00587110[0]);
        DataList::store(arg1, ListRef((igObject *)beBaseInfoDataList_Create(a)));
    }
    s3 = (beSelectCtrlInfoRamData *)igProperty_FindByName(arg1->_dataList, DAT_00585be0[0], DAT_0050f800);
    s2 = (beSelectCtrlInfoWork *)s3->_work;
    switch (beMessenger_ResolveEnumValue(arg0->_messenger, FUN_003459a0(), arg2)) {
    case 0:
        arg1->_isRun = 1;
        arg1->_st0 = 0;
        arg1->_st3 = 0;
        arg1->_st2 = 0;
        arg1->_st1 = 0;
        a = igObject_GetAllocator(arg0);
        a = (GPR_00554c14 != 0) ? a : Memory_GetAllocatorBySelector(DAT_00587110[0]);
        {
            WorkRef work((beSelectCtrlInfoWork *)FUN_00345680(a));
            t = (igObject *)work.p;
            if (t != 0) t->_refCount = (int)t->_refCount + 1;
            REL(s3->_work)
            s3->_work = (int)t;
            u = work.p;
        }
        s3->_selectNo = 0;
        if (beMessenger_GetIntCount(arg0->_messenger) != 0) {
            u->_selectMax = beMessenger_GetInt(arg0->_messenger, 0);
            if (beMessenger_GetIntCount(arg0->_messenger) == 2) {
                s3->_selectNo = beMessenger_GetInt(arg0->_messenger, 1);
            }
        } else {
            u->_selectMax = s3->_maxSelect;
        }
        if (beMessenger_GetVec3Count(arg0->_messenger) != 0) {
            beMessenger_GetVec3(sp80, arg0->_messenger, 0);
            ((float *)u->_offsetPos)[0] = sp80[0];
            ((float *)u->_offsetPos)[1] = sp80[1];
            ((float *)u->_offsetPos)[2] = sp80[2];
        } else {
            ((float *)u->_offsetPos)[0] = DAT_004e1058[0];
            ((float *)u->_offsetPos)[1] = DAT_004e105c[0];
            ((float *)u->_offsetPos)[2] = DAT_004e1060[0];
        }
        if (beMessenger_GetStringCount(arg0->_messenger) != 0) {
            if (igStrCmp(beMessenger_GetString(arg0->_messenger, 0), DAT_0050f8d0) == 0) {
                u->_isCancel = 0;
            }
        }
        n = beMessenger_GetBoolCount(arg0->_messenger);
        if (n != 0 && n == u->_selectMax) {
            a = igObject_GetAllocator(arg0);
            a = (GPR_00554c14 != 0) ? a : Memory_GetAllocatorBySelector(DAT_00587110[0]);
            BoolListRef decide((igObject *)FUN_002cb0d0(a));
            t = decide.p;
            if (t != 0) t->_refCount = (int)t->_refCount + 1;
            REL(u->_decideList)
            u->_decideList = (int)t;
            i = 0;
            if (0 < n) {
                do {
                    v = beMessenger_GetBool(arg0->_messenger, i) & 0xFF;
                    l = (igBoolList *)decide.p;
                    b = l->_count;
                    if (b < l->_capacity) {
                        l->_count = b + 1;
                    } else {
                        List_Resize(l, b + 1, 1);
                    }
                    i += 1;
                    ((unsigned char *)l->_data)[b] = v;
                } while (i < n);
            }
        }
        return 1;
    case 3:
        if (arg1->_isRun != 0) {
            if (arg1->_st0 == 2 || arg1->_st0 == 3) {
                beMessenger_AppendBool(arg0->_messenger, 0);
            } else {
                beMessenger_AppendBool(arg0->_messenger, 1);
            }
        } else {
            beMessenger_AppendBool(arg0->_messenger, 0);
        }
        return 1;
    case 1:
        if (arg1->_isRun != 0) {
            beMessenger_AppendBool(arg0->_messenger, 0);
        } else {
            beMessenger_AppendBool(arg0->_messenger, 1);
        }
        return 1;
    case 2:
        beMessenger_AppendInt(arg0->_messenger, s3->_selectNo);
        return 1;
    case 5:
        if (arg1->_st0 == 1 && arg1->_st1 == 0) {
            beMessenger_AppendBool(arg0->_messenger, 0);
        } else {
            beMessenger_AppendBool(arg0->_messenger, 1);
        }
        return 1;
    case 4:
        if (arg1->_st0 == 1 && arg1->_st1 == 0) {
            s3->_selectNo = 0;
            if (beMessenger_GetIntCount(arg0->_messenger) > 0) {
                s2->_selectMax = beMessenger_GetInt(arg0->_messenger, 0);
                n = beMessenger_GetBoolCount(arg0->_messenger);
                if (n != 0 && n == s2->_selectMax) {
                    a = igObject_GetAllocator(arg0);
                    a = (GPR_00554c14 != 0) ? a : Memory_GetAllocatorBySelector(DAT_00587110[0]);
                    BoolListRef decide((igObject *)FUN_002cb0d0(a));
                    t = decide.p;
                    if (t != 0) t->_refCount = (int)t->_refCount + 1;
                    REL(s2->_decideList)
                    s2->_decideList = (int)t;
                    i2 = 0;
                    if (0 < n) {
                        do {
                            v2 = beMessenger_GetBool(arg0->_messenger, i2) & 0xFF;
                            l2 = (igBoolList *)decide.p;
                            b2 = l2->_count;
                            if (b2 < l2->_capacity) {
                                l2->_count = b2 + 1;
                            } else {
                                List_Resize(l2, b2 + 1, 1);
                            }
                            i2 += 1;
                            ((unsigned char *)l2->_data)[b2] = v2;
                        } while (i2 < n);
                    }
                }
            }
            arg1->_st0 = 0xA;
            arg1->_st3 = 0;
            arg1->_st2 = 0;
            arg1->_st1 = 0;
            beMessenger_AppendBool(arg0->_messenger, 1);
        } else {
            beMessenger_AppendBool(arg0->_messenger, 0);
        }
        return 1;
    case 6:
        s3->_selectNo = -1;
        arg1->_st0 = 2;
        arg1->_st3 = 0;
        arg1->_st2 = 0;
        arg1->_st1 = 0;
    default:
        return 0;
    }
}
