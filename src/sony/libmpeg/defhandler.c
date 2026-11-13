#include "dw4/sony/libmpeg.h"

int sceIpuStopDMA(void *env);
int sceIpuRestartDMA(void *env);

/* The callbacks a stream starts with for sceMpegCbStopDMA and sceMpegCbRestartDMA. */
int _sceMpegDefaultStopDMA(sceMpeg *mp, sceMpegCbData *cbdata, void *anyData) {
    sceIpuStopDMA(mp->sys->ipu_dma_env);
    return 1;
}

int _sceMpegDefaultRestartDMA(sceMpeg *mp, sceMpegCbData *cbdata, void *anyData) {
    sceIpuRestartDMA(mp->sys->ipu_dma_env);
    return 1;
}
