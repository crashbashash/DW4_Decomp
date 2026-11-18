#ifndef DW4_P2WATCHDOG_H
#define DW4_P2WATCHDOG_H

#include "dw4/p2/p2dma.h"

#ifdef __cplusplus
extern "C" {
#endif

extern int p2WatchdogThread;
/* written by thread code and the DMAC handlers while the watchdog thread reads it */
extern volatile p2DmaWatch p2DmaWatchFlags;

#ifdef __cplusplus
}
#endif

#endif
