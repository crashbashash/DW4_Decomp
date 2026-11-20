#include "dw4/support/reflected.h"
#include "dw4/core/igSmartPointer.h"
#include "dw4/core/StringPool.h"
#include "dw4/game/beBaseInfoDataList.h"
#include "dw4/game/beMessenger.h"
#include "dw4/game/ndmw/beNDMWDegiData.h"
#include "dw4/game/ndmw/beNDMWLoadCtrl2CommonIntf.h"
#include "dw4/game/ndmw/beNDMWLoadSavePlWork.h"
#include "dw4/game/ndmw/beNDMWMcUtilCtrl.h"
#include "dw4/game/ndmw/beNDMWSaveCtrl.h"
#include "dw4/game/ndmw/beNDMWSaveCtrlCtrlData.h"
#include "dw4/game/ndmw/beNDMWSaveCtrlInfo.h"
#include "dw4/game/bePadManager.h"
#include "dw4/game/beSystem.h"
#include "dw4/core/igDataLists.h"
#include "dw4/insight/igInsightCore.h"
#include "dw4/core/igMemoryPoolContext.h"
#include "dw4/core/igNamedObject.h"
#include "dw4/core/igObject.h"
#include "dw4/game/beDBManager.h"

#pragma push
#pragma readonly_strings on

#define OWNER_ALLOCATOR(dst, obj) { int alloc = (int)((Gap::Core::igObject *)(obj))->getMemoryPool(); if (g_useOwnerAllocator != 0) { dst = alloc; } else { dst = (int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleUser1); } }
/* The per-player work records of the common interface, and its memory-card utility. */
#define PLW(common, i) (((beNDMWLoadSavePlWork **)((beNDMWLoadSavePlWorkList *)(common)->_flagWork)->_data)[i])
#define MCU(common) ((beNDMWMcUtilCtrl *)(common)->_mcUtilCtrl)


extern "C" void beNDMWSaveCtrl_Prepare(beNDMWSaveCtrl *self);
extern "C" void beNDMWSaveCtrl_UpdateRam(beNDMWSaveCtrl *self, beBaseInfoRam *ram);
extern "C" int beNDMWSaveCtrl_GetInfoMeta(void);
extern "C" void beNDMWSaveCtrl_OnAddRam(beNDMWSaveCtrl *self, int info);
extern "C" int beNDMWSaveCtrl_OnMessage(beNDMWSaveCtrl *self, beBaseInfoRam *ram, beBaseInfo *info);
extern "C" int beNDMWSaveCtrl_GetMeta(void);

/* Owning stack references while the controller list is wired up; each releases its object on scope
 * exit. */
class SaveCtrlDataRef {
public:
    igObject *p;
    SaveCtrlDataRef(igObject *o) : p(o) {}
    ~SaveCtrlDataRef() { igObject *o = p; if (o != 0) { o->_refCount = o->_refCount - 1; if ((o->_refCount & 0x7fffff) == 0) igObject_Destroy(o); } }
};
class CommonIntfRef {
public:
    igObject *p;
    CommonIntfRef(igObject *o) : p(o) {}
    ~CommonIntfRef() { igObject *o = p; if (o != 0) { o->_refCount = o->_refCount - 1; if ((o->_refCount & 0x7fffff) == 0) igObject_Destroy(o); } }
};
class DegiDataRef {
public:
    igObject *p;
    DegiDataRef(igObject *o) : p(o) {}
    ~DegiDataRef() { igObject *o = p; if (o != 0) { o->_refCount = o->_refCount - 1; if ((o->_refCount & 0x7fffff) == 0) igObject_Destroy(o); } }
};
class FlagWorkRef {
public:
    igObject *p;
    FlagWorkRef(igObject *o) : p(o) {}
    ~FlagWorkRef() { igObject *o = p; if (o != 0) { o->_refCount = o->_refCount - 1; if ((o->_refCount & 0x7fffff) == 0) igObject_Destroy(o); } }
};
/* Owning stack reference to a pooled string token (reference count at p[-1], chunk header at p[-2]);
 * releases the token on scope exit. */
