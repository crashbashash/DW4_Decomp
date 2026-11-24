#include "dw4/support/reflected.h"
#include "dw4/maths/igVec3f.h"
#include "dw4/core/igobject_release.h"
#include "dw4/core/igSmartPointer.h"
#include "dw4/datapump/igRandomNumberDispatchView.h"
#include "dw4/core/StringPool.h"
#include "dw4/game/be.h"
#include "dw4/game/beBaseInfoRam.h"
#include "dw4/game/beDBManager.h"
#include "dw4/game/beDataBase.h"
#include "dw4/game/beGenerater.h"
#include "dw4/game/beGeneraterInfo.h"
#include "dw4/game/beGeneraterInfoWork.h"
#include "dw4/game/beLua.h"
#include "dw4/game/beMessenger.h"
#include "dw4/game/beTargetObj.h"
#include "dw4/core/igDataLists.h"
#include "dw4/insight/igInsightCore.h"
#include "dw4/maths/igMatrix44f.h"
#include "dw4/core/igMemoryPoolContext.h"
#include "dw4/core/igObject.h"
#include "dw4/support/softfloat.h"
#include <string.h>
#include "dw4/support/emptyString.h"
#pragma push
#pragma readonly_strings on

extern "C" igMetaObject *beGenerater_GetInfoMeta(void);
extern "C" igMetaObject *beGenerater_GetMeta(void);
extern "C" void beGenerater_OnAddRam(beGenerater *self, beGeneraterInfoRam *ram);
extern "C" void beGenerater_Prepare(beGenerater *self);
extern "C" int GENERATER[4];
extern "C" void beGenerater_UpdateRam(beGenerater *self, beBaseInfoRam *ram);
extern "C" char *g_itemDropCategories[];
extern "C" void beGenerater_DropItemsForDead(beGenerater *self, beBaseInfoRam *ram, bool lastWave);
extern "C" int beGenerater_OnMessageText(beGenerater *self, beBaseInfoRam *ram, int message);
extern "C" int beGenerater_SpawnEnemies(beGenerater *self, beBaseInfoRam *ram, int count);

/* An object list with the list's inline accessors. */
template <class T> struct ObjectListOf : igObjectList {
    T *get(int index) const { return ((T **)_data)[index]; }
};
typedef igSmartPointer<ObjectListOf<beGeneraterItemDataOne> > DropListRef;
typedef igSmartPointer<ObjectListOf<beBaseInfoRam> > EnemyRamListRef;

/* The generator data the ram plays: its entry in the parent info's data list. */
static inline beGeneraterData *dataOf(beGeneraterInfoRam *geneRam)
{
    return (beGeneraterData *)((int *)((igObjectList *)((beGeneraterInfo *)geneRam->_parentInfo)->_dataList_)->_data)[geneRam->_ramNo];
}

/* A list of 12-byte positions. */
struct Vec3fList : igObjectList {
    igVec3f *at(int index) const { return &((igVec3f *)_data)[index]; }
};
struct FloatList : igObjectList {
    float at(int index) const { return ((float *)_data)[index]; }
};

void beGenerater_Prepare(beGenerater *self) {
    if (self->_luaManager == 0) {
        self->_luaManager = (int)(igInsightCore_FindManager((igInsightCore *)self->_insight, g_beLua_metaObject));
    }
}

igMetaObject *beGenerater_GetInfoMeta(void)
{
    return g_beGeneraterInfo_metaObject;
}

void beGenerater_OnAddRam(beGenerater *self, beGeneraterInfoRam *ram) {
    int *name = (int *)((beGeneraterInfo *)ram->_parentInfo)->_name;
    int ramNo = ram->_ramNo;
    beMessenger_RegisterReceiver((beMessenger *)self->_messenger, (beBaseInfoRam *)ram, (const char *)&GENERATER[0], (const char *)(name ? name : (int *)emptyString), ramNo);
}

/* Sends FIND_SPACE for each enemy still to spawn and GENERATE to the model that answers, at the next spawn point;
 * returns how many it spawned. */
