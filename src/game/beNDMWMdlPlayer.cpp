#include "dw4/reflected.h"
#include "dw4/igSmartPointer.h"

/* beNDMWMdlPlayer: the model controller of the player's Digimon. It overrides the beModelCtrl
 * slots that resolve its managers, register it as a PLAYER receiver, drive the pad (turn attacks,
 * guard, the panel and lobby buttons), wait for a combo step to finish, create the player's info
 * work on GENERATE and close the status panel when control, freeze, erase or remove arrive. */

extern "C" int Gap__Core__igObject__vfunc_23(...);
extern "C" int igInsightCore_FindManager(int, int);
extern "C" void *StringPool_Allocate(...);
extern "C" igIntList *igIntList_Create(int);
extern "C" int Matrix44_Invert(void *, void *, int);
extern "C" int Vec3f_TransformDirection(void *, void *, void *);
extern "C" void beModelCtrl__OnGenerate(...);
extern "C" int strcmp(...);
extern "C" int memset(...);
extern "C" void sprintf(char *, const char *, int);
extern "C" float atan2f(float, float);
extern "C" int __divdi3(long long, int);
extern "C" int igMatrix44f_SetIdentity(...);
extern "C" void Matrix44_Copy(...);
extern "C" int Memory_GetAllocatorBySelector(...);
extern "C" int igObject_GetAllocator(...);
extern "C" int igNamedObject_SetName(void *, void *);
extern "C" void List_Reserve(...);
extern "C" void List_Resize(...);
extern "C" void StringChunk_ReleaseHeader(...);
extern "C" void *StringPool_Construct(...);
extern "C" const char *StringPool_Intern(...);
extern "C" igObject *beBaseInfoDataList_Create(...);
extern "C" int beBaseInfoRam_StartTimer(void *, void *, int);
extern "C" int beBaseInfoRam_IsTimerExpired(void *, void *);
extern "C" bePadData *bePadManager_GetPadForPlayer(...);
extern "C" void *beModelCtrlHITBOX_Create(void *);
extern "C" int beModelCtrlSubCom_AddHitBox(int, void *, int, int);
extern "C" int beModelCtrlInfoWork_SetSeqLabel(void *, void *, void *, void *, void *);
extern "C" int beModelCtrl_RunCommands(...);
extern "C" igObject *beNDMWMdlPlayerInfoWork_Create(int);
extern "C" void *PanelCloseSeqList_GetMetaEnum(void);
extern "C" void beMessenger_RegisterReceiverFromInfo(int, int, char *);
extern "C" int beMessenger_AppendInt(...);
extern "C" int beMessenger_AppendObject(int, void *);
extern "C" int beMessenger_AppendString(...);
extern "C" void beMessenger_AppendMatrix(...);
extern "C" void beMessenger_AppendFloat(int, float);
extern "C" void beMessenger_AppendVec3(int, int *);
extern "C" void beMessenger_AppendBool(int, int);
extern "C" int beMessenger_DispatchSelected(...);
extern "C" int beMessenger_GetBool(...);
extern "C" int beMessenger_GetBoolCount(...);
extern "C" void *beMessenger_GetString(int, int);
extern "C" int beMessenger_GetObject(...);
extern "C" int beMessenger_GetVec3Count(...);
extern "C" int beMessenger_GetMatrixCount(...);
extern "C" void beMessenger_GetMatrix(...);
extern "C" void beMessenger_PushArgContext(...);
extern "C" void beMessenger_PopArgContext(...);
extern "C" int beMessenger_SelectGroup(...);
extern "C" int beMessenger_SelectReceivers(...);
extern "C" int beMessenger_SendNamed(...);
extern "C" void beMessenger_SendDelayedNamed(...);
extern "C" int beMessenger_SetRunCheck(int, int);

extern "C" int g_bePadManager_metaObject[4];
extern "C" int g_beNDMWGameRam_metaObject[4];
extern "C" int g_igViewerSceneInfoManager_metaObject[4];
extern "C" int g_beNDMWMdlPlayer_metaObject[4];
extern "C" int g_propertyNameField[4];
extern "C" int g_defaultAllocatorSelector[4];
extern "C" int g_stringPool[4];
extern "C" unsigned char g_useOwnerAllocator;
extern "C" int emptyString[4];
extern "C" int g_vec3ZAxis[4];

/* Turn attacks: the stick direction (1..15) picks one of eight timers, -1 for none. */
extern "C" int g_stickTurnAttackSlot[4];
extern "C" int g_turnAttackTimerStart[4];
/* "SQ_DLTM01".."SQ_DLTM13": the status panel's attack-delay sequence, by ATTACKDELAY level. */
extern "C" int g_attackDelaySeqNames[4];
extern "C" int g_upDataInitial[4];
extern "C" int g_downDataInitial[4];
extern "C" unsigned char g_baseIsUseInitial;
/* The default names of players 1 to 4. */
extern "C" int g_defaultPlayerNames[4];
/* Dungeon stages on which the player is told SETMETAL. */
extern "C" int g_metalStageNames[4];
extern "C" int g_mainLobbyStageNames[4];
/* "SQ_ENTR1P".."SQ_ENTR4P". */
extern "C" int g_playerEntrySeqNames[4];

