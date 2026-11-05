/* 0x00262fe0 — FUN_00262fe0 (128 bytes). Writes a 36-byte header (tag byte 0x80, 0, big-endian length 32, then the FUN_00262ee8 body) into a buffer of size bytes; returns -1 when the buffer is too small, else 0 with the written size in *written. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
void FUN_00262a30(unsigned char *bytes, short value);
void FUN_00262ee8(unsigned char *bytes, int source);

int FUN_00262fe0(unsigned char *buffer, int size, int *written, int source) {
    if (written != 0) {
        *written = 0;
    }
    if (size < 36) {
        return -1;
    }
    buffer[1] = 0;
    buffer[0] = 0x80;
    FUN_00262a30(buffer + 2, 32);
    FUN_00262ee8(buffer + 4, source);
    *written = 36;
    return 0;
}
