/* Forwards to FUN_002b0338(handle, 0, 10, a, b), reporting error 0xFF000135 instead when
 * FUN_002a0dd8 refuses. */
int FUN_002a0dd8(int handle);
void FUN_002a0bb8(int obj, int code);
void FUN_002b0338(int handle, int a, int b, int c, int d);

void FUN_002ac418(int handle, int c, int d) {
    if (FUN_002a0dd8(handle) != 0) {
        FUN_002a0bb8(0, 0xFF000135);
        return;
    }
    FUN_002b0338(handle, 0, 10, c, d);
}
