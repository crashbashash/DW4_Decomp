#include "dw4/reflected.h"
#include "dw4/igSmartPointer.h"
#include "dw4/StringPool.h"
#include "dw4/beBaseInfoDataList.h"
#include "dw4/beMessenger.h"
#include "dw4/bePadManager.h"
#include "dw4/beSelectCtrl.h"
#include "dw4/beSelectCtrlInfo.h"
#include "dw4/beSelectCtrlInfoWork.h"
#include "dw4/igDataLists.h"
#include "dw4/igInsightCore.h"
#include "dw4/igMathConstants.h"
#include "dw4/igMemoryPoolContext.h"
#include "dw4/igNamedObject.h"
#include "dw4/igObject.h"
#include <stdio.h>
#include <string.h>
#include "dw4/emptyString.h"
#pragma push
#pragma readonly_strings on

/* SELECTCTRL: a cursor over a row of choices drawn by a MODELCTRL model. The update opens the model,
 * moves the cursor with the stick or D-pad, plays the decide or cancel sequence and closes it again;
 * the message handler starts a selection and answers the script's questions about it. */

/* beMessenger_ResolveEnumValue values of the handler's command names. */
enum SelectMessage {
    MESSAGE_GENERATE, MESSAGE_ISEND, MESSAGE_GETSELECT, MESSAGE_ISSELECTNOW, MESSAGE_FO2TOP,
    MESSAGE_ISFO2TOP, MESSAGE_REMOVE
};

/* beBaseInfoRam::_st0 of a running selection. */
enum SelectState {
    STATE_OPEN = 0,
    STATE_SELECT = 1,
    STATE_CLOSE = 2,
    STATE_END = 3,
    STATE_FO2TOP = 10
};

/* bePadData::_lStk direction bits and bePadData::_button D-pad and face buttons. */
enum PadBits {
    STICK_UP = 0x1,
    STICK_RIGHT = 0x2,
    STICK_DOWN = 0x4,
    STICK_LEFT = 0x8,
    PAD_UP = 0x10,
    PAD_RIGHT = 0x20,
    PAD_DOWN = 0x40,
    PAD_LEFT = 0x80,
    PAD_DIRECTIONS = 0xF0,
    PAD_CIRCLE = 0x2000,
    PAD_CROSS = 0x4000
};

#define RELEASE(type, object) { type *released = (type *)(object); if (released != 0) { released->_refCount = (int)released->_refCount - 1; if ((released->_refCount & 0x7FFFFF) == 0) igObject_Destroy(released); } }
#define PICK_ALLOCATOR(allocator, owner) { allocator = (int)igObject_GetAllocator(owner); allocator = (g_useOwnerAllocator != 0) ? allocator : (int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleUser1); }
#define INFO_NAME (info->_name ? info->_name : (int)emptyString)
#define SELECT_MODEL() { int ramNo = ram->_ramNo; beMessenger_SelectReceivers((beMessenger *)self->_messenger, "MODELCTRL", (const char *)INFO_NAME, ramNo); }
#define SEND_MODEL(sequence) { int ramNo = ram->_ramNo; beMessenger_SendNamed((beMessenger *)self->_messenger, "MODELCTRL", (const char *)INFO_NAME, ramNo, (const char *)sequence); }
#define SEND_SAVED_SEQUENCE() { int sequence = work->_svSeqName; int ramNo = ram->_ramNo; beMessenger_SendNamed((beMessenger *)self->_messenger, "MODELCTRL", (const char *)INFO_NAME, ramNo, (const char *)sequence); }
/* Asks the model whether it still plays the named sequence; the reply is the first bool. */
#define ASK_PLAYING(sequence) \
    SELECT_MODEL() \
    beMessenger_AppendString((beMessenger *)self->_messenger, (const char *)sequence); \
    beMessenger_DispatchSelected((beMessenger *)self->_messenger, "ISSEQNAME");
#define PLAY_CURSOR_NG() \
    beMessenger_SelectGroup((beMessenger *)self->_messenger, "SOUND"); \
    beMessenger_AppendString((beMessenger *)self->_messenger, "CURSOR_NG"); \
    beMessenger_DispatchSelected((beMessenger *)self->_messenger, "PLAY");
#define ENSURE_STRING_POOL() if (g_stringPool == 0) { \
        value = (int)StringPool_Allocate(0x10); \
        if (value != 0) value = (int)StringPool_Construct((StringPool *)value); \
        g_stringPool = (StringPool *)value; \
    }
