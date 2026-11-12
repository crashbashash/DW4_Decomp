#include "dw4/reflected.h"
#include "dw4/igSmartPointer.h"
#define SET_KEYNAME(w, text) { \
    const char *tok_; \
    int *old_; \
    if (((void * *)DAT_00586f20)[0] == 0) { \
        void *pool_ = FUN_002eb010(0x10); \
        if (pool_ != 0) pool_ = StringPool_Construct(pool_); \
        ((void * *)DAT_00586f20)[0] = pool_; \
    } \
    tok_ = StringPool_Intern(((void * *)DAT_00586f20)[0], (text)); \
    old_ = (int *)(w)->_keyEventName; \
    if (old_ != 0) { \
        int *hdr_ = old_ - 2; \
        int n_ = old_[-1] - 1; \
        old_[-1] = n_; \
        if (n_ == 0) StringChunk_ReleaseHeader(*hdr_, hdr_); \
    } \
    (w)->_keyEventName = (int)tok_; }
#define SEND_TO_SELF(m, w, str) { \
    beMessenger_SelectReceivers((m), DAT_00516148, 0, arg1->id); \
    beMessenger_AppendObject((m), (w)); \
    beMessenger_DispatchSelected((m), (str)); \
    if (beMessenger_GetBoolCount((m)) != 0) (w)->_isPanel = 1; }

extern "C" igObject *beBaseInfoDataList_Create(...);
extern "C" int FUN_00236f80(int, int);
extern "C" int Gap__Core__igObject__vfunc_23(...);
extern "C" int strcmp(...);
extern "C" int Gap__Bec__beNDMWMdlPlayer__vfunc_35(int dummy0, int arg1);
extern "C" void beMessenger_RegisterReceiverFromInfo(int, int, char *);
extern "C" float atan2f(float, float);
extern "C" int memset(...);
extern "C" int igMatrix44f_SetIdentity(...);
extern "C" int FUN_00191f30(void *, void *, int);
extern "C" int FUN_00192f50(void *, void *, void *);
extern "C" int __divdi3(long long, int);
extern "C" void * FUN_002eb010(...);
extern "C" void *FUN_00354a60(void *);
extern "C" int FUN_00393c80(void *, void *, void *, void *, void *);
extern "C" int FUN_0039a500(int, void *, int, int);
extern "C" int FUN_003a7a20(void *, void *, int);
extern "C" int FUN_003a7e90(void *, void *);
extern "C" void StringChunk_ReleaseHeader(...);
extern "C" void * StringPool_Construct(...);
extern "C" const char * StringPool_Intern(...);
extern "C" int beMessenger_AppendInt(...);
extern "C" int beMessenger_AppendObject(int, void *);
extern "C" int beMessenger_AppendString(...);
extern "C" int beMessenger_DispatchSelected(...);
extern "C" int beMessenger_GetBool(...);
extern "C" int beMessenger_GetBoolCount(...);
extern "C" void *beMessenger_GetString(int, int);
extern "C" int beMessenger_SelectGroup(...);
extern "C" int beMessenger_SelectReceivers(...);
extern "C" int beMessenger_SendNamed(...);
extern "C" int beMessenger_SetRunCheck(int, int);
extern "C" int igNamedObject_SetName(void *, void *);
extern "C" int * igProperty_GetRecord(...);
extern "C" int FUN_00395250(...);
extern "C" int Memory_GetAllocatorBySelector(...);
extern "C" int igObject_GetAllocator(...);
extern "C" void List_Reserve(...);
extern "C" void List_Resize(...);
extern "C" int beMessenger_GetVec3Count(...);
extern "C" int beMessenger_GetMatrixCount(...);
extern "C" void beMessenger_PushArgContext(...);
extern "C" void beMessenger_PopArgContext(...);
extern "C" void beMessenger_AppendMatrix(...);
extern "C" void beMessenger_AppendFloat(int, float);
extern "C" void beMessenger_GetMatrix(...);
extern "C" void Matrix44_Copy(...);
extern "C" int beMessenger_GetObject(...);
extern "C" void beMessenger_SendDelayedNamed(...);
extern "C" void FUN_00396740(...);
extern "C" void sprintf(char *, const char *, int);
extern "C" void beMessenger_AppendVec3(int, int *);
extern "C" void beMessenger_AppendBool(int, int);
extern "C" void *FUN_003bf830(void);
extern "C" int Gap__Bec__beNDMWMdlPlayer__vfunc_20(void);
extern "C" int DAT_00588518[4];
extern "C" int DAT_0058c0a0[4];
extern "C" int DAT_0058c790[4];
extern "C" void Gap__Bec__beNDMWMdlPlayer__vfunc_23(beNDMWMdlPlayer *arg0);
extern "C" int DAT_00516028[4];
extern "C" char DAT_00516038[];
extern "C" void Gap__Bec__beNDMWMdlPlayer__vfunc_37(beNDMWMdlPlayer * p0, int p1, char * p2);
/* Per-frame lobby player update. Two owning references are live across calls: the lobby property
 * list built by CreateProps (igSmartPointer<RefHdr>) and the sub-command object (NamedRef); the unreferenced result
 * slot of the view transform sits between them. Frame-slot order is a compiler constraint, see the
 * "matching construct" notes below. PlayerArg, IntList, RefHdr and PropRec project only the offsets
 * used here. */



