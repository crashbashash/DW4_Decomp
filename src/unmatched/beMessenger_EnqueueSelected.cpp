/* The release time is the insight clock plus `delay` frames of 16,666,666 clock units each. The
 * delay record and the temporary that holds the old argument object are smart references with
 * destructors, which keeps them in stack memory; both destructors have the same body, and the unit
 * declares two classes so each local owns one emitted copy. The insertion search reads the list
 * through helpers that take the list base as a parameter, which keeps separate index / byte-offset
 * inductions and the list data pointer hoisted out of the loop; a direct `list->data[i]` is turned
 * into one pointer induction by this compiler. The dummy re-read `l2 = list` at the bottom of the
 * loop and the integer type of `cur` fix the preheader order and the register assignment.
 * Reference counts follow the usual inline pattern: the low 23 bits of the word at +4 are the
 * count and the object is destroyed at 0. */
#include "dw4/reflected.h"

extern "C" {
void igObject_Destroy(void *);
void List_RemoveWordAt(void *, int);
void List_InsertWords(void *, int, int, void *);
void *FUN_002eb010(int);
void *StringPool_Construct(void *);
const char *StringPool_Intern(void *, const char *);
void StringChunk_ReleaseHeader(int, int *);
extern void *DAT_00586f20[4];
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

/* Owning reference to the delay record. */
struct RowRef {
    igObject *p;
    RowRef(igObject *o) { p = o; if (p) ++p->_refCount; }
    ~RowRef() { igObject *o = p; RELEASE_OBJ(o) }
};

/* Owning reference to the old argument object. */
struct SavedRef {
    igObject *p;
    SavedRef(igObject *o) { p = o; }
    void operator=(igObject *in) {
        igObject *old;
        if (in) ++in->_refCount;
        old = p;
        RELEASE_OBJ(old)
        p = in;
    }
    ~SavedRef() { igObject *o = p; RELEASE_OBJ(o) }
};

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
 * to the list insert. Its constructor reads its stored word back through a laundered pointer and
 * fetches the delay-stack handle between that read and the null test. */
struct Ref {
    igObject * value;
    Ref(igObject *p, beMessenger *m, int &out) : value(p) {
        Ref *s = (Ref *)(int)this;
        igObject *v = s->value;
        out = m->_delayStack;
        if (v) ++v->_refCount;
        Ref *r = s;
        (void)r;
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

extern "C" void beMessenger_EnqueueSelected(beMessenger *self, const char *text, long long delay)
{
    igObjectList *stack;
    int idx, last, i, n, st;
    igObjectList *list;
    const char *token;

    stack = (igObjectList *)self->_delayStack;
    idx = stack->_count - 1;
    RowRef row(((igObject **)stack->_data)[idx]);
    {
        long long now = Insight::Get((igInsightCore *)self->_insight);
        ((beMessengerDelay *)row.p)->_sendTime = now + delay * 16666666;
    }

    {
        SavedRef saved(0);
        saved = (igObject *)self->_argData;
        beMessengerDelay *r = (beMessengerDelay *)row.p;
        Ref::assign((igObject **)&self->_argData, (igObject *)r->_argData);
        r = (beMessengerDelay *)row.p;
        RowOps::SetArg(r, saved.p);
    }

    {
        beMessengerDelay *r = (beMessengerDelay *)row.p;
        if (DAT_00586f20[0] == 0) {
            void *pool = FUN_002eb010(0x10);
            if (pool != 0) pool = StringPool_Construct(pool);
            DAT_00586f20[0] = pool;
        }
        token = StringPool_Intern(DAT_00586f20[0], text);
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
    Ref::release(((igObject **)stack->_data)[last]);
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
    Ref tmp(row.p, self, st);
    List_InsertWords((void *)st, i, 1, (void *)&tmp.value);
}
