extern char DAT_00580000[];
extern long long DAT_00586f70[4];
extern long long DAT_00586f78[4];
extern long long DAT_00586f80[4];
extern long long DAT_00586f88[4];
extern long long DAT_00586f90[4];
extern long long DAT_00586f98[4];
extern long long DAT_00586fa0[4];
extern long long DAT_00586fa8[4];
extern long long DAT_00586fb0[4];
extern long long DAT_00586fb8[4];
extern long long DAT_00586fc0[4];
extern long long DAT_00586fc8[4];
void FUN_002f2450(long long arg0, long long arg1, int arg2) {
    long long t;
    if (arg2 != 0) {
        t = (int)arg0;
        DAT_00586f70[0] += t;
        DAT_00586f80[0] += t;
        if (DAT_00586f88[0] < DAT_00586f80[0]) {
            DAT_00586f88[0] = DAT_00586f80[0];
        }
        t = (int)arg1;
        DAT_00586f90[0] += t;
        DAT_00586fa0[0] += t;
        if (DAT_00586fa8[0] < DAT_00586fa0[0]) {
            DAT_00586fa8[0] = DAT_00586fa0[0];
        }
        DAT_00586fb0[0] += 1;
        DAT_00586fc0[0] += 1;
        if (DAT_00586fc8[0] < DAT_00586fc0[0]) {
            DAT_00586fc8[0] = DAT_00586fc0[0];
        }
    } else {
        t = (int)arg0;
        DAT_00586f78[0] += t;
        DAT_00586f80[0] -= t;
        DAT_00586f98[0] += t;
        DAT_00586fa0[0] -= t;
        DAT_00586fb8[0] += 1;
        DAT_00586fc0[0] -= 1;
    }
}
