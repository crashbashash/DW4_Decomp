#ifndef DW4_IGPROJECTIVESHADOWSHADER_H
#define DW4_IGPROJECTIVESHADOWSHADER_H

struct igProjectiveShadowShader;
struct igTextureFunctionAttr;
struct igMetaObject;

#ifdef __cplusplus
extern "C" {
#endif

void igProjectiveShadowShader_ConfigureSharedAttrs(void);
struct igMetaObject *igProjectiveShadowShader_GetOrCreateMetaObject(void);
extern struct igTextureFunctionAttr *g_shadowTextureFunctionAttr0[4];
void igProjectiveShadowShader_Initialize(struct igProjectiveShadowShader *self);

#ifdef __cplusplus
}
#endif

#endif
