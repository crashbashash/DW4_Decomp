#ifndef DW4_IGVERTEXSTREAMDISPATCHVIEW_H
#define DW4_IGVERTEXSTREAMDISPATCHVIEW_H
#include "dw4/core/igObjectDispatchView.h"
#include "dw4/core/igSmartPointer.h"
#include "dw4/gfx/GfxMetaEnums.h"

/* igVertexStream's virtual functions as igVertexArray2 calls them on its stream (alchemy-kit_202309
 * igGfx/igVertexStream.h order: getRawVertexStream, getEditableComponent, commitComponentEdits, configure, reset).
 * ABI view only: never instantiated. */
class igVertexStreamDispatchView : public igObjectDispatchView {
public:
    virtual void d21(); virtual void d22(); virtual void d23();
    virtual bool configure(igSmartPointer<igVertexDataList> vertexDataList, igIndexArray *indexArray,
                           igPrimLengthArray *primLengthArray, igVisualContext *vc);   /* slot 24 */
    virtual void reset();                                                              /* slot 25 */
};

#endif
