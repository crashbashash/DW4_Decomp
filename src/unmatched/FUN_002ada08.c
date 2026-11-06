/* Calls FUN_002ada78(entry, a, b) for every non-null entry of the eight-slot table DAT_004beadc. */
extern int DAT_004beadc[8];
int FUN_002ada78();

void FUN_002ada08(int a, int b) {
    int i;

    for (i = 0; i < 8; i++) {
        if (DAT_004beadc[i] != 0) {
            FUN_002ada78(DAT_004beadc[i], a, b);
        }
    }
}
