#ifndef DW4_IGSKELETONDISPATCHVIEW_H
#define DW4_IGSKELETONDISPATCHVIEW_H
#include "dw4/core/igObjectDispatchView.h"

/* igSkeleton's virtual functions as the game calls them: slot 25 looks a bone up by name (-1 when
 * the skeleton has none), the slot Gap::Sg::igSkeleton::vfunc_27 holds.
 * ABI view only: never instantiated. */
class igSkeletonDispatchView : public igObjectDispatchView {
public:
    virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24();
    virtual int FindBoneIndex(const char *name);                            /* slot 25 */
};

#endif
