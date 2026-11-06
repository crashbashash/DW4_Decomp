/* Stores a pair of words into +236 / +240 of a stream handle when it validates (FUN_0028da60). */
struct Stream28b {
    int state;
    char pad4[232];
    int first;    /* +236 */
    int second;   /* +240 */
};

extern int FUN_0028da60(struct Stream28b *stream);

void FUN_0028b6b0(struct Stream28b *stream, int first, int second) {
    if (FUN_0028da60(stream) == 0) {
        stream->first = first;
        stream->second = second;
    }
}
