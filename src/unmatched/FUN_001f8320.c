int p2readGSPrivRegister(int);

void FUN_001f8320(void) {
    if (*(int *)0x490B60 != 0) {
        p2readGSPrivRegister(0x48);
    }
}
