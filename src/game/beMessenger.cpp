#include "dw4/reflected.h"
#include "dw4/igSmartPointer.h"

class StringRef;

extern "C" {
void igInsightCore_AddToScheduler(int, char *);
void igInsightCore_RemoveFromScheduler(int, char *);
void beMessenger_InitializeMemory(beMessenger *);
void beMessenger_ResetMemory(beMessenger *);
void beMessengerArgData_Clear(beMessengerArgData *);
void beMessengerDelay_Clear(beMessengerDelay *);
void *beMessengerArgData_Create(void *);
void *beMessengerWork_Create(void *);
int ObjectList_ResizeRetained(void *, int);
int strcpy(int *, int);
int strcmp(...);
int igMetaEnum_GetValueByName(int *, int, int, int *);
void *igProperty_FindByName(void *, int, ...);
void *igObject_GetAllocator(void *);
void *Memory_GetAllocatorBySelector(int);
void *beMessengerGroup_Create(void *);
void *beMessengerDelay_Create(void *);
void igNamedObject_SetName(void *, const char *);
void ObjectList_AppendRetained(...);
void List_Resize(void *, int, int);
void List_Reserve(void *, int, int);
void List_RemoveWordAt(void *, int);
void List_InsertWords(void *, int, int, void *);
void *StringPool_Allocate(int);
void *StringPool_Construct(void *);
const char *StringPool_Intern(void *, const char *);
void StringChunk_ReleaseHeader(int, void *);
void StringList_CopyRetained(void *, void *, int);
void StringList_AppendRetained(void *, const StringRef &);
void Matrix44_Copy(void *, void *);
int FUN_00100610(void *);

extern void *g_stringPool[4];
extern int g_defaultAllocatorSelector[4];
extern int g_propertyNameField[4];
extern unsigned char GPR_00554c14;
extern int g_statusSucceeded[4];
extern int DAT_0058a4e0[4];
extern int DAT_0058a4f0[4];
extern int DAT_0058a530[4];
extern int emptyString[4];
extern char DAT_0050ee10[], DAT_0050ee18[];
extern int DAT_004c8f88[4];
extern unsigned char GPR_005549d4, GPR_005549d8;
extern int g_beMessenger_metaObject[4];

void Gap__Bec__beMessenger__vfunc_21(beMessenger *, int);
void Gap__Bec__beMessenger__vfunc_22(beMessenger *, int);
void Gap__Bec__beMessenger__vfunc_23(void);
void Gap__Bec__beMessenger__vfunc_24(void);
int Gap__Bec__beMessenger__vfunc_25(beMessenger *arg0);
void Gap__Bec__beMessenger__vfunc_26(beMessenger *);
void beMessenger_SetFreezeTime(beMessenger *arg0, int arg1);
int beMessenger_ResolveEnumValue(beMessenger *self, int arg1, int arg2);
void beMessenger_RegisterReceiver(beMessenger *self, void *recv, const char *name, const char *text, int value);
void beMessenger_RegisterReceiverFromInfo(int arg0, beBaseInfoRam *arg1, int arg2);
void beMessenger_SelectReceivers(beMessenger *self, char *category, char *name, int id);
void beMessenger_DispatchSelected(beMessenger *self, int name);
void beMessenger_SelectGroupRam(void *, const char *, int);
void beMessenger_SelectGroup(void *, const char *);
void beMessenger_SendNamed(void *, const char *, const char *, int, const char *);
void beMessenger_SendRam(void *, const char *, int, const char *);
void beMessenger_SendGroup(void *, const char *, const char *);
void beMessenger_PrepareDelayedSelection(beMessenger *self, const char *group, const char *name, int number);
void beMessenger_EnqueueSelected(beMessenger *self, const char *text, long long delay);
void beMessenger_SendDelayedNamed(void *, const char *, const char *, int, const char *, long long);
void beMessenger_SendDelayedGroup(void *, const char *, const char *, long long);
void beMessenger_PrepareDelayedGroup(void *, const char *);
void beMessenger_PushArgContext(beMessenger *self);
void beMessenger_PopArgContext(beMessenger *self);
void beMessenger_SetRunCheck(beMessenger *self, char enabled);
int beMessenger_GetBoolCount(beMessenger *self);
void beMessenger_ResizeBool(beMessenger *arg0, int arg1);
void beMessenger_AppendBool(beMessenger *self, char value);
void beMessenger_ClearBool(beMessenger *self);
void beMessenger_SetBool(beMessenger *arg0, int arg1, char arg2);
unsigned char beMessenger_GetBool(beMessenger *self, int index);
int beMessenger_GetIntCount(beMessenger *self);
void beMessenger_AppendInt(beMessenger *self, int value);
void beMessenger_ClearInt(beMessenger *self);
void beMessenger_SetInt(beMessenger *arg0, int arg1, int arg2);
int beMessenger_GetInt(beMessenger *self, int index);
int beMessenger_GetFloatCount(beMessenger *self);
void beMessenger_AppendFloat(beMessenger *self, float value);
float beMessenger_GetFloat(beMessenger *self, int index);
int beMessenger_GetLongCount(beMessenger *self);
void beMessenger_AppendLong(beMessenger *arg0, long long arg1);
long long beMessenger_GetLong(beMessenger *self, int index);
int beMessenger_GetVec3Count(beMessenger *self);
void beMessenger_AppendVec3(beMessenger *self, float *value);
void beMessenger_ClearVec3(beMessenger *self);
void beMessenger_GetVec3(float *out, beMessenger *self, int index);
int beMessenger_GetMatrixCount(beMessenger *self);
void beMessenger_AppendMatrix(beMessenger *self, void *value);
void beMessenger_GetMatrix(void *out, beMessenger *self, int index);
int beMessenger_GetObjectCount(beMessenger *self);
void beMessenger_AppendObject(beMessenger *self, int object);
void beMessenger_ClearObjects(beMessenger *arg0);
int beMessenger_GetObject(beMessenger *self, int index);
int beMessenger_GetStringCount(beMessenger *self);
void beMessenger_AppendString(beMessenger *self, const char *text);
int beMessenger_GetString(beMessenger *self, int index);
int Gap__Bec__beMessenger__vfunc_20(void);
}

static inline int countOf(const igIntList *l) { return l->_count; }
static inline int countOf(const igFloatList *l) { return l->_count; }

/* Owning stack reference to a pooled string token (reference count at p[-1], chunk header at
 * p[-2]); releases the token on scope exit. */
class StringRef {
public:
    int p;
    StringRef(int s) : p(s) {}
    StringRef(const char *s) : p((int)s) {}
    ~StringRef() { if (p) { int *h = (int *)p - 2; int r = ((int *)p)[-1] - 1; ((int *)p)[-1] = r; if (r == 0) StringChunk_ReleaseHeader(*h, h); } }
};

/* matching construct: the list/group fields are 4-byte arena handles in the reflected structs; the (void *) / (T *) casts give the typed views (no layout effect) */
#define RETAIN_REF(q) { igObject *rr = (q); if (rr) ++rr->_refCount; }
#define RELEASE_REF(q) { igObject *rr = (q); \
    if (rr) { --rr->_refCount; if (!(rr->_refCount & 0x7fffff)) igObject_Destroy(rr); } }

