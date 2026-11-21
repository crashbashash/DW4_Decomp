#ifndef DW4_IGCOLORATTRDISPATCHVIEW_H
#define DW4_IGCOLORATTRDISPATCHVIEW_H
#include "dw4/core/igObjectDispatchView.h"

/* igColorAttr's virtual functions: slot 30 stores the colour (Gap::Attrs::igColorAttr::set).
 * ABI view only: never instantiated. */
class igColorAttrDispatchView : public igObjectDispatchView {
public:
    virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29();
    virtual void SetColor(const float *rgba);                               /* slot 30 */
};

#endif
