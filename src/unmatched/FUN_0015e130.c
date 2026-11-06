/* Population count. */
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
