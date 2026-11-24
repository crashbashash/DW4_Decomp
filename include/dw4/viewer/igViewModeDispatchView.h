#ifndef DW4_IGVIEWMODEDISPATCHVIEW_H
#define DW4_IGVIEWMODEDISPATCHVIEW_H
#include "dw4/core/igObjectDispatchView.h"

/* igViewMode's flag-taking virtual functions as igViewManager forwards its receiver events: retail hands the
 * receiver's bool flag to slots 23, 25 and 27 as it came in, where igViewMode's own declarations take it as an
 * int (igPickMode's tests of it do not mask), and the int form masks the flag first.
 * ABI view only: never instantiated. */
class igViewModeDispatchView : public igObjectDispatchView {
public:
    virtual void d21(); virtual void d22();
    virtual void OnKeyEvent(int key, bool down);                            /* slot 23 */
    virtual void d24();
    virtual void OnMouseButton(int button, bool pressed);                   /* slot 25 */
    virtual void d26();
    virtual void OnButtonEvent(void *controller, int key, bool down);       /* slot 27 */
};

#endif
