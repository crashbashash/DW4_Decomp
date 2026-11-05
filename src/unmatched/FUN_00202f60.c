/* 0x00202f60 — walks the linked list from arg0 and returns the first node whose 64-bit key (table row (node->+16) * 64) equals
 * arg1, or null. Combat compiler at plain -O3; the key and parameter are 64-bit (ld / beq on full registers). */
extern int DAT_00562da0[4];
int *FUN_00202f60(int *arg0, long long arg1) {
    for (; arg0 != 0; arg0 = (int *)arg0[5]) {
        if (arg1 == *(long long *)((char *)DAT_00562da0 + (arg0[4] << 6))) break;
    }
    return arg0;
}