typedef struct RefHdr : public igObject { } RefHdr;
typedef struct IntList : public igObject { int count; int cap; int *data; } IntList;
typedef struct PlayerArg : public igObject { int id; char pad12[28]; RefHdr *props; } PlayerArg;
typedef struct PropRec { char pad[20]; beNDMWMdlPlayerInfoWork *work; } PropRec;
extern "C" bePadData * bePadManager_GetPadForPlayer(...);
extern "C" int DAT_004cc730[4];
extern "C" int DAT_004cc770[4];
extern "C" int DAT_004cc780[4];
extern "C" int DAT_004e1098[4];
extern "C" int DAT_00516110[4];
extern "C" int DAT_00516118[4];
extern "C" int DAT_00516120[4];
extern "C" int DAT_00516130[4];
extern "C" int DAT_00516138[4];
extern "C" int DAT_00516148[4];
extern "C" int DAT_00516158[4];
extern "C" int DAT_00516160[4];
extern "C" int DAT_00516168[4];
extern "C" int DAT_00516170[4];
extern "C" int DAT_00516180[4];
extern "C" int DAT_00516188[4];
extern "C" int DAT_00516198[4];
extern "C" int DAT_005161a0[4];
extern "C" int DAT_005161b0[4];
extern "C" int DAT_005161c0[4];
extern "C" int DAT_005161d0[4];
extern "C" int DAT_005161d8[4];
extern "C" int DAT_005161e8[4];
extern "C" int DAT_005161f0[4];
extern "C" int DAT_005161f8[4];
extern "C" int DAT_00516208[4];
extern "C" int DAT_00516218[4];
extern "C" int DAT_00516228[4];
extern "C" int DAT_00516238[4];
extern "C" int DAT_00516248[4];
extern "C" int DAT_00516250[4];
extern "C" int DAT_00516258[4];
extern "C" int DAT_00516260[4];
extern "C" int DAT_00585be0[4];
extern "C" int DAT_00587110[4];
extern "C" unsigned char GPR_00554c14;
struct NamedRef {
    RefHdr *p;
    NamedRef(RefHdr *x) { p = x; }
    ~NamedRef() { igObject *o = (igObject *)p; if (o != 0) { o->_refCount = o->_refCount - 1; if ((o->_refCount & 0x7fffff) == 0) igObject_Destroy(o); } }
};
/* matching construct: slot order.  NamedRef (slot 252) is a block local of the caller; the locals of a
 * static inline member are allocated below the caller's, and `obj` (244) must sit under the view-transform
 * result (248), which is therefore a by-reference temporary (Scratch).  Found by trial (no permuter). */
struct Scratch { int w; Scratch() { } };
struct Locals {
    static inline void CreateProps(PlayerArg *arg1) {
        void *alloc;
        RefHdr *rr;
        RefHdr *old;
        alloc = ((void *)igObject_GetAllocator(arg1));
        alloc = GPR_00554c14 ? alloc : ((void *)Memory_GetAllocatorBySelector(DAT_00587110[0]));
        {
            igSmartPointer<igObject> obj(beBaseInfoDataList_Create(alloc));
            rr = (RefHdr *)obj.p;
            if (rr != 0) rr->_refCount = rr->_refCount + 1;
            old = arg1->props;
            if (old != 0) {
                old->_refCount = old->_refCount - 1;
                if ((old->_refCount & 0x7FFFFF) == 0) igObject_Destroy(old);
            }
            arg1->props = rr;
        }
    }
    static inline void Project(void *a, int view, const Scratch &tmp) {
        FUN_00191f30((void *)&tmp, a, view);
    }
};
extern "C" void Gap__Bec__beNDMWMdlPlayer__vfunc_38(beNDMWMdlPlayer *arg0, PlayerArg *arg1);
extern "C" igObject * beBaseInfoDataList_Create(...);
struct PropertyRecord { char header[20]; beNDMWMdlPlayerInfoWork *value; };
extern "C" PropertyRecord * igProperty_FindByName(...);
extern "C" int DAT_004e0858[4];
extern "C" int DAT_00516270[4];
extern "C" int DAT_00516278[4];
extern "C" int DAT_00516280[4];
extern "C" int DAT_00516290[4];
extern "C" int DAT_00516298[4];
extern "C" int DAT_005162a0[4];
extern "C" int DAT_00586f20[4];
/* matching construct: inline release helper reproduces the retail release sequence */
struct ReleaseRef { static inline void go(igObject *object) {
    if (object) {
        --object->_refCount;
        if (((unsigned long long)(long long)object->_refCount & 0x7fffffULL) == 0)
            igObject_Destroy(object);
    }
} };
/* matching construct: dummy-virtual class: filler virtual slots place vX at the retail vtable offset */
struct MdlPlayerVirtualSlots { virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void vX(void *, void *);};
extern "C" void Gap__Bec__beNDMWMdlPlayer__vfunc_39(beNDMWMdlPlayer *arg0, beBaseInfoRam *arg1);
extern "C" igObject *FUN_003bfc80(int);
extern "C" igIntList *FUN_002caa70(int);
struct PropertyRecord_3d3640 { char p[20]; beNDMWMdlPlayerInfoWork *value; };
struct IntRec { char p[12]; int f12; };
struct ByteRec { char p[12]; unsigned char f12; };
struct ArrRec { char p[12]; igIntList *f12; };
struct BArrRec { char p[12]; igUnsignedCharList *f12; };
struct SListRec { char p[12]; igStringObjList *f12; };
extern "C" ByteRec *igProperty_GetRecordByte(...);
extern "C" ArrRec *FUN_003a9250(...);
extern "C" BArrRec *igProperty_GetRecordArray(...);
extern "C" SListRec *FUN_003a9310(...);
extern "C" int DAT_004cc7b8[4];
extern "C" int DAT_004cc7c0[4];
extern "C" int DAT_004cc7d0[4];
extern "C" int DAT_004cc7e0[4];
extern "C" int DAT_004cc800[4];
extern "C" int DAT_00516368[4];
extern "C" int DAT_00516378[4];
extern "C" int DAT_00516388[4];
extern "C" int DAT_00516390[4];
extern "C" int DAT_005163a0[4];
extern "C" int DAT_005163a8[4];
extern "C" int DAT_005163b0[4];
extern "C" int DAT_005163b8[4];
extern "C" int DAT_005163c0[4];
extern "C" int DAT_005163c8[4];
extern "C" int DAT_005163d8[4];
extern "C" int DAT_005163e0[4];
extern "C" int DAT_005163f0[4];
extern "C" int DAT_00516400[4];
extern "C" int DAT_00516410[4];
extern "C" int DAT_00516420[4];
extern "C" int DAT_00516430[4];
extern "C" int DAT_00516440[4];
extern "C" int DAT_00516448[4];
extern "C" int DAT_00516450[4];
extern "C" int DAT_00516460[4];
extern "C" int DAT_00516470[4];
extern "C" int DAT_00516478[4];
extern "C" int DAT_00516488[4];
extern "C" int DAT_00516490[4];
extern "C" int DAT_00516498[4];
extern "C" int DAT_005164a0[4];
extern "C" unsigned char GPR_005549e0;
struct ReleaseRefInline { static inline void go(igObject *object) {
    if (object) {
        --object->_refCount;
        if (((unsigned long long)(long long)object->_refCount & 0x7fffffULL) == 0)
            igObject_Destroy(object);
    }
} };
/* Owning stack reference to the slot's new data list; released on scope exit (reference count in
 * the low 23 bits of _refCount). */

