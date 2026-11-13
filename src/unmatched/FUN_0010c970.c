extern int (*DAT_00481e64)(int c);
unsigned long __fixunsdfdi(double value);
int FUN_0010c8d8(unsigned long bits);
int kprintf(const char *format, ...);
void FUN_0010c970(double value) {
    double zero = 0.0;
    int exponent = 0;
    int digits;
    if (value < zero) {
        value = zero - value;
        DAT_00481e64('-');
    }
    if (value < 0.1) {
        while (value < 0.1) {
            value *= 10.0;
            exponent--;
        }
    } else if (value >= 1.0) {
        while (value >= 1.0) {
            value /= 10.0;
            exponent++;
        }
    }
    digits = FUN_0010c8d8(__fixunsdfdi(value * 1000000.0));
    kprintf("0.%d", digits);
    if (exponent >= 0) {
        kprintf("e+%d", exponent);
    } else {
        kprintf("e%d", exponent);
    }
}
