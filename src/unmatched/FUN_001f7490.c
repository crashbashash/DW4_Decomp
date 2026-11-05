int printf();
long long p2readGSPrivRegister();
extern int DAT_004e5110[4];
void FUN_001f7490(void) {
    long long temp_v0;
    int a, b;
    temp_v0 = p2readGSPrivRegister(0x40);
    a = (temp_v0 >> 0x18) & 0xFF;
    b = (temp_v0 >> 0x10) & 0xFF;
    printf(&DAT_004e5110[0], a, b);
}
