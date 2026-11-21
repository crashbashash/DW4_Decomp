#ifndef DW4_IGCAPABILITYMANAGERDISPATCHVIEW_H
#define DW4_IGCAPABILITYMANAGERDISPATCHVIEW_H
#include "dw4/core/igObjectDispatchView.h"
#include "dw4/gfx/GfxMetaEnums.h"

/* igCapabilityManager's virtual functions as the attrs' getUnitCount calls them: slot 21 is the kit's
 * pure virtual getCapability (alchemy-kit_202309 include/igGfx/igCapabilityManager.h), the first slot the
 * class adds to igObject's. ABI view only: never instantiated. */
class igCapabilityManagerDispatchView : public igObjectDispatchView {
public:
    virtual int getCapability(IG_GFX_CAPABILITY which) const;              /* slot 21 */
};
#endif
