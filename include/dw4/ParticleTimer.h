#ifndef DW4_PARTICLETIMER_H
#define DW4_PARTICLETIMER_H

struct igMetaObject;

#ifdef __cplusplus
extern "C" {
#endif

struct igMetaObject *ParticleTimer_GetMetaObject(void);
void ParticleTimer_RegisterTraversalFunction(void);

extern struct igMetaObject *g_ParticleTimer_metaObject;

#ifdef __cplusplus
}
#endif

#endif
