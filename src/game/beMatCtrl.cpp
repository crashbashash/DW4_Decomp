/* beMatCtrl: the material controller. Each update marks, per material, which players stand inside one
 * of its boxes (a player bit in an igIntList element) and runs the material's Lua script when a
 * player's bit changes; the Lua MAT bindings read the current and previous masks of the material whose
 * script is running. The MATCTRL messages show or hide a material's switch graph, toggle the Lua call
 * trace and pause or restart a RAM. */
#include "dw4/reflected.h"
#include "dw4/igSmartPointer.h"
#include "dw4/listSet.h"
#include "dw4/igTDataList.h"
#pragma push
#pragma readonly_strings on

/* beMessenger_ResolveEnumValue values of the handler's command names. */
enum MatCtrlMessage {
    MESSAGE_SHOWMAT, MESSAGE_HIDEMAT, MESSAGE_SHOW_LUACALL, MESSAGE_HIDE_LUACALL, MESSAGE_PAUSE,
    MESSAGE_RESTART
};

/* beMatCtrl_GetPlayerMatStat results. */
enum PlayerMatStat { MATSTAT_OUTSIDE, MATSTAT_LEAVE, MATSTAT_ENTER, MATSTAT_STAY };

/* igAABox_IntersectPoint result of a point inside the box. */
#define INTERSECT_INSIDE 2

#define PLAYER_MAX 4

/* The Shift-JIS marks of the Lua call trace. */
#define MARK_YES "\x81\x9b" /* ○ */
#define MARK_NO "\x81~"     /* × */
#define MARK_NONE "\x81|"   /* － */

/* The trace's rows for each player: on the material, rode on it, rode off it. */
enum TraceRow { TRACE_ON, TRACE_RIDE, TRACE_RIDE_OFF, TRACE_ROWS };

/* A mask list held through its element accessors. */
typedef igSmartPointer<igTDataList<int> > MaskListRef;

/* The RAM's reference to its work. */
typedef igSmartPointer<beMatCtrlInfoWork> WorkRef;

extern "C" {
int igInsightCore_FindManager(int insight, int meta);
void beMessenger_RegisterReceiver(int messenger, void *receiver, const char *name, const char *text, int value);
unsigned int beMessenger_ResolveEnumValue(int messenger, int metaEnum, int name);
int beMatCtrl_GetMessageEnum(void);
void igSwitch_EnableAllChildren(int switchgraph);
void igSwitch_DisableAllChildren(int switchgraph);
int igAABox_IntersectPoint(igAABox *box, const float *point);

bool beMatCtrl_IsPlayer(beMatCtrl *self);
bool beMatCtrl_IsAllPlayer(beMatCtrl *self);
int beMatCtrl_GetPlayerNo(beMatCtrl *self);
bool beMatCtrl_IsRidePlayer(beMatCtrl *self, int player);
bool beMatCtrl_IsRideOffPlayer(beMatCtrl *self, int player);
void beMatCtrl_SetRun(beMatCtrl *self, bool run);
int beMatCtrl_GetPlayerMatStat(beMatCtrl *self, int player);
void beMatCtrl_Prepare(beMatCtrl *self);
int beMatCtrl_GetInfoMeta(void);
void beMatCtrl_OnAddRam(beMatCtrl *self, beMatCtrlInfoRam *ram);
void beMatCtrl_MarkContacts(beMatCtrl *self, igIntList *masks, beMatCtrlSearchList *nodes, int player, float *point, beMatCtrlDataList *materials);
int beMatCtrl_OnMessage(beMatCtrl *self, beMatCtrlInfoRam *ram, beMessengerWork *message);
int beMatCtrl_GetMeta(void);
void beMatCtrl_UpdateRam(beMatCtrl *self, beMatCtrlInfoRam *ram);
void *igObject_GetAllocator(void *object);
void *Memory_GetAllocatorBySelector(int selector);
beMatCtrlInfoWork *beMatCtrlInfoWork_Create(void *allocator);
igIntList *igIntList_Create(void *allocator);
void ObjectList_AppendRetained(int list, void *object);
void beMessenger_SendGroup(int messenger, const char *group, const char *message);
int beMessenger_GetMatrixCount(int messenger);
int beMessenger_GetInt(int messenger, int index);
void beMessenger_GetMatrix(float *matrix, int messenger, int index);
void igMatrix44f_GetTranslation(const float *matrix, float *point);
int sprintf(char *buffer, const char *format, ...);
int beLua__RunNamedChunk(int lua, const char *chunk, int given);

extern int g_beLua_metaObject[4];
extern int g_beMatCtrlInfo_metaObject[4];
extern int g_beMatCtrl_metaObject[4];
extern const char MATCTRL[];
extern const char emptyString[];
extern int kIGMemoryPoolHandleUser1[4];
extern int g_mdlEntity[4];
extern unsigned char g_useOwnerAllocator;
}

