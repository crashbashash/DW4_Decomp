#ifndef DW4_IGTEXTUREBINDATTRDISPATCHVIEW_H
#define DW4_IGTEXTUREBINDATTRDISPATCHVIEW_H
#include "dw4/igObjectDispatchView.h"

/* igTextureBindAttr's virtual functions: slot 31 retains a texture and stores it in _texture,
 * releasing the one it held.
 * ABI view only: never instantiated. */
class igTextureBindAttrDispatchView : public igObjectDispatchView {
public:
    virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30();
    virtual void setTexture(igObject *texture);                             /* slot 31 */
};

#endif
