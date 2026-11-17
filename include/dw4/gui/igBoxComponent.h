#ifndef DW4_IGBOXCOMPONENT_H
#define DW4_IGBOXCOMPONENT_H

struct igMetaObject;

#ifdef __cplusplus
extern "C" {
#endif

struct igMetaObject *igBoxComponent_GetOrCreateMetaObject(void);
void igBoxComponent_RunStaticInit(void);

#ifdef __cplusplus
}
#endif

#endif