/* Reference-counted object prefix: the count is the low 23 bits at +4. */
typedef igObject Obj;

#define OBJ_RELEASE(o) if (o) { --(o)->_refCount; if (((o)->_refCount & 0x7fffff) == 0) igObject_Destroy(o); }
/* Interned strings carry {owner, count} in the 8 bytes before the text. */
#define STR_RELEASE(s) if (s) { int *h_ = (int *)((char *)(s) - 8); if (--h_[1] == 0) StringChunk_ReleaseHeader(h_[0], h_); }
#define POOL() if (!g_stringPool[0]) { void *p_ = StringPool_Allocate(16); if (p_) p_ = StringPool_Construct(p_); g_stringPool[0] = p_; }

typedef beMessengerWork Work;
/* Stack reference to a work record: adopts or retains on construction, releases when it leaves scope. */
struct WorkRef {
    Obj *p;
    Work *operator->() { return (Work *)p; }
    WorkRef(Obj *o) : p(o) {}
    WorkRef(Obj *o, RetainReference) { p = o; if (p) p->_refCount++; }
    /* The assignment inside the condition is what reproduces retail's
     * register choice around the inlined copies of this release. */
    ~WorkRef() { Obj *o; if ((o = p) != 0) { --o->_refCount; if ((o->_refCount & 0x7fffff) == 0) igObject_Destroy(o); } }
};

typedef igObject RefObj;
/* Owning stack reference to an argument object: adopts the object it is built with or takes a
 * retained one by assignment, and releases it on scope exit (reference count in the low 23 bits of
 * _refCount). */
class ObjectRef {
public:
    RefObj *p;
    RefObj *get() const { return p; }
    ObjectRef(RefObj *o) : p(o) {}
    ObjectRef &operator=(RefObj *incoming) {
        RefObj *outgoing;
        if (incoming) ++incoming->_refCount;
        outgoing = p;
        release(outgoing);
        p = incoming;
        return *this;
    }
    ~ObjectRef() { RefObj *o = p; release(o); }
    static void release(RefObj *o) {
        if (o) {
            --o->_refCount;
            if (((unsigned long long)(long long)(int)o->_refCount & 0x7fffffULL) == 0)
                igObject_Destroy(o);
        }
    }
    static void assign(RefObj **dest, RefObj *incoming) {
        RefObj *outgoing;
        if (incoming) ++incoming->_refCount;
        outgoing = *dest;
        release(outgoing);
        *dest = incoming;
    }
};

#define ALLOC(var) \
    { var = igObject_GetAllocator(arg0); var = GPR_00554c14 ? var : Memory_GetAllocatorBySelector(g_defaultAllocatorSelector[0]); }

template <class Ref> static inline void storeAt(const int &list, int i, const Ref &slot) {
    igObject *cur = slot.p;
    igObjectList *l = (igObjectList *)list;
    RETAIN_REF(cur)
    RELEASE_REF(((igObject **)l->_data)[i])
    int n = l->_count;
    if (n != 0 && i >= 0 && i < n) ((igObject **)l->_data)[i] = cur;
}
#define GROUP(field, CNT, factory, Ref) { \
    igObjectList *list = (igObjectList *)arg0->field; \
    if (list->_count < (CNT) + 1) List_Reserve(list, CNT, 4); \
    ObjectList_ResizeRetained((void *)arg0->field, CNT); \
    int i; \
    for (i = 0; i < (CNT); i += 1) { \
        void *alloc; \
        ALLOC(alloc) \
        Ref slot((igObject *)factory(alloc)); \
        storeAt(arg0->field, i, slot); \
    } }

void beMessenger_InitializeMemory(beMessenger *arg0)
{
    void *alloc0;

    ALLOC(alloc0)
    {
        ObjectRef argData((igObject *)beMessengerArgData_Create(alloc0));
        igObject *cur0 = argData.p;
        RETAIN_REF(cur0)
        RELEASE_REF((igObject *)arg0->_argData)
        arg0->_argData = (int)cur0;
    }
    GROUP(_workStack, 0x40, beMessengerWork_Create, WorkRef)
    GROUP(_delayStack, 0x20, beMessengerDelay_Create, igSmartPointer<igObject>)
    GROUP(_pushPopStack, 4, beMessengerArgData_Create, ObjectRef)
    arg0->_pushPopCount = 0;
    arg0->_isMemoryAssign = 1;
}

#define CLEAR(src) { \
    igObjectList *l = (igObjectList *)(src); \
    int n = l->_count; \
    int i; \
    int m; \
    int j; \
    igObject *o; \
    for (i = 0; i < n; i++) { \
        o = ((igObject **)l->_data)[i]; \
        if (o != 0) { \
            o->_refCount = (int)o->_refCount - 1; \
            if (((unsigned long long)((long long)(int)o->_refCount << 0x29) >> 0x29) == 0) igObject_Destroy(o); \
        } \
    } \
    m = l->_count; \
    for (j = 0; j < m; j++) { \
        ((igObject **)l->_data)[j] = 0; \
    } \
    l->_count = 0; }
void beMessenger_ResetMemory(beMessenger *arg0) {
    igObject *t = (igObject *)arg0->_argData;
    if (t != 0) {
        t->_refCount = (int)t->_refCount - 1;
        if (((unsigned long long)((long long)(int)t->_refCount << 0x29) >> 0x29) == 0) igObject_Destroy(t);
    }
    arg0->_argData = 0;
    CLEAR(arg0->_groupList)
    if (((igObjectList *)arg0->_groupList)->_count < 5) List_Reserve((igObjectList *)arg0->_groupList, 4, 4);
    CLEAR(arg0->_workStack)
    if (((igObjectList *)arg0->_workStack)->_count < 5) List_Reserve((igObjectList *)arg0->_workStack, 4, 4);
    CLEAR(arg0->_delayStack)
    if (((igObjectList *)arg0->_delayStack)->_count < 5) List_Reserve((igObjectList *)arg0->_delayStack, 4, 4);
    CLEAR(arg0->_pushPopStack)
    if (((igObjectList *)arg0->_pushPopStack)->_count < 5) List_Reserve((igObjectList *)arg0->_pushPopStack, 4, 4);
    arg0->_pushPopCount = 0;
    arg0->_freezeTime = 0;
    arg0->_isMemoryAssign = 0;
}

