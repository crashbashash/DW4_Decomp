/* 0x002829f0 — FUN_002829f0 (200 bytes). For message base 0xA4000000 only, sends two byte-swapped words through FUN_002823f0: 0xA470xx00 with the high 7 bits of `value`, then base|xx00 with the low 7 bits. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
int FUN_002823f0(unsigned int message);

#define SWAP32(x) ((((x) & 0xFF) << 24) | (((x) & 0xFF00) << 8) | (((x) & 0xFF0000) >> 8) | (((x) & 0xFF000000) >> 24))

int FUN_002829f0(unsigned int base, unsigned int value) {
    unsigned int message;
    int result;

    if (base != 0xA4000000) {
        return -2;
    }
    message = (value & 0x7F00) + 0xA4700000;
    result = FUN_002823f0(SWAP32(message));
    if (result != 0) {
        return result;
    }
    message = ((value & 0x7F) << 8) + base;
    return FUN_002823f0(SWAP32(message));
}
