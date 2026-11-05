/* 0x00293118 — FUN_00293118. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_00276fb8();
int FUN_00292958();
int FUN_002936a8();
int FUN_00293728();
int FUN_00295808();
int FUN_002977f8();
int FUN_002982e8();
int FUN_00299eb8();
int FUN_0029a320();
int FUN_0029b240();
int memset();
extern int DAT_004bd0e0[4];
extern int DAT_004f3000[4];
void FUN_00293118(void *arg0) {
    int temp_a0;
    int temp_a0_2;
    int temp_a0_3;
    int temp_a0_6;
    void **temp_a0_4;
    void **temp_a0_5;

    if (arg0 != 0) {
        FUN_00295808();
        *(int *)((char *)(arg0) + 4) = 0;
        FUN_002982e8(arg0);
        temp_a0 = *(int *)((char *)(arg0) + 172);
        if (temp_a0 != 0) {
            FUN_002977f8(temp_a0);
        }
        temp_a0_2 = *(int *)((char *)(arg0) + 76);
        if (temp_a0_2 != 0) {
            FUN_00276fb8(temp_a0_2);
        }
        temp_a0_3 = *(int *)((char *)(arg0) + 68);
        if (temp_a0_3 != 0) {
            FUN_0029b240(temp_a0_3);
        }
        temp_a0_4 = (void **)(*(int *)((char *)(arg0) + 468));
        if (temp_a0_4 != 0) {
            ((int (*)())*(int *)((char *)((*temp_a0_4)) + 12))(temp_a0_4);
        }
        temp_a0_5 = (void **)(*(int *)((char *)(arg0) + 500));
        if (temp_a0_5 != 0) {
            ((int (*)())*(int *)((char *)((*temp_a0_5)) + 12))(temp_a0_5);
        }
        temp_a0_6 = *(int *)((char *)(arg0) + 64);
        if (temp_a0_6 != 0) {
            FUN_00292958(temp_a0_6);
        }
        FUN_00299eb8((char *)arg0 + 0x294);
        FUN_002936a8(arg0);
        if (FUN_00293728(arg0) != 0) {
            FUN_0029a320(&DAT_004f3000[0]);
        }
        memset(arg0, 0, 0x2B8);
        *(int *)((char *)(arg0) + 4) = 0;
        *(int *)((char *)(arg0) + 0) = (int)(&DAT_004bd0e0[0]);
    }
}
