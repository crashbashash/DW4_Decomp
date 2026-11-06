#include "dw4/reflected.h"
extern "C" {
void *FUN_00348c70(...);
void *FUN_00348f60(...);
void *FUN_00349270(...);
void *FUN_003495f0(...);
void *FUN_00349870(...);
void *FUN_00349af0(...);
void *FUN_00349d70(...);
int FUN_00346c20(...);
int FUN_003ae680(...);
int Memory_GetAllocatorBySelector(...);
int beMessenger_AppendBool(...);
int beMessenger_AppendInt(...);
int beMessenger_AppendObject(...);
int beMessenger_GetBoolCount(...);
int beMessenger_GetInt(...);
int beMessenger_GetIntCount(...);
void *beMessenger_GetObject(...);
int beMessenger_GetObjectCount(...);
unsigned int beMessenger_ResolveEnumValue(...);
int igObject_Destroy(...);
int igObject_GetAllocator(...);
extern int DAT_00587110[4];
extern unsigned char GPR_00554c14;
}

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
#define DELIVER(r) ((Deliver *)(r)->_deliver)
#define ALLOC(a, self) { int base_ = igObject_GetAllocator(self); if (GPR_00554c14 != 0) { a = base_; } else { a = Memory_GetAllocatorBySelector(DAT_00587110[0]); } }

/* Every request case starts the same way: build the request object, then reset the record's slot
 * to -1 and take the first integer argument of the message as the slot (the one-case switch tests
 * the first argument; a plain if (i == 0) compiles to different branch code). */
#define NEW_REQUEST(r, kind, create) ALLOC(a, self); RP<kind> r((RC *)create(a));
#define TAKE_SLOT_ARGUMENT(self, info) \
    DELIVER(info)->slot = -1; \
    for (i = 0; i < beMessenger_GetIntCount((self)->_messenger); i++) { \
        int v = beMessenger_GetInt((self)->_messenger, i); \
        switch (i) { case 0: DELIVER(info)->slot = v; break; } \
    }

extern "C" int Gap__Bec__beSaveUtil__vfunc_34(beSaveUtil *self, beSaveUtilInfoRam *info, MsgArg *msg);

int Gap__Bec__beSaveUtil__vfunc_34(beSaveUtil *self, beSaveUtilInfoRam *info, MsgArg *msg) {
    int a;
    int i;
    switch (beMessenger_ResolveEnumValue(self->_messenger, FUN_00346c20(), msg->f20)) {
    case 3: {
        NEW_REQUEST(r, 0, FUN_00349af0)
        TAKE_SLOT_ARGUMENT(self, info)
        FUN_003ae680(self, info, r.p);
        break;
    }
    case 5: {
        NEW_REQUEST(r, 1, FUN_003495f0)
        TAKE_SLOT_ARGUMENT(self, info)
        FUN_003ae680(self, info, r.p);
        break;
    }
    case 8: {
        NEW_REQUEST(r, 2, FUN_00348c70)
        TAKE_SLOT_ARGUMENT(self, info)
        FUN_003ae680(self, info, r.p);
        break;
    }
    case 2: {
        NEW_REQUEST(r, 3, FUN_00349d70)
        TAKE_SLOT_ARGUMENT(self, info)
        if (beMessenger_GetObjectCount(self->_messenger) != 0) {
            DELIVER(info)->f8 = (int)beMessenger_GetObject(self->_messenger, 0);
        }
        FUN_003ae680(self, info, r.p);
        break;
    }
    case 4: {
        NEW_REQUEST(r, 4, FUN_00349870)
        TAKE_SLOT_ARGUMENT(self, info)
        FUN_003ae680(self, info, r.p);
        break;
    }
    case 7: {
        NEW_REQUEST(r, 5, FUN_00348f60)
        TAKE_SLOT_ARGUMENT(self, info)
        if (beMessenger_GetObjectCount(self->_messenger) != 0) {
            DELIVER(info)->f8 = (int)beMessenger_GetObject(self->_messenger, 0);
        }
        FUN_003ae680(self, info, r.p);
        break;
    }
    case 6: {
        NEW_REQUEST(r, 6, FUN_00349270)
        TAKE_SLOT_ARGUMENT(self, info)
        if (beMessenger_GetObjectCount(self->_messenger) != 0) {
            DELIVER(info)->f8 = (int)beMessenger_GetObject(self->_messenger, 0);
        }
        FUN_003ae680(self, info, r.p);
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
