#ifndef DW4_IGVIEWMODEDISPATCHVIEW_H
#define DW4_IGVIEWMODEDISPATCHVIEW_H
#include "dw4/core/igObjectDispatchView.h"

/* igViewMode's virtual functions as igViewManager forwards its events to the current view mode:
 * slots 23 to 27 take the key, mouse, stick and controller-button events, slot 28 advances the
 * mode by a frame's time in seconds.
 * ABI view only: never instantiated. */
class igViewModeDispatchView : public igObjectDispatchView {
public:
    virtual void d21(); virtual void d22();
    virtual int OnKeyEvent();                                               /* slot 23 */
    virtual int OnMouseMove();                                              /* slot 24 */
    virtual int OnMouseButton();                                            /* slot 25 */
    virtual void OnStickEvent(int controller, int stick, float x, float y); /* slot 26 */
    virtual int OnButtonEvent();                                            /* slot 27 */
    virtual void Update(float seconds);                                     /* slot 28 */
};

#endif
