#include "dw4/reflected.h"

extern "C" int igObject_Destroy(...);
extern "C" int FUN_003ad950(int, int);
extern "C" int FUN_003ada60(int);
extern "C" int FUN_003add40(int, int);
extern "C" void FUN_00100610(...);
extern "C" void **FUN_003af090(void **arg0, short arg1);
extern "C" int Gap__Bec__beSaveUtil__vfunc_30(void);
extern "C" int Gap__Bec__beSaveUtil__vfunc_20(void);
extern "C" void beMessenger_RegisterReceiverFromInfo(int, int, char *);
extern "C" void *FUN_00348c70(...);
extern "C" void *FUN_00348f60(...);
extern "C" void *FUN_00349270(...);
extern "C" void *FUN_003495f0(...);
extern "C" void *FUN_00349870(...);
extern "C" void *FUN_00349af0(...);
extern "C" void *FUN_00349d70(...);
extern "C" int FUN_00346c20(...);
extern "C" int Memory_GetAllocatorBySelector(...);
extern "C" int beMessenger_AppendBool(...);
extern "C" int beMessenger_AppendInt(...);
extern "C" int beMessenger_AppendObject(...);
extern "C" int beMessenger_GetBoolCount(...);
extern "C" int beMessenger_GetInt(...);
extern "C" int beMessenger_GetIntCount(...);
extern "C" void *beMessenger_GetObject(...);
extern "C" int beMessenger_GetObjectCount(...);
extern "C" unsigned int beMessenger_ResolveEnumValue(...);
extern "C" int igObject_GetAllocator(...);
class M { public: char pad[28]; int f28; char pad2[12]; unsigned char f44; };
class R { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void vX(M *); int refs; int f8; int f12; };
class B { public: char pad[24]; int f24; int f28; int f32; int f36; char pad40[8]; M *f48; };
class A { public: char pad[32]; R *obj; };
extern "C" unsigned char FUN_003ae680(A *arg0, B *arg1, R *arg2);
typedef struct S0 { char pad36[36]; int f24; } S0;
typedef struct S1 { char pad48[48]; int f30; } S1;
extern "C" void FUN_003ae770(S0 *arg0, S1 *arg1);
extern "C" void Gap__Bec__beSaveUtil__vfunc_32(beSaveUtil *arg0);
/* Deleting destructor; the deletion flag is a signed short. */
typedef struct ObjectRefTarget { int word0; int references; } ObjectRefTarget;
typedef struct ObjectRefWord { ObjectRefTarget *value; } ObjectRefWord;
extern "C" ObjectRefWord *FUN_003af010(ObjectRefWord *self,int delete_storage);
typedef struct S_temp_a0 { char pad4[4]; int f4; } S_temp_a0;
extern "C" int g_beSaveUtilInfo_metaObject[4];
extern "C" int g_beSaveUtil_metaObject[4];
extern "C" char DAT_00510738[];
extern "C" void Gap__Bec__beSaveUtil__vfunc_29(beSaveUtil * p0, int p1, char * p2);
extern "C" int g_defaultAllocatorSelector[4];
extern "C" unsigned char GPR_00554c14;
/* reference-counted engine object header: refcount word at +4 */
struct RC { int vt; int rc; };
/* Owning stack reference to a request object; one instantiation per request kind (case), so each
 * case gets its own out-of-line destructor. */
template <int kind> struct RP {
    RC *p;
    RP(RC *q) : p(q) {}
    ~RP() { RC *q = p; if (q != 0) { q->rc = q->rc - 1; if ((q->rc & 0x7fffff) == 0) igObject_Destroy(q); } }
};
/* message record: only the enum value name at +20 is read */
struct MsgArg { char pad20[20]; int f20; };
/* The info record's +48 object (beSaveUtilInfoRam._deliver). */
struct Deliver {
    int pad0[2];
    int f8;                 /* object argument forwarded to the request */
    int pad12;
    int slot;               /* +16 */
    int f20;                /* +20 */
    int f24;                /* +24 */
    int pad28;
    int f32;                /* +32 */
    int f36;                /* +36 */
    unsigned char pad40[2];
    unsigned char b42;
    unsigned char b43;
    unsigned char b44;
};
extern "C" int Gap__Bec__beSaveUtil__vfunc_34(beSaveUtil *self, beSaveUtilInfoRam *info, MsgArg *msg);

