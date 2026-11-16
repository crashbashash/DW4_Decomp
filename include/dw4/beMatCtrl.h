#ifndef DW4_BEMATCTRL_H
#define DW4_BEMATCTRL_H

struct beMatCtrl;
struct igMetaEnum;
struct igMetaObject;

#ifdef __cplusplus
extern "C" {
#endif

struct beMatCtrl *beMatCtrl_CreateInstance(int allocator);
struct igMetaEnum *beMatCtrl_GetMessageEnum(void);
int beMatCtrl_GetPlayerMatStat(struct beMatCtrl *self, int player);
int beMatCtrl_GetPlayerNo(struct beMatCtrl *self);
bool beMatCtrl_IsAllPlayer(struct beMatCtrl *self);
bool beMatCtrl_IsPlayer(struct beMatCtrl *self);
bool beMatCtrl_IsRideOffPlayer(struct beMatCtrl *self, int player);
bool beMatCtrl_IsRidePlayer(struct beMatCtrl *self, int player);
void beMatCtrl_SetRun(struct beMatCtrl *self, bool run);

extern struct igMetaObject *g_beMatCtrl_metaObject;

#ifdef __cplusplus
}
#endif

#endif
