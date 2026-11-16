#include "dw4/reflected.h"
#include "dw4/beBaseInfoManagerVirtuals.h"
#include "dw4/igobject_release.h"

extern "C" void beBaseInfoManager_Activate(void);
extern "C" void beBaseInfoManager_Deactivate(void);
extern "C" void beBaseInfoManager_Stop(void);
extern "C" int igInsightCore_FindManager(...);
extern "C" int igInsightCore_AddToScheduler(...);
extern "C" int ObjectList_AppendRetained(...);
extern "C" void beBaseInfoManager_OnAddRam(void);
extern "C" int igInsightCore_RemoveFromScheduler(...);
extern "C" int List_Reserve(...);
extern "C" int igObject_Destroy(...);
extern "C" int beSystem_IsRunning(...);
extern "C" int beBaseInfoManager_GetMeta(void);
extern "C" int g_beSystem_metaObject[4];
extern "C" int g_beMessenger_metaObject[4];
extern "C" void beBaseInfoManager_Start(beBaseInfoManager *self);
extern "C" int beBaseInfoManager_AddInfo(beBaseInfoManager *self, beBaseInfo *info);
extern "C" void beBaseInfoManager_RemoveAllInfo(beBaseInfoManager *self);
extern "C" void beBaseInfoManager_Update(beBaseInfoManager *self);
extern "C" int g_beBaseInfoManager_metaObject[4];

void beBaseInfoManager_Activate(void)
{
}

/* Slot 22 default: empty. */
void beBaseInfoManager_Deactivate(void)
{
}

void beBaseInfoManager_Start(beBaseInfoManager *self) {
    ((beBaseInfoManagerVirtuals *)self)->prepare();
    self->_system = igInsightCore_FindManager(self->_insight, g_beSystem_metaObject[0]);
    self->_messenger = igInsightCore_FindManager(self->_insight, g_beMessenger_metaObject[0]);
}

/* Slot 24 default: empty. */
void beBaseInfoManager_Stop(void)
{
}

int beBaseInfoManager_AddInfo(beBaseInfoManager *self, beBaseInfo *info) {
    beBaseInfoManagerVirtuals *manager = (beBaseInfoManagerVirtuals *)self;
    int infoMeta = manager->getInfoMeta();
    if (infoMeta == ((igObjectVirtuals *)info)->getMeta()) {
        int count;
        int i;
        ObjectList_AppendRetained(self->_infoList, info);
        manager->onAddInfo(info);
        count = ((beBaseInfoRamList *)info->_ramList)->_count;
        for (i = 0; i < count; i++) {
            beBaseInfoRam *ram = ((beBaseInfoRam **)((beBaseInfoRamList *)info->_ramList)->_data)[i];
            ram->_st0 = 0;
            ram->_st3 = 0;
            ram->_st2 = 0;
            ram->_st1 = 0;
            ram->_parentManager = (int)self;
            ram->_parentInfo = (int)info;
            ram->_ramNo = i;
            manager->onAddRam(ram);
        }
        igInsightCore_AddToScheduler(self->_insight, self);
        self->_isUpdateRun = 1;
        return 1;
    }
    return 0;
}

void beBaseInfoManager_OnAddRam(void)
{
}

void beBaseInfoManager_RemoveAllInfo(beBaseInfoManager *self) {
    int infoCount;
    beBaseInfoList *infosForRelease;
    int infoIndex;
    beBaseInfoList *infos;
    beBaseInfoRamList *rams;
    int releaseCount;
    int ramCount;
    int clearCount;
    int ramIndex;
    int clearIndex;
    int releaseIndex;

    ((beBaseInfoManagerVirtuals *)self)->prepare();
    infos = (beBaseInfoList *)self->_infoList;
    infoCount = infos->_count;
    for (infoIndex = 0; infoIndex < infoCount; infoIndex++) {
        rams = (beBaseInfoRamList *)((beBaseInfo **)((beBaseInfoList *)self->_infoList)->_data)[infoIndex]->_ramList;
        ramCount = rams->_count;
        for (ramIndex = 0; ramIndex < ramCount; ramIndex++) {
            beBaseInfoRam *ram = ((beBaseInfoRam **)rams->_data)[ramIndex];
            ram->_parentManager = 0;
            ram->_parentInfo = 0;
        }
    }
    infosForRelease = (beBaseInfoList *)self->_infoList;
    releaseCount = infosForRelease->_count;
    for (releaseIndex = 0; releaseIndex < releaseCount; releaseIndex++) {
        igObject *info = ((igObject **)infosForRelease->_data)[releaseIndex];
        IG_OBJECT_RELEASE(info);
    }
    clearCount = infosForRelease->_count;
    for (clearIndex = 0; clearIndex < clearCount; clearIndex++) {
        ((void **)infosForRelease->_data)[clearIndex] = 0;
    }
    infosForRelease->_count = 0;
    infosForRelease = (beBaseInfoList *)self->_infoList;
    int ok = infosForRelease->_count > 0;
    if (ok == 0) {
        List_Reserve(infosForRelease, 0, 4);
    }
    igInsightCore_RemoveFromScheduler(self->_insight, self);
    self->_isUpdateRun = 0;
}

void beBaseInfoManager_Update(beBaseInfoManager *self) {
    int infoCount;
    int infoIndex;
    int ramCount;
    int ramIndex;
    beBaseInfoRamList *rams;
    if (beSystem_IsRunning(self->_system) != 0 && self->_isUpdateRun != 0 && ((beSystem *)self->_system)->_isFrameSkip == 0) {
        infoCount = ((beBaseInfoList *)self->_infoList)->_count;
        for (infoIndex = 0; infoIndex < infoCount; infoIndex++) {
            rams = (beBaseInfoRamList *)((beBaseInfo **)((beBaseInfoList *)self->_infoList)->_data)[infoIndex]->_ramList;
            ramCount = rams->_count;
            for (ramIndex = 0; ramIndex < ramCount; ramIndex++) {
                ((beBaseInfoManagerVirtuals *)self)->updateRam(((beBaseInfoRam **)rams->_data)[ramIndex]);
            }
        }
    }
}

int beBaseInfoManager_GetMeta(void)
{
    return g_beBaseInfoManager_metaObject[0];
}

