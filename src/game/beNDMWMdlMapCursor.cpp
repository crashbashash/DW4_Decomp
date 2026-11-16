#include "dw4/igSmartPointer.h"

extern "C" int strcmp(const char *, const char *);
extern "C" int beNDMWMdlMapCursor_IsKind(int dummy0, const char *kind);
extern "C" int igObject_GetAllocator(...);
extern "C" int Memory_GetAllocatorBySelector(...);
extern "C" int StringChunk_ReleaseHeader(int, int *);
extern "C" int StringPool_Construct(int);
extern "C" void *StringPool_Intern(int, int);
extern "C" int StringPool_Allocate(int);
extern "C" int beModelCtrl__OnGenerate(void *, void *);
extern "C" int beMessenger_GetInt(int, int);
extern "C" int beMessenger_GetIntCount(int);
extern "C" int beMessenger_GetString(int, int);
extern "C" int beMessenger_SendGroup(...);
extern "C" int beMessenger_SendNamed(...);
extern "C" int beMessenger_SendRam(...);
extern "C" int beMessenger_GetMatrixCount(...);
extern "C" int beMessenger_GetMatrix(...);
extern "C" int igMatrix44f_GetTranslation(...);
extern "C" int igMatrix44f_SetTranslation(...);
extern "C" int beNDMWMdlMapCursor_GetMeta(void);
extern "C" igObject *beBaseInfoDataList_Create(int);
extern "C" beModelCtrlInfoWork *beModelCtrlInfoWork_Create(int);
extern "C" beModelCtrlInfoRamData *igProperty_FindByName(...);
extern "C" int g_propertyNameField[4];
extern "C" int g_stringPool[4];
extern "C" int kIGMemoryPoolHandleUser1[4];
extern "C" unsigned char g_useOwnerAllocator;
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
        int al = igObject_GetAllocator(ram);
        al = g_useOwnerAllocator ? al : Memory_GetAllocatorBySelector(kIGMemoryPoolHandleUser1[0]);
        igSmartPointer<igObject> list(beBaseInfoDataList_Create(al));
        igObject *t = list.p;
        RefCount::addref(t);
        RefCount::release((igObject *)ram->_dataList);
        ram->_dataList = (int)t;
    }
} };
extern "C" void beNDMWMdlMapCursor_OnGenerate(beNDMWMdlMapCursor *self, beBaseInfoRam *ram);
extern "C" int emptyString[4];
extern "C" float g_vec3Zero[4];
/* matching construct: inline release helper reproduces the retail inlined release of the previous data list */
struct RefRelease { static inline void go(igObject *object) {
    if (object) {
        --object->_refCount;
        if (((unsigned long long)(long long)object->_refCount & 0x7fffffULL) == 0)
            igObject_Destroy(object);
    }
} };
struct Vec3f { float x, y, z; };
extern "C" void beNDMWMdlMapCursor_OnUpdateRam(beNDMWMdlMapCursor *self, beBaseInfoRam *ram);
extern "C" int g_beNDMWMdlMapCursor_metaObject[4];

#pragma push
#pragma readonly_strings on

int beNDMWMdlMapCursor_IsKind(int dummy0, const char *kind) {
    return strcmp(kind, "KIND_MAPCURSOR") == 0;
}

void beNDMWMdlMapCursor_OnGenerate(beNDMWMdlMapCursor *self, beBaseInfoRam *ram) {
    beModelCtrlInfoWork *t;
    void *nw;
    beModelCtrlInfoWork *t2;
    int al;
    beModelCtrlInfoRamData *pr;
    int s;
    RamDataList::Ensure(ram);
    pr = igProperty_FindByName(ram->_dataList, g_propertyNameField[0], "ONE");
    al = igObject_GetAllocator(self);
    al = g_useOwnerAllocator ? al : Memory_GetAllocatorBySelector(kIGMemoryPoolHandleUser1[0]);
    {
    /* The new value object is owned by the stack reference while it replaces the record's value and
     * takes the messenger's reply; released at the block end, before the model refresh. */
    ValueRef value(beModelCtrlInfoWork_Create(al));
    t = value.p;
    RefCount::addref(t);
    RefCount::release((igObject *)pr->_work);
    pr->_work = (int)t;
    if (beMessenger_GetIntCount(self->_messenger) != 0) {
        s = beMessenger_GetString(self->_messenger, 0);
        t2 = value.p;
        if (g_stringPool[0] == 0) {
            int pool = StringPool_Allocate(16);
            if (pool != 0) pool = StringPool_Construct(pool);
            g_stringPool[0] = pool;
        }
        nw = StringPool_Intern(g_stringPool[0], s);
        int *oldstr = (int *)t2->_hitParentName;
        if (oldstr != 0) {
            int *hdr = oldstr - 2;
            int c = oldstr[-1] - 1;
            oldstr[-1] = c;
            if (c == 0) StringChunk_ReleaseHeader(*hdr, hdr);
        }
        t2->_hitParentName = (int)nw;
        value.p->_hitParentRamNo = beMessenger_GetInt(self->_messenger, 0);
    }
    }
    beModelCtrl__OnGenerate(self, ram);
}