/* Owning stack reference to the new player info work; released on scope exit. */
class InfoWorkRef {
public:
    igObject *p;
    InfoWorkRef(igObject *o) : p(o) {}
    ~InfoWorkRef() { igObject *o = p; if (o != 0) { --o->_refCount; if ((o->_refCount & 0x7fffff) == 0) igObject_Destroy(o); } }
};
/* Owning stack reference to the new turn-attack timer list; released on scope exit. */
class IntListRef {
public:
    igIntList *p;
    IntListRef(igIntList *l) : p(l) {}
    ~IntListRef() { igIntList *o = p; if (o != 0) { --o->_refCount; if ((o->_refCount & 0x7fffff) == 0) igObject_Destroy(o); } }
};
/* Owning stack reference to a pooled string token (reference count at p[-1], chunk header at
 * p[-2]); releases the token on scope exit. */
class StringRef {
public:
    int *p;
    StringRef(int *s) : p(s) {}
    ~StringRef() { if (p) { int *h = (int *)p - 2; int r = ((int *)p)[-1] - 1; ((int *)p)[-1] = r; if (r == 0) StringChunk_ReleaseHeader(*h, h); } }
};
extern "C" StringRef StringList_CopyRetained(igStringObjList *, int);
struct Slot { static inline void setDataList(beBaseInfoRam *ram, const igSmartPointer<igObject> &r) {
    igObject *t = r.p;
    if (t != 0) t->_refCount = t->_refCount + 1;
    ReleaseRefInline::go((igObject *)ram->_dataList);
    ram->_dataList = (int)t;
}
static inline void adopt(beBaseInfoRam *ram, igObject *created) { igSmartPointer<igObject> list(created); setDataList(ram, list); }
};
struct ParentInfoRef { char header[8]; int *name; };
struct SystemObjectView { char p[56]; int f56; };
extern "C" void Gap__Bec__beNDMWMdlPlayer__vfunc_36(beNDMWMdlPlayer *arg0, beBaseInfoRam *arg1);
extern "C" int DAT_005164b0[4];
struct PropertyRecord_3d40f0 { char pad[20]; int f20; };
struct PropertyPayload { char pad[292]; unsigned char f292; };
struct UnidentifiedArg1Object { char pad[8]; int f8; char pad2[28]; igObject *f40; };
extern "C" void Gap__Bec__beNDMWMdlPlayer__vfunc_40(beNDMWMdlPlayer *arg0, struct UnidentifiedArg1Object *arg1);
/* Minimal view of the property's work record: only the byte flag at +292 is used here. */
struct PropertyData { char p[292]; unsigned char f292; };
struct PropertyRecord_3d4240 { char p[20]; PropertyData *q; };
extern "C" void Gap__Bec__beNDMWMdlPlayer__vfunc_41(beNDMWMdlPlayer *arg0, beBaseInfoRam *arg1);
struct igResult { int w0; igResult() {} igResult(const igResult &o) { w0 = o.w0; } bool operator==(const igResult &o) const { return w0 == o.w0; } };
typedef struct Ref : public igObject { } Ref;
typedef struct Msg {
    char _pad0[8];
    int number;            /* +8  player number */
    char *info;            /* +12 */
    char _pad16[24];
    Ref *cache;            /* +40 */
} Msg;
extern "C" igResult igMetaEnum_GetValueByName(void *, int, int *);
extern "C" void FUN_00445200(void *, Msg *);
extern "C" char DAT_005164b8[];
extern "C" char DAT_005164c8[];
extern "C" char DAT_005164d8[];
extern "C" igResult DAT_004fb410;
extern "C" void Gap__Bec__beNDMWMdlPlayer__vfunc_44(beNDMWMdlPlayer *self, Msg *msg);
struct PropertyRecord_3d45f0 { char p[16]; int f16; PropertyData *q; };
extern "C" int DAT_004cc810[4];
extern "C" int DAT_00516528[4];
extern "C" int DAT_00516538[4];
/* Owning stack reference to the freshly created data list (reference count in the low 23 bits of
 * _refCount); released on scope exit. */

struct RamInfoArg { char p0[8]; int f8; char p1[28]; igObject *m40; };
extern "C" void Gap__Bec__beNDMWMdlPlayer__vfunc_43(beNDMWMdlPlayer *arg0, RamInfoArg *arg1);
/* igProperty record payload: only the flag byte at +292 is used */
struct PropertyValueView { char p[292]; unsigned char f292; };
struct PropertyRecordView { char p[20]; PropertyValueView *q; };
struct Rel { static inline void go(igObject *object) {
    if (object) {
        --object->_refCount;
        if (((unsigned long long)(long long)object->_refCount & 0x7fffffULL) == 0)
            igObject_Destroy(object);
    }
} };
extern "C" void Gap__Bec__beNDMWMdlPlayer__vfunc_42(beNDMWMdlPlayer *arg0, beBaseInfoRam *arg1);
extern "C" int g_beNDMWMdlPlayer_metaObject[4];

void Gap__Bec__beNDMWMdlPlayer__vfunc_23(beNDMWMdlPlayer *arg0) {
    Gap__Core__igObject__vfunc_23();
    arg0->_gameRam = FUN_00236f80(arg0->_insight, DAT_0058c0a0[0]);
    arg0->_padManager = FUN_00236f80(arg0->_insight, DAT_00588518[0]);
    arg0->_viewerSIManager = FUN_00236f80(arg0->_insight, DAT_0058c790[0]);
}

int Gap__Bec__beNDMWMdlPlayer__vfunc_35(int dummy0, int arg1) {
    return strcmp(arg1, &DAT_00516028[0]) == 0;
}

void Gap__Bec__beNDMWMdlPlayer__vfunc_37(beNDMWMdlPlayer * p0, int p1, char * p2)
{
    beMessenger_RegisterReceiverFromInfo(p0->_messenger, p1, DAT_00516038);
}

/* matching construct: intern a string through the global pool and publish it as the key-event name */




