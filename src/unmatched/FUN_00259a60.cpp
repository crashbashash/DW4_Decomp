extern "C" {
int FUN_0010f330(int *, int);
int FUN_0010f5b8(int);
int FUN_0010f970(int, void *, int);
int FUN_0010fbd0(int, int *, int);
char *FUN_002ee430(int);
extern int DAT_004ecf40[4];
extern int DAT_004ecf50[4];
extern char *DAT_0056df78[4];
extern char GPR_00554be8;

void FUN_00259a60(void) {
    struct { int len; int type; } hdr;
    char *buf;
    int h;

    buf = FUN_002ee430(0x200);
    while (1) {
        h = FUN_0010f330(&DAT_004ecf40[0], 3);
        if (FUN_0010f970(h, &hdr, 8) < 0) {
            FUN_0010f5b8(h);
            continue;
        }
        if (hdr.type == 0) {
            FUN_0010f5b8(h);
            continue;
        }
        if (hdr.len > 0) {
            FUN_0010f970(h, buf, hdr.len);
        }
        if (hdr.type == 1) {
            DAT_0056df78[0] = buf;
            buf[hdr.len] = 0;
            GPR_00554be8 = 1;
        }
        hdr.len = 0;
        hdr.type = 0;
        FUN_0010fbd0(h, &DAT_004ecf50[0], 2);
        FUN_0010f5b8(h);
    }
}
}
