#include "dw4/reflected.h"

extern "C" int igObject_Destroy(void *);
extern "C" void * beBaseInfoDataList_Create(...);
extern "C" int beNDMWSaveIntf_GetInfoMeta(void);
extern "C" int beNDMWSaveIntf_GetMeta(void);
extern "C" void *beNDMWSaveIntfCtrlData_Create(...);
extern "C" int beNDMWSaveIntf_GetMessageEnum(...);
extern "C" void *beNDMWLoadIntf2SelSlot_Create(...);
extern "C" void *beNDMWLoadIntf2DataSelIntf_Create(...);
extern "C" void *beNDMWLoadIntf2DegiStateCtrl_Create(...);
extern "C" void *beNDMWLoadIntf2DegiState_Create(...);
extern "C" void *beNDMWLoadIntf2MesWin_Create(...);
extern "C" void *beNDMWLoadIntf2ComMdlCtrl_Create(...);
extern "C" void *beNDMWLoadIntf2TextOrder_Create(...);
extern "C" int beNDMWLoadIntf2DegiState__Init(...);
extern "C" int Memory_GetAllocatorBySelector(...);
extern "C" int ObjectList_AppendRetained(...);
extern "C" int beMessenger_AppendInt(...);
extern "C" int beMessenger_DispatchSelected(...);
extern "C" int beMessenger_GetInt(...);
extern "C" int beMessenger_GetIntCount(...);
extern "C" void *beMessenger_GetObject(...);
extern "C" unsigned int beMessenger_ResolveEnumValue(...);
extern "C" int beMessenger_SelectGroup(...);
extern "C" int beMessenger_SendNamed(...);
extern "C" int beMessenger_SetInt(...);
extern "C" int igObject_GetAllocator(...);
extern "C" void *igProperty_FindByName(...);
/* Header of every reference-counted engine object; the count is in the low 23 bits. */
struct RefObject { int vtable; int refCount; };
extern "C" RefObject * igInsightCore_FindManager(...);
extern "C" int g_bePadManager_metaObject[4];
extern "C" void beNDMWSaveIntf_AcquirePadManager(beNDMWSaveIntf *self);
extern "C" int g_beNDMWSaveIntfInfo_metaObject[4];
extern "C" int g_beNDMWSaveIntf_metaObject[4];
extern "C" int beMessenger_RegisterReceiver(int, beBaseInfoRam *, int *, int, int);
extern "C" int beMessenger_RegisterReceiverFromInfo(int, beBaseInfoRam *, int *);
extern "C" int SAVEINTF_ALL[4];
extern "C" int SAVEINTF[4];
extern "C" void beNDMWSaveIntf_RegisterReceivers(beNDMWSaveIntf *self, beBaseInfoRam *ram);
/* The values of the save interface's Message enum (beNDMWSaveIntf_GetMessageEnum). */
enum SaveMessage {
    MSG_GENERATE = 0,
    MSG_LINKCOMMON = 1,
    MSG_ISENTRY = 2,
    MSG_ISRDY = 3,
    MSG_ONCTRL = 4,
    MSG_OFFCTRL = 5,
    MSG_SETSELECT_DATA = 6
};
/* Message record: only the enum value name at +20 is read. */
struct MessageArg { char header[20]; int enumName; };
struct ModelPlacement { float x, y, z; };
extern "C" ModelPlacement g_saveModelPlacement[4];
extern "C" int CTRL_3[4];
extern "C" int COMMDLCTRL_3[4];
extern "C" int MESWIN_2[4];
extern "C" int COMMONINTF_2[4];
extern "C" int DEGISTATECTRL_2[4];
extern "C" int GAMERAM_5[4];
extern "C" int SAVECTRL[4];
extern "C" int GETCOMMON_4[4];
extern "C" int TEXTORDER_3[4];
extern "C" int GAMEREMOVE[4];
extern "C" int g_propertyNameField[4];
extern "C" int kIGMemoryPoolHandleUser1[4];
extern "C" int g_beSystem_metaObject[4];
extern "C" int g_beLua_metaObject[4];
extern "C" unsigned char g_useOwnerAllocator;
/* Owning stack reference to a newly created child object; one instantiation per child class (0 the
 * data list, 1 the control data, 2 text order, 3 model control, 4 message window, 5 slot selector,
 * 6 state control, 7 state data, 8 data selector), so each gets its own out-of-line destructor. */
template <int kind> struct ChildRef {
    RefObject *object;
    ChildRef(RefObject *created) : object(created) {}
    ~ChildRef() { RefObject *q = object; if (q != 0) { q->refCount = q->refCount - 1; if ((q->refCount & 0x7fffff) == 0) igObject_Destroy(q); } }
};
/* Creates the info record's child list on first use; every expansion keeps its own stack reference. */
struct DataListGuard {
    static inline void Ensure(beBaseInfoRam *ram) {
    if (ram->_dataList == 0) {
        int own = igObject_GetAllocator(ram); int allocator; if (g_useOwnerAllocator != 0) { allocator = own; } else { allocator = Memory_GetAllocatorBySelector(kIGMemoryPoolHandleUser1[0]); }
        ChildRef<0> list((RefObject *)beBaseInfoDataList_Create(allocator)); RefObject *created; RefObject *old;
        created = list.object; if (created != 0) created->refCount = created->refCount + 1;
        old = (RefObject *)ram->_dataList;
        if (old != 0) { old->refCount = old->refCount - 1; if (((unsigned long long)((long long)old->refCount << 0x29) >> 0x29) == 0) igObject_Destroy(old); }
        ram->_dataList = (int)created;
    }
    }
};
struct AllocatorValue { int allocator; AllocatorValue(const AllocatorValue &o) : allocator(o.allocator) {} };
extern "C" int DataList_GetData_003e9090(...);
extern "C" void *DataList_GetWordAt_003e9240(...);
extern "C" int igDataList_GetCount(...);
extern "C" void *beNDMWLoadSlotPlayer_Create(...);
extern "C" void *beNDMWDegiData_Create(...);
extern "C" int beNDMWLoadIntf2DegiState__RequestOpen(...);
extern "C" int beNDMWLoadIntf2DegiState__RequestClose(...);
extern "C" int beNDMWLoadIntf2DegiState__RequestConfirmClose(...);
extern "C" int beNDMWLoadIntf2DegiState__Update(...);
extern "C" int beNDMWLoadIntf2DataSelIntf__Init(...);
extern "C" int beNDMWLoadIntf2DataSelIntf__ClearStatesFrom(...);
extern "C" int beNDMWLoadIntf2DataSelIntf__OpenSaveArea(...);
extern "C" int beNDMWLoadIntf2DataSelIntf__UpdateSelection(...);
extern "C" int beNDMWLoadIntf2DataSelIntf__CloseAll(...);
extern "C" int beNDMWLoadIntf2DataSelIntf__ShowSelectedStatus(...);
extern "C" int beNDMWLoadIntf2DataSelIntf__RestoreSaveArea(...);
extern "C" int beNDMWLoadIntf2DataSelIntf__CloseStatusWindows(...);
extern "C" int beNDMWLoadIntf2DataSelIntf__OpenSlotSaveArea(...);
extern "C" int beNDMWLoadIntf2DataSelIntf__OpenAreaCursor(...);
extern "C" int beNDMWLoadIntf2DataSelIntf__CloseSaveArea(...);
extern "C" int beNDMWLoadIntf2DataSelIntf__ShowAccessPlayers(...);
extern "C" int beNDMWLoadIntf2SelSlot__Reset(...);
extern "C" int beNDMWLoadIntf2SelSlot__Init(...);
extern "C" int beNDMWLoadIntf2SelSlot__Open(...);
extern "C" int beNDMWLoadIntf2SelSlot__UpdateSelection(...);
extern "C" int beNDMWLoadIntf2SelSlot__PublishCursor(...);
extern "C" int beNDMWLoadIntf2SelSlot__Close(...);
extern "C" int beNDMWLoadIntf2SelSlot__RefreshSlotMarks(...);
extern "C" int beNDMWLoadIntf2ComMdlCtrl__IsOpenQueueEmpty(...);
extern "C" int beNDMWLoadIntf2ComMdlCtrl__Close(...);
extern "C" int beNDMWLoadIntf2ComMdlCtrl__IsCloseQueueEmpty(...);
extern "C" int beNDMWLoadIntf2ComMdlCtrl__Poll(...);
extern "C" int beNDMWLoadSavePlWork__SetIsCtrl(...);
extern "C" int beNDMWLoadSavePlWork__GetIsRdy(...);
extern "C" int beNDMWLoadSavePlWork__GetIsEntry(...);
extern "C" void *DataList_FindProperty_003e9280(...);
extern "C" int ObjectRef_Get_003e92a0(...);
extern "C" AllocatorValue AllocatorValue_Make_003e9360(...);
extern "C" int ObjectRef_Get_003e93b0(...);
extern "C" int beNDMWLoadIntf2MesWin__Update(...);
extern "C" int beNDMWLoadIntf2MesWin__RequestOpen(...);
extern "C" int beNDMWLoadIntf2MesWin__RequestClose(...);
extern "C" int beNDMWLoadIntf2MesWin__RequestMessage(...);
extern "C" int beNDMWLoadIntf2MesWin__RequestQuestion(...);
extern "C" int beNDMWLoadIntf2MesWin__RequestPrompt(...);
extern "C" int beNDMWLoadIntf2MesWin__Cancel(...);
extern "C" int beNDMWLoadIntf2MesWin__GetIsCtrl(...);
extern "C" int beNDMWLoadIntf2MesWin__GetCurPoint(...);
extern "C" int beNDMWLoadIntf2MesWin__RequestMesErase(...);
extern "C" int beNDMWLoadIntf2MesWin__RequestSystemMessage(...);
extern "C" int beNDMWLoadIntf2MesWin__EndSystemMessage(...);
extern "C" int beNDMWLoadCtrl2CommonIntf__StepNoticeQuestion(...);
extern "C" int beNDMWLoadCtrl2CommonIntf__StepCheckMemoryCard(...);
extern "C" int beNDMWLoadCtrl2CommonIntf__StepCreateSaveFile(...);
extern "C" int beNDMWLoadCtrl2CommonIntf__StepReadMedia(...);
extern "C" int beNDMWLoadCtrl2CommonIntf__StepWriteSaveData(...);
extern "C" int beNDMWLoadCtrl2CommonIntf__StepFormatMemoryCard(...);
extern "C" int beNDMWLoadCtrl2CommonIntf__StartUtilFor(...);
extern "C" int beNDMWLoadCtrl2CommonIntf__RemoveAccessPlayer(...);
extern "C" int beNDMWDegiData__LoadFromProperties(...);
extern "C" int List_Resize(...);
extern "C" int Memory_SelectAllocator_003e9370(...);
extern "C" void *ObjectList_GetAt_003e9260(...);
extern "C" int beMessenger_AppendString(...);
extern "C" void *bePadManager_GetPadForPlayer(...);
extern "C" void *igProperty_GetRecordByte(...);
extern "C" int * g_playerModelRow[4];
extern "C" int SELSLOT_2[4];
extern "C" int DATASELINTF_2[4];
extern "C" int j_chrselbase_2[4];
extern "C" int SQ_OPEN_3[4];
extern "C" int GETPLAYER_3[4];
extern "C" int ISUSE_3[4];
extern "C" int CURRENT2BASE[4];
extern "C" int g_defaultPlayerName[4];
extern "C" int GAMESTART_2[4];
extern "C" int j_chrselmesswin_2[4];
extern "C" int SQ_CLOSE_5[4];
struct ReleasedObject {
    int vtable;
    int refCount;
    static void Release(ReleasedObject *object) {
        if (object) {
            --object->refCount;
            if (((unsigned long long)(long long)object->refCount & 0x7fffffULL) == 0)
                igObject_Destroy(object);
        }
    }
};
template <int kind> class CreatedRef {
public:
    void *value;
    CreatedRef(void *created) : value(created) {}
    ~CreatedRef() { ReleasedObject::Release((ReleasedObject *)value); }
};
struct AccessList {
    int vtable;
    int refCount;
    int count;
    int capacity;
    int getCount() const { return count; }
};
struct AllocatorChoice {
    static int Select(const int *selector, int own) { if (g_useOwnerAllocator) return own; else return Memory_GetAllocatorBySelector(*selector); }
};
struct ModelPos {
    float x, y, z, w;
    ModelPos(const ModelPos &o);
};
extern "C" int beNDMWLoadIntf2ComMdlCtrl__StartAt(void *, int, void *, void *, ModelPos &, int);
class NewDataListRef {
public:
    void *value;
    NewDataListRef(const AllocatorValue &source) : value(beBaseInfoDataList_Create(source.allocator)) {}
    ~NewDataListRef();
};
extern "C" int *ObjectRef_Assign_003e92b0(void *, const NewDataListRef &);
struct FreshDataList {
    static int *Assign(void *slot, int allocator) {
        NewDataListRef created(AllocatorValue_Make_003e9360(Memory_SelectAllocator_003e9370(&kIGMemoryPoolHandleUser1[0], allocator)));
        return ObjectRef_Assign_003e92b0(slot, created);
    }
};
/* bePadData::_trigger bits the save dialogue reads. */
enum PadButton {
    PAD_START = 0x0008,
    PAD_CIRCLE = 0x2000
};
/* beNDMWSaveIntfCtrlData::_st0: where one player's save dialogue stands. */
enum SaveStep {
    SAVE_OPEN = 0,
    SAVE_OPEN_WINDOW = 1,
    SAVE_ASK = 2,
    SAVE_SELECT_CARD = 4,
    SAVE_PREPARE_DATA = 5,
    SAVE_SELECT_DATA = 6,
    SAVE_ASK_CONTINUE = 7,
    SAVE_WAIT_PLAYERS = 8,
    SAVE_DONE = 9
};
/* beNDMWLoadSavePlWork::_sysStat0: what a player's work record is doing. */
enum PlayerStage {
    STAGE_DIALOGUE = 0,
    STAGE_WAIT_UTIL = 1,
    STAGE_CLOSE = 2,
    STAGE_SAVE_DATA = 3,
    STAGE_CARD_ACCESS = 4,
    STAGE_UTIL_ERROR = 6,
    STAGE_UTIL_DONE = 7,
    STAGE_RESUME = 8
};
static inline void EnterState(beNDMWSaveIntfCtrlData *c, int state) { c->_st0 = state; c->_st3 = 0; c->_st2 = 0; c->_st1 = 0; }
static inline void NextStep(beNDMWSaveIntfCtrlData *c) { c->_st1 = c->_st1 + 1; c->_st3 = 0; c->_st2 = 0; }
static inline void SetStep(beNDMWSaveIntfCtrlData *c, int step) { c->_st1 = step; c->_st3 = 0; c->_st2 = 0; }
static inline void NextSubstep(beNDMWSaveIntfCtrlData *c) { c->_st2 = c->_st2 + 1; c->_st3 = 0; }
static inline void SetSubstep(beNDMWSaveIntfCtrlData *c, int substep) { c->_st2 = substep; c->_st3 = 0; }
static inline void NextTick(beNDMWSaveIntfCtrlData *c) { c->_st3 = c->_st3 + 1; }
static inline void EnterSlotState(beNDMWLoadIntf2SelSlot *c, int state) { c->_st0 = state; c->_st3 = 0; c->_st2 = 0; c->_st1 = 0; }
static inline void EnterStage(beNDMWLoadSavePlWork *w, int stage) { w->_sysStat0 = stage; w->_sysStat3 = 0; w->_sysStat2 = 0; w->_sysStat1 = 0; }
static inline void NextStageStep(beNDMWLoadSavePlWork *w) { w->_sysStat1 = w->_sysStat1 + 1; w->_sysStat3 = 0; w->_sysStat2 = 0; }
static inline void SetStageStep(beNDMWLoadSavePlWork *w, int step) { w->_sysStat1 = step; w->_sysStat3 = 0; w->_sysStat2 = 0; }
static inline void NextStageSubstep(beNDMWLoadSavePlWork *w) { w->_sysStat2 = w->_sysStat2 + 1; w->_sysStat3 = 0; }
static inline void SetStageSubstep(beNDMWLoadSavePlWork *w, int substep) { w->_sysStat2 = substep; w->_sysStat3 = 0; }
static inline void NextStageTick(beNDMWLoadSavePlWork *w) { w->_sysStat3 = w->_sysStat3 + 1; }
static inline int TextId(const beBaseInfoRam *host, int token) { return (host->_ramNo << 0x10) | token; }
static inline int PlayerTextId(int player, int token) { return (player << 0x10) | token; }
static inline int AllEntriesReady(void *works) {
    int entryCount = 0;
    int readyCount = 0;
    int index;
    for (index = 0; index < igDataList_GetCount(works); index++) {
        if ((beNDMWLoadSavePlWork__GetIsEntry(DataList_GetWordAt_003e9240(works, index)) & 0xFF) == 1) {
            entryCount += 1;
        }
        if ((beNDMWLoadSavePlWork__GetIsRdy(DataList_GetWordAt_003e9240(works, index)) & 0xFF) == 1) {
            readyCount += 1;
        }
    }
    return entryCount == readyCount;
}
static inline void EndInterface(beNDMWLoadCtrl2CommonIntf *common) {
    int index = 0;
    common->_intfStat = 3;
    void *works = (void *)(common->_flagWork);
    for (index = 0; index < igDataList_GetCount(works); index++) {
        beNDMWLoadSavePlWork__SetIsCtrl(DataList_GetWordAt_003e9240(works, index), 0);
    }
}
extern "C" void beNDMWSaveIntf_Update(beNDMWSaveIntf *self, beBaseInfoRam *ram);
extern "C" int beNDMWSaveIntf_OnMessage(beNDMWSaveIntf *self, beBaseInfoRam *ram, MessageArg *message);

