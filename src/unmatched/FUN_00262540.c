/* Stores in field 12 of an object, and returns, the number of 2048-byte sectors (rounded up) for
 * the byte count FUN_00262580 returns. */
int FUN_00262580(void *object);

int FUN_00262540(int *object) {
    return object[3] = (FUN_00262580(object) + 2047) / 2048;
}
