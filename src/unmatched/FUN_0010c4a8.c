typedef struct { unsigned short len; unsigned short rsvd; unsigned short proto; unsigned char src; char dst; int data; char buf[256]; } Hdr;
typedef struct { volatile int id; volatile int len; int b; volatile int busy; Hdr *tx; } D;
extern D DAT_00555bd0;
extern char DAT_00555c00[];
int FUN_00113f20(void);
int FUN_00113f78(void);
int FUN_0010c0a0(int, char);
void FUN_0010c0d0(int);
int FUN_0010c4a8(char *buf, int n) {
    int written = 0;
    int len = 0;
    int s;
    Hdr *h;
    char *p;
    if (DAT_00555bd0.busy) return -1;
    s = FUN_00113f20();
    DAT_00555bd0.busy = 1;
    h = (Hdr *)((unsigned int)DAT_00555c00 | 0x20000000);
    DAT_00555bd0.tx = h;
    p = h->buf;
    while (n--) {
        if (*buf == '\n') {
            *p++ = '\r';
            len++;
            if (len >= 256) break;
        }
        *p++ = *buf++;
        len++;
        written++;
        if (len >= 256) break;
    }
    DAT_00555bd0.len = len + 12;
    h->len = DAT_00555bd0.len;
    if (FUN_0010c0a0(DAT_00555bd0.id, h->dst) < 0) {
        DAT_00555bd0.busy = 0;
        if (s) FUN_00113f78();
        return -1;
    }
    while (DAT_00555bd0.busy) FUN_0010c0d0(DAT_00555bd0.id);
    if (s) FUN_00113f78();
    return written;
}
