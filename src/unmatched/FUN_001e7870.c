int FUN_001e7930();
extern int DAT_00562c70[];
extern int DAT_00569330[4];
extern char DAT_00569340[];
extern char * DAT_0056ad80[4];
void FUN_001e7870(void) {
    int i;
    int j;
    int v;

    for (i = 0; i < 16; i++) {
        v = 0;
        if (i > 1) {
            v = i - 1;
        }
        DAT_00569330[0] = i;
        DAT_0056ad80[0] = &DAT_00569340[v * 0x1C0];
        for (j = 0; j < 28; j++) {
            FUN_001e7930(j, 0);
        }
        DAT_00562c70[i] = 0;
    }
    DAT_00569330[0] = 0;
    DAT_0056ad80[0] = &DAT_00569340[0];
}