void Gap__Bec__beNDMWMdlPlayer__vfunc_38(beNDMWMdlPlayer *arg0, PlayerArg *arg1) {
    beNDMWMdlPlayerInfoWork *w;
    bePadData *pad;
    float stickX, stickY;
    int lStk;
    int hold, trig;
    unsigned char handled;
    bool full;
    int m;
    float spA0[18];
    float spE8[3];

    if (arg1->props == 0) Locals::CreateProps(arg1);
    w = ((PropRec *)igProperty_FindByName(arg1->props, DAT_00585be0[0], DAT_00516110))->work;
    pad = bePadManager_GetPadForPlayer(arg0->_padManager, arg1->id);
    lStk = pad->_lStk;
    stickX = *(float *)&pad->_LStick[0];
    stickY = *(float *)&pad->_LStick[1];
    full = 0;
    if (lStk != 0) {
        int idx;
        IntList *tl;
        int cnt8;
        int i;
        tl = (IntList *)w->_turnAtkTimer;
        idx = DAT_004cc730[lStk];
        if (idx != -1) {
            int c = tl->count;
            if (c != 0 && idx >= 0 && idx < c) tl->data[idx] = DAT_004cc770[0];
        }
        cnt8 = 0;
        for (i = 0; i < 8; i++) {
            int v = tl->data[i];
            if (v > 0) {
                int nv = v - 1;
                if (tl->count != 0 && i >= 0 && i < tl->count) tl->data[i] = nv;
                cnt8++;
            }
        }
        if (cnt8 >= 8) full = 1;
        igMatrix44f_SetIdentity(spA0);
        Locals::Project(spA0, (int)&((igViewerParameters *)((igViewerSceneInfoManager *)arg0->_viewerSIManager)->_parameters)->_viewMatrix, Scratch());
        FUN_00192f50(spE8, DAT_004e1098, spA0);
        {
            float r1 = atan2f(spE8[0], spE8[2]);
            *(float *)&w->_targetDirection[1] = r1 + atan2f(stickX, -stickY);
        }
        w->_keyInput = 1;
    } else {
        w->_keyInput = 0;
    }
    hold = pad->_trigger;
    trig = pad->_button;
    if (w->_isMainLobby == 0) {
        if (strcmp(w->_seqCodeName, DAT_00516118) != 0 && (hold & 0x8000)) {
            SET_KEYNAME(w, DAT_00516120)
        }
        if (trig & 0x8000) {
            float t = w->_bodyAtkTimer;
            if (!(t <= 0.0f)) {
                float n = t - ((beSystem *)arg0->_system)->_frameTimeF;
                if (!(n < 0.0f)) w->_bodyAtkTimer = n;
                else w->_bodyAtkTimer = 0.0f;
            }
            switch (w->_bodyAtkSt0) {
            case 0:
                if (w->_keyInput == 0) w->_bodyAtkSt0 = 1;
                break;
            case 1:
                if (w->_keyInput == 1) {
                    w->_bodyAtkTimer = 15.0f;
                    w->_bodyAtkPad = lStk;
                    w->_bodyAtkSt0 = 2;
                }
                break;
            case 2:
                if (w->_bodyAtkTimer == 0.0f) w->_bodyAtkSt0 = 0;
                else if (w->_keyInput == 0) w->_bodyAtkSt0 = 3;
                break;
            case 3:
                if (w->_bodyAtkTimer == 0.0f) {
                    w->_bodyAtkSt0 = 0;
                } else if (w->_keyInput != 0) {
                    if (lStk == w->_bodyAtkPad && strcmp(w->_seqCodeName, DAT_00516118) != 0 && strcmp(w->_seqCodeName, DAT_00516130) != 0) {
                        SET_KEYNAME(w, DAT_00516138)
                        w->_ctrlSt0 = 0;
                        w->_ctrlSt1 = 0;
                    }
                    w->_bodyAtkSt0 = 0;
                }
                break;
            }
        } else {
            w->_bodyAtkSt0 = 0;
        }
    }
    if (strcmp(w->_seqCodeName, DAT_00516118) != 0 && strcmp(w->_seqCodeName, DAT_00516130) != 0) {
        unsigned char pan = w->_isPanel;
        if (pan != 0) {
            handled = 0;
            beMessenger_SendNamed(arg0->_messenger, DAT_00516148, 0, arg1->id, DAT_00516158);
            m = arg0->_messenger;
            if (beMessenger_GetBoolCount(m) == 0 || !(unsigned char)beMessenger_GetBool(arg0->_messenger, 0)) {
                w->_isPanel = 0;
            } else if (beMessenger_GetBool(arg0->_messenger, 2) != 0) {
                if (beMessenger_GetBool(arg0->_messenger, 1) != 0) {
                    SET_KEYNAME(w, DAT_00516160)
                } else {
                    FUN_00393c80(arg0, arg1, w, DAT_00516168, beMessenger_GetString(arg0->_messenger, 0));
                    SET_KEYNAME(w, DAT_00516168)
                }
                handled = 1;
            }
            if (!(handled & 0xFF)) {
                if (hold & 0x2000) {
                    SET_KEYNAME(w, DAT_00516118)
                    return;
                }
                if (hold & 0x1000) {
                    SEND_TO_SELF(arg0->_messenger, w, DAT_00516170)
                } else if (w->_keyInput == 0 && !(trig & ~8) && (hold & 8)) {
                    beMessenger_SelectGroup(arg0->_messenger, DAT_00516180);
                    beMessenger_AppendString(arg0->_messenger, DAT_00516188);
                    beMessenger_DispatchSelected(arg0->_messenger, DAT_00516198);
                }
            }
        } else {
            if (hold & 0x2000) {
                SET_KEYNAME(w, DAT_00516118)
                return;
            }
            if (hold & 0x1000) {
                SEND_TO_SELF(arg0->_messenger, w, DAT_00516170)
            } else if ((hold & 0x400) && !(pan & 0xFF)) {
                SEND_TO_SELF(arg0->_messenger, w, DAT_005161a0)
            } else if ((hold & 0x800) && !(pan & 0xFF)) {
                SEND_TO_SELF(arg0->_messenger, w, DAT_005161b0)
            } else if ((hold & 0x200) && !(pan & 0xFF)) {
                SEND_TO_SELF(arg0->_messenger, w, DAT_005161c0)
            } else if (hold & 0x4000) {
                if (w->_isMainLobby != 0) {
                    int *o;
                    void *al2 = ((void *)igObject_GetAllocator(arg0));
                    al2 = GPR_00554c14 ? al2 : ((void *)Memory_GetAllocatorBySelector(DAT_00587110[0]));
                    {
                        NamedRef nobj((RefHdr *)FUN_00354a60(al2));
                        igNamedObject_SetName((void *)nobj.p, DAT_005161d0);
                        ((int *)nobj.p)[3] = 0xEA60;
                        ((int *)nobj.p)[4] = 0x3F800000;
                        ((int *)nobj.p)[5] = 0x3F800000;
                        o = (int *)nobj.p;
                        o[6] = 0;
                        o[7] = 0x40800000;
                        o[8] = 0x40E00000;
                        o = (int *)nobj.p;
                        o[9] = 0x40400000;
                        o[10] = 0x40400000;
                        o[11] = 0x40400000;
                        FUN_0039a500(w->_subCommand, (void *)nobj.p, 0x3F800000, 0xEA60);
                    }
                } else {
                    beMessenger_SelectGroup(arg0->_messenger, DAT_005161d8);
                    beMessenger_AppendInt(arg0->_messenger, arg1->id);
                    beMessenger_SetRunCheck(arg0->_messenger, 1);
                    beMessenger_DispatchSelected(arg0->_messenger, DAT_005161e8);
                    if (beMessenger_GetBoolCount(arg0->_messenger) == 0 && FUN_003a7e90(arg1, DAT_005161f0) != 0) {
                        int lv;
                        int q;
                        if (full) {
                            IntList *tl2;
                            SET_KEYNAME(w, DAT_005161f8)
                            tl2 = (IntList *)w->_turnAtkTimer;
                            if (tl2->count != 0) memset(tl2->data, 0, tl2->count * 4);
                        } else {
                            SET_KEYNAME(w, DAT_00516208)
                        }
                        lv = igProperty_GetRecord(((int *)((IntList *)((beNDMWGameRam *)arg0->_gameRam)->_playerDataListList)->data)[arg1->id], DAT_00516218)[3];
                        FUN_003a7a20(arg1, DAT_005161f0, __divdi3((long long)lv * 1000000000, 0x3C));
                        q = (lv - 22) / 4;
                        beMessenger_SendNamed(arg0->_messenger, DAT_00516228, DAT_00516238, arg1->id, (void *)DAT_004cc780[q]);
                    }
                }
            } else if (w->_keyInput == 0 && !(trig & ~8) && (hold & 8)) {
                beMessenger_SendNamed(arg0->_messenger, DAT_00516148, 0, -1, DAT_00516248);
                if (beMessenger_GetBoolCount(arg0->_messenger) != 0 && (unsigned char)beMessenger_GetBool(arg0->_messenger, 0) == 1) {
                    beMessenger_SelectGroup(arg0->_messenger, DAT_00516180);
                    beMessenger_AppendString(arg0->_messenger, DAT_00516188);
                    beMessenger_DispatchSelected(arg0->_messenger, DAT_00516198);
                    return;
                }
                beMessenger_SelectReceivers(arg0->_messenger, DAT_00516250, 0, 0);
                beMessenger_AppendInt(arg0->_messenger, arg1->id);
                beMessenger_AppendString(arg0->_messenger, DAT_00516258);
                beMessenger_DispatchSelected(arg0->_messenger, DAT_00516260);
            }
        }
    }
}

