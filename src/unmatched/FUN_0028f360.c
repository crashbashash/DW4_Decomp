/* 0x0028f360 — FUN_0028f360 (160 bytes). Wraps a memory buffer in a temporary stream object (FUN_0027b408), runs FUN_0028f100 on it, reports how many bytes it consumed (size - remaining from vtable +36) and destroys the stream (vtable +12). Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
struct Stream0028f360;
struct StreamVtbl0028f360 {
    char pad0[12];
    void (*destroy)(struct Stream0028f360 *self);           /* +12 */
    char pad16[36 - 16];
    int (*remaining)(struct Stream0028f360 *self, int a);   /* +36 */
};
struct Stream0028f360 {
    struct StreamVtbl0028f360 *vtbl;
};

struct Buffer0028f360 {
    void *data; /* +0 */
    int size;   /* +4 */
};

struct Stream0028f360 *FUN_0027b408(void *data, int size);
int FUN_0028f100(void *decoder, struct Stream0028f360 *stream);

int FUN_0028f360(void *decoder, struct Buffer0028f360 *buffer, int *consumed) {
    struct Stream0028f360 *stream;
    int result;

    stream = FUN_0027b408(buffer->data, buffer->size);
    if (stream == 0) {
        return -1;
    }
    result = FUN_0028f100(decoder, stream);
    *consumed = buffer->size - stream->vtbl->remaining(stream, 1);
    stream->vtbl->destroy(stream);
    return result;
}
