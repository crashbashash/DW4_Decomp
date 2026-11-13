extern "C" {
void *__DecodeUnsignedNumber(void *, int *);

void FUN_001025d0(char *arg0) {
    int sp2C;
    int temp_s0;
    void *temp_a0;

    temp_s0 = *arg0 & 0x40;
    temp_a0 = (void *)(__DecodeUnsignedNumber(__DecodeUnsignedNumber(arg0 + 1, &sp2C), &sp2C));
    if (temp_s0 != 0) {
        __DecodeUnsignedNumber(temp_a0, &sp2C);
    }
}
}
