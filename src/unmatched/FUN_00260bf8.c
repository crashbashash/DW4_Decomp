/* Returns the number of 2048-byte sectors needed to hold a byte count (division rounded up). */
int FUN_00260bf8(int bytes) {
    return bytes / 2048 + (bytes % 2048 > 0);
}
