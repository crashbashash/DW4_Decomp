/* Hooks of the MPEG-2 video decoder that mpv_InstallHooks (mpvinst.c) points at the M2V entry points:
 * the word at 0x004bcbf8 says whether they are installed, the pointers after it are the entry points
 * in the order of the install. Each wrapper calls its hook when one is set. */
#include "dw4/cri/mpv.h"

extern int DAT_004bcbf8[4];
extern int (*DAT_004bcbfc)(void);
extern int (*DAT_004bcc00)(void);
extern int (*DAT_004bcc04)();
extern int (*DAT_004bcc08)();
extern int (*DAT_004bcc0c)(void);
extern int (*DAT_004bcc10)();
extern int (*DAT_004bcc14)();
extern int (*DAT_004bcc18)();
extern int (*DAT_004bcc1c)();
extern int (*DAT_004bcc20)();
extern int (*DAT_004bcc24)();
extern int (*DAT_004bcc28)();
extern int (*DAT_004bcc2c)();
extern int (*DAT_004bcc30)();
extern int (*DAT_004bcc34)();
extern int (*DAT_004bcc38)();
extern int (*DAT_004bcc3c)();
extern int (*DAT_004bcc40)();
extern int (*DAT_004bcc44)();
extern int (*DAT_004bcc48)();

int mpvhook_IsInstalled(void) {
    return DAT_004bcbf8[0];
}

int FUN_00285170(void) {
    if (DAT_004bcbfc != 0) {
        return DAT_004bcbfc();
    }
    return 0;
}

int FUN_002851a0(void) {
    if (DAT_004bcc00 != 0) {
        return DAT_004bcc00();
    }
    return 0;
}

void mpvhook_Init(int nobj, void *work, int size) {
    if (DAT_004bcc04 != 0) {
        DAT_004bcc04(nobj, work, size);
    }
}

void mpvhook_Finish(void) {
    if (DAT_004bcc08 != 0) {
        DAT_004bcc08();
    }
}

int mpvhook_Create(void) {
    if (DAT_004bcc0c != 0) {
        return DAT_004bcc0c();
    }
    return 0;
}

void mpvhook_Destroy(int lower) {
    if (DAT_004bcc10 != 0) {
        DAT_004bcc10(lower);
    }
}

void FUN_00285278(void) {
    if (DAT_004bcc18 != 0) {
        DAT_004bcc18();
    }
}

void mpvhook_SetCond(int lower, int no, int value) {
    if (DAT_004bcc14 != 0) {
        DAT_004bcc14(lower, no, value);
    }
}

void FUN_002852c8(void) {
    if (DAT_004bcc1c != 0) {
        DAT_004bcc1c();
    }
}

void FUN_002852f0(void) {
    if (DAT_004bcc20 != 0) {
        DAT_004bcc20();
    }
}

void FUN_00285318(void) {
    if (DAT_004bcc24 != 0) {
        DAT_004bcc24();
    }
}

void FUN_00285340(void) {
    if (DAT_004bcc28 != 0) {
        DAT_004bcc28();
    }
}

void mpvhook_SetBufEnt(int lower, int index, SfdSj *sj, MpvUsrDatFn fn, void *obj) {
    if (DAT_004bcc2c != 0) {
        DAT_004bcc2c(lower, index, sj, fn, obj);
    }
}

void mpvhook_SetSize(int lower, char *buf, int size) {
    if (DAT_004bcc30 != 0) {
        DAT_004bcc30(lower, buf, size);
    }
}

void mpvhook_SetFlagPtr(int lower, int index, int *flag) {
    if (DAT_004bcc34 != 0) {
        DAT_004bcc34(lower, index, flag);
    }
}

int mpvhook_Start(int lower, SfdSj *sj) {
    if (DAT_004bcc38 != 0) {
        return DAT_004bcc38(lower, sj);
    }
    return 0;
}

void mpvhook_GetPicInf(int lower, MpvPicInf *inf) {
    if (DAT_004bcc3c != 0) {
        DAT_004bcc3c(lower, inf);
    }
}

void mpvhook_GetInf(int lower, int *inf) {
    if (DAT_004bcc40 != 0) {
        DAT_004bcc40(lower, inf);
    }
}

void mpvhook_GetRate(int lower, int *a, int *b, int *c) {
    if (DAT_004bcc44 != 0) {
        DAT_004bcc44(lower, a, b, c);
    }
}

void mpvhook_GetDispSize(int lower, int *width, int *height) {
    if (DAT_004bcc48 != 0) {
        DAT_004bcc48(lower, width, height);
    }
}
