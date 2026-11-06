/* Returns the index of the first free handle slot (DAT_004beadc), or -1. */
typedef struct SfdHandle SfdHandle;

extern SfdHandle *DAT_004beadc[8];

int FUN_002ab878(void) {
    SfdHandle **slot = DAT_004beadc;
    int i;

    for (i = 0; i < 8; i++) {
        if (*slot++ == 0) {
            return i;
        }
    }
    return -1;
}
