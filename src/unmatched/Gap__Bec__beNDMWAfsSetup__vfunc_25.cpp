#include "dw4/reflected.h"
extern "C" {
int igObject_IsKindOf(igObject *, int);
void *FUN_00236f80(int, int);
void FUN_00236be0(int, beNDMWAfsSetup *);
void FUN_0037d270(beCri *, int, int);
void FUN_0037d2a0(beCri *, int, const char *, int);
void ObjectList_AppendRetained(int, igObject *);
void *FUN_002eb010(int);
void *StringPool_Construct(void *);
const char *StringPool_Intern(void *, const char *);
void StringChunk_ReleaseHeader(int, int *);
extern void *DAT_00586f20[4];
extern int DAT_0058c110[4];
extern int DAT_00589ad8[4];
extern int DAT_00587d08[4];
extern char DAT_004e0858[];                 /* "" */
extern char DAT_00515710[];                 /* "stagis08.igb" */
int Gap__Bec__beNDMWAfsSetup__vfunc_25(beNDMWAfsSetup *self, igObject *info);
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