extern "C" int KIND_PLAYER[4];
extern "C" char PLAYER_4[];
extern "C" int ONE_4[4];
extern "C" int SQ_JUMP[4];
extern "C" int SQ_GUARD[4];
extern "C" int SQ_FALL_2[4];
extern "C" int SQ_ATCK1[4];
extern "C" int SQ_ATCK2[4];
extern "C" int SQ_ATCK3[4];
extern "C" int SQ_ITEM[4];
extern "C" int SQ_WAZA[4];
extern "C" int SQ_WAIT_3[4];
extern "C" int NDMWPANEL[4];
extern "C" int ISCHECK[4];
extern "C" int GENEEMGHEAL[4];
extern "C" int SOUND_3[4];
extern "C" int CURSOR_NG[4];
extern "C" int PLAY_2[4];
extern "C" int GENERATEITEM[4];
extern "C" int GENERATEWAZA[4];
extern "C" int GENERATESTAT[4];
extern "C" int Set_2[4];
extern "C" int DROPITEM[4];
extern "C" int ACTION1[4];
extern "C" int ATDELAY[4];
extern "C" int ATTACKDELAY_2[4];
extern "C" int MODELCTRL_8[4];
extern "C" int i_stpnl05[4];
extern "C" int ISRUN_4[4];
extern "C" int SUBWND[4];
extern "C" int STATUS[4];
extern "C" int GENERATE_6[4];
extern "C" int Atck01[4];
extern "C" int Atck02[4];
extern "C" int Atck03[4];
extern "C" int ACTION_3[4];
extern "C" int ISCOMEND_2[4];
extern "C" int PLAYERPOINT_3[4];
extern "C" int GETMATRIX_3[4];
extern "C" int GAMERAM_8[4];
extern "C" int GETPLAYER_5[4];
extern "C" int HP_4[4];
extern "C" int MHP_3[4];
extern "C" int MMP_3[4];
extern "C" int MP_4[4];
extern "C" int UPDATA_2[4];
extern "C" int DOWNDATA_2[4];
extern "C" int ISUSE_6[4];
extern "C" int GAMESTART_4[4];
extern "C" int BASE_ISUSE_3[4];
extern "C" int POWERSOCKETNAME_2[4];
extern "C" int PLAYERARMS[4];
extern "C" int RECALCPLAYER_3[4];
extern "C" int NUMBERCTRL_2[4];
extern "C" int lvnm_2[4];
extern "C" int LEVEL_6[4];
extern "C" int SETVALUE_2[4];
extern "C" int METERCTRL_2[4];
extern "C" int hpmt_2[4];
extern "C" int SETPERCENT_2[4];
extern "C" int hpnm_2[4];
extern "C" int mpmt_2[4];
extern "C" int mpnm_2[4];
extern "C" int SETMETAL[4];
extern "C" int REMOVE_3[4];
extern "C" char i_pcnumic[];
extern "C" char SQ_OPENP_d[];
extern "C" char SETEFFECT_2[];
extern "C" int g_000bcaps[4];
extern "C" int BKCHIPBITEXP[4];

/* Property records: the value sits after the record's 12-byte header. */
struct PropIntRecord { int header[3]; int value; };
struct PropByteRecord { int header[3]; unsigned char value; };
struct PropIntListRecord { int header[3]; igIntList *value; };
struct PropByteListRecord { int header[3]; igUnsignedCharList *value; };
struct PropStringListRecord { int header[3]; igStringObjList *value; };
extern "C" beModelCtrlInfoRamData *igProperty_FindByName(...);
extern "C" PropIntRecord *igProperty_GetRecord(...);
extern "C" PropByteRecord *igProperty_GetRecordByte(...);
extern "C" PropIntListRecord *igProperty_GetRecordIntList(...);
extern "C" PropByteListRecord *igProperty_GetRecordArray(...);
extern "C" PropStringListRecord *igProperty_GetRecordStringList(...);

struct igResult { int w0; igResult() {} igResult(const igResult &o) { w0 = o.w0; } bool operator==(const igResult &o) const { return w0 == o.w0; } };
extern "C" igResult igMetaEnum_GetValueByName(void *, int, int *);
extern "C" igResult g_statusSucceeded;
extern "C" void beNDMWMdlPEBase_OnSequenceChange(void *, beBaseInfoRam *);

extern "C" void beNDMWMdlPlayer__ResolveManagers(beNDMWMdlPlayer *self);
extern "C" int beNDMWMdlPlayer__IsKind(int self, int kind);
extern "C" void beNDMWMdlPlayer__RegisterReceiver(beNDMWMdlPlayer *self, int info, char *unused);
extern "C" void beNDMWMdlPlayer__UpdateControl(beNDMWMdlPlayer *self, beBaseInfoRam *ram);
extern "C" void beNDMWMdlPlayer__UpdateWaitCheck(beNDMWMdlPlayer *self, beBaseInfoRam *ram);
extern "C" void beNDMWMdlPlayer__OnGenerate(beNDMWMdlPlayer *self, beBaseInfoRam *ram);
extern "C" void beNDMWMdlPlayer__OnControlOff(beNDMWMdlPlayer *self, beBaseInfoRam *ram);
extern "C" void beNDMWMdlPlayer__OnFreeze(beNDMWMdlPlayer *self, beBaseInfoRam *ram);
extern "C" void beNDMWMdlPlayer__OnSequenceChange(beNDMWMdlPlayer *self, beBaseInfoRam *ram);
extern "C" void beNDMWMdlPlayer__OnErase(beNDMWMdlPlayer *self, beBaseInfoRam *ram);
extern "C" void beNDMWMdlPlayer__OnRemove(beNDMWMdlPlayer *self, beBaseInfoRam *ram);
extern "C" int beNDMWMdlPlayer__GetMeta(void);

/* Intern `text` through the global string pool and make it the work's key event name. */
#define SET_KEY_EVENT(work, text) { \
    const char *tok_; \
    int *old_; \
    if (((void * *)g_stringPool)[0] == 0) { \
        void *pool_ = StringPool_Allocate(0x10); \
        if (pool_ != 0) pool_ = StringPool_Construct(pool_); \
        ((void * *)g_stringPool)[0] = pool_; \
    } \
    tok_ = StringPool_Intern(((void * *)g_stringPool)[0], (text)); \
    old_ = (int *)(work)->_keyEventName; \
    if (old_ != 0) { \
        int *hdr_ = old_ - 2; \
        int n_ = old_[-1] - 1; \
        old_[-1] = n_; \
        if (n_ == 0) StringChunk_ReleaseHeader(*hdr_, hdr_); \
    } \
    (work)->_keyEventName = (int)tok_; }

/* Ask this player's panel to open `request` for the work; a reply marks the panel open. */
#define OPEN_PANEL(messenger, ram, work, request) { \
    beMessenger_SelectReceivers((messenger), NDMWPANEL, 0, (ram)->_ramNo); \
    beMessenger_AppendObject((messenger), (work)); \
    beMessenger_DispatchSelected((messenger), (request)); \
    if (beMessenger_GetBoolCount((messenger)) != 0) (work)->_isPanel = 1; }

static inline void ReleaseObject(igObject *object) {
    if (object) {
        --object->_refCount;
        if (((unsigned long long)(long long)object->_refCount & 0x7fffffULL) == 0)
            igObject_Destroy(object);
    }
}

