#ifndef DW4_IGVERTEXARRAY2_H
#define DW4_IGVERTEXARRAY2_H

struct igVertexArray2;
struct igVertexData;

#ifdef __cplusplus
extern "C" {
#endif

struct igVertexData *igVertexArray2__FindVertexData(struct igVertexArray2 *self, int componentType, int componentIndex);

#ifdef __cplusplus
}
#endif

#endif
