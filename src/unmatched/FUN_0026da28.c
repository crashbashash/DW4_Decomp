int FUN_002670e0();
int FUN_002671b8();
int FUN_002671c8();
int FUN_002671d8();
int FUN_002671e8();
int FUN_002672e8();
int FUN_00267300();
int FUN_00267330();
int FUN_002674b8();
int FUN_0026dae0();

void FUN_0026da28(void *arg0) {
    int temp_s0;
    int temp_s0_2;
    int temp_s1;
    int temp_s3;
    int temp_s4;

    temp_s1 = *(int *)((char *)(arg0) + 4);
    temp_s3 = FUN_002672e8(temp_s1);
    temp_s4 = FUN_00267300(temp_s1);
    temp_s0 = FUN_00267330(temp_s1);
    FUN_002674b8(temp_s1);
    temp_s0_2 = temp_s0 - temp_s3;
    FUN_002671d8(temp_s1, 0);
    *(int *)((char *)(arg0) + 144) = temp_s0_2;
    FUN_002671c8(temp_s1, temp_s0_2);
    FUN_002671e8(temp_s1, temp_s4);
    FUN_002670e0(temp_s1, temp_s3);
    FUN_002671b8(temp_s1, &FUN_0026dae0, arg0);
}
