#ifndef DW4_IGTRANSFORMDISPATCHVIEW_H
#define DW4_IGTRANSFORMDISPATCHVIEW_H
#include "dw4/igObjectDispatchView.h"

/* igTransform's virtual functions: slot 35 stores the transform's matrix (igTransform_SetMatrix).
 * ABI view only: never instantiated. */
class igTransformDispatchView : public igObjectDispatchView {
public:
    virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30();
    virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34();
    virtual void SetMatrix(const float *matrix);                            /* slot 35 */
};

#endif