/* Owning stack reference to the hit box the main lobby builds on the 0x4000 button. */
struct HitBoxRef {
    beModelCtrlHITBOX *p;
    HitBoxRef(beModelCtrlHITBOX *x) { p = x; }
    ~HitBoxRef() { igObject *o = (igObject *)p; if (o != 0) { o->_refCount = o->_refCount - 1; if ((o->_refCount & 0x7fffff) == 0) igObject_Destroy(o); } }
};
/* Owning stack reference to the new player info work. */
class InfoWorkRef {
public:
    igObject *p;
    InfoWorkRef(igObject *o) : p(o) {}
    ~InfoWorkRef() { igObject *o = p; if (o != 0) { --o->_refCount; if ((o->_refCount & 0x7fffff) == 0) igObject_Destroy(o); } }
};
/* Owning stack reference to the new turn-attack timer list. */
class IntListRef {
public:
    igIntList *p;
    IntListRef(igIntList *l) : p(l) {}
    ~IntListRef() { igIntList *o = p; if (o != 0) { --o->_refCount; if ((o->_refCount & 0x7fffff) == 0) igObject_Destroy(o); } }
};
/* Owning stack reference to a pooled string token (reference count at p[-1], chunk header at
 * p[-2]). */
class StringRef {
public:
    int *p;
    StringRef(int *s) : p(s) {}
    ~StringRef() { if (p) { int *h = (int *)p - 2; int r = ((int *)p)[-1] - 1; ((int *)p)[-1] = r; if (r == 0) StringChunk_ReleaseHeader(*h, h); } }
};
extern "C" StringRef StringList_CopyRetained(igStringObjList *, int);

/* matching construct: slot order.  HitBoxRef (slot 252) is a block local of the caller; the locals of a
 * static inline member are allocated below the caller's, and `list` (244) must sit under the view-transform
 * result (248), which is therefore a by-reference temporary (Scratch).  Found by trial (no permuter). */
struct Scratch { int w; Scratch() { } };
struct Locals {
    static inline void CreateDataList(beBaseInfoRam *ram) {
        void *alloc;
        igObject *created;
        igObject *old;
        alloc = ((void *)igObject_GetAllocator(ram));
        alloc = g_useOwnerAllocator ? alloc : ((void *)Memory_GetAllocatorBySelector(g_defaultAllocatorSelector[0]));
        {
            igSmartPointer<igObject> list(beBaseInfoDataList_Create(alloc));
            created = list.p;
            if (created != 0) created->_refCount = created->_refCount + 1;
            old = (igObject *)ram->_dataList;
            if (old != 0) {
                old->_refCount = old->_refCount - 1;
                if ((old->_refCount & 0x7FFFFF) == 0) igObject_Destroy(old);
            }
            ram->_dataList = (int)created;
        }
    }
    static inline void Project(void *matrix, int view, const Scratch &result) {
        Matrix44_Invert((void *)&result, matrix, view);
    }
};
/* matching construct: the new list is a temporary bound to the setter's reference parameter (it
 * takes the stack slot below the named references, as retail's +0x100 does) */
struct Slot { static inline void setDataList(beBaseInfoRam *ram, const igSmartPointer<igObject> &r) {
    igObject *t = r.p;
    if (t != 0) t->_refCount = t->_refCount + 1;
    ReleaseObject((igObject *)ram->_dataList);
    ram->_dataList = (int)t;
}
static inline void adopt(beBaseInfoRam *ram, igObject *created) { igSmartPointer<igObject> list(created); setDataList(ram, list); }
};

/* matching construct: dummy-virtual view; the 33 fillers put vfunc_33 at beModelCtrl::vfunc_33,
 * the message handler. */
struct MdlPlayerSlots { virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void vfunc_33(beBaseInfoRam *, void *);};

void beNDMWMdlPlayer__ResolveManagers(beNDMWMdlPlayer *self) {
    Gap__Core__igObject__vfunc_23();
    self->_gameRam = igInsightCore_FindManager(self->_insight, g_beNDMWGameRam_metaObject[0]);
    self->_padManager = igInsightCore_FindManager(self->_insight, g_bePadManager_metaObject[0]);
    self->_viewerSIManager = igInsightCore_FindManager(self->_insight, g_igViewerSceneInfoManager_metaObject[0]);
}

int beNDMWMdlPlayer__IsKind(int self, int kind) {
    return strcmp(kind, &KIND_PLAYER[0]) == 0;
}

void beNDMWMdlPlayer__RegisterReceiver(beNDMWMdlPlayer *self, int info, char *unused)
{
    beMessenger_RegisterReceiverFromInfo(self->_messenger, info, PLAYER_4);
}

