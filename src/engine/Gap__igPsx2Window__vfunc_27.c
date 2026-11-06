int FUN_002eb010();
int StringChunk_ReleaseHeader();
int StringPool_Construct();
int *StringPool_Intern();
extern int DAT_00586f20[4];
void Gap__igPsx2Window__vfunc_27(int *arg0, char *arg1) {
    int *old;
    int *hdr;
    int *s;
    int v;
    if ((arg1 != 0) && (*arg1 != 0)) {
        if (DAT_00586f20[0] == 0) {
            v = FUN_002eb010(0x10);
            if (v != 0) {
                v = StringPool_Construct(v);
            }
            DAT_00586f20[0] = v;
        }
        s = StringPool_Intern(DAT_00586f20[0], arg1);
        old = (int *)arg0[8];
        if (old != 0) {
            hdr = old - 2;
            v = old[-1] - 1;
            old[-1] = v;
            if (v == 0) {
                StringChunk_ReleaseHeader(*hdr, hdr);
            }
        }
        arg0[8] = (int)s;
    }
}
