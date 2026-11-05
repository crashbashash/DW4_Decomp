/* 0x0015e130 — 40 bytes. Population count.
 *   retail: 10000005 b    0x15e148      ; enter at the loop test
 *           0000102d move v0,zero
 *           10600002 beqz v1,0x15e144
 *           00000000 nop
 *           24420001 addiu v0,v0,1
 *           00042042 srl  a0,a0,0x1
 *           1480fffb bnez a0,0x15e138
 *           30830001 andi v1,a0,0x1     ; delay slot: bit for the next pass
 *           03e00008 jr   ra
 *           00000000 nop
 *
 * First non-trivial match, and the function that pinned the optimisation flags:
 * it matches at -O3 (and -O4,s) but NOT at -O4,p, -O2 or -O1 — the three 8-byte
 * leaves earlier matched -O4,p by coincidence because they cannot discriminate. */
int FUN_0015e130(unsigned int v)
{
    int n = 0;
    while (v) {
        if (v & 1)
            n++;
        v >>= 1;
    }
    return n;
}
