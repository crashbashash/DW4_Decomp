#include "dw4/reflected.h"
extern "C" {
void *FUN_002bb500(...);
int FUN_0030b3c0(...);
int ObjectList_ResizeRetained(...);
void igObject_Destroy(void *);
int igObject_GetAllocator(...);
int strcmp(int, int);
int thunk_FUN_0012a110(int, int);
extern int DAT_004c22f0[4];
}
/* Arena handles (4-byte refs) of the reflected int fields are followed through casts. */
struct Ref {
    igRegistryValue *p;
    ~Ref() {
        igRegistryValue *q = p;
        if (q != 0) {
            q->_refCount = q->_refCount - 1;
            if (((unsigned long long)(long long)q->_refCount & 0x7fffffULL) == 0) igObject_Destroy(q);
        }
    }
};
extern "C" igRegistryValue *FUN_00307c10(igRegistry *arg0, int arg1, int arg2, int arg3);
igRegistryValue *FUN_00307c10(igRegistry *arg0, int arg1, int arg2, int arg3) {
    int s2 = 0;
    int s1 = -1;
    Ref r;
    r.p = 0;
    for (; s2 < ((igRegistryValueList *)arg0->_valueTable)->_count; s2++) {
        igRegistryValue *s0 = ((igRegistryValue **)((igRegistryValueList *)arg0->_valueTable)->_data)[s2];
        igRegistryValue *old;
        if (s0 != 0) s0->_refCount = s0->_refCount + 1;
        old = r.p;
        if (old != 0) {
            old->_refCount = old->_refCount - 1;
            if (((unsigned long long)(long long)old->_refCount & 0x7fffffULL) == 0) igObject_Destroy(old);
        }
        r.p = s0;
        if (r.p != 0 && arg1 == r.p->_section) {
            int nm;
            if (arg0->_valueNameCaseSensitive != 0) {
                nm = (((igStringObj *)r.p->_valueName)->_buffer == 0) ? DAT_004c22f0[0] : ((igStringObj *)r.p->_valueName)->_buffer;
                if (strcmp(nm, arg2) == 0) {
                    igRegistryValue *ret = r.p;
                    return ret;
                }
            } else {
                nm = (((igStringObj *)r.p->_valueName)->_buffer == 0) ? DAT_004c22f0[0] : ((igStringObj *)r.p->_valueName)->_buffer;
                if (thunk_FUN_0012a110(nm, arg2) == 0) {
                    igRegistryValue *ret = r.p;
                    return ret;
                }
            }
        } else if (r.p == 0 && s1 < 0) {
            s1 = s2;
        }
    }
    if (arg3 != 0) {
        int s0;
        igRegistryValueList *l;
        igRegistryValue *old;
        igRegistryValue *t;
        if (s1 < 0) {
            s1 = ((igRegistryValueList *)arg0->_valueTable)->_count;
            ObjectList_ResizeRetained(((igRegistryValueList *)arg0->_valueTable), s1 * 2);
        }
        s0 = igObject_GetAllocator(arg0);
        old = r.p;
        if (old != 0) {
            old->_refCount = old->_refCount - 1;
            if (((unsigned long long)(long long)old->_refCount & 0x7fffffULL) == 0) igObject_Destroy(old);
        }
        r.p = (igRegistryValue *)FUN_002bb500(s0);
        l = (igRegistryValueList *)arg0->_valueTable;
        arg0 = (igRegistry *)r.p;
        if (arg0 != 0) ((igRegistryValue *)arg0)->_refCount = ((igRegistryValue *)arg0)->_refCount + 1;
        old = ((igRegistryValue **)l->_data)[s1];
        if (old != 0) {
            old->_refCount = old->_refCount - 1;
            if (((unsigned long long)(long long)old->_refCount & 0x7fffffULL) == 0) igObject_Destroy(old);
        }
        if (l->_count != 0 && s1 >= 0 && s1 < l->_count) ((igRegistryValue **)l->_data)[s1] = (igRegistryValue *)arg0;
        r.p->_section = arg1;
        FUN_0030b3c0(((igStringObj *)r.p->_valueName), arg2);
        {
            igRegistryValue *ret = r.p;
            return ret;
        }
    }
    return 0;
}