/* Owning stack reference to the freshly created property list; released on scope exit once the ram
 * holds its own reference (reference count in the low 23 bits of _refCount). */

void Gap__Bec__beNDMWMdlPlayer__vfunc_39(beNDMWMdlPlayer *arg0, beBaseInfoRam *arg1) {
    igObject *t0;
    beBaseInfo *s1;
    beNDMWMdlPlayerInfoWork *s0;
    int s4;
    /* matching construct: separate per-arm ni/old locals, declared in this order, fix register allocation */
    int *ni1;
    int *ni2;
    int *ni3;
    int *old1;
    int *old2;
    int *old3;
    int *a2;
    int a3;
    s1 = (beBaseInfo *)arg1->_parentInfo;
    if (arg1->_dataList == 0) {
        int alloc = igObject_GetAllocator(arg1);
        int a;
        if (GPR_00554c14 != 0) {
            a = alloc;
        } else {
            a = Memory_GetAllocatorBySelector(DAT_00587110[0]);
        }
        igSmartPointer<igObject> created(beBaseInfoDataList_Create(a));
        t0 = created.p;
        if (t0 != 0) {
            t0->_refCount++;
        }
        ReleaseRef::go((igObject *)arg1->_dataList);
        arg1->_dataList = (int)t0;
    }
    s0 = igProperty_FindByName((void *)arg1->_dataList, DAT_00585be0[0], DAT_00516110)->value;
    s4 = 0;
    if (s0->_isOnCtrl != 0) {
        s4 = bePadManager_GetPadForPlayer(arg0->_padManager, arg1->_ramNo)->_button;
    }
    if (strcmp(s0->_wCheckName, DAT_00516270) == 0) {
        switch (s0->_wCheckSt) {
        case 0:
            s0->_wCheckMode = 0;
            s0->_wCheckSt = 1;
        case 1:
            if (!(s4 & 0x4000)) {
                s0->_wCheckMode = 1;
            }
            a2 = (int *)s1->_name;
            a3 = arg1->_ramNo;
            a2 = a2 ? a2 : DAT_004e0858;
            beMessenger_SendNamed(arg0->_messenger, DAT_00516278, a2, a3, DAT_00516280);
            if (beMessenger_GetBool(arg0->_messenger, 0) != 0) {
                if (DAT_00586f20[0] == 0) {
                    int n = ((int)FUN_002eb010(16));
                    if (n != 0) n = ((int)StringPool_Construct(n));
                    DAT_00586f20[0] = n;
                }
                ni1 = ((int *)StringPool_Intern(DAT_00586f20[0], 0));
                old1 = (int *)s0->_wCheckName;
                if (old1 != 0) {
                    int *hd = old1 - 2;
                    int c = old1[-1] - 1;
                    old1[-1] = c;
                    if (c == 0) StringChunk_ReleaseHeader(*hd, hd);
                }
                s0->_wCheckName = (int)ni1;
                s0->_wCheckSt = 0;
                if (s0->_wCheckMode == 0) {
                    FUN_00395250(arg0, s1, arg1, s0);
                    return;
                }
                ((MdlPlayerVirtualSlots *)arg0)->vX(arg1, DAT_00516290);
                return;
            }
            break;
        }
    } else if (strcmp(s0->_wCheckName, DAT_00516298) == 0) {
        if (!(s4 & 0x4000)) {
            ((MdlPlayerVirtualSlots *)arg0)->vX(arg1, DAT_00516290);
        }
        a2 = (int *)s1->_name;
        a3 = arg1->_ramNo;
        a2 = a2 ? a2 : DAT_004e0858;
        beMessenger_SendNamed(arg0->_messenger, DAT_00516278, a2, a3, DAT_00516280);
        if (beMessenger_GetBool(arg0->_messenger, 0) != 0) {
            if (DAT_00586f20[0] == 0) {
                int n = ((int)FUN_002eb010(16));
                if (n != 0) n = ((int)StringPool_Construct(n));
                DAT_00586f20[0] = n;
            }
            ni2 = ((int *)StringPool_Intern(DAT_00586f20[0], 0));
            old2 = (int *)s0->_wCheckName;
            if (old2 != 0) {
                int *hd = old2 - 2;
                int c = old2[-1] - 1;
                old2[-1] = c;
                if (c == 0) StringChunk_ReleaseHeader(*hd, hd);
            }
            s0->_wCheckName = (int)ni2;
            FUN_00395250(arg0, s1, arg1, s0);
        }
    } else if (strcmp(s0->_wCheckName, DAT_005162a0) == 0 && !(s4 & 0x4000)) {
        if (DAT_00586f20[0] == 0) {
            int n = ((int)FUN_002eb010(16));
            if (n != 0) n = ((int)StringPool_Construct(n));
            DAT_00586f20[0] = n;
        }
        ni3 = ((int *)StringPool_Intern(DAT_00586f20[0], 0));
        old3 = (int *)s0->_wCheckName;
        if (old3 != 0) {
            int *hd = old3 - 2;
            int c = old3[-1] - 1;
            old3[-1] = c;
            if (c == 0) StringChunk_ReleaseHeader(*hd, hd);
        }
        s0->_wCheckName = (int)ni3;
        FUN_00395250(arg0, s1, arg1, s0);
    }
}

