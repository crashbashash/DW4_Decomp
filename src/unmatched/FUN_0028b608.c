/* Stores a word into +16 of a stream handle after validating it (mps_CheckHn); an invalid handle
 * is reported as error 0xFF020302 through mps_ReportError. */
struct Stream28b {
    int state;
    char pad4[12];
    int value16;   /* +16 */
};

extern int mps_CheckHn(struct Stream28b *stream);
extern void mps_ReportError(int a0, int code);

/* matching construct: hand search — int return type with no return value (implicit-int style); with void
   the epilogue restores are scheduled differently */
int FUN_0028b608(struct Stream28b *stream, int value) {
    if (mps_CheckHn(stream) != 0) {
        mps_ReportError(0, 0xFF020302);
        return;
    }
    stream->value16 = value;
}
