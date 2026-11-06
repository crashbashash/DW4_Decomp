/* Returns half of what slot 9 of track index's stream interface reports for argument 0. */
typedef struct Stream_265a78 Stream_265a78;
typedef struct StreamTable_265a78 {
    void *slot[9];
    unsigned int (*slot9)(Stream_265a78 *self, int value);   /* +0x24 */
} StreamTable_265a78;
struct Stream_265a78 {
    StreamTable_265a78 *table;
};

typedef struct Track_265a78 {
    int f0;
    void *handle;           /* 0x04 */
    Stream_265a78 *stream;  /* 0x08 */
} Track_265a78;

typedef struct TrackList_265a78 {
    int f0;
    int f4;
    Track_265a78 *tracks[1];  /* 0x08: indexed by track number */
} TrackList_265a78;

typedef struct Object_265a78 {
    int f0;
    int f4;
    int f8;
    TrackList_265a78 *tracks;  /* 0x0c */
} Object_265a78;

unsigned int FUN_00265a78(Object_265a78 *object, int index) {
    Stream_265a78 *stream = object->tracks->tracks[index]->stream;

    return stream->table->slot9(stream, 0) >> 1;
}
