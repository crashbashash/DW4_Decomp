/* Copies the five 64-bit words at +168..+200 of a stream handle to out[0..4] after validating it
 * (mps_CheckHn); an invalid handle is reported as error 0xFF020203 through mps_ReportError. */
struct Stream28d {
    int state;
    char pad4[164];
    long long info[5];   /* +168 */
};

extern int mps_CheckHn(struct Stream28d *stream);
extern void mps_ReportError(int a0, int code);

/* matching construct: hand search — returns the validation result on the success path (keeps it live in v0,
   so the copy uses v1/a0); the error path returns no value, as in the implicit-int original */
int FUN_0028d658(struct Stream28d *stream, long long *out) {
    int result;

    result = mps_CheckHn(stream);
    if (result != 0) {
        mps_ReportError(0, 0xFF020203);
        return;
    }
    out[0] = stream->info[0];
    out[1] = stream->info[1];
    out[2] = stream->info[2];
    out[3] = stream->info[3];
    out[4] = stream->info[4];
    return result;
}
