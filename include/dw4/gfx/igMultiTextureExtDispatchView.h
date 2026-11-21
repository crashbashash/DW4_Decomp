#ifndef DW4_IGMULTITEXTUREEXTDISPATCHVIEW_H
#define DW4_IGMULTITEXTUREEXTDISPATCHVIEW_H
#include "dw4/core/igObjectDispatchView.h"

/* igMultiTextureExt's virtual functions as igTextureFunctionAttr calls them on the PS2 extension: slots 28 and
 * 29 are the kit's setTextureStageType and setTextureStageFunction (alchemy-kit_202309
 * include/igGfx/igMultiTextureExt.h), after igContextExt's slots 21-26 and DW4's slot 27. The stage type is the
 * kit's TEXTURE_STAGE_TYPE enum, which retail's caller loads as unsigned. ABI view only: never instantiated. */
class igMultiTextureExtDispatchView : public igObjectDispatchView {
public:
    virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25();
    virtual void d26(); virtual void d27();
    virtual void setTextureStageType(int stage, int functionType, unsigned int type); /* slot 28 */
    virtual void setTextureStageFunction(int stage, int functionType, int function); /* slot 29 */
};
#endif