void beNDMWMdlPlayer__UpdateControl(beNDMWMdlPlayer *self, beBaseInfoRam *ram) {
    beNDMWMdlPlayerInfoWork *work;
    bePadData *pad;
    float stickX, stickY;
    int stickDir;
    int pressed, held;
    unsigned char handled;
    bool turnTimersFull;
    int messenger;
    float cameraMatrix[18];
    float cameraForward[3];

    if (ram->_dataList == 0) Locals::CreateDataList(ram);
    work = (beNDMWMdlPlayerInfoWork *)igProperty_FindByName(ram->_dataList, g_propertyNameField[0], ONE_4)->_work;
    pad = bePadManager_GetPadForPlayer(self->_padManager, ram->_ramNo);
    stickDir = pad->_lStk;
    stickX = *(float *)&pad->_LStick[0];
    stickY = *(float *)&pad->_LStick[1];
    turnTimersFull = 0;
    if (stickDir != 0) {
        int slot;
        igIntList *timers;
        int running;
        int i;
        timers = (igIntList *)work->_turnAtkTimer;
        slot = g_stickTurnAttackSlot[stickDir];
        if (slot != -1) {
            int count = timers->_count;
            if (count != 0 && slot >= 0 && slot < count) ((int *)timers->_data)[slot] = g_turnAttackTimerStart[0];
        }
        running = 0;
        for (i = 0; i < 8; i++) {
            int left = ((int *)timers->_data)[i];
            if (left > 0) {
                int next = left - 1;
                if (timers->_count != 0 && i >= 0 && i < timers->_count) ((int *)timers->_data)[i] = next;
                running++;
            }
        }
        if (running >= 8) turnTimersFull = 1;
        igMatrix44f_SetIdentity(cameraMatrix);
        Locals::Project(cameraMatrix, (int)&((igViewerParameters *)((igViewerSceneInfoManager *)self->_viewerSIManager)->_parameters)->_viewMatrix, Scratch());
        Vec3f_TransformDirection(cameraForward, g_vec3ZAxis, cameraMatrix);
        {
            float cameraYaw = atan2f(cameraForward[0], cameraForward[2]);
            *(float *)&work->_targetDirection[1] = cameraYaw + atan2f(stickX, -stickY);
        }
        work->_keyInput = 1;
    } else {
        work->_keyInput = 0;
    }
    pressed = pad->_trigger;
    held = pad->_button;
    if (work->_isMainLobby == 0) {
        if (strcmp(work->_seqCodeName, SQ_JUMP) != 0 && (pressed & 0x8000)) {
            SET_KEY_EVENT(work, SQ_GUARD)
        }
        if (held & 0x8000) {
            float t = work->_bodyAtkTimer;
            if (!(t <= 0.0f)) {
                float n = t - ((beSystem *)self->_system)->_frameTimeF;
                if (!(n < 0.0f)) work->_bodyAtkTimer = n;
                else work->_bodyAtkTimer = 0.0f;
            }
            switch (work->_bodyAtkSt0) {
            case 0:
                if (work->_keyInput == 0) work->_bodyAtkSt0 = 1;
                break;
            case 1:
                if (work->_keyInput == 1) {
                    work->_bodyAtkTimer = 15.0f;
                    work->_bodyAtkPad = stickDir;
                    work->_bodyAtkSt0 = 2;
                }
                break;
            case 2:
                if (work->_bodyAtkTimer == 0.0f) work->_bodyAtkSt0 = 0;
                else if (work->_keyInput == 0) work->_bodyAtkSt0 = 3;
                break;
            case 3:
                if (work->_bodyAtkTimer == 0.0f) {
                    work->_bodyAtkSt0 = 0;
                } else if (work->_keyInput != 0) {
                    if (stickDir == work->_bodyAtkPad && strcmp(work->_seqCodeName, SQ_JUMP) != 0 && strcmp(work->_seqCodeName, SQ_FALL_2) != 0) {
                        SET_KEY_EVENT(work, SQ_ATCK3)
                        work->_ctrlSt0 = 0;
                        work->_ctrlSt1 = 0;
                    }
                    work->_bodyAtkSt0 = 0;
                }
                break;
            }
        } else {
            work->_bodyAtkSt0 = 0;
        }
    }
    if (strcmp(work->_seqCodeName, SQ_JUMP) != 0 && strcmp(work->_seqCodeName, SQ_FALL_2) != 0) {
        unsigned char panelOpen = work->_isPanel;
        if (panelOpen != 0) {
            handled = 0;
            beMessenger_SendNamed(self->_messenger, NDMWPANEL, 0, ram->_ramNo, ISCHECK);
            messenger = self->_messenger;
            if (beMessenger_GetBoolCount(messenger) == 0 || !(unsigned char)beMessenger_GetBool(self->_messenger, 0)) {
                work->_isPanel = 0;
            } else if (beMessenger_GetBool(self->_messenger, 2) != 0) {
                if (beMessenger_GetBool(self->_messenger, 1) != 0) {
                    SET_KEY_EVENT(work, SQ_ITEM)
                } else {
                    beModelCtrlInfoWork_SetSeqLabel(self, ram, work, SQ_WAZA, beMessenger_GetString(self->_messenger, 0));
                    SET_KEY_EVENT(work, SQ_WAZA)
                }
                handled = 1;
            }
            if (!(handled & 0xFF)) {
                if (pressed & 0x2000) {
                    SET_KEY_EVENT(work, SQ_JUMP)
                    return;
                }
                if (pressed & 0x1000) {
                    OPEN_PANEL(self->_messenger, ram, work, GENEEMGHEAL)
                } else if (work->_keyInput == 0 && !(held & ~8) && (pressed & 8)) {
                    beMessenger_SelectGroup(self->_messenger, SOUND_3);
                    beMessenger_AppendString(self->_messenger, CURSOR_NG);
                    beMessenger_DispatchSelected(self->_messenger, PLAY_2);
                }
            }
        } else {
            if (pressed & 0x2000) {
                SET_KEY_EVENT(work, SQ_JUMP)
                return;
            }
            if (pressed & 0x1000) {
                OPEN_PANEL(self->_messenger, ram, work, GENEEMGHEAL)
            } else if ((pressed & 0x400) && !(panelOpen & 0xFF)) {
                OPEN_PANEL(self->_messenger, ram, work, GENERATEITEM)
            } else if ((pressed & 0x800) && !(panelOpen & 0xFF)) {
                OPEN_PANEL(self->_messenger, ram, work, GENERATEWAZA)
            } else if ((pressed & 0x200) && !(panelOpen & 0xFF)) {
                OPEN_PANEL(self->_messenger, ram, work, GENERATESTAT)
            } else if (pressed & 0x4000) {
                if (work->_isMainLobby != 0) {
                    beModelCtrlHITBOX *box;
                    void *alloc = ((void *)igObject_GetAllocator(self));
                    alloc = g_useOwnerAllocator ? alloc : ((void *)Memory_GetAllocatorBySelector(g_defaultAllocatorSelector[0]));
                    {
                        HitBoxRef hitBox((beModelCtrlHITBOX *)beModelCtrlHITBOX_Create(alloc));
                        igNamedObject_SetName((void *)hitBox.p, Set_2);
                        hitBox.p->_kind = 60000;
                        hitBox.p->_start = 1.0f;
                        hitBox.p->_length = 1.0f;
                        box = hitBox.p;
                        box->_offset[0] = 0.0f;
                        box->_offset[1] = 4.0f;
                        box->_offset[2] = 7.0f;
                        box = hitBox.p;
                        box->_boxSize[0] = 3.0f;
                        box->_boxSize[1] = 3.0f;
                        box->_boxSize[2] = 3.0f;
                        beModelCtrlSubCom_AddHitBox(work->_subCommand, (void *)hitBox.p, 0x3F800000, 60000);
                    }
                } else {
                    beMessenger_SelectGroup(self->_messenger, DROPITEM);
                    beMessenger_AppendInt(self->_messenger, ram->_ramNo);
                    beMessenger_SetRunCheck(self->_messenger, 1);
                    beMessenger_DispatchSelected(self->_messenger, ACTION1);
                    if (beMessenger_GetBoolCount(self->_messenger) == 0 && beBaseInfoRam_IsTimerExpired(ram, ATDELAY) != 0) {
                        int delay;
                        int delayStep;
                        if (turnTimersFull) {
                            igIntList *timers;
                            SET_KEY_EVENT(work, SQ_ATCK2)
                            timers = (igIntList *)work->_turnAtkTimer;
                            if (timers->_count != 0) memset((void *)timers->_data, 0, timers->_count * 4);
                        } else {
                            SET_KEY_EVENT(work, SQ_ATCK1)
                        }
                        delay = igProperty_GetRecord(((int *)((igIntList *)((beNDMWGameRam *)self->_gameRam)->_playerDataListList)->_data)[ram->_ramNo], ATTACKDELAY_2)->value;
                        beBaseInfoRam_StartTimer(ram, ATDELAY, __divdi3((long long)delay * 1000000000, 60));
                        delayStep = (delay - 22) / 4;
                        beMessenger_SendNamed(self->_messenger, MODELCTRL_8, i_stpnl05, ram->_ramNo, (void *)g_attackDelaySeqNames[delayStep]);
                    }
                }
            } else if (work->_keyInput == 0 && !(held & ~8) && (pressed & 8)) {
                beMessenger_SendNamed(self->_messenger, NDMWPANEL, 0, -1, ISRUN_4);
                if (beMessenger_GetBoolCount(self->_messenger) != 0 && (unsigned char)beMessenger_GetBool(self->_messenger, 0) == 1) {
                    beMessenger_SelectGroup(self->_messenger, SOUND_3);
                    beMessenger_AppendString(self->_messenger, CURSOR_NG);
                    beMessenger_DispatchSelected(self->_messenger, PLAY_2);
                    return;
                }
                beMessenger_SelectReceivers(self->_messenger, SUBWND, 0, 0);
                beMessenger_AppendInt(self->_messenger, ram->_ramNo);
                beMessenger_AppendString(self->_messenger, STATUS);
                beMessenger_DispatchSelected(self->_messenger, GENERATE_6);
            }
        }
    }
}

