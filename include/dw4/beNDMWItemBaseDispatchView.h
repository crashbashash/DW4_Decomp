#ifndef DW4_BENDMWITEMBASEDISPATCHVIEW_H
#define DW4_BENDMWITEMBASEDISPATCHVIEW_H
#include "dw4/igObjectDispatchView.h"

/* beNDMWItemBase's virtual functions as the item's users call them: slot 22 uses the item on a
 * player (beNDMWItemBase_Use, overridden by beNDMWItemDisk_Use and beNDMWItemInstant_Use) and reports
 * whether it took effect; slot 23 packs the item into an integer and slot 24 restores it from one
 * (beNDMWItemBase_Pack, beNDMWItemBase_Unpack).
 * ABI view only: never instantiated. */
class beNDMWItemBaseDispatchView : public igObjectDispatchView {
public:
    virtual void d21();
    virtual int Use(igObject *user, int playerNo);                          /* slot 22 */
    virtual int Pack();                                                     /* slot 23 */
    virtual void Unpack(int packed);                                        /* slot 24 */
};

#endif
