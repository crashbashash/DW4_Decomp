/* Seeks the handle at arg0 by whence 0/1/2 (absolute, relative to FUN_0026a160, relative to the
 * FUN_0026aa00 size rounded up to 2048-byte sectors); returns 0. */
int FUN_0026a140();
int FUN_0026a160();
int FUN_0026aa00();

int FUN_0029b0b8(int handle, int offset, int whence) {
    if (whence == 0) {
        FUN_0026a140(handle, offset);
    } else if (whence == 1) {
        FUN_0026a140(handle, FUN_0026a160(handle) + offset);
    } else if (whence == 2) {
        FUN_0026a140(handle, (FUN_0026aa00(handle) + 2047) / 2048 + offset);
    }
    return 0;
}
