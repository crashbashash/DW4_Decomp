#include "dw4/reflected.h"
typedef igObject RefObj;
extern "C" {
void igObject_Destroy(RefObj *);
void List_RemoveWordAt(void *, int);
void List_InsertWords(void *, int, int, void *);
void beMessenger_PushArgContext(beMessenger *self);
}
/* Owning stack reference to the saved arg-data object: starts empty, takes a retained object by
 * assignment and releases it on scope exit (reference count in the low 23 bits of _refCount). */
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
