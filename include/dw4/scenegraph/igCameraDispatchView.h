#ifndef DW4_IGCAMERADISPATCHVIEW_H
#define DW4_IGCAMERADISPATCHVIEW_H
#include "dw4/core/igObjectDispatchView.h"

/* igCamera's virtual functions as the camera modes call them: a mode's attach handler activates its
 * camera and its detach handler deactivates it (igCamera_<Name>).
 * ABI view only: never instantiated. */
class igCameraDispatchView : public igObjectDispatchView {
public:
    virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30();
    virtual void d31(); virtual void d32();
    virtual void Activate();                                                /* slot 33 */
    virtual void Deactivate();
};

#endif