/* Drops the work's share of its saved sequence name (the reference count is the word before the text). */
#define RELEASE_SAVED_SEQUENCE(header) { \
        oldName = (int *)work->_svSeqName; \
        if (oldName != 0) { \
            header = oldName - 2; \
            value = oldName[-1] - 1; \
            oldName[-1] = value; \
            if (value == 0) StringChunk_ReleaseHeader((StringChunk *)*header, (StringTokenHeader *)header); \
        } \
    }
#define SAVE_SEQUENCE(text) { \
        ENSURE_STRING_POOL() \
        name = (int *)StringPool_Intern(g_stringPool, text); \
        RELEASE_SAVED_SEQUENCE(header) \
        work->_svSeqName = (int)name; \
    }
#define NEXT_STATE(ram) { (ram)->_st0 = (ram)->_st0 + 1; (ram)->_st3 = 0; (ram)->_st2 = 0; (ram)->_st1 = 0; }
#define NEXT_STEP(ram) { (ram)->_st1 = (ram)->_st1 + 1; (ram)->_st3 = 0; (ram)->_st2 = 0; }
#define ENTER_STATE(ram, state) { (ram)->_st0 = state; (ram)->_st3 = 0; (ram)->_st2 = 0; (ram)->_st1 = 0; }
/* Replaces the work's decide list with one bool per choice, read from the message. */
#define READ_DECIDE_LIST(work, count, i, flag, list, slot) { \
        PICK_ALLOCATOR(allocator, self) \
        BoolListRef decide((igObject *)igBoolList_Create(allocator)); \
        held = decide.p; \
        if (held != 0) held->_refCount = (int)held->_refCount + 1; \
        RELEASE(igObject, (work)->_decideList) \
        (work)->_decideList = (int)held; \
        i = 0; \
        if (0 < count) { \
            do { \
                flag = beMessenger_GetBool((beMessenger *)self->_messenger, i); \
                list = (igBoolList *)decide.p; \
                slot = list->_count; \
                if (slot < list->_capacity) { \
                    list->_count = slot + 1; \
                } else { \
                    List_Resize(list, slot + 1, 1); \
                } \
                i += 1; \
                ((unsigned char *)list->_data)[slot] = flag; \
            } while (i < count); \
        } \
    }

extern "C" igMetaObject *beSelectCtrl_GetInfoMeta(void);
extern "C" igMetaObject *beSelectCtrl_GetMeta(void);
extern "C" int igBoolList_Create(int);
extern "C" void beSelectCtrl_Prepare(beSelectCtrl *self);
extern "C" void beSelectCtrl_OnAddRam(beSelectCtrl *self, int info);
extern "C" void beSelectCtrl_UpdateRam(beSelectCtrl *self, beBaseInfoRam *ram);
extern "C" int beSelectCtrl_OnMessageText(beSelectCtrl *self, beBaseInfoRam *ram, int message);

/* Owning stack reference to the work created by GENERATE, released on scope exit. */
class WorkRef {
public:
    beSelectCtrlInfoWork *p;
    WorkRef(beSelectCtrlInfoWork *o) : p(o) {}
    ~WorkRef() { beSelectCtrlInfoWork *o = p; if (o != 0) { --o->_refCount; if ((o->_refCount & 0x7fffff) == 0) igObject_Destroy(o); } }
};
/* Owning stack reference to a new decide list while it is filled, released on scope exit. */
class BoolListRef {
public:
    igObject *p;
    BoolListRef(igObject *o) : p(o) {}
    ~BoolListRef() { igObject *o = p; if (o != 0) { --o->_refCount; if ((o->_refCount & 0x7fffff) == 0) igObject_Destroy(o); } }
};
/* Stores a freshly created data list in the ram, taking the ram's share and dropping the previous list;
 * the temporary holder gives up the creating share at the end of the full expression. */
struct DataList {
    static inline void store(beBaseInfoRam *ram, const igSmartPointer<igObject> &list) {
        igObject *created = list.p;
        if (created != 0) created->_refCount = (int)created->_refCount + 1;
        RELEASE(igObject, ram->_dataList)
        ram->_dataList = (int)created;
    }
    static inline void create(beBaseInfoRam *ram, int allocator) { igSmartPointer<igObject> list(beBaseInfoDataList_Create(allocator)); store(ram, list); }
};

