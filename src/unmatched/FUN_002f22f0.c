/* 0x002f22f0 — FUN_002f22f0. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
#include "dw4/reflected.h"
extern unsigned char GPR_00554994;

void FUN_002f22f0(igMemoryPool *arg0) {
    arg0->_localAllocated = 0;
    arg0->_localNetAllocated = 0;
    arg0->_localNetAllocatedHigh = 0;
    arg0->_localAllocatedWithOverhead = 0;
    arg0->_localNetAllocatedWithOverhead = 0;
    arg0->_localNetAllocatedWithOverheadHigh = 0;
    arg0->_localAllocationCount = 0;
    arg0->_localNetAllocationCount = 0;
    arg0->_localNetAllocationCountHigh = 0;
    arg0->_localFreed = 0;
    arg0->_localNetAllocated = 0;
    arg0->_localFreedWithOverhead = 0;
    arg0->_localNetAllocatedWithOverhead = 0;
    arg0->_localFreeCount = 0;
    arg0->_localNetAllocationCount = 0;
    arg0->_updateGlobalStatistics = 1;
    arg0->_updateStatistics = (unsigned char) GPR_00554994;
}
