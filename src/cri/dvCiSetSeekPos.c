#include "dw4/cri/dvci.h"
#include "dw4/cri/cri_srd.h"

int dvCiSetSeekPos(int lsn) {
    return SRD_SetDvdSeekPos(lsn);
}
