int memset();
int FUN_002452d0();
int Memory_AllocateDefaultBuffer();
int Memory_FreeBufferAlias_002ed4b0();
extern unsigned int DAT_004986c0[4];
extern unsigned int DAT_004986c8[4];
extern unsigned int DAT_0056ded0[4];
extern int *DAT_0056ded8[4];
extern int DAT_0056dee0[4];
struct N { int a; struct N *next; };
void FUN_00245310(void) {
    unsigned int log, nlog, ncap, bytes;
    int *nt;
    unsigned int i;
    struct N *p; struct N *nx;
    if (DAT_0056ded8[0] == 0) {
        DAT_0056ded8[0] = (int *)Memory_AllocateDefaultBuffer(DAT_004986c8[0] * 4);
        memset(DAT_0056ded8[0], 0, DAT_004986c8[0] * 4);
        return;
    }
    if (DAT_0056dee0[0] == 0) {
        if (DAT_0056ded0[0] == 0) {
            Memory_FreeBufferAlias_002ed4b0(DAT_0056ded8[0], DAT_0056ded0[0]);
            DAT_0056ded8[0] = 0;
            DAT_004986c8[0] = 128;
            return;
        }
        log = DAT_004986c0[0];
        nlog = log;
        if (DAT_004986c8[0] < DAT_0056ded0[0]) {
            nlog = log + 1;
        } else if (DAT_0056ded0[0] < (DAT_004986c8[0] >> 1) && log > 7) {
            nlog = log - 1;
        }
        if (nlog != log) {
            ncap = 1 << nlog;
            bytes = ncap * 4;
            nt = (int *)Memory_AllocateDefaultBuffer(bytes);
            memset(nt, 0, bytes);
            for (i = 0; i < DAT_004986c8[0]; i++) {
                p = ((struct N **)DAT_0056ded8[0])[i];
                while (p != 0) {
                    nx = p->next;
                    FUN_002452d0(p, nt, ncap, nlog);
                    p = nx;
                }
            }
            DAT_004986c8[0] = ncap;
            DAT_004986c0[0] = nlog;
            Memory_FreeBufferAlias_002ed4b0(DAT_0056ded8[0]);
            DAT_0056ded8[0] = nt;
        }
    }
}
