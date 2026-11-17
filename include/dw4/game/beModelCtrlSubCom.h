#ifndef DW4_BEMODELCTRLSUBCOM_H
#define DW4_BEMODELCTRLSUBCOM_H

struct beBaseInfoRam;
struct beModelCtrlHITBOX;
struct beModelCtrlSubCom;
struct igMetaObject;

#ifdef __cplusplus
extern "C" {
#endif

void beModelCtrlSubCom_AddHitBox(struct beModelCtrlSubCom *self, struct beModelCtrlHITBOX *hitBox);
void beModelCtrlSubCom_AddSound(struct beModelCtrlSubCom *self, const char *sndName, float startFrame);
void beModelCtrlSubCom_StopAll(struct beModelCtrlSubCom *self, struct beBaseInfoRam *ram);
void beModelCtrlSubCom_StopType(struct beModelCtrlSubCom *self, struct beBaseInfoRam *ram, struct igMetaObject *metaObject);
void beModelCtrlSubCom_Update(struct beModelCtrlSubCom *self, struct beBaseInfoRam *ram);

#ifdef __cplusplus
}

#include "dw4/maths/igVec3f.h"

extern "C" void beModelCtrlSubCom_AddEffect(struct beModelCtrlSubCom *self, const char *modelName, const char *seqName, float startFrame, const igVec3f &offset, igVec3f rotation, unsigned char isSeqDead, unsigned char isPositionLock);
#endif

#endif
