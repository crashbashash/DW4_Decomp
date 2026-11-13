/* Attaches a stream interface at offset 4 and, between ADXCRS_Lock and ADXCRS_Unlock, stores the
 * sum of its slot-9 values for 0 and 1 at offset 64, then copies that total to offsets 24 and 28. */
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

void ADXCRS_Lock(void);
void ADXCRS_Unlock(void);

void FUN_0026aae8(Object_26aae8 *object, Stream_26aae8 *stream) {
    int first;

    object->stream = stream;
    ADXCRS_Lock();
    first = stream->table->slot9(stream, 0);
    object->total = first + stream->table->slot9(stream, 1);
    ADXCRS_Unlock();
    object->f28 = object->f24 = object->total;
}
