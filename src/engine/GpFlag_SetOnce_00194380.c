extern unsigned char DAT_00554b80[4];
void GpFlag_SetOnce_00194380(void) {
    if (DAT_00554b80[0] == 0) {
        DAT_00554b80[0] = 1;
    }
}
