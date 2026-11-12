#include "dw4/reflected.h"
#include "dw4/igSmartPointer.h"

extern "C" int strcmp(int, int *);
extern "C" int Gap__Bec__beNDMWMdlMapBase__vfunc_35(int dummy0, int arg1);
extern "C" void beMessenger_RegisterReceiverFromInfo(int, int, char *);
extern "C" int FUN_002eb010(...);
extern "C" void *FUN_00350020(...);
extern "C" void * beBaseInfoDataList_Create(...);
extern "C" int FUN_00396740(...);
extern "C" int Memory_GetAllocatorBySelector(...);
extern "C" int StringChunk_ReleaseHeader(...);
extern "C" int StringPool_Construct(...);
extern "C" void *StringPool_Intern(...);
extern "C" int beMessenger_GetInt(...);
extern "C" int beMessenger_GetIntCount(...);
extern "C" int beMessenger_GetString(...);
extern "C" int igObject_GetAllocator(...);
extern "C" void * igProperty_FindByName(...);
extern "C" int beMessenger_SendGroup(...);
extern "C" int beMessenger_GetMatrixCount(...);
extern "C" int beMessenger_GetMatrix(...);
extern "C" int Matrix44_GetTranslation(...);
extern "C" int Matrix44_SetTranslation(...);
extern "C" int Gap__Bec__beNDMWMdlMapBase__vfunc_20(void);
extern "C" int DAT_0051db90[4];
extern "C" char DAT_0051dba0[];
extern "C" void Gap__Bec__beNDMWMdlMapBase__vfunc_37(beNDMWMdlMapBase * p0, int p1, char * p2);
extern "C" int DAT_0051dba8[4];
extern "C" int g_propertyNameField[4];
extern "C" int g_stringPool[4];
extern "C" int g_defaultAllocatorSelector[4];
extern "C" unsigned char GPR_00554c14;
/* Property record: reference at +20. */
struct Prop { char pad[20]; igObject *f20; };
struct Tgt { char pad[220]; int f220; int f224; };
struct Rel { static inline void go(igObject *o) { igObject *t = o; if (t != 0) { --t->_refCount; if ((t->_refCount & 0x7fffff) == 0) igObject_Destroy(t); } } };
/* Owning stack reference to the slot's new data list; released on scope exit (reference count in
 * the low 23 bits of _refCount). */

/* Owning stack reference to the new map info work; released on scope exit. */
class InfoWorkRef {
public:
    igObject *p;
    InfoWorkRef(igObject *o) : p(o) {}
    ~InfoWorkRef() { igObject *o = p; if (o != 0) { --o->_refCount; if ((o->_refCount & 0x7fffff) == 0) igObject_Destroy(o); } }
};
struct Slot { static inline void setDataList(beBaseInfoRam *ram, const igSmartPointer<igObject> &r) {
    igObject *t = r.p;
    if (t != 0) t->_refCount = t->_refCount + 1;
    Rel::go((igObject *)ram->_dataList);
    ram->_dataList = (int)t;
}
static inline void adopt(beBaseInfoRam *ram, igObject *created) { igSmartPointer<igObject> list(created); setDataList(ram, list); }
};
extern "C" void Gap__Bec__beNDMWMdlMapBase__vfunc_36(beNDMWMdlMapBase *arg0, beBaseInfoRam *arg1);
struct PropertyRecord { char p[16]; int f16; };
extern "C" int DAT_0051dbb0[4];
extern "C" int DAT_0051dbb8[4];
extern "C" float g_vec3Zero[4];
extern "C" float DAT_004e105c[4];
extern "C" float DAT_004e1060[4];
/* Owning stack reference to the freshly created data list; released on scope exit (reference count
 * in the low 23 bits of _refCount). */

struct Vec3Float { float x, y, z; };
struct RamInfoArg { char p0[40]; igObject *m40; };
extern "C" void Gap__Bec__beNDMWMdlMapBase__vfunc_46(beNDMWMdlMapBase *arg0, RamInfoArg *arg1);
extern "C" int g_beNDMWMdlMapBase_metaObject[4];

int Gap__Bec__beNDMWMdlMapBase__vfunc_35(int dummy0, int arg1) {
    return strcmp(arg1, &DAT_0051db90[0]) == 0;
}

void Gap__Bec__beNDMWMdlMapBase__vfunc_37(beNDMWMdlMapBase * p0, int p1, char * p2)
{
    beMessenger_RegisterReceiverFromInfo(p0->_messenger, p1, DAT_0051dba0);
}

