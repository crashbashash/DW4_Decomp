/* CRI LSC (link stream controller) object; src/cri/lsc.c. */
#ifndef DW4_CRI_LSC_H
#define DW4_CRI_LSC_H

#include "dw4/cri/sfdsj.h"

#define LSC_MAX_STM 16

/* One queued file range. */
typedef struct LscStm {
    int id;
    char *fname;
    int fname_sum;
    void *dir;
    int ofst;
    int nsct;
    int stat;
    int rdsct;
} LscStm;

typedef struct LscObj {
    signed char used;
    signed char stat;
    signed char reading;
    signed char loop;
    signed char pause;
    char pad5[3];
    SfdSj *sj;
    char pad12[8];
    int flow_min;
    int flow_max;
    int wpos;
    int rpos;
    int nstm;
    void *stm;
    int stm_size;
    int pad48;
    int pad52;
    LscStm stms[LSC_MAX_STM];
} LscObj;

#endif
