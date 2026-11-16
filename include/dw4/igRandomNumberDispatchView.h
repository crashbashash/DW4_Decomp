#ifndef DW4_IGRANDOMNUMBERDISPATCHVIEW_H
#define DW4_IGRANDOMNUMBERDISPATCHVIEW_H
#include "dw4/igObjectDispatchView.h"

/* igRandomNumber's virtual functions as the game calls them on the system's
 * igMersenneTwisterRandomNumber, named after the Mersenne Twister reference routines they are:
 * slot 21 seeds the state with the 69069 generator, slot 22 draws the next tempered 32-bit number.
 * ABI view only: never instantiated. */
class igRandomNumberDispatchView : public igObjectDispatchView {
public:
    virtual void sgenrand(unsigned int seed);                               /* slot 21 */
    virtual unsigned int genrand();                                         /* slot 22 */
};

#endif
