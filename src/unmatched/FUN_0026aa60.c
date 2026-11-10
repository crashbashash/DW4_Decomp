/* Stores the byte size cvFsGetFileSize reports for the handle as a count of 2048-byte sectors,
 * rounded up, and returns 1. */
int cvFsGetFileSize(int handle);

int FUN_0026aa60(int handle, int *sectors) {
    int bytes = cvFsGetFileSize(handle);
    int count = bytes / 2048;

    *sectors = count;
    if (bytes - count * 2048 > 0) {
        *sectors = count + 1;
    }
    return 1;
}
