/* Decodes a 16-bit sign-magnitude sample (bit 15 = sign, 15-bit magnitude) into a 64-bit fixed-
 * point value (magnitude << 23). One 64-bit variable is widened, masked, shifted and negated in
 * place. */
long long Gap__Sg__igCompressedAnimationSequenceQS__vfunc_42(int *arg0, int arg1) {
    unsigned short *d = *(unsigned short **)(arg0[4] + 16);
    long long v = d[arg1];
    if (v & 0x8000) { v &= 0x7FFF; v <<= 0x17; v = -v; } else v <<= 0x17;
    return v;
}
