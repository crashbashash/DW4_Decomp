int igObject_Destroy();
extern void * DAT_00586df8[4];
extern char GPR_00554bfc;

void FUN_002dc9c0(void) {
    if (DAT_00586df8[0] != 0) {
        {
            void *held = (void *)DAT_00586df8[0];
            *(int *)((char *)(held) + 4) = *(int *)((char *)(held) + 4) - 1;
            if (((unsigned long long) ((long long) *(int *)((char *)(held) + 4) << 0x29) >> 0x29) == 0) {
                igObject_Destroy(held);
            }
        }
    }
    DAT_00586df8[0] = (void *)(0);
    GPR_00554bfc = 1;
}
