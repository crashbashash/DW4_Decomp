/* Hooks of the MPEG-2 video decoder that mpv_InstallHooks (mpvinst.c) points at the M2V entry points:
 * the word at 0x004bcbf8 says whether they are installed, the pointers after it are the entry points
 * in the order of the install. Each wrapper calls its hook when one is set. */
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
extern int (*DAT_004bcc38)(void);
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

void mpvhook_Init(void) {
    if (DAT_004bcc04 != 0) {
        DAT_004bcc04();
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

void mpvhook_Destroy(void) {
    if (DAT_004bcc10 != 0) {
        DAT_004bcc10();
    }
}

void FUN_00285278(void) {
    if (DAT_004bcc18 != 0) {
        DAT_004bcc18();
    }
}

void mpvhook_SetCond(void) {
    if (DAT_004bcc14 != 0) {
        DAT_004bcc14();
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

void mpvhook_SetBufEnt(void) {
    if (DAT_004bcc2c != 0) {
        DAT_004bcc2c();
    }
}

void mpvhook_SetSize(void) {
    if (DAT_004bcc30 != 0) {
        DAT_004bcc30();
    }
}

void mpvhook_SetFlagPtr(void) {
    if (DAT_004bcc34 != 0) {
        DAT_004bcc34();
    }
}

int mpvhook_Start(void) {
    if (DAT_004bcc38 != 0) {
        return DAT_004bcc38();
    }
    return 0;
}

void mpvhook_GetPicInf(void) {
    if (DAT_004bcc3c != 0) {
        DAT_004bcc3c();
    }
}

void mpvhook_GetInf(void) {
    if (DAT_004bcc40 != 0) {
        DAT_004bcc40();
    }
}

void mpvhook_GetRate(void) {
    if (DAT_004bcc44 != 0) {
        DAT_004bcc44();
    }
}

void mpvhook_GetDispSize(void) {
    if (DAT_004bcc48 != 0) {
        DAT_004bcc48();
    }
}
