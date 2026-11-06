/* arg1 is overwritten with the scaled index and then with the sum, so the index parameter stays
 * one web instead of using temporaries. */
int FUN_002adc40(int arg0, int arg1) {
    arg1 *= 4;
    arg1 += arg0;
    return *(int *)((char *)arg1 + 2564);
}
