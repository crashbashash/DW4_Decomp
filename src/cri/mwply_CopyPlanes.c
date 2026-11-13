/* Copies an SFD plane layout into the order the SFX conversion takes: the three plane addresses
 * (base first) and the matching strides (luma, then chroma twice). */
#include "dw4/cri/sfmpv.h"

typedef struct MwsfdPlanes {
    char *addr0;
    char *addr1;
    char *addr2;
    int stride0;
    int stride1;
    int stride2;
} MwsfdPlanes;

void mwply_CopyPlanes(SfdPlanes *src, MwsfdPlanes *dst) {
    dst->addr0 = src->base;
    dst->addr1 = src->luma;
    dst->stride1 = src->chromaStride;
    dst->stride0 = src->lumaStride;
    dst->addr2 = src->chroma;
    dst->stride2 = src->chromaStride;
}
