#ifndef DW4_BEPADDATA_H
#define DW4_BEPADDATA_H

struct bePadData;
struct igMetaObject;

#ifdef __cplusplus
extern "C" {
#endif

struct bePadData *bePadData_Create(int allocator);
void bePadData_UpdateButtons(struct bePadData *pad, int buttons);
void bePadData_UpdateLeftStick(struct bePadData *pad, float *stick);
void bePadData_UpdateRightStick(struct bePadData *pad, float *stick);

extern struct igMetaObject *g_bePadData_metaObject;

#ifdef __cplusplus
}
#endif

#endif
