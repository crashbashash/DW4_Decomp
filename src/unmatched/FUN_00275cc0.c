typedef struct {
    char used;
    char cached;
    signed char state;
    char pad3[5];
    long long size;
    int nsct;
    int f20;
    int fd;
    int pos;
    char *buf;
    int req;
    int done;
    void *stm;
} HtCiFile;

extern int DAT_004aba00;
extern char DAT_004f0850[];
extern char DAT_004f0868[];
extern char DAT_004f0888[];
void FUN_002753d8(HtCiFile *h, const char *message);
int FUN_00275408(HtCiFile *h);
void *FUN_00271670(void);
void FUN_002754c0(HtCiFile *h, int nsct);
int FUN_00271888(void *stm, int fd, long pos, unsigned long nbyte, char *buf);
void FUN_00272228(void);
void FUN_00272118(void);
void FUN_002716f8(void *stm);

int FUN_00275cc0(HtCiFile *h, int nsct, char *buf)
{
    unsigned long nbyte;

    if (h == 0) {
        FUN_002753d8(h, DAT_004f0850);
        return 0;
    }
    if (nsct < 0) {
        FUN_002753d8(h, DAT_004f0868);
        return 0;
    }
    if (buf == 0) {
        FUN_002753d8(h, DAT_004f0888);
        return 0;
    }
    if (FUN_00275408(h) == 1) {
        return 0;
    }
    if (h->state == 2) {
        return 0;
    }
    if (nsct == 0) {
        h->state = 1;
        return 0;
    }
    h->stm = FUN_00271670();
    if (h->stm == 0) {
        return 0;
    }
    h->buf = buf;
    h->req = (nsct < h->nsct - h->pos) ? nsct : h->nsct - h->pos;
    nbyte = nsct << 11;
    if (h->size < nbyte) {
        nbyte = h->size;
    }
    FUN_002754c0(h, h->req);
    if (FUN_00271888(h->stm, h->fd, h->pos, nbyte, buf) == 0) {
        return 0;
    }
    if (DAT_004aba00 == 1) {
        FUN_00272228();
        FUN_00272118();
        h->pos += h->req;
        FUN_002716f8(h->stm);
        h->stm = 0;
        h->state = 1;
        h->done = h->req;
    } else {
        h->state = 2;
        h->done = 0;
    }
    h->f20 = 0;
    return h->req;
}
