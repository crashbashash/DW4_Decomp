#ifndef DW4_IGCAMERADISPATCHVIEW_H
#define DW4_IGCAMERADISPATCHVIEW_H
#include "dw4/igObjectDispatchView.h"

/* igCamera's virtual functions as the camera modes call them: a mode's attach handler calls slot 33
 * and its detach handler slot 34. Neither has a recovered name: igCamera's own bodies for both are
 * empty and no class overrides them.
 * ABI view only: never instantiated. */
class igCameraDispatchView : public igObjectDispatchView {
public:
    virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30();
    virtual void d31(); virtual void d32();
    virtual void vfunc_35();                                                /* slot 33 */
    virtual void vfunc_36();                                                /* slot 34 */
};

#endif
