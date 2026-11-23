#ifndef DW4_IGWINDOWDISPATCHVIEW_H
#define DW4_IGWINDOWDISPATCHVIEW_H
#include "dw4/core/igObjectDispatchView.h"

namespace Gap { namespace Gfx { class igVisualContext; } }

/* igWindow's virtual functions as the game calls them on igPsx2Window: slot 36 returns the visual
 * context the window draws into (_vc), slot 41 whether the window is still open (_open).
 * ABI view only: never instantiated. */
class igWindowDispatchView : public igObjectDispatchView {
public:
    virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30();
    virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35();
    virtual Gap::Gfx::igVisualContext *getVisualContext();                  /* slot 36 */
    virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40();
    virtual int isOpen();                                                   /* slot 41 */
};

#endif
