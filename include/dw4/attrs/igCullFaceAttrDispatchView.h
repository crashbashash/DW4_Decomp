#ifndef DW4_IGCULLFACEATTRDISPATCHVIEW_H
#define DW4_IGCULLFACEATTRDISPATCHVIEW_H
#include "dw4/core/igObjectDispatchView.h"

/* igCullFaceAttr's virtual functions: slot 30 stores the face culled (an IG_GFX_CULL_FACE_MODE), slot 31
 * switches culling on or off.
 * ABI view only: never instantiated. */
class igCullFaceAttrDispatchView : public igObjectDispatchView {
public:
    virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29();
    virtual void SetMode(int mode);                                         /* slot 30 */
    virtual void SetState(int enabled);                                     /* slot 31 */
};

#endif