void Gap__Bec__beNDMWMdlPlayer__vfunc_36(beNDMWMdlPlayer *arg0, beBaseInfoRam *arg1) {
    float spC0[16];
    float sp80[16];
    ParentInfoRef *s6;
    PropertyRecord_3d3640 *s3;
    beNDMWMdlPlayerInfoWork *s5;
    igObject *s0o;
    igIntList *l0;
    s6 = (ParentInfoRef *)arg1->_parentInfo;
    if (arg1->_dataList == 0) {
        int alloc = igObject_GetAllocator(arg1);
        int a;
        if (GPR_00554c14 != 0) {
            a = alloc;
        } else {
            a = Memory_GetAllocatorBySelector(DAT_00587110[0]);
        }
        igObject *created = beBaseInfoDataList_Create(a);
        /* matching construct: the new list is a temporary bound to the setter's reference parameter (it
         * takes the stack slot below the named references, as retail's +0x100 does) */
        Slot::adopt(arg1, created);
    }
    s3 = ((PropertyRecord_3d3640 *)igProperty_FindByName((void *)arg1->_dataList, DAT_00585be0[0], DAT_00516110));
    {
        int alloc = igObject_GetAllocator(arg0);
        int a;
        if (GPR_00554c14 != 0) {
            a = alloc;
        } else {
            a = Memory_GetAllocatorBySelector(DAT_00587110[0]);
        }
        InfoWorkRef work(FUN_003bfc80(a));
        s0o = work.p;
        if (s0o != 0) {
            s0o->_refCount++;
        }
        ReleaseRefInline::go((igObject *)s3->value);
        s3->value = (beNDMWMdlPlayerInfoWork *)s0o;
        s5 = (beNDMWMdlPlayerInfoWork *)work.p;
        s5->_isPlayer = 1;
        s5->_directionLimiter[0] = 0.0f;
        s5->_directionLimiter[1] = 7.0f;
        s5->_directionLimiter[2] = 0.0f;
        {
            int alloc = igObject_GetAllocator(arg0);
            int a;
            if (GPR_00554c14 != 0) {
                a = alloc;
            } else {
                a = Memory_GetAllocatorBySelector(DAT_00587110[0]);
            }
            IntListRef timer(FUN_002caa70(a));
            {
                igIntList *t = timer.p;
                if (t->_count < 9) {
                    List_Reserve(t, 8, 4);
                }
            }
            {
                igIntList *t = timer.p;
                if (t->_capacity >= 8) {
                    t->_count = 8;
                } else {
                    List_Resize(t, 8, 4);
                }
            }
            l0 = timer.p;
            if (l0->_count != 0) {
                memset(l0->_data, 0, l0->_count * 4);
            }
            l0 = timer.p;
            if (l0 != 0) {
                l0->_refCount++;
            }
            ReleaseRefInline::go((igObject *)s5->_turnAtkTimer);
            s5->_turnAtkTimer = (int)l0;
        }
    }
    if (beMessenger_GetVec3Count(arg0->_messenger) == 0 && beMessenger_GetMatrixCount(arg0->_messenger) == 0) {
        igMatrix44f_SetIdentity(spC0);
        beMessenger_PushArgContext(arg0->_messenger);
        beMessenger_SelectGroup(arg0->_messenger, DAT_00516368);
        beMessenger_AppendInt(arg0->_messenger, 0);
        beMessenger_AppendInt(arg0->_messenger, arg1->_ramNo);
        beMessenger_DispatchSelected(arg0->_messenger, DAT_00516378);
        if (beMessenger_GetMatrixCount(arg0->_messenger) != 0) {
            beMessenger_GetMatrix(sp80, arg0->_messenger, 0);
            Matrix44_Copy(spC0, sp80);
        }
        beMessenger_PopArgContext(arg0->_messenger);
        beMessenger_AppendMatrix(arg0->_messenger, spC0);
    }
    FUN_00396740(arg0, arg1);
    beMessenger_SelectGroup(arg0->_messenger, DAT_00516388);
    beMessenger_AppendInt(arg0->_messenger, arg1->_ramNo);
    beMessenger_DispatchSelected(arg0->_messenger, DAT_00516390);
    int obj = beMessenger_GetObject(arg0->_messenger, 0);
    {
        IntRec *r3 = ((IntRec *)igProperty_GetRecord(obj, DAT_005163a0));
        if (r3 != 0) ((igObject *)r3)->_refCount++;
        ReleaseRefInline::go((igObject *)s5->_hp);
        s5->_hp = (int)r3;
    }
    {
        IntRec *r3 = ((IntRec *)igProperty_GetRecord(obj, DAT_005163a8));
        if (r3 != 0) ((igObject *)r3)->_refCount++;
        ReleaseRefInline::go((igObject *)s5->_mHp);
        s5->_mHp = (int)r3;
    }
    if (((IntRec *)s5->_hp)->f12 == 0) {
        int t = ((IntRec *)igProperty_GetRecord(obj, DAT_005163a8))->f12;
        ((IntRec *)igProperty_GetRecord(obj, DAT_005163a0))->f12 = t;
        t = ((IntRec *)igProperty_GetRecord(obj, DAT_005163b0))->f12;
        ((IntRec *)igProperty_GetRecord(obj, DAT_005163b8))->f12 = t;
    }
    {
        int i = 0, off = 0;
        do {
            igIntList *v = FUN_003a9250(obj, DAT_005163c0)->f12;
            if (v->_count != 0 && i >= 0 && i < v->_count) {
                *(int *)(v->_data + off) /* matching construct: byte-offset element write; indexing by i or off/4 changes the induction variable */ = DAT_004cc7b8[0];
            }
            i += 1;
            off += 4;
        } while (i < 7);
    }
    {
        int i = 0, off = 0;
        do {
            igIntList *v = FUN_003a9250(obj, DAT_005163c8)->f12;
            if (v->_count != 0 && i >= 0 && i < v->_count) {
                *(int *)(v->_data + off) /* matching construct: byte-offset element write; indexing by i or off/4 changes the induction variable */ = DAT_004cc7c0[0];
            }
            i += 1;
            off += 4;
        } while (i < 6);
    }
    if (igProperty_GetRecordByte(obj, DAT_005163d8)->f12 == 0) {
        int *a1;
        beMessenger_SelectGroup(arg0->_messenger, DAT_00516388);
        beMessenger_AppendInt(arg0->_messenger, arg1->_ramNo);
        a1 = s6->name;
        a1 = a1 ? a1 : DAT_004e0858;
        beMessenger_AppendString(arg0->_messenger, a1);
        beMessenger_AppendString(arg0->_messenger, DAT_004cc7d0[arg1->_ramNo]);
        beMessenger_DispatchSelected(arg0->_messenger, DAT_005163e0);
        igUnsignedCharList *bv = igProperty_GetRecordArray(obj, DAT_005163f0)->f12;
        int n = bv->_count;
        unsigned char *d = (unsigned char *)bv->_data;
        for (int i = 0; i < n; i++) {
            d[i] = GPR_005549e0;
        }
    }
    if (FUN_003a9310(obj, DAT_00516400)->f12->_count != 0) {
        StringRef name = StringList_CopyRetained(FUN_003a9310(obj, DAT_00516400)->f12, 0);
        beMessenger_SendDelayedNamed(arg0->_messenger, DAT_00516410, name.p, arg1->_ramNo, DAT_00516260, 1);
    }
    beMessenger_SelectGroup(arg0->_messenger, DAT_00516388);
    beMessenger_AppendInt(arg0->_messenger, arg1->_ramNo);
    beMessenger_DispatchSelected(arg0->_messenger, DAT_00516420);
    beMessenger_SelectReceivers(arg0->_messenger, DAT_00516430, DAT_00516440, arg1->_ramNo);
    beMessenger_AppendInt(arg0->_messenger, ((IntRec *)igProperty_GetRecord(obj, DAT_00516448))->f12);
    beMessenger_DispatchSelected(arg0->_messenger, DAT_00516450);
    beMessenger_SelectReceivers(arg0->_messenger, DAT_00516460, DAT_00516470, arg1->_ramNo);
    {
        int d = ((IntRec *)igProperty_GetRecord(obj, DAT_005163a8))->f12;
        beMessenger_AppendFloat(arg0->_messenger, (100.0f * (float)((IntRec *)igProperty_GetRecord(obj, DAT_005163a0))->f12) / (float)d);
    }
    beMessenger_DispatchSelected(arg0->_messenger, DAT_00516478);
    beMessenger_SelectReceivers(arg0->_messenger, DAT_00516430, DAT_00516488, arg1->_ramNo);
    beMessenger_AppendInt(arg0->_messenger, ((IntRec *)igProperty_GetRecord(obj, DAT_005163a0))->f12);
    beMessenger_DispatchSelected(arg0->_messenger, DAT_00516450);
    beMessenger_SelectReceivers(arg0->_messenger, DAT_00516460, DAT_00516490, arg1->_ramNo);
    {
        int n = ((IntRec *)igProperty_GetRecord(obj, DAT_005163b8))->f12;
        IntRec *r = ((IntRec *)igProperty_GetRecord(obj, DAT_005163b0));
        beMessenger_AppendFloat(arg0->_messenger, (float)(n * 100 / r->f12));
    }
    beMessenger_DispatchSelected(arg0->_messenger, DAT_00516478);
    beMessenger_SelectReceivers(arg0->_messenger, DAT_00516430, DAT_00516498, arg1->_ramNo);
    beMessenger_AppendInt(arg0->_messenger, ((IntRec *)igProperty_GetRecord(obj, DAT_005163b8))->f12);
    beMessenger_DispatchSelected(arg0->_messenger, DAT_00516450);
    int s4 = ((SystemObjectView *)arg0->_system)->f56;
    for (int j = 0; j < 5; j++) {
        if (strcmp(((int *)DAT_004cc7e0)[j], s4) == 0) {
            beMessenger_SendNamed(arg0->_messenger, ((int *)DAT_00516038), 0, arg1->_ramNo, DAT_005164a0);
            break;
        }
    }
    for (int k = 0; k < 4; k++) {
        if (strcmp(((int *)DAT_004cc800)[k], s4) == 0) {
            s5->_isMainLobby = 1;
            break;
        }
    }
}

