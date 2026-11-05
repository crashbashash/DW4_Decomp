extern "C" {
int ObjectRef_Destruct_001c6460(int **, int);
int FUN_003b2f30(int **, int);
int FUN_003b2fb0(int **, int);
int ObjectRef_Destruct_00150eb0(int **, int);
int thunk_FUN_002ed460__002ff810(int **);
extern int DAT_0053dc30[4];
extern int DAT_0053f790[4];
int **FUN_003b3030(int **arg0, long long arg1);
}
int **FUN_003b3030(int **arg0, long long arg1) {
    if (arg0 != 0) {
        *arg0 = &DAT_0053f790[0];
        if (arg0 != 0) {
            *arg0 = &DAT_0053dc30[0];
            ObjectRef_Destruct_001c6460((int **)((char *)arg0 + 0x4C), -1);
            ObjectRef_Destruct_00150eb0((int **)((char *)arg0 + 0x48), -1);
            ObjectRef_Destruct_001c6460((int **)((char *)arg0 + 0x44), -1);
            ObjectRef_Destruct_001c6460((int **)((char *)arg0 + 0x40), -1);
            ObjectRef_Destruct_001c6460((int **)((char *)arg0 + 0x3C), -1);
            FUN_003b2f30((int **)((char *)arg0 + 0x38), -1);
            FUN_003b2fb0((int **)((char *)arg0 + 0x34), -1);
        }
        if (((long long) (arg1 << 0x30) >> 0x30) > 0) {
            thunk_FUN_002ed460__002ff810(arg0);
        }
    }
    return arg0;
}
