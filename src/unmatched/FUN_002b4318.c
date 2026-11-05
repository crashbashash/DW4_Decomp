/* 0x002b4318 — FUN_002b4318. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
/* matching construct: variant search — statement order; the unit compiler (Sony EE GCC 2.96 -O2 -G0) schedules the last independent store of the body into the return delay slot and keeps the rest in source order, so the stores are written in retail's emitted order */
void FUN_002b4318(void *arg0) {
    *(int *)((char *)arg0 + 60) = 0;
    *(int *)((char *)arg0 + 64) = 0;
    *(int *)((char *)arg0 + 68) = 0;
    *(int *)((char *)arg0 + 72) = 0;
    *(int *)((char *)arg0 + 4) = 0;
}
