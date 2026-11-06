extern unsigned char DAT_00554b10[4];
void GpFlag_SetOnce_00142f10(void) {
    if (DAT_00554b10[0] == 0) {
        DAT_00554b10[0] = 1;
    }
}
