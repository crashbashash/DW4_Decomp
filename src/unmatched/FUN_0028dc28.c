/* Runs mps_CheckHn on the object; on failure reports error 0xFF020103 through mps_ReportError,
 * otherwise sets its first word to 1. */
extern int mps_CheckHn(int *obj);
extern int mps_ReportError(int zero, int code);

int FUN_0028dc28(int *obj) {
    if (mps_CheckHn(obj) != 0) {
        return mps_ReportError(0, 0xFF020103);
    }
    *obj = 1;
    return 0;
}
