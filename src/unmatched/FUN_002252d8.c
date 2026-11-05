/* 0x002252d8 - 40 bytes. Empty varargs function: spills a1..t3 and returns. The local array is
 * kept because __builtin_next_arg takes its address; its size (33..48 bytes) sets the 128-byte frame. */
void FUN_002252d8(int a0, ...) {
    char d[48];
    __builtin_next_arg(d);
}