int beGenerater_SpawnEnemies(beGenerater *self, beBaseInfoRam *ram, int count)
{
    beGeneraterInfoRam *geneRam = (beGeneraterInfoRam *)ram;
    if (count <= 0) {
        return 0;
    }
    beGeneraterInfoWork *work = (beGeneraterInfoWork *)geneRam->_work;
    int spawned = 0;
    beGeneraterData *data = dataOf(geneRam);
    int point = work->_genePoint;
    int pointCount = ((igObjectList *)data->_genePosList)->_count;
    do {
        beMessenger_SendNamed((beMessenger *)self->_messenger, "MODELCTRL", (const char *)work->_geneEnemyName, -1, "FIND_SPACE");
        if (beMessenger_GetObjectCount((beMessenger *)self->_messenger) == 0) {
            break;
        }
        beBaseInfoRam *enemyRam = (beBaseInfoRam *)beMessenger_GetObject((beMessenger *)self->_messenger, 0);
        ((Gap::Core::igObjectList *)work->_enemyRamList)->append((Gap::Core::igObject *)enemyRam);
        beMessenger_SelectReceivers((beMessenger *)self->_messenger, "MODELCTRL", (const char *)work->_geneEnemyName, enemyRam->_ramNo);
        igVec3f position;
        if (data->_genePosIsGlobal) {
            position = *((Vec3fList *)data->_genePosList)->at(point);
        } else {
            igVec3f relative = *((Vec3fList *)data->_genePosList)->at(point);
            /* matching construct: IR dump, sweep — the one-pass loop puts the sum after the return path; the stores
             * through a float pointer to the indexed vector keep their stack offsets, and the offset's elements read
             * as plain members (no operator[] call) with the x term from the data keep the operand order */
            for (int i = 0; i < 1; i++) {
                const float *origin = data->_pos.vec;
                const igVec3f &offset = (&relative)[i];
                ((float *)&(&position)[i])[0] = offset.vec[0] + data->_pos[0];
                ((float *)&(&position)[i])[1] = offset.vec[1] + origin[1];
                ((float *)&(&position)[i])[2] = offset.vec[2] + origin[2];
            }
        }
        float degrees = 57.29578f * ((FloatList *)data->_geneRotYRadianList)->at(point);
        const char *sequence = data->_geneEnemySeq == 0 ? "SQ_ENTR" : (const char *)data->_geneEnemySeq;
        beMessenger_AppendVec3((beMessenger *)self->_messenger, position);
        beMessenger_AppendVec3((beMessenger *)self->_messenger, igVec3f(0.0f, degrees, 0.0f));
        beMessenger_AppendString((beMessenger *)self->_messenger, sequence);
        beMessenger_AppendInt((beMessenger *)self->_messenger, work->_geneEnemyRecNo);
        beMessenger_AppendInt((beMessenger *)self->_messenger, work->_geneEnemyMHp);
        beMessenger_DispatchSelected((beMessenger *)self->_messenger, "GENERATE");
        point++;
        spawned++;
        if (point == pointCount) {
            point = 0;
        }
        work->_genePoint = point;
    } while (count == -1 || --count != 0);
    return spawned;
}

