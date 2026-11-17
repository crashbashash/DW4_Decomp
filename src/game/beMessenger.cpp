#include "dw4/reflected.h"
#include "dw4/igSmartPointer.h"
#include "dw4/listSet.h"
#include "dw4/beMessenger.h"
#include "dw4/StringPool.h"
#include "dw4/beMessengerArgData.h"
#include "dw4/beMessengerDelay.h"
#include "dw4/beMessengerGroup.h"
#include "dw4/beMessengerWork.h"
#include "dw4/igDataLists.h"
#include "dw4/igInsightCore.h"
#include "dw4/igMemoryPoolContext.h"
#include "dw4/igNamedObject.h"
#include "dw4/igObject.h"
#include "dw4/igResult.h"
#include <string.h>

class StringRef;

extern "C" {
void beMessenger_InitializeMemory(beMessenger *);
void beMessenger_ResetMemory(beMessenger *);
void beMessengerArgData_Clear(beMessengerArgData *);
void beMessengerDelay_Clear(beMessengerDelay *);
int ObjectList_ResizeRetained(void *, int);
int igMetaEnum_GetValueByName(int *, igMetaEnum *, const char *, int *);
void StringList_CopyRetained(void *, void *, int);
void StringList_AppendRetained(void *, const StringRef &);
void igMatrix44f_Copy(void *, void *);

extern int g_resolveEnumLastMetaEnum[4];
extern int g_resolveEnumLastName[4];
extern int g_resolveEnumLastValue[4];
extern char emptyString[];
extern char SEARCH[], FIND_SPACE_3[];

void beMessenger_Activate(beMessenger *, int);
void beMessenger_Deactivate(beMessenger *, int);
void beMessenger_Start(void);
void beMessenger_Stop(void);
int beMessenger_AddInfo(beMessenger *self);
void beMessenger_RemoveAllInfo(beMessenger *);
void beMessenger_Update(beMessenger *self);
void beMessenger_SelectGroupRam(void *, const char *, int);
igMetaObject *beMessenger_GetMeta(void);
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
    ~StringRef() { if (p) { int *h = (int *)p - 2; int r = ((int *)p)[-1] - 1; ((int *)p)[-1] = r; if (r == 0) StringChunk_ReleaseHeader((StringChunk *)*h, (StringTokenHeader *)h); } }
};

/* matching construct: the list/group fields are 4-byte arena handles in the reflected structs; the (void *) / (T *) casts give the typed views (no layout effect) */
#define RETAIN_REF(q) { igObject *rr = (q); if (rr) ++rr->_refCount; }
#define RELEASE_REF(q) { igObject *rr = (q); \
    if (rr) { --rr->_refCount; if (!(rr->_refCount & 0x7fffff)) igObject_Destroy(rr); } }

/* Reference-counted object prefix: the count is the low 23 bits at +4. */
typedef igObject Obj;

#define OBJ_RELEASE(o) if (o) { --(o)->_refCount; if (((o)->_refCount & 0x7fffff) == 0) igObject_Destroy(o); }
/* Interned strings carry {owner, count} in the 8 bytes before the text. */
#define STR_RELEASE(s) if (s) { int *h_ = (int *)((char *)(s) - 8); if (--h_[1] == 0) StringChunk_ReleaseHeader((StringChunk *)h_[0], (StringTokenHeader *)h_); }
#define POOL() if (!g_stringPool) { StringPool *p_ = (StringPool *)StringPool_Allocate(16); if (p_) p_ = StringPool_Construct(p_); g_stringPool = p_; }

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

#define ALLOC(var, owner) \
    { var = (int)igObject_GetAllocator(owner); var = g_useOwnerAllocator ? var : (int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleUser1); }

template <class Ref> static inline void storeAt(const int &list, int i, const Ref &slot) {
    igObject *cur = slot.p;
    igObjectList *l = (igObjectList *)list;
    RETAIN_REF(cur)
    RELEASE_REF(((igObject **)l->_data)[i])
    int n = l->_count;
    if (n != 0 && i >= 0 && i < n) ((igObject **)l->_data)[i] = cur;
}
#define GROUP(field, CNT, factory, Ref, T) { \
    igObjectList *list = (igObjectList *)self->field; \
    if (list->_count < (CNT) + 1) List_Reserve((igDataList *)list, CNT, 4); \
    ObjectList_ResizeRetained((void *)self->field, CNT); \
    int i; \
    for (i = 0; i < (CNT); i += 1) { \
        int alloc; \
        ALLOC(alloc, self) \
        Ref slot((T *)factory(alloc)); \
        storeAt(self->field, i, slot); \
    } }

