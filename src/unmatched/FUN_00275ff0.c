/* Returns the high word of the readable byte count of a handle: the 64-bit position (+8) clamped
 * to the file size (+40 sectors of 2048 bytes). */
struct File276 {
    int f0;
    int f4;
    unsigned long long position;   /* +8 */
    char pad16[24];
    int sectors;                   /* +40 */
};

long long FUN_00275ff0(struct File276 *file) {
    unsigned long long size = (long long)file->sectors << 11;

    return (long long)(file->position < size ? file->position : size) >> 32;
}
