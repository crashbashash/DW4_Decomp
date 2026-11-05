#include "dw4/reflected.h"
struct BoxF { int vt; unsigned rc; float mn[3]; float mx[3]; };
extern "C" {
void igObject_Destroy(igObject *);
igObject *beBaseInfoDataList_Create(int);
BoxF *FUN_0018a660(int);
int FUN_003908d0(...);
int FUN_00394400(...);
int Memory_GetAllocatorBySelector(...);
int beMessenger_AppendInt(...);
int beMessenger_AppendMatrix(...);
int beMessenger_AppendObject(...);
int beMessenger_AppendString(...);
int beMessenger_DispatchSelected(...);
int beMessenger_GetBoolCount(...);
int beMessenger_SelectGroup(...);
int beMessenger_SetRunCheck(...);
int igObject_GetAllocator(...);
int thunk_FUN_0018ac80(...);
struct PropertyRecord { char p[16]; int f16; beModelCtrlInfoWork *q; };
PropertyRecord *igProperty_FindByName(...);
extern int DAT_004e0858[4];
extern int DAT_0050f410[4];
extern int DAT_0050f420[4];
extern int DAT_0050f430[4];
extern int DAT_0050f440[4];
extern int DAT_0050f450[4];
extern int DAT_0050f460[4];
extern int DAT_00585be0[4];
extern int DAT_00587110[4];
extern float DAT_0058a540[4];
extern unsigned char GPR_00554c14;
extern char GPR_00554e54;
}
struct V3 { float x, y, z; };
struct V4 { float x, y, z, w; };
struct ReleaseRefInline { static inline void go(igObject *object) {
    if (object) {
        --object->_refCount;
        if (((unsigned long long)(long long)object->_refCount & 0x7fffffULL) == 0)
            igObject_Destroy(object);
    }
} };
/* owning reference to the freshly created data list (retail cleanup 0x33e9c0 in the exception table) */
struct ObjectRef { igObject *p; ObjectRef(igObject *o) : p(o) {} ~ObjectRef() { igObject *object = p; if (object) { --object->_refCount; if ((object->_refCount & 0x7fffff) == 0) igObject_Destroy(object); } } };
/* owning reference to the working box (retail cleanup 0x198190 in the exception table) */
struct Ref { BoxF *p; Ref(BoxF *o) : p(o) {} ~Ref() { igObject *object = (igObject *)p; if (object) { --object->_refCount; if (((unsigned long long)(long long)object->_refCount & 0x7fffffULL) == 0) igObject_Destroy(object); } } };

/* matching construct: expression temporary -- the freshly created data list is held by a temporary passed to an
   inline helper, so its frame slot (168) sorts below the box reference (172); a named local took 172 instead. */
