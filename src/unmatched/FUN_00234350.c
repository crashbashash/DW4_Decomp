/* Float arguments (lwc1) for the converter calls. */
int printf();
int FUN_00230298(float);
extern int DAT_004e9650[4];
void FUN_00234350(int arg0, int arg1, float *arg2) {
    /* matching construct: variant search — decl order [1, 0]; the unit compiler (combat build -O3 -Iinclude) assigns stack slots and registers in declaration order, the reverse of the 2001 default */
    int temp_s1;
    int temp_s0;

    temp_s1 = FUN_00230298(arg2[0]);
    temp_s0 = FUN_00230298(arg2[1]);
    printf(&DAT_004e9650[0], arg0, arg1, temp_s1, temp_s0, FUN_00230298(arg2[2]));
}
