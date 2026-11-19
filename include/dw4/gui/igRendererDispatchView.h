#ifndef DW4_IGRENDERERDISPATCHVIEW_H
#define DW4_IGRENDERERDISPATCHVIEW_H
#include "dw4/core/igObjectDispatchView.h"

struct igVisualContext;

/* igRenderer's virtual functions as igRenderer_SetVisualContext calls them: slot 21 prepares drawing on
 * the new visual context, slot 22 ends drawing on the old one (alchemy-kit_202309 include/igGui/igRenderer.h
 * declares initializeDrawing and terminateDrawing in that order). ABI view only: never instantiated. */
class igRendererDispatchView : public igObjectDispatchView {
public:
    virtual void initializeDrawing();                                       /* slot 21 */
    virtual void terminateDrawing();                                        /* slot 22 */
    igVisualContext *_visualContext;
};

#endif
