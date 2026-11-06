extern unsigned char DAT_00554e78[4];
void GpFlag_SetOnce_00458680(void) {
    if (DAT_00554e78[0] == 0) {
        DAT_00554e78[0] = 1;
    }
}
