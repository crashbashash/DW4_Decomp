extern unsigned char DAT_00554bd4[4];
void GpFlag_SetOnce_00238d50(void) {
    if (DAT_00554bd4[0] == 0) {
        DAT_00554bd4[0] = 1;
    }
}
