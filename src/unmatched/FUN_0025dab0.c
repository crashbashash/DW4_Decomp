/* 0x0025dab0 — FUN_0025dab0 (96 bytes). Maps the decoder mode in f152 and sub-mode in f156 to a block size code: 16 by default, 4 or 8 for mode 2, 4 for mode 1 with sub-mode 2. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
/* CRI ADX decoder block as this function touches it; field meanings are not yet known */
typedef struct DecoderBlock {
    short f0;
    short state;
    char f4[8];
    unsigned char f12;
    unsigned char f13;
    signed char f14;
    signed char f15;
    int f16;
    int f20;
    int f24;
    short f28;
    short f30;
    int f32;
    short f36;
    short f38;
    int f40;
    int f44;
    int f48;
    int f52;
    char f56[4];
    int f60;
    int f64;
    int f68;
    char f72[8];
    int f80;
    int f84;
    int f88;
    int f92;
    int f96;
    int f100;
    char f104[32];
    int f136;
    int f140;
    char f144[8];
    short f152;
    unsigned short f154;
    short f156;
    short f158;
    unsigned short f160;
    unsigned short f162;
    unsigned short f164;
} DecoderBlock;

int FUN_0025dab0(DecoderBlock *block) {
    short mode = block->f152;

    if (mode == 0) {
        return 16;
    }
    if (mode == 2) {
        if (block->f156 == 2) {
            return 4;
        }
        if (block->f156 == 1) {
            return 8;
        }
        return 16;
    }
    if (mode == 1) {
        if (block->f156 == 2) {
            return 4;
        }
        return 16;
    }
    return 16;
}
