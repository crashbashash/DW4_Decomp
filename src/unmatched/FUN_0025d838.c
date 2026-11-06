/* Fills the decoder block with a fixed default format (48000 in f20, 2 in f14, 16 in f13, 127 in
 * f15) and clears its position counters. */
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

void FUN_0025d838(DecoderBlock *block) {
    block->state = 1;
    block->f20 = 48000;
    block->f14 = 2;
    block->f13 = 16;
    block->f24 = 0x7fffffff;
    block->f15 = 127;
    block->f16 = 1024;
    block->f152 = block->f154;
    block->f80 = 2;
    block->f84 = 127;
    block->f88 = 1024;
    block->f92 = block->f60;
    block->f96 = block->f64;
    block->f100 = block->f68;
    block->f140 = 0;
    block->f28 = 0;
    block->f36 = 0;
    block->f38 = 0;
    block->f32 = 0;
    block->f40 = 0;
    block->f44 = 0;
    block->f48 = 0;
    block->f52 = 0;
    block->f136 = 0;
}
