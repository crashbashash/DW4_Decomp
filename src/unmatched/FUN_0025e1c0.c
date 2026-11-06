/* Copies count halfwords from buffer+offset to the start of buffer; the third argument is unused. */
void FUN_0025e120(short *dst, short *src, int count);

void FUN_0025e1c0(short *buffer, int offset, int unused, int count) {
    FUN_0025e120(buffer, buffer + offset, count);
}
