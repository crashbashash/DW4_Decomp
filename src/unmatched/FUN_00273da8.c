typedef struct DvCiHandle {
    char b0, b1;
    char state;         /* 2 */
    char pad3[5];
    int totalSct;       /* 8 */
    int curSct;         /* 12 */
    int nreq;           /* 16 */
    int lastReq;        /* 20 */
    void *buf;          /* 24 */
    int req;            /* 28 */
    int base;           /* 32 */
    char pad36[32];
    unsigned char cmd[3];   /* 68 */
} DvCiHandle;

extern DvCiHandle DAT_004aa7c0[40];

DvCiHandle *FUN_00273da8(void)
{
    DvCiHandle *h = 0;
    int i;

    for (i = 0; i < 40; i++) {
        if (DAT_004aa7c0[i].b0 == 0)
            h = &DAT_004aa7c0[i];
    }
    return h;
}
