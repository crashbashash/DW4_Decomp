/* Stream write hook: for an append-mode stream (flag 0x100) first seeks to the end through
 * FUN_00125fc8, clears the offset-valid flag 0x1000 and writes through FUN_0012fe90. The shape of
 * newlib's __swrite (hypothesis; installed by FUN_00124f28). */
typedef struct Stream12a008 {
    char pad0[12];
    unsigned short flags;   /* +12: 0x100 append, 0x1000 offset valid */
    short file;             /* +14 */
    char pad16[68];
    void *state;            /* +84 */
} Stream12a008;

long FUN_00125fc8(void *state, int file, long offset, int whence);
long FUN_0012fe90(void *state, int file, const void *buf, int count);

int FUN_0012a008(void *cookie, const char *buf, int count) {
    Stream12a008 *stream = cookie;

    if (stream->flags & 0x100) {
        FUN_00125fc8(stream->state, stream->file, 0, 2);
    }
    stream->flags &= ~0x1000;
    return FUN_0012fe90(stream->state, stream->file, buf, count);
}
