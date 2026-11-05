#include "dw4/reflected.h"
extern "C" {
int FUN_002eb010(int n);
int StringChunk_ReleaseHeader(...);
int StringPool_Construct(int p);
int StringPool_Intern(int pool, int s);
void igObject_Destroy(void *t);
extern int DAT_00586f20[4];
}
/* matching construct: dummy virtual slots so the vX() call dispatches through the retail vtable offset 88 */
class Src { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void *vX(); };
extern "C" igObject *igMetaObject_FindFieldByName(void *m, int name);
extern "C" void FUN_001e6230(igDataPump *arg0, Src **arg1, int arg2);
void FUN_001e6230(igDataPump *arg0, Src **arg1, int arg2) {
    igObject *s0;
    igObject *old;
    igMetaField *fld;
    int name;
    int v;
    int newv;
    int oldv;
    s0 = (igObject *)*arg1;
    if (s0 != 0) {
        s0->_refCount = s0->_refCount + 1;
    }
    old = (igObject *)arg0->_destObj;
    if (old != 0) {
        --old->_refCount;
        if (((unsigned long long)(long long)old->_refCount & 0x7fffffULL) == 0) {
            igObject_Destroy(old);
        }
    }
    arg0->_destObj = (int)s0;
    fld = (igMetaField *)igMetaObject_FindFieldByName((*arg1)->vX(), arg2);
    if (fld != 0) {
        fld->_refCount = fld->_refCount + 1;
    }
    old = (igObject *)arg0->_destMeta;
    if (old != 0) {
        --old->_refCount;
        if (((unsigned long long)(long long)old->_refCount & 0x7fffffULL) == 0) {
            igObject_Destroy(old);
        }
    }
    arg0->_destMeta = (int)fld;
    name = ((igMetaObject *)((igMetaField *)arg0->_destMeta)->_parentMetaObject)->_name;
    if (DAT_00586f20[0] == 0) {
        v = FUN_002eb010(16);
        if (v != 0) {
            v = StringPool_Construct(v);
        }
        DAT_00586f20[0] = v;
    }
    newv = StringPool_Intern(DAT_00586f20[0], name);
    oldv = arg0->_destMetaClassName;
    if (oldv != 0) {
        int *a1 = (int *)oldv - 2;
        int v0 = ((int *)oldv)[-1] - 1;
        ((int *)oldv)[-1] = v0;
        if (v0 == 0) {
            StringChunk_ReleaseHeader(*a1, a1);
        }
    }
    arg0->_destMetaClassName = newv;
    name = ((igMetaField *)arg0->_destMeta)->_fieldName;
    if (DAT_00586f20[0] == 0) {
        v = FUN_002eb010(16);
        if (v != 0) {
            v = StringPool_Construct(v);
        }
        DAT_00586f20[0] = v;
    }
    newv = StringPool_Intern(DAT_00586f20[0], name);
    oldv = arg0->_destMetaFieldName;
    if (oldv != 0) {
        int *a1 = (int *)oldv - 2;
        int v0 = ((int *)oldv)[-1] - 1;
        ((int *)oldv)[-1] = v0;
        if (v0 == 0) {
            StringChunk_ReleaseHeader(*a1, a1);
        }
    }
    arg0->_destMetaFieldName = newv;
}
