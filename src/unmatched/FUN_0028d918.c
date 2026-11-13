/* Applies FUN_0028d9b0(target, a, b) to a stream handle's +4 block after validating it
 * (mps_CheckHn), or to the global work area 0x004bcc68 when the handle is null; an invalid handle
 * is reported as error 0xFF020101 through mps_ReportError and its result returned. Returns 0
 * otherwise. */
struct Stream28d {
    int state;
    char block[4];   /* +4 */
};

extern void FUN_0028d9b0(void *target, int a, int b);
extern int mps_CheckHn(struct Stream28d *stream);
extern int mps_ReportError(int a0, int code);
extern void *DAT_004bcc68;

int FUN_0028d918(struct Stream28d *stream, int a, int b) {
    if (stream == 0) {
        FUN_0028d9b0(DAT_004bcc68, a, b);
    } else {
        if (mps_CheckHn(stream) != 0) {
            return mps_ReportError(0, 0xFF020101);
        }
        FUN_0028d9b0(stream->block, a, b);
    }
    return 0;
}
