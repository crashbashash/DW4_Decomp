extern unsigned char DAT_00554bcc[4];
void GpFlag_SetOnce_00230f50(void) {
    if (DAT_00554bcc[0] == 0) {
        DAT_00554bcc[0] = 1;
    }
}
