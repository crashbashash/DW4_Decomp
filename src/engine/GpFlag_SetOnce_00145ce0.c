extern unsigned char DAT_00554b14[4];
void GpFlag_SetOnce_00145ce0(void) {
    if (DAT_00554b14[0] == 0) {
        DAT_00554b14[0] = 1;
    }
}
