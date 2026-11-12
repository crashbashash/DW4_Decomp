#include "dw4/reflected.h"

extern "C" int FUN_0037d2f0(int);
extern "C" void Gap__Bec__beNDMWAfsSetup__vfunc_21(void);
extern "C" void Gap__Bec__beNDMWAfsSetup__vfunc_22(void);
extern "C" void Gap__Bec__beNDMWAfsSetup__vfunc_23(void);
extern "C" void Gap__Bec__beNDMWAfsSetup__vfunc_27(void);
extern "C" int Gap__Bec__beNDMWAfsSetup__vfunc_20(void);
extern "C" void * FUN_00236f80(...);
extern "C" void *FUN_002eb010(int);
extern "C" void *StringPool_Construct(void *);
extern "C" const char *StringPool_Intern(void *, const char *);
extern "C" void StringChunk_ReleaseHeader(int, int *);
extern "C" void Gap__Bec__beNDMWAfsStageLoad__vfunc_21(void);
extern "C" int Gap__Bec__beNDMWAfsStageLoad__vfunc_20(void);
extern "C" int g_beCri_metaObject[4];
extern "C" int g_beNDMWAfsSetup_metaObject[4];
extern "C" void Gap__Bec__beNDMWAfsSetup__vfunc_24(beNDMWAfsSetup *self);
extern "C" int igObject_IsKindOf(igObject *, int);
extern "C" void FUN_00236be0(int, beNDMWAfsSetup *);
extern "C" void FUN_0037d270(beCri *, int, int);
extern "C" void FUN_0037d2a0(beCri *, int, const char *, int);
extern "C" void ObjectList_AppendRetained(int, igObject *);
extern "C" void *DAT_00586f20[4];
extern "C" int DAT_0058c110[4];
extern "C" int DAT_00589ad8[4];
extern "C" int DAT_00587d08[4];
extern "C" char DAT_004e0858[];
extern "C" char DAT_00515710[];
extern "C" int Gap__Bec__beNDMWAfsSetup__vfunc_25(beNDMWAfsSetup *self, igObject *info);
extern "C" int FUN_00236c40(int, beNDMWAfsSetup *);
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

/* Finds the insight's beCri component (CRI sound middleware owner) and hands it to FUN_0037d2f0,
 * which tears down the global string/object lists. */
void Gap__Bec__beNDMWAfsSetup__vfunc_24(beNDMWAfsSetup *self) {
    FUN_0037d2f0(((int)FUN_00236f80(self->_insight, g_beCri_metaObject[0])));
}

int Gap__Bec__beNDMWAfsSetup__vfunc_25(beNDMWAfsSetup *self, igObject *info) {
    if (igObject_IsKindOf(info, DAT_0058c110[0])) {
        beCri *cri = (beCri *)FUN_00236f80(self->_insight, DAT_00589ad8[0]);
        if (cri == 0) return 0;
        ObjectList_AppendRetained(self->_infoList, info);
        FUN_00236be0(self->_insight, self);
        beNDMWAfsSetupInfo *setup = (beNDMWAfsSetupInfo *)info;
        igObjectList *files = (igObjectList *)setup->_dataList;
        FUN_0037d270(cri, files->_count, setup->_insideFiles);
        int i;
        for (i = 0; i < files->_count; i++) {
            beNDMWAfsSetupData *data = ((beNDMWAfsSetupData **)files->_data)[i];
            int count = data->_fileCount;
            FUN_0037d2a0(cri, i, data->_name ? (const char *)data->_name : DAT_004e0858, count);
        }
        beSystem *system = (beSystem *)FUN_00236f80(self->_insight, DAT_00587d08[0]);
        if (DAT_00586f20[0] == 0) {
            void *pool = FUN_002eb010(16);
            if (pool != 0) pool = StringPool_Construct(pool);
            DAT_00586f20[0] = pool;
        }
        const char *token = StringPool_Intern(DAT_00586f20[0], DAT_00515710);
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
    FUN_00236c40(arg0->_insight, arg0);
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
