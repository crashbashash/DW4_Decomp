/* 0x002af1a0 — FUN_002af1a0 (56 bytes). Converts a time record with FUN_002af110 at the fixed base rate 24000, then reports the caller's own rate through outRate. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
int FUN_002af110();

/* FUN_002af110(rate, record, out, outRate) scales the record's fields by rate into *out and stores rate into *outRate; this wrapper overwrites that rate. */
void FUN_002af1a0(int rate, void *record, int *out, int *outRate) {
    FUN_002af110(24000, record, out, outRate);
    *outRate = rate;
}
