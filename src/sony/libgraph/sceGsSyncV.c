#include "dw4/sony/libgraph.h"
#include "dw4/libkernl.h"

#define GS_CSR (*(volatile unsigned long long *)0x12001000)
#define GS_CSR_FIELD 13

int sceGsSyncV(void)
{
    GsGParam *g = sceGsGetGParam();
    long long field;

    if (g->vsync_set == 0) {
        VSync();
        if (g->inter != 1) return 1;
        return (GS_CSR >> GS_CSR_FIELD) & 1;
    }
    field = (VSync2() >> GS_CSR_FIELD) & 1;
    if (g->inter != 1) return 1;
    return field;
}