/* Finish the pending wait check: clear the work's wait-check name to the pool's empty token. */
#define CLEAR_WAIT_CHECK(work, token, old) { \
    if (g_stringPool[0] == 0) { \
        int pool = ((int)StringPool_Allocate(16)); \
        if (pool != 0) pool = ((int)StringPool_Construct(pool)); \
        g_stringPool[0] = pool; \
    } \
    token = ((int *)StringPool_Intern(g_stringPool[0], 0)); \
    old = (int *)(work)->_wCheckName; \
    if (old != 0) { \
        int *hdr = old - 2; \
        int refs = old[-1] - 1; \
        old[-1] = refs; \
        if (refs == 0) StringChunk_ReleaseHeader(*hdr, hdr); \
    } \
    (work)->_wCheckName = (int)token; }

void beNDMWMdlPlayer__UpdateWaitCheck(beNDMWMdlPlayer *self, beBaseInfoRam *ram) {
    igObject *created;
    beBaseInfo *info;
    beNDMWMdlPlayerInfoWork *work;
    int held;
    /* matching construct: separate per-arm token/old locals, declared in this order, fix register allocation */
    int *token1;
    int *token2;
    int *token3;
    int *old1;
    int *old2;
    int *old3;
    int *infoName;
    int ramNo;
    info = (beBaseInfo *)ram->_parentInfo;
    if (ram->_dataList == 0) {
        int owner = igObject_GetAllocator(ram);
        int alloc;
        if (g_useOwnerAllocator != 0) {
            alloc = owner;
        } else {
            alloc = Memory_GetAllocatorBySelector(g_defaultAllocatorSelector[0]);
        }
        igSmartPointer<igObject> list(beBaseInfoDataList_Create(alloc));
        created = list.p;
        if (created != 0) {
            created->_refCount++;
        }
        ReleaseObject((igObject *)ram->_dataList);
        ram->_dataList = (int)created;
    }
    work = (beNDMWMdlPlayerInfoWork *)igProperty_FindByName((void *)ram->_dataList, g_propertyNameField[0], ONE_4)->_work;
    held = 0;
    if (work->_isOnCtrl != 0) {
        held = bePadManager_GetPadForPlayer(self->_padManager, ram->_ramNo)->_button;
    }
    if (strcmp(work->_wCheckName, Atck01) == 0) {
        switch (work->_wCheckSt) {
        case 0:
            work->_wCheckMode = 0;
            work->_wCheckSt = 1;
        case 1:
            if (!(held & 0x4000)) {
                work->_wCheckMode = 1;
            }
            infoName = (int *)info->_name;
            ramNo = ram->_ramNo;
            infoName = infoName ? infoName : emptyString;
            beMessenger_SendNamed(self->_messenger, ACTION_3, infoName, ramNo, ISCOMEND_2);
            if (beMessenger_GetBool(self->_messenger, 0) != 0) {
                CLEAR_WAIT_CHECK(work, token1, old1)
                work->_wCheckSt = 0;
                if (work->_wCheckMode == 0) {
                    beModelCtrl_RunCommands(self, info, ram, work);
                    return;
                }
                ((MdlPlayerSlots *)self)->vfunc_33(ram, SQ_WAIT_3);
                return;
            }
            break;
        }
    } else if (strcmp(work->_wCheckName, Atck02) == 0) {
        if (!(held & 0x4000)) {
            ((MdlPlayerSlots *)self)->vfunc_33(ram, SQ_WAIT_3);
        }
        infoName = (int *)info->_name;
        ramNo = ram->_ramNo;
        infoName = infoName ? infoName : emptyString;
        beMessenger_SendNamed(self->_messenger, ACTION_3, infoName, ramNo, ISCOMEND_2);
        if (beMessenger_GetBool(self->_messenger, 0) != 0) {
            CLEAR_WAIT_CHECK(work, token2, old2)
            beModelCtrl_RunCommands(self, info, ram, work);
        }
    } else if (strcmp(work->_wCheckName, Atck03) == 0 && !(held & 0x4000)) {
        CLEAR_WAIT_CHECK(work, token3, old3)
        beModelCtrl_RunCommands(self, info, ram, work);
    }
}

