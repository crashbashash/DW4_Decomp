#include "dw4/support/reflected.h"
#include "dw4/core/igSmartPointer.h"
#include "dw4/core/StringPool.h"
#include "dw4/game/beBaseInfoDataList.h"
#include "dw4/game/beMessenger.h"
#include "dw4/game/beModelCtrl.h"
#include "dw4/game/beModelCtrlInfoWork.h"
#include "dw4/game/ndmw/beNDMWMdlMapBase.h"
#include "dw4/core/igDataLists.h"
#include "dw4/maths/igMatrix44f.h"
#include "dw4/core/igMemoryPoolContext.h"
#include "dw4/core/igNamedObject.h"
#include "dw4/core/igObject.h"
#include "dw4/maths/igVec3f.h"
#include <string.h>
#include "dw4/maths/igMathConstants.h"

extern "C" unsigned char beNDMWMdlMapBase_IsKind(int dummy0, int kind);
extern "C" int beNDMWMdlMapBase_GetMeta(void);
extern "C" int KIND_MAPBASE[4];
extern "C" char MAPBASE[];
extern "C" void beNDMWMdlMapBase_RegisterReceiver(beNDMWMdlMapBase *self, int info, char *unused);
struct Rel { static inline void go(igObject *o) { igObject *t = o; igObject::release(t); } };
/* Owning stack reference to the slot's new data list; released on scope exit (reference count in
 * the low 23 bits of _refCount). */

/* Owning stack reference to the new map info work; released on scope exit. */
class InfoWorkRef {
public:
    igObject *p;
    InfoWorkRef(igObject *o) : p(o) {}
    ~InfoWorkRef() { igObject *o = p; igObject::release(o); }
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
/* Owning stack reference to the freshly created data list; released on scope exit (reference count
 * in the low 23 bits of _refCount). */

extern "C" void beNDMWMdlMapBase_OnUpdateRam(beNDMWMdlMapBase *self, beBaseInfoRam *ram);

#pragma push
#pragma readonly_strings on

unsigned char beNDMWMdlMapBase_IsKind(int dummy0, int kind) {
    return strcmp((const char *)kind, (const char *)KIND_MAPBASE) == 0;
}

void beNDMWMdlMapBase_RegisterReceiver(beNDMWMdlMapBase *self, int info, char *unused)
{
    beMessenger_RegisterReceiverFromInfo((beMessenger *)self->_messenger, (beBaseInfoRam *)info, MAPBASE);
}

void beNDMWMdlMapBase_OnGenerate(beNDMWMdlMapBase *self, beBaseInfoRam *ram) {
    if (ram->_dataList == 0) {
        igMemoryPoolView *a = ((Gap::Core::igObject *)ram)->getMemoryPool();
        igMemoryPoolView *al = g_useOwnerAllocator != 0 ? a : Memory_GetAllocatorBySelector(kIGMemoryPoolHandleUser1);
        igObject *created = beBaseInfoDataList_Create((int)al);
        /* matching construct: the new list is a temporary bound to the setter's reference parameter (it
         * takes the stack slot below the named info-work reference, as retail's +0x58 does) */
        Slot::adopt(ram, created);
    }
    beModelCtrlInfoRamData *s3 = (beModelCtrlInfoRamData *)((Gap::Core::igObjectList *)ram->_dataList)->search((Gap::Core::igStringMetaField *)g_propertyNameField, "ONE");
    {
        igMemoryPoolView *a2 = ((Gap::Core::igObject *)self)->getMemoryPool();
        igMemoryPoolView *al2 = g_useOwnerAllocator != 0 ? a2 : Memory_GetAllocatorBySelector(kIGMemoryPoolHandleUser1);
        InfoWorkRef w(beModelCtrlInfoWork_Create((int)al2));
        igObject *t2 = w.p;
        if (t2 != 0) t2->_refCount = t2->_refCount + 1;
        Rel::go((igObject *)s3->_work);
        s3->_work = (int)t2;
        if (beMessenger_GetIntCount((beMessenger *)self->_messenger) != 0) {
            const char *str = beMessenger_GetString((beMessenger *)self->_messenger, 0);
            int ns;
            beModelCtrlInfoWork *tg = (beModelCtrlInfoWork *)w.p;
            if (g_stringPool == 0) {
                StringPool *v = (StringPool *)StringPool_Allocate(16);
                if (v != 0) v = StringPool_Construct(v);
                g_stringPool = v;
            }
            ns = (int)StringPool_Intern(g_stringPool, str);
            int old = tg->_hitParentName;
            if (old != 0) {
                int *hdr = (int *)(old - 8);
                int c = hdr[1] - 1;
                hdr[1] = c;
                if (c == 0) StringChunk_ReleaseHeader((StringChunk *)*hdr, (StringTokenHeader *)hdr);
            }
            tg->_hitParentName = ns;
            ((beModelCtrlInfoWork *)w.p)->_hitParentRamNo = beMessenger_GetInt((beMessenger *)self->_messenger, 0);
        }
    }
    beModelCtrl__OnGenerate((beModelCtrl *)self, ram);
}

void beNDMWMdlMapBase_OnUpdateRam(beNDMWMdlMapBase *self, beBaseInfoRam *ram) {
    beModelCtrlInfoRamData *r;
    int m[16];
    igVec3f sum;
    igVec3f t;
    int n, i;
    sum[0] = g_vec3Zero[0];
    sum[1] = g_vec3Zero[1];
    sum[2] = g_vec3Zero[2];
    beMessenger_SendGroup((beMessenger *)self->_messenger, (const char *)PLAYER_10, (const char *)GETMATRIX_8);
    if (beMessenger_GetMatrixCount((beMessenger *)self->_messenger) != 0) {
        n = beMessenger_GetMatrixCount((beMessenger *)self->_messenger);
        for (i = 0; i < n; i++) {
            {
                beMessenger_GetMatrix(m, (beMessenger *)self->_messenger, i);
                igMatrix44f_GetTranslation((const float *)m, t.vec);
                sum[0] += t[0];
                sum[1] += t[1];
                sum[2] += t[2];
            }
        }
        switch (n) {
        case 0: break;
        case 1: break;
        case 2: sum[0] /= 2.0f; sum[2] /= 2.0f; break;
        case 3: sum[0] /= 3.0f; sum[2] /= 3.0f; break;
        case 4: sum[0] /= 4.0f; sum[2] /= 4.0f; break;
        }
        sum[0] = -sum[0];
        sum[1] = 0.0f;
        sum[2] = -sum[2];
    }
    if (ram->_dataList == 0) {
        igMemoryPoolView *alloc = ((Gap::Core::igObject *)ram)->getMemoryPool();
        igMemoryPoolView *a;
        if (g_useOwnerAllocator != 0) {
            a = alloc;
        } else {
            a = Memory_GetAllocatorBySelector(kIGMemoryPoolHandleUser1);
        }
        igSmartPointer<igObject> created(beBaseInfoDataList_Create((int)a));
        igObject *s0 = created.p;
        igObject::ref(s0);
        igObject *old = (igObject *)ram->_dataList;
        igObject::release(old);
        ram->_dataList = (int)s0;
    }
    r = (beModelCtrlInfoRamData *)((Gap::Core::igObjectList *)ram->_dataList)->search((Gap::Core::igStringMetaField *)g_propertyNameField, "ONE");
    igMatrix44f_SetTranslation((float *)((char *)r->_node + 32), (const float *)&sum);
}

int beNDMWMdlMapBase_GetMeta(void)
{
    return (int)g_beNDMWMdlMapBase_metaObject;
}

#pragma pop
