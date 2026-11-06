extern unsigned char DAT_00554dfc[4];
void GpFlag_SetOnce_00334440(void) {
    if (DAT_00554dfc[0] == 0) {
        DAT_00554dfc[0] = 1;
    }
}
