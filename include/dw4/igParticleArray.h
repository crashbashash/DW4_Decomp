#ifndef DW4_IGPARTICLEARRAY_H
#define DW4_IGPARTICLEARRAY_H

struct igParticleArray;

#ifdef __cplusplus
extern "C" {
#endif

void Gap__Gfx__igParticleArray__resetFields(struct igParticleArray *array);
void *igParticleArray_Destroy(struct igParticleArray *self, short flags);
void igParticleArray_Register(void);

#ifdef __cplusplus
}
#endif

#endif
