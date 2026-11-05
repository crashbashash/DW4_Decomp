void FUN_0016a300(int *a, unsigned int x) {
    a[224] = (x & 0xffffff) | (((x >> 1) & 0x7f000000) + (x & 0x01000000));
}
