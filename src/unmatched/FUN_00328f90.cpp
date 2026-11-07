extern "C" {
int strcpy(...);
int strlen(...);
extern int DAT_004f7910[4];
int FUN_00328f90(void **arg0, int *arg1);
}
class DW4VC_16_1 { public: virtual void d0(); virtual void d1(); virtual int vX(int); };
int FUN_00328f90(void **arg0, int *arg1) {
    int *var_s1;
    int temp_v0;

    var_s1 = (int *)(arg1);
    if (var_s1 == 0) {
        var_s1 = (int *)(&DAT_004f7910[0]);
    }
    temp_v0 = ((DW4VC_16_1 *)(arg0))->vX((int)(strlen(var_s1) + 1));
    if (temp_v0 != 0) {
        strcpy(temp_v0, var_s1);
    }
    return temp_v0;
}