unsigned char FUN_003ae680(A *arg0, B *arg1, R *arg2) {
    unsigned char var_v0;
    R *temp_a0;

    var_v0 = 0;
    if (arg0->obj == 0) {
        if (arg2 != 0) {
            arg2->refs = arg2->refs + 1;
        }
        temp_a0 = arg0->obj;
        if (temp_a0 != 0) {
            temp_a0->refs = temp_a0->refs - 1;
            if (((unsigned long long)((long long)temp_a0->refs << 0x29) >> 0x29) == 0) {
                igObject_Destroy(temp_a0);
            }
        }
        arg0->obj = arg2;
        arg0->obj->vX(arg1->f48);
        arg1->f48->f28 = arg0->obj->f12;
        arg1->f48->f44 = 0;
        arg1->f24 = 1;
        arg1->f36 = 0;
        arg1->f32 = 0;
        arg1->f28 = 0;
        arg1->f28 = 1;
        arg1->f36 = 0;
        arg1->f32 = 0;
        arg1->f32 = 1;
        arg1->f36 = 0;
        var_v0 = 1;
    }
    return var_v0;
}

void FUN_003ae770(S0 *arg0, S1 *arg1) {
    FUN_003ad950(arg0->f24, arg1->f30);
    FUN_003ada60(arg0->f24);
    FUN_003add40(arg0->f24, arg1->f30);
}

void Gap__Bec__beSaveUtil__vfunc_32(beSaveUtil *arg0) {
    igObject *temp_a0;
    igObject *temp_a0_2;

    temp_a0 = (igObject *)arg0->_api;
    if (temp_a0 != 0) {
        if (temp_a0 != 0) {
            temp_a0->_refCount = (int)temp_a0->_refCount - 1;
            if (((unsigned long long)((long long)(int)temp_a0->_refCount << 0x29) >> 0x29) == 0) {
                igObject_Destroy(temp_a0);
            }
        }
        arg0->_api = 0;
    }
    temp_a0_2 = (igObject *)arg0->_connectCheck;
    if (temp_a0_2 != 0) {
        if (temp_a0_2 != 0) {
            temp_a0_2->_refCount = (int)temp_a0_2->_refCount - 1;
            if (((unsigned long long)((long long)(int)temp_a0_2->_refCount << 0x29) >> 0x29) == 0) {
                igObject_Destroy(temp_a0_2);
            }
        }
        arg0->_connectCheck = 0;
    }
}

ObjectRefWord *FUN_003af010(ObjectRefWord *self,int delete_storage) {
    if(self) {
        ObjectRefTarget *object=self->value;
        if(object) {
            --object->references;
            if(((unsigned long long)(long long)object->references & 0x7fffffULL)==0)
                igObject_Destroy(object);
        }
        if((short)delete_storage>0) FUN_00100610(self);
    }
    return self;
}

void **FUN_003af090(void **arg0, short arg1) {
    S_temp_a0 *temp_a0;

    if (arg0 != 0) {
        temp_a0 = (S_temp_a0 *)(*arg0);
        if (temp_a0 != 0) {
            temp_a0->f4 = (int)((int) (temp_a0->f4 - 1));
            if ((temp_a0->f4 & 0x7FFFFF) == 0) {
                igObject_Destroy(temp_a0);
            }
        }
        if (arg1 > 0) {
            FUN_00100610(arg0);
        }
    }
    return arg0;
}

int Gap__Bec__beSaveUtil__vfunc_30(void)
{
    return g_beSaveUtilInfo_metaObject[0];
}

void Gap__Bec__beSaveUtil__vfunc_29(beSaveUtil * p0, int p1, char * p2)
{
    beMessenger_RegisterReceiverFromInfo(p0->_messenger, p1, DAT_00510738);
}

#define DELIVER(r) ((Deliver *)(r)->_deliver)
#define ALLOC(a, self) { int base_ = igObject_GetAllocator(self); if (GPR_00554c14 != 0) { a = base_; } else { a = Memory_GetAllocatorBySelector(g_defaultAllocatorSelector[0]); } }
#define NEW_REQUEST(r, kind, create) ALLOC(a, self); RP<kind> r((RC *)create(a));
#define TAKE_SLOT_ARGUMENT(self, info) \
    DELIVER(info)->slot = -1; \
    for (i = 0; i < beMessenger_GetIntCount((self)->_messenger); i++) { \
        int v = beMessenger_GetInt((self)->_messenger, i); \
        switch (i) { case 0: DELIVER(info)->slot = v; break; } \
    }