void beNDMWMdlPlayer__OnGenerate(beNDMWMdlPlayer *self, beBaseInfoRam *ram) {
    float startMatrix[16];
    float pointMatrix[16];
    beBaseInfo *info;
    beModelCtrlInfoRamData *record;
    beNDMWMdlPlayerInfoWork *work;
    igObject *created;
    igIntList *timers;
    info = (beBaseInfo *)ram->_parentInfo;
    if (ram->_dataList == 0) {
        int owner = igObject_GetAllocator(ram);
        int alloc;
        if (g_useOwnerAllocator != 0) {
            alloc = owner;
        } else {
            alloc = Memory_GetAllocatorBySelector(g_defaultAllocatorSelector[0]);
        }
        Slot::adopt(ram, beBaseInfoDataList_Create(alloc));
    }
    record = igProperty_FindByName((void *)ram->_dataList, g_propertyNameField[0], ONE_4);
    {
        int owner = igObject_GetAllocator(self);
        int alloc;
        if (g_useOwnerAllocator != 0) {
            alloc = owner;
        } else {
            alloc = Memory_GetAllocatorBySelector(g_defaultAllocatorSelector[0]);
        }
        InfoWorkRef newWork(beNDMWMdlPlayerInfoWork_Create(alloc));
        created = newWork.p;
        if (created != 0) {
            created->_refCount++;
        }
        ReleaseObject((igObject *)record->_work);
        record->_work = (int)created;
        work = (beNDMWMdlPlayerInfoWork *)newWork.p;
        work->_isPlayer = 1;
        work->_directionLimiter[0] = 0.0f;
        work->_directionLimiter[1] = 7.0f;
        work->_directionLimiter[2] = 0.0f;
        {
            int owner = igObject_GetAllocator(self);
            int alloc;
            if (g_useOwnerAllocator != 0) {
                alloc = owner;
            } else {
                alloc = Memory_GetAllocatorBySelector(g_defaultAllocatorSelector[0]);
            }
            IntListRef newTimers(igIntList_Create(alloc));
            {
                igIntList *t = newTimers.p;
                if (t->_count < 9) {
                    List_Reserve(t, 8, 4);
                }
            }
            {
                igIntList *t = newTimers.p;
                if (t->_capacity >= 8) {
                    t->_count = 8;
                } else {
                    List_Resize(t, 8, 4);
                }
            }
            timers = newTimers.p;
            if (timers->_count != 0) {
                memset((void *)timers->_data, 0, timers->_count * 4);
            }
            timers = newTimers.p;
            if (timers != 0) {
                timers->_refCount++;
            }
            ReleaseObject((igObject *)work->_turnAtkTimer);
            work->_turnAtkTimer = (int)timers;
        }
    }
    if (beMessenger_GetVec3Count(self->_messenger) == 0 && beMessenger_GetMatrixCount(self->_messenger) == 0) {
        igMatrix44f_SetIdentity(startMatrix);
        beMessenger_PushArgContext(self->_messenger);
        beMessenger_SelectGroup(self->_messenger, PLAYERPOINT_3);
        beMessenger_AppendInt(self->_messenger, 0);
        beMessenger_AppendInt(self->_messenger, ram->_ramNo);
        beMessenger_DispatchSelected(self->_messenger, GETMATRIX_3);
        if (beMessenger_GetMatrixCount(self->_messenger) != 0) {
            beMessenger_GetMatrix(pointMatrix, self->_messenger, 0);
            Matrix44_Copy(startMatrix, pointMatrix);
        }
        beMessenger_PopArgContext(self->_messenger);
        beMessenger_AppendMatrix(self->_messenger, startMatrix);
    }
    beModelCtrl__OnGenerate(self, ram);
    beMessenger_SelectGroup(self->_messenger, GAMERAM_8);
    beMessenger_AppendInt(self->_messenger, ram->_ramNo);
    beMessenger_DispatchSelected(self->_messenger, GETPLAYER_5);
    int player = beMessenger_GetObject(self->_messenger, 0);
    {
        PropIntRecord *hp = igProperty_GetRecord(player, HP_4);
        if (hp != 0) ((igObject *)hp)->_refCount++;
        ReleaseObject((igObject *)work->_hp);
        work->_hp = (int)hp;
    }
    {
        PropIntRecord *maxHp = igProperty_GetRecord(player, MHP_3);
        if (maxHp != 0) ((igObject *)maxHp)->_refCount++;
        ReleaseObject((igObject *)work->_mHp);
        work->_mHp = (int)maxHp;
    }
    if (((PropIntRecord *)work->_hp)->value == 0) {
        int full = igProperty_GetRecord(player, MHP_3)->value;
        igProperty_GetRecord(player, HP_4)->value = full;
        full = igProperty_GetRecord(player, MMP_3)->value;
        igProperty_GetRecord(player, MP_4)->value = full;
    }
    {
        int i = 0, off = 0;
        do {
            igIntList *list = igProperty_GetRecordIntList(player, UPDATA_2)->value;
            if (list->_count != 0 && i >= 0 && i < list->_count) {
                *(int *)(list->_data + off) /* matching construct: byte-offset element write; indexing by i or off/4 changes the induction variable */ = g_upDataInitial[0];
            }
            i += 1;
            off += 4;
        } while (i < 7);
    }
    {
        int i = 0, off = 0;
        do {
            igIntList *list = igProperty_GetRecordIntList(player, DOWNDATA_2)->value;
            if (list->_count != 0 && i >= 0 && i < list->_count) {
                *(int *)(list->_data + off) /* matching construct: byte-offset element write; indexing by i or off/4 changes the induction variable */ = g_downDataInitial[0];
            }
            i += 1;
            off += 4;
        } while (i < 6);
    }
    if (igProperty_GetRecordByte(player, ISUSE_6)->value == 0) {
        int *infoName;
        beMessenger_SelectGroup(self->_messenger, GAMERAM_8);
        beMessenger_AppendInt(self->_messenger, ram->_ramNo);
        infoName = (int *)info->_name;
        infoName = infoName ? infoName : emptyString;
        beMessenger_AppendString(self->_messenger, infoName);
        beMessenger_AppendString(self->_messenger, g_defaultPlayerNames[ram->_ramNo]);
        beMessenger_DispatchSelected(self->_messenger, GAMESTART_4);
        igUnsignedCharList *baseUse = igProperty_GetRecordArray(player, BASE_ISUSE_3)->value;
        int n = baseUse->_count;
        unsigned char *flags = (unsigned char *)baseUse->_data;
        for (int i = 0; i < n; i++) {
            flags[i] = g_baseIsUseInitial;
        }
    }
    if (igProperty_GetRecordStringList(player, POWERSOCKETNAME_2)->value->_count != 0) {
        StringRef socket = StringList_CopyRetained(igProperty_GetRecordStringList(player, POWERSOCKETNAME_2)->value, 0);
        beMessenger_SendDelayedNamed(self->_messenger, PLAYERARMS, socket.p, ram->_ramNo, GENERATE_6, 1);
    }
    beMessenger_SelectGroup(self->_messenger, GAMERAM_8);
    beMessenger_AppendInt(self->_messenger, ram->_ramNo);
    beMessenger_DispatchSelected(self->_messenger, RECALCPLAYER_3);
    beMessenger_SelectReceivers(self->_messenger, NUMBERCTRL_2, lvnm_2, ram->_ramNo);
    beMessenger_AppendInt(self->_messenger, igProperty_GetRecord(player, LEVEL_6)->value);
    beMessenger_DispatchSelected(self->_messenger, SETVALUE_2);
    beMessenger_SelectReceivers(self->_messenger, METERCTRL_2, hpmt_2, ram->_ramNo);
    {
        int maxHp = igProperty_GetRecord(player, MHP_3)->value;
        beMessenger_AppendFloat(self->_messenger, (100.0f * (float)igProperty_GetRecord(player, HP_4)->value) / (float)maxHp);
    }
    beMessenger_DispatchSelected(self->_messenger, SETPERCENT_2);
    beMessenger_SelectReceivers(self->_messenger, NUMBERCTRL_2, hpnm_2, ram->_ramNo);
    beMessenger_AppendInt(self->_messenger, igProperty_GetRecord(player, HP_4)->value);
    beMessenger_DispatchSelected(self->_messenger, SETVALUE_2);
    beMessenger_SelectReceivers(self->_messenger, METERCTRL_2, mpmt_2, ram->_ramNo);
    {
        int mp = igProperty_GetRecord(player, MP_4)->value;
        PropIntRecord *maxMp = igProperty_GetRecord(player, MMP_3);
        beMessenger_AppendFloat(self->_messenger, (float)(mp * 100 / maxMp->value));
    }
    beMessenger_DispatchSelected(self->_messenger, SETPERCENT_2);
    beMessenger_SelectReceivers(self->_messenger, NUMBERCTRL_2, mpnm_2, ram->_ramNo);
    beMessenger_AppendInt(self->_messenger, igProperty_GetRecord(player, MP_4)->value);
    beMessenger_DispatchSelected(self->_messenger, SETVALUE_2);
    int stageName = ((beSystem *)self->_system)->_stageName;
    for (int j = 0; j < 5; j++) {
        if (strcmp(((int *)g_metalStageNames)[j], stageName) == 0) {
            beMessenger_SendNamed(self->_messenger, ((int *)PLAYER_4), 0, ram->_ramNo, SETMETAL);
            break;
        }
    }
    for (int k = 0; k < 4; k++) {
        if (strcmp(((int *)g_mainLobbyStageNames)[k], stageName) == 0) {
            work->_isMainLobby = 1;
            break;
        }
    }
}