void beMessengerArgData_Clear(beMessengerArgData *arg0) {
    igDataList *lo;
    void *v;
    int v0;
    int *old;
    int *hd;
    int *s1;
    igDataList *l;
    igDataList *sl;
    int n1;
    int i1;
    int n2;
    int i2;

    arg0->_isRunCheck = 0;
    if (g_stringPool[0] == 0) {
        v = StringPool_Allocate(0x10);
        if (v != 0) {
            v = StringPool_Construct(v);
        }
        g_stringPool[0] = v;
    }
    s1 = (int *)StringPool_Intern(g_stringPool[0], 0);
    old = (int *)arg0->_debugString;
    if (old != 0) {
        hd = old - 2;
        v0 = old[-1] - 1;
        old[-1] = v0;
        if (v0 == 0) {
            StringChunk_ReleaseHeader(*hd, hd);
        }
    }
    arg0->_debugString = (int)s1;
    ((igBoolList *)arg0->_boolList)->_count = 0;
    l = (igDataList *)arg0->_boolList;
    /* matching construct: list shrink guard spelled as nested ifs ("&&" or "> 4" changes the compare) */
    if (l->_capacity > 4) { if (l->_count < 5) List_Reserve(l, 4, 1); }
    ((igIntList *)arg0->_intList)->_count = 0;
    l = (igDataList *)arg0->_intList;
    if (l->_capacity > 4) { if (l->_count < 5) List_Reserve(l, 4, 4); }
    ((igFloatList *)arg0->_floatList)->_count = 0;
    l = (igDataList *)arg0->_floatList;
    if (l->_capacity > 4) { if (l->_count < 5) List_Reserve(l, 4, 4); }
    ((igLongList *)arg0->_longList)->_count = 0;
    l = (igDataList *)arg0->_longList;
    if (l->_capacity > 4) { if (l->_count < 5) List_Reserve(l, 4, 8); }
    ((igVec3fList *)arg0->_vec3fList)->_count = 0;
    l = (igDataList *)arg0->_vec3fList;
    if (l->_capacity > 4) { if (l->_count < 5) List_Reserve(l, 4, 12); }
    ((igMatrix44fList *)arg0->_matrix44fList)->_count = 0;
    l = (igDataList *)arg0->_matrix44fList;
    if (l->_capacity > 4) { if (l->_count < 5) List_Reserve(l, 4, 64); }
    sl = (igDataList *)arg0->_stringList;

    /* matching construct: separate n/i counters per loop and block-local rr/m/j fix register allocation */
    n1 = sl->_count;
    for (i1 = 0; i1 < n1; i1++) {
        int **slot = &((int **)sl->_data)[i1];
        int *rr;
        if (g_stringPool[0] == 0) {
            v = StringPool_Allocate(0x10);
            if (v != 0) {
                v = StringPool_Construct(v);
            }
            g_stringPool[0] = v;
        }
        rr = (int *)StringPool_Intern(g_stringPool[0], 0);
        old = *slot;
        if (old != 0) {
            hd = old - 2;
            v0 = old[-1] - 1;
            old[-1] = v0;
            if (v0 == 0) {
                StringChunk_ReleaseHeader(*hd, hd);
            }
        }
        *slot = rr;
    }

    sl->_count = 0;
    sl = (igDataList *)arg0->_stringList;
    if (sl->_capacity > 4) { if (sl->_count < 5) List_Reserve(sl, 4, 4); }
    lo = (igDataList *)arg0->_objectList;

    n2 = lo->_count;
    for (i2 = 0; i2 < n2; i2++) {
        igObject *o = ((igObject **)lo->_data)[i2];
        if (o != 0) {
            o->_refCount = (int)o->_refCount - 1;
            if (((unsigned long long)((long long)(int)o->_refCount << 0x29) >> 0x29) == 0) {
                igObject_Destroy(o);
            }
        }
    }

    {
        int m = lo->_count;
        int j;
        for (j = 0; j < m; j++) {
            ((igObject **)lo->_data)[j] = 0;
        }
    }
    lo->_count = 0;
    l = (igDataList *)arg0->_objectList;
    if (l->_capacity > 4) { if (l->_count < 5) List_Reserve(l, 4, 4); }
}

void beMessengerDelay_Clear(beMessengerDelay *arg0) {
    void *v;
    int v0;
    int *old;
    int *hd;
    int *s1;
    arg0->_isUse = 0;
    arg0->_sendTime = 0;
    if (g_stringPool[0] == 0) {
        v = StringPool_Allocate(0x10);
        if (v != 0) {
            v = StringPool_Construct(v);
        }
        g_stringPool[0] = v;
    }
    s1 = (int *)StringPool_Intern(g_stringPool[0], 0);
    old = (int *)arg0->_groupName;
    if (old != 0) {
        hd = old - 2;
        v0 = old[-1] - 1;
        old[-1] = v0;
        if (v0 == 0) {
            StringChunk_ReleaseHeader(*hd, hd);
        }
    }
    arg0->_groupName = (int)s1;
    if (g_stringPool[0] == 0) {
        v = StringPool_Allocate(0x10);
        if (v != 0) {
            v = StringPool_Construct(v);
        }
        g_stringPool[0] = v;
    }
    s1 = (int *)StringPool_Intern(g_stringPool[0], 0);
    old = (int *)arg0->_infoName;
    if (old != 0) {
        hd = old - 2;
        v0 = old[-1] - 1;
        old[-1] = v0;
        if (v0 == 0) {
            StringChunk_ReleaseHeader(*hd, hd);
        }
    }
    arg0->_infoName = (int)s1;
    arg0->_ramNo = 0;
    if (g_stringPool[0] == 0) {
        v = StringPool_Allocate(0x10);
        if (v != 0) {
            v = StringPool_Construct(v);
        }
        g_stringPool[0] = v;
    }
    s1 = (int *)StringPool_Intern(g_stringPool[0], 0);
    old = (int *)arg0->_message;
    if (old != 0) {
        hd = old - 2;
        v0 = old[-1] - 1;
        old[-1] = v0;
        if (v0 == 0) {
            StringChunk_ReleaseHeader(*hd, hd);
        }
    }
    arg0->_message = (int)s1;
    beMessengerArgData_Clear((beMessengerArgData *)arg0->_argData);
}

void Gap__Bec__beMessenger__vfunc_21(beMessenger *self, int unusedArg)
{
    igInsightCore_AddToScheduler(self->_insight, (char *)self); /* matching construct: char * parameter on FUN_00236*, receiver passed as a byte pointer */
}

void Gap__Bec__beMessenger__vfunc_22(beMessenger *self, int unusedArg)
{
    igInsightCore_RemoveFromScheduler(self->_insight, (char *)self); /* matching construct: char * parameter on FUN_00236*, receiver passed as a byte pointer */
}

void Gap__Bec__beMessenger__vfunc_23(void)
{
}

void Gap__Bec__beMessenger__vfunc_24(void)
{
}

int Gap__Bec__beMessenger__vfunc_25(beMessenger *arg0) {
    if (arg0->_isMemoryAssign == 0) {
        beMessenger_InitializeMemory(arg0);
    }
    return 0;
}

void Gap__Bec__beMessenger__vfunc_26(beMessenger *self)
{
    beMessenger_ResetMemory(self);
}

void beMessenger_SetFreezeTime(beMessenger *arg0, int arg1) {
    if (arg1 != 0) {
        arg0->_freezeTime = (long long) ((igInsightCore *)arg0->_insight)->_worldTime;
        return;
    }
    arg0->_freezeTime = 0;
}

int beMessenger_ResolveEnumValue(beMessenger *self, int arg1, int arg2) {
    int value;
    int found;
    if ((DAT_0058a4e0[0] == arg1) && (strcmp(&DAT_0058a4f0[0], arg2) == 0)) {
        return DAT_0058a530[0];
    }
    igMetaEnum_GetValueByName(&found, arg1, arg2, &value);
    if (*(int *)(unsigned)&found == g_statusSucceeded[0]) {
        DAT_0058a4e0[0] = arg1;
        strcpy(&DAT_0058a4f0[0], arg2);
        DAT_0058a530[0] = value;
        return value;
    }
    return -1;
}

