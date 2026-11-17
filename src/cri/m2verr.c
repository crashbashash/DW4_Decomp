#include "dw4/cri/m2v.h"

/* CRI M2V error information: the library-wide record and each handle's own, and the error-code report. */
void M2VERR_InitErrInf(M2vErrInf *inf);
int m2verr_SetCodeSub(M2vErrInf *inf, int code);

M2vErrInf m2verrinf;

void M2VERR_Init(void)
{
    M2VERR_InitErrInf(&m2verrinf);
}

void M2VERR_InitErrInf(M2vErrInf *inf)
{
    inf->func = 0;
    inf->obj = 0;
    inf->code = 0;
    inf->reserved[0] = 0;
    inf->reserved[1] = 0;
}

void M2V_SetErrFunc(M2vObj *hn, int (*func)(void *obj), void *obj)
{
    M2vErrInf *inf;

    if (M2VLIB_CheckHn(hn) != 0) {
        M2VERR_SetCode(0, 0xFF030203);
        return;
    }
    inf = &hn->err;
    inf->func = func;
    inf->obj = obj;
}

void M2V_GetErrInf(M2vObj *hn, M2vErrInf *inf)
{
    if (M2VLIB_CheckHn(hn) != 0) {
        M2VERR_SetCode(0, 0xFF030204);
        return;
    }
    *inf = hn->err;
}

int M2VERR_SetCode(M2vObj *hn, int code)
{
    if (hn == 0) {
        m2verr_SetCodeSub(&m2verrinf, code);
    } else {
        m2verr_SetCodeSub(&hn->err, code);
    }
    return code;
}

int m2verr_SetCodeSub(M2vErrInf *inf, int code)
{
    inf->code = code;
    if (code != 0) {
        code = (int)inf->func;
        if (code != 0) {
            code = inf->func(inf->obj);
        }
    }
    return code;
}
