extern int DAT_00491270[4];
extern int DAT_00491478[4];
extern int DAT_0056aef0[4];
extern int DAT_0056aef8[4];
extern long long DAT_0056af28[4];
extern int DAT_0056af40[4];
void FUN_001f8830(int arg0) {
    void **temp_a1;
    void *temp_v1;

    temp_a1 = (void **)(&DAT_0056af40[arg0]);
    temp_v1 = (void *)(*temp_a1);
    if (*(int *)((char *)(temp_v1) + 128) == 0) {
        *(int *)((char *)(temp_v1) + 128) = 1;
        DAT_0056aef0[0] += 1;
        if (*(int *)((char *)((*temp_a1)) + 124) == 1) {
            DAT_0056aef8[0] += 1;
        }
    }
    DAT_00491270[0] = 1;
    DAT_0056af28[0] += 1;
    DAT_00491478[0] |= 0x84;
}