class StringRef {
public:
    char *p;
    StringRef(char *s) : p(s) {}
    ~StringRef() { if (p) { int *h = (int *)p - 2; int r = ((int *)p)[-1] - 1; ((int *)p)[-1] = r; if (r == 0) StringChunk_ReleaseHeader((StringChunk *)(void *)*h, (StringTokenHeader *)h); } }
};

/* Releases an object reference, used for the old list during the list install. */
struct ReleaseRef { static inline void Apply(igObject *object) {
    if (object) {
        --object->_refCount;
        if ((object->_refCount & 0x7fffff) == 0)
            igObject_Destroy(object);
    }
} };

/* Drops one reference to a pooled string token. */
static inline void releaseString(char *text) {
    if (text != 0) {
        int *header = (int *)(text - 8);
        int count = header[1] - 1;
        header[1] = count;
        if (count == 0) {
            StringChunk_ReleaseHeader((StringChunk *)(void *)header[0], (StringTokenHeader *)header);
        }
    }
}

/* A ram without a data list gets a fresh beBaseInfoDataList from the owner's or the user pool. */
static inline void ensureDataList(beBaseInfoRam *ram) {
    if (ram->_dataList == 0) {
        int a;
        OWNER_ALLOCATOR(a, ram);
        igSmartPointer<igObject> list(beBaseInfoDataList_Create(a));
        igObject *t = list.p;
        if (t != 0) t->_refCount++;
        ReleaseRef::Apply((igObject *)ram->_dataList);
        ram->_dataList = (int)t;
    }
}

static inline int st1(const beNDMWSaveCtrlCtrlData *data) { return data->_st1; }

void beNDMWSaveCtrl_Prepare(beNDMWSaveCtrl *self) {
    igObject *found;
    igObject *previous;

    if (self->_padManager == 0) {
        found = igInsightCore_FindManager((igInsightCore *)self->_insight, g_bePadManager_metaObject);
        if (found != 0) {
            found->_refCount = found->_refCount + 1;
        }
        previous = (igObject *)self->_padManager;
        if (previous != 0) {
            previous->_refCount = previous->_refCount - 1;
            if ((previous->_refCount & 0x7FFFFF) == 0) {
                igObject_Destroy(previous);
            }
        }
        self->_padManager = (int)found;
    }
}

/* Steps the save controller: asks for the controller list while the ram has none, then runs the ctrl
 * data through its states. _st0 1 starts the memory-card utility and waits for it, 2 runs the save
 * screen (the model controller's sequences, the save interfaces, their closing and the hand-off of the
 * player data to GAMERAM) and 3 removes the utility again and sends the game on to the next stage. */
