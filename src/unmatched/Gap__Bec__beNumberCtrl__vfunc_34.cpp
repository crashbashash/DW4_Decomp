#include "dw4/reflected.h"
/* igObject header (vtable, reference count); the count at +4 is not a reflected field */
/* unreflected message argument: only the command word at +20 is read */
struct MessageCommandArg { char p0[20]; int command; };
extern "C" {
void *FUN_0034d2b0(...);
int FUN_0034e300();
int FUN_003a4b20(...);
int FUN_003a4e40(...);
int Memory_GetAllocatorBySelector(...);
int beMessenger_AppendInt(...);
int beMessenger_GetInt(...);
int beMessenger_GetIntCount(...);
int beMessenger_ResolveEnumValue(...);
void igObject_Destroy(void *);
int igObject_GetAllocator(...);
extern int DAT_00587110[4];
extern unsigned char GPR_00554c14;
int Gap__Bec__beNumberCtrl__vfunc_34(beNumberCtrl *arg0, beNumberCtrlInfoRam *arg1, MessageCommandArg *arg2);
}
/* matching construct: stack smart pointer whose destructor releases the object, reproduces the retail cleanup path */
struct Ref {
    igObject *p;
    Ref(void *x) { p = (igObject *)x; }
    ~Ref() {
        igObject *q = p;
        if (q != 0) {
            q->_refCount = q->_refCount - 1;
            if (((unsigned long long)(long long)q->_refCount & 0x7fffffULL) == 0) igObject_Destroy(q);
        }
    }
};
int Gap__Bec__beNumberCtrl__vfunc_34(beNumberCtrl *arg0, beNumberCtrlInfoRam *arg1, MessageCommandArg *arg2) {
    int s3;
    int var;
    beNumberCtrlInfoWork *s0;
    s3 = arg2->command;
    beMessenger_ResolveEnumValue(arg0->_messenger, FUN_0034e300(), s3);
    s0 = (beNumberCtrlInfoWork *)arg1->_work;
    switch (beMessenger_ResolveEnumValue(arg0->_messenger, FUN_0034e300(), s3)) {
    case 0:
        if (s0 != 0) {
            beMessenger_AppendInt(arg0->_messenger, s0->_realNum);
        }
        return 1;
    case 1:
        if (s0 == 0) {
            igObject *o;
            int var;
            var = igObject_GetAllocator(arg0);
            var = GPR_00554c14 != 0 ? var : Memory_GetAllocatorBySelector(DAT_00587110[0]);
            Ref r((igObject *)FUN_0034d2b0(var));
            s0 = (beNumberCtrlInfoWork *)r.p;
            if (s0 != 0) ((igObject *)s0)->_refCount = ((igObject *)s0)->_refCount + 1;
            o = ((igObject *)arg1->_work);
            if (o != 0) {
                o->_refCount = o->_refCount - 1;
                if (((unsigned long long)(long long)o->_refCount & 0x7fffffULL) == 0) igObject_Destroy(o);
            }
            arg1->_work = (int)s0;
            s0 = (beNumberCtrlInfoWork *)r.p;
        }
        if (beMessenger_GetIntCount(arg0->_messenger) == 0) return 1;
        s3 = beMessenger_GetInt(arg0->_messenger, 0);
        if (s3 < 0) s3 = 0;
        if (arg1->_maxValue < s3) s3 = arg1->_maxValue;
        FUN_003a4b20(arg0, arg1, s3, 0);
        s0->_dispNum = s3;
        s0->_realNum = s3;
        s0->_changeNum = 0;
        return 1;
    case 3:
        if (s0 == 0) {
            igObject *o;
            int var;
            var = igObject_GetAllocator(arg0);
            var = GPR_00554c14 != 0 ? var : Memory_GetAllocatorBySelector(DAT_00587110[0]);
            Ref r((igObject *)FUN_0034d2b0(var));
            s0 = (beNumberCtrlInfoWork *)r.p;
            if (s0 != 0) ((igObject *)s0)->_refCount = ((igObject *)s0)->_refCount + 1;
            o = ((igObject *)arg1->_work);
            if (o != 0) {
                o->_refCount = o->_refCount - 1;
                if (((unsigned long long)(long long)o->_refCount & 0x7fffffULL) == 0) igObject_Destroy(o);
            }
            arg1->_work = (int)s0;
            s0 = (beNumberCtrlInfoWork *)r.p;
        }
        if (beMessenger_GetIntCount(arg0->_messenger) == 0) return 1;
        s3 = s0->_realNum;
        s0->_realNum = s3 + beMessenger_GetInt(arg0->_messenger, 0);
        if (s0->_realNum < 0) s0->_realNum = 0;
        {
            int v1 = arg1->_maxValue;
            if (v1 < s0->_realNum) s0->_realNum = v1;
        }
        s0->_changeNum = FUN_003a4e40(arg0, s0->_realNum - s0->_dispNum);
        return 1;
    default:
        return 0;
    }
}
