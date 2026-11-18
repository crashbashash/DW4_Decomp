#ifndef DW4_IGCLEARRENDERER_H
#define DW4_IGCLEARRENDERER_H

#ifdef __cplusplus
extern "C" {
#endif

void igClearRenderer_EnsureRegistered(void);

struct igMetaObject *igClearRenderer_GetOrCreateMetaObject(void);

#ifdef __cplusplus
}
#endif

#endif
