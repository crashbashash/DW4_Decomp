/* libipu.h - Sony libipu: IPU reset, the IPU DMA pause/resume pair libmpeg's default callbacks use,
 * and the busy wait (Sony libipu.h). */
#ifndef DW4_SONY_LIBIPU_H
#define DW4_SONY_LIBIPU_H

/* What sceIpuStopDMA saves and sceIpuRestartDMA puts back: the to-IPU (channel 4) and from-IPU
 * (channel 3) DMA registers and the IPU's bit pointer and control. */
typedef struct sceIpuDmaEnv {
    unsigned int d4madr;
    unsigned int d4tadr;
    unsigned int d4qwc;
    unsigned int d4chcr;
    unsigned int d3madr;
    unsigned int d3qwc;
    unsigned int d3chcr;
    unsigned int ipubp;
    unsigned int ipuctrl;
} sceIpuDmaEnv;

void sceIpuInit(void);
void sceIpuStopDMA(sceIpuDmaEnv *env);
void sceIpuRestartDMA(sceIpuDmaEnv *env);
/* mode 0 waits until the IPU is idle, 1 returns whether it is busy; the timeout is not used */
int sceIpuSync(int mode, unsigned short timeout);

#endif
