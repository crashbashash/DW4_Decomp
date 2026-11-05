/* 0x00261720 — FUN_00261720 (88 bytes). Returns the first unused ADXF handle of the 16-entry table, or 0 (allocator used by adxf_CreateAdxFs, per the error string at DAT_004edb58; name is a hypothesis). Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
/* ADXF file handle, 68 bytes (16 of them at DAT_00499de8); field meanings beyond the ones set here are not yet known */
typedef struct AdxfHandle {
    signed char used;
    signed char f1;
    signed char f2;
    signed char f3;
    void *stream;
    int f8;
    char f12[12];
    int f24;
    int f28;
    int f32;
    char f36[8];
    int f44;
    char f48[20];
} AdxfHandle;

#define ADXF_HANDLE_COUNT 16

extern AdxfHandle DAT_00499de8[ADXF_HANDLE_COUNT];

AdxfHandle *FUN_00261720(void) {
    AdxfHandle *found = 0;
    int i;

    for (i = 0; i < ADXF_HANDLE_COUNT; i++) {
        if (DAT_00499de8[i].used == 0) {
            found = &DAT_00499de8[i];
            break;
        }
    }
    return found;
}
