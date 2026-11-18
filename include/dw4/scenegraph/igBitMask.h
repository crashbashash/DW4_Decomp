#ifndef DW4_IGBITMASK_H
#define DW4_IGBITMASK_H

struct igBitMask;

#ifdef __cplusplus
extern "C" {
#endif

void igBitMask_ClearAll(struct igBitMask *mask);
void igBitMask_SetAll(struct igBitMask *mask);
void igBitMask_SetBitCount(struct igBitMask *mask, unsigned int bits);

struct igMetaObject *igBitMask_GetOrCreateMetaObject(void);

#ifdef __cplusplus
}
#endif

#endif
