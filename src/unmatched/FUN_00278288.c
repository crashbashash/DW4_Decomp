typedef struct {
    char used;
    signed char stat;
    char pad2[2];
    int sctsize;
    int f8;
    int nsct;
    int pos;
    int nbyte;
    int reqsct;
    char name[20];
    int ofs;
    int len;
    int avail;
} MfCiFile;

extern char DAT_004f0dc8[];
extern char DAT_004f0de8[];
extern char DAT_004f0e08[];
void FUN_00277da0(void);
void FUN_00277db8(void);
void FUN_00277de8(MfCiFile *fh, const char *message);
char *FUN_00277e30(char *name, int *size);
void *memcpy(void *dst, const void *src, unsigned int n);
void *memset(void *dst, int value, unsigned int size);

int FUN_00278288(MfCiFile *fh, int nsct, char *buf)
{
    char *data;
    int size;
    int n;
    int ofs;
    int len;
    int avail;

    if (fh == 0) {
        FUN_00277de8(fh, DAT_004f0dc8);
        return 0;
    }
    if (nsct < 0) {
        FUN_00277de8(fh, DAT_004f0de8);
        return 0;
    }
    if (buf == 0) {
        FUN_00277de8(fh, DAT_004f0e08);
        return 0;
    }
    if (nsct == 0) {
        fh->stat = 1;
        return 0;
    }
    if (fh->stat == 2) {
        return 0;
    }
    FUN_00277da0();
    fh->nbyte = 0;
    n = fh->nsct - fh->pos;
    if (nsct < n) {
        n = nsct;
    }
    fh->reqsct = n;
    ofs = fh->pos * fh->sctsize;
    len = n * fh->sctsize;
    if (len == 0) {
        fh->stat = 1;
        FUN_00277db8();
        return 0;
    }
    fh->ofs = ofs;
    fh->len = len;
    fh->stat = 2;
    data = FUN_00277e30(fh->name, &size);
    avail = (size - fh->ofs < fh->len) ? size - fh->ofs : fh->len;
    FUN_00277db8();
    memcpy(buf, data + fh->ofs, fh->len);
    memset(buf + avail, 0, fh->len - avail);
    FUN_00277da0();
    fh->stat = 1;
    fh->pos += fh->reqsct;
    fh->nbyte = fh->reqsct * fh->sctsize;
    FUN_00277db8();
    return fh->reqsct;
}
