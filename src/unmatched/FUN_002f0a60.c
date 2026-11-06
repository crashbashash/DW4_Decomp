extern char DAT_004f9fe0[];
int FUN_00304430();
int FUN_00304680();
extern int DAT_004f90b0[4];
extern char * DAT_00586f70[4];
extern int DAT_00586f78[4];
extern int DAT_00586f80[4];
extern int DAT_00586f88[4];
extern int DAT_00586f90[4];
extern int DAT_00586f98[4];
extern int DAT_00586fa0[4];
extern int DAT_00586fa8[4];
extern int DAT_00586fb0[4];
extern int DAT_00586fb8[4];
extern int DAT_00586fc0[4];
extern int DAT_00586fc8[4];
void FUN_002f0a60(char *arg0) {
    if ((arg0 != 0) && (*arg0 != 0)) {
        FUN_00304430(&DAT_004f90b0[0], arg0);
        FUN_00304680();
    }
    FUN_00304430((int *)DAT_004f9fe0, DAT_00586f70[0], DAT_00586f78[0], DAT_00586f80[0], DAT_00586f88[0], DAT_00586f90[0], DAT_00586f98[0], DAT_00586fa0[0], (long long) DAT_00586fa8[0], (long long) DAT_00586fb0[0], (long long) DAT_00586fb8[0], (long long) DAT_00586fc0[0], (long long) DAT_00586fc8[0]);
    FUN_00304680();
}
