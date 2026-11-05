/* 0x0029b3a8 — FUN_0029b3a8 (96 bytes). Recognises a 288-byte stream header (0x80, 0x00 lead bytes and the 6-byte DAT_004f4b68 tag at +282); always reports the header size. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
int FUN_0012aba0();
extern char DAT_004f4b68[];

int FUN_0029b3a8(unsigned char *header, int length, int *headerSize) {
    *headerSize = 288;
    if (length < 288) {
        return 0;
    }
    if (header[0] != 0x80) {
        return 0;
    }
    if (header[1] != 0) {
        return 0;
    }
    return FUN_0012aba0(header + 282, DAT_004f4b68, 6) == 0;
}
