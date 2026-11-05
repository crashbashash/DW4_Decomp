extern "C" {
void *FUN_00100cf0(void *, int *);

void FUN_001025d0(char *arg0) {
    int sp2C;
    int temp_s0;
    void *temp_a0;

    temp_s0 = *arg0 & 0x40;
    temp_a0 = (void *)(FUN_00100cf0(FUN_00100cf0(arg0 + 1, &sp2C), &sp2C));
    if (temp_s0 != 0) {
        FUN_00100cf0(temp_a0, &sp2C);
    }
}
}