/* The mask lists' memory is addressed by byte offset: the queries scale the running material's index
 * once and read both lists at that offset. */
static inline int MaskAt(int masks, int offset) {
    return *(int *)(((igIntList *)masks)->_data + offset);
}

static inline bool HasPlayer(int mask, int bit) {
    return bit == (bit & mask);
}

bool beMatCtrl_IsPlayer(beMatCtrl *self) {
    bool onMaterial = false;
    if (MaskAt(self->_wkMatOnList, self->_wkChkMat * sizeof(int)) != 0) {
        onMaterial = true;
    }
    return onMaterial;
}

bool beMatCtrl_IsAllPlayer(beMatCtrl *self) {
    bool all = true;
    for (int player = 0; player < PLAYER_MAX; player++) {
        if (self->_wkPlExist[player] != 0) {
            int bit = 1 << player;
            if (!HasPlayer(MaskAt(self->_wkMatOnList, self->_wkChkMat * sizeof(int)), bit)) {
                all = false;
                break;
            }
        }
    }
    return all;
}

int beMatCtrl_GetPlayerNo(beMatCtrl *self) {
    for (int player = 0; player < PLAYER_MAX; player++) {
        if (self->_wkPlExist[player] != 0) {
            int offset = self->_wkChkMat * sizeof(int);
            int bit = 1 << player;
            if (HasPlayer(MaskAt(self->_wkMatOnList, offset), bit) && !HasPlayer(MaskAt(self->_wkMatOldOnList, offset), bit)) return player;
        }
    }
    return 0;
}

bool beMatCtrl_IsRidePlayer(beMatCtrl *self, int player) {
    int offset = self->_wkChkMat * sizeof(int);
    int bit = 1 << player;
    if (HasPlayer(MaskAt(self->_wkMatOnList, offset), bit) && !HasPlayer(MaskAt(self->_wkMatOldOnList, offset), bit)) {
        return true;
    }
    return false;
}

bool beMatCtrl_IsRideOffPlayer(beMatCtrl *self, int player) {
    int offset = self->_wkChkMat * sizeof(int);
    int bit = 1 << player;
    if (!HasPlayer(MaskAt(self->_wkMatOnList, offset), bit) && HasPlayer(MaskAt(self->_wkMatOldOnList, offset), bit)) {
        return true;
    }
    return false;
}

/* Asks the update to set the running material's run flag once its script returns. */
void beMatCtrl_SetRun(beMatCtrl *self, bool run) {
    self->_wkChgFlagNO = self->_wkChkMat;
    self->_wkChgFlag = run;
}

int beMatCtrl_GetPlayerMatStat(beMatCtrl *self, int player) {
    int bit;
    int offset;
    bool wasOn;
    int isOn;
    int stat;
    offset = self->_wkChkMat * sizeof(int);
    bit = 1 << player;
    wasOn = bit == (bit & MaskAt(self->_wkMatOldOnList, offset));
    isOn = bit == (bit & MaskAt(self->_wkMatOnList, offset));
    stat = MATSTAT_OUTSIDE;
    if (isOn == 1 && wasOn == 1) stat = MATSTAT_STAY;
    else if (isOn == 1 && wasOn != 1) stat = MATSTAT_ENTER;
    else if (isOn != 1 && wasOn == 1) stat = MATSTAT_LEAVE;
    else if (isOn != 1 && wasOn != 1) stat = MATSTAT_OUTSIDE;
    return stat;
}

