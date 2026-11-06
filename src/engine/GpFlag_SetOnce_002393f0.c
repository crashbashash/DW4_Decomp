extern unsigned char DAT_00554bd8[4];
void GpFlag_SetOnce_002393f0(void) {
    if (DAT_00554bd8[0] == 0) {
        DAT_00554bd8[0] = 1;
    }
}
