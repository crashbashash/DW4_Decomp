int igMatrix44f_SetIdentity();
int FUN_001904f0();
int FUN_00190c60();
int Matrix44_Copy();
int Matrix44_SetTranslation();
extern int DAT_00562890[4];

typedef struct A { char pad[208]; unsigned char f208; } A;

void FUN_001d5f70(A *arg0, int arg1, int *arg2, int *arg3, int *arg4) {
    int spA0[4];
    int sp90[4];
    int sp50[16];

    Matrix44_Copy(arg4);
    FUN_001904f0(arg4, arg4, arg2);
    FUN_001904f0(arg4, arg4, arg3);
    igMatrix44f_SetIdentity(&sp50[0]);
    spA0[0] = 0x3F000000;
    spA0[2] = 0;
    spA0[1] = 0xBF000000;
    FUN_00190c60(&sp50[0], &spA0[0]);
    sp90[0] = 0x3F000000;
    sp90[2] = 0x3F800000;
    sp90[1] = 0x3F000000;
    Matrix44_SetTranslation(&sp50[0], &sp90[0]);
    if (arg0->f208 != 0) {
        FUN_001904f0(&sp50[0], &sp50[0], &DAT_00562890[0]);
    }
    FUN_001904f0(arg4, arg4, &sp50[0]);
}
