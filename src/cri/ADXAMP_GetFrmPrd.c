/* CRI ADXAMP: measures the peak amplitude of each output channel, one frame at a time. */
#include "dw4/cri/sfdsj.h"

typedef struct AdxAmpObj {
    signed char used;       /* 0x00 */
    signed char stat;       /* 0x01 */
    signed char maxnch;     /* 0x02 */
    char pad3;
    SfdSj *sji[2];          /* 0x04: decoded samples in */
    SfdSj *sjo[2];          /* 0x0c: amplitude records out */
    int nsmpl[2];           /* 0x14: samples measured, per channel */
    int nch;                /* 0x1c */
    int sfreq;              /* 0x20 */
    float frmlen;           /* 0x24: seconds per measured frame */
    float frmprd;           /* 0x28 */
    int nfrm;               /* 0x2c */
} AdxAmpObj;

float ADXAMP_GetFrmPrd(AdxAmpObj *amp)
{
    return amp->frmprd;
}
