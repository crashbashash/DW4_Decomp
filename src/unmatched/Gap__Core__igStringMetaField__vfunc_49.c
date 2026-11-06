typedef struct S { char pad8[8]; int f8; char pad12[26]; unsigned char f26; } S;
int strlen();

int Gap__Core__igStringMetaField__vfunc_49(S *arg0, int arg1) {
    int temp_a0;
    int var_s0;
    int len;

    if (arg0->f26 == 0) {
        return 0;
    }
    var_s0 = 0;
    temp_a0 = *(int *)(arg1 + arg0->f8);
    var_s0 += 4;
    if (temp_a0 != 0) {
        len = strlen(temp_a0) + 1;
        var_s0 += (len + 3) & ~3;
    }
    return var_s0;
}