void Gap__Bec__beNDMWMdlMapBase__vfunc_36(beNDMWMdlMapBase *arg0, beBaseInfoRam *arg1) {
    if (arg1->_dataList == 0) {
        int a = igObject_GetAllocator(arg1);
        int al = GPR_00554c14 != 0 ? a : Memory_GetAllocatorBySelector(g_defaultAllocatorSelector[0]);
        igObject *created = (igObject *)beBaseInfoDataList_Create(al);
        /* matching construct: the new list is a temporary bound to the setter's reference parameter (it
         * takes the stack slot below the named info-work reference, as retail's +0x58 does) */
        Slot::adopt(arg1, created);
    }
    Prop *s3 = (Prop *)igProperty_FindByName(arg1->_dataList, g_propertyNameField[0], DAT_0051dba8);
    {
        int a2 = igObject_GetAllocator(arg0);
        int al2 = GPR_00554c14 != 0 ? a2 : Memory_GetAllocatorBySelector(g_defaultAllocatorSelector[0]);
        InfoWorkRef w((igObject *)FUN_00350020(al2));
        igObject *t2 = w.p;
        if (t2 != 0) t2->_refCount = t2->_refCount + 1;
        Rel::go(s3->f20);
        s3->f20 = t2;
        if (beMessenger_GetIntCount(arg0->_messenger) != 0) {
            int str = beMessenger_GetString(arg0->_messenger, 0);
            int ns;
            Tgt *tg = (Tgt *)w.p;
            if (g_stringPool[0] == 0) {
                int v = FUN_002eb010(16);
                if (v != 0) v = StringPool_Construct(v);
                g_stringPool[0] = v;
            }
            ns = (int)StringPool_Intern(g_stringPool[0], str);
            int old = tg->f220;
            if (old != 0) {
                int *hdr = (int *)(old - 8);
                int c = hdr[1] - 1;
                hdr[1] = c;
                if (c == 0) StringChunk_ReleaseHeader(*hdr, hdr);
            }
            tg->f220 = ns;
            ((Tgt *)w.p)->f224 = beMessenger_GetInt(arg0->_messenger, 0);
        }
    }
    FUN_00396740(arg0, arg1);
}

void Gap__Bec__beNDMWMdlMapBase__vfunc_46(beNDMWMdlMapBase *arg0, RamInfoArg *arg1) {
    PropertyRecord *r;
    int m[16];
    Vec3Float sum;
    Vec3Float t;
    int n, i;
    float *py = &sum.y;
    float *pz = &sum.z;
    sum.x = g_vec3Zero[0];
    *py = DAT_004e105c[0];
    *pz = DAT_004e1060[0];
    beMessenger_SendGroup(arg0->_messenger, DAT_0051dbb0, DAT_0051dbb8);
    if (beMessenger_GetMatrixCount(arg0->_messenger) != 0) {
        n = beMessenger_GetMatrixCount(arg0->_messenger);
        for (i = 0; i < n; i++) {
            {
                beMessenger_GetMatrix(m, arg0->_messenger, i);
                Matrix44_GetTranslation(m, &t);
                sum.x += t.x;
                *py += t.y;
                *pz += t.z;
            }
        }
        switch (n) {
        case 0: break;
        case 1: break;
        case 2: sum.x /= 2.0f; *pz /= 2.0f; break;
        case 3: sum.x /= 3.0f; *pz /= 3.0f; break;
        case 4: sum.x /= 4.0f; *pz /= 4.0f; break;
        }
        sum.x = -sum.x;
        *py = 0.0f;
        *pz = -*pz;
    }
    if (arg1->m40 == 0) {
        int alloc = igObject_GetAllocator(arg1);
        int a;
        if (GPR_00554c14 != 0) {
            a = alloc;
        } else {
            a = Memory_GetAllocatorBySelector(g_defaultAllocatorSelector[0]);
        }
        igSmartPointer<igObject> created(((igObject *)beBaseInfoDataList_Create(a)));
        igObject *s0 = created.p;
        if (s0 != 0) {
            s0->_refCount++;
        }
        igObject *old = arg1->m40;
        if (old != 0) {
            --old->_refCount;
            if ((old->_refCount & 0x7fffff) == 0) igObject_Destroy(old);
        }
        arg1->m40 = s0;
    }
    r = ((PropertyRecord *)igProperty_FindByName(arg1->m40, g_propertyNameField[0], DAT_0051dba8));
    Matrix44_SetTranslation(r->f16 + 32, &sum);
}

int Gap__Bec__beNDMWMdlMapBase__vfunc_20(void)
{
    return g_beNDMWMdlMapBase_metaObject[0];
}

