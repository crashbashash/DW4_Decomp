/* Fills a 32-byte block with 0xFF bytes through FUN_0028b530. */
extern void FUN_0028b530(void *dst, int value, int size);

void FUN_002a7ad0(void *block) {
    FUN_0028b530(block, -1, 32);
}
