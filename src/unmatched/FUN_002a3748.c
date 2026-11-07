int FUN_002a37e0();
int FUN_002a3850();
int FUN_002a38f0();
int FUN_002a3908();
int FUN_002a3b70();
int FUN_002a3c38();
int FUN_002adc40();

int FUN_002a3748(void *arg0) {
    int temp_s0;
    int var_v0;

    var_v0 = FUN_002adc40(arg0, 5);
    if (var_v0 != 0) {
        if (FUN_002a38f0(arg0) == 1) {
            return 0;
        }
        FUN_002a37e0(arg0);
        if (*(int *)((char *)(arg0) + 72) == 2) {
            FUN_002a3850(arg0);
        }
        temp_s0 = FUN_002a3c38(arg0);
        FUN_002a3908(arg0);
        FUN_002a3b70(arg0);
        var_v0 = temp_s0;
        
        return var_v0;
    }
    return var_v0;
}
