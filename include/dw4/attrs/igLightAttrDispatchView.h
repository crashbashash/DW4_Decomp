#ifndef DW4_IGLIGHTATTRDISPATCHVIEW_H
#define DW4_IGLIGHTATTRDISPATCHVIEW_H
#include "dw4/core/igObjectDispatchView.h"

/* igLightAttr's virtual functions: the setters store a colour or the position and mark the light
 * changed.
 * ABI view only: never instantiated. */
class igLightAttrDispatchView : public igObjectDispatchView {
public:
    virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29();
    virtual void setDiffuse(const float *rgba);                             /* slot 30 */
    virtual void setAmbient(const float *rgba);                             /* slot 31 */
    virtual void setSpecular(const float *rgba);                            /* slot 32 */
    virtual void setPosition(const float *position);                        /* slot 33 */
};

#endif
