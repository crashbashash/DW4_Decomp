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

int FUN_002744a8(DvCiHandle *h)
{
    return (long)h->lastReq * 2048 >> 32;
}
