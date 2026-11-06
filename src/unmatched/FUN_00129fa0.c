/* Stream read hook: reads through FUN_00129008 on the stream's file and, on success, advances the
 * stream's offset (+80); on failure clears the offset-valid flag 0x1000. The shape of newlib's
 * __sread (hypothesis; installed by FUN_00124f28). */
typedef struct Stream129fa0 {
    char pad0[12];
    unsigned short flags;   /* +12: 0x1000 = offset (+80) is valid */
    short file;             /* +14 */
    char pad16[64];
    int offset;             /* +80 */
    void *state;            /* +84 */
} Stream129fa0;

long FUN_00129008(void *state, int file, void *buf, int count);

int FUN_00129fa0(void *cookie, char *buf, int count) {
    Stream129fa0 *stream = cookie;
    int ret;

    ret = FUN_00129008(stream->state, stream->file, buf, count);
    if (ret >= 0) {
        stream->offset += ret;
    } else {
        stream->flags &= ~0x1000;
    }
    return ret;
}