void beNDMWSaveIntf_AcquirePadManager(beNDMWSaveIntf *self) {
    RefObject *found;
    RefObject *old;

    if (self->_padManager == 0) {
        found = igInsightCore_FindManager(self->_insight, g_bePadManager_metaObject[0]);
        if (found != 0) {
            found->refCount = found->refCount + 1;
        }
        old = (RefObject *)self->_padManager;
        if (old != 0) {
            old->refCount = old->refCount - 1;
            if (((unsigned long long) ((long long) old->refCount << 0x29) >> 0x29) == 0) {
                igObject_Destroy(old);
            }
        }
        self->_padManager = (int)found;
    }
}

void beNDMWSaveIntf_Update(beNDMWSaveIntf *self, beBaseInfoRam *ram) {
    beNDMWSaveIntfCtrlData *ctrl;
    beNDMWLoadIntf2ComMdlCtrl *comMdl;
    beNDMWLoadIntf2MesWin *mesWin;
    beNDMWLoadIntf2SelSlot *selSlot;
    beNDMWLoadCtrl2CommonIntf *common;
    beNDMWLoadIntf2DegiStateCtrl *degiStates;
    beNDMWLoadIntf2DataSelIntf *dataSel;
    int padTrigger;
    unsigned char countdownDone;
    int accessCount;
    int accessPlayer;
    int newAccessCount;
    int newAccessPlayer;
    int remaining;
    int player;
    unsigned char otherEntry;
    int index;
    int ramNo;
    int degiNo;
    beNDMWLoadSavePlWork *work;
    int result;
    void *playerData;
    AccessList *accessList;
    int degiIndex;
    int allocator;
    int textId;
    int noticeText;
    int questionText;
    int slot;
    void *statusWin;
    beNDMWMcUtilCtrl *mcUtil;
    beNDMWLoadSavePlWork *errorWork;
    int cardResult;
    beNDMWLoadSavePlWork *selectWork;
    beNDMWLoadSavePlWork *cardWork;
    beNDMWLoadSavePlWork *waitWork;
    void *slotPlayer;

    int tref;
    if (ram->_dataList != 0) {
        tref = ObjectRef_Get_003e93b0(&ram->_dataList);
        if (tref == 0) {
            FreshDataList::Assign(&ram->_dataList, igObject_GetAllocator(ram));
        }
        ctrl = (beNDMWSaveIntfCtrlData *)(DataList_FindProperty_003e9280(ObjectRef_Get_003e92a0(&ram->_dataList), g_propertyNameField[0], CTRL_3));
        tref = ObjectRef_Get_003e93b0(&ram->_dataList);
        if (tref == 0) {
            FreshDataList::Assign(&ram->_dataList, igObject_GetAllocator(ram));
        }
        comMdl = (beNDMWLoadIntf2ComMdlCtrl *)(DataList_FindProperty_003e9280(ObjectRef_Get_003e92a0(&ram->_dataList), g_propertyNameField[0], COMMDLCTRL_3));
        tref = ObjectRef_Get_003e93b0(&ram->_dataList);
        if (tref == 0) {
            FreshDataList::Assign(&ram->_dataList, igObject_GetAllocator(ram));
        }
        mesWin = (beNDMWLoadIntf2MesWin *)(DataList_FindProperty_003e9280(ObjectRef_Get_003e92a0(&ram->_dataList), g_propertyNameField[0], MESWIN_2));
        tref = ObjectRef_Get_003e93b0(&ram->_dataList);
        if (tref == 0) {
            FreshDataList::Assign(&ram->_dataList, igObject_GetAllocator(ram));
        }
        selSlot = (beNDMWLoadIntf2SelSlot *)(DataList_FindProperty_003e9280(ObjectRef_Get_003e92a0(&ram->_dataList), g_propertyNameField[0], SELSLOT_2));
        tref = ObjectRef_Get_003e93b0(&ram->_dataList);
        if (tref == 0) {
            FreshDataList::Assign(&ram->_dataList, igObject_GetAllocator(ram));
        }
        common = (beNDMWLoadCtrl2CommonIntf *)(DataList_FindProperty_003e9280(ObjectRef_Get_003e92a0(&ram->_dataList), g_propertyNameField[0], COMMONINTF_2));
        tref = ObjectRef_Get_003e93b0(&ram->_dataList);
        if (tref == 0) {
            FreshDataList::Assign(&ram->_dataList, igObject_GetAllocator(ram));
        }
        degiStates = (beNDMWLoadIntf2DegiStateCtrl *)(DataList_FindProperty_003e9280(ObjectRef_Get_003e92a0(&ram->_dataList), g_propertyNameField[0], DEGISTATECTRL_2));
        tref = ObjectRef_Get_003e93b0(&ram->_dataList);
        if (tref == 0) {
            FreshDataList::Assign(&ram->_dataList, igObject_GetAllocator(ram));
        }
        dataSel = (beNDMWLoadIntf2DataSelIntf *)(DataList_FindProperty_003e9280(ObjectRef_Get_003e92a0(&ram->_dataList), g_propertyNameField[0], DATASELINTF_2));
        beNDMWLoadIntf2ComMdlCtrl__Poll(comMdl);
        beNDMWLoadIntf2MesWin__Update(mesWin);
        padTrigger = 0;
        if (((beNDMWLoadSavePlWork *)(ObjectList_GetAt_003e9260(common->_flagWork, ram->_ramNo)))->_isCtrl == 1) {
            padTrigger = ((bePadData *)(bePadManager_GetPadForPlayer(self->_padManager, ram->_ramNo)))->_trigger;
        }
        switch (((beNDMWLoadSavePlWork *)(ObjectList_GetAt_003e9260(common->_flagWork, ram->_ramNo)))->_sysStat0) {
        case STAGE_WAIT_UTIL:
            countdownDone = 0;
            switch ((((beNDMWLoadSavePlWork *)(ObjectList_GetAt_003e9260(common->_flagWork, ram->_ramNo)))->_sysStat1)) {
            case 0:
                beNDMWLoadIntf2MesWin__RequestSystemMessage(mesWin, TextId(ram, 0x51C));
                SetStageStep(((beNDMWLoadSavePlWork *)(DataList_GetWordAt_003e9240(common->_flagWork, ram->_ramNo))), 1);
                break;
            case 1:
                waitWork = (beNDMWLoadSavePlWork *)(ObjectList_GetAt_003e9260(common->_flagWork, ram->_ramNo));
                remaining = waitWork->_sysCount0 - 1;
                waitWork->_sysCount0 = remaining;
                if (remaining <= 0) {
                    { beNDMWLoadSavePlWork *work = (beNDMWLoadSavePlWork *)ObjectList_GetAt_003e9260(common->_flagWork, ram->_ramNo); work->_sysCount0 = 0; }
                    countdownDone = 1;
                }
                break;
            }
            if (countdownDone != 1) {
            case STAGE_DIALOGUE:
                switch (ctrl->_st0) {
                case SAVE_OPEN:
                    switch (ctrl->_st1) {
                    default:
                        ModelPos openPos(*(ModelPos *)comMdl->_pos);
                        beNDMWLoadIntf2ComMdlCtrl__StartAt(comMdl, ram->_ramNo, j_chrselbase_2, SQ_OPEN_3, openPos, 1);
                        NextStep(ctrl);
                        return;
                    case 1:
                        if ((beNDMWLoadIntf2ComMdlCtrl__IsOpenQueueEmpty(comMdl) & 0xFF) == 1) {
                            NextStep(ctrl);
                            return;
                        }
                        break;
                    case 2:
                        beMessenger_SelectGroup(self->_messenger, GAMERAM_5);
                        beMessenger_AppendInt(self->_messenger, ram->_ramNo);
                        beMessenger_DispatchSelected(self->_messenger, GETPLAYER_3);
                        playerData = beMessenger_GetObject(self->_messenger, 0);
                        if (*(unsigned char *)((char *)(igProperty_GetRecordByte(playerData, ISUSE_3)) + 12) == 1) {
                            beMessenger_SelectGroup(self->_messenger, GAMERAM_5);
                            beMessenger_AppendInt(self->_messenger, ram->_ramNo);
                            beMessenger_DispatchSelected(self->_messenger, CURRENT2BASE);
                            beNDMWDegiData__LoadFromProperties(ObjectList_GetAt_003e9260(common->_gameUseData, ram->_ramNo), playerData);
                            EnterState(ctrl, SAVE_OPEN_WINDOW);
                            { beNDMWLoadSavePlWork *work = (beNDMWLoadSavePlWork *)ObjectList_GetAt_003e9260(common->_flagWork, ram->_ramNo); work->_isRdy = 0; }
                            { beNDMWLoadSavePlWork *work = (beNDMWLoadSavePlWork *)ObjectList_GetAt_003e9260(common->_flagWork, ram->_ramNo); work->_isEntry = 1; }
                            return;
                        }
                        if (ram->_ramNo == 0) {
                            beMessenger_SelectGroup(self->_messenger, GAMERAM_5);
                            beMessenger_AppendInt(self->_messenger, ram->_ramNo);
                            beMessenger_AppendString(self->_messenger, g_playerModelRow[0]);
                            beMessenger_AppendString(self->_messenger, g_defaultPlayerName);
                            beMessenger_DispatchSelected(self->_messenger, GAMESTART_2);
                            beMessenger_SelectGroup(self->_messenger, GAMERAM_5);
                            beMessenger_AppendInt(self->_messenger, ram->_ramNo);
                            beMessenger_DispatchSelected(self->_messenger, GETPLAYER_3);
                            playerData = beMessenger_GetObject(self->_messenger, 0);
                            beNDMWDegiData__LoadFromProperties(ObjectList_GetAt_003e9260(common->_gameUseData, ram->_ramNo), playerData);
                            return;
                        }
                        { beNDMWLoadSavePlWork *work = (beNDMWLoadSavePlWork *)ObjectList_GetAt_003e9260(common->_flagWork, ram->_ramNo); work->_isEntry = 0; }
                        EnterState(ctrl, SAVE_DONE);
                        return;
                        break;
                    }
                    break;
                case SAVE_OPEN_WINDOW:
                    switch (ctrl->_st1) {
                    case 0:
                        ModelPos winPos(*(ModelPos *)comMdl->_pos);
                        beNDMWLoadIntf2ComMdlCtrl__StartAt(comMdl, ram->_ramNo, j_chrselmesswin_2, SQ_OPEN_3, winPos, 1);
                        beNDMWLoadIntf2MesWin__RequestOpen(mesWin);
                        NextStep(ctrl);
                        return;
                    case 1:
                        if ((beNDMWLoadIntf2ComMdlCtrl__IsOpenQueueEmpty(comMdl) & 0xFF) == 1) {
                            beNDMWLoadIntf2MesWin__RequestMesErase(mesWin);
                            EnterState(ctrl, SAVE_ASK);
                            return;
                        }
                        break;
                    }
                    break;
                case SAVE_ASK:
                    switch (ctrl->_st1) {
                    default:
                        beNDMWLoadIntf2MesWin__RequestQuestion(mesWin, TextId(ram, 0x502), 0);
                        NextStep(ctrl);
                        return;
                    case 1:
                        if (!(beNDMWLoadIntf2MesWin__GetIsCtrl(mesWin) & 0xFF)) {
                            switch (beNDMWLoadIntf2MesWin__GetCurPoint(mesWin)) {
                            case 0:
                                EnterState(ctrl, SAVE_SELECT_CARD);
                                return;
                            case 1:
                                NextStep(ctrl);
                                return;
                            }
                        }
                        break;
                    case 2:
                        switch (ctrl->_st2) {
                        case 0:
                            degiNo = ram->_ramNo;
                            statusWin = ObjectList_GetAt_003e9260(degiStates->_statDataList, 0);
                            beNDMWLoadIntf2DegiState__RequestOpen(statusWin, 1, degiNo);
                            NextSubstep(ctrl);
                            return;
                        case 1:
                            if ((beNDMWLoadIntf2DegiState__Update(ObjectList_GetAt_003e9260(degiStates->_statDataList, 0)) & 0xFF) == 1) {
                                if (ram->_ramNo == 0) {
                                    player = 1;
                                    otherEntry = 0;
                                    do {
                                        if (((beNDMWLoadSavePlWork *)(ObjectList_GetAt_003e9260(common->_flagWork, player)))->_isEntry == 1) {
                                            otherEntry = 1;
                        break;
                                        }
                                        player += 1;
                                    } while (player < 4);
                                    if ((otherEntry & 0xFF) == 1) {
                                        EnterState(ctrl, SAVE_WAIT_PLAYERS);
                                        return;
                                    }
                                    EnterState(ctrl, SAVE_ASK_CONTINUE);
                                    return;
                                }
                                EnterState(ctrl, SAVE_ASK_CONTINUE);
                                return;
                            }
                            break;
                        }
                        break;
                    }
                    break;
                case SAVE_SELECT_CARD:
                    switch (ctrl->_st1) {
                    case 0:
                        switch (ctrl->_st2) {
                        case 0:
                            beNDMWLoadCtrl2CommonIntf__RemoveAccessPlayer(common, ram->_ramNo, 2);
                            beNDMWLoadIntf2SelSlot__Init(selSlot);
                            EnterSlotState(selSlot, 0);
                            NextSubstep(ctrl);
                            return;
                        case 1:
                            if ((beNDMWLoadIntf2SelSlot__Open(selSlot, -1, 2) & 0xFF) == 1) {
                                textId = -1;
                                switch (common->_kindHard) {
                                case 0:
                                    textId = TextId(ram, 0x1024);
                                    break;
                                case 1:
                                    textId = TextId(ram, 0x2024);
                                    break;
                                case 2:
                                    textId = TextId(ram, 0x3024);
                                    break;
                                }
                                beNDMWLoadIntf2MesWin__RequestMessage(mesWin, textId);
                                EnterSlotState(selSlot, 1);
                                NextStep(ctrl);
                                return;
                            }
                            break;
                        }
                        break;
                    case 1:
                        switch (ctrl->_st2) {
                        case 0:
                            if ((beNDMWLoadIntf2SelSlot__UpdateSelection(selSlot, ((beNDMWLoadSavePlWork *)(ObjectList_GetAt_003e9260(common->_flagWork, ram->_ramNo)))->_isCtrl, 1) & 0xFF) == 1) {
                                if (selSlot->_isReOpenReq == 1) {
                                    NextStep(ctrl);
                                    return;
                                }
                                if (selSlot->_isCansel == 1) {
                                    NextStep(ctrl);
                                    return;
                                }
                                NextSubstep(ctrl);
                                return;
                            }
                            break;
                        case 1:
                            switch (ctrl->_st3) {
                            case 0:
                                textId = -1;
                                switch (common->_kindHard) {
                                case 0:
                                    textId = TextId(ram, 0x1004);
                                    break;
                                case 1:
                                    textId = TextId(ram, 0x2004);
                                    break;
                                case 2:
                                    textId = TextId(ram, 0x3004);
                                    break;
                                }
                                beNDMWLoadIntf2MesWin__RequestMessage(mesWin, textId);
                                beNDMWLoadCtrl2CommonIntf__StartUtilFor(common, ram->_ramNo, STAGE_CARD_ACCESS);
                                NextTick(ctrl);
                                return;
                            case 1:
                                switch (((beNDMWLoadSavePlWork *)(ObjectList_GetAt_003e9260(common->_flagWork, ram->_ramNo)))->_utilReturn) {
                                case 0:
                                    NextStep(ctrl);
                                    return;
                                case 1:
                                case 2:
                                    textId = -1;
                                    switch (common->_kindHard) {
                                    case 0:
                                        textId = TextId(ram, 0x1024);
                                        break;
                                    case 1:
                                        textId = TextId(ram, 0x2024);
                                        break;
                                    case 2:
                                        textId = TextId(ram, 0x3024);
                                        break;
                                    }
                                    beNDMWLoadIntf2MesWin__RequestMessage(mesWin, textId);
                                    beNDMWLoadIntf2SelSlot__PublishCursor(selSlot);
                                    SetStep(ctrl, 1);
                                    return;
                                case 4:
                                    textId = -1;
                                    switch (common->_kindHard) {
                                    case 0:
                                        textId = TextId(ram, 0x1024);
                                        break;
                                    case 1:
                                        textId = TextId(ram, 0x2024);
                                        break;
                                    case 2:
                                        textId = TextId(ram, 0x3024);
                                        break;
                                    }
                                    beNDMWLoadIntf2MesWin__RequestMessage(mesWin, textId);
                                    beNDMWLoadIntf2SelSlot__PublishCursor(selSlot);
                                    SetStep(ctrl, 1);
                                    return;
                                }
                                break;
                            }
                            break;
                        }
                        break;
                    case 2:
                        switch (ctrl->_st2) {
                        case 0:
                            EnterSlotState(selSlot, 2);
                            NextSubstep(ctrl);
                            return;
                        case 1:
                            if ((beNDMWLoadIntf2SelSlot__Close(selSlot) & 0xFF) == 1) {
                                if (selSlot->_isReOpenReq == 1) {
                                    EnterState(ctrl, SAVE_SELECT_CARD);
                                    return;
                                }
                                if (selSlot->_isCansel == 1) {
                                    EnterState(ctrl, SAVE_ASK);
                                    return;
                                }
                                EnterState(ctrl, SAVE_PREPARE_DATA);
                                return;
                            }
                            break;
                        }
                        break;
                    }
                    break;
                case SAVE_PREPARE_DATA:
                    switch (ctrl->_st1) {
                    case 0:
                        beNDMWLoadIntf2DataSelIntf__Init(dataSel, ram->_ramNo, 1);
                        NextStep(ctrl);
                        return;
                    case 1:
                        switch (ctrl->_st2) {
                        case 0:
                            beNDMWLoadIntf2DataSelIntf__ClearStatesFrom(dataSel, 0, 1);
                            NextSubstep(ctrl);
                            return;
                        case 1:
                            if ((beNDMWLoadIntf2DataSelIntf__OpenSaveArea(dataSel, 0, 1) & 0xFF) == 1) {
                                EnterState(ctrl, SAVE_SELECT_DATA);
                                return;
                            }
                            break;
                        }
                        break;
                    }
                    break;
                case SAVE_SELECT_DATA:
                    switch (ctrl->_st1) {
                    case 0x0:
                        if (((beNDMWLoadSavePlWork *)(ObjectList_GetAt_003e9260(common->_flagWork, ram->_ramNo)))->_isCutConnect == 1) {
                            SetStep(ctrl, 0x64);
                            return;
                        }
                        switch (ctrl->_st2) {
                        case 0:
                            beNDMWLoadIntf2DataSelIntf__ClearStatesFrom(dataSel, 0);
                            NextSubstep(ctrl);
                            return;
                        case 1:
                            if ((beNDMWLoadIntf2DataSelIntf__UpdateSelection(dataSel, 0) & 0xFF) == 1) {
                                if (dataSel->_isCancel != 0) {
                                    NextSubstep(ctrl);
                                    return;
                                }
                                NextStep(ctrl);
                                return;
                            }
                            break;
                        case 2:
                            beNDMWLoadIntf2DataSelIntf__ClearStatesFrom(dataSel, 0);
                            NextSubstep(ctrl);
                            return;
                        case 3:
                            if ((beNDMWLoadIntf2DataSelIntf__CloseAll(dataSel, 0) & 0xFF) == 1) {
                                EnterState(ctrl, SAVE_SELECT_CARD);
                                return;
                            }
                            break;
                        }
                        break;
                    case 0x1:
                        switch (ctrl->_st2) {
                        case 0x0:
                            beNDMWLoadCtrl2CommonIntf__StartUtilFor(common, ram->_ramNo, STAGE_SAVE_DATA);
                            NextSubstep(ctrl);
                            return;
                        case 0x1:
                            switch (((beNDMWLoadSavePlWork *)(ObjectList_GetAt_003e9260(common->_flagWork, ram->_ramNo)))->_utilReturn) {
                            case 0:
                                ctrl->_isOneSave = 1;
                                NextStep(ctrl);
                                return;
                            case 1:
                                SetSubstep(ctrl, 0x32);
                                return;
                            case 3:
                                selSlot->_isSelect = 0;
                                SetStep(ctrl, 0);
                                return;
                            case 2:
                                SetSubstep(ctrl, 0x32);
                                return;
                            }
                            break;
                        case 0x32:
                            EnterSlotState(selSlot, 2);
                            NextSubstep(ctrl);
                            return;
                        case 0x33:
                            if ((beNDMWLoadIntf2SelSlot__Close(selSlot, 1, 2) & 0xFF) == 1) {
                                SetStep(ctrl, 0x64);
                                return;
                            }
                            break;
                        }
                        break;
                    case 0x2:
                        if (((beNDMWLoadSavePlWork *)(ObjectList_GetAt_003e9260(common->_flagWork, ram->_ramNo)))->_isCutConnect == 1) {
                            SetStep(ctrl, 0x64);
                            return;
                        }
                        switch (ctrl->_st2) {
                        default:
                        case 0:
                            beNDMWLoadIntf2MesWin__RequestPrompt(mesWin, TextId(ram, 0x50B));
                            NextSubstep(ctrl);
                            return;
                        case 1:
                            if (!(beNDMWLoadIntf2MesWin__GetIsCtrl(mesWin, 1) & 0xFF)) {
                                NextSubstep(ctrl);
                                return;
                            }
                            break;
                        case 2:
                            beNDMWLoadIntf2MesWin__RequestQuestion(mesWin, TextId(ram, 0x50D), 0);
                            NextSubstep(ctrl);
                            return;
                        case 3:
                            if (!(beNDMWLoadIntf2MesWin__GetIsCtrl(mesWin, 1) & 0xFF)) {
                                switch (beNDMWLoadIntf2MesWin__GetCurPoint(mesWin)) {
                                case 0:
                                    SetSubstep(ctrl, 5);
                                    return;
                                case 1:
                                    SetSubstep(ctrl, 4);
                                    return;
                                }
                            }
                            break;
                        case 4:
                            switch (ctrl->_st3) {
                            case 0:
                                beNDMWLoadIntf2DataSelIntf__ClearStatesFrom(dataSel, 0);
                                NextTick(ctrl);
                                return;
                            case 1:
                                if ((beNDMWLoadIntf2DataSelIntf__OpenAreaCursor(dataSel, 0) & 0xFF) == 1) {
                                    EnterState(ctrl, SAVE_SELECT_DATA);
                                    return;
                                }
                                break;
                            }
                            break;
                        case 5:
                            switch (ctrl->_st3) {
                            case 0:
                                beNDMWLoadCtrl2CommonIntf__RemoveAccessPlayer(common, ram->_ramNo);
                                beNDMWLoadIntf2DataSelIntf__ClearStatesFrom(dataSel, 0);
                                NextTick(ctrl);
                                return;
                            case 1:
                                if ((beNDMWLoadIntf2DataSelIntf__CloseSaveArea(dataSel, 0) & 0xFF) == 1) {
                                    if (ram->_ramNo == 0) {
                                        player = 1;
                                        otherEntry = 0;
                                        do {
                                            if (((beNDMWLoadSavePlWork *)(ObjectList_GetAt_003e9260(common->_flagWork, player)))->_isEntry == 1) {
                                                otherEntry = 1;
                                                break;
                                            }
                                            player += 1;
                                        } while (player < 4);
                                        if ((otherEntry & 0xFF) == 1) {
                                            EnterState(ctrl, SAVE_WAIT_PLAYERS);
                                            return;
                                        }
                                        EnterState(ctrl, SAVE_ASK_CONTINUE);
                                        return;
                                    }
                                    EnterState(ctrl, SAVE_ASK_CONTINUE);
                                    return;
                                }
                                break;
                            }
                            break;
                        }
                        break;
                    case 0x64:
                        switch (ctrl->_st2) {
                        case 0:
                            beNDMWLoadIntf2MesWin__Cancel(mesWin);
                            beNDMWLoadIntf2DataSelIntf__ClearStatesFrom(dataSel, 0);
                            NextSubstep(ctrl);
                            return;
                        case 1:
                            if ((beNDMWLoadIntf2DataSelIntf__CloseAll(dataSel, 0) & 0xFF) == 1) {
                                EnterState(ctrl, SAVE_SELECT_CARD);
                                return;
                            }
                            break;
                        }
                        break;
                    }
                    break;
                case SAVE_ASK_CONTINUE:
                    switch (ctrl->_st1) {
                    case 0:
                    default:
                        switch (ctrl->_st2) {
                        case 0:
                            beNDMWLoadIntf2MesWin__RequestPrompt(mesWin, TextId(ram, 0x50E));
                            NextSubstep(ctrl);
                            return;
                        case 1:
                            if (!(beNDMWLoadIntf2MesWin__GetIsCtrl(mesWin) & 0xFF)) {
                                NextSubstep(ctrl);
                                return;
                            }
                            break;
                        case 2:
                            beNDMWLoadIntf2MesWin__RequestQuestion(mesWin, TextId(ram, 0x510), 0);
                            NextSubstep(ctrl);
                            return;
                        case 3:
                            if (!(beNDMWLoadIntf2MesWin__GetIsCtrl(mesWin) & 0xFF)) {
                                switch (beNDMWLoadIntf2MesWin__GetCurPoint(mesWin)) {
                                case 0:
                                    EnterState(ctrl, SAVE_WAIT_PLAYERS);
                                    return;
                                case 1:
                                    NextStep(ctrl);
                                    return;
                                }
                            }
                            break;
                        }
                    break;
                    case 1:
                        switch (ctrl->_st2) {
                        case 0:
                            if (ctrl->_isOneSave == 1) {
                                SetSubstep(ctrl, 4);
                                return;
                            }
                            beNDMWLoadIntf2MesWin__RequestPrompt(mesWin, TextId(ram, 0x527), 1);
                            NextSubstep(ctrl);
                            return;
                        case 1:
                            if (!(beNDMWLoadIntf2MesWin__GetIsCtrl(mesWin) & 0xFF)) {
                                NextSubstep(ctrl);
                                return;
                            }
                            break;
                        case 2:
                            beNDMWLoadIntf2MesWin__RequestQuestion(mesWin, TextId(ram, 0x529), 1);
                            NextSubstep(ctrl);
                            return;
                        case 3:
                            if (!(beNDMWLoadIntf2MesWin__GetIsCtrl(mesWin) & 0xFF)) {
                                switch (beNDMWLoadIntf2MesWin__GetCurPoint(mesWin)) {
                                case 0:
                                    SetSubstep(ctrl, 4);
                                    return;
                                case 1:
                                    SetSubstep(ctrl, 5);
                                    return;
                                }
                            }
                            break;
                        case 4:
                            switch (ctrl->_st3) {
                            case 0:
                                beNDMWLoadIntf2DegiState__RequestClose(ObjectList_GetAt_003e9260(degiStates->_statDataList, 0), 1);
                                beNDMWLoadIntf2ComMdlCtrl__Close(comMdl, ram->_ramNo, j_chrselmesswin_2, SQ_CLOSE_5, 1);
                                beNDMWLoadIntf2MesWin__RequestClose(mesWin);
                                NextTick(ctrl);
                                return;
                            case 1:
                                if (((beNDMWLoadIntf2DegiState__Update(ObjectList_GetAt_003e9260(degiStates->_statDataList, 0)) & 0xFF) == 1) && ((beNDMWLoadIntf2ComMdlCtrl__IsCloseQueueEmpty(comMdl) & 0xFF) == 1)) {
                                    EnterState(ctrl, SAVE_DONE);
                                    { beNDMWLoadSavePlWork *work = (beNDMWLoadSavePlWork *)ObjectList_GetAt_003e9260(common->_flagWork, ram->_ramNo); work->_isEntry = 0; }
                                    { beNDMWLoadSavePlWork *work = (beNDMWLoadSavePlWork *)ObjectList_GetAt_003e9260(common->_flagWork, ram->_ramNo); work->_isRdy = 0; }
                                    return;
                                }
                                break;
                            }
                            break;
                        case 5:
                            switch (ctrl->_st3) {
                            case 0:
                                beNDMWLoadIntf2DegiState__RequestClose(ObjectList_GetAt_003e9260(degiStates->_statDataList, 0), 0);
                                NextTick(ctrl);
                                return;
                            case 1:
                                if ((beNDMWLoadIntf2DegiState__Update(ObjectList_GetAt_003e9260(degiStates->_statDataList, 0)) & 0xFF) == 1) {
                                    EnterState(ctrl, SAVE_ASK);
                                    return;
                                }
                                break;
                            }
                            break;
                        }
                    break;
                    }
                    break;
                case SAVE_WAIT_PLAYERS:
                    switch (ctrl->_st1) {
                    case 0:
                        { beNDMWLoadSavePlWork *work = (beNDMWLoadSavePlWork *)ObjectList_GetAt_003e9260(common->_flagWork, ram->_ramNo); work->_isRdy = 1; }
                        ramNo = ram->_ramNo;
                        if (ramNo == 0) {
                            if (AllEntriesReady((void *)common->_flagWork) == 1) {
                                beNDMWLoadIntf2MesWin__RequestMessage(mesWin, TextId(ram, 0x51D));
                                SetStep(ctrl, 3);
                                return;
                            }
                            beNDMWLoadIntf2MesWin__RequestMessage(mesWin, TextId(ram, 0x530));
                            NextStep(ctrl);
                            return;
                        }
                        beNDMWLoadIntf2MesWin__RequestMessage(mesWin, PlayerTextId(ramNo, 0x530));
                        NextStep(ctrl);
                        return;
                    case 1:
                        switch (ctrl->_st3) {
                        case 0:
                            if (ram->_ramNo == 0) {
                                if (AllEntriesReady((void *)common->_flagWork) == 1) {
                                    SetStep(ctrl, 3);
                                    return;
                                }
                                if (padTrigger & PAD_CIRCLE) {
                                    { beNDMWLoadSavePlWork *work = (beNDMWLoadSavePlWork *)ObjectList_GetAt_003e9260(common->_flagWork, ram->_ramNo); work->_isRdy = 0; }
                                    NextStep(ctrl);
                                    return;
                                }
                            } else {
                                if (AllEntriesReady((void *)common->_flagWork) == 1) {
                                    beNDMWLoadIntf2MesWin__RequestMessage(mesWin, TextId(ram, 0x51F));
                                    NextTick(ctrl);
                                    return;
                                }
                                if (padTrigger & PAD_CIRCLE) {
                                    { beNDMWLoadSavePlWork *work = (beNDMWLoadSavePlWork *)ObjectList_GetAt_003e9260(common->_flagWork, ram->_ramNo); work->_isRdy = 0; }
                                    NextStep(ctrl);
                                    return;
                                }
                            }
                            break;
                        case 1:
                            if (AllEntriesReady((void *)common->_flagWork) == 0) {
                                beNDMWLoadIntf2MesWin__RequestMessage(mesWin, TextId(ram, 0x530));
                                ctrl->_st3 = 0;
                                return;
                            }
                            if (padTrigger & PAD_CIRCLE) {
                                { beNDMWLoadSavePlWork *work = (beNDMWLoadSavePlWork *)ObjectList_GetAt_003e9260(common->_flagWork, ram->_ramNo); work->_isRdy = 0; }
                                NextStep(ctrl);
                                return;
                            }
                            break;
                        }
                        break;
                    case 2:
                        switch (ctrl->_st2) {
                        case 0:
                            beNDMWLoadIntf2DegiState__RequestClose(ObjectList_GetAt_003e9260(degiStates->_statDataList, 0), 2);
                            NextSubstep(ctrl);
                            return;
                        case 1:
                            if ((beNDMWLoadIntf2DegiState__Update(ObjectList_GetAt_003e9260(degiStates->_statDataList, 0)) & 0xFF) == 1) {
                                EnterState(ctrl, SAVE_ASK);
                                return;
                            }
                            break;
                        }
                        break;
                    case 3:
                        switch (ctrl->_st2) {
                        case 0:
                            beNDMWLoadIntf2MesWin__RequestMessage(mesWin, TextId(ram, 0x51D));
                            NextSubstep(ctrl);
                            return;
                        case 1:
                            if (padTrigger & PAD_CIRCLE) {
                                { beNDMWLoadSavePlWork *work = (beNDMWLoadSavePlWork *)ObjectList_GetAt_003e9260(common->_flagWork, ram->_ramNo); work->_isRdy = 0; }
                                SetStep(ctrl, 2);
                                return;
                            }
                            if (AllEntriesReady((void *)common->_flagWork) == 1) {
                                if (padTrigger & PAD_START) {
                                    EndInterface(common);
                                    NextSubstep(ctrl);
                                    return;
                                }
                            } else {
                                beNDMWLoadIntf2MesWin__RequestMessage(mesWin, TextId(ram, 0x530));
                                SetStep(ctrl, 1);
                                return;
                            }
                            break;
                        }
                        break;
                    }
                    break;
                case SAVE_DONE:
                    switch (ctrl->_st1) {
                    case 0:
                        ramNo = ram->_ramNo;
                        if (ramNo == 0) {
                            beNDMWLoadIntf2MesWin__RequestMessage(mesWin, PlayerTextId(ramNo, 0x51F));
                            EndInterface(common);
                        }
                        NextStep(ctrl);
                        return;
                    case 1:
                        break;
                    }
                    break;
                }
            }
            break;
        case STAGE_CLOSE:
            switch (((beNDMWLoadSavePlWork *)(ObjectList_GetAt_003e9260(common->_flagWork, ram->_ramNo)))->_sysStat1) {
            case 0:
                switch (ctrl->_st0) {
                case SAVE_DONE:
                default:
                    SetStageStep(((beNDMWLoadSavePlWork *)(DataList_GetWordAt_003e9240(common->_flagWork, ram->_ramNo))), 1);
                    break;
                case SAVE_WAIT_PLAYERS:
                    beNDMWLoadIntf2ComMdlCtrl__Close(comMdl, ram->_ramNo, j_chrselmesswin_2, SQ_CLOSE_5, 1);
                    beNDMWLoadIntf2MesWin__RequestClose(mesWin);
                    beNDMWLoadIntf2DegiState__RequestConfirmClose(ObjectList_GetAt_003e9260(degiStates->_statDataList, 0));
                    SetStageStep(((beNDMWLoadSavePlWork *)(DataList_GetWordAt_003e9240(common->_flagWork, ram->_ramNo))), 2);
                    break;
                }
                beNDMWLoadIntf2ComMdlCtrl__Close(comMdl, ram->_ramNo, j_chrselbase_2, SQ_CLOSE_5, 1);
                return;
            case 1:
                if ((beNDMWLoadIntf2ComMdlCtrl__IsCloseQueueEmpty(comMdl) & 0xFF) == 1) {
                    { beNDMWLoadSavePlWork *work = (beNDMWLoadSavePlWork *)ObjectList_GetAt_003e9260(common->_flagWork, ram->_ramNo); work->_isClose = 1; }
                    SetStageStep(((beNDMWLoadSavePlWork *)(DataList_GetWordAt_003e9240(common->_flagWork, ram->_ramNo))), 3);
                    return;
                }
                break;
            case 2:
                if (((beNDMWLoadIntf2DegiState__Update(ObjectList_GetAt_003e9260(degiStates->_statDataList, 0)) & 0xFF) == 1) && ((beNDMWLoadIntf2ComMdlCtrl__IsCloseQueueEmpty(comMdl) & 0xFF) == 1)) {
                    { beNDMWLoadSavePlWork *work = (beNDMWLoadSavePlWork *)ObjectList_GetAt_003e9260(common->_flagWork, ram->_ramNo); work->_isClose = 1; }
                    SetStageStep(((beNDMWLoadSavePlWork *)(DataList_GetWordAt_003e9240(common->_flagWork, ram->_ramNo))), 3);
                    return;
                }
                break;
            case 3:
                break;
            }
            break;
        case STAGE_SAVE_DATA:
            selectWork = (beNDMWLoadSavePlWork *)(ObjectList_GetAt_003e9260(common->_flagWork, ram->_ramNo));
            switch (selectWork->_sysStat1) {
            case 0x0:
                switch (selectWork->_sysStat2) {
                case 0:
                    beNDMWLoadIntf2DataSelIntf__ClearStatesFrom(dataSel, 0);
                    NextStageSubstep(selectWork);
                    return;
                case 1:
                    if ((beNDMWLoadIntf2DataSelIntf__ShowSelectedStatus(dataSel, 0) & 0xFF) == 1) {
                        NextStageStep(selectWork);
                        return;
                    }
                    break;
                }
                break;
            case 0x1:
                switch (selectWork->_sysStat2) {
                default:
                    if (((beNDMWLoadSavePlWork *)(ObjectList_GetAt_003e9260(common->_flagWork, ram->_ramNo)))->_isCutConnect == 1) {
                        SetStageStep(selectWork, 0x64);
                        return;
                    }
                    switch (selectWork->_sysStat3) {
                    case 0:
                        if (((beNDMWDegiData *)(ObjectList_GetAt_003e9260(((beNDMWLoadSlotPlayer *)(selectWork->_haveSaveData))->_saveDataList, dataSel->_svDataSelPoint)))->_isUse == 0) {
                            beNDMWLoadIntf2MesWin__RequestPrompt(mesWin, TextId(ram, 0x508));
                        } else {
                            beNDMWLoadIntf2MesWin__RequestPrompt(mesWin, TextId(ram, 0x505));
                        }
                        NextStageTick(selectWork);
                        return;
                    case 1:
                        if (!(beNDMWLoadIntf2MesWin__GetIsCtrl(mesWin, 1) & 0xFF)) {
                            NextStageTick(selectWork);
                            return;
                        }
                        break;
                    case 2:
                        if (((beNDMWDegiData *)(ObjectList_GetAt_003e9260(((beNDMWLoadSlotPlayer *)(selectWork->_haveSaveData))->_saveDataList, dataSel->_svDataSelPoint)))->_isUse == 1) {
                            beNDMWLoadIntf2MesWin__RequestQuestion(mesWin, TextId(ram, 0x50A), 0);
                        } else {
                            beNDMWLoadIntf2MesWin__RequestQuestion(mesWin, TextId(ram, 0x507), 0);
                        }
                        NextStageTick(selectWork);
                        return;
                    case 3:
                        if (!(beNDMWLoadIntf2MesWin__GetIsCtrl(mesWin, 1) & 0xFF)) {
                            NextStageSubstep(selectWork);
                            return;
                        }
                        break;
                    }
                    break;
                case 1:
                    switch (selectWork->_sysStat3) {
                    case 0:
                        beNDMWLoadIntf2DataSelIntf__ClearStatesFrom(dataSel, 0);
                        NextStageTick(selectWork);
                        return;
                    case 1:
                        if (beNDMWLoadIntf2MesWin__GetCurPoint(mesWin, 2) == 0) {
                            if ((beNDMWLoadIntf2DataSelIntf__CloseStatusWindows(dataSel, 0) & 0xFF) == 1) {
                                NextStageSubstep(selectWork);
                                return;
                            }
                        } else if ((beNDMWLoadIntf2DataSelIntf__RestoreSaveArea(dataSel, 0) & 0xFF) == 1) {
                            NextStageSubstep(selectWork);
                            return;
                        }
                        break;
                    }
                    break;
                case 2:
                    switch (beNDMWLoadIntf2MesWin__GetCurPoint(mesWin, 2)) {
                    case 0:
                        NextStageStep(selectWork);
                        textId = -1;
                        switch (common->_kindHard) {
                        case 0:
                            textId = TextId(ram, 0x100B);
                            break;
                        case 1:
                            textId = TextId(ram, 0x200B);
                            break;
                        case 2:
                            textId = TextId(ram, 0x300B);
                            break;
                        }
                        beNDMWLoadIntf2MesWin__RequestMessage(mesWin, textId);
                        return;
                    case 1:
                        NextStageSubstep(selectWork);
                        return;
                    }
                    break;
                case 3:
                    switch (selectWork->_sysStat3) {
                    case 0:
                        beNDMWLoadIntf2DataSelIntf__ClearStatesFrom(dataSel, 0);
                        NextStageTick(selectWork);
                        return;
                    case 1:
                        if ((beNDMWLoadIntf2DataSelIntf__OpenAreaCursor(dataSel, 0) & 0xFF) == 1) {
                            EnterStage(selectWork, STAGE_UTIL_DONE);
                            selectWork->_utilReturn = 3;
                            return;
                        }
                        break;
                    }
                    break;
                }
                break;
            case 0x2:
                switch (selectWork->_sysStat2) {
                case 0:
                    switch (selectWork->_sysStat3) {
                    case 0:
                        ((beSystem *)self->_system_)->_isResetEnable = 0;
                        beNDMWLoadIntf2SelSlot__Reset(selSlot, 2);
                        EnterSlotState(selSlot, 0);
                        NextStageTick(selectWork);
                        return;
                    case 1:
                        if (((beNDMWMcSlot *)(ObjectList_GetAt_003e9260(((beNDMWMcUtilCtrl *)(common->_mcUtilCtrl))->_slot, selSlot->_mcSelPoint)))->_isConnect != 1) {
                            NextStageTick(selectWork);
                            return;
                        }
                        if ((beNDMWLoadIntf2SelSlot__Open(selSlot, -1) & 0xFF) == 1) {
                            NextStageSubstep(selectWork);
                            return;
                        }
                        break;
                    case 2:
                        if ((beNDMWLoadIntf2SelSlot__Open(selSlot, -1) & 0xFF) == 1) {
                            ((beNDMWMcUtilCtrl *)(common->_mcUtilCtrl))->_result = 0xC;
                            ((beSystem *)self->_system_)->_isResetEnable = 1;
                            EnterStage(selectWork, STAGE_UTIL_ERROR);
                            return;
                        }
                        break;
                    }
                    break;
                case 1:
                    switch (beNDMWLoadCtrl2CommonIntf__StepCheckMemoryCard(common, ram->_ramNo, mesWin, selSlot->_mcSelPoint, 3)) {
                    case 0:
                        break;
                    case 1:
                        NextStageSubstep(selectWork);
                        return;
                    case 2:
                        switch (((beNDMWMcUtilCtrl *)(common->_mcUtilCtrl))->_result) {
                        case 0xC:
                        ((beSystem *)self->_system_)->_isResetEnable = 1;
                        EnterStage(selectWork, STAGE_UTIL_ERROR);
                        return;
                        default:
                            ((beSystem *)self->_system_)->_isResetEnable = 1;
                            EnterStage(selectWork, STAGE_UTIL_ERROR);
                            return;
                        }
                    }
                    break;
                case 2:
                    switch (beNDMWLoadCtrl2CommonIntf__StepWriteSaveData(common, ram->_ramNo, mesWin, selSlot->_mcSelPoint, dataSel->_svDataSelPoint, 3)) {
                    case 0:
                        break;
                    case 1:
                        NextStageStep(selectWork);
                        return;
                    case 2:
                        switch (((beNDMWMcUtilCtrl *)(common->_mcUtilCtrl))->_result) {
                        case 0xC:
                        ((beSystem *)self->_system_)->_isResetEnable = 1;
                        EnterStage(selectWork, STAGE_UTIL_ERROR);
                        return;
                        default:
                            ((beSystem *)self->_system_)->_isResetEnable = 1;
                            EnterStage(selectWork, STAGE_UTIL_ERROR);
                            return;
                        }
                    }
                    break;
                }
                break;
            case 0x3:
                if ((selectWork->_sysStat3 == 0) && (((beNDMWMcSlot *)(ObjectList_GetAt_003e9260(((beNDMWMcUtilCtrl *)(common->_mcUtilCtrl))->_slot, selSlot->_mcSelPoint)))->_isConnect != 1)) {
                    selectWork->_sysStat3 = 1;
                }
                switch (selectWork->_sysStat2) {
                case 0:
                    ((beSystem *)self->_system_)->_isResetEnable = 1;
                    EnterSlotState(selSlot, 2);
                    NextStageSubstep(selectWork);
                    return;
                case 1:
                    if ((beNDMWLoadIntf2SelSlot__Close(selSlot) & 0xFF) == 1) {
                        NextStageSubstep(selectWork);
                        return;
                    }
                    break;
                case 2:
                    beNDMWLoadIntf2DataSelIntf__ClearStatesFrom(dataSel, 0);
                    NextStageSubstep(selectWork);
                    return;
                case 3:
                    if ((beNDMWLoadIntf2DataSelIntf__OpenSlotSaveArea(dataSel, 0) & 0xFF) == 1) {
                        NextStageSubstep(selectWork);
                        return;
                    }
                    break;
                case 4:
                    beNDMWLoadIntf2DataSelIntf__ClearStatesFrom(dataSel, 0);
                    NextStageSubstep(selectWork);
                    return;
                case 5:
                    if ((beNDMWLoadIntf2DataSelIntf__ShowAccessPlayers(dataSel, 0) & 0xFF) == 1) {
                        if (selectWork->_sysStat3 == 0) {
                            EnterStage(selectWork, STAGE_UTIL_DONE);
                            selectWork->_utilReturn = 0;
                            return;
                        }
                        NextStageStep(selectWork);
                        return;
                    }
                    break;
                }
                break;
            case 0x4:
                switch (selectWork->_sysStat3) {
                case 0:
                    beNDMWLoadIntf2MesWin__RequestPrompt(mesWin, TextId(ram, 0x50B));
                    NextStageTick(selectWork);
                    return;
                case 1:
                    if (!(beNDMWLoadIntf2MesWin__GetIsCtrl(mesWin) & 0xFF)) {
                        SetStageStep(selectWork, 0x64);
                        return;
                    }
                    break;
                }
                break;
            case 0x64:
                switch (selectWork->_sysStat2) {
                case 0:
                    beNDMWLoadIntf2MesWin__Cancel(mesWin);
                    NextStageSubstep(selectWork);
                    beNDMWLoadIntf2DataSelIntf__ClearStatesFrom(dataSel, 0);
                    return;
                case 1:
                    if ((beNDMWLoadIntf2DataSelIntf__CloseAll(dataSel, 0) & 0xFF) == 1) {
                        EnterStage(selectWork, STAGE_UTIL_DONE);
                        selectWork->_utilReturn = 2;
                        return;
                    }
                    break;
                }
                break;
            }
            break;
        case STAGE_CARD_ACCESS:
            cardWork = (beNDMWLoadSavePlWork *)(ObjectList_GetAt_003e9260(common->_flagWork, ram->_ramNo));
            switch (cardWork->_sysStat1) {
            case 0:
                switch (beNDMWLoadCtrl2CommonIntf__StepCheckMemoryCard(common, ram->_ramNo, mesWin, selSlot->_mcSelPoint, 3)) {
                case 0:
                    break;
                case 1:
                    SetStageStep(cardWork, 5);
                    return;
                case 2:
                    switch (((beNDMWMcUtilCtrl *)(common->_mcUtilCtrl))->_result) {
                    case 2:
                        SetStageStep(cardWork, 5);
                        return;
                    case 4:
                    case 3:
                        SetStageStep(cardWork, 1);
                        return;
                    case 7:
                        SetStageStep(cardWork, 3);
                        return;
                    case 12:
                        EnterStage(cardWork, STAGE_UTIL_ERROR);
                        return;
                    default:
                        EnterStage(cardWork, STAGE_UTIL_ERROR);
                        return;
                    }
                    break;
                }
                break;
            case 1:
                if (((beNDMWMcSlot *)(ObjectList_GetAt_003e9260(((beNDMWMcUtilCtrl *)(common->_mcUtilCtrl))->_slot, selSlot->_mcSelPoint)))->_isConnect != 1) {
                    beNDMWLoadIntf2MesWin__Cancel(mesWin);
                    EnterStage(cardWork, STAGE_UTIL_DONE);
                    cardWork->_utilReturn = 2;
                    return;
                }
                noticeText = -1;
                questionText = -1;
                switch (common->_kindHard) {
                case 0:
                    noticeText = TextId(ram, 0x1000);
                    questionText = TextId(ram, 0x1002);
                    break;
                case 1:
                    noticeText = TextId(ram, 0x2000);
                    questionText = TextId(ram, 0x2002);
                    break;
                case 2:
                    noticeText = TextId(ram, 0x3000);
                    questionText = TextId(ram, 0x3002);
                    break;
                }
                switch (beNDMWLoadCtrl2CommonIntf__StepNoticeQuestion(common, ram->_ramNo, mesWin, noticeText, questionText, 0, 3)) {
                case 0:
                    break;
                case 1:
                    SetStageStep(cardWork, 2);
                    return;
                case 2:
                    EnterStage(cardWork, STAGE_UTIL_DONE);
                    cardWork->_utilReturn = 1;
                    return;
                }
                break;
            case 2:
                switch (cardWork->_sysStat2) {
                case 0:
                    ((beSystem *)self->_system_)->_isResetEnable = 0;
                    NextStageSubstep(cardWork);
                    return;
                case 1:
                    result = beNDMWLoadCtrl2CommonIntf__StepCreateSaveFile(common, ram->_ramNo, mesWin, selSlot->_mcSelPoint, 3);
                    switch (result) {
                    case 0:
                        break;
                    case 1:
                        SetStageStep(cardWork, 5);
                        break;
                    case 2:
                        switch ((((beNDMWMcUtilCtrl *)(common->_mcUtilCtrl))->_result) - 3) {
                        case 4:
                            SetStageStep(cardWork, 3);
                            break;
                        case 6:
                        case 7:
                            EnterStage(cardWork, STAGE_UTIL_ERROR);
                            cardWork->_utilReturn = 1;
                            break;
                        case 0:
                        case 1:
                        case 2:
                        case 3:
                        case 5:
                        case 8:
                        case 9:
                        default:
                            EnterStage(cardWork, STAGE_UTIL_ERROR);
                            cardWork->_utilReturn = 1;
                            break;
                        }
                        break;
                    }
                    if (result != 0) {
                        ((beSystem *)self->_system_)->_isResetEnable = 1;
                        return;
                    }
                    break;
                }
                break;
            case 3:
                if (((beNDMWMcSlot *)(ObjectList_GetAt_003e9260(((beNDMWMcUtilCtrl *)(common->_mcUtilCtrl))->_slot, selSlot->_mcSelPoint)))->_isConnect != 1) {
                    beNDMWLoadIntf2MesWin__Cancel(mesWin);
                    EnterStage(cardWork, STAGE_UTIL_DONE);
                    cardWork->_utilReturn = 2;
                    return;
                }
                noticeText = -1;
                questionText = -1;
                switch (common->_kindHard) {
                case 0:
                    noticeText = TextId(ram, 0x1005);
                    questionText = TextId(ram, 0x1007);
                    break;
                case 1:
                    noticeText = TextId(ram, 0x2005);
                    questionText = TextId(ram, 0x2007);
                    break;
                case 2:
                    noticeText = TextId(ram, 0x3005);
                    questionText = TextId(ram, 0x3007);
                    break;
                }
                switch (beNDMWLoadCtrl2CommonIntf__StepNoticeQuestion(common, ram->_ramNo, mesWin, noticeText, questionText, 1, 3)) {
                case 0:
                    break;
                case 1:
                    SetStageStep(cardWork, 4);
                    return;
                case 2:
                    EnterStage(cardWork, STAGE_UTIL_DONE);
                    cardWork->_utilReturn = 1;
                    return;
                }
                break;
            case 4:
                switch (cardWork->_sysStat2) {
                case 0:
                    textId = -1;
                    switch (common->_kindHard) {
                    case 0:
                        textId = TextId(ram, 0x1008);
                        break;
                    case 1:
                        textId = TextId(ram, 0x2008);
                        break;
                    case 2:
                        textId = TextId(ram, 0x3008);
                        break;
                    }
                    beNDMWLoadIntf2MesWin__RequestMessage(mesWin, textId);
                    ((beSystem *)self->_system_)->_isResetEnable = 0;
                    NextStageSubstep(cardWork);
                    return;
                case 1:
                    result = beNDMWLoadCtrl2CommonIntf__StepFormatMemoryCard(common, ram->_ramNo, mesWin, selSlot->_mcSelPoint, 3);
                    switch (result) {
                    case 0:
                        break;
                    case 1:
                        SetStageStep(cardWork, 1);
                        break;
                    case 2:
                        switch ((((beNDMWMcUtilCtrl *)(common->_mcUtilCtrl))->_result) - 3) {
                        case 9:
                            EnterStage(cardWork, STAGE_UTIL_ERROR);
                            cardWork->_utilReturn = 2;
                            break;
                        case 0:
                        case 1:
                        case 2:
                        case 3:
                        case 4:
                        case 5:
                        case 6:
                        case 7:
                        case 8:
                        default:
                            cardWork->_utilReturn = 2;
                            EnterStage(cardWork, STAGE_UTIL_ERROR);
                            break;
                        }
                        break;
                    }
                    if (result != 0) {
                        ((beSystem *)self->_system_)->_isResetEnable = 1;
                        return;
                    }
                    break;
                }
                break;
            case 5:
                slotPlayer = (void *)(0);
                for (slot = 0; slot < ((beNDMWLoadSlotPlayerList *)(*(int *)&common->_slotSaveData))->_count; slot++) {
                    beNDMWLoadSlotPlayer *candidate = (beNDMWLoadSlotPlayer *)ObjectList_GetAt_003e9260((common->_slotSaveData), slot);
                    if (candidate->_connectNO == selSlot->_mcSelPoint) {
                        slotPlayer = (void *)(ObjectList_GetAt_003e9260((common->_slotSaveData), slot));
                        break;
                    }
                }
                if (slotPlayer == 0) {
                    if (((beNDMWMcUtilCtrl *)(common->_mcUtilCtrl))->_isUseUtil != 0) {
                        NextStageStep(cardWork);
                        return;
                    }
                } else {
                    accessList = (AccessList *)(((beNDMWLoadSlotPlayer *)(slotPlayer))->_accessPlList);
                    accessPlayer = ram->_ramNo;
                    accessCount = accessList->count;
                    if (accessCount < accessList->capacity) {
                        accessList->count = (accessList->getCount() + 1);
                    } else {
                        List_Resize(accessList, accessCount + 1, 4);
                    }
                    ((int *)DataList_GetData_003e9090(accessList))[accessCount] = accessPlayer;
                    cardWork->_haveSaveData = (int)(slotPlayer);
                    EnterStage(cardWork, STAGE_UTIL_DONE);
                    cardWork->_utilReturn = 0;
                    return;
                }
                break;
            case 6:
                switch (beNDMWLoadCtrl2CommonIntf__StepReadMedia(common, ram->_ramNo, mesWin, selSlot->_mcSelPoint, 3)) {
                case 0:
                    break;
                case 1:
                    EnterStage(cardWork, STAGE_UTIL_DONE);
                    cardWork->_utilReturn = 0;
                    return;
                case 2:
                    switch ((((beNDMWMcUtilCtrl *)(common->_mcUtilCtrl))->_result) - 3) {
                    case 4:
                        SetStageStep(cardWork, 3);
                        return;
                    case 6:
                    case 7:
                        EnterStage(cardWork, STAGE_UTIL_ERROR);
                        cardWork->_utilReturn = 1;
                        return;
                    case 5:
                        NextStageStep(cardWork);
                        return;
                    case 0:
                    case 1:
                    case 2:
                    case 3:
                    case 8:
                    case 9:
                    default:
                        EnterStage(cardWork, STAGE_UTIL_ERROR);
                        cardWork->_utilReturn = 1;
                        return;
                    }
                    break;
                }
                break;
            case 7:
                if (((beNDMWMcSlot *)(ObjectList_GetAt_003e9260(((beNDMWMcUtilCtrl *)(common->_mcUtilCtrl))->_slot, selSlot->_mcSelPoint)))->_isConnect != 1) {
                    beNDMWLoadIntf2MesWin__Cancel(mesWin);
                    EnterStage(cardWork, STAGE_UTIL_DONE);
                    cardWork->_utilReturn = 2;
                    return;
                }
                switch (cardWork->_sysStat2) {
                case 0:
                    textId = -1;
                    switch (common->_kindHard) {
                    case 0:
                        textId = TextId(ram, 0x102B);
                        break;
                    case 1:
                        textId = TextId(ram, 0x202B);
                        break;
                    case 2:
                        textId = TextId(ram, 0x302B);
                        break;
                    }
                    beNDMWLoadIntf2MesWin__RequestPrompt(mesWin, textId);
                    NextStageSubstep(cardWork);
                    return;
                case 1:
                    if (!(beNDMWLoadIntf2MesWin__GetIsCtrl(mesWin) & 0xFF)) {
                        NextStageSubstep(cardWork);
                        return;
                    }
                    break;
                case 2:
                    textId = -1;
                    switch (common->_kindHard) {
                    case 0:
                        textId = TextId(ram, 0x102C);
                        break;
                    case 1:
                        textId = TextId(ram, 0x202C);
                        break;
                    case 2:
                        textId = TextId(ram, 0x302C);
                        break;
                    }
                    beNDMWLoadIntf2MesWin__RequestPrompt(mesWin, textId);
                    NextStageSubstep(cardWork);
                    return;
                case 3:
                    if (!(beNDMWLoadIntf2MesWin__GetIsCtrl(mesWin) & 0xFF)) {
                        NextStageSubstep(cardWork);
                        return;
                    }
                    break;
                case 4:
                    textId = -1;
                    switch (common->_kindHard) {
                    case 0:
                        textId = TextId(ram, 0x102D);
                        break;
                    case 1:
                        textId = TextId(ram, 0x202D);
                        break;
                    case 2:
                        textId = TextId(ram, 0x302D);
                        break;
                    }
                    beNDMWLoadIntf2MesWin__RequestQuestion(mesWin, textId, 0);
                    NextStageSubstep(cardWork);
                    return;
                case 5:
                    if (!(beNDMWLoadIntf2MesWin__GetIsCtrl(mesWin) & 0xFF)) {
                        switch (beNDMWLoadIntf2MesWin__GetCurPoint(mesWin)) {
                        case 0:
                            NextStageSubstep(cardWork);
                            return;
                        case 1:
                            cardWork->_utilReturn = 1;
                            EnterStage(cardWork, STAGE_UTIL_DONE);
                            return;
                        }
                    }
                    break;
                case 6:
                    {
                    allocator = AllocatorChoice::Select(&kIGMemoryPoolHandleUser1[0], igObject_GetAllocator(self));
                    CreatedRef<1> newSlotPlayer((void *)(beNDMWLoadSlotPlayer_Create(allocator)));
                    degiIndex = 0;
                    do {
                        allocator = AllocatorChoice::Select(&kIGMemoryPoolHandleUser1[0], igObject_GetAllocator(self));
                        {
                        CreatedRef<0> degiData((void *)(beNDMWDegiData_Create(allocator)));
                        ObjectList_AppendRetained(((beNDMWLoadSlotPlayer *)(newSlotPlayer.value))->_saveDataList, degiData.value);
                        }
                        degiIndex += 1;
                    } while (degiIndex < 4);
                    degiIndex = 0;
                    do {
                        ((beNDMWDegiData *)(ObjectList_GetAt_003e9260(((beNDMWLoadSlotPlayer *)(newSlotPlayer.value))->_saveDataList, degiIndex)))->_isUse = 0;
                        degiIndex += 1;
                    } while (degiIndex < 4);
                    ((beNDMWLoadSlotPlayer *)(newSlotPlayer.value))->_connectNO = (int)((int) selSlot->_mcSelPoint);
                    newAccessPlayer = ram->_ramNo;
                    accessList = (AccessList *)(((beNDMWLoadSlotPlayer *)(newSlotPlayer.value))->_accessPlList);
                    newAccessCount = accessList->count;
                    if (newAccessCount < accessList->capacity) {
                        accessList->count = (accessList->getCount() + 1);
                    } else {
                        List_Resize(accessList, newAccessCount + 1, 4);
                    }
                    ((int *)DataList_GetData_003e9090(accessList))[newAccessCount] = newAccessPlayer;
                    ObjectList_AppendRetained((common->_slotSaveData), newSlotPlayer.value);
                    cardWork->_haveSaveData = (int)(newSlotPlayer.value);
                    }
                    cardWork->_utilReturn = 0;
                    EnterStage(cardWork, STAGE_UTIL_DONE);
                    return;
                }
                break;
            }
            break;
        case STAGE_UTIL_ERROR:
            errorWork = (beNDMWLoadSavePlWork *)(ObjectList_GetAt_003e9260(common->_flagWork, ram->_ramNo));
            if (common->_kindHard == 2) {
                beNDMWLoadIntf2SelSlot__UpdateSelection(selSlot, 0, 0);
            }
            switch (errorWork->_sysStat1) {
            case 0:
            switch (errorWork->_sysStat2) {
            case 0:
                mcUtil = (beNDMWMcUtilCtrl *)(common->_mcUtilCtrl);
                if (mcUtil->_isFormatRun == 1) {
                    if (mcUtil->_result == 0xC) {
                        beNDMWLoadIntf2SelSlot__RefreshSlotMarks(selSlot, selSlot->_mcSelPoint);
                    } else {
                        beNDMWLoadIntf2SelSlot__RefreshSlotMarks(selSlot, -1);
                    }
                    textId = -1;
                    switch (common->_kindHard) {
                    case 0:
                        textId = TextId(ram, 0x100E);
                        break;
                    case 1:
                        textId = TextId(ram, 0x200E);
                        break;
                    case 2:
                        textId = TextId(ram, 0x300E);
                        break;
                    }
                    beNDMWLoadIntf2MesWin__RequestPrompt(mesWin, textId);
                } else if (((beNDMWMcSlot *)(ObjectList_GetAt_003e9260(mcUtil->_slot, selSlot->_mcSelPoint)))->_isConnect == 1) {
                    cardResult = ((beNDMWMcUtilCtrl *)(common->_mcUtilCtrl))->_result;
                    if (common->_kindHard != 2) {
                        if (cardResult == 0xC) {
                            beNDMWLoadIntf2SelSlot__RefreshSlotMarks(selSlot, selSlot->_mcSelPoint);
                        } else {
                            beNDMWLoadIntf2SelSlot__RefreshSlotMarks(selSlot, -1);
                        }
                    }
                    switch (cardResult - 3) {
                    case 4:
                        textId = -1;
                        switch (common->_kindHard) {
                        case 0:
                            textId = TextId(ram, 0x1012);
                            break;
                        case 1:
                            textId = TextId(ram, 0x2012);
                            break;
                        case 2:
                            textId = TextId(ram, 0x3012);
                            break;
                        }
                        beNDMWLoadIntf2MesWin__RequestPrompt(mesWin, textId);
                        break;
                    case 6:
                        textId = -1;
                        switch (common->_kindHard) {
                        case 0:
                            textId = TextId(ram, 0x1014);
                            break;
                        case 1:
                            textId = TextId(ram, 0x2014);
                            break;
                        case 2:
                            textId = TextId(ram, 0x3014);
                            break;
                        }
                        beNDMWLoadIntf2MesWin__RequestPrompt(mesWin, textId);
                        break;
                    case 7:
                        textId = -1;
                        switch (common->_kindHard) {
                        case 0:
                            textId = TextId(ram, 0x1015);
                            break;
                        case 1:
                            textId = TextId(ram, 0x2015);
                            break;
                        case 2:
                            textId = TextId(ram, 0x3015);
                            break;
                        }
                        beNDMWLoadIntf2MesWin__RequestPrompt(mesWin, textId);
                        break;
                    case 2:
                        textId = -1;
                        switch (common->_kindHard) {
                        case 0:
                            textId = TextId(ram, 0x1010);
                            break;
                        case 1:
                            textId = TextId(ram, 0x2010);
                            break;
                        case 2:
                            textId = TextId(ram, 0x3010);
                            break;
                        }
                        beNDMWLoadIntf2MesWin__RequestPrompt(mesWin, textId);
                        break;
                    case 3:
                        textId = -1;
                        switch (common->_kindHard) {
                        case 0:
                            textId = TextId(ram, 0x1011);
                            break;
                        case 1:
                            textId = TextId(ram, 0x2011);
                            break;
                        case 2:
                            textId = TextId(ram, 0x3011);
                            break;
                        }
                        beNDMWLoadIntf2MesWin__RequestPrompt(mesWin, textId);
                        break;
                    case 5:
                        textId = -1;
                        switch (common->_kindHard) {
                        case 0:
                            textId = TextId(ram, 0x1013);
                            break;
                        case 1:
                            textId = TextId(ram, 0x2013);
                            break;
                        case 2:
                            textId = TextId(ram, 0x3013);
                            break;
                        }
                        beNDMWLoadIntf2MesWin__RequestPrompt(mesWin, textId);
                        break;
                    case 9:
                        textId = -1;
                        switch (common->_kindHard) {
                        case 0:
                            textId = TextId(ram, 0x1016);
                            break;
                        case 1:
                            textId = TextId(ram, 0x2016);
                            break;
                        case 2:
                            textId = TextId(ram, 0x3016);
                            break;
                        }
                        beNDMWLoadIntf2MesWin__RequestPrompt(mesWin, textId);
                        break;
                    case 1:
                        textId = -1;
                        switch (common->_kindHard) {
                        case 0:
                            textId = TextId(ram, 0x100F);
                            break;
                        case 1:
                            textId = TextId(ram, 0x200F);
                            break;
                        case 2:
                            textId = TextId(ram, 0x300F);
                            break;
                        }
                        beNDMWLoadIntf2MesWin__RequestPrompt(mesWin, textId);
                        break;
                    case 0:
                    case 8:
                    default:
                        textId = -1;
                        switch (common->_kindHard) {
                        case 0:
                            textId = TextId(ram, 0x100E);
                            break;
                        case 1:
                            textId = TextId(ram, 0x200E);
                            break;
                        case 2:
                            textId = TextId(ram, 0x300E);
                            break;
                        }
                        beNDMWLoadIntf2MesWin__RequestPrompt(mesWin, textId);
                        break;
                    }
                } else {
                    if (common->_kindHard != 2) {
                        beNDMWLoadIntf2SelSlot__RefreshSlotMarks(selSlot, selSlot->_mcSelPoint);
                    }
                    textId = -1;
                    switch (common->_kindHard) {
                    case 0:
                        textId = TextId(ram, 0x1016);
                        break;
                    case 1:
                        textId = TextId(ram, 0x2016);
                        break;
                    case 2:
                        textId = TextId(ram, 0x3016);
                        break;
                    }
                    beNDMWLoadIntf2MesWin__RequestPrompt(mesWin, textId);
                }
                NextStageSubstep(errorWork);
                return;
            case 1:
                if (!(beNDMWLoadIntf2MesWin__GetIsCtrl(mesWin) & 0xFF)) {
                    errorWork->_utilReturn = 1;
                    EnterStage(errorWork, STAGE_UTIL_DONE);
                    return;
                }
                break;
            }
            break;
            }
            break;
        case STAGE_UTIL_DONE:
            index = 0;
            do {
                work = (beNDMWLoadSavePlWork *)(DataList_GetWordAt_003e9240(common->_flagWork, index));
                index += 1;
                EnterStage(work, STAGE_RESUME);
            } while (index < 4);
            return;
        case STAGE_RESUME:
            beNDMWLoadIntf2MesWin__EndSystemMessage(mesWin);
            EnterStage(((beNDMWLoadSavePlWork *)(DataList_GetWordAt_003e9240(common->_flagWork, ram->_ramNo))), 0);
            { beNDMWLoadSavePlWork *work = (beNDMWLoadSavePlWork *)ObjectList_GetAt_003e9260(common->_flagWork, ram->_ramNo); work->_isCtrl = 1; }
            break;
        }
    }
}