void beNDMWSaveCtrl_UpdateRam(beNDMWSaveCtrl *self, beBaseInfoRam *ram) {
    beNDMWSaveCtrlCtrlData *ctrl;
    beNDMWLoadCtrl2CommonIntf *common;
    int i;
    int playerCount;
    unsigned char allClosed;
    int j;
    beNDMWLoadSavePlWorkList *flagWork;
    int k;
    int readyCount;
    int m;
    beNDMWLoadSavePlWorkList *flagList;
    igObject *gameCommon;

    if (ram->_dataList == 0) {
        beMessenger_SendNamed((beMessenger *)self->_messenger, "SAVECTRL", 0, -1, "GENERATE");
        return;
    }
    ensureDataList(ram);
    ctrl = (beNDMWSaveCtrlCtrlData *)igProperty_FindByName((igObjectList *)ram->_dataList, g_propertyNameField, "CTRL");
    ensureDataList(ram);
    common = (beNDMWLoadCtrl2CommonIntf *)igProperty_FindByName((igObjectList *)ram->_dataList, g_propertyNameField, "COMMONINTF");
    switch (ctrl->_st0) {
    case 0:
        break;
    case 1:
        switch (ctrl->_st1) {
        case 0:
            beNDMWMcUtilCtrl__Generate(MCU(common));
            ctrl->_st1 = ctrl->_st1 + 1;
            ctrl->_st3 = 0;
            ctrl->_st2 = 0;
            break;
        case 1:
            if (beNDMWMcUtilCtrl__CheckReady(MCU(common)) == 1) {
                ctrl->_st0 = 2;
                ctrl->_st3 = 0;
                ctrl->_st2 = 0;
                ctrl->_st1 = 0;
            }
            break;
        }
        break;
    case 2:
        switch (st1(ctrl)) {
        case 0:
            beMessenger_SendNamed((beMessenger *)self->_messenger, "MODELCTRL", "j_chrselback", 0, "GENERATE");
            beMessenger_SendNamed((beMessenger *)self->_messenger, "MODELCTRL", "j_chrselback", 0, "SQ_OPEN");
            ctrl->_st1 = ctrl->_st1 + 1;
            ctrl->_st3 = 0;
            ctrl->_st2 = 0;
            break;
        case 1:
            beMessenger_SelectReceivers((beMessenger *)self->_messenger, "MODELCTRL", "j_chrselback", 0);
            beMessenger_AppendString((beMessenger *)self->_messenger, "SQ_OPEN");
            beMessenger_DispatchSelected((beMessenger *)self->_messenger, "ISSEQNAME");
            if (beMessenger_GetBool((beMessenger *)self->_messenger, 0) == 0) {
                ctrl->_st1 = ctrl->_st1 + 1;
                ctrl->_st3 = 0;
                ctrl->_st2 = 0;
            }
            break;
        case 2:
            beMessenger_SendNamed((beMessenger *)self->_messenger, "SAVEINTF_ALL", 0, -1, "GENERATE");
            ctrl->_st1 = ctrl->_st1 + 1;
            ctrl->_st3 = 0;
            ctrl->_st2 = 0;
            break;
        case 3:
            switch (common->_intfStat) {
            case 0:
                beNDMWLoadCtrl2CommonIntf__UpdateCutConnect(common);
                break;
            case 2:
                break;
            case 3:
                ctrl->_st1 = ctrl->_st1 + 1;
                ctrl->_st3 = 0;
                ctrl->_st2 = 0;
                break;
            }
            break;
        case 4:
            switch (ctrl->_st2) {
            case 0:
                i = 0;
                do {
                    beNDMWLoadSavePlWork *work;
                    PLW(common, i)->_isClose = 0;
                    work = PLW(common, i);
                    i++;
                    work->_sysStat0 = 2;
                    work->_sysStat3 = 0;
                    work->_sysStat2 = 0;
                    work->_sysStat1 = 0;
                } while (i < 4);
                ctrl->_st2 = ctrl->_st2 + 1;
                ctrl->_st3 = 0;
                break;
            case 1:
                allClosed = 1;
                j = 0;
                flagWork = (beNDMWLoadSavePlWorkList *)common->_flagWork;
                do {
                    if (((beNDMWLoadSavePlWork **)flagWork->_data)[j]->_isClose != 1) { allClosed = 0; break; }
                    j++;
                    flagWork = (beNDMWLoadSavePlWorkList *)common->_flagWork;
                } while (j < 4);
                if (allClosed == 1) {
                    ctrl->_st2 = ctrl->_st2 + 1;
                    ctrl->_st3 = 0;
                }
                break;
            case 2:
                beMessenger_SendNamed((beMessenger *)self->_messenger, "MODELCTRL", "i_fadewn01", 0, "GENERATE");
                beMessenger_SendNamed((beMessenger *)self->_messenger, "MODELCTRL", "i_fadewn01", 0, "SQ_BLOUT30");
                beMessenger_SendNamed((beMessenger *)self->_messenger, "MODELCTRL", "j_chrselback", 0, "SQ_CLOSE");
                ctrl->_st2 = ctrl->_st2 + 1;
                ctrl->_st3 = 0;
                break;
            case 3:
                beMessenger_SendNamed((beMessenger *)self->_messenger, "MODELCTRL", "j_chrselback", 0, "ISRUN");
                if (beMessenger_GetBool((beMessenger *)self->_messenger, 0) == 0) {
                    ctrl->_st2 = ctrl->_st2 + 1;
                    ctrl->_st3 = 0;
                }
                break;
            case 4:
                /* The players who did not join lose their stage chip; the rest are counted into NINZU. */
                beMessenger_SendNamed((beMessenger *)self->_messenger, "SAVEINTF_ALL", 0, -1, "SETSELECT_DATA");
                beMessenger_SendGroup((beMessenger *)self->_messenger, "GAMERAM", "GETCOMMON");
                gameCommon = beMessenger_GetObject((beMessenger *)self->_messenger, 0);
                playerCount = 0;
                for (k = 0; k < 4; k++) {
                    if (PLW(common, k)->_isRdy == 1) {
                        playerCount++;
                    } else {
                        StringRef none(0);
                        igStringRefList *stages = (igStringRefList *)igProperty_GetRecordStringList(gameCommon, "BKCHIPSTAGE")->_data;
                        int count = stages->_count;
                        if (count != 0 && k >= 0 && k < count) {
                            char **slot = (char **)stages->_data + k;
                            if (none.p != 0) ((int *)none.p)[-1] = ((int *)none.p)[-1] + 1;
                            releaseString(*slot);
                            *slot = none.p;
                        }
                    }
                }
                igProperty_GetRecord(gameCommon, "NINZU")->_data = playerCount;
                ctrl->_st0 = 3;
                ctrl->_st3 = 0;
                ctrl->_st2 = 0;
                ctrl->_st1 = 0;
                break;
            }
            break;
        }
        break;
    case 3:
        switch (ctrl->_st1) {
        case 0:
            beNDMWMcUtilCtrl__Remove(MCU(common));
            ctrl->_st1 = ctrl->_st1 + 1;
            ctrl->_st3 = 0;
            ctrl->_st2 = 0;
            break;
        case 1:
            if (beNDMWMcUtilCtrl__IsRemoved(MCU(common)) == 1) {
                /* matching construct: hand search — the count loop's list load is the out-of-line block
                 * after the return, as retail lays it out */
                readyCount = 0;
                m = 0;
                goto count_start;
            count_body:
                if (((beNDMWLoadSavePlWork **)flagList->_data)[m]->_isRdy == 1) readyCount++;
                m++;
            count_test:
                if (m < 4) goto count_body;
                if (readyCount <= 0) {
                    beMessenger_SelectGroup((beMessenger *)self->_messenger, "STAGECTL");
                    beMessenger_AppendString((beMessenger *)self->_messenger, "stagis10");
                    beMessenger_DispatchSelected((beMessenger *)self->_messenger, "NEXTSTAGE");
                } else {
                    beMessenger_SelectReceivers((beMessenger *)self->_messenger, "PLAYERPOINT", 0, -1);
                    beMessenger_AppendInt((beMessenger *)self->_messenger, 2);
                    beMessenger_DispatchSelected((beMessenger *)self->_messenger, "SETGENERATEPOS");
                    beMessenger_SelectGroup((beMessenger *)self->_messenger, "STAGECTL");
                    beMessenger_AppendString((beMessenger *)self->_messenger, "stagML12");
                    beMessenger_DispatchSelected((beMessenger *)self->_messenger, "NEXTSTAGE");
                }
                ctrl->_st0 = ctrl->_st0 + 1;
                ctrl->_st3 = 0;
                ctrl->_st2 = 0;
                ctrl->_st1 = 0;
            }
            break;
        }
        break;
    }
    return;
count_start:
    flagList = (beNDMWLoadSavePlWorkList *)common->_flagWork;
    goto count_test;
}