/* Rolls the item drop of every enemy that has died since the last call and removes it from the live list. */
void beGenerater_DropItemsForDead(beGenerater *self, beBaseInfoRam *ram, bool lastWave)
{
    beGeneraterInfoRam *geneRam = (beGeneraterInfoRam *)ram;
    beGeneraterInfoWork *work = (beGeneraterInfoWork *)geneRam->_work;
    bool dropped;
    int k;
    int count = ((EnemyRamListRef &)work->_enemyRamList)->_count;
    for (int index = 0; index < count; index++) {
        if (((EnemyRamListRef &)work->_enemyRamList)->get(index)->_isRun == 0) {
            beBaseInfoRam *enemyRam = ((EnemyRamListRef &)work->_enemyRamList)->get(index);
            beGeneraterData *data = dataOf(geneRam);
            beMessenger_SendNamed((beMessenger *)self->_messenger, "MODELCTRL", (const char *)work->_geneEnemyName, enemyRam->_ramNo, "GETMATRIX_ALL");
            float matrix[16];
            beMessenger_GetMatrix(matrix, (beMessenger *)self->_messenger, 0);
            igVec3f position;
            igMatrix44f_GetTranslation(matrix, (float *)&position);
            beMessenger_SendGroup((beMessenger *)self->_messenger, "GAMERAM", "GETCOMMON");
            int difficulty = igProperty_GetRecord(beMessenger_GetObject((beMessenger *)self->_messenger, 0), "DIFFICULTY")->_data;
            int playerIndex = work->_playerCount - 1;
            beGeneraterPlayerData *playerData = (beGeneraterPlayerData *)((int *)((igObjectList *)data->_playerDataList)->_data)[playerIndex];
            beGeneraterItemData *items;
            if (lastWave && count == 1) {
                items = (beGeneraterItemData *)((int *)((igObjectList *)playerData->_itemLastDataList)->_data)[difficulty];
            } else {
                items = (beGeneraterItemData *)((int *)((igObjectList *)playerData->_itemDataList)->_data)[difficulty];
            }
            int dropCount = ((igObjectList *)items->_dataList)->_count;
            if (dropCount != 0) {
                do {
                    dropped = false;
                    unsigned int roll = ((igRandomNumberDispatchView *)((beSystem *)self->_system)->_random)->genrand() % 10000;
                    for (int i = 0; i < dropCount; i++) {
                        beGeneraterItemDataOne *drop = ((DropListRef &)items->_dataList)->get(i);
                        roll -= drop->_rate;
                        if ((int)roll <= 0) {
                            const char *category = drop->_name ? (const char *)drop->_name : (const char *)emptyString;
                            int itemId = drop->_id;
                            beMessenger_SendNamed((beMessenger *)self->_messenger, "DATABASE", category, 0, "GETDATABASE");
                            beDataBase *database = (beDataBase *)beMessenger_GetObject((beMessenger *)self->_messenger, 0);
                            for (k = 0;; k += 2) {
                                const char *entry = g_itemDropCategories[k];
                                if (entry == 0) {
                                    break;
                                }
                                if (strcmp(entry, category) == 0) {
                                    const char *model = g_itemDropCategories[k + 1] ? g_itemDropCategories[k + 1] : beDataBase_GetRecordString(database, itemId, "MODEL");
                                    beMessenger_SelectReceivers((beMessenger *)self->_messenger, "MODELCTRL", model, -2);
                                    beMessenger_AppendVec3((beMessenger *)self->_messenger, position);
                                    beMessenger_AppendInt((beMessenger *)self->_messenger, itemId);
                                    beMessenger_AppendInt((beMessenger *)self->_messenger, k / 2);
                                    beMessenger_DispatchSelected((beMessenger *)self->_messenger, "GENERATE");
                                    dropped = true;
                                    break;
                                }
                            }
                            break;
                        }
                    }
                } while (!dropped && self->_isPerfectDrop);
            }
            ObjectListOf<beBaseInfoRam> *enemies = ((EnemyRamListRef &)work->_enemyRamList).get();
            igObject *removed = (igObject *)enemies->get(index);
            IG_OBJECT_RELEASE(removed);
            List_RemoveWordAt((igDataList *)enemies, index);
            ((int *)enemies->_data)[enemies->_count] = 0;
            count--;
            index--;
        }
    }
}

/* Drops the list's share of every object it holds and empties it. */
static inline void removeAll(igObjectList *list)
{
    int count = list->_count;
    int i;
    for (i = 0; i < count; i++) {
        ((igObject **)list->_data)[i] = 0;
    }
    list->_count = 0;
}

static inline void releaseAll(igObjectList *list)
{
    int count = list->_count;
    int i;
    for (i = 0; i < count; i++) {
        igObject *object = ((igObject **)list->_data)[i];
        IG_OBJECT_RELEASE(object);
    }
    removeAll(list);
}

/* Resizes the list's storage to `capacity` items, unless it holds more than that. */
static inline void setCapacity(igObjectList *list, int capacity)
{
    if (capacity >= list->_count) {
        ((Gap::Core::igDataList *)list)->setCapacity(capacity, 4);
    }
}

/* The messages a beGenerater answers, in the order of its message enum. */
enum beGeneraterMessage {
    MSG_START,
    MSG_STOP,
    MSG_STOPREVERS,
    MSG_RESET,
    MSG_RESTART,
    MSG_PERFECTDROP,
    MSG_ONFREEZE,
    MSG_OFFREEZE,
};

