#ifndef DW4_IGRANDOMNUMBERDISPATCH_H
#define DW4_IGRANDOMNUMBERDISPATCH_H

#include "dw4/igObjectVirtuals.h"

/* The system's igMersenneTwisterRandomNumber seen through its vtable: slot 22 draws the next
 * 32-bit random number. */
class RandomNumberDispatch : public igObjectVirtuals {
public:
    DW4_SLOTS_1(t0)
    virtual unsigned int genrand();
};

#endif
