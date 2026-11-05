/* 0x002aa810 — FUN_002aa810 (84 bytes). Runs FUN_002aa868 on every occupied handle slot (DAT_004beadc), then FUN_002ab6b8. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
typedef struct SfdHandle SfdHandle;

extern SfdHandle *DAT_004beadc[8];
extern void FUN_002aa868(SfdHandle *handle);
extern void FUN_002ab6b8(void);

void FUN_002aa810(void) {
    SfdHandle **slot = DAT_004beadc;
    int i;

    for (i = 0; i < 8; i++) {
        SfdHandle *handle = *slot++;
        if (handle != 0) {
            FUN_002aa868(handle);
        }
    }
    FUN_002ab6b8();
}
