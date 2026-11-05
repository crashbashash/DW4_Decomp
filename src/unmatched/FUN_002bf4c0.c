#include "dw4/reflected.h"
int StringChunk_ReleaseHeader();
int igObject_Destroy();
int thunk_FUN_002ed460__002ff810();
extern int DAT_0052ec50[4];
extern int DAT_0052f230[4];
extern int DAT_00532a50[4];
void *FUN_002bf4c0(igMemoryRefMetaField *arg0, long long arg1) {
    igObject *o;
    int *a1;
    int v0;
    if (arg0 != 0) {
        arg0->_vtable = (int)&DAT_00532a50[0];
        if (&arg0->_poolName != 0) {
            char *p = (char *)arg0->_poolName;
            if (p != 0) {
                a1 = (int *)(p - 8);
                v0 = *(int *)(p - 4) - 1;
                *(int *)(p - 4) = v0;
                if (v0 == 0) {
                    StringChunk_ReleaseHeader(*a1, a1);
                }
            }
        }
        if (&arg0->_memTypeRef != 0) {
            o = (igObject *)arg0->_memTypeRef;
            if (o != 0) {
                o->_refCount = o->_refCount - 1;
                if ((o->_refCount & 0x7FFFFF) == 0) {
                    igObject_Destroy(o);
                }
            }
        }
        if (arg0 != 0) {
            arg0->_vtable = (int)&DAT_0052ec50[0];
            if (arg0 != 0) {
                arg0->_vtable = (int)&DAT_0052f230[0];
                if (&arg0->_fieldName != 0) {
                    char *p = (char *)arg0->_fieldName;
                    if (p != 0) {
                        a1 = (int *)(p - 8);
                        v0 = *(int *)(p - 4) - 1;
                        *(int *)(p - 4) = v0;
                        if (v0 == 0) {
                            StringChunk_ReleaseHeader(*a1, a1);
                        }
                    }
                }
            }
        }
        if ((short)arg1 > 0) {
            thunk_FUN_002ed460__002ff810(arg0);
        }
    }
    return arg0;
}