struct Str { static inline const char *intern(const char *text) {
    const char *token;
    if (text == 0) {
        token = 0;
    } else {
        if (g_stringPool[0] == 0) {
            void *pool = StringPool_Allocate(0x10);
            if (pool != 0) pool = StringPool_Construct(pool);
            g_stringPool[0] = pool;
        }
        token = StringPool_Intern(g_stringPool[0], text);
    }
    return token;
} };

void beMessenger_RegisterReceiver(beMessenger *self, void *recv, const char *name, const char *text, int value)
{
    void *allocator;
    igIntList *l;
    int n;

    igSmartPointer<beMessengerGroup> grp((beMessengerGroup *)igProperty_FindByName((void *)self->_groupList, g_propertyNameField[0]));
    RETAIN_REF(grp.p)
    if (grp.p == 0) {
        allocator = igObject_GetAllocator(self);
        allocator = GPR_00554c14 ? allocator : Memory_GetAllocatorBySelector(g_defaultAllocatorSelector[0]);
        RELEASE_REF(grp.p)
        grp.p = (beMessengerGroup *)beMessengerGroup_Create(allocator);
        igNamedObject_SetName(grp.p, name);
        ObjectList_AppendRetained((void *)self->_groupList, grp.p);
    }
    ObjectList_AppendRetained((void *)grp.p->_ramList, recv);
    {
        const char *token = Str::intern(text);
        StringList_AppendRetained((void *)grp.p->_infoNameList, StringRef(token));
    }
    l = (igIntList *)grp.p->_ramNoList;
    n = l->_count;
    if (n < l->_capacity) l->_count = countOf(l) + 1;
    else List_Resize(l, n + 1, 4);
    ((int *)l->_data)[n] = value;
}

/* C++ keeps the call a real jal (C turns a trailing call into a tail jump); the ternary gives the
 * empty-then / branch-over shape. */
void beMessenger_RegisterReceiverFromInfo(int arg0, beBaseInfoRam *arg1, int arg2) {
    beBaseInfo *info = (beBaseInfo *)arg1->_parentInfo;
    int *recv = (int *)info->_name;
    int t = arg1->_ramNo;
    recv = recv != 0 ? recv : &emptyString[0];
    beMessenger_RegisterReceiver((beMessenger *)arg0, arg1, (const char *)arg2, (const char *)recv, t);
}

/* The lists are igObjectList (_count +8, _capacity +12, _data +16); the data
 * handle is read as an array of object pointers. */
typedef igObjectList List;
static inline int countOf(const List *l) { return l->_count; }
#define LDATA(l) ((Obj **)(l)->_data)

/* A second reader of the info name; the first load is not reused for the null-handling comparison,
 * and this access path does not either. */
struct WorkOps {
static inline char *InfoName2(Work *w) { return (char *)((Work *)w)->_infoName; }
static inline char *Intern(char *text) {
    POOL();
    return (char *)StringPool_Intern(g_stringPool[0], text);
}
static inline void SetGroupName(Work *w, char *c) { char *s; s = Intern(c); char *o = (char *)w->_groupName; STR_RELEASE(o); w->_groupName = (int)s; }
static inline void SetInfoName(Work *w, char *n) { char *s; s = Intern(n); char *o = (char *)w->_infoName; STR_RELEASE(o); w->_infoName = (int)s; }
};

typedef beMessengerGroup Group;
typedef beMessenger Messenger;

/* A retained word that lives on the stack and is then stored into a list by address. It has no
 * destructor: the list takes the reference. The constructor reads its own stored word back through
 * a laundered pointer, fetches the work-stack handle between that read and the null test, and
 * increments the count through that pointer; that shape makes the address register, delay slot and
 * stack layout come out. */
struct RefTmp {
    Obj * value;
    RefTmp(Obj *p, Messenger *m, int &out) : value(p) {
        RefTmp *s = (RefTmp *)(int)this;
        Obj *v = s->value;
        out = m->_workStack;
        if (v) ++s->value->_refCount;
    }
    static void PushFront(Messenger *m, Obj *obj) {
        int dst;
        RefTmp tmp(obj, m, dst);
        List_InsertWords((void *)dst, 0, 1, (void *)&tmp.value);
    }
};

#define IW ((Work *)item.p)

void beMessenger_SelectReceivers(Messenger *self, char *category, char *name, int id) {
    /* Declaration order matters for retail's register assignment. */
    int k;
    unsigned char found;
    int c;
    Work *work;
    Obj **src;
    Group *g;
    List *l;
    int i, n;
    int m;
    int lastIdx;
    int last;

    if (!self->_isMemoryAssign) beMessenger_InitializeMemory(self);
    else beMessengerArgData_Clear((beMessengerArgData *)self->_argData);

    found = 0;
    n = ((List *)self->_workStack)->_count;
    for (i = 0; i < n; i++) {
        WorkRef item(LDATA((List *)self->_workStack)[i], kRetainReference);
        if (!IW->_groupName) continue;
        if (strcmp((char *)IW->_groupName, category)) continue;
        if (IW->_infoName == 0 || name == 0) {
            if (WorkOps::InfoName2(IW) != name) continue;
        } else if (strcmp((char *)IW->_infoName, name)) continue;
        IW->_ramNo = id;
        if (i) {
            List *l = (List *)self->_workStack;
            Obj *old = LDATA(l)[i];
            OBJ_RELEASE(old);
            List_RemoveWordAt(l, i);
            LDATA(l)[l->_count] = 0;
            RefTmp::PushFront(self, item.p);
        }
        found = 1;
        break;
    }
    if (found == 0) {
        lastIdx = ((List *)self->_workStack)->_count - 1;
        WorkRef item(LDATA((List *)self->_workStack)[lastIdx], kRetainReference);
        List *q;
        WorkOps::SetGroupName(item.operator->(), category);
        WorkOps::SetInfoName(item.operator->(), name);
        IW->_ramNo = id;
        ((List *)IW->_findRamNoList)->_count = 0;
        q = (List *)IW->_findRamNoList;
        if (q->_capacity > 4 && q->_count < 5) List_Reserve(q, 4, 4);
        {
            List *r = (List *)IW->_findRamList;
            int m = r->_count, k;
            for (k = 0; k < m; k++) { Obj *o = LDATA(r)[k]; OBJ_RELEASE(o); }
            m = r->_count;
            for (k = 0; k < m; k++) LDATA(r)[k] = 0;
            r->_count = 0;
            q = (List *)IW->_findRamList;
            if (q->_capacity > 4 && q->_count < 5) List_Reserve(q, 4, 4);
        }
        {
            List *l2 = (List *)self->_workStack;
            last = l2->_count - 1;
            Obj *o = LDATA(l2)[last];
            OBJ_RELEASE(o);
            List_RemoveWordAt(l2, last);
            LDATA(l2)[l2->_count] = 0;
            RefTmp::PushFront(self, item.p);
        }
    }

    work = (Work *)LDATA((List *)self->_workStack)[0];
    if (((List *)work->_findRamList)->_count == 0) {
        g = (Group *)igProperty_FindByName((void *)self->_groupList, g_propertyNameField[0], (char *)work->_groupName);
        if (g) {
            m = ((List *)g->_ramList)->_count;
            for (k = 0; k < m; k++) {
                char *tmp;
                char *s;
                StringList_CopyRetained(&tmp, (void *)g->_infoNameList, k);
                s = tmp;
                STR_RELEASE(s);
                if (!(work->_infoName && s) || !strcmp((char *)work->_infoName, s)) {
                    src = &LDATA((List *)g->_ramNoList)[k];
                    l = (List *)work->_findRamNoList;
                    c = l->_count;
                    if (c < l->_capacity) l->_count = countOf(l) + 1;
                    else List_Resize(l, c + 1, 4);
                    LDATA(l)[c] = *src;
                    ObjectList_AppendRetained((void *)work->_findRamList, LDATA((List *)g->_ramList)[k]);
                }
            }
        }
    }
}

