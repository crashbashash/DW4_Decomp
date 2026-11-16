#ifndef DW4_IGFILEVIRTUALS_H
#define DW4_IGFILEVIRTUALS_H

#include "dw4/igObjectVirtuals.h"

/* igFile seen through its vtable: open by name and mode, close, and read. */
class igFileVirtuals : public igObjectVirtuals {
public:
    DW4_SLOTS_1(t0) DW4_SLOTS_1(t1)
    virtual int openFile(int fileName, const char *mode);
    virtual void closeFile();
    virtual void read(int buffer, int size, int count);
};

#endif
