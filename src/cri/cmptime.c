/* Compares two times given as fractions num/den: 1 when num1/den1 is not before num0/den0, 0 when it is,
 * by cross-multiplying in 64 bits. */
int UTY_CmpTime(int num0, int den0, int num1, int den1)
{
    long long x = (long long)num0 * den1;
    long long y = (long long)num1 * den0;

    if (y < x) {
        return 0;
    }
    return 1;
}