typedef struct DispatchObj { int w0; int ref; } DispatchObj;

static inline int listCount(const igIntList *list) { return list->_count; }

/* matching construct: dummy-virtual class so r->Check / r->Send compile to vtable slots 34 / 33 (beBaseInfoManager vtable) */
class MsgReceiver {
public:
    virtual void vfunc_00();
    virtual void vfunc_01();
    virtual void vfunc_02();
    virtual void vfunc_03();
    virtual void vfunc_04();
    virtual void vfunc_05();
    virtual void vfunc_06();
    virtual void vfunc_07();
    virtual void vfunc_08();
    virtual void vfunc_09();
    virtual void vfunc_10();
    virtual void vfunc_11();
    virtual void vfunc_12();
    virtual void vfunc_13();
    virtual void vfunc_14();
    virtual void vfunc_15();
    virtual void vfunc_16();
    virtual void vfunc_17();
    virtual void vfunc_18();
    virtual void vfunc_19();
    virtual void vfunc_20();
    virtual void vfunc_21();
    virtual void vfunc_22();
    virtual void vfunc_23();
    virtual void vfunc_24();
    virtual void vfunc_25();
    virtual void vfunc_26();
    virtual void vfunc_27();
    virtual void vfunc_28();
    virtual void vfunc_29();
    virtual void vfunc_30();
    virtual void vfunc_31();
    virtual void vfunc_32();
    virtual void Send(beBaseInfoRam *obj, int name);
    virtual unsigned char Check(beBaseInfoRam *obj, beMessengerWork *work);
};

/* matching construct: RAII holder reproduces the retail inline retain/release and the emitted destructor at 0x0038e530 */
class ObjRef {
public:
    DispatchObj *value;
    ObjRef(DispatchObj *p) : value(p) { if (value) ++value->ref; }
    void operator=(DispatchObj *p) {
        DispatchObj *object;
        if (p) ++p->ref;
        object = value;
        if (object) {
            --object->ref;
            if (((unsigned long long)(long long)object->ref & 0x7fffffULL) == 0) igObject_Destroy(object);
        }
        value = p;
    }
    ~ObjRef() {
        DispatchObj *object = value;
        if (object) {
            --object->ref;
            if (((unsigned long long)(long long)object->ref & 0x7fffffULL) == 0) igObject_Destroy(object);
        }
    }
};

void beMessenger_DispatchSelected(beMessenger *self, int name)
{
    int n;
    void *alloc;
    igIntList *il;
    int *header;
    int i;
    int str;
    int i3;
    int count;
    igBoolList *bl;
    int i2;
    beMessengerWork *work;
    int old;
    int refs;
    int matches;

    work = (beMessengerWork *)((int *)((beMessengerWorkList *)self->_workStack)->_data)[0];
    if (g_stringPool[0] == 0) {
        alloc = StringPool_Allocate(16);
        if (alloc) alloc = StringPool_Construct(alloc);
        g_stringPool[0] = alloc;
    }
    str = (int)StringPool_Intern(g_stringPool[0], (const char *)name);
    old = work->_message;
    if (old) {
        header = (int *)(old - 8);
        refs = *(int *)(old - 4) - 1;
        *(int *)(old - 4) = refs;
        if (!refs) StringChunk_ReleaseHeader(*header, header);
    }
    work->_message = str;
    igObjectList *fl = (igObjectList *)work->_findRamList;
    count = fl->_count;
    if (strcmp(name, DAT_0050ee10) == 0) {
        matches = 0;
        for (i = 0; i < count; i++) {
            igIntList *list = (igIntList *)work->_findRamNoList; int have = ((int *)list->_data)[i]; if (work->_ramNo == -1 || *(int *)(list->_data + i * 4) /* matching construct: byte-offset element read keeps the data load inside the loop */ == -1 || have == work->_ramNo) matches++;
        }
        {
            if (matches) {
                igBoolList *bla = (igBoolList *)((beMessengerArgData *)self->_argData)->_boolList;
                int na = bla->_count;
                if (na < bla->_capacity) bla->_count = na + 1; else List_Resize(bla, na + 1, 1);
                ((char *)bla->_data)[na] = GPR_005549d4;
                il = (igIntList *)((beMessengerArgData *)self->_argData)->_intList;
                n = il->_count;
                if (n < il->_capacity) il->_count = listCount(il) + 1; else List_Resize(il, n + 1, 4);
                ((int *)il->_data)[n] = matches;
            } else {
                igBoolList *blc = (igBoolList *)((beMessengerArgData *)self->_argData)->_boolList;
                n = blc->_count;
                if (n < blc->_capacity) blc->_count = n + 1; else List_Resize(blc, n + 1, 1);
                ((char *)blc->_data)[n] = GPR_005549d8;
                il = (igIntList *)((beMessengerArgData *)self->_argData)->_intList;
                int nd = il->_count;
                if (nd < il->_capacity) il->_count = listCount(il) + 1; else List_Resize(il, nd + 1, 4);
                ((int *)il->_data)[nd] = DAT_004c8f88[0];
            }
        }
    } else if (strcmp(name, DAT_0050ee18) == 0) {
        ObjRef held(0);
        for (i2 = 0; i2 < count; i2++) {
            igObjectList *list = (igObjectList *)work->_findRamList;
            beBaseInfoRam *obj = ((beBaseInfoRam **)list->_data)[i2];
            if (((beBaseInfoRam **)list->_data)[i2]->_isRun == 0) {
                held = (DispatchObj *)obj;
                break;
            }
        }
        if (held.value) ObjectList_AppendRetained((void *)((beMessengerArgData *)self->_argData)->_objectList, held.value);
    } else {
        for (i3 = 0; i3 < count; i3++) {
            int sid = work->_ramNo;
            beBaseInfoRam *obj = ((beBaseInfoRam **)((igObjectList *)work->_findRamList)->_data)[i3];
            MsgReceiver *r;
            if (sid == -2) {
                if (obj->_isRun != 0) continue;
            } else {
                int have = ((int *)((igIntList *)work->_findRamNoList)->_data)[i3];
                if (((beMessengerArgData *)self->_argData)->_isRunCheck == 1 && obj->_isRun == 0) continue;
                if (!(sid == -1 || have == -1 || have == sid)) continue;
            }
            r = (MsgReceiver *)obj->_parentManager;
            if (!(r->Check(obj, work) & 0xff)) r->Send(obj, name);
            if (work->_ramNo == -2) break;
        }
    }
}