int beNDMWSaveCtrl_GetInfoMeta(void)
{
    return (int)g_beNDMWSaveCtrlInfo_metaObject;
}

/* Registers the save controller with its messenger as the SAVECTRL receiver. */
void beNDMWSaveCtrl_OnAddRam(beNDMWSaveCtrl *self, int info)
{
    beMessenger_RegisterReceiverFromInfo((beMessenger *)self->_messenger, (beBaseInfoRam *)info, "SAVECTRL");
}

/* Handles a message to the save controller: 0 builds the controller list (the ctrl data at state 1 and
 * the common interface with four players' data and work records), 3 hands the common interface back. */
int beNDMWSaveCtrl_OnMessage(beNDMWSaveCtrl *self, beBaseInfoRam *ram, beBaseInfo *info) {
    int message;
    int i;
    message = beMessenger_ResolveEnumValue((beMessenger *)self->_messenger, SaveCtrlMessage_GetMetaEnum(), (const char *)info->_dataList);
    if (message == 0) {
        if (ram->_dataList == 0) {
            int a;
            OWNER_ALLOCATOR(a, self);
            {
            igSmartPointer<igObject> list(beBaseInfoDataList_Create(a));
            igObject *t = list.p;
            if (t != 0) t->_refCount++;
            ReleaseRef::Apply((igObject *)ram->_dataList);
            ram->_dataList = (int)t;
            OWNER_ALLOCATOR(a, self);
            {
            SaveCtrlDataRef ctrl(beNDMWSaveCtrlCtrlData_Create(a));
            ObjectList_AppendRetained((igObjectList *)(int)(igObject *)ram->_dataList, (igObject *)(int)ctrl.p);
            beNDMWSaveCtrlCtrlData *o = (beNDMWSaveCtrlCtrlData *)ctrl.p;
            o->_st0 = 1;
            o->_st3 = 0;
            o->_st2 = 0;
            o->_st1 = 0;
            }
            OWNER_ALLOCATOR(a, self);
            {
            CommonIntfRef common(beNDMWLoadCtrl2CommonIntf_Create(a));
            ((beNDMWLoadCtrl2CommonIntf *)common.p)->_system = ((int)igInsightCore_FindManager((igInsightCore *)self->_insight, g_beSystem_metaObject));
            ((beNDMWLoadCtrl2CommonIntf *)common.p)->_inforam = (int)ram;
            ((beNDMWLoadCtrl2CommonIntf *)common.p)->_insight = self->_insight;
            i = 0;
            do {
                OWNER_ALLOCATOR(a, self);
                {
                DegiDataRef degi(beNDMWDegiData_Create(a));
                ObjectList_AppendRetained((igObjectList *)((beNDMWLoadCtrl2CommonIntf *)common.p)->_gameUseData, (igObject *)(int)degi.p);
                }
                OWNER_ALLOCATOR(a, self);
                {
                FlagWorkRef flag(beNDMWLoadSavePlWork_Create(a));
                ObjectList_AppendRetained((igObjectList *)((beNDMWLoadCtrl2CommonIntf *)common.p)->_flagWork, (igObject *)(int)flag.p);
                }
                i++;
            } while (i < 4);
            ((beNDMWLoadCtrl2CommonIntf *)common.p)->_kindHard = 0;
            beNDMWMcUtilCtrl__Init((beNDMWMcUtilCtrl *)((beNDMWLoadCtrl2CommonIntf *)common.p)->_mcUtilCtrl, self->_messenger, 0);
            ObjectList_AppendRetained((igObjectList *)ram->_dataList, (igObject *)(int)common.p);
            }
            }
        }
        return 1;
    }
    if (ram->_dataList == 0) return 1;
    ensureDataList(ram);
    igProperty_FindByName((igObjectList *)ram->_dataList, g_propertyNameField, "CTRL");
    switch (message) {
    case 1:
        return 1;
    case 2:
        return 1;
    case 3:
        if (beMessenger_GetObjectCount((beMessenger *)self->_messenger) == 0) {
            ensureDataList(ram);
            beMessenger_AppendObject((beMessenger *)self->_messenger, (igObject *)igProperty_FindByName((igObjectList *)ram->_dataList, g_propertyNameField, "COMMONINTF"));
        }
        return 1;
    default:
        return 0;
    }
}

int beNDMWSaveCtrl_GetMeta(void)
{
    return (int)g_beNDMWSaveCtrl_metaObject;
}

#pragma pop
