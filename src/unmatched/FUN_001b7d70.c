float sqrtf(float);
struct V { float x, y, z, w; };
int FUN_00192fc0();
int FUN_001b9530();
int FUN_001d1da0(void *, float);
extern void * DAT_0055efe8[4];
int FUN_001b7d70(void *arg0, void *arg1) {
    struct V sp40;
    struct V sp30;
    float temp_f4;
    float temp_f3;
    float dist;
    float dx, dy, dz;
    float r;
    void *temp_a0;
    void *temp_a1;
    int temp_v0;
    int temp_v0_2;
    int temp_v1;
    int var_v0;
    int var_a2;

    sp30.x = *(float *)((char *)(arg1) + 76);
    sp30.y = *(float *)((char *)(arg1) + 80);
    sp30.z = *(float *)((char *)(arg1) + 84);
    temp_a1 = (void *)(*(int *)((char *)(arg0) + 52));
    temp_a0 = (void *)(*(int *)(*(int *)((char *)(*(int *)((char *)(temp_a1) + 16)) + 16) + (*(int *)(*(int *)((char *)(temp_a1) + 68) + (*(int *)((char *)(DAT_0055efe8[0]) + 8) * 4)) * 4)));
    temp_v0 = *(int *)((char *)(temp_a0) + 24);
    if (temp_v0 >= 0) {
        var_v0 = *(int *)(*(int *)((char *)(temp_a0) + 16) + (temp_v0 * 4));
    } else {
        temp_v0_2 = *(int *)((char *)(temp_a0) + 8);
        if (temp_v0_2 != 0) {
            var_v0 = *(int *)(*(int *)((char *)(temp_a0) + 16) + ((temp_v0_2 - 1) * 4));
        } else {
            var_v0 = *(int *)((char *)(temp_a0) + 20);
        }
    }
    var_a2 = var_v0 + 0xC;
    if (*(int *)((char *)(arg1) + 20) & 0x20) {
        return 0;
    }
    FUN_00192fc0(&sp40, &sp30, var_a2);
    dy = sp40.y;
    dx = sp40.x;
    dz = sp40.z;
    temp_f4 = *(float *)((char *)(arg1) + 88);
    temp_f3 = *(float *)((char *)(arg1) + 92);
    dist = sqrtf(dx * dx + dy * dy + dz * dz);
    if (dist <= temp_f4 || (temp_v1 = *(int *)((char *)(arg1) + 72)) == 3) {
        FUN_001d1da0(arg1, 1.0f);
    } else {
        if (!(dist < temp_f3)) {
            FUN_001d1da0(arg1, 0.0f);
        } else {
            r = (temp_f3 - dist) / (temp_f3 - temp_f4);
            if (temp_v1 == 0) {
                FUN_001d1da0(arg1, r);
            } else if (temp_v1 == 1) {
                FUN_001d1da0(arg1, r * r);
            } else if (temp_v1 == 2) {
                FUN_001d1da0(arg1, sqrtf(r));
            }
        }
    }
    return FUN_001b9530(arg0, arg1);
}
