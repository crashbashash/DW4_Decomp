/* 0x00265af0 — FUN_00265af0 (52 bytes). Returns half of FUN_0027da60(handle, 0) for track index's handle. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
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
unsigned int FUN_0027da60(void *handle, int mode);

unsigned int FUN_00265af0(Object_265a78 *object, int index) {
    return FUN_0027da60(object->tracks->tracks[index]->handle, 0) >> 1;
}