/* Owning stack reference to the freshly created data list; released on scope exit (reference count
 * in the low 23 bits of _refCount). */

void Gap__Bec__beNDMWMdlPlayer__vfunc_40(beNDMWMdlPlayer *arg0, struct UnidentifiedArg1Object *arg1) {
    struct PropertyPayload *q;

    if (arg1->f40 == 0) {
        int al = igObject_GetAllocator(arg1);
        igSmartPointer<igObject> created(beBaseInfoDataList_Create(GPR_00554c14 != 0 ? al : Memory_GetAllocatorBySelector(DAT_00587110[0])));
        igObject *t = created.p;
        if (t != 0) {
            t->_refCount = t->_refCount + 1;
        }
        igObject *u = arg1->f40;
        if (u != 0) {
            u->_refCount = u->_refCount - 1;
            if ((u->_refCount & 0x7FFFFF) == 0) {
                igObject_Destroy(u);
            }
        }
        arg1->f40 = t;
    }
    q = (struct PropertyPayload *)((struct PropertyRecord_3d40f0 *)igProperty_FindByName(arg1->f40, DAT_00585be0[0], &DAT_00516110[0]))->f20;
    if (q->f292 != 0) {
        q->f292 = 0U;
        beMessenger_SendNamed(arg0->_messenger, &DAT_00516148[0], 0, arg1->f8, &DAT_005164b0[0]);
    }
}

void Gap__Bec__beNDMWMdlPlayer__vfunc_41(beNDMWMdlPlayer *arg0, beBaseInfoRam *arg1) {
    igObject *s0;
    if (arg1->_dataList == 0) {
        int alloc = igObject_GetAllocator(arg1);
        int a;
        igObject *old;
        if (GPR_00554c14 != 0) {
            a = alloc;
        } else {
            a = Memory_GetAllocatorBySelector(DAT_00587110[0]);
        }
        igSmartPointer<igObject> ref(beBaseInfoDataList_Create(a));
        s0 = ref.p;
        if (s0 != 0) {
            s0->_refCount++;
        }
        old = (igObject *)arg1->_dataList;
        if (old != 0) {
            --old->_refCount;
            if ((old->_refCount & 0x7fffff) == 0) igObject_Destroy(old);
        }
        arg1->_dataList = (int)s0;
    }
    PropertyData *q = ((PropertyRecord_3d4240 *)igProperty_FindByName(arg1->_dataList, DAT_00585be0[0], DAT_00516110))->q;
    if (q->f292 != 0) {
        q->f292 = 0;
        beMessenger_SendNamed(arg0->_messenger, DAT_00516148, 0, arg1->_ramNo, DAT_005164b0);
    }
}

