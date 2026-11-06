/* True when every one of the eight handle slots (DAT_004beadc) is empty or passes FUN_002aa728. */
typedef struct SfdHandle SfdHandle;

extern SfdHandle *DAT_004beadc[8];
extern int FUN_002aa728(SfdHandle *handle);

int FUN_002aa750(void) {
    SfdHandle **slot = DAT_004beadc;
    int i;

    for (i = 0; i < 8; i++) {
        SfdHandle *handle = *slot++;
        if (handle != 0 && FUN_002aa728(handle) == 0) {
            return 0;
        }
    }
    return 1;
}
