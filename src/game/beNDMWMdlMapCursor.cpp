#include "dw4/core/igSmartPointer.h"
#include "dw4/core/StringPool.h"
#include "dw4/game/beBaseInfoDataList.h"
#include "dw4/game/beMessenger.h"
#include "dw4/game/beModelCtrl.h"
#include "dw4/game/beModelCtrlInfoWork.h"
#include "dw4/game/ndmw/beNDMWMdlMapCursor.h"
#include "dw4/core/igDataLists.h"
#include "dw4/maths/igMatrix44f.h"
#include "dw4/core/igMemoryPoolContext.h"
#include "dw4/core/igNamedObject.h"
#include "dw4/core/igObject.h"
#include "dw4/maths/igVec3f.h"
#include <string.h>
#include "dw4/maths/igMathConstants.h"
#include "dw4/support/emptyString.h"

extern "C" unsigned char beNDMWMdlMapCursor_IsKind(int dummy0, const char *kind);
extern "C" int beNDMWMdlMapCursor_GetMeta(void);
/* matching construct: inline retain/release helpers reproduce the retail inlined refcount code */
struct RefCount { static inline void addref(igObject *o) { if (o != 0) o->_refCount = o->_refCount + 1; }
 static inline void release(igObject *o) { if (o != 0) { o->_refCount = o->_refCount - 1; if (((unsigned long long)(long long)o->_refCount & 0x7fffffULL) == 0) igObject_Destroy(o); } } };
/* Owning stack reference to the freshly created data list (reference count in the low 23 bits of
 * _refCount); released on scope exit. */

/* Owning stack reference to the new property value object; released on scope exit. */
class ValueRef {
public:
    beModelCtrlInfoWork *p;
    ValueRef(beModelCtrlInfoWork *o) : p(o) {}
    ~ValueRef() { igObject *o = p; if (o != 0) { --o->_refCount; if ((o->_refCount & 0x7fffff) == 0) igObject_Destroy(o); } }
};
/* Inlined helper shared by the model-controller "apply ram" methods: a ram without a data list gets a
 * fresh beBaseInfoDataList (allocator chosen by the global selector flag).  Being an inlined callee, its
 * list reference is laid out after the caller's own value reference (+0x58 below +0x5c), as retail does. */
struct RamDataList { static inline void Ensure(beBaseInfoRam *ram) {
    if (ram->_dataList == 0) {
        igMemoryPoolView *al = ((Gap::Core::igObject *)ram)->getMemoryPool();
        al = g_useOwnerAllocator ? al : Memory_GetAllocatorBySelector(kIGMemoryPoolHandleUser1);
        igSmartPointer<igObject> list(beBaseInfoDataList_Create((int)al));
        igObject *t = list.p;
        RefCount::addref(t);
        RefCount::release((igObject *)ram->_dataList);
        ram->_dataList = (int)t;
    }
} };
extern "C" void beNDMWMdlMapCursor_OnGenerate(beNDMWMdlMapCursor *self, beBaseInfoRam *ram);
/* matching construct: inline release helper reproduces the retail inlined release of the previous data list */
struct RefRelease { static inline void go(igObject *object) {
    if (object) {
        --object->_refCount;
        if (((unsigned long long)(long long)object->_refCount & 0x7fffffULL) == 0)
            igObject_Destroy(object);
    }
} };
extern "C" void beNDMWMdlMapCursor_OnUpdateRam(beNDMWMdlMapCursor *self, beBaseInfoRam *ram);

#pragma push
#pragma readonly_strings on

unsigned char beNDMWMdlMapCursor_IsKind(int dummy0, const char *kind) {
    return strcmp(kind, "KIND_MAPCURSOR") == 0;
}

void beNDMWMdlMapCursor_OnGenerate(beNDMWMdlMapCursor *self, beBaseInfoRam *ram) {
    beModelCtrlInfoWork *t;
    void *nw;
    beModelCtrlInfoWork *t2;
    igMemoryPoolView *al;
    beModelCtrlInfoRamData *pr;
    const char *s;
    RamDataList::Ensure(ram);
    pr = (beModelCtrlInfoRamData *)igProperty_FindByName((igObjectList *)ram->_dataList, g_propertyNameField, "ONE");
    al = ((Gap::Core::igObject *)self)->getMemoryPool();
    al = g_useOwnerAllocator ? al : Memory_GetAllocatorBySelector(kIGMemoryPoolHandleUser1);
    {
    /* The new value object is owned by the stack reference while it replaces the record's value and
     * takes the messenger's reply; released at the block end, before the model refresh. */
    ValueRef value(beModelCtrlInfoWork_Create((int)al));
    t = value.p;
    RefCount::addref(t);
    RefCount::release((igObject *)pr->_work);
    pr->_work = (int)t;
    if (beMessenger_GetIntCount((beMessenger *)self->_messenger) != 0) {
        s = beMessenger_GetString((beMessenger *)self->_messenger, 0);
        t2 = value.p;
        if (g_stringPool == 0) {
            StringPool *pool = (StringPool *)StringPool_Allocate(16);
            if (pool != 0) pool = StringPool_Construct(pool);
            g_stringPool = pool;
        }
        nw = StringPool_Intern(g_stringPool, s);
        int *oldstr = (int *)t2->_hitParentName;
        if (oldstr != 0) {
            int *hdr = oldstr - 2;
            int c = oldstr[-1] - 1;
            oldstr[-1] = c;
            if (c == 0) StringChunk_ReleaseHeader((StringChunk *)*hdr, (StringTokenHeader *)hdr);
        }
        t2->_hitParentName = (int)nw;
        value.p->_hitParentRamNo = beMessenger_GetInt((beMessenger *)self->_messenger, 0);
    }
    }
    beModelCtrl__OnGenerate((beModelCtrl *)self, ram);
}

