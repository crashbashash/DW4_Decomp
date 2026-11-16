/* libdma.h - Sony libdma: the calls made from outside the library (Sony libdma.h). */
#ifndef DW4_SONY_LIBDMA_H
#define DW4_SONY_LIBDMA_H

#ifdef __cplusplus
extern "C" {
#endif

/* Stops every channel and clears the controller's environment; `enable` 1 turns the controller back
 * on. Returns whether it was on. */
int sceDmaReset(int enable);

#ifdef __cplusplus
}
#endif

#endif
