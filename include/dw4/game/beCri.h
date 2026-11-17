#ifndef DW4_BECRI_H
#define DW4_BECRI_H

struct beCri;
struct beSoundData;
struct igMetaObject;
struct igObjectList;

#ifdef __cplusplus
extern "C" {
#endif

struct beCri *beCri_CreateInstance(int allocator);
void beCri_FadeByID(struct beCri *self, long long playID, float from, float to, float frames);
void beCri_FadeByName(struct beCri *self, char *name, float from, float to, float frames);
int beCri_FreeSfpData(struct beCri *self, int includeFirst);
unsigned char beCri_IsReady(struct beCri *self, const char *name);
bool beCri_IsTransferDone(struct beCri *self);
void beCri_LoadPartition(struct beCri *self, int partition, const char *path, int fileCount);
long long beCri_PlayEffect(struct beCri *self, struct igObjectList *names, struct beSoundData *cue);
long long beCri_PlayStream(struct beCri *self, struct igObjectList *names, struct beSoundData *cue);
void beCri_ReleasePartitions(struct beCri *self);
void beCri_SetFreezeAudible(struct beCri *self, int audible);
void beCri_SetFx(struct beCri *self, const char *name);
void beCri_SetSndfVolume(struct beCri *self, int volume);
void beCri_SetupPartitions(struct beCri *self, int count, int insideFiles);
bool beCri_StartSfpTransfers(struct beCri *self);
void beCri_StopByID(struct beCri *self, long long playID);
void beCri_StopGroup(struct beCri *self, int group);
void beCri_UnpauseByName(struct beCri *self, const char *name);

extern struct igMetaObject *g_beCri_metaObject;

#ifdef __cplusplus
}
#endif

#endif
