/* CRI MFCI: the cvFs device that serves files already in memory, named by address and size;
 * src/cri/mfci.c. */
#ifndef DW4_CRI_MFCI_H
#define DW4_CRI_MFCI_H

#include "dw4/cri/cri_cvfs.h"

#ifdef __cplusplus
extern "C" {
#endif

CvFsVtbl *mfCiGetInterface(void);

#ifdef __cplusplus
}
#endif

#endif