/* Empties a published mask list and drops the controller's reference to it. */
static inline void DropMaskList(int &masks) {
    igIntList *list = (igIntList *)masks;
    if (list != 0) {
        list->_count = 0;
        igRelease((igObject *)masks);
        masks = 0;
    }
}

void beMatCtrl_Prepare(beMatCtrl *self) {
    self->_lua = igInsightCore_FindManager(self->_insight, g_beLua_metaObject[0]);
    DropMaskList(self->_wkMatOnList);
    DropMaskList(self->_wkMatOldOnList);
}

int beMatCtrl_GetInfoMeta(void) {
    return g_beMatCtrlInfo_metaObject[0];
}

void beMatCtrl_OnAddRam(beMatCtrl *self, beMatCtrlInfoRam *ram) {
    beMessenger_RegisterReceiver(self->_messenger, ram, MATCTRL, 0, -1);
}

static inline beMatCtrlSearch *SearchNode(beMatCtrlSearchList *nodes, int i) {
    return ((beMatCtrlSearch **)nodes->_data)[i];
}

/* Sets the player's bit in the mask of every material whose box holds the point. A node whose X range
 * misses the point skips its subtree; a node with material -1 only groups its members. */
void beMatCtrl_MarkContacts(beMatCtrl *self, igIntList *masks, beMatCtrlSearchList *nodes, int player, float *point, beMatCtrlDataList *materials) {
    int count = nodes->_count;
    int i;
    if (count != 0) {
        for (i = 0; i < count; i++) {
            float pointX = *point;
            beMatCtrlSearch *node = SearchNode(nodes, i);
            if (node->_minX <= pointX && !(node->_maxX < pointX)) {
                int material = node->_matNO;
                if (material != -1) {
                    beMatCtrlData *data = ((beMatCtrlData **)materials->_data)[material];
                    if (igAABox_IntersectPoint((igAABox *)data->_chkBox, point) == INTERSECT_INSIDE) {
                        int *mask = (int *)masks->_data;
                        int marked = mask[material];
                        int maskCount = masks->_count;
                        marked |= (1 << player);
                        if (maskCount != 0 && material >= 0 && material < maskCount) mask[material] = marked;
                    }
                }
                beMatCtrl_MarkContacts(self, masks, (beMatCtrlSearchList *)SearchNode(nodes, i)->_memberList, player, point, materials);
            }
        }
    }
}

/* Sets a list's count, growing its storage when the count is above its capacity. */
template <class List> static inline void SetListCount(List *list, int count, int elementSize) {
    if (count >= 0) {
        if (count <= list->_capacity) {
            list->_count = count;
        } else {
            List_Resize(list, count, elementSize);
        }
    }
}

/* Stores value in every element of a list. */
template <class T, class List> static inline void FillList(List *list, const T &value) {
    int count = list->_count;
    T *data = (T *)list->_data;
    for (int i = 0; i < count; i++) data[i] = value;
}

/* Makes a reference field hold next: retains next, then releases what the field held. */
static inline void AssignRef(int &field, igObject *next) {
    if (next != 0) next->_refCount = next->_refCount + 1;
    igRelease((igObject *)field);
    field = (int)next;
}

/* Makes element index of a list hold object: retains it, releases what the element held and stores it
 * when the index is inside the list. */
static inline void StoreListRef(igObject *object, igObjectList *list, int index) {
    if (object != 0) object->_refCount = object->_refCount + 1;
    igRelease(((igObject **)list->_data)[index]);
    ListSet(list, index, object);
}

static inline void *OwnerAllocator(beMatCtrl *self) {
    void *owner = igObject_GetAllocator(self);
    return g_useOwnerAllocator != 0 ? owner : Memory_GetAllocatorBySelector(kIGMemoryPoolHandleUser1[0]);
}

