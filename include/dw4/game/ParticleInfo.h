#ifndef DW4_PARTICLEINFO_H
#define DW4_PARTICLEINFO_H

struct ParticleInfo;
struct igMetaObject;

#ifdef __cplusplus
extern "C" {
#endif

struct igMetaObject *ParticleInfo_GetMeta(void);
void ParticleInfo_resetFields(struct ParticleInfo *self, int clearControls);

extern struct igMetaObject *g_ParticleInfo_metaObject;

#ifdef __cplusplus
}
#endif

#endif
