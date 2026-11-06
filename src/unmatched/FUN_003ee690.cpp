/* Calls memcpy(arg0->f28, arg1, arg0->f36) with the incoming a1 passed through, then
 * beNDMWDegiData__UpdateFieldsFromData(arg0); the last read is volatile so it is issued before the
 * copy of arg0 (default compiler). */
#include "dw4/reflected.h"
/* The retail unit was C++ with exceptions on (it keeps an exception index record);
 * the code is C, so the whole unit keeps C linkage. */
extern "C" {
int memcpy(int, int, int);
int beNDMWDegiData__UpdateFieldsFromData(void *);
void FUN_003ee690(beNDMWDegiData *arg0, int arg1) {
    memcpy(arg0->_data, arg1, *(volatile int *)&arg0->_dataSize);
    beNDMWDegiData__UpdateFieldsFromData(arg0);
}
} /* extern "C" */
