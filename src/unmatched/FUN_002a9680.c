/* 0x002a9680 — FUN_002a9680 (76 bytes). Rounds the stream's buffered byte count (+20) up to a 2048-byte multiple (after adding 3) under the stream semaphore. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
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

/* Rounds the buffered byte count up (by 2051, to a 2048 multiple) under the stream semaphore. */
void FUN_002a9680(struct Stream *stream) {
    WaitSema(stream->sema);
    stream->f20 = (stream->f20 + 2051) / 2048 * 2048;
    SignalSema(stream->sema);
}