void beNDMWMdlPlayer__OnControlOff(beNDMWMdlPlayer *self, beBaseInfoRam *ram) {
    beNDMWMdlPlayerInfoWork *work;

    if (ram->_dataList == 0) {
        int owner = igObject_GetAllocator(ram);
        igSmartPointer<igObject> list(beBaseInfoDataList_Create(g_useOwnerAllocator != 0 ? owner : Memory_GetAllocatorBySelector(g_defaultAllocatorSelector[0])));
        igObject *created = list.p;
        if (created != 0) {
            created->_refCount = created->_refCount + 1;
        }
        igObject *old = (igObject *)ram->_dataList;
        if (old != 0) {
            old->_refCount = old->_refCount - 1;
            if ((old->_refCount & 0x7FFFFF) == 0) {
                igObject_Destroy(old);
            }
        }
        ram->_dataList = (int)created;
    }
    work = (beNDMWMdlPlayerInfoWork *)igProperty_FindByName((igObject *)ram->_dataList, g_propertyNameField[0], &ONE_4[0])->_work;
    if (work->_isPanel != 0) {
        work->_isPanel = 0U;
        beMessenger_SendNamed(self->_messenger, &NDMWPANEL[0], 0, ram->_ramNo, &REMOVE_3[0]);
    }
}

void beNDMWMdlPlayer__OnFreeze(beNDMWMdlPlayer *self, beBaseInfoRam *ram) {
    igObject *created;
    if (ram->_dataList == 0) {
        int owner = igObject_GetAllocator(ram);
        int alloc;
        igObject *old;
        if (g_useOwnerAllocator != 0) {
            alloc = owner;
        } else {
            alloc = Memory_GetAllocatorBySelector(g_defaultAllocatorSelector[0]);
        }
        igSmartPointer<igObject> list(beBaseInfoDataList_Create(alloc));
        created = list.p;
        if (created != 0) {
            created->_refCount++;
        }
        old = (igObject *)ram->_dataList;
        if (old != 0) {
            --old->_refCount;
            if ((old->_refCount & 0x7fffff) == 0) igObject_Destroy(old);
        }
        ram->_dataList = (int)created;
    }
    beNDMWMdlPlayerInfoWork *work = (beNDMWMdlPlayerInfoWork *)igProperty_FindByName(ram->_dataList, g_propertyNameField[0], ONE_4)->_work;
    if (work->_isPanel != 0) {
        work->_isPanel = 0;
        beMessenger_SendNamed(self->_messenger, NDMWPANEL, 0, ram->_ramNo, REMOVE_3);
    }
}

