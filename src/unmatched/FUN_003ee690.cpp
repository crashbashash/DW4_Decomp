/* The last read is volatile so it is issued before the copy of arg0. */
#include "dw4/reflected.h"
extern "C" {
int memcpy(int, int, int);
int beNDMWDegiData__UpdateFieldsFromData(void *);
void FUN_003ee690(beNDMWDegiData *arg0, int arg1) {
    memcpy(arg0->_data, arg1, *(volatile int *)&arg0->_dataSize);
    beNDMWDegiData__UpdateFieldsFromData(arg0);
}
}