void beMessenger_InitializeMemory(beMessenger *self)
{
    int alloc0;

    ALLOC(alloc0, self)
    {
        ObjectRef argData((igObject *)beMessengerArgData_Create(alloc0));
        igObject *cur0 = argData.p;
        RETAIN_REF(cur0)
        RELEASE_REF((igObject *)self->_argData)
        self->_argData = (int)cur0;
    }
    GROUP(_workStack, 0x40, beMessengerWork_Create, WorkRef, igObject)
    GROUP(_delayStack, 0x20, beMessengerDelay_Create, igSmartPointer<beMessengerDelay>, beMessengerDelay)
    GROUP(_pushPopStack, 4, beMessengerArgData_Create, ObjectRef, igObject)
    self->_pushPopCount = 0;
    self->_isMemoryAssign = 1;
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
void beMessenger_ResetMemory(beMessenger *self) {
    igObject *t = (igObject *)self->_argData;
    if (t != 0) {
        t->_refCount = (int)t->_refCount - 1;
        if (((unsigned long long)((long long)(int)t->_refCount << 0x29) >> 0x29) == 0) igObject_Destroy(t);
    }
    self->_argData = 0;
    CLEAR(self->_groupList)
    if (((igObjectList *)self->_groupList)->_count < 5) List_Reserve((igDataList *)self->_groupList, 4, 4);
    CLEAR(self->_workStack)
    if (((igObjectList *)self->_workStack)->_count < 5) List_Reserve((igDataList *)self->_workStack, 4, 4);
    CLEAR(self->_delayStack)
    if (((igObjectList *)self->_delayStack)->_count < 5) List_Reserve((igDataList *)self->_delayStack, 4, 4);
    CLEAR(self->_pushPopStack)
    if (((igObjectList *)self->_pushPopStack)->_count < 5) List_Reserve((igDataList *)self->_pushPopStack, 4, 4);
    self->_pushPopCount = 0;
    self->_freezeTime = 0;
    self->_isMemoryAssign = 0;
}

void beMessengerArgData_Clear(beMessengerArgData *self) {
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

    self->_isRunCheck = 0;
    if (g_stringPool == 0) {
        v = StringPool_Allocate(0x10);
        if (v != 0) {
            v = StringPool_Construct((StringPool *)v);
        }
        g_stringPool = (StringPool *)v;
    }
    s1 = (int *)StringPool_Intern(g_stringPool, 0);
    old = (int *)self->_debugString;
    if (old != 0) {
        hd = old - 2;
        v0 = old[-1] - 1;
        old[-1] = v0;
        if (v0 == 0) {
            StringChunk_ReleaseHeader((StringChunk *)*hd, (StringTokenHeader *)hd);
        }
    }
    self->_debugString = (int)s1;
    ((igBoolList *)self->_boolList)->_count = 0;
    l = (igDataList *)self->_boolList;
    /* matching construct: list shrink guard spelled as nested ifs ("&&" or "> 4" changes the compare) */
    if (l->_capacity > 4) { if (l->_count < 5) List_Reserve(l, 4, 1); }
    ((igIntList *)self->_intList)->_count = 0;
    l = (igDataList *)self->_intList;
    if (l->_capacity > 4) { if (l->_count < 5) List_Reserve(l, 4, 4); }
    ((igFloatList *)self->_floatList)->_count = 0;
    l = (igDataList *)self->_floatList;
    if (l->_capacity > 4) { if (l->_count < 5) List_Reserve(l, 4, 4); }
    ((igLongList *)self->_longList)->_count = 0;
    l = (igDataList *)self->_longList;
    if (l->_capacity > 4) { if (l->_count < 5) List_Reserve(l, 4, 8); }
    ((igVec3fList *)self->_vec3fList)->_count = 0;
    l = (igDataList *)self->_vec3fList;
    if (l->_capacity > 4) { if (l->_count < 5) List_Reserve(l, 4, 12); }
    ((igMatrix44fList *)self->_matrix44fList)->_count = 0;
    l = (igDataList *)self->_matrix44fList;
    if (l->_capacity > 4) { if (l->_count < 5) List_Reserve(l, 4, 64); }
    sl = (igDataList *)self->_stringList;

    /* matching construct: separate n/i counters per loop and block-local rr/m/j fix register allocation */
    n1 = sl->_count;
    for (i1 = 0; i1 < n1; i1++) {
        int **slot = &((int **)sl->_data)[i1];
        int *rr;
        if (g_stringPool == 0) {
            v = StringPool_Allocate(0x10);
            if (v != 0) {
                v = StringPool_Construct((StringPool *)v);
            }
            g_stringPool = (StringPool *)v;
        }
        rr = (int *)StringPool_Intern(g_stringPool, 0);
        old = *slot;
        if (old != 0) {
            hd = old - 2;
            v0 = old[-1] - 1;
            old[-1] = v0;
            if (v0 == 0) {
                StringChunk_ReleaseHeader((StringChunk *)*hd, (StringTokenHeader *)hd);
            }
        }
        *slot = rr;
    }

    sl->_count = 0;
    sl = (igDataList *)self->_stringList;
    if (sl->_capacity > 4) { if (sl->_count < 5) List_Reserve(sl, 4, 4); }
    lo = (igDataList *)self->_objectList;

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
    l = (igDataList *)self->_objectList;
    if (l->_capacity > 4) { if (l->_count < 5) List_Reserve(l, 4, 4); }
}

void beMessengerDelay_Clear(beMessengerDelay *self) {
    void *v;
    int v0;
    int *old;
    int *hd;
    int *s1;
    self->_isUse = 0;
    self->_sendTime = 0;
    if (g_stringPool == 0) {
        v = StringPool_Allocate(0x10);
        if (v != 0) {
            v = StringPool_Construct((StringPool *)v);
        }
        g_stringPool = (StringPool *)v;
    }
    s1 = (int *)StringPool_Intern(g_stringPool, 0);
    old = (int *)self->_groupName;
    if (old != 0) {
        hd = old - 2;
        v0 = old[-1] - 1;
        old[-1] = v0;
        if (v0 == 0) {
            StringChunk_ReleaseHeader((StringChunk *)*hd, (StringTokenHeader *)hd);
        }
    }
    self->_groupName = (int)s1;
    if (g_stringPool == 0) {
        v = StringPool_Allocate(0x10);
        if (v != 0) {
            v = StringPool_Construct((StringPool *)v);
        }
        g_stringPool = (StringPool *)v;
    }
    s1 = (int *)StringPool_Intern(g_stringPool, 0);
    old = (int *)self->_infoName;
    if (old != 0) {
        hd = old - 2;
        v0 = old[-1] - 1;
        old[-1] = v0;
        if (v0 == 0) {
            StringChunk_ReleaseHeader((StringChunk *)*hd, (StringTokenHeader *)hd);
        }
    }
    self->_infoName = (int)s1;
    self->_ramNo = 0;
    if (g_stringPool == 0) {
        v = StringPool_Allocate(0x10);
        if (v != 0) {
            v = StringPool_Construct((StringPool *)v);
        }
        g_stringPool = (StringPool *)v;
    }
    s1 = (int *)StringPool_Intern(g_stringPool, 0);
    old = (int *)self->_message;
    if (old != 0) {
        hd = old - 2;
        v0 = old[-1] - 1;
        old[-1] = v0;
        if (v0 == 0) {
            StringChunk_ReleaseHeader((StringChunk *)*hd, (StringTokenHeader *)hd);
        }
    }
    self->_message = (int)s1;
    beMessengerArgData_Clear((beMessengerArgData *)self->_argData);
}

void beMessenger_Activate(beMessenger *self, int unusedArg)
{
    igInsightCore_AddToScheduler((igInsightCore *)self->_insight, (igObject *)self); /* matching construct: char * parameter on FUN_00236*, receiver passed as a byte pointer */
}

void beMessenger_Deactivate(beMessenger *self, int unusedArg)
{
    igInsightCore_RemoveFromScheduler((igInsightCore *)self->_insight, (igObject *)self); /* matching construct: char * parameter on FUN_00236*, receiver passed as a byte pointer */
}

void beMessenger_Start(void)
{
}

void beMessenger_Stop(void)
{
}

int beMessenger_AddInfo(beMessenger *self) {
    if (self->_isMemoryAssign == 0) {
        beMessenger_InitializeMemory(self);
    }
    return 0;
}

void beMessenger_RemoveAllInfo(beMessenger *self)
{
    beMessenger_ResetMemory(self);
}

/* The insight object's clock (+80, 64 bits). */
struct Insight {
    static long long Get(igInsightCore *i) { return i->_worldTime; }
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

static inline beMessengerDelay *DelayAt(beMessenger *self, int index)
{
    return ((beMessengerDelay **)((igObjectList *)self->_delayStack)->_data)[index];
}

static inline long long SendTimeOf(const beMessengerDelay *delay) { return delay->_sendTime; }

/* Sends the queued messages whose time has come, oldest first, and moves each sent row to the back of the
 * queue; while the clock is frozen it moves every queued time forward by the time spent frozen instead. */
void beMessenger_Update(beMessenger *self)
{
    if (self->_isMemoryAssign != 0) {
        igObjectList *stack = (igObjectList *)self->_delayStack;
        int count = stack->_count;
        if (count != 0) {
            if (self->_freezeTime == 0) {
                long long now = Insight::Get((igInsightCore *)self->_insight);
                int i;
                for (i = 0; i < count; i++) {
                    igSmartPointer<beMessengerDelay> row(DelayAt(self, 0), kRetainReference);
                    if (!row->_isUse) break;
                    if (now < SendTimeOf(row)) break;
                    beMessenger_SelectReceivers(self, (char *)row->_groupName, (char *)row->_infoName, row->_ramNo);
                    {
                        ObjectRef saved(0);
                        saved = (igObject *)self->_argData;
                        DelayRef::assign((igObject **)&self->_argData, (igObject *)row->_argData);
                        RowOps::SetArg(row.get(), saved.get());
                    }
                    beMessenger_DispatchSelected(self, (const char *)row->_message);
                    beMessengerDelay_Clear(row.p);
                    stack = (igObjectList *)self->_delayStack;
                    DelayRef::release(((igObject **)stack->_data)[0]);
                    List_RemoveWordAt((igDataList *)stack, 0);
                    ((igObject **)stack->_data)[stack->_count] = 0;
                    ObjectList_AppendRetained((igObjectList *)self->_delayStack, (igObject *)row.p);
                }
            } else {
                long long now = Insight::Get((igInsightCore *)self->_insight);
                long long elapsed = now - self->_freezeTime;
                int i;
                for (i = 0; i < count; i++) {
                    beMessengerDelay *delay = DelayAt(self, i);
                    if (!delay->_isUse) break;
                    delay->_sendTime = elapsed + SendTimeOf(delay);
                }
                self->_freezeTime = now;
            }
            beMessengerArgData_Clear((beMessengerArgData *)self->_argData);
        }
    }
}

void beMessenger_SetFreezeTime(beMessenger *self, int frozen) {
    if (frozen != 0) {
        self->_freezeTime = (long long) ((igInsightCore *)self->_insight)->_worldTime;
        return;
    }
    self->_freezeTime = 0;
}

unsigned int beMessenger_ResolveEnumValue(beMessenger *self, igMetaEnum *metaEnum, const char *name) {
    int value;
    int found;
    if ((g_resolveEnumLastMetaEnum[0] == (int)metaEnum) && (strcmp((const char *)&g_resolveEnumLastName[0], name) == 0)) {
        return g_resolveEnumLastValue[0];
    }
    igMetaEnum_GetValueByName(&found, metaEnum, name, &value);
    if (*(int *)(unsigned)&found == g_resultSuccess.v) {
        g_resolveEnumLastMetaEnum[0] = (int)metaEnum;
        strcpy((char *)&g_resolveEnumLastName[0], name);
        g_resolveEnumLastValue[0] = value;
        return value;
    }
    return -1;
}

struct Str { static inline const char *intern(const char *text) {
    const char *token;
    if (text == 0) {
        token = 0;
    } else {
        if (g_stringPool == 0) {
            StringPool *pool = (StringPool *)StringPool_Allocate(0x10);
            if (pool != 0) pool = StringPool_Construct(pool);
            g_stringPool = pool;
        }
        token = StringPool_Intern(g_stringPool, text);
    }
    return token;
} };

void beMessenger_RegisterReceiver(beMessenger *self, beBaseInfoRam *recv, const char *name, const char *text, int value)
{
    int allocator;
    igIntList *l;
    int n;

    igSmartPointer<beMessengerGroup> grp((beMessengerGroup *)igProperty_FindByName((igObjectList *)self->_groupList, g_propertyNameField, name));
    RETAIN_REF(grp.p)
    if (grp.p == 0) {
        allocator = (int)igObject_GetAllocator(self);
        allocator = g_useOwnerAllocator ? allocator : (int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleUser1);
        RELEASE_REF(grp.p)
        grp.p = beMessengerGroup_Create(allocator);
        igNamedObject_SetName((igNamedObject *)grp.p, name);
        ObjectList_AppendRetained((igObjectList *)self->_groupList, (igObject *)grp.p);
    }
    ObjectList_AppendRetained((igObjectList *)grp.p->_ramList, (igObject *)recv);
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
void beMessenger_RegisterReceiverFromInfo(beMessenger *self, beBaseInfoRam *ram, const char *group) {
    beBaseInfo *info = (beBaseInfo *)ram->_parentInfo;
    int *recv = (int *)info->_name;
    int t = ram->_ramNo;
    recv = recv != 0 ? recv : (int *)emptyString;
    beMessenger_RegisterReceiver(self, ram, group, (const char *)recv, t);
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
static inline char *Intern(const char *text) {
    POOL();
    return StringPool_Intern(g_stringPool, text);
}
static inline void SetGroupName(Work *w, const char *c) { char *s; s = Intern(c); char *o = (char *)w->_groupName; STR_RELEASE(o); w->_groupName = (int)s; }
static inline void SetInfoName(Work *w, const char *n) { char *s; s = Intern(n); char *o = (char *)w->_infoName; STR_RELEASE(o); w->_infoName = (int)s; }
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
        List_InsertWords((igDataList *)dst, 0, 1, (void *)&tmp.value);
    }
};

#define IW ((Work *)item.p)

void beMessenger_SelectReceivers(beMessenger *self, const char *category, const char *name, int id) {
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
            List_RemoveWordAt((igDataList *)l, i);
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
        if (q->_capacity > 4 && q->_count < 5) List_Reserve((igDataList *)q, 4, 4);
        {
            List *r = (List *)IW->_findRamList;
            int m = r->_count, k;
            for (k = 0; k < m; k++) { Obj *o = LDATA(r)[k]; OBJ_RELEASE(o); }
            m = r->_count;
            for (k = 0; k < m; k++) LDATA(r)[k] = 0;
            r->_count = 0;
            q = (List *)IW->_findRamList;
            if (q->_capacity > 4 && q->_count < 5) List_Reserve((igDataList *)q, 4, 4);
        }
        {
            List *l2 = (List *)self->_workStack;
            last = l2->_count - 1;
            Obj *o = LDATA(l2)[last];
            OBJ_RELEASE(o);
            List_RemoveWordAt((igDataList *)l2, last);
            LDATA(l2)[l2->_count] = 0;
            RefTmp::PushFront(self, item.p);
        }
    }

    work = (Work *)LDATA((List *)self->_workStack)[0];
    if (((List *)work->_findRamList)->_count == 0) {
        g = (Group *)igProperty_FindByName((igObjectList *)self->_groupList, g_propertyNameField, (const char *)work->_groupName);
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
                    ObjectList_AppendRetained((igObjectList *)work->_findRamList, LDATA((List *)g->_ramList)[k]);
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

void beMessenger_DispatchSelected(beMessenger *self, const char *name)
{
    int n;
    int alloc;
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
    if (g_stringPool == 0) {
        alloc = (int)StringPool_Allocate(16);
        if (alloc) alloc = (int)StringPool_Construct((StringPool *)alloc);
        g_stringPool = (StringPool *)alloc;
    }
    str = (int)StringPool_Intern(g_stringPool, (const char *)name);
    old = work->_message;
    if (old) {
        header = (int *)(old - 8);
        refs = *(int *)(old - 4) - 1;
        *(int *)(old - 4) = refs;
        if (!refs) StringChunk_ReleaseHeader((StringChunk *)*header, (StringTokenHeader *)header);
    }
    work->_message = str;
    igObjectList *fl = (igObjectList *)work->_findRamList;
    count = fl->_count;
    if (strcmp(name, SEARCH) == 0) {
        matches = 0;
        for (i = 0; i < count; i++) {
            igIntList *list = (igIntList *)work->_findRamNoList; int have = ((int *)list->_data)[i]; if (work->_ramNo == -1 || *(int *)(list->_data + i * 4) /* matching construct: byte-offset element read keeps the data load inside the loop */ == -1 || have == work->_ramNo) matches++;
        }
        {
            if (matches) {
                igBoolList *bla = (igBoolList *)((beMessengerArgData *)self->_argData)->_boolList;
                int na = bla->_count;
                if (na < bla->_capacity) bla->_count = na + 1; else List_Resize(bla, na + 1, 1);
                ListStore(bla, na, true);
                il = (igIntList *)((beMessengerArgData *)self->_argData)->_intList;
                n = il->_count;
                if (n < il->_capacity) il->_count = listCount(il) + 1; else List_Resize(il, n + 1, 4);
                ((int *)il->_data)[n] = matches;
            } else {
                igBoolList *blc = (igBoolList *)((beMessengerArgData *)self->_argData)->_boolList;
                n = blc->_count;
                if (n < blc->_capacity) blc->_count = n + 1; else List_Resize(blc, n + 1, 1);
                ListStore(blc, n, false);
                il = (igIntList *)((beMessengerArgData *)self->_argData)->_intList;
                int nd = il->_count;
                if (nd < il->_capacity) il->_count = listCount(il) + 1; else List_Resize(il, nd + 1, 4);
                ListStore(il, nd, 0);
            }
        }
    } else if (strcmp(name, FIND_SPACE_3) == 0) {
        ObjRef held(0);
        for (i2 = 0; i2 < count; i2++) {
            igObjectList *list = (igObjectList *)work->_findRamList;
            beBaseInfoRam *obj = ((beBaseInfoRam **)list->_data)[i2];
            if (((beBaseInfoRam **)list->_data)[i2]->_isRun == 0) {
                held = (DispatchObj *)obj;
                break;
            }
        }
        if (held.value) ObjectList_AppendRetained((igObjectList *)((beMessengerArgData *)self->_argData)->_objectList, (igObject *)held.value);
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
            if (r->Check(obj, work) == 0) r->Send(obj, (int)name);
            if (work->_ramNo == -2) break;
        }
    }
}

void beMessenger_SelectGroupRam(void *self,const char *category,int id){beMessenger_SelectReceivers((beMessenger *)self,category,0,id);}
void beMessenger_SelectGroup(beMessenger *self,const char *category){beMessenger_SelectReceivers(self,category,0,-1);}
void beMessenger_SendNamed(beMessenger *self,const char *category,const char *name,int id,const char *key){beMessenger_SelectReceivers(self,category,name,id);beMessenger_DispatchSelected(self,key);}
void beMessenger_SendRam(beMessenger *self,const char *category,int id,const char *key){beMessenger_SelectGroupRam(self,category,id);beMessenger_DispatchSelected(self,key);}
void beMessenger_SendGroup(beMessenger *self,const char *category,const char *key){beMessenger_SelectGroup(self,category);beMessenger_DispatchSelected(self,key);}

#define SET_STRING(field, text) { \
    beMessengerDelay *r = (beMessengerDelay *)row.p; \
    if (g_stringPool == 0) { \
        StringPool *pool = (StringPool *)StringPool_Allocate(0x10); \
        if (pool != 0) pool = StringPool_Construct(pool); \
        g_stringPool = pool; \
    } \
    token = StringPool_Intern(g_stringPool, (text)); \
    int *old = (int *)r->field; \
    if (old) { \
        int *header = old - 2; \
        if (--old[-1] == 0) StringChunk_ReleaseHeader((StringChunk *)*header, (StringTokenHeader *)header); \
    } \
    r->field = (int)token; }

void beMessenger_PrepareDelayedSelection(beMessenger *self, const char *group, const char *name, int number)
{
    int allocator;
    const char *token;
    beMessengerDelayList *stack;
    int last;

    if (self->_isMemoryAssign == 0)
        beMessenger_InitializeMemory(self);
    else
        beMessengerArgData_Clear((beMessengerArgData *)self->_argData);
    stack = (beMessengerDelayList *)self->_delayStack;
    last = stack->_count - 1;
    igSmartPointer<beMessengerDelay> row(((beMessengerDelay **)stack->_data)[last]);
    RETAIN_REF(row.p)
    if (row->_isUse) {
        allocator = (int)igObject_GetAllocator(self);
        allocator = g_useOwnerAllocator ? allocator : (int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleUser1);
        RELEASE_REF(row.p)
        row.p = beMessengerDelay_Create(allocator);
        ObjectList_AppendRetained((igObjectList *)self->_delayStack, (igObject *)row.p);
    }
    SET_STRING(_groupName, group)
    SET_STRING(_infoName, name)
    row->_ramNo = number;
}

void beMessenger_EnqueueSelected(beMessenger *self, const char *text, long long delay)
{
    igObjectList *stack;
    int idx, last, i, n, st;
    igObjectList *list;
    const char *token;

    stack = (igObjectList *)self->_delayStack;
    idx = stack->_count - 1;
    igSmartPointer<beMessengerDelay> row(((beMessengerDelay **)stack->_data)[idx], kRetainReference);
    {
        long long now = Insight::Get((igInsightCore *)self->_insight);
        row->_sendTime = now + delay * 16666666;
    }

    {
        ObjectRef saved(0);
        saved = (igObject *)self->_argData;
        DelayRef::assign((igObject **)&self->_argData, (igObject *)row->_argData);
        RowOps::SetArg(row.get(), saved.get());
    }

    {
        beMessengerDelay *r = row.p;
        if (g_stringPool == 0) {
            StringPool *pool = (StringPool *)StringPool_Allocate(0x10);
            if (pool != 0) pool = StringPool_Construct(pool);
            g_stringPool = (StringPool *)pool;
        }
        token = StringPool_Intern(g_stringPool, text);
        int *old = (int *)r->_message;
        if (old) {
            int *header = old - 2;
            if (--old[-1] == 0) StringChunk_ReleaseHeader((StringChunk *)*header, (StringTokenHeader *)header);
        }
        r->_message = (int)token;
    }
    row->_isUse = 1;

    stack = (igObjectList *)self->_delayStack;
    last = stack->_count - 1;
    DelayRef::release(((igObject **)stack->_data)[last]);
    List_RemoveWordAt((igDataList *)stack, last);
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
    List_InsertWords((igDataList *)st, i, 1, (void *)&tmp.value);
}

void beMessenger_SendDelayedNamed(beMessenger *self,const char *group,const char *name,int id,const char *message,long long delay){beMessenger_PrepareDelayedSelection(self,group,name,id);beMessenger_EnqueueSelected(self,message,delay);}
void beMessenger_SendDelayedGroup(beMessenger *self,const char *group,const char *message,long long delay){beMessenger_PrepareDelayedSelection(self,group,0,-1);beMessenger_EnqueueSelected(self,message,delay);}
void beMessenger_PrepareDelayedGroup(beMessenger *self,const char *group){beMessenger_PrepareDelayedSelection(self,group,0,-1);}

static inline void insertWords(igObjectList *l, int at, int n, RefObj **src) {
    int i;
    for (i = 0; i < n; i++) {
        RefObj *v = src[i];
        if (v) ++v->_refCount;
    }
    List_InsertWords((igDataList *)l, at, n, (void *)src);
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
        List_RemoveWordAt((igDataList *)stack, last);
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
        List_RemoveWordAt((igDataList *)list, 0);
        ((RefObj **)list->_data)[list->_count] = 0;
        ObjectList_AppendRetained((igObjectList *)self->_pushPopStack, saved.p);
    }
    --self->_pushPopCount;
}

