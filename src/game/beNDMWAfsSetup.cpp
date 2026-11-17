#include "dw4/support/reflected.h"
#include "dw4/core/StringPool.h"
#include "dw4/game/beCri.h"
#include "dw4/game/ndmw/beNDMWAfsSetup.h"
#include "dw4/game/ndmw/beNDMWAfsSetupInfo.h"
#include "dw4/game/ndmw/beNDMWAfsStageLoad.h"
#include "dw4/game/beSystem.h"
#include "dw4/core/igDataLists.h"
#include "dw4/insight/igInsightCore.h"
#include "dw4/core/igObject.h"
#include "dw4/support/emptyString.h"

extern "C" void beNDMWAfsSetup_Activate(void);
extern "C" void beNDMWAfsSetup_Deactivate(void);
extern "C" void beNDMWAfsSetup_Start(void);
extern "C" void beNDMWAfsSetup_Update(void);
extern "C" int beNDMWAfsSetup_GetMeta(void);
extern "C" void beNDMWAfsStageLoad_Execute(void);
extern "C" int beNDMWAfsStageLoad_GetMeta(void);
extern "C" void beNDMWAfsSetup_Stop(beNDMWAfsSetup *self);
extern "C" char text_stagis08_igb[];
extern "C" int beNDMWAfsSetup_AddInfo(beNDMWAfsSetup *self, igObject *info);
extern "C" void beNDMWAfsSetup_RemoveAllInfo(beNDMWAfsSetup *self);

/* Empty virtual slot 21 */
void beNDMWAfsSetup_Activate(void)
{
}

/* Empty virtual slot 22 */
void beNDMWAfsSetup_Deactivate(void)
{
}

/* Empty virtual slot 23 */
void beNDMWAfsSetup_Start(void)
{
}

/* Finds the insight's beCri component (CRI sound middleware owner) and hands it to beCri_ReleasePartitions,
 * which tears down the global string/object lists. */
void beNDMWAfsSetup_Stop(beNDMWAfsSetup *self) {
    beCri_ReleasePartitions((beCri *)igInsightCore_FindManager((igInsightCore *)self->_insight, g_beCri_metaObject));
}

int beNDMWAfsSetup_AddInfo(beNDMWAfsSetup *self, igObject *info) {
    if (igObject_IsKindOf(info, g_beNDMWAfsSetupInfo_metaObject)) {
        beCri *cri = (beCri *)igInsightCore_FindManager((igInsightCore *)self->_insight, g_beCri_metaObject);
        if (cri == 0) return 0;
        ObjectList_AppendRetained((igObjectList *)self->_infoList, info);
        igInsightCore_AddToScheduler((igInsightCore *)self->_insight, (igObject *)self);
        beNDMWAfsSetupInfo *setup = (beNDMWAfsSetupInfo *)info;
        igObjectList *files = (igObjectList *)setup->_dataList;
        beCri_SetupPartitions(cri, files->_count, setup->_insideFiles);
        int i;
        for (i = 0; i < files->_count; i++) {
            beNDMWAfsSetupData *data = ((beNDMWAfsSetupData **)files->_data)[i];
            int count = data->_fileCount;
            beCri_LoadPartition(cri, i, data->_name ? (const char *)data->_name : emptyString, count);
        }
        beSystem *system = (beSystem *)igInsightCore_FindManager((igInsightCore *)self->_insight, g_beSystem_metaObject);
        if (g_stringPool == 0) {
            StringPool *pool = (StringPool *)StringPool_Allocate(16);
            if (pool != 0) pool = StringPool_Construct(pool);
            g_stringPool = pool;
        }
        const char *token = StringPool_Intern(g_stringPool, text_stagis08_igb);
        const char *old = (const char *)system->_nextStage;
        if (old != 0) {
            int *header = (int *)old - 2;
            int count = ((int *)old)[-1] - 1;
            ((int *)old)[-1] = count;
            if (count == 0) StringChunk_ReleaseHeader((StringChunk *)*header, (StringTokenHeader *)header);
        }
        system->_nextStage = (int)token;
        system->_isStageLoop = 0;
        return 1;
    }
    return 0;
}

void beNDMWAfsSetup_RemoveAllInfo(beNDMWAfsSetup *self) {
    igDataList *l;
    int n;
    int n2;
    int i;
    int j;
    igObject *p;

    l = (igDataList *)self->_infoList;
    n = l->_count;
    for (i = 0; i < n; i++) {
        p = ((igObject **)l->_data)[i];
        if (p != 0) {
            p->_refCount = p->_refCount - 1;
            if ((p->_refCount & 0x7FFFFF) == 0) {
                igObject_Destroy(p);
            }
        }
    }
    n2 = l->_count;
    for (j = 0; j < n2; j++) {
        ((igObject **)l->_data)[j] = 0;
    }
    l->_count = 0;
    if (!(0 < ((igDataList *)self->_infoList)->_count)) {
        List_Reserve((igDataList *)self->_infoList, 0, 4);
    }
    igInsightCore_RemoveFromScheduler((igInsightCore *)self->_insight, (igObject *)self);
}

/* Empty virtual slot 27 */
void beNDMWAfsSetup_Update(void)
{
}

void beNDMWAfsStageLoad_Execute(void)
{
}

int beNDMWAfsStageLoad_GetMeta(void)
{
    return (int)g_beNDMWAfsStageLoad_metaObject;
}

int beNDMWAfsSetup_GetMeta(void)
{
    return (int)g_beNDMWAfsSetup_metaObject;
}
