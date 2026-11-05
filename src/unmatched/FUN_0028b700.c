/* 0x0028b700 — FUN_0028b700 (76 bytes). Stores a pair of words into +244 / +248 of a stream handle when it validates
   (FUN_0028da60). Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
struct Stream28b {
    int state;
    char pad4[240];
    int first;    /* +244 */
    int second;   /* +248 */
};

extern int FUN_0028da60(struct Stream28b *stream);

void FUN_0028b700(struct Stream28b *stream, int first, int second) {
    if (FUN_0028da60(stream) == 0) {
        stream->first = first;
        stream->second = second;
    }
}
