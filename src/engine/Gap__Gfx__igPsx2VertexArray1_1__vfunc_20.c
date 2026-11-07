int FUN_0015e050();
int FUN_0017d170();
int FUN_0015e2b0();
extern int DAT_0055fac8[4];
void Gap__Gfx__igPsx2VertexArray1_1__vfunc_20(void *arg0, int arg1) {
    unsigned int var_a6;
    unsigned int *var_a5;
    unsigned int temp_a4;

    FUN_0015e050();
    if (DAT_0055fac8[0] == arg1) {
        FUN_0015e2b0(arg0, arg1);
    }
    FUN_0017d170(arg0);
    if (*(int *)((char *)(arg0) + 28) & 4) {
        var_a5 = (unsigned int *)(*(int *)((char *)(*(int *)((char *)(arg0) + 8)) + 8));
        for (var_a6 = 0; var_a6 < (unsigned int) *(int *)((char *)(arg0) + 12); var_a6++) {
            temp_a4 = *var_a5;
            *var_a5 = (temp_a4 & 0xFFFFFF) | (((temp_a4 >> 1) & 0x7F000000) + (temp_a4 & 0x01000000));
            var_a5 += 1;
        }
    }
}
