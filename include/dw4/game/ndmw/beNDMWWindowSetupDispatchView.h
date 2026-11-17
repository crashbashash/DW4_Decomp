#ifndef DW4_BENDMWWINDOWSETUPDISPATCHVIEW_H
#define DW4_BENDMWWINDOWSETUPDISPATCHVIEW_H
#include "dw4/game/ndmw/beNDMWWindowDispatchView.h"

/* The windows that set up their models (the select and title windows): slot 22 is the per-window
 * model setup the window's update calls.
 * ABI view only: never instantiated. */
class beNDMWWindowSetupDispatchView : public beNDMWWindowDispatchView {
public:
    virtual void Setup();                                                   /* slot 22 */
};

#endif
