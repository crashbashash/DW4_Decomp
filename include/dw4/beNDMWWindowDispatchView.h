#ifndef DW4_BENDMWWINDOWDISPATCHVIEW_H
#define DW4_BENDMWWINDOWDISPATCHVIEW_H
#include "dw4/igObjectDispatchView.h"

/* beNDMWWindow's virtual functions as the window files call them: slot 21 is the per-frame
 * update every window class overrides.
 * ABI view only: never instantiated. */
class beNDMWWindowDispatchView : public igObjectDispatchView {
public:
    virtual void Update();                                                  /* slot 21 */
};

#endif