void beMessenger_SelectGroupRam(void *self,const char *category,int id){beMessenger_SelectReceivers((beMessenger *)self,(char *)category,0,id);}
void beMessenger_SelectGroup(void *self,const char *category){beMessenger_SelectReceivers((beMessenger *)self,(char *)category,0,-1);}
void beMessenger_SendNamed(void *self,const char *category,const char *name,int id,const char *key){beMessenger_SelectReceivers((beMessenger *)self,(char *)category,(char *)name,id);beMessenger_DispatchSelected((beMessenger *)self,(int)key);}
void beMessenger_SendRam(void *self,const char *category,int id,const char *key){beMessenger_SelectGroupRam(self,category,id);beMessenger_DispatchSelected((beMessenger *)self,(int)key);}
void beMessenger_SendGroup(void *self,const char *category,const char *key){beMessenger_SelectGroup(self,category);beMessenger_DispatchSelected((beMessenger *)self,(int)key);}

#define SET_STRING(field, text) { \
    beMessengerDelay *r = (beMessengerDelay *)row.p; \
    if (g_stringPool[0] == 0) { \
        void *pool = StringPool_Allocate(0x10); \
        if (pool != 0) pool = StringPool_Construct(pool); \
        g_stringPool[0] = pool; \
    } \
    token = StringPool_Intern(g_stringPool[0], (text)); \
    int *old = (int *)r->field; \
    if (old) { \
        int *header = old - 2; \
        if (--old[-1] == 0) StringChunk_ReleaseHeader(*header, header); \
    } \
    r->field = (int)token; }

void beMessenger_PrepareDelayedSelection(beMessenger *self, const char *group, const char *name, int number)
{
    void *allocator;
    const char *token;
    beMessengerDelayList *stack;
    int last;

    if (self->_isMemoryAssign == 0)
        beMessenger_InitializeMemory(self);
    else
        beMessengerArgData_Clear((beMessengerArgData *)self->_argData);
    stack = (beMessengerDelayList *)self->_delayStack;
    last = stack->_count - 1;
    igSmartPointer<igObject> row(((igObject **)stack->_data)[last]);
    RETAIN_REF(row.p)
    if (((beMessengerDelay *)row.p)->_isUse) {
        allocator = igObject_GetAllocator(self);
        allocator = GPR_00554c14 ? allocator : Memory_GetAllocatorBySelector(g_defaultAllocatorSelector[0]);
        RELEASE_REF(row.p)
        row.p = (igObject *)beMessengerDelay_Create(allocator);
        ObjectList_AppendRetained((void *)self->_delayStack, row.p);
    }
    SET_STRING(_groupName, group)
    SET_STRING(_infoName, name)
    ((beMessengerDelay *)row.p)->_ramNo = number;
}

/* The insight object's clock (+80, 64 bits). */
struct Insight {
    static long long Get(igInsightCore *i) { return i->_worldTime; }
};

/* Loop helpers: the list base and the element access are separate calls. */
struct ListOps {
    static igObject **Data(igObjectList *l) { return (igObject **)l->_data; }
    static igObject *At(igObject **b, int k) { return b[k]; }
};

#define RELEASE_OBJ(o) { \
    if (o) { \
        --(o)->_refCount; \
        if (((unsigned long long)(long long)(o)->_refCount & 0x7fffffULL) == 0) \
            igObject_Destroy(o); \
    } }

struct RowOps {
    static void SetArg(beMessengerDelay *r, igObject *in) {
        igObject *old;
        if (in) ++in->_refCount;
        old = (igObject *)r->_argData;
        RELEASE_OBJ(old)
        r->_argData = (int)in;
    }
};

/* Reference stored through a pointer (the messenger's own argument slot) and the temporary handed
 * to the list insert. Its constructor reads its stored word back through a laundered pointer, fetches
 * the delay-stack handle between that read and the null test, and increments the count through that
 * pointer. */
struct DelayRef {
    igObject * value;
    DelayRef(igObject *p, beMessenger *m, int &out) : value(p) {
        DelayRef *s = (DelayRef *)(int)this;
        igObject *v = s->value;
        out = m->_delayStack;
        if (v) ++s->value->_refCount;
    }
    static void release(igObject *o) { RELEASE_OBJ(o) }
    static void assign(igObject **dest, igObject *incoming) {
        igObject *outgoing;
        if (incoming) ++incoming->_refCount;
        outgoing = *dest;
        release(outgoing);
        *dest = incoming;
    }
};

void beMessenger_EnqueueSelected(beMessenger *self, const char *text, long long delay)
{
    igObjectList *stack;
    int idx, last, i, n, st;
    igObjectList *list;
    const char *token;

    stack = (igObjectList *)self->_delayStack;
    idx = stack->_count - 1;
    igSmartPointer<igObject> row(((igObject **)stack->_data)[idx], kRetainReference);
    {
        long long now = Insight::Get((igInsightCore *)self->_insight);
        ((beMessengerDelay *)row.p)->_sendTime = now + delay * 16666666;
    }

    {
        ObjectRef saved(0);
        saved = (igObject *)self->_argData;
        beMessengerDelay *r = (beMessengerDelay *)row.p;
        DelayRef::assign((igObject **)&self->_argData, (igObject *)r->_argData);
        r = (beMessengerDelay *)row.p;
        RowOps::SetArg(r, saved.p);
    }

    {
        beMessengerDelay *r = (beMessengerDelay *)row.p;
        if (g_stringPool[0] == 0) {
            void *pool = StringPool_Allocate(0x10);
            if (pool != 0) pool = StringPool_Construct(pool);
            g_stringPool[0] = pool;
        }
        token = StringPool_Intern(g_stringPool[0], text);
        int *old = (int *)r->_message;
        if (old) {
            int *header = old - 2;
            if (--old[-1] == 0) StringChunk_ReleaseHeader(*header, header);
        }
        r->_message = (int)token;
    }
    ((beMessengerDelay *)row.p)->_isUse = 1;

    stack = (igObjectList *)self->_delayStack;
    last = stack->_count - 1;
    DelayRef::release(((igObject **)stack->_data)[last]);
    List_RemoveWordAt(stack, last);
    ((igObject **)stack->_data)[stack->_count] = 0;

    list = (igObjectList *)self->_delayStack;
    n = list->_count;
    unsigned cur;
    igObjectList *l2 = list;
    for (i = 0; i < n; i++) {
        cur = (unsigned)row.p;
        beMessengerDelay *d = (beMessengerDelay *)((igObject **)l2->_data)[i];
        if (!d->_isUse) break;
        if (d->_sendTime > ((beMessengerDelay *)cur)->_sendTime) break;
        l2 = list;
    }
    DelayRef tmp(row.p, self, st);
    List_InsertWords((void *)st, i, 1, (void *)&tmp.value);
}

