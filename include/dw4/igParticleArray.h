#ifndef DW4_IGPARTICLEARRAY_H
#define DW4_IGPARTICLEARRAY_H

struct igParticleArray;
struct igMetaObject;
struct CallbackArray;

#ifdef __cplusplus
extern "C" {
#endif

void Gap__Gfx__igParticleArray__resetFields(struct igParticleArray *array);
void *igParticleArray_Destroy(struct igParticleArray *self, short flags);
struct CallbackArray *igParticleArray_Register(void);
int igParticleArray_Update(struct igParticleArray *self, unsigned int num, unsigned int offset, int *status, float time);
struct igMetaObject *igParticleArray_GetPublishedMetaObject(void);

#ifdef __cplusplus
}
#endif

#endif