static inline void EnsureDataList(beBaseInfoRam *ram)
{
    if (ram->_dataList == 0) {
        void *owner = ((void *)igObject_GetAllocator(ram));
        void *alloc;
        if (g_useOwnerAllocator != 0) {
            alloc = owner;
        } else {
            alloc = ((void *)Memory_GetAllocatorBySelector(g_defaultAllocatorSelector[0]));
        }
        igSmartPointer<igObject> list(beBaseInfoDataList_Create(alloc));
        igObject *created = list.p;
        if (created) created->_refCount++;
        igObject *old = (igObject *)ram->_dataList;
        if (old) {
            old->_refCount--;
            if ((old->_refCount & 0x7fffff) == 0) igObject_Destroy(old);
        }
        ram->_dataList = (int)created;
    }
}

void beNDMWMdlPlayer__OnSequenceChange(beNDMWMdlPlayer *self, beBaseInfoRam *ram)
{
    beNDMWMdlPlayerInfoWork *work;
    beBaseInfo *info = (beBaseInfo *)ram->_parentInfo;
    char seqName[24];
    int badgeOffset[3];
    int enumValue;
    EnsureDataList(ram);
    int list = ram->_dataList;
    work = (beNDMWMdlPlayerInfoWork *)igProperty_FindByName(list, g_propertyNameField[0], ((char *)ONE_4))->_work;
    if (strcmp(work->_seqCodeName, ((char *)SQ_WAIT_3)) == 0) {
        const char *infoName = (const char *)info->_name;
        int ramNo = ram->_ramNo;
        const char *receiver = infoName ? infoName : ((char *)emptyString);
        beMessenger_SelectReceivers(self->_messenger, ((char *)MODELCTRL_8), receiver, ramNo);
        beMessenger_AppendString(self->_messenger, i_pcnumic);
        sprintf(seqName, SQ_OPENP_d, ram->_ramNo);
        beMessenger_AppendString(self->_messenger, seqName);
        beMessenger_AppendFloat(self->_messenger, 480.0f);
        badgeOffset[0] = 0; badgeOffset[1] = 0x41200000; badgeOffset[2] = 0;
        beMessenger_AppendVec3(self->_messenger, badgeOffset);
        beMessenger_AppendBool(self->_messenger, 1);
        beMessenger_AppendBool(self->_messenger, 1);
        beMessenger_DispatchSelected(self->_messenger, SETEFFECT_2);
    }
    if (work->_isPanel != 0) {
        if (igMetaEnum_GetValueByName(PanelCloseSeqList_GetMetaEnum(), work->_seqCodeName, &enumValue) == g_statusSucceeded) {
            work->_isPanel = 0;
            beMessenger_SendNamed(self->_messenger, ((char *)NDMWPANEL), 0, ram->_ramNo, ((char *)REMOVE_3));
        }
    }
    beNDMWMdlPEBase_OnSequenceChange(self, ram);
}

void beNDMWMdlPlayer__OnErase(beNDMWMdlPlayer *self, beBaseInfoRam *ram) {
    igObject *created;
    beModelCtrlInfoRamData *record;
    beNDMWMdlPlayerInfoWork *work;
    if (ram->_dataList == 0) {
        int owner = igObject_GetAllocator(ram);
        int alloc;
        if (g_useOwnerAllocator != 0) {
            alloc = owner;
        } else {
            alloc = Memory_GetAllocatorBySelector(g_defaultAllocatorSelector[0]);
        }
        {
            igSmartPointer<igObject> list(beBaseInfoDataList_Create(alloc));
            created = list.p;
            if (created != 0) {
                created->_refCount++;
            }
            ReleaseObject((igObject *)ram->_dataList);
            ram->_dataList = (int)created;
        }
    }
    record = igProperty_FindByName(ram->_dataList, g_propertyNameField[0], ONE_4);
    work = (beNDMWMdlPlayerInfoWork *)record->_work;
    beMessenger_SelectReceivers(self->_messenger, MODELCTRL_8, g_000bcaps, ram->_ramNo);
    beMessenger_AppendMatrix(self->_messenger, record->_node + 32);
    beMessenger_AppendString(self->_messenger, g_playerEntrySeqNames[ram->_ramNo]);
    beMessenger_DispatchSelected(self->_messenger, GENERATE_6);
    beMessenger_SendNamed(self->_messenger, MODELCTRL_8, g_000bcaps, ram->_ramNo, ISRUN_4);
    if (beMessenger_GetBoolCount(self->_messenger) != 0 && (beMessenger_GetBool(self->_messenger, 0) & 0xff) == 1) {
        beMessenger_SelectGroup(self->_messenger, GAMERAM_8);
        beMessenger_AppendInt(self->_messenger, ram->_ramNo);
        beMessenger_DispatchSelected(self->_messenger, BKCHIPBITEXP);
    }
    if (work->_isPanel != 0) {
        work->_isPanel = 0;
        beMessenger_SendNamed(self->_messenger, NDMWPANEL, 0, ram->_ramNo, REMOVE_3);
    }
}

void beNDMWMdlPlayer__OnRemove(beNDMWMdlPlayer *self, beBaseInfoRam *ram) {
    igObject *created;
    if (((igObject *)ram->_dataList) == 0) {
        int owner = igObject_GetAllocator(ram);
        int alloc;
        if (g_useOwnerAllocator != 0) {
            alloc = owner;
        } else {
            alloc = Memory_GetAllocatorBySelector(g_defaultAllocatorSelector[0]);
        }
        igSmartPointer<igObject> list(beBaseInfoDataList_Create(alloc));
        created = list.p;
        if (created != 0) {
            created->_refCount++;
        }
        ReleaseObject(((igObject *)ram->_dataList));
        ram->_dataList = (int)created;
    }
    beNDMWMdlPlayerInfoWork *work = (beNDMWMdlPlayerInfoWork *)igProperty_FindByName(((igObject *)ram->_dataList), g_propertyNameField[0], ONE_4)->_work;
    if (work->_isPanel != 0) {
        work->_isPanel = 0;
        beMessenger_SendNamed(self->_messenger, NDMWPANEL, 0, ram->_ramNo, REMOVE_3);
    }
}

int beNDMWMdlPlayer__GetMeta(void)
{
    return g_beNDMWMdlPlayer_metaObject[0];
}
