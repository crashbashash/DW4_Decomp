int DeleteThread();
int FUN_0010b9c0();
int FUN_0010ba90();
int printf();
int FUN_001ea9c0();
int FUN_001eb570();
int FUN_001f0730();
int FUN_00203500();
int FUN_00204950();
int FUN_00206540();
int FUN_00207f30();
int FUN_00207fa0();
int FUN_0020ccd0();
int RemoveDmacHandler();
int RemoveIntcHandler();
int TerminateThread();
extern int DAT_00490b60[4];
extern int DAT_00490be0[4];
extern int DAT_00490be8[4];
extern int DAT_00490bf4[4];
extern int DAT_00491478[4];
extern int DAT_004965b8[4];
extern int DAT_004e4ed0[4];
extern int DAT_004e4ef0[4];
extern int DAT_004e4f10[4];
extern int DAT_004e4f30[4];
extern int DAT_004e4f50[4];
extern int DAT_004e4f80[4];
extern int DAT_004e4fb0[4];
extern int DAT_00568e38[4];
extern int DAT_00569190[4];
extern int DAT_00569194[4];
extern int DAT_00569198[4];
void FUN_001edf20(void) {
    FUN_00207fa0(FUN_00207f30(1));
    DAT_00491478[0] = 0x1FF;
    FUN_001ea9c0(1);
    FUN_00206540();
    if (DAT_00490b60[0] == 0) {
        printf(&DAT_004e4ed0[0]);
        DAT_00568e38[0] = 1;
        if (FUN_0010ba90(1) == 0) {
            printf(&DAT_004e4ef0[0]);
        }
        if (FUN_0010ba90(0) == 0) {
            printf(&DAT_004e4f10[0]);
        }
        if (FUN_0010ba90(2) == 0) {
            printf(&DAT_004e4f30[0]);
        }
        if (RemoveDmacHandler(1, DAT_00569194[0]) == -1) {
            printf(&DAT_004e4f50[0]);
        }
        if ((DAT_00569190[0] != -1) && (RemoveDmacHandler(0, DAT_00569190[0]) == -1)) {
            printf(&DAT_004e4f80[0]);
        }
        if (RemoveDmacHandler(2, DAT_00569198[0]) == -1) {
            printf(&DAT_004e4fb0[0]);
        }
        FUN_0020ccd0();
        FUN_0010b9c0(0);
        RemoveIntcHandler(0, DAT_00490be0[0]);
        if (DAT_00490be8[0] != -1) {
            FUN_0010b9c0(2);
            RemoveIntcHandler(2, DAT_00490be8[0]);
        }
        if (DAT_00490bf4[0] != -1) {
            FUN_0010b9c0(5);
            RemoveIntcHandler(5, DAT_00490bf4[0]);
        }
        TerminateThread(DAT_004965b8[0]);
        DeleteThread(DAT_004965b8[0]);
        FUN_001eb570();
        FUN_00203500();
        FUN_001f0730();
        FUN_00204950(3, 0);
        FUN_00204950(9, 0);
        FUN_00204950(0xA, 0);
        FUN_00204950(7, 0);
        FUN_00204950(8, 0);
        FUN_00204950(0xB, 0);
        FUN_00204950(0xD, 0);
        FUN_00204950(0, 0);
        FUN_00204950(1, 0);
        FUN_00204950(2, 0);
        FUN_00204950(4, 0);
        FUN_00204950(5, 0);
        FUN_00204950(6, 0);
    }
}
