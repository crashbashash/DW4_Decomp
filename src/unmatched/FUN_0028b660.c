/* Stores a pair of words into +228 / +232 of a stream handle when it validates (mps_CheckHn). */
struct Stream28b {
    int state;
    char pad4[224];
    int first;    /* +228 */
    int second;   /* +232 */
};

extern int mps_CheckHn(struct Stream28b *stream);

void FUN_0028b660(struct Stream28b *stream, int first, int second) {
    if (mps_CheckHn(stream) == 0) {
        stream->first = first;
        stream->second = second;
    }
}
