/* Copies a halfword run from row a to row 0 and from row a+b to row b of one buffer. */
/* FUN_0025e120 (0x25e120): copies count halfwords from src to dst. */
void FUN_0025e120(short *dst, short *src, int count);

void FUN_0025e150(short *buffer, int offset, int second, int count) {
    FUN_0025e120(buffer, buffer + offset, count);
    FUN_0025e120(buffer + second, buffer + (second + offset), count);
}
