#ifndef DW4_BEPADDATA_H
#define DW4_BEPADDATA_H

struct bePadData;
struct igMetaObject;

#ifdef __cplusplus
extern "C" {
#endif

void bePadData_UpdateButtons(struct bePadData *pad, int buttons);


#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
#include "dw4/maths/igVec2f.h"

extern "C" void bePadData_UpdateLeftStick(struct bePadData *pad, igVec2f stick);
extern "C" void bePadData_UpdateRightStick(struct bePadData *pad, igVec2f stick);
#endif

#endif
