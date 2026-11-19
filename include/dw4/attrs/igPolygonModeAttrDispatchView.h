#ifndef DW4_IGPOLYGONMODEATTRDISPATCHVIEW_H
#define DW4_IGPOLYGONMODEATTRDISPATCHVIEW_H
#include "dw4/core/igObjectDispatchView.h"

/* igPolygonModeAttr's virtual functions: slot 30 stores how polygons are drawn (an IG_GFX_RENDER_MODE).
 * ABI view only: never instantiated. */
class igPolygonModeAttrDispatchView : public igObjectDispatchView {
public:
    virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29();
    virtual void SetMode(int mode);                                         /* slot 30 */
};

#endif
