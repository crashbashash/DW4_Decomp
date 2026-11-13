/* beMatCtrl: the material controller. Each update marks, per material, which players stand inside one
 * of its boxes (a player bit in an igIntList element) and runs the material's Lua script when a
 * player's bit changes; the Lua MAT bindings read the current and previous masks of the material whose
 * script is running. The MATCTRL messages show or hide a material's switch graph, toggle the Lua call
 * trace and pause or restart a RAM. */
#include "dw4/reflected.h"
#include "dw4/igSmartPointer.h"

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
void beMatCtrl_RegisterReceiver(beMatCtrl *self, beMatCtrlInfoRam *ram);
void beMatCtrl_MarkContacts(beMatCtrl *self, igIntList *masks, beMatCtrlSearchList *nodes, int player, float *point, beMatCtrlDataList *materials);
int beMatCtrl_OnMessage(beMatCtrl *self, beMatCtrlInfoRam *ram, beMessengerWork *message);
int beMatCtrl_GetMeta(void);

extern int g_beLua_metaObject[4];
extern int g_beMatCtrlInfo_metaObject[4];
extern int g_beMatCtrl_metaObject[4];
extern const char MATCTRL[];
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

void beMatCtrl_RegisterReceiver(beMatCtrl *self, beMatCtrlInfoRam *ram) {
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
