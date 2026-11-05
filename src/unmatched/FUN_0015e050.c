struct S_arg0 { char pad0[8]; int f8; char padC[12]; int f24; };
struct S_temp_v0_2 { char pad0[4]; int f4; };
int memset();
int FUN_00300e50();
int Memory_GetBufferSize();
int igObject_Destroy();
void *igObject_GetAllocator();

void FUN_0015e050(struct S_arg0 *arg0) {
    int temp_a0;
    int temp_s0;
    int temp_v0;
    struct S_temp_v0_2 *temp_a0_2;
    struct S_temp_v0_2 *temp_v0_2;

    temp_a0 = arg0->f8;
    if (temp_a0 != 0) {
        temp_v0 = Memory_GetBufferSize(temp_a0);
        temp_s0 = 0x50 - temp_v0;
        if (temp_s0 > 0) {
            arg0->f8 = FUN_00300e50(arg0, arg0->f8, 0x50);
            memset(arg0->f8 + temp_v0, 0, temp_s0);
        }
    }
    if (arg0->f24 == 0) {
        temp_v0_2 = (struct S_temp_v0_2 *)(igObject_GetAllocator(arg0));
        if (temp_v0_2 != 0) {
            temp_v0_2->f4 = (int)((int) (temp_v0_2->f4 + 1));
        }
        temp_a0_2 = (struct S_temp_v0_2 *)(arg0->f24);
        if (temp_a0_2 != 0) {
            temp_a0_2->f4 = temp_a0_2->f4 - 1;
            if ((temp_a0_2->f4 & 0x7FFFFF) == 0) {
                igObject_Destroy(temp_a0_2);
            }
        }
        arg0->f24 = (int)(temp_v0_2);
    }
}
