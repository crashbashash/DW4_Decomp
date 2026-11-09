/* The size reads as unsigned so it is issued before the copy of arg0. */
#include "dw4/reflected.h"
static inline unsigned dataSize(const beNDMWDegiData *data) { return data->_dataSize; }
extern "C" {
int memcpy(int, int, int);
int beNDMWDegiData__UpdateFieldsFromData(void *);
void FUN_003ee690(beNDMWDegiData *arg0, int arg1) {
    memcpy(arg0->_data, arg1, dataSize(arg0));
    beNDMWDegiData__UpdateFieldsFromData(arg0);
}
}
