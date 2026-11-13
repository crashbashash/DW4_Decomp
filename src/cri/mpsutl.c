/* MPS memory utilities: unrolled byte and word copies and fills. */
#include "dw4/cri/mps.h"

void mpsutl_CopyBytes(char *dst, char *src, unsigned int n) {
    int i;
    int a, b, c, d;

    for (i = n & 31; i != 0; i--) {
        *dst++ = *src++;
    }
    for (n >>= 5; n != 0; n--) {
        a = *src++; b = *src++; c = *src++; d = *src++;
        dst[0] = a; dst[1] = b; dst[2] = c; dst[3] = d;
        a = *src++; b = *src++; c = *src++; d = *src++;
        dst[4] = a; dst[5] = b; dst[6] = c; dst[7] = d;
        a = *src++; b = *src++; c = *src++; d = *src++;
        dst[8] = a; dst[9] = b; dst[10] = c; dst[11] = d;
        a = *src++; b = *src++; c = *src++; d = *src++;
        dst[12] = a; dst[13] = b; dst[14] = c; dst[15] = d;
        dst += 16;
        a = *src++; b = *src++; c = *src++; d = *src++;
        dst[0] = a; dst[1] = b; dst[2] = c; dst[3] = d;
        a = *src++; b = *src++; c = *src++; d = *src++;
        dst[4] = a; dst[5] = b; dst[6] = c; dst[7] = d;
        a = *src++; b = *src++; c = *src++; d = *src++;
        dst[8] = a; dst[9] = b; dst[10] = c; dst[11] = d;
        a = *src++; b = *src++; c = *src++; d = *src++;
        dst[12] = a; dst[13] = b; dst[14] = c; dst[15] = d;
        dst += 16;
    }
}

void mpsutl_CopyWords(int *dst, int *src, unsigned int n) {
    int i;
    int a, b, c, d;

    for (i = n & 15; i != 0; i--) {
        *dst++ = *src++;
    }
    for (n >>= 4; n != 0; n--) {
        a = *src++; b = *src++; c = *src++; d = *src++;
        dst[0] = a; dst[1] = b; dst[2] = c; dst[3] = d;
        a = *src++; b = *src++; c = *src++; d = *src++;
        dst[4] = a; dst[5] = b; dst[6] = c; dst[7] = d;
        a = *src++; b = *src++; c = *src++; d = *src++;
        dst[8] = a; dst[9] = b; dst[10] = c; dst[11] = d;
        a = *src++; b = *src++; c = *src++; d = *src++;
        dst[12] = a; dst[13] = b; dst[14] = c; dst[15] = d;
        dst += 16;
    }
}

/* Both fills work backwards from the end: the remainder first, then blocks of 16. */
void mpsutl_FillBytes(char *dst, char value, unsigned int count) {
    char *p = dst + count;
    unsigned int n;

    for (n = count & 15; n != 0; n--) {
        *--p = value;
    }
    for (count >>= 4; count != 0; count--) {
        *--p = value; *--p = value; *--p = value; *--p = value;
        *--p = value; *--p = value; *--p = value; *--p = value;
        *--p = value; *--p = value; *--p = value; *--p = value;
        *--p = value; *--p = value; *--p = value; *--p = value;
    }
}

void mpsutl_FillWords(int *dst, int value, unsigned int count) {
    int *p = dst + count;
    unsigned int n;

    for (n = count & 15; n != 0; n--) {
        *--p = value;
    }
    for (count >>= 4; count != 0; count--) {
        *--p = value; *--p = value; *--p = value; *--p = value;
        *--p = value; *--p = value; *--p = value; *--p = value;
        *--p = value; *--p = value; *--p = value; *--p = value;
        *--p = value; *--p = value; *--p = value; *--p = value;
    }
}

void mpsutl_Init(void) {
}

void mpsutl_Finish(void) {
}
