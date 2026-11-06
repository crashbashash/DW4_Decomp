/* Fills out->data/size (+64/+68) from the frame's chunk, skipping a 4-byte header when there is
 * more than 4 bytes; cleared when FUN_00294d28 is not 1 or the decoder's current entry (+380) is
 * its own embedded one (+356). */
int FUN_00294d28(void);

struct Chunk00293bd8 {
    unsigned char *data; /* +0 */
    int size;            /* +4 */
};

struct Frame00293bd8 {
    char pad0[56];
    struct Chunk00293bd8 *chunk; /* +56 */
};

struct Out00293bd8 {
    char pad0[64];
    unsigned char *data; /* +64 */
    int size;            /* +68 */
};

struct Decoder00293bd8 {
    char pad0[356];
    char embedded[380 - 356]; /* +356 */
    void *current;            /* +380 */
};

void FUN_00293bd8(struct Decoder00293bd8 *decoder, struct Frame00293bd8 *frame, struct Out00293bd8 *out) {
    void *embedded = decoder->embedded;
    void *current = decoder->current;
    unsigned char *data = frame->chunk->data;
    int size = frame->chunk->size;

    if (FUN_00294d28() != 1 || current == embedded) {
        out->data = 0;
        out->size = 0;
        return;
    }
    if (data != 0 && size >= 5) {
        data += 4;
        size -= 4;
    }
    out->data = data;
    out->size = size;
}
