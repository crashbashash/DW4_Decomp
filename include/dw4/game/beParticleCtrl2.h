#ifndef DW4_BEPARTICLECTRL2_H
#define DW4_BEPARTICLECTRL2_H

struct beParticleCtrl2;
struct igMetaEnum;
struct igMetaObject;

#ifdef __cplusplus
extern "C" {
#endif

struct beParticleCtrl2 *beParticleCtrl2_CreateInstance(int allocator);
struct igMetaEnum *beParticleCtrl2_GetMessageEnum(void);

extern struct igMetaObject *g_beParticleCtrl2_metaObject;

#ifdef __cplusplus
}
#endif

#endif
