/* 0x002af210 — FUN_002af210 (56 bytes). Converts a time record with FUN_002af110 at the fixed base rate 60000, then reports the caller's own rate through outRate. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
int FUN_002af110();

/* FUN_002af110(rate, record, out, outRate) scales the record's fields by rate into *out and stores rate into *outRate; this wrapper overwrites that rate. */
void FUN_002af210(int rate, void *record, int *out, int *outRate) {
    FUN_002af110(60000, record, out, outRate);
    *outRate = rate;
}
