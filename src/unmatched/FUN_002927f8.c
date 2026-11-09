typedef struct UsrBufAttachUsrBuf {
    char *addr;
    int size;
    int unit;
} UsrBufAttachUsrBuf;

typedef struct UsrBufAttachPly {
    char pad[28];
    int count;
    char pad32[32];
    int handle;
    char pad68[312];
    UsrBufAttachUsrBuf *usrbuf;
} UsrBufAttachPly;

extern char DAT_004f2c98[];
extern char DAT_004f2cd0[];
int FUN_00294d28(void);
void FUN_0029a320(const char *format, ...);
void FUN_002a34d0(int handle, char *addr, int count, int unit);

void FUN_002927f8(UsrBufAttachPly *ply)
{
    UsrBufAttachUsrBuf *buf = ply->usrbuf;
    char *addr;
    int count;
    int unit;

    if (buf == 0) {
        FUN_0029a320(DAT_004f2c98);
        return;
    }
    unit = buf->unit;
    count = ply->count + 4;
    addr = buf->addr;
    if (buf->size < count * unit) {
        FUN_0029a320(DAT_004f2cd0);
        return;
    }
    if (FUN_00294d28() != 1)
        return;
    FUN_002a34d0(ply->handle, addr, count, unit);
}
