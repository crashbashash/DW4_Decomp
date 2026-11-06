extern unsigned char DAT_00554e68[4];
void GpFlag_SetOnce_003b0a10(void) {
    if (DAT_00554e68[0] == 0) {
        DAT_00554e68[0] = 1;
    }
}
