typedef struct WriteArea {
    char *addr0;
    int len0;
    char *addr1;
    int len1;
    int f16;
    int f20;
    int pad[2];
} WriteArea;

typedef struct PtsEntry {
    long long pts;
    char *addr;
    int len;
} PtsEntry;

typedef struct PtsNotify {
    long long pts;
    int len;
} PtsNotify;

typedef struct WriteObj {
    char pad[4824];
    char sub[4];
} WriteObj;

extern int (*DAT_004beb1c)(void *sub, PtsNotify *n);
int FUN_0028b0c0(void *dst, void *src, int n);
int FUN_0029dd80(WriteObj *obj, int ch, WriteArea *area);
int FUN_0029de58(WriteObj *obj, int ch, int len, int f20);
int FUN_002ac7f0(WriteObj *obj, int id, PtsEntry *e, void *out);
int FUN_002acaf0(WriteObj *obj, int id);

int FUN_002a2048(WriteObj *obj, int ch, char *data, int len, long long pts)
{
    WriteArea area;
    PtsEntry e;
    PtsNotify n;
    int out[4];
    int ret;
    char *addr0;
    char *addr1;
    int len0;
    int tag;

    ret = FUN_0029dd80(obj, ch, &area);
    if (ret != 0)
        return ret;
    len0 = area.len0;
    addr0 = area.addr0;
    addr1 = area.addr1;
    tag = area.f20;
    if (len0 + area.len1 < len)
        return 0;
    if (ch == 1) {
        if (pts >= 0) {
            if (FUN_002acaf0(obj, 1) != 0)
                return 0;
            e.pts = pts;
            e.addr = addr0;
            e.len = len;
            ret = FUN_002ac7f0(obj, 1, &e, out);
            if (ret != 0)
                return ret;
        }
    } else if (ch == 2) {
        if (DAT_004beb1c != 0) {
            n.pts = pts;
            n.len = len;
            if (DAT_004beb1c(obj->sub, &n) == -1)
                return 0;
        }
    }
    if (len0 >= len)
        FUN_0028b0c0(addr0, data, len);
    else {
        FUN_0028b0c0(addr0, data, len0);
        FUN_0028b0c0(addr1, data + len0, len - len0);
    }
    ret = FUN_0029de58(obj, ch, len, tag);
    if (ret == 0)
        ret = 1;
    return ret;
}
