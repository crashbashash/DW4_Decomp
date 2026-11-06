/* Clears the reader cursor at +24 when it lies outside both chunks FUN_0029e068 maps from the
 * ring. */
int FUN_0029e068();

struct Chunk {
    char *data;
    int size;
};
struct Cursor {
    char *pos;
    int f4;
};
struct Reader29dfd8 {
    int f0;
    void *ring;                           /* +4 */
    char pad8[24 - 8];
    struct Cursor cursor;                 /* +24 */
};

/* Drops the cursor when it no longer points into either mapped chunk of the ring. */
void FUN_0029dfd8(struct Reader29dfd8 *reader) {
    struct Cursor *cursor = &reader->cursor;
    struct Chunk first;
    struct Chunk second;
    char *pos;

    FUN_0029e068(reader->ring, 1, &first, &second);
    pos = cursor->pos;
    if (pos < first.data || pos >= first.data + first.size) {
        if (pos < second.data || pos >= second.data + second.size) {
            cursor->pos = 0;
            cursor->f4 = 0;
        }
    }
}
