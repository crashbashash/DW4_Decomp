#include "dw4/reflected.h"
typedef igObject RefObj;
extern "C" {
void igObject_Destroy(RefObj *);
void beMessengerArgData_Clear(int);
void List_RemoveWordAt(void *, int);
void ObjectList_AppendRetained(int, RefObj *);
}
struct Ref {
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
/* Owning stack reference to the popped arg-data object: starts empty, takes the object by
 * assignment (retain new, release old) and releases it on scope exit (reference count in the low
 * 23 bits of _refCount). */
class ObjectRef {
public:
    RefObj *p;
    ObjectRef() : p(0) {}
    void operator=(RefObj *incoming) { Ref::assign(&p, incoming); }
    ~ObjectRef() { RefObj *o = p; if (o != 0) { --o->_refCount; if ((o->_refCount & 0x7fffff) == 0) igObject_Destroy(o); } }
};
extern "C" void beMessenger_PopArgContext(beMessenger *self) {
    igObjectList *list;
    beMessengerArgData_Clear(self->_argData);
    {
        ObjectRef saved;
        saved = (RefObj *)self->_argData;
        Ref::assign((RefObj **)&self->_argData, ((RefObj **)((igObjectList *)self->_pushPopStack)->_data)[0]);
        list = (igObjectList *)self->_pushPopStack;
        Ref::release(((RefObj **)list->_data)[0]);
        List_RemoveWordAt(list, 0);
        ((RefObj **)list->_data)[list->_count] = 0;
        ObjectList_AppendRetained(self->_pushPopStack, saved.p);
    }
    --self->_pushPopCount;
}
