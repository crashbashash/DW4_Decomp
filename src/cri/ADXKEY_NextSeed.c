/* One step of the ADX key generator: seed = seed * mul + add, 16 bits. */
int ADXKEY_NextSeed(unsigned short *seed, unsigned short *mul, unsigned short *add)
{
    *seed = *add + (*seed * *mul);
    return 0;
}
