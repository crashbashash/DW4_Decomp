#ifndef DW4_BESAVEAPIDISPATCHVIEW_H
#define DW4_BESAVEAPIDISPATCHVIEW_H
#include "dw4/core/igObjectDispatchView.h"

/* beSaveApi's virtual functions: the request slots every save-request class overrides after
 * GetMeta (slot 20): start issues the request, poll reports whether it has finished, report
 * hands the result to the delivery, checksum sums the save image.
 * ABI view only: never instantiated. */
class beSaveApiDispatchView : public igObjectDispatchView {
public:
    virtual void start(beSvDeliver *deliver);                               /* slot 21 */
    virtual int poll();
    virtual void report(beSvDeliver *deliver);
    virtual int checksum(int *data, int size);
};

#endif
