#ifndef DW4_BEBASEINFORAM_H
#define DW4_BEBASEINFORAM_H

struct beBaseInfoRam;
struct igMetaObject;

#ifdef __cplusplus
extern "C" {
#endif

void beBaseInfoRam_EnsureRegistered(void);
struct igMetaObject *beBaseInfoRam_GetOrCreateMetaObject(void);
struct igMetaObject *beBaseInfoRam_GetPublishedMetaObject(void);
float beBaseInfoRam_GetTimerFrameDelta(struct beBaseInfoRam *self, const char *name);
int beBaseInfoRam_HasTimer(struct beBaseInfoRam *self, const char *name);
int beBaseInfoRam_IsTimerExpired(struct beBaseInfoRam *self, const char *name);
void *beBaseInfoRam_Register(void);
void beBaseInfoRam_RemoveAllTimers(struct beBaseInfoRam *self);
void beBaseInfoRam_RemoveTimer(struct beBaseInfoRam *self, const char *name);
void beBaseInfoRam_SetAllTimerScales(struct beBaseInfoRam *self, float scale);
void beBaseInfoRam_StartTimer(struct beBaseInfoRam *self, const char *name, long long endTime);

extern int g_beBaseInfoRam_vtable[4];

#ifdef __cplusplus
}
#endif

#endif
