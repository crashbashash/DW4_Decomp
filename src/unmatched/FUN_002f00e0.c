/* 0x002f00e0 — FUN_002f00e0. m2c draft, hand-fixed; verified byte-identical by
 * tools/verify.py (loop: tools/m2c_loop.py). */
int Memory_GetAllocatorBySelector();

void FUN_002f00e0(void) {
    Memory_GetAllocatorBySelector(3);
}
