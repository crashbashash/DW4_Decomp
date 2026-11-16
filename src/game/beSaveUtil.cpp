#include "dw4/reflected.h"
#include "dw4/igobject_release.h"
#include "dw4/igSmartPointer.h"
#include "dw4/igTDataList.h"

extern "C" int beSvConnectCheck_PollMultitap(int, int);
extern "C" int beSvConnectCheck_Poll(int);
extern "C" int beSvConnectCheck_FillDeliver(int, int);
extern "C" void __dl__FPv(...);
extern "C" int beSaveUtil_GetInfoMeta(void);
extern "C" int beSaveUtil_GetMeta(void);
extern "C" void beMessenger_RegisterReceiverFromInfo(int, int, char *);
extern "C" void *beSvGetFreeSizeApi_Create(...);
extern "C" void *beSvWriteMediaApi_Create(...);
extern "C" void *beSvReadMediaApi_Create(...);
extern "C" void *beSvUseCheckApi_Create(...);
extern "C" void *beSvFormatApi_Create(...);
extern "C" void *beSvFileFindApi_Create(...);
extern "C" void *beSvFileMakeApi_Create(...);
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
extern "C" void beSaveUtil_PollConnectCheck(S0 *arg0, S1 *arg1);
extern "C" void beSaveUtil_Prepare(beSaveUtil *arg0);
/* Deleting destructor; the deletion flag is a signed short. */
typedef struct ObjectRefTarget { int word0; int references; } ObjectRefTarget;
typedef struct ObjectRefWord { ObjectRefTarget *value; } ObjectRefWord;
typedef struct S_temp_a0 { char pad4[4]; int f4; } S_temp_a0;
extern "C" int g_beSaveUtilInfo_metaObject[4];
extern "C" int g_beSaveUtil_metaObject[4];
extern "C" char SAVEUTILITY_2[];
extern "C" void beSaveUtil_OnAddRam(beSaveUtil * p0, int p1, char * p2);
extern "C" int kIGMemoryPoolHandleUser1[4];
extern "C" unsigned char g_useOwnerAllocator;
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
extern "C" int beSaveUtil_OnMessage(beSaveUtil *self, beSaveUtilInfoRam *info, MsgArg *msg);

extern "C" beSvConnectCheck *beSvConnectCheck_Create(int allocator);
extern "C" beSvEndApi *beSvEndApi_Create(int allocator);
extern "C" beSvStartApi *beSvStartApi_Create(int allocator);
extern "C" void beSaveUtil_UpdateRam(beSaveUtil *self, beSaveUtilInfoRam *info);
extern "C" unsigned char g_useOwnerAllocator;

/* The request slots a beSaveApi object answers after getMetaObject (slot 20). */
class beSaveApiVirtuals {
public:
    virtual void slot00(); virtual void slot01(); virtual void slot02(); virtual void slot03();
    virtual void slot04(); virtual void slot05(); virtual void slot06(); virtual void slot07();
    virtual void slot08(); virtual void slot09(); virtual void slot10(); virtual void slot11();
    virtual void slot12(); virtual void slot13(); virtual void slot14(); virtual void slot15();
    virtual void slot16(); virtual void slot17(); virtual void slot18(); virtual void slot19();
    virtual void slot20();
    virtual void start(beSvDeliver *deliver);
    virtual int poll();
    virtual void report(beSvDeliver *deliver);
};
#define ALLOC(a, self) { int base_ = igObject_GetAllocator(self); if (g_useOwnerAllocator != 0) { a = base_; } else { a = Memory_GetAllocatorBySelector(kIGMemoryPoolHandleUser1[0]); } }

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

void beSaveUtil_PollConnectCheck(S0 *arg0, S1 *arg1) {
    beSvConnectCheck_PollMultitap(arg0->f24, arg1->f30);
    beSvConnectCheck_Poll(arg0->f24);
    beSvConnectCheck_FillDeliver(arg0->f24, arg1->f30);
}

