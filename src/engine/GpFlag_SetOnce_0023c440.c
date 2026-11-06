extern unsigned char DAT_00554bdc[4];
void GpFlag_SetOnce_0023c440(void) {
    if (DAT_00554bdc[0] == 0) {
        DAT_00554bdc[0] = 1;
    }
}