/* The game's string pool, created on first use. */
static inline void *stringPool(void)
{
    if (g_stringPool == 0) {
        void *pool = StringPool_Allocate(16);
        if (pool != 0) {
            pool = StringPool_Construct((StringPool *)pool);
        }
        g_stringPool = (StringPool *)pool;
    }
    return (void *)g_stringPool;
}

/* A pooled string keeps its chunk owner and reference count in the two words before its text. */
static inline void releaseString(char *text)
{
    if (text != 0) {
        int *header = (int *)(text - 8);
        int count = header[1] - 1;
        header[1] = count;
        if (count == 0) {
            StringChunk_ReleaseHeader((StringChunk *)header[0], (StringTokenHeader *)header);
        }
    }
}

/* Points the work's enemy name at the pooled copy of `name`, releasing the string it held. */
static inline void setGeneEnemyName(beGeneraterInfoWork *work, const char *name)
{
    char *token = StringPool_Intern((StringPool *)stringPool(), name);
    releaseString((char *)work->_geneEnemyName);
    work->_geneEnemyName = (int)token;
}

/* The allocator an object's new members come from: its own, or the default one. */
static inline int allocatorFor(void *object)
{
    int allocator = (int)(((Gap::Core::igObject *)object)->getMemoryPool());
    return (int)(g_useOwnerAllocator ? allocator : Memory_GetAllocatorBySelector(kIGMemoryPoolHandleUser1));
}

/* The enemy record the generator spawns. */
static inline int enemyRecNo(beGeneraterInfoRam *geneRam)
{
    return dataOf(geneRam)->_geneEnemyId;
}

/* Looks up enemy record `recNo` in the enemy database and copies its model and maximum HP into the work. */
static inline void setGeneEnemy(beGenerater *self, igSmartPointer<beGeneraterInfoWork> &work, int recNo)
{
    beMessenger_SendNamed((beMessenger *)self->_messenger, "DATABASE", "enemy", 0, "GETDATABASE");
    beDataBase *database = (beDataBase *)beMessenger_GetObject((beMessenger *)self->_messenger, 0);
    work->_geneEnemyRecNo = recNo;
    setGeneEnemyName(work, beDataBase_GetRecordString(database, recNo, "MODEL"));
    int maxHp = beDataBase_GetRecordInt(database, recNo, "HPMAX");
    work->_geneEnemyMHp = maxHp;
}

/* Frames at 60 per second, as timer nanoseconds. */
static inline long long framesToTime(const float frames)
{
    return (long long)(1e9f * frames / 60.0f);
}

/* Spawns `count` enemies and counts them off the generator's remainder; true when none are left. */
static inline bool spawnRemaining(beGenerater *self, beBaseInfoRam *ram, beGeneraterInfoWork *work, int count)
{
    work->_nokoriKazu -= beGenerater_SpawnEnemies(self, ram, count);
    return work->_nokoriKazu <= 0;
}

/* Moves the generator on to its next state. */
static inline void nextState(beGeneraterInfoRam *geneRam)
{
    geneRam->_st1 = geneRam->_st1 + 1;
    geneRam->_st3 = 0;
    geneRam->_st2 = 0;
}

