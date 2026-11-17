#ifndef DW4_BETARGETOBJ_H
#define DW4_BETARGETOBJ_H

struct beTargetObj;
struct igMetaObject;
struct igVec3f;

#ifdef __cplusplus
extern "C" {
#endif

struct beTargetObj *beTargetObj_CreateInstance(int allocator);
struct igVec3f *beTargetObj_GetOrigin(void);
int beTargetObj_GetPlayerCentre(float *out);
float beTargetObj_GetTargetBearing(float offset);
float beTargetObj_GetTargetDistanceSq(void);
struct igVec3f *beTargetObj_GetTargetPosition(void);
int beTargetObj_GetTargetRamNo(void);
unsigned char beTargetObj_SelectTarget(float *matrix, const char *group, const char *mode);
unsigned char beTargetObj_SetTarget(float *matrix, float *position);

extern struct igMetaObject *g_beTargetObj_metaObject;

#ifdef __cplusplus
}
#endif

#endif
