int FUN_002670e0();
int ADXSJD_EntryTrapFunc();
int ADXSJD_SetTrapNumSmpl();
int ADXSJD_SetTrapCnt();
int ADXSJD_SetTrapDtLen();
int ADXSJD_GetLpStartPos();
int FUN_00267300();
int ADXSJD_GetLpEndPos();
int FUN_002674b8();
int FUN_0026dae0();

void adxt_trap_entry_lp(void *arg0) {
    int temp_s0;
    int temp_s0_2;
    int temp_s1;
    int temp_s3;
    int temp_s4;

    temp_s1 = *(int *)((char *)(arg0) + 4);
    temp_s3 = ADXSJD_GetLpStartPos(temp_s1);
    temp_s4 = FUN_00267300(temp_s1);
    temp_s0 = ADXSJD_GetLpEndPos(temp_s1);
    FUN_002674b8(temp_s1);
    temp_s0_2 = temp_s0 - temp_s3;
    ADXSJD_SetTrapCnt(temp_s1, 0);
    *(int *)((char *)(arg0) + 144) = temp_s0_2;
    ADXSJD_SetTrapNumSmpl(temp_s1, temp_s0_2);
    ADXSJD_SetTrapDtLen(temp_s1, temp_s4);
    FUN_002670e0(temp_s1, temp_s3);
    ADXSJD_EntryTrapFunc(temp_s1, &FUN_0026dae0, arg0);
}
