/* Smart-pointer assignment guarded by an allocator check; reference count masked to 23 bits. */
typedef struct S1 { char pad4[4]; int f4; } S1;
typedef struct S0 { char pad148[148]; S1 *f94; } S0;
int igObject_Destroy();
S0 *igObject_GetAllocator();

void FUN_003247b0(S0 *arg0, S1 *arg1) {
    S1 *temp_a0;
    if ((arg1 == 0) || (igObject_GetAllocator(arg1) != arg0)) {
        if (arg1 != 0) {
            arg1->f4 = (int)((int) (arg1->f4 + 1));
        }
        temp_a0 = arg0->f94;
        if (temp_a0 != 0) {
            temp_a0->f4 = (int)((int) (temp_a0->f4 - 1));
            if (((unsigned long long) ((long long) temp_a0->f4 << 0x29) >> 0x29) == 0) {
                igObject_Destroy(temp_a0);
            }
        }
        arg0->f94 = arg1;
    }
}
