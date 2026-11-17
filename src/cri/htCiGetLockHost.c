#include "dw4/cri/htci.h"
#include "dw4/cri/cri_srd.h"

int htCiGetLockHost(void) {
    return SRD_GetLockHost();
}