void beMessenger_SetRunCheck(beMessenger *self, unsigned char enabled) {
    beMessengerArgData *args = (beMessengerArgData *)self->_argData;
    args->_isRunCheck = enabled;
}

int beMessenger_GetBoolCount(beMessenger *self) {
    beMessengerArgData *args = (beMessengerArgData *)self->_argData;
    igBoolList *list = (igBoolList *)args->_boolList;
    return list->_count;
}

void beMessenger_ResizeBool(beMessenger *self, int count) {
    igBoolList *list;
    list = (igBoolList *)((beMessengerArgData *)self->_argData)->_boolList;
    if (count >= 0) {
        if (count <= list->_capacity) {
            list->_count = count;
            return;
        }
        List_Resize(list, count, 1);
    }
}

void beMessenger_AppendBool(beMessenger *self, unsigned char value)
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

void beMessenger_SetBool(beMessenger *self, int index, unsigned char value) {
    igBoolList *l = (igBoolList *)((beMessengerArgData *)self->_argData)->_boolList;
    int n = l->_count;
    if (n != 0 && index >= 0 && index < n) {
        ((char *)l->_data)[index] = value;
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

void beMessenger_SetInt(beMessenger *self, int index, int value) {
    beMessengerArgData *args = (beMessengerArgData *)self->_argData;
    igIntList *list = (igIntList *)args->_intList;
    int n = list->_count;
    if ((n != 0) && (index >= 0) && (index < n)) {
        ((int *)list->_data)[index] = value;
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

void beMessenger_AppendLong(beMessenger *self, long long value) {
    int index;
    beMessengerArgData *args;
    igLongList *list;

    args = (beMessengerArgData *)self->_argData;
    list = (igLongList *)args->_longList;
    index = list->_count;
    if (index < list->_capacity) {
        list->_count = index + 1;
    } else {
        List_Resize(list, index + 1, 8);
    }
    ((long long *)list->_data)[index] = value;
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

igVec3f beMessenger_GetVec3(beMessenger *self, int index) {
    beMessengerArgData *args = (beMessengerArgData *)self->_argData;
    igVec3fList *list = (igVec3fList *)args->_vec3fList;
    return ((igVec3f *)list->_data)[index];
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
    igMatrix44f_Copy((char *)list->_data + index * 64, value);
}

void beMessenger_GetMatrix(void *out, beMessenger *self, int index)
{
    igMatrix44f_Copy(out, (void *)(((igMatrix44fList *)((beMessengerArgData *)self->_argData)->_matrix44fList)->_data + index * 64));
}

int beMessenger_GetObjectCount(beMessenger *self) {
    beMessengerArgData *args = (beMessengerArgData *)self->_argData;
    igObjectList *list = (igObjectList *)args->_objectList;
    return list->_count;
}

void beMessenger_AppendObject(beMessenger *self, igObject *object)
{
    ObjectList_AppendRetained((igObjectList *)((beMessengerArgData *)self->_argData)->_objectList, object);
}

void beMessenger_ClearObjects(beMessenger *self) {
    beMessengerArgData *args;
    igObjectList *l;
    int n;
    int i;
    igObject *o;
    int n2;
    int j;

    args = (beMessengerArgData *)self->_argData;
    l = (igObjectList *)args->_objectList;
    n = l->_count;
    for (i = 0; i < n; i++) {
        o = ((igObject **)l->_data)[i];
        if (o != 0) {
            o->_refCount = (int)o->_refCount - 1;
            if (((unsigned long long) ((long long)(int)o->_refCount << 0x29) >> 0x29) == 0) {
                igObject_Destroy(o);
            }
        }
    }
    n2 = l->_count;
    for (j = 0; j < n2; j++) {
        ((igObject **)l->_data)[j] = 0;
    }
    l->_count = 0;
}

igObject *beMessenger_GetObject(beMessenger *self, int index) {
    beMessengerArgData *args = (beMessengerArgData *)self->_argData;
    igObjectList *list = (igObjectList *)args->_objectList;
    return *(igObject **)(list->_data + (index * 4));
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
        if (g_stringPool == 0) {
            pool = StringPool_Allocate(16);
            if (pool)
                pool = StringPool_Construct((StringPool *)pool);
            g_stringPool = (StringPool *)pool;
        }
        token = (int)StringPool_Intern(g_stringPool, text);
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
const char *beMessenger_GetString(beMessenger *self, int index)
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
            StringChunk_ReleaseHeader((StringChunk *)header->owner, header);
    }
    return (const char *)token;
}

igMetaObject *beMessenger_GetMeta(void)
{
    return g_beMessenger_metaObject;
}
