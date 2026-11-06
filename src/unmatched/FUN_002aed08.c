/* Stores a value at +3392 of the handle's object, or reports error 0xFF000124 when FUN_002a0dd8
 * rejects the handle. */
int FUN_002a0bb8();
int FUN_002a0dd8();

struct Obj0D40 {
    char pad[3392];
    int f3392;
};

/* FUN_002a0dd8(handle) records the handle in a global and returns -1 when it is null or its word at +72 is clear (asm/FUN_002a0dd8.s). */
int FUN_002aed08(struct Obj0D40 *handle, int value) {
    if (FUN_002a0dd8(handle) != 0) {
        return FUN_002a0bb8(0, 0xFF000124);
    }
    handle->f3392 = value;
    return 0;
}
