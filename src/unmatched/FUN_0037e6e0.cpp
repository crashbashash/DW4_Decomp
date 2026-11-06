/* Queue a kind-7 keep-message whose parameter is the interned string `arg1`; a build work is
 * created first when the manager has none. */
#include "dw4/reflected.h"

extern "C" {
int FUN_002eb010(int);
beDemoManagerWork *FUN_003637c0(int allocator);
beDemoKeepMes *FUN_00363c20(int allocator);
int Memory_GetAllocatorBySelector(int);
int ObjectList_AppendRetained(int list, beDemoKeepMes *o);
void StringChunk_ReleaseHeader(int, int *);
int StringPool_Construct(int);
char *StringPool_Intern(int pool, int key);
void igObject_Destroy(void *);
int igObject_GetAllocator(beDemoManager *);
extern int DAT_00586f20[4];
extern int DAT_00587110[4];
extern unsigned char GPR_00554c14;
void FUN_0037e6e0(beDemoManager *arg0, int arg1);
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

void FUN_0037e6e0(beDemoManager *arg0, int arg1) {
    beDemoManagerWork *l;
    beDemoKeepMes *s1;
    beDemoManagerWork *old;
    int var_v0;
    int key;
    int *temp_v1;
    int temp_v0;
    int var_v0_2;
    int *temp_a1;
    int var_v0_3;

    key = arg1;
    if (arg0->_buildData == 0) {
        var_v0_3 = igObject_GetAllocator(arg0);
        if (GPR_00554c14 != 0) {
            var_v0_3 = (int)var_v0_3;
        } else {
            var_v0_3 = Memory_GetAllocatorBySelector(DAT_00587110[0]);
        }
        old = (beDemoManagerWork *)arg0->_buildData;
        if (old != 0) {
            old->_refCount = old->_refCount - 1;
            if ((old->_refCount & 0x7FFFFF) == 0) {
                igObject_Destroy(old);
            }
        }
        arg0->_buildData = (int)FUN_003637c0(var_v0_3);
        arg0->_turningOK = 0;
    }
    l = (beDemoManagerWork *)arg0->_buildData;
    var_v0 = igObject_GetAllocator(arg0);
    if (GPR_00554c14 != 0) {
        var_v0 = (int)var_v0;
    } else {
        var_v0 = Memory_GetAllocatorBySelector(DAT_00587110[0]);
    }
    KeepMesRef mes(FUN_00363c20(var_v0));
    mes.p->_kind = 7;
    s1 = mes.p;
    if (DAT_00586f20[0] == 0) {
        var_v0_2 = FUN_002eb010(0x10);
        if (var_v0_2 != 0) {
            var_v0_2 = StringPool_Construct(var_v0_2);
        }
        DAT_00586f20[0] = var_v0_2;
    }
    key = (int)StringPool_Intern(DAT_00586f20[0], key);
    temp_v1 = (int *)s1->_mesParam;
    if (temp_v1 != 0) {
        temp_a1 = temp_v1 - 2;
        temp_v0 = temp_v1[-1] - 1;
        temp_v1[-1] = temp_v0;
        if (temp_v0 == 0) {
            StringChunk_ReleaseHeader(*temp_a1, temp_a1);
        }
    }
    s1->_mesParam = key;
    ObjectList_AppendRetained(l->_keepMesList, mes.p);
}
