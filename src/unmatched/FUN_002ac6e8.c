/* Hands `size` bytes at `data` to FUN_002ac770 on the block at +0x13B4, ignoring empty input and
 * reporting error 0xFF000165 when FUN_002a0dd8 refuses. */
int FUN_002a0dd8(int handle);
int FUN_002a0bb8(int obj, int code);
void FUN_002ac770(int block, int data, int size);

int FUN_002ac6e8(int handle, int data, int size) {
    if (data == 0 || size <= 0) {
        return 0;
    }
    if (FUN_002a0dd8(handle) != 0) {
        return FUN_002a0bb8(0, 0xFF000165);
    }
    FUN_002ac770(handle + 0x13B4, data, size);
    return 0;
}
