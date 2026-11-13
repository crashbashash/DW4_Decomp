/* Stores a pair of words into +236 / +240 of a stream handle when it validates (mps_CheckHn). */
struct Stream28b {
    int state;
    char pad4[232];
    int first;    /* +236 */
    int second;   /* +240 */
};

extern int mps_CheckHn(struct Stream28b *stream);

void FUN_0028b6b0(struct Stream28b *stream, int first, int second) {
    if (mps_CheckHn(stream) == 0) {
        stream->first = first;
        stream->second = second;
    }
}
