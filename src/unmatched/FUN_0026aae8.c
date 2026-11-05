/* 0x0026aae8 — FUN_0026aae8 (128 bytes). Attaches a stream interface at offset 4 and, between FUN_0025f2d0 and FUN_0025f2e8, stores the sum of its slot-9 values for 0 and 1 at offset 64, then copies that total to offsets 24 and 28. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
typedef struct Stream_26aae8 Stream_26aae8;
typedef struct StreamTable_26aae8 {
    void *slot[9];
    int (*slot9)(Stream_26aae8 *self, int which);   /* +0x24 */
} StreamTable_26aae8;
struct Stream_26aae8 {
    StreamTable_26aae8 *table;
};

typedef struct Object_26aae8 {
    int f0;
    Stream_26aae8 *stream;  /* 0x04 */
    char pad8[16];
    int f24;                /* 0x18 */
    int f28;                /* 0x1c */
    char pad32[32];
    int total;              /* 0x40 */
} Object_26aae8;

void FUN_0025f2d0(void);
void FUN_0025f2e8(void);

void FUN_0026aae8(Object_26aae8 *object, Stream_26aae8 *stream) {
    int first;

    object->stream = stream;
    FUN_0025f2d0();
    first = stream->table->slot9(stream, 0);
    object->total = first + stream->table->slot9(stream, 1);
    FUN_0025f2e8();
    object->f28 = object->f24 = object->total;
}
