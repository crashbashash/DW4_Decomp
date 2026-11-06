extern unsigned char DAT_00554bb4[4];
void GpFlag_SetOnce_001e3ff0(void) {
    if (DAT_00554bb4[0] == 0) {
        DAT_00554bb4[0] = 1;
    }
}