void beSaveUtil_Prepare(beSaveUtil *arg0) {
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

/* The deliver's per-slot int lists (connected slots, free size, free files, format state, total size). */
struct SlotList : igTDataList<int> {
    void clear() {
        if (_count > 0) {
            _count = 0;
        }
    }
    void append(const int &value) {
        int n = count();
        if (n < _capacity) {
            _count = _count + 1;
        } else {
            List_Resize(this, n + 1, sizeof(int));
        }
        _data[n] = value;
    }
};

#define DELIVERY(info) ((beSvDeliver *)(info)->_deliver)
#define API(self) ((beSaveApiVirtuals *)(self)->_api)

/* Steps one save request through its life: _st1 0 starts the card session (the connect-check object
 * and the slot lists are made, then a start request is issued), 1 serves requests (polling the
 * cards, one request at a time) and 2 ends the session with an end request; _st2 is the sub-step
 * of a request, issued at 0 and polled at 1. _st0 3 is idle once the session has ended. */
void beSaveUtil_UpdateRam(beSaveUtil *self, beSaveUtilInfoRam *info) {
    int allocator;
    int i;
    SlotList *list;
    igObject *old;
    switch (info->_st0) {
    case 0:
        break;
    case 1:
        switch (info->_st1) {
        case 0:
            switch (info->_st2) {
            case 0:
                if (self->_connectCheck == 0) {
                    ALLOC(allocator, self)
                    old = (igObject *)self->_connectCheck;
                    IG_OBJECT_RELEASE(old);
                    self->_connectCheck = (int)beSvConnectCheck_Create(allocator);
                }
                /* matching construct: register trace — one `list` re-pointed at each deliver list: the appends'
                 * lists are its later lifetimes, numbered after the append's count, so they take s3 and the count s4 */
                list = (SlotList *)DELIVERY(info)->_actConnect;
                list->clear();
                list = (SlotList *)DELIVERY(info)->_freeSizeList;
                list->clear();
                list = (SlotList *)DELIVERY(info)->_freeFileList;
                list->clear();
                list = (SlotList *)DELIVERY(info)->_formatList;
                list->clear();
                list = (SlotList *)DELIVERY(info)->_totalSizeList;
                list->clear();
                /* The test reads the deliver through the reference field's `operator->() const`, a temporary of its
                 * own that is not shared with the body's plain read of the field. */
                for (i = 0; i < ((beSvPlatBaseData *)((igSmartPointer<beSvDeliver> &)info->_deliver)->_platformData)->_connectMax; i++) {
                    list = (SlotList *)DELIVERY(info)->_actConnect;
                    list->append(0);
                    list = (SlotList *)DELIVERY(info)->_freeSizeList;
                    list->append(0);
                    list = (SlotList *)DELIVERY(info)->_freeFileList;
                    list->append(0);
                    list = (SlotList *)DELIVERY(info)->_formatList;
                    list->append(0);
                    list = (SlotList *)DELIVERY(info)->_totalSizeList;
                    list->append(0);
                }
                {
                    ALLOC(allocator, self)
                    igSmartPointer<beSvStartApi> request(beSvStartApi_Create(allocator));
                    ((beSaveApiVirtuals *)request.p)->start(DELIVERY(info));
                    *(igSmartPointer<igObject> *)&self->_api = (igObject *)request.p;
                    info->_st2 = info->_st2 + 1;
                    info->_st3 = 0;
                }
                break;
            case 1:
                if (API(self)->poll() != 0) {
                    *(igSmartPointer<igObject> *)&self->_api = 0;
                    info->_isRdy = 1;
                    info->_st1 = 1;
                    info->_st3 = 0;
                    info->_st2 = 0;
                }
                break;
            }
            break;
        case 1:
            beSaveUtil_PollConnectCheck((S0 *)self, (S1 *)info);
            switch (info->_st2) {
            case 0:
                break;
            case 1:
                if (self->_api == 0) {
                    info->_st2 = 0;
                    info->_st3 = 0;
                } else if (API(self)->poll() != 0) {
                    API(self)->report(DELIVERY(info));
                    info->_st2 = 0;
                    info->_st3 = 0;
                    *(igSmartPointer<igObject> *)&self->_api = 0;
                }
                break;
            }
            break;
        case 2:
            switch (info->_st2) {
            case 0: {
                ALLOC(allocator, self)
                igSmartPointer<beSvEndApi> request(beSvEndApi_Create(allocator));
                ((beSaveApiVirtuals *)request.p)->start(DELIVERY(info));
                *(igSmartPointer<igObject> *)&self->_api = (igObject *)request.p;
                info->_st2 = info->_st2 + 1;
                info->_st3 = 0;
                break;
            }
            case 1:
                if (API(self)->poll() != 0) {
                    *(igSmartPointer<igObject> *)&self->_api = 0;
                    info->_st0 = 2;
                    info->_st3 = 0;
                    info->_st2 = 0;
                    info->_st1 = 0;
                }
                break;
            }
            break;
        }
        break;
    case 2:
        list = (SlotList *)DELIVERY(info)->_actConnect;
        list->clear();
        list = (SlotList *)DELIVERY(info)->_freeSizeList;
        list->clear();
        list = (SlotList *)DELIVERY(info)->_freeFileList;
        list->clear();
        list = (SlotList *)DELIVERY(info)->_formatList;
        list->clear();
        info->_isRdy = 0;
        info->_st0 = 3;
        info->_st3 = 0;
        info->_st2 = 0;
        info->_st1 = 0;
        break;
    case 3:
        break;
    }
}

#undef API
#undef DELIVERY

int beSaveUtil_GetInfoMeta(void)
{
    return g_beSaveUtilInfo_metaObject[0];
}

void beSaveUtil_OnAddRam(beSaveUtil * p0, int p1, char * p2)
{
    beMessenger_RegisterReceiverFromInfo(p0->_messenger, p1, SAVEUTILITY_2);
}

#define DELIVER(r) ((Deliver *)(r)->_deliver)
#define NEW_REQUEST(r, kind, create) ALLOC(a, self); RP<kind> r((RC *)create(a));
#define TAKE_SLOT_ARGUMENT(self, info) \
    DELIVER(info)->slot = -1; \
    for (i = 0; i < beMessenger_GetIntCount((self)->_messenger); i++) { \
        int v = beMessenger_GetInt((self)->_messenger, i); \
        switch (i) { case 0: DELIVER(info)->slot = v; break; } \
    }
int beSaveUtil_OnMessage(beSaveUtil *self, beSaveUtilInfoRam *info, MsgArg *msg) {
    int a;
    int i;
    switch (beMessenger_ResolveEnumValue(self->_messenger, FUN_00346c20(), msg->f20)) {
    case 3: {
        NEW_REQUEST(r, 0, beSvFileFindApi_Create)
        TAKE_SLOT_ARGUMENT(self, info)
        ((int)FUN_003ae680((A *)self, (B *)info, (R *)r.p));
        break;
    }
    case 5: {
        NEW_REQUEST(r, 1, beSvUseCheckApi_Create)
        TAKE_SLOT_ARGUMENT(self, info)
        ((int)FUN_003ae680((A *)self, (B *)info, (R *)r.p));
        break;
    }
    case 8: {
        NEW_REQUEST(r, 2, beSvGetFreeSizeApi_Create)
        TAKE_SLOT_ARGUMENT(self, info)
        ((int)FUN_003ae680((A *)self, (B *)info, (R *)r.p));
        break;
    }
    case 2: {
        NEW_REQUEST(r, 3, beSvFileMakeApi_Create)
        TAKE_SLOT_ARGUMENT(self, info)
        if (beMessenger_GetObjectCount(self->_messenger) != 0) {
            DELIVER(info)->f8 = (int)beMessenger_GetObject(self->_messenger, 0);
        }
        FUN_003ae680((A *)self, (B *)info, (R *)r.p);
        break;
    }
    case 4: {
        NEW_REQUEST(r, 4, beSvFormatApi_Create)
        TAKE_SLOT_ARGUMENT(self, info)
        ((int)FUN_003ae680((A *)self, (B *)info, (R *)r.p));
        break;
    }
    case 7: {
        NEW_REQUEST(r, 5, beSvWriteMediaApi_Create)
        TAKE_SLOT_ARGUMENT(self, info)
        if (beMessenger_GetObjectCount(self->_messenger) != 0) {
            DELIVER(info)->f8 = (int)beMessenger_GetObject(self->_messenger, 0);
        }
        FUN_003ae680((A *)self, (B *)info, (R *)r.p);
        break;
    }
    case 6: {
        NEW_REQUEST(r, 6, beSvReadMediaApi_Create)
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
#undef DELIVER

int beSaveUtil_GetMeta(void)
{
    return g_beSaveUtil_metaObject[0];
}
