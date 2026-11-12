#include "dw4/reflected.h"

extern "C" void Gap__Bec__beNumberCtrl__vfunc_32(void);
extern "C" int Gap__Bec__beNumberCtrl__vfunc_30(void);
extern "C" int Gap__Bec__beNumberCtrl__vfunc_20(void);
extern "C" int FUN_003a4e40(void *arg0, int arg1);
extern "C" void *FUN_0034d2b0(...);
extern "C" int FUN_0034e300(...);
extern "C" int FUN_003a4b20(...);
extern "C" int Memory_GetAllocatorBySelector(...);
extern "C" int beMessenger_AppendInt(...);
extern "C" int beMessenger_GetInt(...);
extern "C" int beMessenger_GetIntCount(...);
extern "C" int beMessenger_ResolveEnumValue(...);
extern "C" void igObject_Destroy(void *);
extern "C" int igObject_GetAllocator(...);
extern "C" int g_beNumberCtrlInfo_metaObject[4];
extern "C" int g_beNumberCtrl_metaObject[4];
struct UnidentifiedNameHolder { char pad8[8]; int f8; };
struct UnidentifiedReceiverObject { char pad8[8]; int f8; UnidentifiedNameHolder *f12; };
extern "C" int beMessenger_RegisterReceiver(int, UnidentifiedReceiverObject *, void *, int *, int);
extern "C" int emptyString[4];
extern "C" int DAT_0050feb0[4];
extern "C" void Gap__Bec__beNumberCtrl__vfunc_29(beNumberCtrl *arg0, UnidentifiedReceiverObject *arg1);
/* igObject header (vtable, reference count); the count at +4 is not a reflected field */
/* unreflected message argument: only the command word at +20 is read */
struct MessageCommandArg { char p0[20]; int command; };
extern "C" int g_defaultAllocatorSelector[4];
extern "C" unsigned char GPR_00554c14;
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
extern "C" int Gap__Bec__beNumberCtrl__vfunc_34(beNumberCtrl *arg0, beNumberCtrlInfoRam *arg1, MessageCommandArg *arg2);

void Gap__Bec__beNumberCtrl__vfunc_32(void)
{
}

int Gap__Bec__beNumberCtrl__vfunc_30(void)
{
    return g_beNumberCtrlInfo_metaObject[0];
}

int FUN_003a4e40(void *arg0, int arg1) {
    int v = 0;
    if (arg1 > 0) {
        v = arg1 / 128 + 1;
        if (v >= 100) {
            v = 99;
        }
        if (v % 10 == 0) {
            v++;
        }
    } else if (arg1 < 0) {
        v = arg1 / 128 - 1;
        if (v < -99) {
            v = -99;
        }
        if (v % 10 == 0) {
            v--;
        }
    }
    return v;
}

void Gap__Bec__beNumberCtrl__vfunc_29(beNumberCtrl *arg0, UnidentifiedReceiverObject *arg1) {
    int *var_a3;
    int t = arg1->f8;
    var_a3 = (int *)(((UnidentifiedNameHolder *)arg1->f12)->f8);
    var_a3 = var_a3 != 0 ? var_a3 : &emptyString[0];
    beMessenger_RegisterReceiver(arg0->_messenger, arg1, &DAT_0050feb0[0], var_a3, t);
}

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
            var = GPR_00554c14 != 0 ? var : Memory_GetAllocatorBySelector(g_defaultAllocatorSelector[0]);
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
            var = GPR_00554c14 != 0 ? var : Memory_GetAllocatorBySelector(g_defaultAllocatorSelector[0]);
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

int Gap__Bec__beNumberCtrl__vfunc_20(void)
{
    return g_beNumberCtrl_metaObject[0];
}
