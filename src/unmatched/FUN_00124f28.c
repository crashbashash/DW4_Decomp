/* Initialises one 88-byte stream: clears its buffer state, sets its flags and file number, makes
 * it its own cookie, installs the four I/O hooks (FUN_00129fa0 read, FUN_0012a008 write,
 * FUN_0012a088 seek, FUN_0012a0f0 close) and records the owning state block. */
typedef struct Stream124f28 {
    unsigned char *p;       /* +0: next byte in the buffer */
    int r;                  /* +4: bytes left to read */
    int w;                  /* +8: bytes left to write */
    short flags;            /* +12 */
    short file;             /* +14 */
    unsigned char *base;    /* +16: buffer */
    int size;               /* +20 */
    int lbfsize;            /* +24 */
    void *cookie;           /* +28: passed to the hooks */
    int (*read)();          /* +32 */
    int (*write)();         /* +36 */
    int (*seek)();          /* +40 */
    int (*close)();         /* +44 */
    char pad48[36];
    void *state;            /* +84: owning state block */
} Stream124f28;

int FUN_00129fa0();
int FUN_0012a008();
int FUN_0012a088();
int FUN_0012a0f0();

void FUN_00124f28(Stream124f28 *stream, int flags, int file, void *state) {
    stream->p = 0;
    stream->r = 0;
    stream->w = 0;
    stream->flags = flags;
    stream->file = file;
    stream->base = 0;
    stream->size = 0;
    stream->lbfsize = 0;
    stream->cookie = stream;
    stream->read = FUN_00129fa0;
    stream->write = FUN_0012a008;
    stream->seek = FUN_0012a088;
    stream->close = FUN_0012a0f0;
    stream->state = state;
}
