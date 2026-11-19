#ifndef DW4_P2WATCHDOG_H
#define DW4_P2WATCHDOG_H

#include "dw4/p2/p2dma.h"

#ifdef __cplusplus
extern "C" {
#endif

extern int p2WatchdogThread;
/* reset by p2SubmitDmaPacket on every packet while the watchdog thread counts it up to 60 */
extern volatile int p2WatchdogTicks;
/* written by thread code and the DMAC handlers while the watchdog thread reads it */
extern volatile p2DmaWatch p2DmaWatchFlags;

#ifdef __cplusplus
}
#endif

#endif