void beNDMWMdlMapCursor_OnUpdateRam(beNDMWMdlMapCursor *self, beBaseInfoRam *ram) {
    static const char *openSequences[] = { "SQ_OPEN00", "SQ_OPEN01", "SQ_OPEN02", "SQ_OPEN03" };
    igObject *s0;
    beModelCtrlInfoRamData *r;
    int m1[16];
    int m2[16];
    igVec3f sum;
    igVec3f t;
    bool s2;
    bool s1;
    s2 = false;
    sum[0] = g_vec3Zero[0];
    sum[1] = g_vec3Zero[1];
    sum[2] = g_vec3Zero[2];
    s1 = false;
    beMessenger_SendRam((beMessenger *)self->_messenger, "PLAYER", ram->_ramNo, "GETMATRIX");
    if (beMessenger_GetMatrixCount((beMessenger *)self->_messenger) != 0) {
        beMessenger_GetMatrix(m1, (beMessenger *)self->_messenger, 0);
        igMatrix44f_GetTranslation((const float *)m1, (float *)&sum);
        s2 = true;
    }
    switch (ram->_st0) {
    case 0:
        if (s2) {
            const char *a2 = (const char *)((beBaseInfo *)ram->_parentInfo)->_name;
            int a3 = ram->_ramNo;
            a2 = a2 ? a2 : (const char *)emptyString;
            beMessenger_SendNamed((beMessenger *)self->_messenger, "MODELCTRL", a2, a3, openSequences[a3]);
            s1 = true;
            ram->_st0 = 1;
            ram->_st3 = 0;
            ram->_st2 = 0;
            ram->_st1 = 0;
        }
        break;
    case 1:
        if (!(s2 & 0xFF)) {
            const char *a2 = (const char *)((beBaseInfo *)ram->_parentInfo)->_name;
            int a3 = ram->_ramNo;
            a2 = a2 ? a2 : (const char *)emptyString;
            beMessenger_SendNamed((beMessenger *)self->_messenger, "MODELCTRL", a2, a3, "SQ_CLOSE");
            ram->_st0 = 0;
            ram->_st3 = 0;
            ram->_st2 = 0;
            ram->_st1 = 0;
        }
        s1 = true;
        break;
    }
    if (s1) {
        beMessenger_SendGroup((beMessenger *)self->_messenger, "MAPBASE", "GETMATRIX");
        if (beMessenger_GetMatrixCount((beMessenger *)self->_messenger) != 0) {
            beMessenger_GetMatrix(m2, (beMessenger *)self->_messenger, 0);
            igMatrix44f_GetTranslation((const float *)m2, t.vec);
            sum[0] += t[0];
            sum[1] += t[1];
            sum[2] += t[2];
            if (ram->_dataList == 0) {
                igMemoryPoolView *alloc = ((Gap::Core::igObject *)ram)->getMemoryPool();
                igMemoryPoolView *a;
                if (g_useOwnerAllocator != 0) {
                    a = alloc;
                } else {
                    a = Memory_GetAllocatorBySelector(kIGMemoryPoolHandleUser1);
                }
                igSmartPointer<igObject> ref(beBaseInfoDataList_Create((int)a));
                s0 = ref.p;
                if (s0 != 0) {
                    s0->_refCount++;
                }
                RefRelease::go((igObject *)ram->_dataList);
                ram->_dataList = (int)s0;
            }
            r = (beModelCtrlInfoRamData *)igProperty_FindByName((igObjectList *)ram->_dataList, g_propertyNameField, "ONE");
            sum[1] = 0.0f;
            igMatrix44f_SetTranslation((float *)((char *)r->_node + 32), (const float *)&sum);
        }
    }
}

int beNDMWMdlMapCursor_GetMeta(void)
{
    return (int)g_beNDMWMdlMapCursor_metaObject;
}

#pragma pop

