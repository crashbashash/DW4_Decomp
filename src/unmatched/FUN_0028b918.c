int FUN_0028ba20();
int FUN_0028be88();
int FUN_0028c6f8();
int MPS_GetStartCodeKind();
typedef struct {
    char pad0[16];
    int mode;               /* +16 */
    char pad20[164];
    unsigned char kind;     /* +184 */
    char pad185[59];
    void (*cb)(int, int);   /* +244 */
    int cbArg;              /* +248 */
} Rd;
int FUN_0028b918(Rd *rd, int pos, int n, int *len, int *flags) {
    int ret;
    int t;

    *len = 0;
    t = MPS_GetStartCodeKind(pos);
    *flags = t;
    ret = 0;
    switch (t) {
    case 0x10000:
        ret = 1;
        FUN_0028ba20(rd, pos, len);
        break;
    case 0x20000:
        ret = 1;
        FUN_0028be88(rd, pos, len);
        break;
    case 0x40000:
        FUN_0028c6f8(rd, pos, len, rd->mode);
        if (rd->cb != 0) {
            rd->cb(rd->cbArg, rd->kind);
        }
        break;
    }
    return ret;
}