void beMessenger_SendDelayedNamed(void *self,const char *group,const char *name,int id,const char *message,long long delay){beMessenger_PrepareDelayedSelection((beMessenger *)self,group,name,id);beMessenger_EnqueueSelected((beMessenger *)self,message,delay);}
void beMessenger_SendDelayedGroup(void *self,const char *group,const char *message,long long delay){beMessenger_PrepareDelayedSelection((beMessenger *)self,group,0,-1);beMessenger_EnqueueSelected((beMessenger *)self,message,delay);}
void beMessenger_PrepareDelayedGroup(void *self,const char *group){beMessenger_PrepareDelayedSelection((beMessenger *)self,group,0,-1);}

static inline void insertWords(igObjectList *l, int at, int n, RefObj **src) {
    int i;
    for (i = 0; i < n; i++) {
        RefObj *v = src[i];
        if (v) ++v->_refCount;
    }
    List_InsertWords(l, at, n, (void *)src);
}
void beMessenger_PushArgContext(beMessenger *self) {
    int idx;
    int last;
    igObjectList *stack;
    {
        ObjectRef saved(0);
        saved = (RefObj *)self->_argData;
        stack = (igObjectList *)self->_pushPopStack;
        idx = stack->_count - 1;
        ObjectRef::assign((RefObj **)&self->_argData, ((RefObj **)stack->_data)[idx]);
        stack = (igObjectList *)self->_pushPopStack;
        last = stack->_count - 1;
        ObjectRef::release(((RefObj **)stack->_data)[last]);
        List_RemoveWordAt(stack, last);
        ((RefObj **)stack->_data)[stack->_count] = 0;
        RefObj *tmp = saved.p;
        insertWords((igObjectList *)self->_pushPopStack, 0, 1, &tmp);
    }
    ++self->_pushPopCount;
}

struct ArgRef {
    static void release(RefObj *o) {
        if (o) {
            --o->_refCount;
            if (((unsigned long long)(long long)o->_refCount & 0x7fffffULL) == 0)
                igObject_Destroy(o);
        }
    }
    static void assign(RefObj **dest, RefObj *incoming) {
        RefObj *outgoing;
        if (incoming) ++incoming->_refCount;
        outgoing = *dest;
        release(outgoing);
        *dest = incoming;
    }
};
void beMessenger_PopArgContext(beMessenger *self) {
    igObjectList *list;
    beMessengerArgData_Clear((beMessengerArgData *)self->_argData);
    {
        ObjectRef saved(0);
        saved = (RefObj *)self->_argData;
        ArgRef::assign((RefObj **)&self->_argData, ((RefObj **)((igObjectList *)self->_pushPopStack)->_data)[0]);
        list = (igObjectList *)self->_pushPopStack;
        ArgRef::release(((RefObj **)list->_data)[0]);
        List_RemoveWordAt(list, 0);
        ((RefObj **)list->_data)[list->_count] = 0;
        ObjectList_AppendRetained(self->_pushPopStack, saved.p);
    }
    --self->_pushPopCount;
}

void beMessenger_SetRunCheck(beMessenger *self, char enabled) {
    beMessengerArgData *args = (beMessengerArgData *)self->_argData;
    args->_isRunCheck = enabled;
}

int beMessenger_GetBoolCount(beMessenger *self) {
    beMessengerArgData *args = (beMessengerArgData *)self->_argData;
    igBoolList *list = (igBoolList *)args->_boolList;
    return list->_count;
}

void beMessenger_ResizeBool(beMessenger *arg0, int arg1) {
    igBoolList *temp_a0;
    temp_a0 = (igBoolList *)((beMessengerArgData *)arg0->_argData)->_boolList;
    if (arg1 >= 0) {
        if (arg1 <= temp_a0->_capacity) {
            temp_a0->_count = arg1;
            return;
        }
        List_Resize(temp_a0, arg1, 1);
    }
}

void beMessenger_AppendBool(beMessenger *self, char value)
{
    int index;
    igCharList *list;

    list = (igCharList *)((beMessengerArgData *)self->_argData)->_boolList;
    index = list->_count;
    if (index < list->_capacity)
        list->_count = index + 1;
    else
        List_Resize(list, index + 1, 1);
    ((char *)list->_data)[index] = value;
}

void beMessenger_ClearBool(beMessenger *self) {
    beMessengerArgData *args = (beMessengerArgData *)self->_argData;
    igBoolList *list = (igBoolList *)args->_boolList;
    list->_count = 0;
}

void beMessenger_SetBool(beMessenger *arg0, int arg1, char arg2) {
    igBoolList *l = (igBoolList *)((beMessengerArgData *)arg0->_argData)->_boolList;
    int n = l->_count;
    if (n != 0 && arg1 >= 0 && arg1 < n) {
        ((char *)l->_data)[arg1] = arg2;
    }
}

unsigned char beMessenger_GetBool(beMessenger *self, int index) {
    beMessengerArgData *args = (beMessengerArgData *)self->_argData;
    igBoolList *list = (igBoolList *)args->_boolList;
    return *(int *)(list->_data + index);
}

int beMessenger_GetIntCount(beMessenger *self) {
    beMessengerArgData *args = (beMessengerArgData *)self->_argData;
    igIntList *list = (igIntList *)args->_intList;
    return list->_count;
}

void beMessenger_AppendInt(beMessenger *self, int value)
{
    int index;
    igIntList *list;

    list = (igIntList *)((beMessengerArgData *)self->_argData)->_intList;
    index = list->_count;
    if (index < list->_capacity)
        list->_count = countOf(list) + 1;
    else
        List_Resize(list, index + 1, 4);
    ((int *)list->_data)[index] = value;
}

void beMessenger_ClearInt(beMessenger *self) {
    beMessengerArgData *args = (beMessengerArgData *)self->_argData;
    igIntList *list = (igIntList *)args->_intList;
    list->_count = 0;
}

void beMessenger_SetInt(beMessenger *arg0, int arg1, int arg2) {
    beMessengerArgData *args = (beMessengerArgData *)arg0->_argData;
    igIntList *a3 = (igIntList *)args->_intList;
    int n = a3->_count;
    if ((n != 0) && (arg1 >= 0) && (arg1 < n)) {
        ((int *)a3->_data)[arg1] = arg2;
    }
}

int beMessenger_GetInt(beMessenger *self, int index) {
    beMessengerArgData *args = (beMessengerArgData *)self->_argData;
    igIntList *list = (igIntList *)args->_intList;
    return *(int *)(list->_data + (index * 4));
}

int beMessenger_GetFloatCount(beMessenger *self) {
    beMessengerArgData *args = (beMessengerArgData *)self->_argData;
    igFloatList *list = (igFloatList *)args->_floatList;
    return list->_count;
}

void beMessenger_AppendFloat(beMessenger *self, float value)
{
    int index;
    igFloatList *list;

    list = (igFloatList *)((beMessengerArgData *)self->_argData)->_floatList;
    index = list->_count;
    if (index < list->_capacity)
        list->_count = countOf(list) + 1;
    else
        List_Resize(list, index + 1, 4);
    ((float *)list->_data)[index] = value;
}

