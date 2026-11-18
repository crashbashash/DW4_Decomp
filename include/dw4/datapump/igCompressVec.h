#ifndef DW4_IGCOMPRESSVEC_H
#define DW4_IGCOMPRESSVEC_H

struct igVec3fList;
struct igQuaternionfList;

#ifdef __cplusplus
extern "C" {
#endif

/* Quantizes every component of the list to 16 bits over the list's range: the lowest component goes to
 * `minimum`, the span to `range`. */
void igCompressVec3fList(struct igVec3fList *list, unsigned short *quantized, float *minimum, float *range);
void igCompressVec4fList(struct igQuaternionfList *list, short *quantized, float *minimum, float *range);

#ifdef __cplusplus
}
#endif

#endif
