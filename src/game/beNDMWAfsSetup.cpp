#include "dw4/reflected.h"

extern "C" int beCri_ReleasePartitions(int);
extern "C" void Gap__Bec__beNDMWAfsSetup__vfunc_21(void);
extern "C" void Gap__Bec__beNDMWAfsSetup__vfunc_22(void);
extern "C" void Gap__Bec__beNDMWAfsSetup__vfunc_23(void);
extern "C" void Gap__Bec__beNDMWAfsSetup__vfunc_27(void);
extern "C" int Gap__Bec__beNDMWAfsSetup__vfunc_20(void);
extern "C" void * igInsightCore_FindManager(...);
extern "C" void *StringPool_Allocate(int);
extern "C" void *StringPool_Construct(void *);
extern "C" const char *StringPool_Intern(void *, const char *);
extern "C" void StringChunk_ReleaseHeader(int, int *);
extern "C" void Gap__Bec__beNDMWAfsStageLoad__vfunc_21(void);
extern "C" int Gap__Bec__beNDMWAfsStageLoad__vfunc_20(void);
extern "C" int g_beCri_metaObject[4];
extern "C" int g_beNDMWAfsSetup_metaObject[4];
extern "C" void Gap__Bec__beNDMWAfsSetup__vfunc_24(beNDMWAfsSetup *self);
extern "C" int igObject_IsKindOf(igObject *, int);
extern "C" void igInsightCore_AddToScheduler(int, beNDMWAfsSetup *);
extern "C" void beCri_SetupPartitions(beCri *, int, int);
extern "C" void beCri_LoadPartition(beCri *, int, const char *, int);
extern "C" void ObjectList_AppendRetained(int, igObject *);
extern "C" void *g_stringPool[4];
extern "C" int g_beNDMWAfsSetupInfo_metaObject[4];
extern "C" int g_beCri_metaObject[4];
extern "C" int g_beSystem_metaObject[4];
extern "C" char emptyString[];
extern "C" char DAT_00515710[];
extern "C" int Gap__Bec__beNDMWAfsSetup__vfunc_25(beNDMWAfsSetup *self, igObject *info);
extern "C" int igInsightCore_RemoveFromScheduler(int, beNDMWAfsSetup *);
extern "C" int List_Reserve(igDataList *, int, int);
extern "C" int igObject_Destroy(igObject *);
extern "C" void Gap__Bec__beNDMWAfsSetup__vfunc_26(beNDMWAfsSetup *arg0);
extern "C" int g_beNDMWAfsStageLoad_metaObject[4];

/* Empty virtual slot 21 */
void Gap__Bec__beNDMWAfsSetup__vfunc_21(void)
{
}

/* Empty virtual slot 22 */
void Gap__Bec__beNDMWAfsSetup__vfunc_22(void)
{
}

/* Empty virtual slot 23 */
void Gap__Bec__beNDMWAfsSetup__vfunc_23(void)
{
}

/* Finds the insight's beCri component (CRI sound middleware owner) and hands it to beCri_ReleasePartitions,
 * which tears down the global string/object lists. */
void Gap__Bec__beNDMWAfsSetup__vfunc_24(beNDMWAfsSetup *self) {
    beCri_ReleasePartitions(((int)igInsightCore_FindManager(self->_insight, g_beCri_metaObject[0])));
}

int Gap__Bec__beNDMWAfsSetup__vfunc_25(beNDMWAfsSetup *self, igObject *info) {
    if (igObject_IsKindOf(info, g_beNDMWAfsSetupInfo_metaObject[0])) {
        beCri *cri = (beCri *)igInsightCore_FindManager(self->_insight, g_beCri_metaObject[0]);
        if (cri == 0) return 0;
        ObjectList_AppendRetained(self->_infoList, info);
        igInsightCore_AddToScheduler(self->_insight, self);
        beNDMWAfsSetupInfo *setup = (beNDMWAfsSetupInfo *)info;
        igObjectList *files = (igObjectList *)setup->_dataList;
        beCri_SetupPartitions(cri, files->_count, setup->_insideFiles);
        int i;
        for (i = 0; i < files->_count; i++) {
            beNDMWAfsSetupData *data = ((beNDMWAfsSetupData **)files->_data)[i];
            int count = data->_fileCount;
            beCri_LoadPartition(cri, i, data->_name ? (const char *)data->_name : emptyString, count);
        }
        beSystem *system = (beSystem *)igInsightCore_FindManager(self->_insight, g_beSystem_metaObject[0]);
        if (g_stringPool[0] == 0) {
            void *pool = StringPool_Allocate(16);
            if (pool != 0) pool = StringPool_Construct(pool);
            g_stringPool[0] = pool;
        }
        const char *token = StringPool_Intern(g_stringPool[0], DAT_00515710);
        const char *old = (const char *)system->_nextStage;
        if (old != 0) {
            int *header = (int *)old - 2;
            int count = ((int *)old)[-1] - 1;
            ((int *)old)[-1] = count;
            if (count == 0) StringChunk_ReleaseHeader(*header, header);
        }
        system->_nextStage = (int)token;
        system->_isStageLoop = 0;
        return 1;
    }
    return 0;
}

void Gap__Bec__beNDMWAfsSetup__vfunc_26(beNDMWAfsSetup *arg0) {
    igDataList *l;
    int n;
    int n2;
    int i;
    int j;
    igObject *p;

    l = (igDataList *)arg0->_infoList;
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
    if (!(0 < ((igDataList *)arg0->_infoList)->_count)) {
        List_Reserve((igDataList *)arg0->_infoList, 0, 4);
    }
    igInsightCore_RemoveFromScheduler(arg0->_insight, arg0);
}

/* Empty virtual slot 27 */
void Gap__Bec__beNDMWAfsSetup__vfunc_27(void)
{
}

void Gap__Bec__beNDMWAfsStageLoad__vfunc_21(void)
{
}

int Gap__Bec__beNDMWAfsStageLoad__vfunc_20(void)
{
    return g_beNDMWAfsStageLoad_metaObject[0];
}

int Gap__Bec__beNDMWAfsSetup__vfunc_20(void)
{
    return g_beNDMWAfsSetup_metaObject[0];
}
