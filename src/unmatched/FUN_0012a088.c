/* 0x0012a088 — FUN_0012a088 (100 bytes). Stream seek hook: seeks the stream's file through FUN_00125fc8 and records the new offset, or clears the offset-valid flag on failure (newlib __sseek shape; name is a hypothesis). Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
typedef struct Stream {
    unsigned char *position;
    int readSpace;
    int writeSpace;
    unsigned short flags;
    short file;
    char f16[64];
    int offset;
    void *data;
} Stream;

#define STREAM_OFFSET_VALID 0x1000 /* __SOFF */

long FUN_00125fc8(void *reent, int file, long offset, int whence);

long FUN_0012a088(void *cookie, long offset, int whence) {
    Stream *stream = (Stream *)cookie;
    long result;

    result = FUN_00125fc8(stream->data, stream->file, offset, whence);
    if (result == -1) {
        stream->flags &= ~STREAM_OFFSET_VALID;
    } else {
        stream->flags |= STREAM_OFFSET_VALID;
        stream->offset = result;
    }
    return result;
}
