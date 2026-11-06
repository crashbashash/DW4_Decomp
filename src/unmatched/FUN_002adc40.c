/* Matched with tools/dispatcher/regalloc.py: retail overwrites the scaled index with the sum (`sll
 * a1,a1,2; addu a1,a1,a0`), i.e. the index parameter is one web, so the C reassigns arg1 instead
 * of using expression temporaries. */
int FUN_002adc40(int arg0, int arg1) {
    arg1 *= 4;
    arg1 += arg0;
    return *(int *)((char *)arg1 + 2564);
}