float beMessenger_GetFloat(beMessenger *self, int index) {
    beMessengerArgData *args = (beMessengerArgData *)self->_argData;
    igFloatList *list = (igFloatList *)args->_floatList;
    return *(float *)(list->_data + index * 4);
}

int beMessenger_GetLongCount(beMessenger *self) {
    beMessengerArgData *args = (beMessengerArgData *)self->_argData;
    igLongList *list = (igLongList *)args->_longList;
    return list->_count;
}

void beMessenger_AppendLong(beMessenger *arg0, long long arg1) {
    int temp_s2;
    beMessengerArgData *args;
    igLongList *temp_s1;

    args = (beMessengerArgData *)arg0->_argData;
    temp_s1 = (igLongList *)args->_longList;
    temp_s2 = temp_s1->_count;
    if (temp_s2 < temp_s1->_capacity) {
        temp_s1->_count = temp_s2 + 1;
    } else {
        List_Resize(temp_s1, temp_s2 + 1, 8);
    }
    ((long long *)temp_s1->_data)[temp_s2] = arg1;
}

long long beMessenger_GetLong(beMessenger *self, int index) {
    beMessengerArgData *args = (beMessengerArgData *)self->_argData;
    igLongList *list = (igLongList *)args->_longList;
    return *(long long *)(list->_data + (index * 8));
}

int beMessenger_GetVec3Count(beMessenger *self) {
    beMessengerArgData *args = (beMessengerArgData *)self->_argData;
    igVec3fList *list = (igVec3fList *)args->_vec3fList;
    return list->_count;
}

void beMessenger_AppendVec3(beMessenger *self, float *value)
{
    int index;
    igVec3fList *list;
    float *slot;

    list = (igVec3fList *)((beMessengerArgData *)self->_argData)->_vec3fList;
    index = list->_count;
    if (index < list->_capacity)
        list->_count = index + 1;
    else
        List_Resize(list, index + 1, 12);
    slot = (float *)list->_data + index * 3;
    slot[0] = value[0];
    slot[1] = value[1];
    slot[2] = value[2];
}

void beMessenger_ClearVec3(beMessenger *self) {
    beMessengerArgData *args = (beMessengerArgData *)self->_argData;
    igVec3fList *list = (igVec3fList *)args->_vec3fList;
    list->_count = 0;
}

void beMessenger_GetVec3(float *out, beMessenger *self, int index) {
    beMessengerArgData *args = (beMessengerArgData *)self->_argData;
    igVec3fList *list = (igVec3fList *)args->_vec3fList;
    float *element;

    element = (float *)(list->_data + (index * 0xC));
    out[0] = element[0];
    out[1] = element[1];
    out[2] = element[2];
}

int beMessenger_GetMatrixCount(beMessenger *self) {
    beMessengerArgData *args = (beMessengerArgData *)self->_argData;
    igMatrix44fList *list = (igMatrix44fList *)args->_matrix44fList;
    return list->_count;
}

void beMessenger_AppendMatrix(beMessenger *self, void *value)
{
    int index;
    igMatrix44fList *list;

    list = (igMatrix44fList *)((beMessengerArgData *)self->_argData)->_matrix44fList;
    index = list->_count;
    if (index < list->_capacity)
        list->_count = index + 1;
    else
        List_Resize(list, index + 1, 64);
    Matrix44_Copy((char *)list->_data + index * 64, value);
}

void beMessenger_GetMatrix(void *out, beMessenger *self, int index)
{
    Matrix44_Copy(out, (void *)(((igMatrix44fList *)((beMessengerArgData *)self->_argData)->_matrix44fList)->_data + index * 64));
}

int beMessenger_GetObjectCount(beMessenger *self) {
    beMessengerArgData *args = (beMessengerArgData *)self->_argData;
    igObjectList *list = (igObjectList *)args->_objectList;
    return list->_count;
}

void beMessenger_AppendObject(beMessenger *self, int object)
{
    ObjectList_AppendRetained(((beMessengerArgData *)self->_argData)->_objectList, object);
}

/* reference-counted engine object header: refcount word at +4 */
typedef struct RefCountedHeader { int pad; int f4; } RefCountedHeader;
/* Element-buffer list header: count at +8, buffer at +16. */
typedef struct ElementBufferList { char pad[8]; int f8; int pad2; RefCountedHeader **f16; } ElementBufferList;

void beMessenger_ClearObjects(beMessenger *arg0) {
    beMessengerArgData *args;
    ElementBufferList *l;
    int n;
    int i;
    RefCountedHeader *o;
    int n2;
    int j;

    args = (beMessengerArgData *)arg0->_argData;
    l = (ElementBufferList *)args->_objectList;
    n = l->f8;
    for (i = 0; i < n; i++) {
        o = l->f16[i];
        if (o != 0) {
            o->f4 = o->f4 - 1;
            if (((unsigned long long) ((long long) o->f4 << 0x29) >> 0x29) == 0) {
                igObject_Destroy(o);
            }
        }
    }
    n2 = l->f8;
    for (j = 0; j < n2; j++) {
        l->f16[j] = 0;
    }
    l->f8 = 0;
}

int beMessenger_GetObject(beMessenger *self, int index) {
    beMessengerArgData *args = (beMessengerArgData *)self->_argData;
    igObjectList *list = (igObjectList *)args->_objectList;
    return *(int *)(list->_data + (index * 4));
}

int beMessenger_GetStringCount(beMessenger *self) {
    beMessengerArgData *args = (beMessengerArgData *)self->_argData;
    igStringRefList *list = (igStringRefList *)args->_stringList;
    return list->_count;
}

/* Intern the text in the shared string pool, append the token to the string list (which takes its
 * own reference) and drop the temporary one when the StringRef bound to the call goes out of
 * scope. */
void beMessenger_AppendString(beMessenger *self, const char *text)
{
    int token;
    void *pool;

    if (text == 0) {
        token = 0;
    } else {
        if (g_stringPool[0] == 0) {
            pool = StringPool_Allocate(16);
            if (pool)
                pool = StringPool_Construct(pool);
            g_stringPool[0] = pool;
        }
        token = (int)StringPool_Intern(g_stringPool[0], text);
    }
    StringList_AppendRetained((void *)((beMessengerArgData *)self->_argData)->_stringList, StringRef(token));
}

/* Header in front of every interned string token: the owning chunk, then the token's reference
 * count. A token points just past this header. */
typedef struct StringTokenHeader {
    int owner;
    int refCount;
} StringTokenHeader;

/* Return the string token at index. The list copy is retained and released again here, so the
 * result is borrowed from the list. */
int beMessenger_GetString(beMessenger *self, int index)
{
    int slot;
    int token;
    StringTokenHeader *header;
    int refCount;

    StringList_CopyRetained(&slot, (void *)((beMessengerArgData *)self->_argData)->_stringList, index);
    token = slot;
    if (token) {
        header = (StringTokenHeader *)(token - 8);
        refCount = header->refCount - 1;
        header->refCount = refCount;
        if (!refCount)
            StringChunk_ReleaseHeader(header->owner, header);
    }
    return token;
}

int Gap__Bec__beMessenger__vfunc_20(void)
{
    return g_beMessenger_metaObject[0];
}