void beSelectCtrl_Prepare(beSelectCtrl *self)
{
    if (self->_padManager == 0) {
        self->_padManager = (int)igInsightCore_FindManager((igInsightCore *)self->_insight, g_bePadManager_metaObject);
    }
}

igMetaObject *beSelectCtrl_GetInfoMeta(void)
{
    return g_beSelectCtrlInfo_metaObject;
}

void beSelectCtrl_OnAddRam(beSelectCtrl *self, int info)
{
    beMessenger_RegisterReceiverFromInfo((beMessenger *)self->_messenger, (beBaseInfoRam *)info, "SELECTCTRL");
}

static inline int waitOf(const beBaseInfoRam *ram) { return ram->_st2; }

void beSelectCtrl_UpdateRam(beSelectCtrl *self, beBaseInfoRam *ram) {
    beBaseInfo *info;
    float offset[3];
    char slideText[16];
    char upText[16];
    char downText[16];
    char onText[16];
    int dpad;
    beSelectCtrlInfoRamData *data;
    int stick;
    int *oldName;
    int state;
    bool moved;
    beSelectCtrlInfoWork *work;
    bePadData *pad;
    bool left;
    int allocator;
    bool right;
    int value;
    int selectNo;
    unsigned pressed;
    int *header;
    bool up;
    bool down;
    int *name;

    if (ram->_isRun == 0) return;
    info = (beBaseInfo *)ram->_parentInfo;
    if (ram->_dataList == 0) {
        igObject *created;
        allocator = (int)igObject_GetAllocator(ram);
        allocator = g_useOwnerAllocator != 0 ? allocator : (int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleUser1);
        igSmartPointer<igObject> list(beBaseInfoDataList_Create(allocator));
        created = list.p;
        if (created != 0) created->_refCount = created->_refCount + 1;
        RELEASE(igObject, ram->_dataList)
        ram->_dataList = (int)created;
    }
    data = (beSelectCtrlInfoRamData *)igProperty_FindByName((igObjectList *)ram->_dataList, g_propertyNameField, "ONE");
    work = (beSelectCtrlInfoWork *)data->_work;
    pad = bePadManager_GetPadForPlayer((bePadManager *)self->_padManager, ram->_ramNo);
    state = ram->_st0;
    pressed = pad->_trigger;
    stick = pad->_lStk;
    dpad = pad->_button & PAD_DIRECTIONS;
    switch (state) {
    case STATE_OPEN:
        switch (ram->_st1) {
        case 0:
            SELECT_MODEL()
            offset[0] = work->_offsetPos[0];
            offset[1] = work->_offsetPos[1];
            offset[2] = work->_offsetPos[2];
            beMessenger_AppendVec3((beMessenger *)self->_messenger, offset);
            beMessenger_AppendString((beMessenger *)self->_messenger, "SQ_OPEN");
            beMessenger_DispatchSelected((beMessenger *)self->_messenger, "GENERATE");
            NEXT_STEP(ram)
            return;
        case 1:
            ASK_PLAYING("SQ_OPEN")
            if (beMessenger_GetBool((beMessenger *)self->_messenger, 0) != 1) {
                sprintf(slideText, "SQ_LINESL%02d", data->_selectNo);
                SEND_MODEL(slideText)
                NEXT_STATE(ram)
                return;
            }
            break;
        }
        break;
    case STATE_SELECT:
        switch (ram->_st1) {
        case 0:
            if (stick != 0 || dpad != 0) {
                switch (ram->_st3) {
                case 0:
                    selectNo = data->_selectNo;
                    moved = false;
                    left = true;
                    if (!(stick & STICK_LEFT) && !(dpad & PAD_LEFT)) left = false;
                    right = true;
                    if (!(stick & STICK_RIGHT) && !(dpad & PAD_RIGHT)) right = false;
                    up = true;
                    if (!(stick & STICK_UP) && !(dpad & PAD_UP)) up = false;
                    down = true;
                    if (!(stick & STICK_DOWN) && !(dpad & PAD_DOWN)) down = false;
                    value = data->_isTateSelect;
                    if ((value != 0 && up) || (value == 0 && left)) {
                        if (selectNo != 0) {
                            selectNo = selectNo - 1;
                            moved = true;
                            sprintf(upText, "SQ_LINEUP%02d", selectNo);
                            SAVE_SEQUENCE(upText)
                        }
                    } else if (((value != 0 && down) || (value == 0 && right)) && selectNo != work->_selectMax - 1) {
                        selectNo = selectNo + 1;
                        moved = true;
                        sprintf(downText, "SQ_LINEDW%02d", selectNo);
                        SAVE_SEQUENCE(downText)
                    }
                    if (moved) {
                        data->_selectNo = selectNo;
                        SEND_SAVED_SEQUENCE()
                        ram->_st3 = ram->_st3 + 1;
                    }
                    break;
                default:
                    ASK_PLAYING(work->_svSeqName)
                    if (!beMessenger_GetBool((beMessenger *)self->_messenger, 0)) ram->_st3 = 0;
                }
            }
            if (pressed & PAD_CIRCLE) {
                if (work->_isCancel != 0) {
                    data->_selectNo = -1;
                    NEXT_STATE(ram)
                    return;
                }
                PLAY_CURSOR_NG()
                ram->_st1 = 2;
                ram->_st3 = 0;
                ram->_st2 = 0;
                return;
            }
            if (pressed & PAD_CROSS) {
                igBoolList *decide = (igBoolList *)work->_decideList;
                if (decide != 0 && ((unsigned char *)decide->_data)[(unsigned)data->_selectNo] == 0) {
                    PLAY_CURSOR_NG()
                    ram->_st1 = 2;
                    ram->_st3 = 0;
                    ram->_st2 = 0;
                    return;
                }
                sprintf(onText, "SQ_LINEON%02d", data->_selectNo);
                SAVE_SEQUENCE(onText)
                SEND_SAVED_SEQUENCE()
                NEXT_STEP(ram)
                return;
            }
            break;
        case 1:
            ASK_PLAYING(work->_svSeqName)
            if (!beMessenger_GetBool((beMessenger *)self->_messenger, 0)) {
                NEXT_STATE(ram)
                return;
            }
            break;
        case 2:
            if (waitOf(ram) < 0x10) {
                ram->_st2 = ram->_st2 + 1;
                ram->_st3 = 0;
                return;
            }
            ram->_st1 = 0;
            ram->_st3 = 0;
            ram->_st2 = 0;
            return;
        }
        break;
    case STATE_CLOSE:
        switch (ram->_st1) {
        case 0:
            if (data->_selectNo != -1) name = (int *)"SQ_CLOSE";
            else name = (int *)"SQ_CANCEL";
            ENSURE_STRING_POOL()
            header = (int *)StringPool_Intern(g_stringPool, (const char *)name);
            {
                int *closeHeader;
                RELEASE_SAVED_SEQUENCE(closeHeader)
            }
            work->_svSeqName = (int)header;
            SEND_SAVED_SEQUENCE()
            NEXT_STEP(ram)
            return;
        case 1:
            ASK_PLAYING(work->_svSeqName)
            if (!beMessenger_GetBool((beMessenger *)self->_messenger, 0)) {
                NEXT_STATE(ram)
                return;
            }
            break;
        }
        break;
    case STATE_FO2TOP:
        switch (ram->_st1) {
        case 0:
            SEND_MODEL("SQ_FO2TOP")
            NEXT_STEP(ram)
            return;
        case 1:
            ASK_PLAYING("SQ_FO2TOP")
            if (!beMessenger_GetBool((beMessenger *)self->_messenger, 0)) {
                ENTER_STATE(ram, STATE_SELECT)
                return;
            }
            break;
        }
        break;
    default:
        ram->_isRun = 0;
        RELEASE(igObject, data->_work)
        data->_work = 0;
        break;
    }
}

