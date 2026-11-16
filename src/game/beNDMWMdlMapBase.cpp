#include "dw4/reflected.h"
#include "dw4/igSmartPointer.h"

extern "C" int strcmp(int, int *);
extern "C" int beNDMWMdlMapBase_IsKind(int dummy0, int kind);
extern "C" void beMessenger_RegisterReceiverFromInfo(int, int, char *);
extern "C" int StringPool_Allocate(...);
extern "C" void *beModelCtrlInfoWork_Create(...);
extern "C" void * beBaseInfoDataList_Create(...);
extern "C" int beModelCtrl__OnGenerate(...);
extern "C" int Memory_GetAllocatorBySelector(...);
extern "C" int StringChunk_ReleaseHeader(...);
extern "C" int StringPool_Construct(...);
extern "C" void *StringPool_Intern(...);
extern "C" int beMessenger_GetInt(...);
extern "C" int beMessenger_GetIntCount(...);
extern "C" int beMessenger_GetString(...);
extern "C" int igObject_GetAllocator(...);
extern "C" beModelCtrlInfoRamData *igProperty_FindByName(...);
extern "C" int beMessenger_SendGroup(...);
extern "C" int beMessenger_GetMatrixCount(...);
extern "C" int beMessenger_GetMatrix(...);
extern "C" int igMatrix44f_GetTranslation(...);
extern "C" int igMatrix44f_SetTranslation(...);
extern "C" int beNDMWMdlMapBase_GetMeta(void);
extern "C" int KIND_MAPBASE[4];
extern "C" char MAPBASE[];
extern "C" void beNDMWMdlMapBase_RegisterReceiver(beNDMWMdlMapBase *self, int info, char *unused);
extern "C" int g_propertyNameField[4];
extern "C" int g_stringPool[4];
extern "C" int kIGMemoryPoolHandleUser1[4];
extern "C" unsigned char g_useOwnerAllocator;
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
extern "C" void beNDMWMdlMapBase_OnGenerate(beNDMWMdlMapBase *self, beBaseInfoRam *ram);
extern "C" int PLAYER_10[4];
extern "C" int GETMATRIX_8[4];
extern "C" float g_vec3Zero[4];
/* Owning stack reference to the freshly created data list; released on scope exit (reference count
 * in the low 23 bits of _refCount). */

struct Vec3Float { float x, y, z; };
extern "C" void beNDMWMdlMapBase_OnUpdateRam(beNDMWMdlMapBase *self, beBaseInfoRam *ram);
extern "C" int g_beNDMWMdlMapBase_metaObject[4];

#pragma push
#pragma readonly_strings on

int beNDMWMdlMapBase_IsKind(int dummy0, int kind) {
    return strcmp(kind, &KIND_MAPBASE[0]) == 0;
}

void beNDMWMdlMapBase_RegisterReceiver(beNDMWMdlMapBase *self, int info, char *unused)
{
    beMessenger_RegisterReceiverFromInfo(self->_messenger, info, MAPBASE);
}

void beNDMWMdlMapBase_OnGenerate(beNDMWMdlMapBase *self, beBaseInfoRam *ram) {
    if (ram->_dataList == 0) {
        int a = igObject_GetAllocator(ram);
        int al = g_useOwnerAllocator != 0 ? a : Memory_GetAllocatorBySelector(kIGMemoryPoolHandleUser1[0]);
        igObject *created = (igObject *)beBaseInfoDataList_Create(al);
        /* matching construct: the new list is a temporary bound to the setter's reference parameter (it
         * takes the stack slot below the named info-work reference, as retail's +0x58 does) */
        Slot::adopt(ram, created);
    }
    beModelCtrlInfoRamData *s3 = igProperty_FindByName(ram->_dataList, g_propertyNameField[0], "ONE");
    {
        int a2 = igObject_GetAllocator(self);
        int al2 = g_useOwnerAllocator != 0 ? a2 : Memory_GetAllocatorBySelector(kIGMemoryPoolHandleUser1[0]);
        InfoWorkRef w((igObject *)beModelCtrlInfoWork_Create(al2));
        igObject *t2 = w.p;
        if (t2 != 0) t2->_refCount = t2->_refCount + 1;
        Rel::go((igObject *)s3->_work);
        s3->_work = (int)t2;
        if (beMessenger_GetIntCount(self->_messenger) != 0) {
            int str = beMessenger_GetString(self->_messenger, 0);
            int ns;
            beModelCtrlInfoWork *tg = (beModelCtrlInfoWork *)w.p;
            if (g_stringPool[0] == 0) {
                int v = StringPool_Allocate(16);
                if (v != 0) v = StringPool_Construct(v);
                g_stringPool[0] = v;
            }
            ns = (int)StringPool_Intern(g_stringPool[0], str);
            int old = tg->_hitParentName;
            if (old != 0) {
                int *hdr = (int *)(old - 8);
                int c = hdr[1] - 1;
                hdr[1] = c;
                if (c == 0) StringChunk_ReleaseHeader(*hdr, hdr);
            }
            tg->_hitParentName = ns;
            ((beModelCtrlInfoWork *)w.p)->_hitParentRamNo = beMessenger_GetInt(self->_messenger, 0);
        }
    }
    beModelCtrl__OnGenerate(self, ram);
}

void beNDMWMdlMapBase_OnUpdateRam(beNDMWMdlMapBase *self, beBaseInfoRam *ram) {
    beModelCtrlInfoRamData *r;
    int m[16];
    Vec3Float sum;
    Vec3Float t;
    int n, i;
    float *py = &sum.y;
    float *pz = &sum.z;
    sum.x = g_vec3Zero[0];
    *py = g_vec3Zero[1];
    *pz = g_vec3Zero[2];
    beMessenger_SendGroup(self->_messenger, PLAYER_10, GETMATRIX_8);
    if (beMessenger_GetMatrixCount(self->_messenger) != 0) {
        n = beMessenger_GetMatrixCount(self->_messenger);
        for (i = 0; i < n; i++) {
            {
                beMessenger_GetMatrix(m, self->_messenger, i);
                igMatrix44f_GetTranslation(m, &t);
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
    if (ram->_dataList == 0) {
        int alloc = igObject_GetAllocator(ram);
        int a;
        if (g_useOwnerAllocator != 0) {
            a = alloc;
        } else {
            a = Memory_GetAllocatorBySelector(kIGMemoryPoolHandleUser1[0]);
        }
        igSmartPointer<igObject> created(((igObject *)beBaseInfoDataList_Create(a)));
        igObject *s0 = created.p;
        if (s0 != 0) {
            s0->_refCount++;
        }
        igObject *old = (igObject *)ram->_dataList;
        if (old != 0) {
            --old->_refCount;
            if ((old->_refCount & 0x7fffff) == 0) igObject_Destroy(old);
        }
        ram->_dataList = (int)s0;
    }
    r = igProperty_FindByName(ram->_dataList, g_propertyNameField[0], "ONE");
    igMatrix44f_SetTranslation((char *)r->_node + 32, &sum);
}

int beNDMWMdlMapBase_GetMeta(void)
{
    return g_beNDMWMdlMapBase_metaObject[0];
}

#pragma pop
