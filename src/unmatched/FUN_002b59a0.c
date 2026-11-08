extern volatile int D_004bf290;
extern int D_004bf294;
extern int D_004bf298;
extern int *D_004f5a70[];
void FUN_002b59a0(void) {
    D_004bf290--;
    if (D_004bf290 == 0 && D_004bf294 != -1 && (D_004bf298 & 0xC7) != 0x82) {
        *D_004f5a70[D_004bf294] = D_004bf298 ^ 0xC00;
    }
    if (D_004bf290 < 0) {
        D_004bf290 = 0;
    }
}
