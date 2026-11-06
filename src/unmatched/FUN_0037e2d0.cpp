/* While "turning OK" is set, queue a kind-4 keep-message carrying the given RAM number on the
 * build work's list. */
#include "dw4/reflected.h"

extern "C" {
beDemoKeepMes *FUN_00363c20(int allocator);
int Memory_GetAllocatorBySelector(int);
int ObjectList_AppendRetained(int list, beDemoKeepMes *o);
void igObject_Destroy(beDemoKeepMes *);
int igObject_GetAllocator(beDemoManager *);
extern int DAT_00587110[4];
extern unsigned char GPR_00554c14;
void FUN_0037e2d0(beDemoManager *a0, int ramNo);
}

/* Owning stack reference to a keep-message.  Its destructor releases the
 * object (reference count in the low 23 bits of _refCount); the out-of-line
 * copy the exception table points at is the retail body 0x0037e250
 * (config/SLUS-20836/unit-objects.json, duplicate __dt__10KeepMesRefFv). */
class KeepMesRef {
public:
    beDemoKeepMes *p;
    KeepMesRef(beDemoKeepMes *o) : p(o) {}
    ~KeepMesRef() {
        beDemoKeepMes *o = p;
        if (o != 0) {
            o->_refCount = o->_refCount - 1;
            if ((o->_refCount & 0x7FFFFF) == 0) {
                igObject_Destroy(o);
            }
        }
    }
};

void FUN_0037e2d0(beDemoManager *a0, int ramNo) {
    beDemoManagerWork *l;
    int al;

    l = (beDemoManagerWork *)a0->_buildData;
    if ((l != 0) && (a0->_turningOK != 0)) {
        al = igObject_GetAllocator(a0);
        al = GPR_00554c14 ? al : Memory_GetAllocatorBySelector(DAT_00587110[0]);
        KeepMesRef mes(FUN_00363c20(al));
        mes.p->_kind = 4;
        mes.p->_ramNo = ramNo;
        ObjectList_AppendRetained(l->_keepMesList, mes.p);
    }
}
