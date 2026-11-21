#include "dw4/support/reflected.h"
#include "dw4/game/beBaseInfoManagerDispatchView.h"
#include "dw4/core/igobject_release.h"
#include "dw4/game/beBaseInfoManager.h"
#include "dw4/game/beMessenger.h"
#include "dw4/game/beSystem.h"
#include "dw4/core/igDataLists.h"
#include "dw4/insight/igInsightCore.h"
#include "dw4/core/igObject.h"

extern "C" void beBaseInfoManager_Activate(void);
extern "C" void beBaseInfoManager_Deactivate(void);
extern "C" void beBaseInfoManager_OnAddRam(void);
extern "C" igMetaObject *beBaseInfoManager_GetMeta(void);
extern "C" void beBaseInfoManager_RemoveAllInfo(beBaseInfoManager *self);
extern "C" void beBaseInfoManager_Update(beBaseInfoManager *self);

void beBaseInfoManager_Activate(void)
{
}

/* Slot 22 default: empty. */
void beBaseInfoManager_Deactivate(void)
{
}

void beBaseInfoManager_Start(beBaseInfoManager *self) {
    ((beBaseInfoManagerDispatchView *)self)->Prepare();
    self->_system = (int)(igInsightCore_FindManager((igInsightCore *)self->_insight, g_beSystem_metaObject));
    self->_messenger = (int)(igInsightCore_FindManager((igInsightCore *)self->_insight, g_beMessenger_metaObject));
}

/* Slot 24 default: empty. */
void beBaseInfoManager_Stop(beBaseInfoManager *self)
{
}

int beBaseInfoManager_AddInfo(beBaseInfoManager *self, beBaseInfo *info) {
    beBaseInfoManagerDispatchView *manager = (beBaseInfoManagerDispatchView *)self;
    igMetaObject *infoMeta = manager->GetInfoMeta();
    if (infoMeta == ((igObjectDispatchView *)info)->GetMeta()) {
        int count;
        int i;
        ObjectList_AppendRetained((igObjectList *)self->_infoList, (igObject *)info);
        manager->OnAddInfo(info);
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
            manager->OnAddRam(ram);
        }
        igInsightCore_AddToScheduler((igInsightCore *)self->_insight, (igObject *)self);
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

    ((beBaseInfoManagerDispatchView *)self)->Prepare();
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
        ((Gap::Core::igDataList *)infosForRelease)->setCapacity(0, 4);
    }
    igInsightCore_RemoveFromScheduler((igInsightCore *)self->_insight, (igObject *)self);
    self->_isUpdateRun = 0;
}

void beBaseInfoManager_Update(beBaseInfoManager *self) {
    int infoCount;
    int infoIndex;
    int ramCount;
    int ramIndex;
    beBaseInfoRamList *rams;
    if (beSystem_IsRunning((beSystem *)self->_system) && self->_isUpdateRun != 0 && ((beSystem *)self->_system)->_isFrameSkip == 0) {
        infoCount = ((beBaseInfoList *)self->_infoList)->_count;
        for (infoIndex = 0; infoIndex < infoCount; infoIndex++) {
            rams = (beBaseInfoRamList *)((beBaseInfo **)((beBaseInfoList *)self->_infoList)->_data)[infoIndex]->_ramList;
            ramCount = rams->_count;
            for (ramIndex = 0; ramIndex < ramCount; ramIndex++) {
                ((beBaseInfoManagerDispatchView *)self)->UpdateRam(((beBaseInfoRam **)rams->_data)[ramIndex]);
            }
        }
    }
}

igMetaObject *beBaseInfoManager_GetMeta(void)
{
    return g_beBaseInfoManager_metaObject;
}

