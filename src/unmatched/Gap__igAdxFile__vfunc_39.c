int FUN_002eb010(int);
int StringChunk_ReleaseHeader(int, int *);
int StringPool_Construct(int);
int StringPool_Intern(int, int);
extern int DAT_00586f20[];
struct AX { char pad[40]; int f40; };
int Gap__igAdxFile__vfunc_39(struct AX *arg0, int arg1) {
    int s0;
    int *a0;
    int *hdr;
    int v;
    int obj;
    if (DAT_00586f20[0] == 0) {
        obj = FUN_002eb010(0x10);
        if (obj != 0) {
            obj = StringPool_Construct(obj);
        }
        DAT_00586f20[0] = obj;
    }
    s0 = StringPool_Intern(DAT_00586f20[0], arg1);
    a0 = (int *)arg0->f40;
    if (a0 != 0) {
        hdr = a0 - 2;
        v = a0[-1] - 1;
        a0[-1] = v;
        if (v == 0) {
            StringChunk_ReleaseHeader(*hdr, hdr);
        }
    }
    arg0->f40 = s0;
    return arg1;
}
