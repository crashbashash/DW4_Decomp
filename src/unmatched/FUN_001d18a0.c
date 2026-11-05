typedef struct K { char pad[16]; unsigned *keys; } K;
typedef struct S { char pad[24]; int f24; char pad2[28]; unsigned f56; } S;
void FUN_001d18a0(S *arg0, int *arg1, int *arg2, float *arg3, K *arg4, int arg5, unsigned arg6)
{
    unsigned a;
    unsigned *keys;
    if (arg5 <= 0) {
        *arg1 = 0;
        *arg2 = 0;
        *arg3 = 0.0f;
        return;
    }
    *arg2 = 0;
    while (*arg2 < arg5 && arg6 > arg4->keys[*arg2]) {
        *arg2 += 1;
    }
    if (*arg2 >= arg5) {
        if (arg0->f24 == 3) {
            *arg1 = arg5 - 1;
            *arg2 = 0;
            a = arg4->keys[*arg1];
            *arg3 = (float)(arg6 - a) / (float)(arg0->f56 - a);
            return;
        }
        *arg2 = arg5 - 1;
        *arg1 = arg5 - 1;
        *arg3 = 0.0f;
        return;
    }
    if (*arg2 == 0) {
        *arg1 = *arg2;
        *arg3 = 0.0f;
        return;
    }
    *arg1 = *arg2 - 1;
    keys = arg4->keys;
    a = keys[*arg1];
    *arg3 = (float)(arg6 - a) / (float)(keys[*arg2] - a);
}
