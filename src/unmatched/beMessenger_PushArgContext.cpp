/* The saved object lives in an owning stack reference (ObjectRef) released at block end. The
 * helper shapes below (a copy-constructed stack temporary that also reads the stack handle, a
 * volatile memory-resident insert slot) are the forms that reproduce the register allocation and
 * delay-slot schedule, not claimed original spellings. */
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
    static void assign(RefObj * volatile *dest, RefObj *incoming) {
        RefObj *outgoing;
        if (incoming) ++incoming->_refCount;
        outgoing = *dest;
        release(outgoing);
        *dest = incoming;
    }
};
/* Retained word handed to List_InsertWords: the stack list takes the reference, so the slot is not released. */
struct InsertSlot {
    RefObj * volatile value;
    /* Retains the incoming object; also loads the push/pop stack handle
     * between the retained-pointer read and its null test. */
    InsertSlot(RefObj *p, beMessenger *m, int &out) : value(p) {
        InsertSlot *s = (InsertSlot *)(int)this;
        RefObj *v = s->value;
        out = m->_pushPopStack;
        if (v) ++v->_refCount;
        InsertSlot *r = s;
        (void)r;
    }
};
void beMessenger_PushArgContext(beMessenger *self) {
    int idx;
    int last;
    igObjectList *stack;
    int st;
    {
        ObjectRef saved(0);
        saved = (RefObj *)self->_argData;
        stack = (igObjectList *)self->_pushPopStack;
        idx = stack->_count - 1;
        ObjectRef::assign((RefObj * volatile *)&self->_argData, ((RefObj **)stack->_data)[idx]);
        stack = (igObjectList *)self->_pushPopStack;
        last = stack->_count - 1;
        ObjectRef::release(((RefObj **)stack->_data)[last]);
        List_RemoveWordAt(stack, last);
        ((RefObj **)stack->_data)[stack->_count] = 0;
        InsertSlot tmp(saved.p, self, st);
        List_InsertWords((void *)st, 0, 1, (void *)&tmp.value);
    }
    ++self->_pushPopCount;
}
