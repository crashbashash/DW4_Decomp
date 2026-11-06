/* Makes one call on the manager's `_sema` object (its virtual method at vtable offset 92) and
 * discards the four-byte result it returns through a hidden buffer. */
#include "dw4/reflected.h"
extern "C" {

void Gap__Core__igPsx2ThreadManager__vfunc_11(igPsx2ThreadManager *self);
}
/* Four-byte struct return stand-in (hidden return buffer). */
struct DW4SR4 { int w0; };
class DW4VCSR_92_0 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual DW4SR4 vX(); };
void Gap__Core__igPsx2ThreadManager__vfunc_11(igPsx2ThreadManager *self) {
    DW4SR4 discarded_result;
    void **semaphore;

    semaphore = (void **)(self->_sema);
    discarded_result = ((DW4VCSR_92_0 *)(semaphore))->vX();
}
