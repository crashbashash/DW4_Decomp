#ifndef DW4_BEPADDATA_H
#define DW4_BEPADDATA_H

struct bePadData;
struct igMetaObject;

#ifdef __cplusplus
extern "C" {
#endif

struct bePadData *bePadData_Create(int allocator);
void bePadData_UpdateButtons(struct bePadData *pad, int buttons);

extern struct igMetaObject *g_bePadData_metaObject;

#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
#include "dw4/maths/igVec2f.h"

extern "C" void bePadData_UpdateLeftStick(struct bePadData *pad, igVec2f stick);
extern "C" void bePadData_UpdateRightStick(struct bePadData *pad, igVec2f stick);
#endif

#endif