static inline void ensureCache(Msg *msg)
{
    if (msg->cache == 0) {
        void *al = ((void *)igObject_GetAllocator(msg));
        void *al2;
        if (GPR_00554c14 != 0) {
            al2 = al;
        } else {
            al2 = ((void *)Memory_GetAllocatorBySelector(DAT_00587110[0]));
        }
        igSmartPointer<igObject> t(beBaseInfoDataList_Create(al2));
        Ref *r = (Ref *)t.p;
        if (r) r->_refCount++;
        Ref *old = msg->cache;
        if (old) {
            old->_refCount--;
            if ((old->_refCount & 0x7fffff) == 0) igObject_Destroy(old);
        }
        msg->cache = r;
    }
}

void Gap__Bec__beNDMWMdlPlayer__vfunc_44(beNDMWMdlPlayer *self, Msg *msg)
{
    beNDMWMdlPlayerInfoWork *pinfo;
    Ref *r;
    char *minfo = msg->info;
    char name[24];
    int vec[3];
    int tmp;
    ensureCache(msg);
    Ref *c0 = msg->cache;
    pinfo = igProperty_FindByName(c0, DAT_00585be0[0], ((char *)DAT_00516110))->value;
    if (strcmp(pinfo->_seqCodeName, ((char *)DAT_00516290)) == 0) {
        const char *who = *(char **)(minfo + 8);
        int num = msg->number;
        const char *w2 = who ? who : ((char *)DAT_004e0858);
        beMessenger_SelectReceivers(self->_messenger, ((char *)DAT_00516228), w2, num);
        beMessenger_AppendString(self->_messenger, DAT_005164b8);
        sprintf(name, DAT_005164c8, msg->number);
        beMessenger_AppendString(self->_messenger, name);
        beMessenger_AppendFloat(self->_messenger, 480.0f);
        vec[0] = 0; vec[1] = 0x41200000; vec[2] = 0;
        beMessenger_AppendVec3(self->_messenger, vec);
        beMessenger_AppendBool(self->_messenger, 1);
        beMessenger_AppendBool(self->_messenger, 1);
        beMessenger_DispatchSelected(self->_messenger, DAT_005164d8);
    }
    if (pinfo->_isPanel != 0) {
        if (igMetaEnum_GetValueByName(FUN_003bf830(), pinfo->_seqCodeName, &tmp) == DAT_004fb410) {
            pinfo->_isPanel = 0;
            beMessenger_SendNamed(self->_messenger, ((char *)DAT_00516148), 0, msg->number, ((char *)DAT_005164b0));
        }
    }
    FUN_00445200(self, msg);
}

void Gap__Bec__beNDMWMdlPlayer__vfunc_43(beNDMWMdlPlayer *arg0, RamInfoArg *arg1) {
    igObject *s0;
    PropertyRecord_3d45f0 *s3;
    PropertyData *q;
    if (arg1->m40 == 0) {
        int alloc = igObject_GetAllocator(arg1);
        int a;
        if (GPR_00554c14 != 0) {
            a = alloc;
        } else {
            a = Memory_GetAllocatorBySelector(DAT_00587110[0]);
        }
        {
            igSmartPointer<igObject> r(beBaseInfoDataList_Create(a));
            s0 = r.p;
            if (s0 != 0) {
                s0->_refCount++;
            }
            ReleaseRefInline::go(arg1->m40);
            arg1->m40 = s0;
        }
    }
    s3 = ((PropertyRecord_3d45f0 *)igProperty_FindByName(arg1->m40, DAT_00585be0[0], DAT_00516110));
    q = s3->q;
    beMessenger_SelectReceivers(arg0->_messenger, DAT_00516228, DAT_00516528, arg1->f8);
    beMessenger_AppendMatrix(arg0->_messenger, s3->f16 + 32);
    beMessenger_AppendString(arg0->_messenger, DAT_004cc810[arg1->f8]);
    beMessenger_DispatchSelected(arg0->_messenger, DAT_00516260);
    beMessenger_SendNamed(arg0->_messenger, DAT_00516228, DAT_00516528, arg1->f8, DAT_00516248);
    if (beMessenger_GetBoolCount(arg0->_messenger) != 0 && (beMessenger_GetBool(arg0->_messenger, 0) & 0xff) == 1) {
        beMessenger_SelectGroup(arg0->_messenger, DAT_00516388);
        beMessenger_AppendInt(arg0->_messenger, arg1->f8);
        beMessenger_DispatchSelected(arg0->_messenger, DAT_00516538);
    }
    if (q->f292 != 0) {
        q->f292 = 0;
        beMessenger_SendNamed(arg0->_messenger, DAT_00516148, 0, arg1->f8, DAT_005164b0);
    }
}

/* Owning stack reference to the freshly created property list; released on scope exit once the ram
 * holds its own reference (reference count in the low 23 bits of _refCount). */

void Gap__Bec__beNDMWMdlPlayer__vfunc_42(beNDMWMdlPlayer *arg0, beBaseInfoRam *arg1) {
    igObject *s0;
    if (((igObject *)arg1->_dataList) == 0) {
        int alloc = igObject_GetAllocator(arg1);
        int a;
        if (GPR_00554c14 != 0) {
            a = alloc;
        } else {
            a = Memory_GetAllocatorBySelector(DAT_00587110[0]);
        }
        igSmartPointer<igObject> created(beBaseInfoDataList_Create(a));
        s0 = created.p;
        if (s0 != 0) {
            s0->_refCount++;
        }
        Rel::go(((igObject *)arg1->_dataList));
        arg1->_dataList = (int)s0;
    }
    PropertyValueView *q = ((PropertyRecordView *)igProperty_FindByName(((igObject *)arg1->_dataList), DAT_00585be0[0], DAT_00516110))->q;
    if (q->f292 != 0) {
        q->f292 = 0;
        beMessenger_SendNamed(arg0->_messenger, DAT_00516148, 0, arg1->_ramNo, DAT_005164b0);
    }
}

int Gap__Bec__beNDMWMdlPlayer__vfunc_20(void)
{
    return g_beNDMWMdlPlayer_metaObject[0];
}
