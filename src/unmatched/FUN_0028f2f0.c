/* 0x0028f2f0 — FUN_0028f2f0 (108 bytes). Peeks at the next chunk of a stream object (vtable +24 to get it, +28 to put it back) and classifies its start code with FUN_0028dc78 when at least 4 bytes are available. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
int FUN_0028dc78(unsigned char *p);

struct Chunk0028f2f0 {
    unsigned char *data; /* +0 */
    int size;            /* +4 */
};

struct Stream0028f2f0;
struct StreamVtbl0028f2f0 {
    char pad0[24];
    void (*get)(struct Stream0028f2f0 *self, int a, int max, struct Chunk0028f2f0 *chunk); /* +24 */
    void (*unget)(struct Stream0028f2f0 *self, int a, struct Chunk0028f2f0 *chunk);        /* +28 */
};
struct Stream0028f2f0 {
    struct StreamVtbl0028f2f0 *vtbl;
};

int FUN_0028f2f0(struct Stream0028f2f0 *stream) {
    struct Chunk0028f2f0 chunk;

    stream->vtbl->get(stream, 1, 0x7FFFFFFF, &chunk);
    stream->vtbl->unget(stream, 1, &chunk);
    if (chunk.size < 4) {
        return 0;
    }
    return FUN_0028dc78(chunk.data);
}
