extern unsigned int sifSregs[32];

unsigned int sceSifSetSreg(int reg, unsigned int value) {
    sifSregs[reg] = value;
    return value;
}
