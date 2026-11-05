/* 0x002a8f90 — FUN_002a8f90 (128 bytes). Consumes count bytes from the stream (+20 and the 64-bit +72) under its semaphore; hangs if the buffer count goes negative. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
int SignalSema();
int WaitSema();

/* IPU stream buffer descriptor guarded by a semaphore at +64. */
struct Stream {
    int f0;
    char *uncached;                       /* +4: buffer address in the uncached segment */
    int sectors;                          /* +8 */
    int pad12;
    int pad16;
    int f20;                              /* +20: bytes buffered */
    int bytes;                            /* +24: sectors * 2048 */
    char pad28[64 - 28];
    int sema;                             /* +64 */
    int pad68;
    long f72;                             /* +72 */
    int f80;
    int f84;
};

/* Consumes count bytes from the stream under its semaphore; hangs if more were consumed than buffered. */
int FUN_002a8f90(struct Stream *stream, int count) {
    WaitSema(stream->sema);
    stream->f20 -= count;
    stream->f72 -= count;
    if (stream->f20 < 0) {
        for (;;) {
        }
    }
    SignalSema(stream->sema);
    return count;
}
