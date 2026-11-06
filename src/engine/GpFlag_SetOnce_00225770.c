extern unsigned char DAT_00554bc8[4];
void GpFlag_SetOnce_00225770(void) {
    if (DAT_00554bc8[0] == 0) {
        DAT_00554bc8[0] = 1;
    }
}
