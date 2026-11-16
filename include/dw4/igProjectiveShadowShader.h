#ifndef DW4_IGPROJECTIVESHADOWSHADER_H
#define DW4_IGPROJECTIVESHADOWSHADER_H

struct igMetaObject;

#ifdef __cplusplus
extern "C" {
#endif

void igProjectiveShadowShader_ConfigureSharedAttrs(void);
struct igMetaObject *igProjectiveShadowShader_GetOrCreateMetaObject(void);

#ifdef __cplusplus
}
#endif

#endif
