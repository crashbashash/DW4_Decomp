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

extern unsigned char D_004ab440[3];
extern int D_004ab444;
extern const char D_004f0348[], D_004f0360[], D_004f0380[];
extern void FUN_002739b8(DvCiHandle *, const char *);
extern int FUN_00271670(void);
extern int FUN_00271798(int, int, int, void *, unsigned char *);
extern void FUN_002716f8(int);
extern void FUN_00271a68(int);
extern void FUN_00272228(void);
extern void FUN_00272118(void);
extern void FUN_00116c80(int);
extern void FUN_0010b918(void *, void *);

int FUN_002740a0(DvCiHandle *h, int nsct, char *buf)
{
    int n, rem;
    int ready;

    if (h == 0) {
        FUN_002739b8(h, D_004f0348);
        return 0;
    }
    if (nsct < 0) {
        FUN_002739b8(h, D_004f0360);
        return 0;
    }
    if (buf == 0) {
        FUN_002739b8(h, D_004f0380);
        return 0;
    }
    if (h->state == 2)
        return 0;
    if (nsct == 0) {
        h->state = 1;
        return 0;
    }
    h->req = FUN_00271670();
    if (h->req == 0)
        return 0;
    rem = h->totalSct - h->curSct;
    n = nsct < rem ? nsct : rem;
    h->cmd[0] = D_004ab440[0];
    h->cmd[1] = D_004ab440[1];
    h->cmd[2] = D_004ab440[2];
    h->buf = buf;
    h->nreq = n;
    FUN_0010b918(buf, buf + (n << 11) - 1);
    if (FUN_00271798(h->req, h->base + h->curSct, h->nreq, h->buf, h->cmd) == 0) {
        FUN_002716f8(h->req);
        return 0;
    }
    ready = D_004ab444;
    if (ready == 1) {
        FUN_00116c80(0);
        FUN_00272228();
        FUN_00272118();
        FUN_00271a68(h->req);
        FUN_002716f8(h->req);
        h->req = 0;
        h->lastReq = nsct;
        h->state = ready;
        h->curSct += h->nreq;
    } else {
        h->state = 2;
    }
    return h->nreq;
}