/* The work's current (0) and previous (1) mask list. */
static inline igIntList *MaskListAt(beMatCtrlInfoWork *work, int index) {
    return ((igIntList **)((igObjectList *)work->_matOnPlLists)->_data)[index];
}

static inline const char *MaterialName(beMatCtrlInfo *info, int material) {
    return (const char *)((beMatCtrlData **)((beMatCtrlDataList *)info->_dataList_)->_data)[material]->_name;
}

static inline unsigned char *RunFlags(beMatCtrlInfoWork *work) {
    return ((igTDataList<unsigned char> *)work->_runFlagList)->_data;
}

static inline void SetState(beMatCtrlInfoRam *ram, int state) {
    ram->_st0 = state;
    ram->_st3 = 0;
    ram->_st2 = 0;
    ram->_st1 = 0;
}

/* The first update of a RAM creates its work: the current and previous mask lists and the run flag of
 * every material. Later updates rebuild the current masks from the players' positions, publish both
 * lists and run the script of each running material on which a player's bit changed; the lists then
 * swap, so this update's masks are the next one's previous masks. */
void beMatCtrl_UpdateRam(beMatCtrl *self, beMatCtrlInfoRam *ram) {
    if (ram->_isRun != 0) {
        beMatCtrlInfo *info = (beMatCtrlInfo *)ram->_parentInfo;
        beMatCtrlInfoWork *work = (WorkRef &)ram->_work;
        switch (ram->_st0) {
        case 1:
            break;
        default: {
            igRelease((igObject *)ram->_work);
            ram->_work = 0;
            {
                WorkRef created(beMatCtrlInfoWork_Create(OwnerAllocator(self)));
                AssignRef(ram->_work, (igObject *)created.p);
                work = (beMatCtrlInfoWork *)ram->_work;
            }
            int materialCount = ((beMatCtrlDataList *)info->_dataList_)->_count;
            {
                igSmartPointer<igIntList> masks(igIntList_Create(OwnerAllocator(self)));
                SetListCount(masks.p, materialCount, sizeof(int));
                FillList(masks.p, 0);
                ObjectList_AppendRetained(work->_matOnPlLists, masks.p);
            }
            {
                igSmartPointer<igIntList> masks(igIntList_Create(OwnerAllocator(self)));
                SetListCount(masks.p, materialCount, sizeof(int));
                FillList(masks.p, 0);
                ObjectList_AppendRetained(work->_matOnPlLists, masks.p);
            }
            SetListCount((igBoolList *)work->_runFlagList, materialCount, sizeof(bool));
            FillList((igBoolList *)work->_runFlagList, true);
            for (int player = 0; player < PLAYER_MAX; player++) self->_wkPlExist[player] = 0;
            SetState(ram, 1);
            return;
        }
        }
        float point[3];
        char chunk[32];
        char trace[TRACE_ROWS][PLAYER_MAX][16];
        float matrix[16];
        igSmartPointer<igIntList> current(MaskListAt(work, 0), kRetainReference);
        igSmartPointer<igIntList> previous(MaskListAt(work, 1), kRetainReference);
        FillList(current.p, 0);
        beMessenger_SendGroup(self->_messenger, "PLAYER", "GETMATRIX");
        int resultCount = beMessenger_GetMatrixCount(self->_messenger);
        for (int player = 0; player < PLAYER_MAX; player++) {
            unsigned char *exists = &self->_wkPlExist[player];
            *exists = 0;
            for (int i = 0; i < resultCount; i++) {
                if (player == beMessenger_GetInt(self->_messenger, i)) {
                    *exists = 1;
                    break;
                }
            }
        }
        for (int i = 0; i < resultCount; i++) {
            int player = beMessenger_GetInt(self->_messenger, i);
            if (self->_wkPlExist[player] != 0) {
                beMessenger_GetMatrix(matrix, self->_messenger, i);
                igMatrix44f_GetTranslation(matrix, point);
                beMatCtrl_MarkContacts(self, current.p, (beMatCtrlSearchList *)info->_search, player, point, (beMatCtrlDataList *)info->_dataList_);
            }
        }
        int materialCount = ((beMatCtrlDataList *)info->_dataList_)->_count;
        AssignRef(self->_wkMatOnList, (igObject *)current.p);
        AssignRef(self->_wkMatOldOnList, (igObject *)previous.p);
        for (int material = 0; material < materialCount; material++) {
            unsigned char *runFlags = RunFlags(work);
            if (runFlags[material] != 0) {
                for (int bit = 0; bit < PLAYER_MAX; bit++) {
                    int mask = 1 << bit;
                    bool now = HasPlayer((*(MaskListRef &)current)[material], mask);
                    bool was = HasPlayer((*(MaskListRef &)previous)[material], mask);
                    if (now != was) {
                        self->_wkChkMat = material;
                        self->_wkChgFlagNO = -1;
                        self->_wkChgFlag = 1;
                        const char *name = MaterialName(info, material);
                        sprintf(chunk, "%s.lua", name != 0 ? name : emptyString);
                        if (self->_isLuaCallDisp == 1) {
                            for (int p = 0; p < PLAYER_MAX; p++) {
                                int playerBit = 1 << p;
                                unsigned char wasOn = HasPlayer((*(MaskListRef &)previous)[material], playerBit);
                                unsigned char isOn = HasPlayer((*(MaskListRef &)current)[material], playerBit);
                                if (isOn == 1) {
                                    sprintf(trace[TRACE_ON][p], MARK_YES);
                                    if (wasOn == 0) {
                                        sprintf(trace[TRACE_RIDE][p], MARK_YES);
                                    } else {
                                        sprintf(trace[TRACE_RIDE][p], MARK_NONE);
                                    }
                                    sprintf(trace[TRACE_RIDE_OFF][p], MARK_NONE);
                                } else {
                                    sprintf(trace[TRACE_ON][p], MARK_NO);
                                    sprintf(trace[TRACE_RIDE][p], MARK_NONE);
                                    if (wasOn == 1) {
                                        sprintf(trace[TRACE_RIDE_OFF][p], MARK_YES);
                                    } else {
                                        sprintf(trace[TRACE_RIDE_OFF][p], MARK_NONE);
                                    }
                                }
                            }
                        }
                        g_mdlEntity[0] = 0;
                        beLua__RunNamedChunk(self->_lua, chunk, 0);
                        if (self->_wkChgFlagNO != -1) ListSet((igBoolList *)work->_runFlagList, self->_wkChgFlagNO, self->_wkChgFlag);
                        break;
                    }
                }
            }
        }
        StoreListRef((igObject *)previous.p, (igObjectList *)work->_matOnPlLists, 0);
        StoreListRef((igObject *)current.p, (igObjectList *)work->_matOnPlLists, 1);
    }
}

int beMatCtrl_OnMessage(beMatCtrl *self, beMatCtrlInfoRam *ram, beMessengerWork *message) {
    beMatCtrlInfo *info = (beMatCtrlInfo *)ram->_parentInfo;
    switch (beMessenger_ResolveEnumValue(self->_messenger, beMatCtrl_GetMessageEnum(), message->_message)) {
    case MESSAGE_SHOWMAT:
        igSwitch_EnableAllChildren(info->_switchgraph);
        break;
    case MESSAGE_HIDEMAT:
        igSwitch_DisableAllChildren(info->_switchgraph);
        break;
    case MESSAGE_SHOW_LUACALL:
        self->_isLuaCallDisp = 1;
        break;
    case MESSAGE_HIDE_LUACALL:
        self->_isLuaCallDisp = 0;
        break;
    case MESSAGE_PAUSE:
        ram->_isRun = 0;
        break;
    case MESSAGE_RESTART:
        ram->_isRun = 1;
        break;
    default:
        return 0;
    }
    return 1;
}

int beMatCtrl_GetMeta(void) {
    return g_beMatCtrl_metaObject[0];
}
#pragma pop