int beNDMWSaveIntf_GetInfoMeta(void)
{
    return g_beNDMWSaveIntfInfo_metaObject[0];
}

void beNDMWSaveIntf_RegisterReceivers(beNDMWSaveIntf *self, beBaseInfoRam *ram) {
    beMessenger_RegisterReceiverFromInfo(self->_messenger, ram, SAVEINTF_ALL);
    beMessenger_RegisterReceiver(self->_messenger, ram, SAVEINTF, 0, ram->_ramNo);
}

int beNDMWSaveIntf_OnMessage(beNDMWSaveIntf *self, beBaseInfoRam *ram, MessageArg *message) {
    unsigned int command = beMessenger_ResolveEnumValue(self->_messenger, beNDMWSaveIntf_GetMessageEnum(), message->enumName);
    if (command == MSG_GENERATE) {
        if (ram->_dataList == 0) {
            int allocator = AllocatorChoice::Select(&kIGMemoryPoolHandleUser1[0], igObject_GetAllocator(self));
            ChildRef<0> list((RefObject *)beBaseInfoDataList_Create(allocator)); RefObject *created; RefObject *old;
            created = list.object; if (created != 0) created->refCount = created->refCount + 1;
            old = (RefObject *)ram->_dataList;
            if (old != 0) { old->refCount = old->refCount - 1; if (((unsigned long long)((long long)old->refCount << 0x29) >> 0x29) == 0) igObject_Destroy(old); }
            ram->_dataList = (int)created;
            self->_system_ = ((int)igInsightCore_FindManager(self->_insight, g_beSystem_metaObject[0]));
            {
                int allocator = AllocatorChoice::Select(&kIGMemoryPoolHandleUser1[0], igObject_GetAllocator(self));
                ChildRef<1> ctrlData((RefObject *)beNDMWSaveIntfCtrlData_Create(allocator));
                ObjectList_AppendRetained(ram->_dataList, ctrlData.object);
                ((beNDMWSaveIntfCtrlData *)ctrlData.object)->_isRun = 1;
                if (ram->_ramNo == 0) {
                    ((beNDMWSaveIntfCtrlData *)ctrlData.object)->_isRdy = 0;
                    ((beNDMWSaveIntfCtrlData *)ctrlData.object)->_isEntry = 1;
                    ((beNDMWSaveIntfCtrlData *)ctrlData.object)->_isCtrl = 1;
                } else {
                    ((beNDMWSaveIntfCtrlData *)ctrlData.object)->_isRdy = 0;
                    ((beNDMWSaveIntfCtrlData *)ctrlData.object)->_isEntry = 0;
                    ((beNDMWSaveIntfCtrlData *)ctrlData.object)->_isCtrl = 1;
                }
            }
            beMessenger_SendNamed(self->_messenger, SAVECTRL, 0, 0, GETCOMMON_4);
            ObjectList_AppendRetained(ram->_dataList, beMessenger_GetObject(self->_messenger, 0));
            {
                int allocator = AllocatorChoice::Select(&kIGMemoryPoolHandleUser1[0], igObject_GetAllocator(self));
                ChildRef<2> textOrder((RefObject *)beNDMWLoadIntf2TextOrder_Create(allocator));
                ((beNDMWLoadIntf2TextOrder *)textOrder.object)->_messenger = self->_messenger;
                beNDMWLoadIntf2TextOrder *order = (beNDMWLoadIntf2TextOrder *)textOrder.object;
                order->_lua = ((int)igInsightCore_FindManager(self->_insight, g_beLua_metaObject[0]));
                ObjectList_AppendRetained(ram->_dataList, textOrder.object);
            }
            {
                int allocator = AllocatorChoice::Select(&kIGMemoryPoolHandleUser1[0], igObject_GetAllocator(self));
                ChildRef<3> model((RefObject *)beNDMWLoadIntf2ComMdlCtrl_Create(allocator));
                ObjectList_AppendRetained(ram->_dataList, model.object);
                ((beNDMWLoadIntf2ComMdlCtrl *)model.object)->_messenger = self->_messenger;
                int player = ram->_ramNo;
                beNDMWLoadIntf2ComMdlCtrl *modelCtrl = (beNDMWLoadIntf2ComMdlCtrl *)model.object;
                float x, y, z;
                z = g_saveModelPlacement[player].z;
                y = g_saveModelPlacement[player].y;
                x = g_saveModelPlacement[player].x;
                modelCtrl->_pos[0] = x;
                modelCtrl->_pos[1] = y;
                modelCtrl->_pos[2] = z;
            }
            {
                int allocator = AllocatorChoice::Select(&kIGMemoryPoolHandleUser1[0], igObject_GetAllocator(self));
                ChildRef<4> window((RefObject *)beNDMWLoadIntf2MesWin_Create(allocator));
                ((beNDMWLoadIntf2MesWin *)window.object)->_ramNo = ram->_ramNo;
                ((beNDMWLoadIntf2MesWin *)window.object)->_messenger = self->_messenger;
                ((beNDMWLoadIntf2MesWin *)window.object)->_padManager = ((int)igInsightCore_FindManager(self->_insight, g_bePadManager_metaObject[0]));
                ObjectList_AppendRetained(ram->_dataList, window.object);
                DataListGuard::Ensure(ram);
                ((beNDMWLoadIntf2MesWin *)window.object)->_textOrder = (int)igProperty_FindByName(ram->_dataList, g_propertyNameField[0], TEXTORDER_3);
            }
            {
                int allocator = AllocatorChoice::Select(&kIGMemoryPoolHandleUser1[0], igObject_GetAllocator(self));
                ChildRef<5> slots((RefObject *)beNDMWLoadIntf2SelSlot_Create(allocator));
                ((beNDMWLoadIntf2SelSlot *)slots.object)->_ramNo = ram->_ramNo;
                ((beNDMWLoadIntf2SelSlot *)slots.object)->_messenger = self->_messenger;
                ((beNDMWLoadIntf2SelSlot *)slots.object)->_padManager = ((int)igInsightCore_FindManager(self->_insight, g_bePadManager_metaObject[0]));
                DataListGuard::Ensure(ram);
                ((beNDMWLoadIntf2SelSlot *)slots.object)->_comMdlCtrl = (int)igProperty_FindByName(ram->_dataList, g_propertyNameField[0], COMMDLCTRL_3);
                DataListGuard::Ensure(ram);
                ((beNDMWLoadIntf2SelSlot *)slots.object)->_textOrder = (int)igProperty_FindByName(ram->_dataList, g_propertyNameField[0], TEXTORDER_3);
                DataListGuard::Ensure(ram);
                ((beNDMWLoadIntf2SelSlot *)slots.object)->_commonIntf = (int)igProperty_FindByName(ram->_dataList, g_propertyNameField[0], COMMONINTF_2);
                ObjectList_AppendRetained(ram->_dataList, slots.object);
            }
            {
                int allocator = AllocatorChoice::Select(&kIGMemoryPoolHandleUser1[0], igObject_GetAllocator(self));
                ChildRef<6> stateCtrl((RefObject *)beNDMWLoadIntf2DegiStateCtrl_Create(allocator));
                {
                    int allocator2 = AllocatorChoice::Select(&kIGMemoryPoolHandleUser1[0], igObject_GetAllocator(self));
                    ChildRef<7> upperState((RefObject *)beNDMWLoadIntf2DegiState_Create(allocator2));
                    DataListGuard::Ensure(ram);
                    void *commonIntf = igProperty_FindByName(ram->_dataList, g_propertyNameField[0], COMMONINTF_2);
                    DataListGuard::Ensure(ram);
                    void *textOrderObj = igProperty_FindByName(ram->_dataList, g_propertyNameField[0], TEXTORDER_3);
                    DataListGuard::Ensure(ram);
                    beNDMWLoadIntf2DegiState__Init(upperState.object, ram->_ramNo, commonIntf, textOrderObj, igProperty_FindByName(ram->_dataList, g_propertyNameField[0], COMMDLCTRL_3), self->_messenger, 0);
                    ObjectList_AppendRetained(((beNDMWLoadIntf2DegiStateCtrl *)stateCtrl.object)->_statDataList, upperState.object);
                }
                {
                    int allocator2 = AllocatorChoice::Select(&kIGMemoryPoolHandleUser1[0], igObject_GetAllocator(self));
                    ChildRef<7> lowerState((RefObject *)beNDMWLoadIntf2DegiState_Create(allocator2));
                    DataListGuard::Ensure(ram);
                    void *commonIntf = igProperty_FindByName(ram->_dataList, g_propertyNameField[0], COMMONINTF_2);
                    DataListGuard::Ensure(ram);
                    void *textOrderObj = igProperty_FindByName(ram->_dataList, g_propertyNameField[0], TEXTORDER_3);
                    DataListGuard::Ensure(ram);
                    beNDMWLoadIntf2DegiState__Init(lowerState.object, ram->_ramNo, commonIntf, textOrderObj, igProperty_FindByName(ram->_dataList, g_propertyNameField[0], COMMDLCTRL_3), self->_messenger, 1);
                    ObjectList_AppendRetained(((beNDMWLoadIntf2DegiStateCtrl *)stateCtrl.object)->_statDataList, lowerState.object);
                }
                ObjectList_AppendRetained(ram->_dataList, stateCtrl.object);
            }
            {
                int allocator = AllocatorChoice::Select(&kIGMemoryPoolHandleUser1[0], igObject_GetAllocator(self));
                ChildRef<8> dataSel((RefObject *)beNDMWLoadIntf2DataSelIntf_Create(allocator));
                ((beNDMWLoadIntf2DataSelIntf *)dataSel.object)->_padManager = ((int)igInsightCore_FindManager(self->_insight, g_bePadManager_metaObject[0]));
                DataListGuard::Ensure(ram);
                ((beNDMWLoadIntf2DataSelIntf *)dataSel.object)->_comMdlCtrl = (int)igProperty_FindByName(ram->_dataList, g_propertyNameField[0], COMMDLCTRL_3);
                DataListGuard::Ensure(ram);
                ((beNDMWLoadIntf2DataSelIntf *)dataSel.object)->_textOrder = (int)igProperty_FindByName(ram->_dataList, g_propertyNameField[0], TEXTORDER_3);
                DataListGuard::Ensure(ram);
                ((beNDMWLoadIntf2DataSelIntf *)dataSel.object)->_commonIntf = (int)igProperty_FindByName(ram->_dataList, g_propertyNameField[0], COMMONINTF_2);
                DataListGuard::Ensure(ram);
                ((beNDMWLoadIntf2DataSelIntf *)dataSel.object)->_mesWin = (int)igProperty_FindByName(ram->_dataList, g_propertyNameField[0], MESWIN_2);
                DataListGuard::Ensure(ram);
                ((beNDMWLoadIntf2DataSelIntf *)dataSel.object)->_statDisp = (int)igProperty_FindByName(ram->_dataList, g_propertyNameField[0], DEGISTATECTRL_2);
                ObjectList_AppendRetained(ram->_dataList, dataSel.object);
            }
        }
        return 1;
    }
    if (ram->_dataList == 0) {
        return 1;
    }
    DataListGuard::Ensure(ram);
    beNDMWSaveIntfCtrlData *ctrl = (beNDMWSaveIntfCtrlData *)igProperty_FindByName(ram->_dataList, g_propertyNameField[0], CTRL_3);
    switch (command) {
    case MSG_LINKCOMMON:
        ObjectList_AppendRetained(ram->_dataList, beMessenger_GetObject(self->_messenger, 0));
        return 1;
    case MSG_ISENTRY:
        if (beMessenger_GetIntCount(self->_messenger) == 0) {
            beMessenger_AppendInt(self->_messenger, 0);
        }
        if (ctrl->_isEntry == 1) {
            beMessenger_SetInt(self->_messenger, 0, beMessenger_GetInt(self->_messenger, 0) + 1);
        }
        return 1;
    case MSG_ISRDY:
        if (beMessenger_GetIntCount(self->_messenger) == 0) {
            beMessenger_AppendInt(self->_messenger, 0);
        }
        if (ctrl->_isRdy == 1) {
            beMessenger_SetInt(self->_messenger, 0, beMessenger_GetInt(self->_messenger, 0) + 1);
        }
        return 1;
    case MSG_ONCTRL:
        ctrl->_isCtrl = 1;
        return 1;
    case MSG_OFFCTRL:
        ctrl->_isCtrl = 0;
        return 1;
    case MSG_SETSELECT_DATA:
        DataListGuard::Ensure(ram);
        {
            beNDMWLoadCtrl2CommonIntf *common = (beNDMWLoadCtrl2CommonIntf *)igProperty_FindByName(ram->_dataList, g_propertyNameField[0], COMMONINTF_2);
            if (((beNDMWLoadSavePlWork **)((beNDMWLoadSavePlWorkList *)common->_flagWork)->_data)[ram->_ramNo]->_isRdy != 1) {
                beMessenger_SelectGroup(self->_messenger, GAMERAM_5);
                beMessenger_AppendInt(self->_messenger, ram->_ramNo);
                beMessenger_DispatchSelected(self->_messenger, GAMEREMOVE);
            }
        }
        return 1;
    default:
        return 0;
    }
}

int beNDMWSaveIntf_GetMeta(void)
{
    return g_beNDMWSaveIntf_metaObject[0];
}

