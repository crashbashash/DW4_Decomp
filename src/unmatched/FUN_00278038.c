/* 0x00278038 — FUN_00278038 (108 bytes). Initialises a buffer descriptor: 2048-byte units, total size from
   FUN_00277fa0 on the area at +28, unit count rounded up, counters cleared and the in-use byte set.
   Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
struct Buffer278 {
    signed char used;     /* +0 */
    signed char busy;     /* +1 */
    char pad2[2];
    int unit_size;        /* +4 */
    int size;             /* +8 */
    int unit_count;       /* +12 */
    int f16;              /* +16 */
    int f20;              /* +20 */
    int f24;              /* +24 */
    char area[4];         /* +28 */
};

extern int FUN_00277fa0(char *area);

void FUN_00278038(struct Buffer278 *buffer) {
    int size;

    buffer->unit_size = 0x800;
    size = FUN_00277fa0(buffer->area);
    buffer->size = size;
    buffer->unit_count = (size + buffer->unit_size - 1) / buffer->unit_size;
    buffer->used = 1;
    buffer->f24 = 0;
    buffer->f20 = 0;
    buffer->busy = 0;
    buffer->f16 = 0;
}
