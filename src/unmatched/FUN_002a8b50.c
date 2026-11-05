/* 0x002a8b50 — FUN_002a8b50 (76 bytes). Returns the 2048-byte sector index of position from the area base, or 0 at the area's end ((f8 * 16 + f4 + 16) masked to 28 bits). Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
struct Area2a8b50 {
    int base;
    int f4;
    int f8;
};

/* Sector index (2048-byte units) of position from the area base, or 0 at the area's end address. */
int FUN_002a8b50(struct Area2a8b50 *area, int position) {
    if (position == ((area->f8 * 16 + area->f4 + 16) & 0x0FFFFFFF)) {
        return 0;
    }
    return (position - area->base) / 2048;
}
