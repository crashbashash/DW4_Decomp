/* 0x001ab4a0 — FUN_001ab4a0. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
#include "dw4/reflected.h"
int igObject_InitHeader();
extern int DAT_00524950[4];
extern int DAT_00528a90[4];
extern int DAT_00528dd0[4];
extern int DAT_00528fa0[4];
void *FUN_001ab4a0(igEnvironmentMapShader2 *arg0) {
    igObject_InitHeader();
    arg0->_vtable = (int)(&DAT_00524950[0]);
    arg0->_name = 0;
    arg0->_vtable = (int)(&DAT_00528a90[0]);
    arg0->_bound = 0;
    arg0->_parentList = 0;
    arg0->_vtable = (int)(&DAT_00528dd0[0]);
    arg0->_childList = 0;
    arg0->_vtable = (int)(&DAT_00528fa0[0]);
    arg0->_envMapTexture = 0;
    arg0->_diffuseTextureBind = 0;
    arg0->_glossMapTexture = 0;
    arg0->_attrPushLists = 0;
    arg0->_attrPopLists = 0;
    arg0->_envMapTextureBind = 0;
    arg0->_envMapCoordSource = 0;
    arg0->_envMapTextureFunc = 0;
    arg0->_diffuseCoordSource = 0;
    arg0->_diffuseTextureFunc = 0;
    arg0->_diffuseBlendState = 0;
    arg0->_glossMapTextureBind = 0;
    arg0->_glossMapCoordSource = 0;
    arg0->_glossMapTextureFunc = 0;
    return arg0;
}