void beGenerater_UpdateRam(beGenerater *self, beBaseInfoRam *ram)
{
    beGeneraterInfoRam *geneRam = (beGeneraterInfoRam *)ram;
    if (!geneRam->_isRun) {
        return;
    }
    if (geneRam->_work == 0) {
        beMessenger_SendGroup((beMessenger *)self->_messenger, "PLAYER", "GETMATRIX");
        int playerCount = beMessenger_GetMatrixCount((beMessenger *)self->_messenger);
        if (playerCount == 0) {
            return;
        }
        igSmartPointer<beGeneraterInfoWork> created((beGeneraterInfoWork *)Gap::Bec::beGeneraterInfoWork::_instantiateFromPool((igMemoryPoolView *)allocatorFor(self)));
        created->_playerCount = playerCount;
        (igSmartPointer<beGeneraterInfoWork> &)geneRam->_work = created;
        setGeneEnemy(self, created, enemyRecNo(geneRam));
    }
    beGeneraterInfoWork *work = (igSmartPointer<beGeneraterInfoWork> &)geneRam->_work;
    beGeneraterData *data = dataOf(geneRam);
    beGeneraterPlayerData *playerData = ((ObjectListOf<beGeneraterPlayerData> *)data->_playerDataList)->get(work->_playerCount - 1);
    if (work->_isFreeze || work->_isSystemFreeze) {
        beGenerater_DropItemsForDead(self, ram, false);
        return;
    }
    switch (geneRam->_st1) {
    case 0: {
        bool ready = false;
        switch (*(char *)data->_startModeStr) {
        case 'd':
            ready = true;
            break;
        case 't':
            /* matching construct: the timer queries return a byte, masked before the test as retail does */
            if (beBaseInfoRam_HasTimer((beBaseInfoRam *)geneRam, "BOOT_TIMER") == 0) {
                beBaseInfoRam_StartTimer((beBaseInfoRam *)geneRam, "BOOT_TIMER", framesToTime(data->_startData));
            } else if (beBaseInfoRam_IsTimerExpired((beBaseInfoRam *)geneRam, "BOOT_TIMER")) {
                ready = true;
                beBaseInfoRam_RemoveTimer((beBaseInfoRam *)geneRam, "BOOT_TIMER");
            }
            break;
        case 'r': {
            float matrix[16];
            igMatrix44f_SetIdentity(matrix);
            igMatrix44f_SetTranslation(matrix, data->_pos.vec);
            if (beTargetObj_SelectTarget(matrix, "PLAYER", "NEAR") != 0) {
                float range = data->_startData;
                if (beTargetObj_GetTargetDistanceSq() <= range) {
                    ready = true;
                }
            }
            break;
        }
        }
        if (ready == false) {
            return;
        }
        nextState(geneRam);
    }
    /* fall through */
    case 1:
        {
            int total = playerData->_geneCount;
            work->_nokoriKazu = total - beGenerater_SpawnEnemies(self, ram, playerData->_geneMaxCount);
        }
        nextState(geneRam);
        if (work->_nokoriKazu <= 0) {
            nextState(geneRam);
            return;
        }
        switch (*(char *)data->_fillModeStr) {
        case 't':
            beBaseInfoRam_StartTimer((beBaseInfoRam *)geneRam, "GENE_TIMER", framesToTime(data->_fillData));
            break;
        }
        break;
    case 2:
        beGenerater_DropItemsForDead(self, ram, false);
        switch (*(char *)data->_fillModeStr) {
        case 'w':
            if (((igObjectList *)work->_enemyRamList)->_count == 0) {
                int remaining = work->_nokoriKazu;
                int wave = playerData->_geneMaxCount;
                if (spawnRemaining(self, ram, work, remaining < wave ? remaining : wave)) {
                    nextState(geneRam);
                    return;
                }
            }
            break;
        case 'a':
            if (((igObjectList *)work->_enemyRamList)->_count != playerData->_geneMaxCount) {
                if (spawnRemaining(self, ram, work, 1)) {
                    nextState(geneRam);
                    return;
                }
            }
            break;
        case 't':
            if (beBaseInfoRam_IsTimerExpired((beBaseInfoRam *)geneRam, "GENE_TIMER")) {
                if (spawnRemaining(self, ram, work, 1)) {
                    nextState(geneRam);
                    beBaseInfoRam_RemoveTimer((beBaseInfoRam *)geneRam, "GENE_TIMER");
                    return;
                }
                beBaseInfoRam_StartTimer((beBaseInfoRam *)geneRam, "GENE_TIMER", framesToTime(data->_fillData));
                return;
            }
            break;
        }
        break;
    case 3:
        beGenerater_DropItemsForDead(self, ram, true);
        if (((igObjectList *)work->_enemyRamList)->_count == 0) {
            if (data->_callLua != 0) {
                g_mdlEntity = 0;
                beLua__RunNamedChunk((beLua *)self->_luaManager, (const char *)data->_callLua, 0);
            }
            geneRam->_isRun = 0;
            ((igSmartPointer<beGeneraterInfoWork> &)geneRam->_work).clear();
            geneRam->_st0 = 1;
            geneRam->_st3 = 0;
            geneRam->_st2 = 0;
            geneRam->_st1 = 0;
        }
        break;
    }
}