void beNDMWMdlMapCursor_OnUpdateRam(beNDMWMdlMapCursor *self, beBaseInfoRam *ram) {
    static const char *openSequences[] = { "SQ_OPEN00", "SQ_OPEN01", "SQ_OPEN02", "SQ_OPEN03" };
    igObject *s0;
    beModelCtrlInfoRamData *r;
    int m1[16];
    int m2[16];
    Vec3f sum;
    Vec3f t;
    bool s2;
    bool s1;
    float *py = &sum.y;
    float *pz = &sum.z;
    s2 = false;
    sum.x = g_vec3Zero[0];
    *py = g_vec3Zero[1];
    *pz = g_vec3Zero[2];
    s1 = false;
    beMessenger_SendRam(self->_messenger, "PLAYER", ram->_ramNo, "GETMATRIX");
    if (beMessenger_GetMatrixCount(self->_messenger) != 0) {
        beMessenger_GetMatrix(m1, self->_messenger, 0);
        igMatrix44f_GetTranslation(m1, &sum);
        s2 = true;
    }
    switch (ram->_st0) {
    case 0:
        if (s2) {
            int a2 = ((beBaseInfo *)ram->_parentInfo)->_name;
            int a3 = ram->_ramNo;
            a2 = a2 ? a2 : (int)emptyString;
            beMessenger_SendNamed(self->_messenger, "MODELCTRL", a2, a3, openSequences[a3]);
            s1 = true;
            ram->_st0 = 1;
            ram->_st3 = 0;
            ram->_st2 = 0;
            ram->_st1 = 0;
        }
        break;
    case 1:
        if (!(s2 & 0xFF)) {
            int a2 = ((beBaseInfo *)ram->_parentInfo)->_name;
            int a3 = ram->_ramNo;
            a2 = a2 ? a2 : (int)emptyString;
            beMessenger_SendNamed(self->_messenger, "MODELCTRL", a2, a3, "SQ_CLOSE");
            ram->_st0 = 0;
            ram->_st3 = 0;
            ram->_st2 = 0;
            ram->_st1 = 0;
        }
        s1 = true;
        break;
    }
    if (s1) {
        beMessenger_SendGroup(self->_messenger, "MAPBASE", "GETMATRIX");
        if (beMessenger_GetMatrixCount(self->_messenger) != 0) {
            beMessenger_GetMatrix(m2, self->_messenger, 0);
            igMatrix44f_GetTranslation(m2, &t);
            sum.x += t.x;
            *py += t.y;
            *pz += t.z;
            if (ram->_dataList == 0) {
                int alloc = igObject_GetAllocator(ram);
                int a;
                if (g_useOwnerAllocator != 0) {
                    a = alloc;
                } else {
                    a = Memory_GetAllocatorBySelector(kIGMemoryPoolHandleUser1[0]);
                }
                igSmartPointer<igObject> ref(beBaseInfoDataList_Create(a));
                s0 = ref.p;
                if (s0 != 0) {
                    s0->_refCount++;
                }
                RefRelease::go((igObject *)ram->_dataList);
                ram->_dataList = (int)s0;
            }
            r = igProperty_FindByName(ram->_dataList, g_propertyNameField[0], "ONE");
            *py = 0.0f;
            igMatrix44f_SetTranslation((char *)r->_node + 32, &sum);
        }
    }
}

int beNDMWMdlMapCursor_GetMeta(void)
{
    return g_beNDMWMdlMapCursor_metaObject[0];
}

#pragma pop