int Gap__Bec__beSaveUtil__vfunc_34(beSaveUtil *self, beSaveUtilInfoRam *info, MsgArg *msg) {
    int a;
    int i;
    switch (beMessenger_ResolveEnumValue(self->_messenger, FUN_00346c20(), msg->f20)) {
    case 3: {
        NEW_REQUEST(r, 0, FUN_00349af0)
        TAKE_SLOT_ARGUMENT(self, info)
        ((int)FUN_003ae680((A *)self, (B *)info, (R *)r.p));
        break;
    }
    case 5: {
        NEW_REQUEST(r, 1, FUN_003495f0)
        TAKE_SLOT_ARGUMENT(self, info)
        ((int)FUN_003ae680((A *)self, (B *)info, (R *)r.p));
        break;
    }
    case 8: {
        NEW_REQUEST(r, 2, FUN_00348c70)
        TAKE_SLOT_ARGUMENT(self, info)
        ((int)FUN_003ae680((A *)self, (B *)info, (R *)r.p));
        break;
    }
    case 2: {
        NEW_REQUEST(r, 3, FUN_00349d70)
        TAKE_SLOT_ARGUMENT(self, info)
        if (beMessenger_GetObjectCount(self->_messenger) != 0) {
            DELIVER(info)->f8 = (int)beMessenger_GetObject(self->_messenger, 0);
        }
        FUN_003ae680((A *)self, (B *)info, (R *)r.p);
        break;
    }
    case 4: {
        NEW_REQUEST(r, 4, FUN_00349870)
        TAKE_SLOT_ARGUMENT(self, info)
        ((int)FUN_003ae680((A *)self, (B *)info, (R *)r.p));
        break;
    }
    case 7: {
        NEW_REQUEST(r, 5, FUN_00348f60)
        TAKE_SLOT_ARGUMENT(self, info)
        if (beMessenger_GetObjectCount(self->_messenger) != 0) {
            DELIVER(info)->f8 = (int)beMessenger_GetObject(self->_messenger, 0);
        }
        FUN_003ae680((A *)self, (B *)info, (R *)r.p);
        break;
    }
    case 6: {
        NEW_REQUEST(r, 6, FUN_00349270)
        TAKE_SLOT_ARGUMENT(self, info)
        if (beMessenger_GetObjectCount(self->_messenger) != 0) {
            DELIVER(info)->f8 = (int)beMessenger_GetObject(self->_messenger, 0);
        }
        FUN_003ae680((A *)self, (B *)info, (R *)r.p);
        break;
    }
    case 9:
        if (beMessenger_GetObjectCount(self->_messenger) == 0) {
            beMessenger_AppendObject(self->_messenger, info->_deliver);
        }
        break;
    case 0:
        info->_st0 = 1;
        info->_st3 = 0; info->_st2 = 0; info->_st1 = 0;
        info->_st1 = 0; info->_st3 = 0; info->_st2 = 0;
        {
            Deliver *d = DELIVER(info);
            if (beMessenger_GetIntCount(self->_messenger) != 0) {
                d->f20 = beMessenger_GetInt(self->_messenger, 0);
            }
        }
        if (beMessenger_GetBoolCount(self->_messenger) == 0) {
            beMessenger_AppendBool(self->_messenger, 1);
        }
        break;
    case 1:
        info->_st0 = 1;
        info->_st3 = 0; info->_st2 = 0; info->_st1 = 0;
        info->_st1 = 2;
        info->_st3 = 0; info->_st2 = 0;
        break;
    case 11:
        if (beMessenger_GetBoolCount(self->_messenger) == 0) {
            if (DELIVER(info)->b44 == 1) {
                beMessenger_AppendBool(self->_messenger, 0);
            } else {
                beMessenger_AppendBool(self->_messenger, 1);
            }
        }
        break;
    case 12:
        if (beMessenger_GetIntCount(self->_messenger) == 0) {
            beMessenger_AppendInt(self->_messenger, DELIVER(info)->f24);
        }
        break;
    case 13:
        if (beMessenger_GetBoolCount(self->_messenger) == 0) {
            if (info->_isRdy == 1) {
                beMessenger_AppendBool(self->_messenger, 1);
            } else {
                beMessenger_AppendBool(self->_messenger, 0);
            }
        }
        break;
    case 14:
        if (beMessenger_GetBoolCount(self->_messenger) == 0) {
            beMessenger_AppendInt(self->_messenger, DELIVER(info)->f32);
            beMessenger_AppendInt(self->_messenger, DELIVER(info)->f36);
            if (DELIVER(info)->b42 == 1) {
                beMessenger_AppendBool(self->_messenger, 1);
            } else {
                beMessenger_AppendBool(self->_messenger, 0);
            }
            if (DELIVER(info)->b43 == 1) {
                beMessenger_AppendBool(self->_messenger, 1);
            } else {
                beMessenger_AppendBool(self->_messenger, 0);
            }
        }
        break;
    case 15:
        if (beMessenger_GetIntCount(self->_messenger) == 0) {
            beMessenger_AppendInt(self->_messenger, DELIVER(info)->f24);
        }
        break;
    case 17:
        break;
    default:
        return 0;
    }
    return 1;
}

#undef TAKE_SLOT_ARGUMENT
#undef NEW_REQUEST
#undef ALLOC
#undef DELIVER

int Gap__Bec__beSaveUtil__vfunc_20(void)
{
    return g_beSaveUtil_metaObject[0];
}
