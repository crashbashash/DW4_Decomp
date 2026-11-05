/* 0x002ab878 — FUN_002ab878 (64 bytes). Returns the index of the first free handle slot (DAT_004beadc), or -1. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
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
