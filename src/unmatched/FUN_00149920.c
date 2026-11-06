int igMetaEnum_Create();
extern int DAT_004879f0[4];
extern int DAT_00487a00[4];
extern int DAT_004d7db0[4];
extern int DAT_0055f898[4];
int FUN_00149920(void) {
    if (DAT_0055f898[0] == 0) {
        DAT_0055f898[0] = igMetaEnum_Create(&DAT_004d7db0[0], &DAT_004879f0[0], &DAT_00487a00[0], 4);
    }
    return DAT_0055f898[0];
}