int beGenerater_OnMessageText(beGenerater *self, beBaseInfoRam *ram, int message)
{
    beGeneraterInfoRam *geneRam = (beGeneraterInfoRam *)ram;
    beGeneraterInfoWork *work = (beGeneraterInfoWork *)geneRam->_work;
    beGeneraterData *data = dataOf(geneRam);
    if (beMessenger_GetStringCount((beMessenger *)self->_messenger) != 0) {
        const char *name = data->_name ? (const char *)data->_name : (const char *)emptyString;
        if (strcmp(beMessenger_GetString((beMessenger *)self->_messenger, 0), name) != 0) {
            return 1;
        }
    }
    switch (beMessenger_ResolveEnumValue((beMessenger *)self->_messenger, beGenerater_GetMsgActionEnum(), (const char *)message)) {
    case MSG_STOP:
        if (work != 0) {
            work->_isFreeze = 1;
        }
        break;
    case MSG_START:
        if (work == 0) {
            if (geneRam->_st0 == 0) {
                geneRam->_isRun = 1;
            }
        } else {
            work->_isFreeze = 0;
        }
        break;
    case MSG_ONFREEZE:
        if (work != 0) {
            work->_isSystemFreeze = 1;
        }
        break;
    case MSG_OFFREEZE:
        if (work != 0) {
            work->_isSystemFreeze = 0;
        }
        break;
    case MSG_STOPREVERS:
        if (work != 0) {
            work->_isFreeze = 1;
            igObjectList *enemies = (igObjectList *)work->_enemyRamList;
            int count = enemies->_count;
            for (int i = 0; i < count; i++) {
                beMessenger_PushArgContext((beMessenger *)self->_messenger);
                beBaseInfoRam *enemyRam = ((beBaseInfoRam **)((igObjectList *)work->_enemyRamList)->_data)[i];
                int ramNo = enemyRam->_ramNo;
                const char *parentName = (const char *)((beGeneraterInfo *)enemyRam->_parentInfo)->_name;
                beMessenger_SendNamed((beMessenger *)self->_messenger, "MODELCTRL", parentName ? parentName : (const char *)emptyString, ramNo, "SQ_ERAS");
                beMessenger_PopArgContext((beMessenger *)self->_messenger);
            }
            releaseAll((igObjectList *)work->_enemyRamList);
            setCapacity((igObjectList *)work->_enemyRamList, 0);
            /* matching construct: hand search — the unsigned conversion puts count first in the add (addu v0,s1,v0);
             * as an int add (+=, either operand order, a const count or the list's count()) the remaining count comes first */
            work->_nokoriKazu = (unsigned)count + work->_nokoriKazu;
            if (work->_nokoriKazu != 0 && geneRam->_st1 == 3) {
                geneRam->_st1 = 2;
                geneRam->_st3 = 0;
                geneRam->_st2 = 0;
            }
        }
        break;
    case MSG_RESET: {
        geneRam->_isRun = 0;
        igObject *held = (igObject *)geneRam->_work;
        IG_OBJECT_RELEASE(held);
        geneRam->_work = 0;
        geneRam->_st0 = 0;
        geneRam->_st3 = 0;
        geneRam->_st2 = 0;
        geneRam->_st1 = 0;
        break;
    }
    case MSG_RESTART: {
        geneRam->_isRun = 1;
        igObject *held = (igObject *)geneRam->_work;
        IG_OBJECT_RELEASE(held);
        geneRam->_work = 0;
        geneRam->_st1 = 0;
        geneRam->_st3 = 0;
        geneRam->_st2 = 0;
        break;
    }
    case MSG_PERFECTDROP:
        if (beMessenger_GetInt((beMessenger *)self->_messenger, 0) == 0) {
            self->_isPerfectDrop = 0;
        } else {
            self->_isPerfectDrop = 1;
        }
        break;
    }
    return 1;
}

igMetaObject *beGenerater_GetMeta(void)
{
    return g_beGenerater_metaObject;
}

#pragma pop
