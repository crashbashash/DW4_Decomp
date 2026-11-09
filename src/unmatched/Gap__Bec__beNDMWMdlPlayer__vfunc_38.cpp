/* Per-frame lobby player update. Two owning references are live across calls: the lobby property
 * list built by CreateProps (igSmartPointer<RefHdr>) and the sub-command object (NamedRef); the unreferenced result
 * slot of the view transform sits between them. Frame-slot order is a compiler constraint, see the
 * "matching construct" notes below. PlayerArg, IntList, RefHdr and PropRec project only the offsets
 * used here. */
#include "dw4/reflected.h"

typedef struct RefHdr { int vt; int refs; } RefHdr;
typedef struct IntList { int vt; unsigned refs; int count; int cap; int *data; } IntList;
typedef struct PlayerArg { int vt; unsigned refs; int id; char pad12[28]; RefHdr *props; } PlayerArg;
typedef struct PropRec { char pad[20]; beNDMWMdlPlayerInfoWork *work; } PropRec;

extern "C" {
float atan2f(float, float);
int memset(void *, int, int);
int igMatrix44f_SetIdentity(void *);
int FUN_00191f30(void *, void *, int);
int FUN_00192f50(void *, void *, void *);
int __divdi3(long long, int);
void *FUN_002eb010(int);
void *FUN_00354a60(void *);
void *beBaseInfoDataList_Create(void *);
int FUN_00393c80(void *, void *, void *, void *, void *);
int FUN_0039a500(int, void *, int, int);
int FUN_003a7a20(void *, void *, int);
int FUN_003a7e90(void *, void *);
void *Memory_GetAllocatorBySelector(int);
void StringChunk_ReleaseHeader(int, int *);
void *StringPool_Construct(void *);
const char *StringPool_Intern(void *, void *);
int beMessenger_AppendInt(int, int);
int beMessenger_AppendObject(int, void *);
int beMessenger_AppendString(int, void *);
int beMessenger_DispatchSelected(int, void *);
int beMessenger_GetBool(int, int);
int beMessenger_GetBoolCount(int);
void *beMessenger_GetString(int, int);
int beMessenger_SelectGroup(int, void *);
int beMessenger_SelectReceivers(int, void *, int, int);
int beMessenger_SendNamed(int, void *, void *, int, void *);
int beMessenger_SetRunCheck(int, int);
bePadData *bePadManager_GetPadForPlayer(int, int);
int igNamedObject_SetName(void *, void *);
void igObject_Destroy(void *);
void *igObject_GetAllocator(void *);
PropRec *igProperty_FindByName(RefHdr *, int, void *);
int *igProperty_GetRecord(int, void *);
int strcmp(int, void *);
extern int DAT_004cc730[4];
extern int DAT_004cc770[4];
extern int DAT_004cc780[4];
extern int DAT_004e1098[4];
extern int DAT_00516110[4];
extern int DAT_00516118[4];
extern int DAT_00516120[4];
extern int DAT_00516130[4];
extern int DAT_00516138[4];
extern int DAT_00516148[4];
extern int DAT_00516158[4];
extern int DAT_00516160[4];
extern int DAT_00516168[4];
extern int DAT_00516170[4];
extern int DAT_00516180[4];
extern int DAT_00516188[4];
extern int DAT_00516198[4];
extern int DAT_005161a0[4];
extern int DAT_005161b0[4];
extern int DAT_005161c0[4];
extern int DAT_005161d0[4];
extern int DAT_005161d8[4];
extern int DAT_005161e8[4];
extern int DAT_005161f0[4];
extern int DAT_005161f8[4];
extern int DAT_00516208[4];
extern int DAT_00516218[4];
extern int DAT_00516228[4];
extern int DAT_00516238[4];
extern int DAT_00516248[4];
extern int DAT_00516250[4];
extern int DAT_00516258[4];
extern int DAT_00516260[4];
extern int DAT_00585be0[4];
extern void *DAT_00586f20[4];
extern int DAT_00587110[4];
extern unsigned char GPR_00554c14;

}

template <class T> struct igSmartPointer {
    T *p;
    igSmartPointer(T *x) { p = x; }
    ~igSmartPointer() { igObject *o = (igObject *)p; if (o != 0) { o->_refCount = o->_refCount - 1; if ((o->_refCount & 0x7fffff) == 0) igObject_Destroy(o); } }
};
struct NamedRef {
    RefHdr *p;
    NamedRef(RefHdr *x) { p = x; }
    ~NamedRef() { igObject *o = (igObject *)p; if (o != 0) { o->_refCount = o->_refCount - 1; if ((o->_refCount & 0x7fffff) == 0) igObject_Destroy(o); } }
};

/* matching construct: slot order.  NamedRef (slot 252) is a block local of the caller; the locals of a
 * static inline member are allocated below the caller's, and `obj` (244) must sit under the view-transform
 * result (248), which is therefore a by-reference temporary (Scratch).  inline_depth(8) keeps igSmartPointer<RefHdr>'s
 * destructor inline inside the inlined helper.  Found by trial (no permuter). */
struct Scratch { int w; Scratch() { } };
struct Locals {
    static inline void CreateProps(PlayerArg *arg1) {
        void *alloc;
        RefHdr *rr;
        RefHdr *old;
        alloc = igObject_GetAllocator(arg1);
        alloc = GPR_00554c14 ? alloc : Memory_GetAllocatorBySelector(DAT_00587110[0]);
        {
            igSmartPointer<RefHdr> obj((RefHdr *)beBaseInfoDataList_Create(alloc));
            rr = obj.p;
            if (rr != 0) rr->refs = rr->refs + 1;
            old = arg1->props;
            if (old != 0) {
                old->refs = old->refs - 1;
                if (((unsigned long long)((long long)old->refs << 0x29) >> 0x29) == 0) igObject_Destroy(old);
            }
            arg1->props = rr;
        }
    }
    static inline void Project(void *a, int view, const Scratch &tmp) {
        FUN_00191f30((void *)&tmp, a, view);
    }
};
/* matching construct: intern a string through the global pool and publish it as the key-event name */
#define SET_KEYNAME(w, text) { \
    const char *tok_; \
    int *old_; \
    if (DAT_00586f20[0] == 0) { \
        void *pool_ = FUN_002eb010(0x10); \
        if (pool_ != 0) pool_ = StringPool_Construct(pool_); \
        DAT_00586f20[0] = pool_; \
    } \
    tok_ = StringPool_Intern(DAT_00586f20[0], (text)); \
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

extern "C" void Gap__Bec__beNDMWMdlPlayer__vfunc_38(beNDMWMdlPlayer *arg0, PlayerArg *arg1) {
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
    w = igProperty_FindByName(arg1->props, DAT_00585be0[0], DAT_00516110)->work;
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
                    void *al2 = igObject_GetAllocator(arg0);
                    al2 = GPR_00554c14 ? al2 : Memory_GetAllocatorBySelector(DAT_00587110[0]);
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
