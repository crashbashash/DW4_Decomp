typedef struct UsrDataPic {
    char *addr;
    int size;
} UsrDataPic;

typedef struct UsrDataFrm {
    char pad[56];
    UsrDataPic *pic;
} UsrDataFrm;

typedef struct UsrDataPly {
    char pad[384];
    char *udbuf;
    int udbufsize;
    char *ud;
    int udsize;
} UsrDataPly;

void *memset(void *s, int c, unsigned int n);
void *memcpy(void *d, const void *s, unsigned int n);
int FUN_00294d28(void);
void FUN_00298ad0(UsrDataPly *ply, char *ud, int size);
void FUN_002b5770(char *addr, int size, char **data, int *len);

void FUN_00293e38(UsrDataPly *ply, UsrDataFrm *frm)
{
    UsrDataPic *pic = frm->pic;
    char *addr = pic->addr;
    int size = pic->size;
    char *data;
    int len;

    if (FUN_00294d28() != 1)
        return;
    if (ply->udbuf == 0)
        return;
    if (addr != 0 && size >= 5)
        FUN_002b5770(addr + 4, size - 4, &data, &len);
    else {
        data = 0;
        len = 0;
    }
    if (data != 0 && len > 0) {
        if (ply->udbufsize < len)
            len = ply->udbufsize;
        memset(ply->udbuf, 0, ply->udbufsize);
        memcpy(ply->udbuf, data, len);
        ply->ud = ply->udbuf;
        ply->udsize = len;
    } else {
        ply->ud = 0;
        ply->udsize = 0;
    }
    FUN_00298ad0(ply, ply->ud, ply->udsize);
}
