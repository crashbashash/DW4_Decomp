/* MPS memory utilities: unrolled byte and word copies and fills. */
#include "dw4/cri/mps.h"

void UTY_MemcpyByte(void *dst, void *src, unsigned int n) {
    char *to = dst;
    char *from = src;
    int i;
    int a, b, c, d;

    for (i = n & 31; i != 0; i--) {
        *to++ = *from++;
    }
    for (n >>= 5; n != 0; n--) {
        a = *from++; b = *from++; c = *from++; d = *from++;
        to[0] = a; to[1] = b; to[2] = c; to[3] = d;
        a = *from++; b = *from++; c = *from++; d = *from++;
        to[4] = a; to[5] = b; to[6] = c; to[7] = d;
        a = *from++; b = *from++; c = *from++; d = *from++;
        to[8] = a; to[9] = b; to[10] = c; to[11] = d;
        a = *from++; b = *from++; c = *from++; d = *from++;
        to[12] = a; to[13] = b; to[14] = c; to[15] = d;
        to += 16;
        a = *from++; b = *from++; c = *from++; d = *from++;
        to[0] = a; to[1] = b; to[2] = c; to[3] = d;
        a = *from++; b = *from++; c = *from++; d = *from++;
        to[4] = a; to[5] = b; to[6] = c; to[7] = d;
        a = *from++; b = *from++; c = *from++; d = *from++;
        to[8] = a; to[9] = b; to[10] = c; to[11] = d;
        a = *from++; b = *from++; c = *from++; d = *from++;
        to[12] = a; to[13] = b; to[14] = c; to[15] = d;
        to += 16;
    }
}

void UTY_MemcpyDword(void *dst, void *src, unsigned int n) {
    int *to = dst;
    int *from = src;
    int i;
    int a, b, c, d;

    for (i = n & 15; i != 0; i--) {
        *to++ = *from++;
    }
    for (n >>= 4; n != 0; n--) {
        a = *from++; b = *from++; c = *from++; d = *from++;
        to[0] = a; to[1] = b; to[2] = c; to[3] = d;
        a = *from++; b = *from++; c = *from++; d = *from++;
        to[4] = a; to[5] = b; to[6] = c; to[7] = d;
        a = *from++; b = *from++; c = *from++; d = *from++;
        to[8] = a; to[9] = b; to[10] = c; to[11] = d;
        a = *from++; b = *from++; c = *from++; d = *from++;
        to[12] = a; to[13] = b; to[14] = c; to[15] = d;
        to += 16;
    }
}

/* Both fills work backwards from the end: the remainder first, then blocks of 16. */
void UTY_MemsetByte(void *dst, char value, unsigned int count) {
    char *p = (char *)dst + count;
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

void UTY_MemsetDword(void *dst, int value, unsigned int count) {
    int *p = (int *)dst + count;
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
