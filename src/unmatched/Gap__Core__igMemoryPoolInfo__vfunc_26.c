int FUN_003065f0(int, int, int, int *, int, int);
int FUN_00306910(int, int, int, int *, int, int);
extern int DAT_004c2230[4];
extern int DAT_004c2238[4];
extern int DAT_004c2240[4];
extern int DAT_004c2248[4];
extern int DAT_004c2250[4];
extern int DAT_004c2258[4];
extern int DAT_004c2260[4];
extern int DAT_004c2268[4];
extern int DAT_004c2270[4];
extern int DAT_004c2278[4];
extern int DAT_004c2280[4];
extern int DAT_004c2288[4];
extern int DAT_004c2290[4];
extern int DAT_004c2298[4];
extern int DAT_004c22a0[4];
extern int DAT_004c22a8[4];
extern int DAT_004c22b0[4];
extern int DAT_004fb410[4];
extern int DAT_004fb418[4];
extern struct { char pad[56]; int i56; } * DAT_00586dc8[4];
void Gap__Core__igMemoryPoolInfo__vfunc_26(int *arg0, int *arg1, int arg2, int arg3) {
    
    if (arg2 == 0) {
        arg2 = DAT_00586dc8[0]->i56;
    }
    if (arg2 == 0) {
        *arg0 = DAT_004fb418[0];
    } else {
        FUN_00306910(arg2, arg3, DAT_004c2230[0], &arg1[2], arg1[2], 0);
        FUN_00306910(arg2, arg3, DAT_004c2238[0], &arg1[5], arg1[5], 0);
        FUN_00306910(arg2, arg3, DAT_004c2240[0], &arg1[6], arg1[6], 0);
        FUN_003065f0(arg2, arg3, DAT_004c2248[0], &arg1[7], arg1[7], 0);
        FUN_003065f0(arg2, arg3, DAT_004c2250[0], &arg1[8], arg1[8], 0);
        FUN_003065f0(arg2, arg3, DAT_004c2258[0], &arg1[9], arg1[9], 0);
        FUN_00306910(arg2, arg3, DAT_004c2260[0], &arg1[10], arg1[10], 0);
        FUN_00306910(arg2, arg3, DAT_004c2268[0], &arg1[11], arg1[11], 0);
        FUN_00306910(arg2, arg3, DAT_004c2270[0], &arg1[12], arg1[12], 0);
        FUN_00306910(arg2, arg3, DAT_004c2278[0], &arg1[13], arg1[13], 0);
        FUN_00306910(arg2, arg3, DAT_004c2280[0], &arg1[14], arg1[14], 0);
        FUN_00306910(arg2, arg3, DAT_004c2288[0], &arg1[15], arg1[15], 0);
        FUN_00306910(arg2, arg3, DAT_004c2290[0], &arg1[16], arg1[16], 0);
        FUN_00306910(arg2, arg3, DAT_004c2298[0], &arg1[17], arg1[17], 0);
        FUN_00306910(arg2, arg3, DAT_004c22a0[0], &arg1[18], arg1[18], 0);
        FUN_00306910(arg2, arg3, DAT_004c22a8[0], &arg1[19], arg1[19], 0);
        FUN_003065f0(arg2, arg3, DAT_004c22b0[0], &arg1[20], arg1[20], 0);
        *arg0 = DAT_004fb410[0];
    }
}