struct DataListInit { static inline void go(beBaseInfoRam *arg1, const ObjectRef &tmp) {
        igObject *s0 = tmp.p;
        if (s0 != 0) {
            s0->_refCount++;
        }
        ReleaseRefInline::go((igObject *)arg1->_dataList);
        arg1->_dataList = (int)s0;
} };
extern "C" int Gap__Bec__beModelCtrlSCHitBox__vfunc_21(beModelCtrlSCHitBox *arg0, beBaseInfoRam *arg1);
int Gap__Bec__beModelCtrlSCHitBox__vfunc_21(beModelCtrlSCHitBox *arg0, beBaseInfoRam *arg1) {
    volatile V3 c98;
    V4 sp80;
    igObject *s0;
    PropertyRecord *s2;
    beModelCtrlInfoWork *s1;
    beModelCtrl *m;
    beBaseInfo *info = (beBaseInfo *)arg1->_parentInfo;
    BoxF *t;
    if (arg1->_dataList == 0) {
        int alloc = igObject_GetAllocator(arg1);
        int a;
        if (GPR_00554c14 != 0) {
            a = alloc;
        } else {
            a = Memory_GetAllocatorBySelector(DAT_00587110[0]);
        }
        DataListInit::go(arg1, ObjectRef(beBaseInfoDataList_Create(a)));
    }
    s2 = igProperty_FindByName(arg1->_dataList, DAT_00585be0[0], DAT_0050f410);
    s1 = s2->q;
    m = (beModelCtrl *)arg1->_parentManager;
    int alloc = igObject_GetAllocator(arg0);
    int a;
    if (GPR_00554c14 != 0) {
        a = alloc;
    } else {
        a = Memory_GetAllocatorBySelector(DAT_00587110[0]);
    }
    Ref spAC(FUN_0018a660(a));
    goto L2;
L1:
    thunk_FUN_0018ac80(spAC.p, s2->f16 + 32);
    { t = spAC.p;
    c98.x = t->mn[0] * 0.5f + t->mx[0] * 0.5f;
    c98.y = t->mn[1] * 0.5f + t->mx[1] * 0.5f;
    c98.z = t->mn[2] * 0.5f + t->mx[2] * 0.5f; }
    goto L3;
L1b:
    if (m->_isDebugHitBox != 0 && s1 != 0) {
        int a1 = s1->_debugHitBoxNode;
        if (a1 != 0) {
            if (GPR_00554e54 == 0) {
                DAT_0058a540[0] = 0;
                DAT_0058a540[1] = 0;
                DAT_0058a540[2] = 1.0f;
                DAT_0058a540[3] = 0.5f;
                DAT_0058a540[4] = 1.0f;
                DAT_0058a540[5] = 1.0f;
                DAT_0058a540[8] = 1.0f;
                DAT_0058a540[6] = 0;
                DAT_0058a540[7] = 0.5f;
                DAT_0058a540[11] = 0.5f;
                DAT_0058a540[9] = 0;
                DAT_0058a540[10] = 0;
                GPR_00554e54 = 1;
            }
            {
                float *p = &DAT_0058a540[arg0->_bulletMode * 4];
                sp80.x = p[0]; sp80.y = p[1]; sp80.z = p[2]; sp80.w = p[3];
            }
            FUN_003908d0(m, a1, spAC.p, &sp80);
        }
    }
    switch (arg0->_bulletMode) {
    case 0:
        beMessenger_SelectGroup(m->_messenger, DAT_0050f420);
        break;
    case 1:
        beMessenger_SelectGroup(m->_messenger, DAT_0050f430);
        break;
    default:
        beMessenger_SelectGroup(m->_messenger, DAT_0050f440);
        break;
    }
    beMessenger_AppendInt(m->_messenger, arg0->_kind);
    beMessenger_AppendObject(m->_messenger, spAC.p);
    beMessenger_AppendMatrix(m->_messenger, s2->f16 + 32);
    {
        int a1 = s1->_hitParentName;
        if (a1 == 0) {
            int n = info->_name != 0 ? info->_name : (int)DAT_004e0858;
            beMessenger_AppendString(m->_messenger, n);
            beMessenger_AppendInt(m->_messenger, arg1->_ramNo);
        } else {
            beMessenger_AppendString(m->_messenger, a1);
            beMessenger_AppendInt(m->_messenger, s1->_hitParentRamNo);
        }
    }
    beMessenger_SetRunCheck(m->_messenger, 1);
    beMessenger_DispatchSelected(m->_messenger, DAT_0050f450);
    if (beMessenger_GetBoolCount(m->_messenger) != 0) {
        int a2 = s2->q->_luaBHit;
        if (a2 != 0) {
            int n = info->_name != 0 ? info->_name : (int)DAT_004e0858;
            FUN_00394400(m, arg1, a2, DAT_0050f460, n, 0, 0, 0, 0, 0);
        }
    }
    return 1;
L3:
    { float sx = ((float *)arg0->_boxSize)[0];
      t->mn[0] = c98.x - sx / 2.0f;
      float x2 = c98.x; t = spAC.p; t->mx[0] = sx / 2.0f + x2; }
    { t = spAC.p; float y = *(volatile float *)((char *)&c98 + 4); float h = ((float *)arg0->_boxSize)[1] / 2.0f;
      t->mn[1] = y - h;
      t = spAC.p; t->mx[1] = h + y; }
    { t = spAC.p; float z = *(volatile float *)((char *)&c98 + 8); float h = ((float *)arg0->_boxSize)[2] / 2.0f;
      t->mn[2] = z - h;
      t = spAC.p; t->mx[2] = h + z; }
    goto L1b;
L2:
    { BoxF *t = spAC.p; t->mn[0] = t->mx[0] = ((float *)arg0->_offset)[0]; }
    { float v = ((float *)arg0->_offset)[1]; BoxF *t = spAC.p; t->mx[1] = v; t->mn[1] = v; }
    { BoxF *t = spAC.p; t->mn[2] = t->mx[2] = ((float *)arg0->_offset)[2]; }
    goto L1;
}
