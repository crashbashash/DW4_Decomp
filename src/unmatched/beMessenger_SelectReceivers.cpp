/* Selects the receivers of a messenger send. The messenger keeps a stack of work records
 * (_workStack); the record whose group name (category), info name and ram number match is moved to
 * the front. If none matches, the oldest record (the last one) is recycled: its names and ram
 * number are replaced, its two result lists are cleared, and it is moved to the front. When the
 * front record has no ram receivers yet, they are looked up in the messenger group registered
 * under the record's group name and copied, one per info name that matches the record's info name.
 * Several helpers are written in an unusual way on purpose: each form is the one that reproduces
 * the instruction stream, register allocation and delay-slot schedule, and each is marked. */
#include "dw4/reflected.h"
extern "C" {
void igObject_Destroy(void *);
int igStrCmp(const char *, const char *);
void List_RemoveWordAt(void *, int);
void List_InsertWords(void *, int, int, void *);
void List_Reserve(void *, int, int);
void List_Resize(void *, int, int);
void StringChunk_ReleaseHeader(void *, int);
void *igProperty_FindByName(void *, int, char *);
int FUN_002eb010(int);
int StringPool_Construct(int);
char *StringPool_Intern(int, char *);
void StringList_CopyRetained(char **, void *, int);
void ObjectList_AppendRetained(void *, void *);
extern int DAT_00586f20[4]; /* interned-string pool singleton */
extern int DAT_00585be0[4]; /* property type used for the group lookup */
}

/* Reference-counted object prefix: the count is the low 23 bits at +4. */
typedef igObject Obj;

#define OBJ_RELEASE(o) if (o) { --(o)->_refCount; if (((o)->_refCount & 0x7fffff) == 0) igObject_Destroy(o); }
/* Interned strings carry {owner, count} in the 8 bytes before the text. */
#define STR_RELEASE(s) if (s) { int *h_ = (int *)((char *)(s) - 8); if (--h_[1] == 0) StringChunk_ReleaseHeader((void *)h_[0], (int)h_); }
#define POOL() if (!DAT_00586f20[0]) { int p_ = FUN_002eb010(16); if (p_) p_ = StringPool_Construct(p_); DAT_00586f20[0] = p_; }

typedef beMessengerWork Work;
/* Stack reference: retains on construction, releases when it leaves scope. */
struct Ref {
    Obj *p;
    Work *operator->() { return (Work *)p; }
    Ref(Obj *o) { p = o; if (p) p->_refCount++; }
    /* The assignment inside the condition is what reproduces retail's
     * register choice around the inlined copies of this release. */
    ~Ref() { Obj *o; if ((o = p) != 0) { --o->_refCount; if ((o->_refCount & 0x7fffff) == 0) igObject_Destroy(o); } }
};

/* The lists are igObjectList (_count +8, _capacity +12, _data +16); the data
 * handle is read as an array of object pointers. */
typedef igObjectList List;
#define LDATA(l) ((Obj **)(l)->_data)

/* beMessengerWork: the work record, reflected fields _groupName, _infoName,
 * _ramNo, _findRamNoList and _findRamList. */
/* A second reader of the info name; the first load is not reused for the null-handling comparison,
 * and this access path does not either. */
struct WorkOps {
static inline char *InfoName2(Work *w) { return (char *)((volatile Work *)w)->_infoName; }
static inline char *Intern(char *text) {
    POOL();
    return StringPool_Intern(DAT_00586f20[0], text);
}
static inline void SetGroupName(Work *w, char *c) { char *s; s = Intern(c); char *o = (char *)w->_groupName; STR_RELEASE(o); w->_groupName = (int)s; }
static inline void SetInfoName(Work *w, char *n) { char *s; s = Intern(n); char *o = (char *)w->_infoName; STR_RELEASE(o); w->_infoName = (int)s; }
};

typedef beMessengerGroup Group;
typedef beMessenger Messenger;

/* A retained word that lives on the stack and is then stored into a list by address. It has no
 * destructor: the list takes the reference. The constructor reads its own stored word back through
 * a laundered pointer and fetches the work-stack handle between that read and the null test; that
 * shape makes the address register, delay slot and stack layout come out. */
struct RefTmp {
    Obj * volatile value;
    RefTmp(Obj *p, Messenger *m, int &out) : value(p) {
        RefTmp *s = (RefTmp *)(int)this;
        Obj *v = s->value;
        out = m->_workStack;
        if (v) ++v->_refCount;
        RefTmp *r = s;
        (void)r;
    }
    static void PushFront(Messenger *m, Obj *obj) {
        int dst;
        RefTmp tmp(obj, m, dst);
        List_InsertWords((void *)dst, 0, 1, (void *)&tmp.value);
    }
};

extern "C" void beMessenger_InitializeMemory(Messenger *);
extern "C" void beMessengerArgData_Clear(void *);

#define IW ((Work *)item.p)

extern "C" void beMessenger_SelectReceivers(Messenger *self, char *category, char *name, int id) {
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
    else beMessengerArgData_Clear((void *)self->_argData);

    found = 0;
    n = ((List *)self->_workStack)->_count;
    for (i = 0; i < n; i++) {
        Ref item(LDATA((List *)self->_workStack)[i]);
        if (!IW->_groupName) continue;
        if (igStrCmp((char *)IW->_groupName, category)) continue;
        if (IW->_infoName == 0 || name == 0) {
            if (WorkOps::InfoName2(IW) != name) continue;
        } else if (igStrCmp((char *)IW->_infoName, name)) continue;
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
        Ref item(LDATA((List *)self->_workStack)[lastIdx]);
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
        g = (Group *)igProperty_FindByName((void *)self->_groupList, DAT_00585be0[0], (char *)work->_groupName);
        if (g) {
            m = ((List *)g->_ramList)->_count;
            for (k = 0; k < m; k++) {
                char *tmp;
                char *s;
                StringList_CopyRetained(&tmp, (void *)g->_infoNameList, k);
                s = tmp;
                STR_RELEASE(s);
                if (!(work->_infoName && s) || !igStrCmp((char *)work->_infoName, s)) {
                    src = &LDATA((List *)g->_ramNoList)[k];
                    l = (List *)work->_findRamNoList;
                    c = l->_count;
                    /* The volatile read keeps the count increment from
                     * being folded into the earlier load. */
                    if (c < l->_capacity) l->_count = ((volatile List *)l)->_count + 1;
                    else List_Resize(l, c + 1, 4);
                    LDATA(l)[c] = *src;
                    ObjectList_AppendRetained((void *)work->_findRamList, LDATA((List *)g->_ramList)[k]);
                }
            }
        }
    }
}