int beSelectCtrl_OnMessageText(beSelectCtrl *self, beBaseInfoRam *ram, int message) {
    int count;
    int i;
    int allocator;
    beSelectCtrlInfoRamData *data;
    beSelectCtrlInfoWork *work;
    int j;
    int flag;
    beSelectCtrlInfoWork *created;
    int flag2;
    int slot2;
    igBoolList *list2;
    int slot;
    igObject *held;
    igBoolList *list;
    if (ram->_dataList == 0) {
        PICK_ALLOCATOR(allocator, ram)
        DataList::create(ram, allocator);
    }
    data = (beSelectCtrlInfoRamData *)igProperty_FindByName((igObjectList *)ram->_dataList, g_propertyNameField, "ONE");
    work = (beSelectCtrlInfoWork *)data->_work;
    switch (beMessenger_ResolveEnumValue((beMessenger *)self->_messenger, beSelectCtrl_GetMessageEnum(), (const char *)message)) {
    case MESSAGE_GENERATE:
        ram->_isRun = 1;
        ENTER_STATE(ram, STATE_OPEN)
        PICK_ALLOCATOR(allocator, self)
        {
            WorkRef newWork(beSelectCtrlInfoWork_Create(allocator));
            held = (igObject *)newWork.p;
            if (held != 0) held->_refCount = (int)held->_refCount + 1;
            RELEASE(igObject, data->_work)
            data->_work = (int)held;
            created = newWork.p;
        }
        data->_selectNo = 0;
        if (beMessenger_GetIntCount((beMessenger *)self->_messenger) != 0) {
            created->_selectMax = beMessenger_GetInt((beMessenger *)self->_messenger, 0);
            if (beMessenger_GetIntCount((beMessenger *)self->_messenger) == 2) {
                data->_selectNo = beMessenger_GetInt((beMessenger *)self->_messenger, 1);
            }
        } else {
            created->_selectMax = data->_maxSelect;
        }
        if (beMessenger_GetVec3Count((beMessenger *)self->_messenger) != 0) {
            igVec3f offset = beMessenger_GetVec3((beMessenger *)self->_messenger, 0);
            created->_offsetPos[0] = offset.x;
            created->_offsetPos[1] = offset.y;
            created->_offsetPos[2] = offset.z;
        } else {
            created->_offsetPos[0] = g_vec3Zero.x;
            created->_offsetPos[1] = g_vec3Zero.y;
            created->_offsetPos[2] = g_vec3Zero.z;
        }
        if (beMessenger_GetStringCount((beMessenger *)self->_messenger) != 0) {
            if (strcmp(beMessenger_GetString((beMessenger *)self->_messenger, 0), "NOCANCEL") == 0) {
                created->_isCancel = 0;
            }
        }
        count = beMessenger_GetBoolCount((beMessenger *)self->_messenger);
        if (count != 0 && count == created->_selectMax) {
            READ_DECIDE_LIST(created, count, i, flag, list, slot)
        }
        return 1;
    case MESSAGE_ISSELECTNOW:
        if (ram->_isRun != 0) {
            if (ram->_st0 == STATE_CLOSE || ram->_st0 == STATE_END) {
                beMessenger_AppendBool((beMessenger *)self->_messenger, 0);
            } else {
                beMessenger_AppendBool((beMessenger *)self->_messenger, 1);
            }
        } else {
            beMessenger_AppendBool((beMessenger *)self->_messenger, 0);
        }
        return 1;
    case MESSAGE_ISEND:
        if (ram->_isRun != 0) {
            beMessenger_AppendBool((beMessenger *)self->_messenger, 0);
        } else {
            beMessenger_AppendBool((beMessenger *)self->_messenger, 1);
        }
        return 1;
    case MESSAGE_GETSELECT:
        beMessenger_AppendInt((beMessenger *)self->_messenger, data->_selectNo);
        return 1;
    case MESSAGE_ISFO2TOP:
        if (ram->_st0 == STATE_SELECT && ram->_st1 == 0) {
            beMessenger_AppendBool((beMessenger *)self->_messenger, 0);
        } else {
            beMessenger_AppendBool((beMessenger *)self->_messenger, 1);
        }
        return 1;
    case MESSAGE_FO2TOP:
        if (ram->_st0 == STATE_SELECT && ram->_st1 == 0) {
            data->_selectNo = 0;
            if (beMessenger_GetIntCount((beMessenger *)self->_messenger) > 0) {
                work->_selectMax = beMessenger_GetInt((beMessenger *)self->_messenger, 0);
                count = beMessenger_GetBoolCount((beMessenger *)self->_messenger);
                if (count != 0 && count == work->_selectMax) {
                    READ_DECIDE_LIST(work, count, j, flag2, list2, slot2)
                }
            }
            ENTER_STATE(ram, STATE_FO2TOP)
            beMessenger_AppendBool((beMessenger *)self->_messenger, 1);
        } else {
            beMessenger_AppendBool((beMessenger *)self->_messenger, 0);
        }
        return 1;
    case MESSAGE_REMOVE:
        data->_selectNo = -1;
        ENTER_STATE(ram, STATE_CLOSE)
    default:
        return 0;
    }
}

igMetaObject *beSelectCtrl_GetMeta(void)
{
    return g_beSelectCtrl_metaObject;
}

#pragma pop
